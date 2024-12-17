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
root@spire:/workspace/ip_camera# idf.py -p /dev/ttyUSB0 flash monitor
Executing action: flash
Running ninja in directory /workspace/ip_camera/build
Executing "ninja flash"...
[1/5] cd /workspace/ip_camera/build/esp-idf/esptool_py && /root/.espressif/pyth...rtition_table/partition-table.bin /workspace/ip_camera/build/camera_example.bin
camera_example.bin binary size 0x4d320 bytes. Smallest app partition is 0x100000 bytes. 0xb2ce0 bytes (70%) free.
[1/1] cd /workspace/ip_camera/build/bootloader/esp-idf/esptool_py && /root/.esp... 0x10000 bootloader 0x1000 /workspace/ip_camera/build/bootloader/bootloader.bin
Bootloader binary size 0x6f50 bytes. 0x80b0 bytes (54%) free.
[2/3] cd /esp-idf/components/esptool_py && /usr/bin/cmake -D IDF_PATH=/esp-idf ...rkspace/ip_camera/build -P /esp-idf/components/esptool_py/run_serial_tool.cmake
esptool.py --chip esp32 -p /dev/ttyUSB0 -b 460800 --before=default_reset --after=hard_reset write_flash --flash_mode dio --flash_freq 80m --flash_size 4MB 0x1000 bootloader/bootloader.bin 0x20000 camera_example.bin 0x10000 partition_table/partition-table.bin
esptool.py v4.8.1
Serial port /dev/ttyUSB0
Connecting....
Chip is ESP32-D0WDQ6 (revision v1.1)
Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
Crystal is 40MHz
MAC: fc:b4:67:01:c1:80
Uploading stub...
Running stub...
Stub running...
Changing baud rate to 460800
Changed.
Configuring flash size...
Flash will be erased from 0x00001000 to 0x00007fff...
Flash will be erased from 0x00020000 to 0x0006dfff...
Flash will be erased from 0x00010000 to 0x00010fff...
SHA digest in image updated
Compressed 28496 bytes to 17337...
Writing at 0x00007a5d... (100 %)
Wrote 28496 bytes (17337 compressed) at 0x00001000 in 0.5 seconds (effective 431.6 kbit/s)...
Hash of data verified.
Compressed 316192 bytes to 161581...
Writing at 0x00067909... (100 %)
Wrote 316192 bytes (161581 compressed) at 0x00020000 in 3.8 seconds (effective 667.6 kbit/s)...
Hash of data verified.
Compressed 3072 bytes to 104...
Writing at 0x00010000... (100 %)
Wrote 3072 bytes (104 compressed) at 0x00010000 in 0.0 seconds (effective 1254.0 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...
Executing action: monitor
Running idf_monitor in directory /workspace/ip_camera
Executing "/root/.espressif/python_env/idf5.3_py3.10_env/bin/python /esp-idf/tools/idf_monitor.py -p /dev/ttyUSB0 -b 115200 --toolchain-prefix xtensa-esp32-elf- --target esp32 --revision 0 /workspace/ip_camera/build/camera_example.elf -m '/root/.espressif/python_env/idf5.3_py3.10_env/bin/python' '/esp-idf/tools/idf.py' '-p' '/dev/ttyUSB0'"...
--- esp-idf-monitor 1.5.0 on /dev/ttyUSB0 115200
--- Quit: Ctrl+] | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H
ets Jun  8 2016 00:22:57

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:1
load:0x3fff0030,len:7524
load:0x40078000,len:16552
load:0x40080400,len:4
--- 0x40080400: _init at ??:?

