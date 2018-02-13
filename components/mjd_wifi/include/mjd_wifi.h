/*
 *
 */
#ifndef __MJD_WIFI_H__
#define __MJD_WIFI_H__

#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"

#include "esp_clk.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "esp_spi_flash.h"
#include "esp_system.h"
#include "esp_wifi.h"

#include "nvs_flash.h"

#ifdef __cplusplus
extern "C" {
#endif

// Function Declarations (public)
void mjd_wifi_init(char *param_ssid, char *param_password);
void mjd_wifi_start();
void mjd_wifi_disconnect_stop();

#ifdef __cplusplus
}
#endif

#endif /* __MJD_WIFI_H__ */
