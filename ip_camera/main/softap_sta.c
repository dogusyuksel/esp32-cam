#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_mac.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif_net_stack.h"
#include "esp_netif.h"
#include "nvs_flash.h"
#include "lwip/inet.h"
#include "lwip/netdb.h"
#include "lwip/sockets.h"
#if IP_NAPT
#include "lwip/lwip_napt.h"
#endif
#include "lwip/err.h"
#include "lwip/sys.h"
#include <sys/param.h>
#include "protocol_examples_common.h"
#include "protocol_examples_utils.h"
#include <esp_http_server.h>
#include "esp_camera.h"
#include "esp_timer.h"
#include "esp_spiffs.h"

#ifndef ETH_ADDR_LEN
#define ETH_ADDR_LEN        (6)  /* MAC Address length */
#endif

esp_vfs_spiffs_conf_t spiffs_conf = {
    .base_path = "/spiffs",
    .partition_label = NULL,
    .max_files = 5,
    .format_if_mount_failed = true
};

#define STA_SSID_STR    "sta_ssid"
#define STA_PWD_STR     "sta_pwd"
#define AP_SSID_STR     "ap_ssid"
#define AP_PWD_STR      "ap_pwd"
#define CAM_RESOL       "cam_resol"
#define CAM_QUAL        "cam_qual"

#define STA_SSID_FILE_NAME  "/spiffs/sta_ssid.txt"
#define STA_PWD_FILE_NAME   "/spiffs/sta_pwd.txt"
#define AP_SSID_FILE_NAME   "/spiffs/ap_ssid.txt"
#define AP_PWD_FILE_NAME    "/spiffs/ap_pwd.txt"

/* STA Configuration */
#define EXAMPLE_ESP_WIFI_STA_SSID           CONFIG_ESP_WIFI_REMOTE_AP_SSID
#define EXAMPLE_ESP_WIFI_STA_PASSWD         CONFIG_ESP_WIFI_REMOTE_AP_PASSWORD
#define EXAMPLE_ESP_MAXIMUM_RETRY           CONFIG_ESP_MAXIMUM_STA_RETRY

#if CONFIG_ESP_WIFI_AUTH_OPEN
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD   WIFI_AUTH_OPEN
#elif CONFIG_ESP_WIFI_AUTH_WEP
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD   WIFI_AUTH_WEP
#elif CONFIG_ESP_WIFI_AUTH_WPA_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD   WIFI_AUTH_WPA_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA2_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD   WIFI_AUTH_WPA2_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA_WPA2_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD   WIFI_AUTH_WPA_WPA2_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA3_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD   WIFI_AUTH_WPA3_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA2_WPA3_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD   WIFI_AUTH_WPA2_WPA3_PSK
#elif CONFIG_ESP_WIFI_AUTH_WAPI_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD   WIFI_AUTH_WAPI_PSK
#endif

/* AP Configuration */
#define EXAMPLE_ESP_WIFI_AP_SSID            CONFIG_ESP_WIFI_AP_SSID
#define EXAMPLE_ESP_WIFI_AP_PASSWD          CONFIG_ESP_WIFI_AP_PASSWORD
#define EXAMPLE_ESP_WIFI_CHANNEL            CONFIG_ESP_WIFI_AP_CHANNEL
#define EXAMPLE_MAX_STA_CONN                CONFIG_ESP_MAX_STA_CONN_AP


/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

/*DHCP server option*/
#define DHCPS_OFFER_DNS             0x02

static const char *TAG = "IPCAM";

static int s_retry_num = 0;

/* FreeRTOS event group to signal when we are connected/disconnected */
static EventGroupHandle_t s_wifi_event_group;

static httpd_handle_t server = NULL;
#define PART_BOUNDARY "123456789000000000000987654321"
static const char* _STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char* _STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char* _STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";

#define BOARD_ESP32CAM_AITHINKER

// WROVER-KIT PIN Map
#ifdef BOARD_WROVER_KIT

#define CAM_PIN_PWDN -1  //power down is not used
#define CAM_PIN_RESET -1 //software reset will be performed
#define CAM_PIN_XCLK 21
#define CAM_PIN_SIOD 26
#define CAM_PIN_SIOC 27