load:0x40080404,len:4312
entry 0x4008065c
I (28) boot: ESP-IDF v5.3.2 2nd stage bootloader
I (28) boot: compile time Dec 17 2024 12:57:20
I (29) boot: Multicore bootloader
I (33) boot: chip revision: v1.1
I (36) qio_mode: Enabling default flash chip QIO
I (42) boot.esp32: SPI Speed      : 80MHz
I (46) boot.esp32: SPI Mode       : QIO
I (51) boot.esp32: SPI Flash Size : 4MB
I (55) boot: Enabling RNG early entropy source...
I (61) boot: Partition Table:
I (64) boot: ## Label            Usage          Type ST Offset   Length
I (72) boot:  0 nvs              WiFi data        01 02 00011000 00006000
I (79) boot:  1 phy_init         RF data          01 01 00017000 00001000
I (87) boot:  2 factory          factory app      00 00 00020000 00100000
I (94) boot: End of partition table
I (98) esp_image: segment 0: paddr=00020020 vaddr=3f400020 size=121dch ( 74204) map
I (126) esp_image: segment 1: paddr=00032204 vaddr=3ffb0000 size=034e0h ( 13536) load
I (130) esp_image: segment 2: paddr=000356ec vaddr=40080000 size=0a92ch ( 43308) load
I (145) esp_image: segment 3: paddr=00040020 vaddr=400d0020 size=25944h (153924) map
I (185) esp_image: segment 4: paddr=0006596c vaddr=4008a92c size=07984h ( 31108) load
I (204) boot: Loaded app from partition at offset 0x20000
I (204) boot: Disabling RNG early entropy source...
I (216) quad_psram: This chip is ESP32-D0WD
I (216) esp_psram: Found 8MB PSRAM device
I (216) esp_psram: Speed: 80MHz
I (220) esp_psram: PSRAM initialized, cache is in low/high (2-core) mode.
W (227) esp_psram: Virtual address not enough for PSRAM, map as much as we can. 4MB is mapped
I (236) cpu_start: Multicore app
D (240) cpu_start: Pro cpu up
D (243) cpu_start: Starting app cpu, entry point is 0x40081404
--- 0x40081404: call_start_cpu1 at /esp-idf/components/esp_system/port/cpu_start.c:190

D (0) cpu_start: App cpu up
I (760) esp_psram: SPI SRAM memory test OK
D (768) clk: RTC_SLOW_CLK calibration value: 3431501
D (773) cpu_start: calling init function: 0x400d2058 on core: 0
--- 0x400d2058: __esp_system_init_fn_init_efuse_check at /esp-idf/components/efuse/src/esp_efuse_startup.c:31

D (773) cpu_start: calling init function: 0x400d22d8 on core: 0
--- 0x400d22d8: __esp_system_init_fn_init_show_cpu_freq at /esp-idf/components/esp_system/startup_funcs.c:58

I (776) cpu_start: Pro cpu start user code
I (780) cpu_start: cpu freq: 240000000 Hz
D (785) cpu_start: calling init function: 0x400d1f98 on core: 0
--- 0x400d1f98: __esp_system_init_fn_init_show_app_info at /esp-idf/components/esp_app_format/esp_app_desc.c:106

I (791) app_init: Application information:
I (796) app_init: Project name:     camera_example
I (801) app_init: App version:      944b69c-dirty
I (807) app_init: Compile time:     Dec 17 2024 12:57:15
I (813) app_init: ELF file SHA256:  856aff165...
I (818) app_init: ESP-IDF:          v5.3.2
D (823) cpu_start: calling init function: 0x400d206c on core: 0
--- 0x400d206c: __esp_system_init_fn_init_efuse_show_app_info at /esp-idf/components/efuse/src/esp_efuse_startup.c:41

I (829) efuse_init: Min chip rev:     v0.0
I (833) efuse_init: Max chip rev:     v3.99 
I (838) efuse_init: Chip rev:         v1.1
D (843) cpu_start: calling init function: 0x400d3a7c on core: 0
--- 0x400d3a7c: __esp_system_init_fn_init_heap at /esp-idf/components/heap/heap_caps_init.c:25

D (849) memory_layout: Checking 10 reserved memory ranges:
D (855) memory_layout: Reserved memory range 0x3f800000 - 0x3fc00000
D (861) memory_layout: Reserved memory range 0x3ff82000 - 0x3ff82000
D (868) memory_layout: Reserved memory range 0x3ffae000 - 0x3ffae6e0
D (874) memory_layout: Reserved memory range 0x3ffb0000 - 0x3ffb3e40
D (880) memory_layout: Reserved memory range 0x3ffe0000 - 0x3ffe0440
D (887) memory_layout: Reserved memory range 0x3ffe3f20 - 0x3ffe4350
D (893) memory_layout: Reserved memory range 0x40070000 - 0x40078000
D (900) memory_layout: Reserved memory range 0x40078000 - 0x40080000
--- 0x40080000: _WindowOverflow4 at /esp-idf/components/xtensa/xtensa_vectors.S:2027

D (906) memory_layout: Reserved memory range 0x40080000 - 0x400922b0
--- 0x40080000: _WindowOverflow4 at /esp-idf/components/xtensa/xtensa_vectors.S:2027

