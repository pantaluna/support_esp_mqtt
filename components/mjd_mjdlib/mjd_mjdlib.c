/*
 * @doc static <global var>/<global func>: its scope is restricted to the file in which it is declared.
 *
 */

// Component header file
#include "mjd_mjdlib.h"

/*
 * Logging
 */
static const char TAG[] = "mjd_mjdlib";

/*
 * SYSTEM
 */

/*********************************************************************************
 * PUBLIC.
 *********************************************************************************/
uint32_t mjdlib_seconds_to_milliseconds(uint32_t seconds) {
    return seconds * 1000;
}
uint32_t mjdlib_seconds_to_microseconds(uint32_t seconds) {
    return seconds * 1000 * 1000;
}

/*********************************************************************************
 * PUBLIC.
 *********************************************************************************/
void mjdlib_print_clanguage_details() {
    printf("C LANGUAGE INFO:\n");
    printf("  __FILE__: %s\n", __FILE__);
    printf("  __LINE__: %d\n", __LINE__);
    printf("  char\n");
    printf("    Storage size for char: %d \n", sizeof(char));
    printf("    Number of bits in a char: %d \n", CHAR_BIT);
    printf("  int\n");
    printf("    Storage size for int: %d \n", sizeof(int));
    printf("    Minimum value: %i\n", INT_MIN);
    printf("    Maximum value: %i\n", INT_MAX);
    printf("  long\n");
    printf("    Storage size for long: %d \n", sizeof(long));
    printf("    Minimum value: %ld\n", LONG_MIN);
    printf("    Maximum value: %ld\n", LONG_MAX);
    printf("  float\n");
    printf("    Storage size for float: %d \n", sizeof(float));
    printf("    Minimum positive value: %E\n", FLT_MIN);
    printf("    Maximum positive value: %E\n", FLT_MAX);
    printf("    Precision value: %d\n", FLT_DIG);
    printf("\n");
}

/*********************************************************************************
 * PUBLIC.
 *********************************************************************************/
void mjdlib_print_time() {
    time_t current_time;
    char* current_time_string;

    /* Obtain current time & Convert to local time format. ctime() adds suffix \n */
    current_time = time(NULL);
    current_time_string = ctime(&current_time);
    if (current_time_string == NULL) {
        fprintf(stderr, "Failure to convert the current time.\n");
    }
    printf("\n*** Current time is %s\n", current_time_string);
}

/*********************************************************************************
 * PUBLIC.
 *********************************************************************************/
void mjdlib_print_chip_info() {
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);

    printf("*** This is an ESP32 chip\n");
    printf("  APB clock frequency (Hz):    %d\n", esp_clk_apb_freq());

    printf("  CPU clock frequency (Hz):   %d\n", esp_clk_cpu_freq());
    printf("  CPU cores:    %d\n", chip_info.cores);
    printf("  Silicon rev.: %d\n", chip_info.revision);
    printf("  Features:     %s%s%s\n", (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WIFI" : "",
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "", (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
    printf("  Flash:        %dMB %s\n", spi_flash_get_chip_size() / 1024 / 1024,
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
    printf("\n");
    fflush(stdout);
}

/*
 * RTOS
 */
/*********************************************************************************
 * PUBLIC.
 *********************************************************************************/
void mjdlib_rtos_wait_forever() {
    while (1) {
        vTaskDelay(RTOS_DELAY_5SEC);
    }
}

/*
 * MCU LED
 */
/*********************************************************************************
 * PUBLIC.
 *********************************************************************************/
void mjdlib_led_setup(int gpio_nr) {
    ESP_LOGI(TAG, "led_setup()");

    gpio_config_t io_conf;

    io_conf.pin_bit_mask = (1ULL << gpio_nr);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&io_conf);
}

/*********************************************************************************
 * PUBLIC.
 *********************************************************************************/
void mjdlib_led_on(int gpio_nr) {
    ESP_ERROR_CHECK(gpio_set_level(gpio_nr, 1));
    ESP_LOGI(TAG, "led_on() for GPIO#%d", gpio_nr);
}

/*********************************************************************************
 * PUBLIC.
 *********************************************************************************/
void mjdlib_led_off(int gpio_nr) {
    ESP_ERROR_CHECK(gpio_set_level(gpio_nr, 0));
    ESP_LOGI(TAG, "led_off() for GPIO#%d", gpio_nr);
}