#define CAM_PIN_D7 35
#define CAM_PIN_D6 34
#define CAM_PIN_D5 39
#define CAM_PIN_D4 36
#define CAM_PIN_D3 19
#define CAM_PIN_D2 18
#define CAM_PIN_D1 5
#define CAM_PIN_D0 4
#define CAM_PIN_VSYNC 25
#define CAM_PIN_HREF 23
#define CAM_PIN_PCLK 22

#endif

// ESP32Cam (AiThinker) PIN Map
#ifdef BOARD_ESP32CAM_AITHINKER

#define CAM_PIN_PWDN 32
#define CAM_PIN_RESET -1 //software reset will be performed
#define CAM_PIN_XCLK 0
#define CAM_PIN_SIOD 26
#define CAM_PIN_SIOC 27

#define CAM_PIN_D7 35
#define CAM_PIN_D6 34
#define CAM_PIN_D5 39
#define CAM_PIN_D4 36
#define CAM_PIN_D3 21
#define CAM_PIN_D2 19
#define CAM_PIN_D1 18
#define CAM_PIN_D0 5
#define CAM_PIN_VSYNC 25
#define CAM_PIN_HREF 23
#define CAM_PIN_PCLK 22

#endif
// ESP32S3 (WROOM) PIN Map
#ifdef BOARD_ESP32S3_WROOM
#define CAM_PIN_PWDN 38
#define CAM_PIN_RESET -1   //software reset will be performed
#define CAM_PIN_VSYNC 6
#define CAM_PIN_HREF 7
#define CAM_PIN_PCLK 13
#define CAM_PIN_XCLK 15
#define CAM_PIN_SIOD 4
#define CAM_PIN_SIOC 5
#define CAM_PIN_D0 11
#define CAM_PIN_D1 9
#define CAM_PIN_D2 8
#define CAM_PIN_D3 10
#define CAM_PIN_D4 12
#define CAM_PIN_D5 18
#define CAM_PIN_D6 17
#define CAM_PIN_D7 16
#endif

static camera_config_t camera_config = {
    .pin_pwdn = CAM_PIN_PWDN,
    .pin_reset = CAM_PIN_RESET,
    .pin_xclk = CAM_PIN_XCLK,
    .pin_sccb_sda = CAM_PIN_SIOD,
    .pin_sccb_scl = CAM_PIN_SIOC,

    .pin_d7 = CAM_PIN_D7,
    .pin_d6 = CAM_PIN_D6,
    .pin_d5 = CAM_PIN_D5,
    .pin_d4 = CAM_PIN_D4,
    .pin_d3 = CAM_PIN_D3,
    .pin_d2 = CAM_PIN_D2,
    .pin_d1 = CAM_PIN_D1,
    .pin_d0 = CAM_PIN_D0,
    .pin_vsync = CAM_PIN_VSYNC,
    .pin_href = CAM_PIN_HREF,
    .pin_pclk = CAM_PIN_PCLK,

    //XCLK 20MHz or 10MHz for OV2640 double FPS (Experimental)
    .xclk_freq_hz = 20000000,
    .ledc_timer = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0,

    .pixel_format = PIXFORMAT_JPEG, //YUV422,GRAYSCALE,RGB565,JPEG
    .frame_size = FRAMESIZE_VGA,    //QQVGA-UXGA, For ESP32, do not use sizes above QVGA when not JPEG. The performance of the ESP32-S series has improved a lot, but JPEG mode always gives better frame rates.

    .jpeg_quality = 16, //0-63, for OV series camera sensors, lower number means higher quality
    .fb_count = 1,       //When jpeg mode is used, if fb_count more than one, the driver will work in continuous mode.
    .fb_location = CAMERA_FB_IN_PSRAM,
    .grab_mode = CAMERA_GRAB_WHEN_EMPTY,
};

static esp_err_t init_camera(void)
{
    //initialize the camera
    esp_err_t err = esp_camera_init(&camera_config);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Camera Init Failed");
        return err;
    }

    return ESP_OK;
}

static int spiffs_config_read(char *file, char *data, uint16_t sizeofdata)
{
    if (!file || !data) {
        return 1;
    }

    struct stat st;
    if (stat(file, &st) == 0) {
        FILE *f = fopen(file, "r");
        if (f == NULL) {
            ESP_LOGE(TAG, "Failed to open file for reading");
            return 1;
        }
        fgets(data, sizeofdata, f);
        fclose(f);
        data[strlen(data) - 1] = '\0';
        ESP_LOGI(TAG, "data read from file: %s", data);
    } else {
        return 1;
    }

    return 0;
}

