/*
 *
 */
#ifndef __MJD_MJDLIB_H__
#define __MJD_MJDLIB_H__

#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"

#include "esp_event_loop.h"
#include "esp_clk.h"
#include "esp_log.h"
#include "esp_spi_flash.h"
#include "esp_system.h"

#include "driver/rmt.h"
#include "nvs_flash.h"
#include "soc/rmt_reg.h"
#include "soc/soc.h"


#ifdef __cplusplus
extern "C" {
#endif

/**********
 * kernel.h
 */
/*
 * ARRAY_SIZE - get the number of elements in array @arr
 * @arr: array to be sized
 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/**********
 * RTOS
 */
#define RTOS_DELAY_1SEC (1 * 1000 / portTICK_PERIOD_MS)
#define RTOS_DELAY_2SEC (2 * 1000 / portTICK_PERIOD_MS)
#define RTOS_DELAY_3SEC (3 * 1000 / portTICK_PERIOD_MS)
#define RTOS_DELAY_5SEC (5 * 1000 / portTICK_PERIOD_MS)
#define RTOS_TASK_PRIORITY_NORMAL (5)

/**********
 *  Definitions for errors
 */
typedef int32_t mjd_err_t;
#define MJD_OK     (0)
#define MJD_ERROR  (-1)

#define MJD_ERR_INVALID_ARG       (0x100)
#define MJD_ERR_CHECKSUM          (0x101)
#define MJD_ERR_ESP_GPIO          (0x102)
#define MJD_ERR_ESP_RMT           (0x103)
#define MJD_ERR_ESP_RTOS          (0x104)

#define MJD_ERR_INVALID_STATE       (0x110)
#define MJD_ERR_NOT_FOUND           (0x111)
#define MJD_ERR_NOT_SUPPORTED       (0x112)
#define MJD_ERR_TIMEOUT             (0x113)
#define MJD_ERR_INVALID_RESPONSE    (0x114)

/**********
 * SYSTEM
 */
void mjdlib_rtos_wait_forever();
uint32_t mjdlib_seconds_to_milliseconds(uint32_t seconds);
uint32_t mjdlib_seconds_to_microseconds(uint32_t seconds);
void mjdlib_print_clanguage_details();
void mjdlib_print_time();
void mjdlib_print_chip_info();

/**********
 * LED
 */
#define HUZZAH32_GPIO_NUM_LED (GPIO_NUM_13)
#define HUZZAH32_GPIO_BITPIN_LED (1ULL<<HUZZAH32_GPIO_NUM_LED)

void mjdlib_led_setup(int gpio_nr);
void mjdlib_led_on(int gpio_nr);
void mjdlib_led_off(int gpio_nr);


#ifdef __cplusplus
}
#endif


#endif /* __MJD_MJDLIB_H__ */
