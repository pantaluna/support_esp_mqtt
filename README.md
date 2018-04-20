https://github.com/256dpi/esp-mqtt/issues/5
https://github.com/pantaluna/support_esp_mqtt

# Problem: the second esp_mqtt_publish(QOS1) always fails with error "esp_mqtt: lwmqtt_yield: -4".
@important This program uses esp_mqtt_publish(QOS1) - opposed to QOS0 which works fine all the time.

# 1. Environment
- MCU: Adafruit HUZZAH32 ESP32 development board.
- MCU: Wemos LOLIN32 Lite development board.
- ESP-IDF Github master branch of Apr 20, 2018.

# 2. MAKE MENUCONFIG: Set WIFI SSID and Password
```
cd ~
git clone --recursive https://github.com/pantaluna/support_esp_mqtt.git
cd  support_esp_mqtt
make menuconfig
```

# 3. MAKE FLASH MONITOR
```
cd  ~/support_esp_mqtt
make flash monitor
```

SERIAL UART:

```
...
I (5775) myapp: MQTT: LOOP#1 of 2500
I (5707) myapp: MQTT: publishing: topic=hello => payload=payloadworld (12)
I (5747) myapp: MQTT: LOOP#2 of 2500
I (5757) myapp: MQTT: publishing: topic=hello => payload=payloadworld (12)
E (7747) esp_mqtt: lwmqtt_yield: -4 *****
I (7747) esp_mqtt: esp_mqtt_process: exit task
W (7747) esp_mqtt: esp_mqtt_publish: not connected
E (7747) myapp: mjd_mqtt_publish(): FAILED *****
...
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

git tag --annotate v1.0 --message "The original bug report"
git push origin --tags

```

# 2. SOP for source updates
```
cd  /c/myiot/esp/support_esp_mqtt
git add .
git commit -m "Testing v0.5.3"
git push --set-upstream origin master

git status
```

# 3. esp-mqtt BUGFIX esp_lwmqtt.c (OK: released in v0.4.4)
void esp_lwmqtt_network_disconnect(esp_lwmqtt_network_t *network) {
  // immediately return if conn is not set
  if (network->conn == NULL) {
    return;
  }

  // delete connection
  netconn_delete(network->conn);

  // BEGIN @bugfix https://github.com/256dpi/esp-mqtt/issues/5
  // reset network
    network->conn = NULL;
    network->rest_buf = NULL;
    network->rest_len = 0;
  // END
}