static int spiffs_config_write(char *file, char *data)
{
    if (!file || !data) {
        return 1;
    }

    unlink(file);
    FILE *f = fopen(file, "w");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return 1;
    }
    fprintf(f, "%s\n", data);
    fclose(f);
    ESP_LOGI(TAG, "File written");

    return 0;
}

static esp_err_t jpg_stream_httpd_handler(httpd_req_t *req){
    camera_fb_t * fb = NULL;
    esp_err_t res = ESP_OK;
    size_t _jpg_buf_len;
    uint8_t * _jpg_buf;
    char * part_buf[64];
    static int64_t last_frame = 0;
    if(!last_frame) {
        last_frame = esp_timer_get_time();
    }

    res = httpd_resp_set_type(req, _STREAM_CONTENT_TYPE);
    if(res != ESP_OK){
        return res;
    }

    while(true){
        fb = esp_camera_fb_get();
        if (!fb) {
            ESP_LOGE(TAG, "Camera capture failed");
            res = ESP_FAIL;
            break;
        }
        if(fb->format != PIXFORMAT_JPEG){
            bool jpeg_converted = frame2jpg(fb, 80, &_jpg_buf, &_jpg_buf_len);
            if(!jpeg_converted){
                ESP_LOGE(TAG, "JPEG compression failed");
                esp_camera_fb_return(fb);
                res = ESP_FAIL;
            }
        } else {
            _jpg_buf_len = fb->len;
            _jpg_buf = fb->buf;
        }

        if(res == ESP_OK){
            res = httpd_resp_send_chunk(req, _STREAM_BOUNDARY, strlen(_STREAM_BOUNDARY));
        }
        if(res == ESP_OK){
            size_t hlen = snprintf((char *)part_buf, 64, _STREAM_PART, _jpg_buf_len);

            res = httpd_resp_send_chunk(req, (const char *)part_buf, hlen);
        }
        if(res == ESP_OK){
            res = httpd_resp_send_chunk(req, (const char *)_jpg_buf, _jpg_buf_len);
        }
        if(fb->format != PIXFORMAT_JPEG){
            free(_jpg_buf);
        }
        esp_camera_fb_return(fb);
        if(res != ESP_OK){
            break;
        }
        int64_t fr_end = esp_timer_get_time();
        int64_t frame_time = fr_end - last_frame;
        last_frame = fr_end;
        frame_time /= 1000;
        ESP_LOGI(TAG, "MJPG: %luKB %lums (%.1ffps)",
            (uint32_t)(_jpg_buf_len/1024),
            (uint32_t)frame_time, 1000.0 / (uint32_t)frame_time);
    }

    last_frame = 0;
    return res;
}

static void update_config(char *conf_name, char *conf_value)
{
    if (!conf_name || !conf_value) {
        return;
    }

    if (strstr(conf_value, "NONE")) {
        return;
    }

    if (strstr(conf_name, STA_SSID_STR)) {
        if (strstr(conf_value, "clear")) {
            unlink(STA_SSID_FILE_NAME);
        } else {
            spiffs_config_write(STA_SSID_FILE_NAME, conf_value);
        }
    } else if (strstr(conf_name, STA_PWD_STR)) {
        if (strstr(conf_value, "clear")) {
            unlink(STA_PWD_FILE_NAME);
        } else {
            spiffs_config_write(STA_PWD_FILE_NAME, conf_value);
        }
    }  else if (strstr(conf_name, AP_SSID_STR)) {
        if (strstr(conf_value, "clear")) {
            unlink(AP_SSID_FILE_NAME);
        } else {
            spiffs_config_write(AP_SSID_FILE_NAME, conf_value);
        }
    }   else if (strstr(conf_name, AP_PWD_STR)) {
        if (strstr(conf_value, "clear")) {
            unlink(AP_PWD_FILE_NAME);
        } else {
            spiffs_config_write(AP_PWD_FILE_NAME, conf_value);
        }
    } else {
        ESP_LOGI(TAG, "unsupported config: %s:%s", conf_name, conf_value);
    }
}

