    /*
 * WIFI
 * @doc static <global var>/<global func>: its scope is restricted to the file in which it is declared.
 */

// Component header file(s)
#include "mjd_mjdlib.h"
#include "mjd_wifi.h"

/*
 * Logging
 */
static const char TAG[] = "mjd_wifi";

/*
 * MAIN
 */
static EventGroupHandle_t wifi_event_group;
const int CONNECTED_BIT = BIT0;
const int DISCONNECTED_BIT = BIT1;

/*********************************************************************************
 * PRIVATE FUNCS
 *
 *********************************************************************************/
static esp_err_t mjd_wifi_event_handler(void *ctx, system_event_t *event) {
    switch (event->event_id) {
    case SYSTEM_EVENT_STA_START:
        ESP_ERROR_CHECK(esp_wifi_connect());
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
        xEventGroupClearBits(wifi_event_group, DISCONNECTED_BIT);
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        xEventGroupSetBits(wifi_event_group, DISCONNECTED_BIT);
        xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
        break;
    default:
        break;
    }
    return ESP_OK;
}


/*********************************************************************************
 * PUBLIC FUNCS.
 *
 *********************************************************************************/
void mjd_wifi_init(char *param_ssid, char *param_password) {
    wifi_event_group = xEventGroupCreate();
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_init(mjd_wifi_event_handler, NULL));
    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_init_config));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    wifi_config_t wifi_config = { 0 };    // init struct fields for this variable

    strcpy((char *)wifi_config.sta.ssid, param_ssid);  // (to,from)
    strcpy((char *)wifi_config.sta.password, param_password);  // (to,from)

    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_LOGI(TAG, "OK: WIFI initialized!");
}

void mjd_wifi_start() {
    ESP_LOGI(TAG, "Connecting to the WIFI network...");
    ESP_ERROR_CHECK(esp_wifi_start());
    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);
    ESP_LOGI(TAG, "OK: WIFI connected!");
}

void mjd_wifi_disconnect_stop() {
    ESP_LOGI(TAG, "Disconnecting from WIFI network...");
    ESP_ERROR_CHECK(esp_wifi_disconnect());
    ESP_ERROR_CHECK(esp_wifi_stop());    //
    xEventGroupWaitBits(wifi_event_group, DISCONNECTED_BIT, false, true, portMAX_DELAY);
    ESP_LOGI(TAG, "OK: WIFI disconnected!");
}
