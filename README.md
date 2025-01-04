ESP32-camera module development environment
==============

# General View

<img src="./docs/images/img1.jpeg" width="200" height="200" />
<img src="./docs/images/img2.jpeg" width="200" height="200" />

# PinOut

<img src="./docs/images/img3.jpeg" width="200" height="200" />

# Helper Board for Flashing

<img src="./docs/images/img4.jpeg" width="200" height="200" />


# Starting Point

[Follow the steps in github actions](./.github/workflows/build-and-tests.yml)


# How To Build

* go into any project and type

```
idf.py build
```

# How To Flash

Use the following command

```
idf.py -p /dev/ttyUSB0 flash
```

# How to See Output

```
root:/workspace/ip_camera# idf.py -p /dev/ttyUSB0 flash monitor
````
<details><summary>Logs</summary>root:/workspace/ip_camera# idf.py -p /dev/ttyUSB0 flash monitor

I (30) boot: ESP-IDF v5.3.2 2nd stage bootloader

I (30) boot: compile time Jan  3 2025 16:54:33

I (30) boot: Multicore bootloader

I (34) boot: chip revision: v1.1

I (38) boot.esp32: SPI Speed      : 40MHz

I (43) boot.esp32: SPI Mode       : DIO

I (47) boot.esp32: SPI Flash Size : 2MB

I (52) boot: Enabling RNG early entropy source...

I (57) boot: Partition Table:

I (61) boot: ## Label            Usage          Type ST Offset   Length

I (68) boot:  0 nvs              WiFi data        01 02 00009000 00006000

I (75) boot:  1 phy_init         RF data          01 01 0000f000 00001000

I (83) boot:  2 factory          factory app      00 00 00010000 00100000

I (90) boot: End of partition table

I (95) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=25b80h (154496) map

I (156) esp_image: segment 1: paddr=00035ba8 vaddr=3ffb0000 size=051e0h ( 20960) load

I (164) esp_image: segment 2: paddr=0003ad90 vaddr=40080000 size=05288h ( 21128) load

I (173) esp_image: segment 3: paddr=00040020 vaddr=400d0020 size=a4600h (673280) map

I (403) esp_image: segment 4: paddr=000e4628 vaddr=40085288 size=18354h ( 99156) load

I (457) boot: Loaded app from partition at offset 0x10000

I (457) boot: Disabling RNG early entropy source...

I (470) quad_psram: This chip is ESP32-D0WD

I (472) esp_psram: Found 8MB PSRAM device

I (472) esp_psram: Speed: 40MHz

I (473) esp_psram: PSRAM initialized, cache is in low/high (2-core) mode.

W (481) esp_psram: Virtual address not enough for PSRAM, map as much as we can. 4MB is mapped

I (490) cpu_start: Multicore app

I (1397) esp_psram: SPI SRAM memory test OK

I (1405) cpu_start: Pro cpu start user code

I (1405) cpu_start: cpu freq: 160000000 Hz

I (1405) app_init: Application information:

I (1408) app_init: Project name:     softap_sta

I (1413) app_init: App version:      4f40319-dirty

I (1419) app_init: Compile time:     Jan  4 2025 14:03:18

I (1425) app_init: ELF file SHA256:  6469049c4...

I (1430) app_init: ESP-IDF:          v5.3.2

I (1435) efuse_init: Min chip rev:     v0.0

I (1440) efuse_init: Max chip rev:     v3.99 

I (1445) efuse_init: Chip rev:         v1.1

I (1450) heap_init: Initializing. RAM available for dynamic allocation:

I (1457) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM

I (1463) heap_init: At 3FFBB4B0 len 00024B50 (146 KiB): DRAM

I (1469) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM

I (1476) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM

I (1482) heap_init: At 4009D5DC len 00002A24 (10 KiB): IRAM

I (1489) esp_psram: Adding pool of 4096K of PSRAM memory to heap allocator

I (1498) spi_flash: detected chip: generic

I (1501) spi_flash: flash io: dio

W (1505) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.

W (1518) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`

I (1530) main_task: Started on CPU0

I (1540) esp_psram: Reserving pool of 32K of internal memory for DMA/internal allocations

I (1540) main_task: Calling app_main()

I (1540) gpio: GPIO[25]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:2 

I (1550) cam_hal: cam init ok