static const httpd_uri_t jpegstream = {
    .uri       = "/jpegstream",
    .method    = HTTP_ANY,
    .handler   = jpg_stream_httpd_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx  = "Hello World!"
};

/* An HTTP POST handler */
static esp_err_t setconfig_post_handler(httpd_req_t *req)
{
    char buf[100];
    int ret, remaining = req->content_len;

    while (remaining > 0) {
        /* Read the data for the request */
        if ((ret = httpd_req_recv(req, buf,
                        MIN(remaining, sizeof(buf)))) <= 0) {
            if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
                /* Retry receiving if timeout occurred */
                continue;
            }
            return ESP_FAIL;
        }

        /* Send back the same data */
        httpd_resp_send_chunk(req, buf, ret);
        remaining -= ret;

        /* Log data received */
        ESP_LOGI(TAG, "=========== RECEIVED DATA ==========");
        ESP_LOGI(TAG, "%.*s", ret, buf);
        ESP_LOGI(TAG, "%s", buf);

        uint8_t item_counter = 0;
        char *token1 = NULL, *restbuff1 = NULL, *str1 = NULL;
        char *token2 = NULL, *restbuff2 = NULL, *str2 = NULL;

        for (str1 = buf;; str1 = NULL) {
            token1 = strtok_r(str1, "&", &restbuff1);
            if (token1 == NULL)
                break;
            ESP_LOGI(TAG, " --> %s", token1);

            if (strchr(token1, (int)'=')) {
                char conf_name[64] = {0};
                for (str2 = token1;; str2 = NULL) {
                    token2 = strtok_r(str2, "=", &restbuff2);
                    if (token2 == NULL)
                        break;
                    ESP_LOGI(TAG, "	--> %s", token2);

                    if (item_counter%2 == 0) {
                        // it is name
                        strcpy(conf_name, token2);
                    } else {
                        //it is value, so update it
                        update_config(conf_name, token2);
                    }
                    item_counter++;
                }
            }
        }
        ESP_LOGI(TAG, "====================================");
    }

    // End response
    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}

static const httpd_uri_t setconfig = {
    .uri       = "/setconfig",
    .method    = HTTP_POST,
    .handler   = setconfig_post_handler,
    .user_ctx  = NULL
};

static httpd_handle_t start_webserver(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.server_port = 80;
    config.lru_purge_enable = true;

    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");
        httpd_register_uri_handler(server, &jpegstream);
        httpd_register_uri_handler(server, &setconfig);
        return server;
    }

    ESP_LOGI(TAG, "Error starting server!");
    return NULL;
}

static esp_err_t stop_webserver(httpd_handle_t server)
{
    // Stop the httpd server
    return httpd_stop(server);
}

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *) event_data;
        ESP_LOGI(TAG, "Station "MACSTR" joined, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t *event = (wifi_event_ap_stadisconnected_t *) event_data;
        ESP_LOGI(TAG, "Station "MACSTR" left, AID=%d, reason:%d",
                 MAC2STR(event->mac), event->aid, event->reason);
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
        ESP_LOGI(TAG, "Station started");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *) event_data;
        ESP_LOGI(TAG, "Got IP:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
        
        if (server == NULL) {
            ESP_LOGI(TAG, "Starting webserver");
            server = start_webserver();
        }
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        ESP_LOGI(TAG, "Disconnected");
        if (server) {
            ESP_LOGI(TAG, "Stopping webserver");
            if (stop_webserver(server) == ESP_OK) {
                server = NULL;
            } else {
                ESP_LOGE(TAG, "Failed to stop http server");
            }
        }
    }
}

