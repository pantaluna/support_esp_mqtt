# 0. Environment
- MCU: Adafruit HUZZAH32 ESP32 development board.
- MCU: Wemos LOLIN32 Lite development board.
- ESP-IDF Github master branch of Feb 12, 2018.

# 1. MENUCONFIG Set WIFI SSID and Password
```
cd ~
git clone --recursive https://github.com/pantaluna/support_esp_mqtt.git
cd  support_esp_mqtt
make menuconfig
```

# 2. The programme crashes consistently during the 2nd iteration of the loop in esp_mqtt_process()=>lwip with message: assertion "netconn state error" failed: file "C:/myiot/esp/esp-idf/components/lwip/api/api_msg.c", line 1055, function: lwip_net
```
cd  ~/support_esp_mqtt
make flash monitor
```

SERIAL UART:

```
I (7799) mjd_wifi: OK: WIFI connected!
I (7799) esp_mqtt: esp_mqtt_start: crreate task
I (7809) esp_mqtt: esp_mqtt_process: begin connection attempt
MQTT: publishing: topic=hello => payload=world (5)

assertion "netconn state error" failed: file "C:/myiot/esp/esp-idf/components/lwip/api/api_msg.c", line 1055, function: lwip_netconn_do_delconn

abort() was called at PC 0x400d2ad7 on core 0

0x400d2ad7: __assert_func at /Users/ivan/e/newlib_xtensa-2.2.0-bin/newlib_xtensa-2.2.0/xtensa-esp32-elf/newlib/libc/stdlib/
../../../.././newlib/libc/stdlib/assert.c:63 (discriminator 8)

Backtrace: 0x4008c478:0x3ffbdb20 0x4008c61b:0x3ffbdb40 0x400d2ad7:0x3ffbdb60 0x4011ea47:0x3ffbdb90 0x4010fda5:0x3ffbdbb0
0x4008c478: invoke_abort at C:/myiot/esp/esp-idf/components/esp32/panic.c:648

0x4008c61b: abort at C:/myiot/esp/esp-idf/components/esp32/panic.c:648

0x400d2ad7: __assert_func at /Users/ivan/e/newlib_xtensa-2.2.0-bin/newlib_xtensa-2.2.0/xtensa-esp32-elf/newlib/libc/stdlib/
../../../.././newlib/libc/stdlib/assert.c:63 (discriminator 8)

0x4011ea47: lwip_netconn_do_delconn at C:/myiot/esp/esp-idf/components/lwip/api/api_msg.c:1881 (discriminator 6)

0x4010fda5: tcpip_thread at C:/myiot/esp/esp-idf/components/lwip/api/tcpip.c:474


CPU halted.
```


# 3. Full Output of CMD make monitor

SERIAL UART:

```
cd  /c/myiot/esp/support_esp_mqtt
make flash monitor
```