D (913) memory_layout: Reserved memory range 0x50001fe8 - 0x50002000
D (919) memory_layout: Building list of available memory regions:
D (925) memory_layout: Available memory region 0x3ffae6e0 - 0x3ffb0000
D (932) memory_layout: Available memory region 0x3ffb3e40 - 0x3ffb8000
D (938) memory_layout: Available memory region 0x3ffb8000 - 0x3ffc0000
D (945) memory_layout: Available memory region 0x3ffc0000 - 0x3ffc2000
D (952) memory_layout: Available memory region 0x3ffc2000 - 0x3ffc4000
D (958) memory_layout: Available memory region 0x3ffc4000 - 0x3ffc6000
D (965) memory_layout: Available memory region 0x3ffc6000 - 0x3ffc8000
D (971) memory_layout: Available memory region 0x3ffc8000 - 0x3ffca000
D (978) memory_layout: Available memory region 0x3ffca000 - 0x3ffcc000
D (985) memory_layout: Available memory region 0x3ffcc000 - 0x3ffce000
D (991) memory_layout: Available memory region 0x3ffce000 - 0x3ffd0000
D (998) memory_layout: Available memory region 0x3ffd0000 - 0x3ffd2000
D (1004) memory_layout: Available memory region 0x3ffd2000 - 0x3ffd4000
D (1011) memory_layout: Available memory region 0x3ffd4000 - 0x3ffd6000
D (1018) memory_layout: Available memory region 0x3ffd6000 - 0x3ffd8000
D (1024) memory_layout: Available memory region 0x3ffd8000 - 0x3ffda000
D (1031) memory_layout: Available memory region 0x3ffda000 - 0x3ffdc000
D (1038) memory_layout: Available memory region 0x3ffdc000 - 0x3ffde000
D (1044) memory_layout: Available memory region 0x3ffde000 - 0x3ffe0000
D (1051) memory_layout: Available memory region 0x3ffe0440 - 0x3ffe3f20
D (1058) memory_layout: Available memory region 0x3ffe4350 - 0x3ffe8000
D (1064) memory_layout: Available memory region 0x3ffe8000 - 0x3fff0000
D (1071) memory_layout: Available memory region 0x3fff0000 - 0x3fff8000
D (1078) memory_layout: Available memory region 0x3fff8000 - 0x3fffc000
D (1085) memory_layout: Available memory region 0x3fffc000 - 0x40000000
--- 0x40000000: _WindowOverflow4 in ROM

D (1091) memory_layout: Available memory region 0x400922b0 - 0x40094000
D (1098) memory_layout: Available memory region 0x40094000 - 0x40096000
D (1105) memory_layout: Available memory region 0x40096000 - 0x40098000
D (1111) memory_layout: Available memory region 0x40098000 - 0x4009a000
D (1118) memory_layout: Available memory region 0x4009a000 - 0x4009c000
D (1125) memory_layout: Available memory region 0x4009c000 - 0x4009e000
D (1131) memory_layout: Available memory region 0x4009e000 - 0x400a0000
I (1138) heap_init: Initializing. RAM available for dynamic allocation:
D (1145) heap_init: New heap initialised at 0x3ffae6e0
I (1151) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
D (1157) heap_init: New heap initialised at 0x3ffb3e40
I (1162) heap_init: At 3FFB3E40 len 0002C1C0 (176 KiB): DRAM
I (1168) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (1175) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
D (1181) heap_init: New heap initialised at 0x400922b0
I (1186) heap_init: At 400922B0 len 0000DD50 (55 KiB): IRAM
D (1193) cpu_start: calling init function: 0x400d1da0 on core: 0
--- 0x400d1da0: __esp_system_init_fn_esp_timer_init_nonos at /esp-idf/components/esp_timer/src/esp_timer_init.c:28

D (1199) cpu_start: calling init function: 0x400d4cf8 on core: 0
--- 0x400d4cf8: __esp_system_init_fn_init_newlib at /esp-idf/components/newlib/newlib_init.c:162

D (1205) cpu_start: calling init function: 0x400d5590 on core: 0
--- 0x400d5590: __esp_system_init_fn_init_psram at /esp-idf/components/esp_psram/esp_psram.c:94