/* Initialize soft AP */
esp_netif_t *wifi_init_softap(char *ap_ssid, char *ap_pwd)
{
    if (!ap_ssid || !ap_pwd) {
        return NULL;
    }

    esp_netif_t *esp_netif_ap = esp_netif_create_default_wifi_ap();

    wifi_config_t wifi_ap_config = {
        .ap = {
            .ssid = EXAMPLE_ESP_WIFI_AP_SSID,
            .ssid_len = strlen(EXAMPLE_ESP_WIFI_AP_SSID),
            .channel = EXAMPLE_ESP_WIFI_CHANNEL,
            .password = EXAMPLE_ESP_WIFI_AP_PASSWD,
            .max_connection = EXAMPLE_MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA2_PSK,
            .pmf_cfg = {
                .required = false,
            },
        },
    };
    uint16_t copy_len = strlen(ap_ssid);
    if (sizeof(wifi_ap_config.ap.ssid) < copy_len) {
        copy_len = sizeof(wifi_ap_config.ap.ssid);
    }
    memcpy(wifi_ap_config.ap.ssid, (uint8_t *)ap_ssid, copy_len);
    wifi_ap_config.ap.ssid_len = copy_len;

    copy_len = strlen(ap_pwd);
    if (sizeof(wifi_ap_config.ap.password) < copy_len) {
        copy_len = sizeof(wifi_ap_config.ap.password);
    }
    memcpy(wifi_ap_config.ap.password, (uint8_t *)ap_pwd, copy_len);

    if (strlen((char *)wifi_ap_config.ap.password) == 0) {
        wifi_ap_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_ap_config));

    ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s channel:%d",
             wifi_ap_config.ap.ssid, wifi_ap_config.ap.password, EXAMPLE_ESP_WIFI_CHANNEL);

    return esp_netif_ap;
}

/* Initialize wifi station */
esp_netif_t *wifi_init_sta(char *sta_ssid, char *sta_pwd)
{
    if (!sta_ssid || !sta_pwd) {
        return NULL;
    }

    esp_netif_t *esp_netif_sta = esp_netif_create_default_wifi_sta();

    wifi_config_t wifi_sta_config = {
        .sta = {
            .ssid = EXAMPLE_ESP_WIFI_STA_SSID,
            .password = EXAMPLE_ESP_WIFI_STA_PASSWD,
            .scan_method = WIFI_ALL_CHANNEL_SCAN,
            .failure_retry_cnt = EXAMPLE_ESP_MAXIMUM_RETRY,
            /* Authmode threshold resets to WPA2 as default if password matches WPA2 standards (password len => 8).
             * If you want to connect the device to deprecated WEP/WPA networks, Please set the threshold value
             * to WIFI_AUTH_WEP/WIFI_AUTH_WPA_PSK and set the password with length and format matching to
            * WIFI_AUTH_WEP/WIFI_AUTH_WPA_PSK standards.
             */
            .threshold.authmode = ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD,
            .sae_pwe_h2e = WPA3_SAE_PWE_BOTH,
        },
    };

    uint16_t copy_len = strlen(sta_ssid);
    if (sizeof(wifi_sta_config.sta.ssid) < copy_len) {
        copy_len = sizeof(wifi_sta_config.sta.ssid);
    }
    memcpy(wifi_sta_config.sta.ssid, (uint8_t *)sta_ssid, copy_len);
    copy_len = strlen(sta_pwd);
    if (sizeof(wifi_sta_config.sta.password) < copy_len) {
        copy_len = sizeof(wifi_sta_config.sta.password);
    }
    memcpy(wifi_sta_config.sta.password, (uint8_t *)sta_pwd, copy_len);

    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_sta_config) );

    ESP_LOGI(TAG, "wifi_init_sta finished.");

    return esp_netif_sta;
}

void softap_set_dns_addr(esp_netif_t *esp_netif_ap,esp_netif_t *esp_netif_sta)
{
    esp_netif_dns_info_t dns;
    esp_netif_get_dns_info(esp_netif_sta,ESP_NETIF_DNS_MAIN,&dns);
    uint8_t dhcps_offer_option = DHCPS_OFFER_DNS;
    ESP_ERROR_CHECK_WITHOUT_ABORT(esp_netif_dhcps_stop(esp_netif_ap));
    ESP_ERROR_CHECK(esp_netif_dhcps_option(esp_netif_ap, ESP_NETIF_OP_SET, ESP_NETIF_DOMAIN_NAME_SERVER, &dhcps_offer_option, sizeof(dhcps_offer_option)));
    ESP_ERROR_CHECK(esp_netif_set_dns_info(esp_netif_ap, ESP_NETIF_DNS_MAIN, &dns));
    ESP_ERROR_CHECK_WITHOUT_ABORT(esp_netif_dhcps_start(esp_netif_ap));
}