I (1560) sccb: pin_sda 26 pin_scl 27

I (1560) sccb: sccb_i2c_port=1

I (1560) gpio: GPIO[32]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 0| Pulldown: 0| Intr:0 

I (1600) camera: Detected camera at address=0x30

I (1600) camera: Detected OV2640 camera

I (1600) camera: Camera PID=0x26 VER=0x42 MIDL=0x7f MIDH=0xa2

I (1690) cam_hal: buffer_size: 32768, half_buffer_size: 4096, node_buffer_size: 2048, node_cnt: 16, total_cnt: 15

I (1690) cam_hal: Allocating 61440 Byte frame buffer in PSRAM

I (1690) cam_hal: cam config ok

I (1700) ov2640: Set PLL: clk_2x: 0, clk_div: 0, pclk_auto: 0, pclk_div: 8

I (1830) wifi:wifi driver task: 3ffd3e68, prio:23, stack:6656, core=0

I (1840) wifi:wifi firmware version: b0fd6006b

I (1840) wifi:wifi certification version: v7.0

I (1840) wifi:config NVS flash: enabled

I (1840) wifi:config nano formating: disabled

I (1850) wifi:Init data frame dynamic rx buffer num: 32

I (1850) wifi:Init static rx mgmt buffer num: 5

I (1860) wifi:Init management short buffer num: 32

I (1860) wifi:Init static tx buffer num: 16

I (1870) wifi:Init tx cache buffer num: 32

I (1870) wifi:Init static rx buffer size: 1600

I (1870) wifi:Init static rx buffer num: 10

I (1880) wifi:Init dynamic rx buffer num: 32

I (1880) wifi_init: rx ba win: 6

I (1890) wifi_init: accept mbox: 6

I (1890) wifi_init: tcpip mbox: 32

I (1890) wifi_init: udp mbox: 6

I (1900) wifi_init: tcp mbox: 6

I (1900) wifi_init: tcp tx win: 5760

I (1910) wifi_init: tcp rx win: 5760

I (1910) wifi_init: tcp mss: 1440

I (1910) wifi_init: WiFi IRAM OP enabled

I (1920) wifi_init: WiFi RX IRAM OP enabled

I (1920) WiFi SoftAP: ESP_WIFI_MODE_AP

I (1930) WiFi SoftAP: wifi_init_softap finished. SSID:dodossid password:mypassword channel:1

I (1940) WiFi Sta: ESP_WIFI_MODE_STA

I (1990) WiFi Sta: wifi_init_sta finished.

I (1990) phy_init: phy_version 4840,02e0d70,Sep  2 2024,19:39:07

I (2060) wifi:mode : sta (fc:b4:67:01:c1:80) + softAP (fc:b4:67:01:c1:81)

I (2070) wifi:enable tsf

I (2070) wifi:Total power save buffer number: 8

I (2070) wifi:Init max length of beacon: 752/752

I (2070) wifi:Init max length of beacon: 752/752

I (2080) WiFi Sta: Station started

I (2080) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1

I (5190) wifi:ap channel adjust o:1,1 n:6,2

I (5190) wifi:new:<6,0>, old:<1,1>, ap:<6,2>, sta:<6,0>, prof:1, snd_ch_cfg:0x0

I (5200) wifi:state: init -> auth (0xb0)

I (5220) wifi:state: auth -> assoc (0x0)

I (5330) wifi:state: assoc -> run (0x10)

I (6430) wifi:connected with VM7326524, aid = 2, channel 6, BW20, bssid = 18:35:d1:a6:c1:c9

I (6430) wifi:security: WPA2-PSK, phy: bgn, rssi: -54

I (6450) wifi:pm start, type: 1



I (6450) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us

I (6450) wifi:AP's beacon interval = 102400 us, DTIM period = 1

I (9130) wifi:<ba-add>idx:0 (ifx:0, 18:35:d1:a6:c1:c9), tid:0, ssn:1, winSize:64

I (9960) WiFi Sta: Got IP:192.168.0.29

I (9960) camera_http_server: Starting webserver

I (9960) camera_http_server: Starting server on port: '80'

I (9960) WiFi Sta: connected to ap SSID:myssid password:mypassword

I (9960) camera_http_server: Registering URI handlers