I (1211) esp_psram: Adding pool of 4096K of PSRAM memory to heap allocator
D (1218) cpu_start: calling init function: 0x400d231c on core: 0
--- 0x400d231c: __esp_system_init_fn_init_brownout at /esp-idf/components/esp_system/startup_funcs.c:67

D (1225) intr_alloc: Connected src 46 to int 1 (cpu 0)
D (1230) cpu_start: calling init function: 0x400d2328 on core: 0
--- 0x400d2328: __esp_system_init_fn_init_newlib_time at /esp-idf/components/esp_system/startup_funcs.c:81

D (1236) cpu_start: calling init function: 0x400d4d64 on core: 0
--- 0x400d4d64: __esp_system_init_fn_init_newlib_stdio at /esp-idf/components/newlib/newlib_init.c:207

D (1242) cpu_start: calling init function: 0x400d5134 on core: 0
--- 0x400d5134: __esp_system_init_fn_init_pthread at /esp-idf/components/pthread/pthread.c:76

D (1248) cpu_start: calling init function: 0x400d2334 on core: 0
--- 0x400d2334: __esp_system_init_fn_init_flash at /esp-idf/components/esp_system/startup_funcs.c:88

D (1254) spi_flash: trying chip: issi
D (1258) spi_flash: trying chip: gd
D (1261) spi_flash: trying chip: mxic
D (1265) spi_flash: trying chip: winbond
D (1269) spi_flash: trying chip: generic
I (1273) spi_flash: detected chip: generic
I (1278) spi_flash: flash io: qio
D (1282) chip_generic: set_io_mode: status before 0x200
D (1287) cpu_start: calling init function: 0x400d20f8 on core: 0
--- 0x400d20f8: __esp_system_init_fn_init_efuse at /esp-idf/components/efuse/src/esp_efuse_startup.c:137

D (1293) cpu_start: calling init function: 0x400e9ec4
--- 0x400e9ec4: _GLOBAL__sub_I__ZN17__eh_globals_init7_S_initE at /builds/idf/crosstool-NG/.build/xtensa-esp-elf/src/gcc/libstdc++-v3/libsupc++/eh_globals.cc:162

D (1298) cpu_start: calling init function: 0x400e9114
--- 0x400e9114: check_i2c_driver_conflict at /esp-idf/components/driver/i2c/i2c.c:1713

W (1303) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
D (1314) cpu_start: calling init function: 0x40089680
--- 0x40089680: enable_timer_group0_for_calibration at /esp-idf/components/esp_hw_support/port/esp32/rtc_time.c:197

D (1319) cpu_start: calling init function: 0x400d3300
--- 0x400d3300: esp_ipc_init at /esp-idf/components/esp_system/esp_ipc.c:113

D (1324) cpu_start: calling init function: 0x400d2940
--- 0x400d2940: esp_reset_reason_init at /esp-idf/components/esp_system/port/soc/esp32/reset_reason.c:60

D (1329) cpu_start: calling init function: 0x400d2358 on core: 0
--- 0x400d2358: __esp_system_init_fn_init_disable_rtc_wdt at /esp-idf/components/esp_system/startup_funcs.c:143