static void spiffs_init(void)
{
    ESP_LOGI(TAG, "Initializing SPIFFS");

    // Use settings defined above to initialize and mount SPIFFS filesystem.
    // Note: esp_vfs_spiffs_register is an all-in-one convenience function.
    esp_err_t ret = esp_vfs_spiffs_register(&spiffs_conf);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(spiffs_conf.partition_label, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s). Formatting...", esp_err_to_name(ret));
        esp_spiffs_format(spiffs_conf.partition_label);
        return;
    } else {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    }

    // Check consistency of reported partition size info.
    if (used > total) {
        ESP_LOGW(TAG, "Number of used bytes cannot be larger than total. Performing SPIFFS_check().");
        ret = esp_spiffs_check(spiffs_conf.partition_label);
        // Could be also used to mend broken files, to clean unreferenced pages, etc.
        // More info at https://github.com/pellepl/spiffs/wiki/FAQ#powerlosses-contd-when-should-i-run-spiffs_check
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "SPIFFS_check() failed (%s)", esp_err_to_name(ret));
            return;
        } else {
            ESP_LOGI(TAG, "SPIFFS_check() successful");
        }
    }
}

static void spiffs_deinit(void)
{
    // All done, unmount partition and disable SPIFFS
    esp_vfs_spiffs_unregister(spiffs_conf.partition_label);
    ESP_LOGI(TAG, "SPIFFS unmounted");
}

static int get_string_from_console(char *buffer, uint16_t buffer_size, char *tag, uint16_t timeout)
{
    int ret = 0;
    int count = 0;
    uint16_t timeout_in_ms = timeout;
    uint8_t delay_between_checks = 10;
    uint16_t iteration_counter = 0;

    if (!buffer || !tag) {
        return 2;
    }

    ESP_LOGI(TAG, "type %s please: ", tag);
    while (count < buffer_size) {
        int c = fgetc(stdin);
        if (c == '\n') {
            buffer[count] = '\0';
            break;
        } else if (c > 0 && c < (buffer_size - 1)) {
            buffer[count] = c;
            ++count;
            iteration_counter = 0;
        }
        vTaskDelay(delay_between_checks / portTICK_PERIOD_MS);
        iteration_counter++;
        if (iteration_counter > (timeout_in_ms / delay_between_checks)) {
            ESP_LOGI(TAG, "timeout");
            ret = 1;
            break;
        }
    }
    if(strlen(buffer) < 2) {
        // use already saved
        ret = 1;
    }
    ESP_LOGI(TAG, "user typed %s: %s", tag, buffer);

    return ret;
}

static void get_set_ssid_and_pwd(char *ssid, uint8_t size_ssid, char *pwd, uint8_t size_pwd,
                                char *ap_ssid, uint8_t ap_size_ssid, char *ap_pwd, uint8_t ap_size_pwd)
{
    char sta_ssid_we_have[128] = {0};
    char sta_pwd_we_have[128] = {0};
    char ap_ssid_we_have[128] = {0};
    char ap_pwd_we_have[128] = {0};

    if (!ssid || !pwd || !ap_ssid || !ap_pwd) {
        ESP_LOGE(TAG, "args are null");
        return;
    }

    spiffs_init();

    // // remove unlinks later
    // unlink(STA_SSID_FILE_NAME);
    // unlink(STA_PWD_FILE_NAME);
    // unlink(AP_SSID_FILE_NAME);
    // unlink(AP_PWD_FILE_NAME);

    if (spiffs_config_read(STA_SSID_FILE_NAME, sta_ssid_we_have, sizeof(sta_ssid_we_have)) != 0) {
        strcpy(sta_ssid_we_have, EXAMPLE_ESP_WIFI_STA_SSID);
    }
    if (spiffs_config_read(STA_PWD_FILE_NAME, sta_pwd_we_have, sizeof(sta_pwd_we_have)) != 0) {
        strcpy(sta_pwd_we_have, EXAMPLE_ESP_WIFI_STA_PASSWD);
    }
    if (spiffs_config_read(AP_SSID_FILE_NAME, ap_ssid_we_have, sizeof(ap_ssid_we_have)) != 0) {
        uint8_t i = 0, j = 0;
        char mac_str[128] = {0};
        uint8_t base_mac_addr[ETH_ADDR_LEN];

        esp_efuse_mac_get_default(base_mac_addr);
        for (i = 0; i < ETH_ADDR_LEN; i++, j += 2) {
            sprintf(&mac_str[j], "%.02X", base_mac_addr[i]);
        }
        ESP_LOGI(TAG, "my mac: %s", mac_str);
        strcpy(ap_ssid_we_have, mac_str);
    }
    if (spiffs_config_read(AP_PWD_FILE_NAME, ap_pwd_we_have, sizeof(ap_pwd_we_have)) != 0) {
        strcpy(ap_pwd_we_have, EXAMPLE_ESP_WIFI_AP_PASSWD);
    }

    if (get_string_from_console(ssid, size_ssid, "sta_ssid", 5000) != 0) {
        strcpy(ssid, sta_ssid_we_have);
    }

    if (get_string_from_console(pwd, size_pwd, "sta_pwd", 5000) != 0) {
        strcpy(pwd, sta_pwd_we_have);
    }

    if (get_string_from_console(ap_ssid, ap_size_ssid, "ap_ssid", 5000) != 0) {
        strcpy(ap_ssid, ap_ssid_we_have);
    }

    if (get_string_from_console(ap_pwd, ap_size_pwd, "ap_pwd", 5000) != 0) {
        strcpy(ap_pwd, ap_pwd_we_have);
    }

    spiffs_config_write(STA_SSID_FILE_NAME, ssid);
    spiffs_config_write(STA_PWD_FILE_NAME, pwd);
    spiffs_config_write(AP_SSID_FILE_NAME, ap_ssid);
    spiffs_config_write(AP_PWD_FILE_NAME, ap_pwd);

    //spiffs_deinit();
}

