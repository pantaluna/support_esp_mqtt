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
 * FreeRTOS settings
 */
#define MYAPP_RTOS_TASK_STACK_SIZE_LARGE (8192)
#define MYAPP_RTOS_TASK_PRIORITY_NORMAL (RTOS_TASK_PRIORITY_NORMAL)

/*
 * WIFI
 */
#define WEB_SERVER_HOST_NAME ("example.com")

char *WIFI_SSID = CONFIG_MY_WIFI_SSID;
char *WIFI_PASSWORD = CONFIG_MY_WIFI_PASSWORD;

/*
 * my loop settings
 */
#define MJD_LOOP_NBR_OF_PUBLISHED_MESSAGES (3)
#define MJD_LOOP_PAYLOAD_LENGTH (4000)

/*
 * MQTT
 */
#define MJD_MQTT_QOS_0 (0)
#define MJD_MQTT_QOS_1 (1)

#define MQTT_BUFFER_SIZE  (4096)  // @suggested 256 @used 4096 (>max payload length)
#define MQTT_TIMEOUT      (2000)  // @suggested 2000 @used 2000

#define MY_MQTT_HOST ("broker.shiftr.io")
#define MY_MQTT_PORT ("1883")
#define MY_MQTT_USER ("try")
#define MY_MQTT_PASS ("try")

/*#define MY_MQTT_HOST "192.168.0.95" // @important The DNS name "s3..." does not work on an MCU@LocalAN because it returns the ISP's WAN IP and this IP is not whitelisted in Ubuntu UFW!
#define MY_MQTT_PORT "12430"
#define MY_MQTT_USER "zurich"
#define MY_MQTT_PASS "swiss"*/

static EventGroupHandle_t mqtt_event_group;
static const int MQTT_CONNECTED_BIT = BIT0;

static void mqtt_status_callback(esp_mqtt_status_t status) {
    switch (status) {
    case ESP_MQTT_STATUS_CONNECTED:
        xEventGroupSetBits(mqtt_event_group, MQTT_CONNECTED_BIT);
        break;
    case ESP_MQTT_STATUS_DISCONNECTED: // @doc This bitflag is not set when stopping mqtt...
        xEventGroupClearBits(mqtt_event_group, MQTT_CONNECTED_BIT);
        break;
    }
}

static void mqtt_message_callback(const char *topic, uint8_t *payload, size_t len) {
    printf("(not used in this prj) subscription message received: topic=%s => payload(%d)=%s \n", topic, (int) len, payload);
}

/*
 * TASK
 */
void main_task(void *pvParameter) {
     ESP_LOGD(TAG, "%s()", __FUNCTION__);

     mjd_log_memory_statistics();

     /* SOC init */
     ESP_LOGI(TAG, "@doc exec nvs_flash_init() - mandatory for Wifi to work later on");
     nvs_flash_init();

     /* MY STANDARD Init */
     ESP_LOGI(TAG, "@doc Wait X seconds after power-on (start logic analyzer, let sensors power-up)");
     vTaskDelay(RTOS_DELAY_1MILLISEC);

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
     esp_mqtt_init(mqtt_status_callback, mqtt_message_callback, MQTT_BUFFER_SIZE, MQTT_TIMEOUT);

     char topic[] = "hello";

     char payload[MJD_LOOP_PAYLOAD_LENGTH + 1] = "";
     memset(payload, '-', MJD_LOOP_PAYLOAD_LENGTH);

     mjd_log_memory_statistics();

     ESP_LOGI(TAG, "WIFI: start");
     mjd_wifi_sta_start();

     mjd_log_memory_statistics();

     ESP_LOGI(TAG, "MQTT info: LOOP %u times (@important it often asserts in the 2nd iteration of the LOOP)", MJD_LOOP_NBR_OF_PUBLISHED_MESSAGES);
     ESP_LOGI(TAG, "MQTT info: esp_mqtt_publish: topic (len %u) => payload (len %u) ", (uint32_t) strlen(topic), (uint32_t) strlen(payload));

     uint32_t nbr_of_errors = 0;
     uint32_t j = 0;
     while (++j <= MJD_LOOP_NBR_OF_PUBLISHED_MESSAGES) {
         printf("ITER#%u ", j); fflush(stdout);

         ESP_LOGI(TAG, "MQTT: start");
         esp_mqtt_start(MY_MQTT_HOST, MY_MQTT_PORT, "support_esp_mqtt", MY_MQTT_USER, MY_MQTT_PASS);
         xEventGroupWaitBits(mqtt_event_group, MQTT_CONNECTED_BIT, false, true, portMAX_DELAY);

         ESP_LOGI(TAG, "MQTT: publish");
         if (esp_mqtt_publish(topic, (void *) payload, (uint32_t) strlen(payload), MJD_MQTT_QOS_1, false) != true) { // QOS 0 works...
             ESP_LOGE(TAG, "esp_mqtt_publish(): FAILED");
             ++nbr_of_errors;
             vTaskDelay(RTOS_DELAY_5SEC);
         }

         ESP_LOGI(TAG, "MQTT: stop");
         esp_mqtt_stop();
         xEventGroupClearBits(mqtt_event_group, MQTT_CONNECTED_BIT); // @important You have to do this MANUALLY. @suggestfeature Await MQTT_STOPPED_BIT

         // avoid triggered watchdog
         vTaskDelay(RTOS_DELAY_1MILLISEC);
     }
     printf("\n\n");

     mjd_log_memory_statistics();

     ESP_LOGI(TAG, "WIFI: stop");
     mjd_wifi_sta_disconnect_stop();

     mjd_log_memory_statistics();

     // Report
     ESP_LOGI(TAG, "REPORT: nbr_of_mqttpublish_errors: %i", nbr_of_errors);

     /********************************************************************************
      * Task Delete
      * @doc Passing NULL will end the current task
      */
     vTaskDelete(NULL);
 }
/*
 * MAIN
 */
void app_main() {
    ESP_LOGD(TAG, "%s()", __FUNCTION__);

    mjd_log_memory_statistics();

    // Production: skip less useless messages!
    esp_log_level_set("wifi", ESP_LOG_WARN); // @important Disable INFO messages which are too detailed for me.
    esp_log_level_set("tcpip_adapter", ESP_LOG_WARN); // @important Disable INFO messages which are too detailed for me.

    /**********
     * TASK:
     * @important For stability (RMT + Wifi): always use xTaskCreatePinnedToCore(APP_CPU_NUM) [Opposed to xTaskCreate()]
     */
    BaseType_t xReturned;
    xReturned = xTaskCreatePinnedToCore(&main_task, "main_task (name)", MYAPP_RTOS_TASK_STACK_SIZE_LARGE, NULL,
    MYAPP_RTOS_TASK_PRIORITY_NORMAL, NULL, APP_CPU_NUM);
    if (xReturned == pdPASS) {
        ESP_LOGI(TAG, "OK Task has been created, and is running right now");
    } else {
        ESP_LOGE(TAG, "ERROR Cannot create task!");
    }

    mjd_log_memory_statistics();

    ESP_LOGD(TAG, "%s() END", __FUNCTION__);
}