D (1335) intr_alloc: Connected src 24 to int 2 (cpu 0)
D (1340) app_start: Starting scheduler on CPU0
I5) intr_maioc: sknnected d on25Pto [nt 1 (cpu 1)
D (1350) app_start: Starting scheduler on CPU1
D (1354) heap_init: New heap initialised at 0x3ffe0440
D (1360) heap_init: New heap initialised at 0x3ffe4350
I (1365) esp_psram: Reserving pool of 32K of internal memory for DMA/internal allocations
D (1374) esp_psram: Allocating block of size 32768 bytes
D (1379) intr_alloc: Connected src 16 to int 3 (cpu 0)
I (1384) main_task: Calling app_main()
I (1389) gpio: GPIO[25]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:2 
D (1398) intr_alloc: Connected src 22 to int 5 (cpu 0)
I (1403) cam_hal: cam init ok
D (1407) camera: Enabling XCLK output
D (1410) ledc: Using clock source 4 (in slow mode), divisor: 0x200
D (1416) ledc: In slow speed mode, global clk set: 4
D (1421) ledc: LEDC_PWM CHANNEL 0|GPIO 00|Duty 0001|Time 0
D (1427) camera: Initializing SCCB
I (1430) sccb: pin_sda 26 pin_scl 27
I (1434) sccb: sccb_i2c_port=1
D (1438) intr_alloc: Connected src 50 to int 8 (cpu 0)
D (1443) camera: Resetting camera by power down line
I (1448) gpio: GPIO[32]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 0| Pulldown: 0| Intr:0 
D (1478) camera: Searching for camera address
I (1488) camera: Detected camera at address=0x30
I (1491) camera: Detected OV2640 camera
D (1491) ov2640: OV2640 Attached
I (1491) camera: Camera PID=0x26 VER=0x42 MIDL=0x7f MIDH=0xa2
D (1496) camera: Doing SW reset of sensor
I (1582) esp32 ll_cam: node_size: 2560, nodes_per_line: 1, lines_per_node: 1, dma_half_buffer_min:  2560, dma_half_buffer: 15360,lines_per_half_buffer:  6, dma_buffer_size: 30720, image_size: 153600
I (1589) cam_hal: buffer_size: 30720, half_buffer_size: 15360, node_buffer_size: 2560, node_cnt: 12, total_cnt: 10
I (1600) cam_hal: Allocating 153600 Byte frame buffer in PSRAM
D (1606) intr_alloc: Connected src 32 to int 9 (cpu 0)
I (1611) cam_hal: cam config ok
D (1615) camera: Setting frame size to 320x240
I (1619) ov2640: Set PLL: clk_2x: 0, clk_div: 3, pclk_auto: 1, pclk_div: 8
I (1699) example:take_picture: Taking picture...
I (1887) example:take_picture: Picture taken! Its size was: 153600 bytes
I (6887) example:take_picture: Taking picture...
I (6887) example:take_picture: Picture taken! Its size was: 153600 bytes
I (11888) example:take_picture: Taking picture...
I (11888) example:take_picture: Picture taken! Its size was: 153600 bytes
I (16889) example:take_picture: Taking picture...
I (16889) example:take_picture: Picture taken! Its size was: 153600 bytes
I (21890) example:take_picture: Taking picture...
I (21890) example:take_picture: Picture taken! Its size was: 153600 bytes
I (26891) example:take_picture: Taking picture...
I (26891) example:take_picture: Picture taken! Its size was: 153600 bytes
I (31892) example:take_picture: Taking picture...
I (31892) example:take_picture: Picture taken! Its size was: 153600 bytes
I (36893) example:take_picture: Taking picture...
I (36893) example:take_picture: Picture taken! Its size was: 153600 bytes
I (41894) example:take_picture: Taking picture...
I (41894) example:take_picture: Picture taken! Its size was: 153600 bytes
I (46895) example:take_picture: Taking picture...
I (46895) example:take_picture: Picture taken! Its size was: 153600 bytes
I (51896) example:take_picture: Taking picture...
I (51896) example:take_picture: Picture taken! Its size was: 153600 bytes
I (56897) example:take_picture: Taking picture...
I (56897) example:take_picture: Picture taken! Its size was: 153600 bytes
I (61898) example:take_picture: Taking picture...
I (61898) example:take_picture: Picture taken! Its size was: 153600 bytes
I (66899) example:take_picture: Taking picture...
I (66899) example:take_picture: Picture taken! Its size was: 153600 bytes
I (71900) example:take_picture: Taking picture...
I (71900) example:take_picture: Picture taken! Its size was: 153600 bytes
I (76901) example:take_picture: Taking picture...
I (76901) example:take_picture: Picture taken! Its size was: 153600 bytes
I (81902) example:take_picture: Taking picture...
I (81902) example:take_picture: Picture taken! Its size was: 153600 bytes
I (86903) example:take_picture: Taking picture...
I (86903) example:take_picture: Picture taken! Its size was: 153600 bytes
I (91904) example:take_picture: Taking picture...
I (91904) example:take_picture: Picture taken! Its size was: 153600 bytes
I (96905) example:take_picture: Taking picture...
I (96905) example:take_picture: Picture taken! Its size was: 153600 bytes
I (101906) example:take_picture: Taking picture...
I (101906) example:take_picture: Picture taken! Its size was: 153600 bytes
I (106907) example:take_picture: Taking picture...
I (106907) example:take_picture: Picture taken! Its size was: 153600 bytes
I (111908) example:take_picture: Taking picture...
I (111908) example:take_picture: Picture taken! Its size was: 153600 bytes
```

## How to Test

TODO


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
