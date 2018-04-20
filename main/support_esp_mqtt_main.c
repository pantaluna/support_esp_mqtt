/*
 *
 */
#include "mjd.h"
#include "mjd_wifi.h"

#include "esp_mqtt.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

/*
 * Logging
 */
static const char TAG[] = "myapp";

/*
 * WIFI
 */
#define WEB_SERVER_HOST_NAME ("example.com")

char *WIFI_SSID = CONFIG_MY_WIFI_SSID;
char *WIFI_PASSWORD = CONFIG_MY_WIFI_PASSWORD;

/*
 * MQTT
 */
#define MQTT_HOST ("broker.shiftr.io")
#define MQTT_PORT ("1883")
#define MQTT_USER ("try")
#define MQTT_PASS ("try")
#define MJD_MQTT_QOS_0 (0)
#define MJD_MQTT_QOS_1 (1)

static EventGroupHandle_t mqtt_event_group;
static const int CONNECTED_BIT = BIT0;
static const int DISCONNECTED_BIT = BIT1;

static void mqtt_status_callback(esp_mqtt_status_t status) {
    switch (status) {
    case ESP_MQTT_STATUS_CONNECTED:
        xEventGroupSetBits(mqtt_event_group, CONNECTED_BIT);
        xEventGroupClearBits(mqtt_event_group, DISCONNECTED_BIT);
        break;
    case ESP_MQTT_STATUS_DISCONNECTED: // @todo This bitflag is not set when stopping mqtt...
        xEventGroupSetBits(mqtt_event_group, DISCONNECTED_BIT);
        xEventGroupClearBits(mqtt_event_group, CONNECTED_BIT);
        break;
    }
}

static void mqtt_message_callback(const char *topic, uint8_t *payload, size_t len) {
    printf("(not used in this prj) subscription message received: topic=%s => payload=%s (%d)\n", topic, payload, (int) len);
}

/*
 * INIT
 */

/*
 * MAIN
 */
void app_main() {
    ESP_LOGI(TAG, "app_main() BEGIN");

    /* SOC init */
    ESP_LOGI(TAG, "@doc exec nvs_flash_init() - mandatory for Wifi to work later on");
    nvs_flash_init();

    /* MY STANDARD Init */
    ESP_LOGI(TAG, "@doc Wait X seconds after power-on (start logic analyzer, let sensors to power-up");
    vTaskDelay(RTOS_DELAY_3SEC);

    /*
     * WIFI
     */
    ESP_LOGI(TAG, "***SECTION: WIFI***");
    ESP_LOGI(TAG, "WIFI_SSID:     %s", WIFI_SSID);
    ESP_LOGI(TAG, "WIFI_PASSWORD: %s", WIFI_PASSWORD);
    mjd_wifi_sta_init(WIFI_SSID, WIFI_PASSWORD);

    /*
     * MQTT
     */
    ESP_LOGI(TAG, "***SECTION: MQTT***");
    mqtt_event_group = xEventGroupCreate();
    esp_mqtt_init(mqtt_status_callback, mqtt_message_callback, 256, 2000);

    const char *payload = "payloadworld";

    ESP_LOGI(TAG, "WIFI+MQTT: start");
    mjd_wifi_sta_start();
    esp_mqtt_start(MQTT_HOST, MQTT_PORT, "support_esp_mqtt", MQTT_USER, MQTT_PASS);
    xEventGroupWaitBits(mqtt_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);

    uint32_t nbr_of_errors = 0;
    uint32_t total = 2500;
    uint32_t j = 0;
    ESP_LOGI(TAG, "MQTT + WIFI: start stop: %u times (@important it always asserts in the 2nd iteration of the LOOP", total);
    while (++j <= total) {
        ESP_LOGI(TAG, "\n\nMQTT: LOOP#%u of %u", j, total);

        ESP_LOGI(TAG, "MQTT: publishing: topic=hello => payload=%s (%u)", payload, (uint32_t) strlen(payload));
        if (esp_mqtt_publish("topichello", (void *) payload, (uint32_t) strlen(payload), MJD_MQTT_QOS_1, false) != true) { // QOS 0 works...
            ESP_LOGE(TAG, "mjd_mqtt_publish(): FAILED");
            ++nbr_of_errors;
            vTaskDelay(RTOS_DELAY_5SEC);
        }

        // avoid triggered watchdog
        vTaskDelay(RTOS_DELAY_1MILLISEC);
    }

    ESP_LOGI(TAG, "WIFI+MQTT: stop");
    esp_mqtt_stop();
    mjd_wifi_sta_disconnect_stop();

    // Report
    ESP_LOGI(TAG, "REPORT");
    ESP_LOGI(TAG, "  nbr_of_errors: %i", nbr_of_errors);

    /*
     * --END
     */
    ESP_LOGI(TAG, "app_main() END");
}
