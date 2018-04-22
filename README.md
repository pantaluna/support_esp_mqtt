https://github.com/256dpi/esp-mqtt/
https://github.com/pantaluna/support_esp_mqtt

# Problem branch idf3 and tag v0.5.3: the 2nd esp_mqtt_publish(QOS1) always fails with error "esp_mqtt: lwmqtt_yield: -4".
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

# 0. GET esp_mqtt from Github

### INITIAL CLONE

#MINGW>>
mkdir --parents /c/myiot/esp/support_esp_mqtt/components
cd              /c/myiot/esp/support_esp_mqtt/components

git clone --recursive https://github.com/256dpi/esp-mqtt.git
cd esp-mqtt
git status

### Checkout tag v0.5.4
cd  /c/myiot/esp/support_esp_mqtt/components/esp-mqtt
git pull
git submodule update --init --recursive
git status

git tag --list
git checkout tags/v0.5.4
git describe --tags
git submodule update --init --recursive
git status

### Checkout branch idf3
cd  /c/myiot/esp/support_esp_mqtt/components/esp-mqtt
git pull
git submodule update --init --recursive
git status

git branch
git checkout idf3
git show-branch
git submodule update --init --recursive
git status


# LWIP error codes
typedef enum {
  LWMQTT_SUCCESS = 0,
  LWMQTT_BUFFER_TOO_SHORT = -1,
  LWMQTT_VARNUM_OVERFLOW = -2,
  LWMQTT_NETWORK_FAILED_CONNECT = -3,
  LWMQTT_NETWORK_TIMEOUT = -4,
  LWMQTT_NETWORK_FAILED_READ = -5,
  LWMQTT_NETWORK_FAILED_WRITE = -6,
  LWMQTT_REMAINING_LENGTH_OVERFLOW = -7,
  LWMQTT_REMAINING_LENGTH_MISMATCH = -8,
  LWMQTT_MISSING_OR_WRONG_PACKET = -9,
  LWMQTT_CONNECTION_DENIED = -10,
  LWMQTT_FAILED_SUBSCRIPTION = -11,
  LWMQTT_SUBACK_ARRAY_OVERFLOW = -12,
  LWMQTT_PONG_TIMEOUT = -13,
} lwmqtt_err_t;


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
git commit -m "Testing branch idf3"
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