I (9970) esp_netif_handlers: sta ip: 192.168.0.29, mask: 255.255.255.0, gw: 192.168.0.1

W (9980) esp_netif_lwip: napt disabled on esp_netif:0x3ffdfc80

I (9990) main_task: Returned from app_main()

I (70880) camera_http_server: MJPG: 14KB 92ms (10.9fps)

I (70950) camera_http_server: MJPG: 13KB 78ms (12.8fps)

I (71030) camera_http_server: MJPG: 12KB 74ms (13.5fps)

I (71130) camera_http_server: MJPG: 12KB 102ms (9.8fps)

I (71350) camera_http_server: MJPG: 12KB 217ms (4.6fps)

I (195940) camera_http_server: MJPG: 7KB 89ms (11.2fps)

W (195990) httpd_txrx: httpd_sock_err: error in send : 104

W (195990) httpd_uri: httpd_uri: uri handler execution failed



Done

root:/workspace/ip_camera# </details>

## How to Test

Type "http://<IP_of_ESP>/jpegstream" to your browser

```
http://172.20.10.14/jpegstream
```

And then see the streamed result

<img src="./docs/images/stream_result.jpeg" width="300" height="300" />



or execute the tools/http_client.py with sdp ip arg.

```
python3 tools/http_client.py <ESP_IP>
```

### Supported Soc

- ESP32
- ESP32-S2
- ESP32-S3

### Supported Sensor

| model   | max resolution | color type | output format                                                | Len Size |
| ------- | -------------- | ---------- | ------------------------------------------------------------ | -------- |
| OV2640  | 1600 x 1200    | color      | YUV(422/420)/YCbCr422<br>RGB565/555<br>8-bit compressed data<br>8/10-bit Raw RGB data | 1/4"     |
| OV3660  | 2048 x 1536    | color      | raw RGB data<br/>RGB565/555/444<br/>CCIR656<br/>YCbCr422<br/>compression | 1/5"     |
| OV5640  | 2592 x 1944    | color      | RAW RGB<br/>RGB565/555/444<br/>CCIR656<br/>YUV422/420<br/>YCbCr422<br/>compression | 1/4"     |
| OV7670  | 640 x 480      | color      | Raw Bayer RGB<br/>Processed Bayer RGB<br>YUV/YCbCr422<br>GRB422<br>RGB565/555 | 1/6"     |
| OV7725  | 640 x 480      | color      | Raw RGB<br/>GRB 422<br/>RGB565/555/444<br/>YCbCr 422         | 1/4"     |
| NT99141 | 1280 x 720     | color      | YCbCr 422<br/>RGB565/555/444<br/>Raw<br/>CCIR656<br/>JPEG compression | 1/4"     |
| GC032A  | 640 x 480      | color      | YUV/YCbCr422<br/>RAW Bayer<br/>RGB565                        | 1/10"    |
| GC0308  | 640 x 480      | color      | YUV/YCbCr422<br/>RAW Bayer<br/>RGB565<br/>Grayscale                         | 1/6.5"   |
| GC2145  | 1600 x 1200    | color      | YUV/YCbCr422<br/>RAW Bayer<br/>RGB565                        | 1/5"     |
| BF3005  | 640 x 480      | color      | YUV/YCbCr422<br/>RAW Bayer<br/>RGB565                        | 1/4"     |
| BF20A6  | 640 x 480      | color      | YUV/YCbCr422<br/>RAW Bayer<br/>Only Y                        | 1/10"    |
| SC101IOT| 1280 x 720     | color      | YUV/YCbCr422<br/>Raw RGB                                     | 1/4.2"   |
| SC030IOT| 640 x 480      | color      | YUV/YCbCr422<br/>RAW Bayer                                   | 1/6.5"   |
| SC031GS | 640 x 480      | monochrome | RAW MONO<br/>Grayscale                                       | 1/6"     |

## Important to Remember

- Except when using CIF or lower resolution with JPEG, the driver requires PSRAM to be installed and activated.
- Using YUV or RGB puts a lot of strain on the chip because writing to PSRAM is not particularly fast. The result is that image data might be missing. This is particularly true if WiFi is enabled. If you need RGB data, it is recommended that JPEG is captured and then turned into RGB using `fmt2rgb888` or `fmt2bmp`/`frame2bmp`.
- When 1 frame buffer is used, the driver will wait for the current frame to finish (VSYNC) and start I2S DMA. After the frame is acquired, I2S will be stopped and the frame buffer returned to the application. This approach gives more control over the system, but results in longer time to get the frame.
- When 2 or more frame bufers are used, I2S is running in continuous mode and each frame is pushed to a queue that the application can access. This approach puts more strain on the CPU/Memory, but allows for double the frame rate. Please use only with JPEG.

