import requests
import argparse

parser = argparse.ArgumentParser(
    prog='config_set_for_ip_camera',
    description='config_set_for_ip_camera',
    epilog='config_set_for_ip_camera')
parser.add_argument('-i', '--ip',
                    action='store',
                    help='default is "192.168.4.1"')
parser.add_argument('-1', '--stassid',
                    action='store',
                    help='ssid for sta')
parser.add_argument('-2', '--stapwd',
                    action='store',
                    help='pwd for sta')
parser.add_argument('-3', '--apssid',
                    action='store',
                    help='ssid for ap')
parser.add_argument('-4', '--appwd',
                    action='store',
                    help='pwd for ap')
parser.add_argument('-5', '--resol',
                    action='store',
                    help='    FRAMESIZE_96X96,    // 96x96 \
                    FRAMESIZE_QQVGA,    // 160x120 \
                    FRAMESIZE_128X128,    // 128x128 \
                    FRAMESIZE_QCIF,     // 176x144 \
                    FRAMESIZE_HQVGA,    // 240x176 \
                    FRAMESIZE_240X240,  // 240x240 \
                    FRAMESIZE_QVGA,     // 320x240 \
                    FRAMESIZE_320X320,  // 320x320 \
                    FRAMESIZE_CIF,      // 400x296 \
                    FRAMESIZE_HVGA,     // 480x320 \
                    FRAMESIZE_VGA,      // 640x480 \
                    FRAMESIZE_SVGA,     // 800x600 \
                    FRAMESIZE_XGA,      // 1024x768 \
                    FRAMESIZE_HD,       // 1280x720 \
                    FRAMESIZE_SXGA,     // 1280x1024 \
                    FRAMESIZE_UXGA,     // 1600x1200')
parser.add_argument('-6', '--quality',
                    action='store',
                    help='0-63, lower numbers\' qualities are better')
args = parser.parse_args()

# ESP32 IP address
IP = "192.168.4.1"
if args.ip is not None:
    IP = args.ip
ESP32_IP = 'http://'+ IP +'/setconfig'

#define STA_SSID_STR    "sta_ssid"
#define STA_PWD_STR     "sta_pwd"
#define AP_SSID_STR     "ap_ssid"
#define AP_PWD_STR      "ap_pwd"
#define CAM_RESOL       "cam_resol"
#define CAM_QUAL        "cam_qual"

STA_SSID_STR = "NONE"
if args.stassid is not None:
    STA_SSID_STR = args.stassid

STA_PWD_STR = "NONE"
if args.stapwd is not None:
    STA_PWD_STR = args.stapwd

AP_SSID_STR = "NONE"
if args.apssid is not None:
    AP_SSID_STR = args.apssid

AP_PWD_STR = "NONE"
if args.appwd is not None:
    AP_PWD_STR = args.appwd

CAM_RESOL = "NONE"
if args.resol is not None:
    CAM_RESOL = args.resol

CAM_QUAL = "NONE"
if args.quality is not None:
    CAM_QUAL = args.quality

r = requests.post(ESP32_IP, data={'sta_ssid': STA_SSID_STR, 'sta_pwd': STA_PWD_STR, 'ap_ssid': AP_SSID_STR, 'ap_pwd': AP_PWD_STR, 'cam_resol': CAM_RESOL, 'cam_qual': CAM_QUAL})
print(r.status_code, r.reason)
print(r.text)