void app_main(void)
{
    char sta_ssid[128] = {0};
    char sta_pwd[128] = {0};
    char ap_ssid[128] = {0};
    char ap_pwd[128] = {0};

    get_set_ssid_and_pwd(sta_ssid, sizeof(sta_ssid), sta_pwd, sizeof(sta_pwd),
                        ap_ssid, sizeof(ap_ssid), ap_pwd, sizeof(ap_pwd));
    ESP_LOGI(TAG, "final decision sta_ssid: %s", sta_ssid);
    ESP_LOGI(TAG, "final decision sta_pwd:  %s", sta_pwd);
    ESP_LOGI(TAG, "final decision ap_ssid:  %s", ap_ssid);
    ESP_LOGI(TAG, "final decision ap_pwd:   %s", ap_pwd);

    if(ESP_OK != init_camera()) {
        return;
    }

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    /* Initialize event group */
    s_wifi_event_group = xEventGroupCreate();

    /* Register Event handler */
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                    ESP_EVENT_ANY_ID,
                    &wifi_event_handler,
                    NULL,
                    NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                    IP_EVENT_STA_GOT_IP,
                    &wifi_event_handler,
                    NULL,
                    NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                    WIFI_EVENT_STA_DISCONNECTED,
                    &wifi_event_handler,
                    NULL,
                    NULL));
    

    /*Initialize WiFi */
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));

    /* Initialize AP */
    ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");
    esp_netif_t *esp_netif_ap = wifi_init_softap(ap_ssid, ap_pwd);

    /* Initialize STA */
    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    esp_netif_t *esp_netif_sta = wifi_init_sta(sta_ssid, sta_pwd);

    /* Start WiFi */
    ESP_ERROR_CHECK(esp_wifi_start() );

    /*
     * Wait until either the connection is established (WIFI_CONNECTED_BIT) or
     * connection failed for the maximum number of re-tries (WIFI_FAIL_BIT).
     * The bits are set by event_handler() (see above)
     */
    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                           WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                           pdFALSE,
                                           pdFALSE,
                                           portMAX_DELAY);

    /* xEventGroupWaitBits() returns the bits before the call returned,
     * hence we can test which event actually happened. */
    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
                 sta_ssid, sta_pwd);
        softap_set_dns_addr(esp_netif_ap,esp_netif_sta);
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
                 sta_ssid, sta_pwd);
    } else {
        ESP_LOGE(TAG, "UNEXPECTED EVENT");
        return;
    }

    /* Set sta as the default interface */
    esp_netif_set_default_netif(esp_netif_sta);

    /* Enable napt on the AP netif */
    if (esp_netif_napt_enable(esp_netif_ap) != ESP_OK) {
        ESP_LOGE(TAG, "NAPT not enabled on the netif: %p", esp_netif_ap);
    }
}