## Installation Instructions


### Using with ESP-IDF

- Add a dependency on `espressif/esp32-camera` component:
  ```bash
  idf.py add-dependency "espressif/esp32-camera"
  ```
  (or add it manually in idf_component.yml of your project)
- Enable PSRAM in `menuconfig` (also set Flash and PSRAM frequiencies to 80MHz)
- Include `esp_camera.h` in your code

These instructions also work for PlatformIO, if you are using `framework=espidf`.


## Examples

This component comes with a basic example illustrating how to get frames from the camera. You can try out the example using the following command:

```
idf.py create-project-from-example "espressif/esp32-camera:camera_example"
```

This command will download the example into `camera_example` directory. It comes already pre-configured with the correct settings in menuconfig.

### Initialization

```c
#include "esp_camera.h"

//WROVER-KIT PIN Map
#define CAM_PIN_PWDN    -1 //power down is not used
#define CAM_PIN_RESET   -1 //software reset will be performed
#define CAM_PIN_XCLK    21
#define CAM_PIN_SIOD    26
#define CAM_PIN_SIOC    27

#define CAM_PIN_D7      35
#define CAM_PIN_D6      34
#define CAM_PIN_D5      39
#define CAM_PIN_D4      36
#define CAM_PIN_D3      19
#define CAM_PIN_D2      18
#define CAM_PIN_D1       5
#define CAM_PIN_D0       4
#define CAM_PIN_VSYNC   25
#define CAM_PIN_HREF    23
#define CAM_PIN_PCLK    22

static camera_config_t camera_config = {
    .pin_pwdn  = CAM_PIN_PWDN,
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

    .xclk_freq_hz = 20000000,//EXPERIMENTAL: Set to 16MHz on ESP32-S2 or ESP32-S3 to enable EDMA mode
    .ledc_timer = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0,

    .pixel_format = PIXFORMAT_JPEG,//YUV422,GRAYSCALE,RGB565,JPEG
    .frame_size = FRAMESIZE_UXGA,//QQVGA-UXGA, For ESP32, do not use sizes above QVGA when not JPEG. The performance of the ESP32-S series has improved a lot, but JPEG mode always gives better frame rates.

    .jpeg_quality = 12, //0-63, for OV series camera sensors, lower number means higher quality
    .fb_count = 1, //When jpeg mode is used, if fb_count more than one, the driver will work in continuous mode.
    .grab_mode = CAMERA_GRAB_WHEN_EMPTY//CAMERA_GRAB_LATEST. Sets when buffers should be filled
};

esp_err_t camera_init(){
    //power up the camera if PWDN pin is defined
    if(CAM_PIN_PWDN != -1){
        pinMode(CAM_PIN_PWDN, OUTPUT);
        digitalWrite(CAM_PIN_PWDN, LOW);
    }

    //initialize the camera
    esp_err_t err = esp_camera_init(&camera_config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Camera Init Failed");
        return err;
    }

    return ESP_OK;
}

esp_err_t camera_capture(){
    //acquire a frame
    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
        ESP_LOGE(TAG, "Camera Capture Failed");
        return ESP_FAIL;
    }
    //replace this with your own function
    process_image(fb->width, fb->height, fb->format, fb->buf, fb->len);
  
    //return the frame buffer back to the driver for reuse
    esp_camera_fb_return(fb);
    return ESP_OK;
}
```

### JPEG HTTP Capture