```
$ make flash monitor
CC build/main/support_esp_mqtt_main.o
AR build/main/libmain.a
LD build/support_esp_mqtt.elf
esptool.py v2.2.1
Flashing binaries to serial port COM3 (app at offset 0x10000)...
esptool.py v2.2.1
Connecting.....
Chip is ESP32D0WDQ6 (revision 1)
Uploading stub...
Running stub...
Stub running...
Changing baud rate to 2000000
Changed.
Configuring flash size...
Auto-detected Flash size: 4MB
Flash params set to 0x0220
Compressed 19648 bytes to 11613...
Wrote 19648 bytes (11613 compressed) at 0x00001000 in 0.1 seconds (effective 1506.0 kbit/s)...
Hash of data verified.
Compressed 506960 bytes to 313240...
Wrote 506960 bytes (313240 compressed) at 0x00010000 in 5.2 seconds (effective 783.7 kbit/s)...
Hash of data verified.
Compressed 3072 bytes to 103...
Wrote 3072 bytes (103 compressed) at 0x00008000 in 0.0 seconds (effective 1754.2 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting...
MONITOR
--- idf_monitor on COM3 115200 ---
--- Quit: Ctrl+] | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
ets Jun  8 2016 00:22:57

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0018,len:4
load:0x3fff001c,len:5636
load:0x40078000,len:0
load:0x40078000,len:13904
entry 0x40078fd8
I (28) boot: ESP-IDFF v3.1-dev-380-gca3faa61 2nd stage bootloader
I (28) boot: compile time 22:51:23
I (28) boot: Enabling RNG early entropy source...
I (34) boot: SPI Speed      : 40MHz
I (38) boot: SPI Mode       : DIO
I (42) boot: SPI Flash Size : 4MB
I (46) boot: Partition Table:
I (50) boot: ## Label            Usage          Type ST Offset   Length
I (57) boot:  0 nvs              WiFi data        001 02 00009000 00006000
I (64) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (72) boot:  2 factory          factory app      00 00 00010000 00100000
I (79) boot: End of partition table
I (83) esp_image: segment 0: paddr=0x00010020 vaddr=0x3f400020 size=0x1110ec ( 69868) map
I (117) esp_image: segment 1: paddr=0x00021114 vaddr=0x3ffb0000 size=0x03390 ( 13200) load
I (122) esp_image: segment 2: paddr=0x000244ac vaddr=0x40080000 size=0x00400 (  1024) load
0x40080000: _iram_start at C:/myiot/esp/esp-idf/components/freertos/xtensa_vectors.S:1685

I (124) esp_image: segment 3: paddr=0x000248b4 vaddr=0x40080400 size=0x0b75c ( 46940) load
I (152) esp_image: segment 4: paddr=0x00030018 vaddr=0x400d0018 size=0x59228 (365096) map
0x400d0018: _stext at ??:?

I (279) esp_image: segment 5: ppaddr=0x00089248 vaddr=0x4008bb5c size=0x029dc ( 10716) load
0x4008bb5c: assert_valid_block at C:/myiot/esp/esp-idf/components/heap/multi_heap.c:154 (discriminator 1)

I (283) esp__image: segment 6: paddr=0x0008bc2c vaddr=0x400c0000 size=0x00000 (     0) load
I (294) boot: Loaded app from partition at offset 0x10000
I (294) boot: Disabling RNG early entropy source...
I (297) cpu_start: Pro cpu up.
I (301) cpu_start: Starting app cpu, entry point is 0x40080fa4
0x40080fa4: call_start_cpu1 at C:/myiot/esp/esp-idf/components/esp32/cpu_start.c:215

I (0) cpu_start: App cpu up.
I (311) heap_init: Initializing. RAM available for dynamic allocation:
D (318) heap_init: New heap initialised at 0x3ffae6e0
I (323) heap_init: At 3FFAE6EE0 len 00001920 (6 KiB): DRAM
D (330) heap_init: New heap initialised at 0x3ffb90c0
I (334) heap_init: At 3FFB90C0 len 00026F40 (155 KiB): DRAM
I (340) heap_init: At 3FFE0440 len 00003BC0 (14 KiB): D/IRAM
I (347) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
D (3555) heap_init: New heap initialised at 0x4008e538
I (358) heap_init: At 4008E538 len 00011AC8 (70 KiB): IRAM
I (365) cpu_start: Pro  cpu start user code
D (377) clk: RTC_SLOW_CLK calibration value: 3198758
V (50) intr_alloc: esp_intr_alloc_intrstatus (cpu 0): checking args
V (50) intr_alloc: esp_intr_alloc_intrstatus (cpu 0): Args okay. Resulting flags 0xE
D (55) intr_alloc: Connected src 46 to int  2 (cpu 0)
V (61) intr_alloc: esp_intr_alloc_intrstatus (cpu 0): checking args
V (67) intr_alloc: esp_intr_alloc_intrstatus (cpu 0): Args okay. Resulting flags 0xC0E
D (75) intr_alloc: Connected src 57 to int 3 (cpu 0)
V (80) intr_alloc: esp_intr_alloc_intrstatus (cpu 0): checking args
V (86) intr_alloc: esp_intr_alloc_intrstatus (cpu 0): Args okay. Resulting flags 0x40E
D (94) intr_alloc: Conneccted src 24 to int 9 (cpu 0)
I (100) cpu_start: Starting scheduler on PRO CPU.
V (0) intr_alloc: esp_intr_alloc_intrstatus (cpu 1): checking args
V (0) intr_alloc: esp_intr_alloc_intrstatus (cpu 1): Args okay. Resulting flags 0x40E
D (10) intr_alloc: Coonnected src 25 to int 2 (cpu 1)
I (10) cpu_start: Starting scheduler on APP CPU.
D (149) heap_init: New heap initialised at 0x3ffe0440
D (149) heap_init: New heap initialised at 0x3ffe4350
V (159) intr_alloc: esp_intr_alloc_intrstatus (cpu 0): checking args
V (159) intr_alloc: esp_intr_alloc_intrstatus (cpu 0): Args okay. Resulting flags 0xE
D (1559) intr_alloc: Connected src 16 to int 12 (cpu 0)
I (179) myapp: app_main() BEGIN
I (179) myapp: @doc exec nvs_flash_init() - mandatory for Wifi to work later on
D (189) nvs: nvs_flash_init_custom partition=nvs start=9 count=6
I (229) myapp: @doc Wait 3 seconds affter power-on (let peripherals become active, e.g. meteo sensors!
I (3229) myapp: ***SECTION: WIFI***
I (3229) myapp: WIFI_SSID:     AREA51
I (3229) myapp: WIFI_PASSWORD: jupilerjupiler
D (3229) nvs: nvs_open_from_partition misc 1
D (3229) nvs: nvs_get_str_or_blob log
I (3239) wifi: wifi firmware version: ebd3e5d
I (3239)) wifi: config NVS flash: enabled
I (3239) wifi: config nano formating: disabled
I (3249) system_api: Base MAC address is not set, read default base MAC address from BLK0 of EFUSE
I (3259) system_api: Base MAC address is not set, read default base MAC address from BLK0 of EFUSE
D (3269) nvs: nvs_open_from_partition nvs.net80211 1
D (3269) nvs:  nvs_get opmode 1
D (3279) nvs: nvs_get_str_or_blob sta.ssid
D (3279) nvs: nvs_get_str_or_blob sta.mac
D (3279) nvs: nvs_get sta.authmode 1
D (3289) nvs: nvs_get_str_or_blob sta.pswd
D (3289) nvs: nvs_get_str_or_blob sta.pmk
D (3299) nvs: nvs_geet sta.chan 1
D (3299) nvs: nvs_get auto.conn 1
D (3299) nvs: nvs_get bssid.set 1
D (3309) nvs: nvs_get_str_or_blob sta.bssid
D (3309) nvs: nvs_get sta.phym 1
D (3309) nvs: nvs_get sta.phybw 1
D (3319) nvs: nvs_get_str_or_blob sta.apsw
D (3319) nvs: nvs_get_str_or_blob sta.apinfo
D (3329) nvs: nvs_get sta.scan_method 1
D (3329) nvs: nvs_get sta.sort_method 1
D (3329) nvs: nvs_get sta.minrssi 1
D (3339) nvs: nvs_get sta.minauth 1
D (3339) nvs: nvs_get_str_or_blob ap.ssid
D (3339) nvs: nvs_get_str_or_blob ap.mac
D (3349) nvs: nvs_get_str_or_blob ap.ppasswd
D (3349) nvs: nvs_get_str_or_blob ap.pmk
D (3359) nvs: nvs_get ap.chan 1
D (3359) nvs: nvs_get ap.authmode 1
D (3359) nvs: nvs_get ap.hidden 1
D (3369) nvs: nvs_get ap.max.conn 1
D (3369) nvs: nvs_get bcn.intervval 2
D (3369) nvs: nvs_get ap.phym 1
D (3379) nvs: nvs_get ap.phybw 1
D (3379) nvs: nvs_get ap.sndchan 1
D (3379) nvs: nvs_set_blob sta.mac 6
D (3389) nvs: nvs_set_blob ap.mac 6
I (3389) wifi: Init dynamic tx buffer num: 32
I (3389) wifi: Init data frame dynamic rx buffer num: 32
I (3399) wifi: Init managementt frame dynamic rx buffer num: 32
I (3409) wifi: wifi driver task: 3ffc08c0, prio:23, stack:4096
I (3409) wifi: Init static rx buffer num: 10
I (3409) wifi: Init dynamic rx buffer num: 32
I (3419) wifi: wifi power manager task: 0x3ffc55ffc prio: 21 stack: 2560
I (3429) mjd_wifi: OK: WIFI initialized!
I (3429) myapp: ***SECTION: MQTT***
I (3429) myapp: MQTT + WIFI: start stop: 10 times (@important it always asserts in the 2nd iteration of the LOOP
I (3439) myapp:

MQTT: LOOP#1 of 10
I (3449) mjd_wifi: Connecting to the WIFI network...
D ((3449) RTC_MODULE: Wi-Fi takes adc2 lock.
D (3459) phy_init: loading PHY init data from application binary
D (3459) nvs: nvs_open_from_partition phy 0
D (3469) nvs: nvs_get cal_version 4
V (3469) phy_init: phy_get_rf_cal_version: 383

D (34779) nvs: nvs_get_str_or_blob cal_mac
D (3479) nvs: nvs_get_str_or_blob cal_data
D (3489) nvs: nvs_close 3
V (3489) phy_init: register_chipv7_phy, init_data=0x3f4108a0, cal_data=0x3ffc5c60, mode=0
I (3549) phy: phy_version: 383.0, 79a622c, Jan 30 2018, 15:38:06, 0, 0
I (3549) wifi: mode : sta (30:ae:a4:30:95:ac)
D (35449) event: SYSTEM_EVENT_STA_START
V (3549) event: enter default callback
V (3559) tcpip_adapter: check: local, if=0 fn=0x400e318c
0x400e318c: tcpip_adapter_start_api at C:/myiot/esp/esp-idf/components/tcpip_adapter/tcpip_adapter_lwip.c:1065


V (3559) tcpip_adapter: call api in lwip: ret=0x0, ggive sem
V (3569) tcpip_adapter: check: remote, if=0 fn=0x400e318c
0x400e318c: tcpip_adapter_start_api at C:/myiot/esp/esp-idf/components/tcpip_adapter/tcpip_adapter_lwip.c:1065


V (3579) event: exit default callback
I (4059) wifi: n:4 1, o:1 0, ap:255 255, sta:4 1, prof:1
I (5049) wifi: state: init -> auth (b0)
I (50499) wifi: state: auth -> assoc (0)
I (5059) wifi: state: assoc -> run (10)
I (5349) wifi: connected with AREA51, channel 4
D (53449) event: SYSTEM_EVENT_STA_CONNECTED, ssid:AREA51, ssid_len:6, bssid:98:fc:11:b6:c9:34, channel:4, authmode:3
V (5349) event: enter default callback
V (5359) tcpip_adapter: check: local, if=0 fn=0x400e33bc
0x400e33bc: tcpip_adapter_up_api at C:/myiot/esp/esp-idf/components/tcpip_adapter/tcpip_adapter_lwip.c:1065


V (5359) tcpip_adapter: call api in lwip: ret=0x0, give sem
V (53369) tcpip_adapter: check: remote, if=0 fn=0x400e33bc
0x400e33bc: tcpip_adapter_up_api at C:/myiot/esp/esp-idf/components/tcpip_adapter/tcpip_adapter_lwip.c:1065


V (5369) tcpip_adapter: check: local, if=0 fn=0x400e3814
0x400e3814: tcpip_adapter_dhcpc_start_api at C:/myiot/esp/esp-idf/components/tcpip_adapter/tcpip_adapter_lwip.c:1065


D (5379) tcpip_adapter: dhcp client init ip/mask/gw to all-0
D (5379) tcpip_adapter: if0 start ip lost tmr: enter
D (5389) tcpip_adapter: if0 start ip lost tmr: no need start because netif=0x3ffc6124 interval=120 ip=0
D (5399) tcpip_adapter: dhcp client start successfully
V (5399) tcpip_adapter: call api in lwip: ret=0x0, give sem
V (5409) tcpipp_adapter: check: remote, if=0 fn=0x400e3814
0x400e3814: tcpip_adapter_dhcpc_start_api at C:/myiot/esp/esp-idf/components/tcpip_adapter/tcpip_adapter_lwip.c:1065


V (5419) event: exit default callback
D (6259) tcpip_adapter: if0 dhcpc cb
D (6259) tcpip_adapter: if0 ip changed=1
D (62559) event: SYSTEM_EVENT_STA_GOT_IP, ip:192.168.0.191, mask:255.255.255.0, gw:192.168.0.1
V (6259) event: enter default callback
I (6269) event: sta ip: 192.168.0.191, mask: 255.255.255.0, gw: 192.168.0.1
V (6269) event: exit default callback
I (6279) mjd_wifi: OK: WIFI connected!
I (6279) esp_mqtt: esp_mqtt_start: create task
I (6289) esp_mqtt: esp_mqtt_process: begin connection attempt
I (6409) esp_mqtt: esp_mqtt_process: attemppt successful
MQTT: publishing: topic=hello => payload=world (5)
I (6419) esp_mqtt: esp_mqtt_stop: deleting task
I (6419) mjd_wifi: Disconnecting from WIFI network...
I (6419) wifi: state: run -> init (0)
I (6429) wifi: n:4 0, o:4 1, ap:255 255, sta:4 1, prof:1
D (6429) event: SYSTEM_EVENT_STA_DISCONNECTED, ssid:AREA51, ssid_len:6, bssiid:98:fc:11:b6:c9:34, reason:8
V (6439) event: enter default callback
V (6439) tcpip_adapter: check: local, if=0 fn=0x400e34b0
0x400e34b0: tcpip_adapter_down_api at C:/myiot/esp/esp-idf/components/tcpip_adapter/tcpip_adapter_lwip.c:1065


I (6439) wifi: flush txq
D (6449) tcpip_adapter: if0 start ip lost tmr: enter
I (6449) wifi: stop sw txq
D (6459) tcpip_adapter: if0 start ip lost tmr: interval=120
I (6459) wifi: lmac stop hw txq
V (6459) tcpip_adapter: call api in lwip: ret=0x0, give sem
D (6469) RTC_MODULE: Wi-Fi returns adc2 lock.
V (6479) tcpip_adapter:  check: remote, if=0 fn=0x400e34b0
0x400e34b0: tcpip_adapter_down_api at C:/myiot/esp/esp-idf/components/tcpip_adapter/tcpip_adapter_lwip.c:1065


V (6479) event: exit default callback
D (6489) event: SYSTEM_EVENT_STA_STOP
V (6489) event: enter default callback
I (6489) mjd_wifi: OK: WIFI disconnected!
V (64889) tcpip_adapter: check: local, if=0 fn=0x400e32e8
0x400e32e8: tcpip_adapter_stop_api at C:/myiot/esp/esp-idf/components/tcpip_adapter/tcpip_adapter_lwip.c:1065


V (6499) tcpip_adapter: call api in lwip: ret=0x5001, give sem
V (6509) tcpip_adapter: check: remote, if=0 fn=0x400e32e8
0x400e32e8: tcpip_adapter_stop_api at C:/myiot/esp/esp-idf/components/tcpip_adapter/tcpip_adapter_lwip.c:1065


V (6519) event: exit default callback
I (6519) myapp:

MQTT: LOOP#2 of 10
I (6519) mjjd_wifi: Connecting to the WIFI network...
D (6529) RTC_MODULE: Wi-Fi takes adc2 lock.
D (6529) phy_init: loading PHY init data from application binary
D (6539) nvs: nvs_open_from_partition phy 0
D (6539) nvs: nvs_get cal_version 4
V (6549) phy_init: phy_get_rf_cal_version: 383

D (6549) nvs: nvs_get_str_or_blob cal_mac
D (65559) nvs: nvs_get_str_or_blob cal_data
D (6569) nvs: nvs_close 4
V (6569) phy_init: register_chipv7_phy, init_data=0x3f4108a0, cal_data=0x3ffc6440, mode=0
I (6569) wifi: mode : sta (30:ae:a4:30:95:ac)
D (6579) event: SYSTEM_EVENT_STA_STTART
V (6579) event: enter default callback
V (6579) tcpip_adapter: check: local, if=0 fn=0x400e318c
0x400e318c: tcpip_adapter_start_api at C:/myiot/esp/esp-idf/components/tcpip_adapter/tcpip_adapter_lwip.c:1065


V (6589) tcpip_adapter: call api  in lwip: ret=0x0, give sem
V (6589) tcpip_adapter: check: remote, if=0 fn=0x400e318c
0x400e318c: tcpip_adapter_start_api at C:/myiot/esp/esp-idf/components/tcpip_adapter/tcpip_adapter_lwip.c:1065


V (6599) event: exit default callback
I (6729) wifi: n:4 1, o:1 0, ap:255 255, sta:4 1, prof:1
I (6729) wifi: state: init -> auth (b0)
I (6729) wifi: state: auth -> assoc (0)
I  (6739) wifi: state: assoc -> run (10)
I (6989) wifi: connected with AREA51, channel 4
D (6989) event: SYSTEM_EVENT_STA_CONNECTED, ssid:AREA51, ssid_len:6, bssid:98:fc:11:b6:c9:34, channel:4, authmode:3
V (6989) event: enter default callback

V (6989) tcpip_adapter: check: local, if=0 fn=0x400e33bc
0x400e33bc: tcpip_adapter_up_api at C:/myiot/esp/esp-idf/components/tcpip_adapter/tcpip_adapter_lwip.c:1065


V (6999) tcpip_adapter: call api in lwip: ret=0x0, give sem
V (7009) tcpip_adapter: check: remote, if=0 fn=0x400e33bc
0x400e33bc: tcpip_adapter_up_api at C:/myiot/esp/esp-idf/components/tcpip_adapter/tcpip_adapter_lwip.c:1065


V (70099) tcpip_adapter: check: local, if=0 fn=0x400e3814
0x400e3814: tcpip_adapter_dhcpc_start_api at C:/myiot/esp/esp-idf/components/tcpip_adapter/tcpip_adapter_lwip.c:1065


D (7019) tcpip_adapter: dhcp client init ip/mask/gw to alll-0
D (7019) tcpip_adapter: if0 start ip lost tmr: enter
D (7029) tcpip_adapter: if0 start ip lost tmr: already started
D (7029) tcpip_adapter: dhcp client start successfully
V (7039) tcpip_adapter: calll api in lwip: ret=0x0, give sem
V (7039) tcpip_adapter: check: remote, if=0 fn=0x400e3814
0x400e3814: tcpip_adapter_dhcpc_start_api at C:/myiot/esp/esp-idf/components/tcpip_adapter/tcpip_adapter_lwip.c:1065


V (7049) event: exit default callback
D (7779) tcpip_adapter: if0 dhcpc cb
D (7779) tcpip_adapter: if0 ip changed=0
D (7779) event: SYSTEM_EVENT_STA_GOT_IP, ip:192.168.0.191, mask:255.255.255.0, gw:192.168.0.1
V (7779) event: entter default callback
I (7779) event: sta ip: 192.168.0.191, mask: 255.255.255.0, gw: 192.168.0.1
V (7789) event: exit default callback
I (7799) mjd_wifi: OK: WIFI connected!
I (7799) esp_mqtt: esp_mqtt_start: crreate task
I (7809) esp_mqtt: esp_mqtt_process: begin connection attempt
MQTT: publishing: topic=hello => payload=world (5)
assertion "netconn state error" failed: file "C:/myiot/esp/esp-idf/components/lwip/api/api_msg.c", line 1055, function: lwi
p_netconn_do_delconn
abort() was called at PC 0x400d2ad7 on core 0
0x400d2ad7: __assert_func at /Users/ivan/e/newlib_xtensa-2.2.0-bin/newlib_xtensa-2.2.0/xtensa-esp32-elf/newlib/libc/stdlib/
../../../.././newlib/libc/stdlib/assert.c:63 (discriminator 8)


Backtrace: 0x4008c478:0x3ffbdb20 0x4008c61b:0x3ffbdb40 0x400d2ad7:0x3ffbdb60 0x4011ea47:0x3ffbdb90 0x4010fda5:0x3ffbdbb0
0x4008c478: invoke_abort at C:/myiot/esp/esp-idf/components/esp32/panic.c:648

0x4008c61b: abort at C:/myiot/esp/esp-idf/components/esp32/panic.c:648

0x400d2ad7: __assert_func at /Users/ivan/e/newlib_xtensa-2.2.0-bin/newlib_xtensa-2.2.0/xtensa-esp32-elf/newlib/libc/stdlib/
../../../.././newlib/libc/stdlib/assert.c:63 (discriminator 8)

0x4011ea47: lwip_netconn_do_delconn at C:/myiot/esp/esp-idf/components/lwip/api/api_msg.c:1881 (discriminator 6)

0x4010fda5: tcpip_thread at C:/myiot/esp/esp-idf/components/lwip/api/tcpip.c:474


CPU halted.
```

#.
# APPENDICES
#.

# 1. SOP for upload to GITHUB
https://github.com/pantaluna/support_esp_mqtt

## 1.a: BROWSER: create github public repo support_esp_mqtt of pantaluna at Github.com

## 1.b: MSYS2 git
```
git config --system --unset credential.helper
git config credential.helper store
git config --list

cd  /c/myiot/esp/support_esp_mqtt
git init
git add .
git commit -m "First commit"
git remote add origin https://github.com/pantaluna/support_esp_mqtt.git
git push --set-upstream origin master

git remote show origin
git status
```

# 2. SOP for source updates
```
cd  /c/myiot/esp/support_esp_mqtt
git add .
git commit -m "Another commit"
git push --set-upstream origin master

git status
```