```c
#include "esp_camera.h"
#include "esp_http_server.h"
#include "esp_timer.h"

typedef struct {
        httpd_req_t *req;
        size_t len;
} jpg_chunking_t;

static size_t jpg_encode_stream(void * arg, size_t index, const void* data, size_t len){
    jpg_chunking_t *j = (jpg_chunking_t *)arg;
    if(!index){
        j->len = 0;
    }
    if(httpd_resp_send_chunk(j->req, (const char *)data, len) != ESP_OK){
        return 0;
    }
    j->len += len;
    return len;
}

esp_err_t jpg_httpd_handler(httpd_req_t *req){
    camera_fb_t * fb = NULL;
    esp_err_t res = ESP_OK;
    size_t fb_len = 0;
    int64_t fr_start = esp_timer_get_time();

    fb = esp_camera_fb_get();
    if (!fb) {
        ESP_LOGE(TAG, "Camera capture failed");
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }
    res = httpd_resp_set_type(req, "image/jpeg");
    if(res == ESP_OK){
        res = httpd_resp_set_hdr(req, "Content-Disposition", "inline; filename=capture.jpg");
    }

    if(res == ESP_OK){
        if(fb->format == PIXFORMAT_JPEG){
            fb_len = fb->len;
            res = httpd_resp_send(req, (const char *)fb->buf, fb->len);
        } else {
            jpg_chunking_t jchunk = {req, 0};
            res = frame2jpg_cb(fb, 80, jpg_encode_stream, &jchunk)?ESP_OK:ESP_FAIL;
            httpd_resp_send_chunk(req, NULL, 0);
            fb_len = jchunk.len;
        }
    }
    esp_camera_fb_return(fb);
    int64_t fr_end = esp_timer_get_time();
    ESP_LOGI(TAG, "JPG: %uKB %ums", (uint32_t)(fb_len/1024), (uint32_t)((fr_end - fr_start)/1000));
    return res;
}
```

### JPEG HTTP Stream

```c
#include "esp_camera.h"
#include "esp_http_server.h"
#include "esp_timer.h"

#define PART_BOUNDARY "123456789000000000000987654321"
static const char* _STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char* _STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char* _STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";

esp_err_t jpg_stream_httpd_handler(httpd_req_t *req){
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
        ESP_LOGI(TAG, "MJPG: %uKB %ums (%.1ffps)",
            (uint32_t)(_jpg_buf_len/1024),
            (uint32_t)frame_time, 1000.0 / (uint32_t)frame_time);
    }

    last_frame = 0;
    return res;
}
```

### BMP HTTP Capture

```c
#include "esp_camera.h"
#include "esp_http_server.h"
#include "esp_timer.h"

esp_err_t bmp_httpd_handler(httpd_req_t *req){
    camera_fb_t * fb = NULL;
    esp_err_t res = ESP_OK;
    int64_t fr_start = esp_timer_get_time();

    fb = esp_camera_fb_get();
    if (!fb) {
        ESP_LOGE(TAG, "Camera capture failed");
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    uint8_t * buf = NULL;
    size_t buf_len = 0;
    bool converted = frame2bmp(fb, &buf, &buf_len);
    esp_camera_fb_return(fb);
    if(!converted){
        ESP_LOGE(TAG, "BMP conversion failed");
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    res = httpd_resp_set_type(req, "image/x-windows-bmp")
       || httpd_resp_set_hdr(req, "Content-Disposition", "inline; filename=capture.bmp")
       || httpd_resp_send(req, (const char *)buf, buf_len);
    free(buf);
    int64_t fr_end = esp_timer_get_time();
    ESP_LOGI(TAG, "BMP: %uKB %ums", (uint32_t)(buf_len/1024), (uint32_t)((fr_end - fr_start)/1000));
    return res;
}
```

# Important Links

[ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html)

[CESP Standard Toolchain Setup for Linux ](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/linux-macos-setup.html)

[esp-idf github](https://github.com/espressif/esp-idf)

[esp32-camera github](https://github.com/espressif/esp32-camera)

[How to Program / Upload Code to ESP32-CAM AI-Thinker (Arduino IDE)](https://randomnerdtutorials.com/program-upload-code-esp32-cam/)

[ESP32 Cam Project Development Example on Ubuntu](https://reversepcb.com/esp32-cam-project-development-example-on-ubuntu/)

[ESP32-CAM-Linux-Motion](https://github.com/xenpac/ESP32-CAM-Linux-Motion)

[AI_Thinker-ESP32-cam](https://github.com/prusa3d/Prusa-Firmware-ESP32-Cam/blob/master/doc/AI_Thinker-ESP32-cam/README.md)

[camera datasheet](./docs/ov2640_ds_1.8_.pdf)

[schematic](./docs/esp32_cam_sch.pdf)
