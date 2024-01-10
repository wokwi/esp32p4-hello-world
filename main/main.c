#include <stdio.h>
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

#define LED_RED GPIO_NUM_9

void app_main(void)
{
  gpio_reset_pin(LED_RED);
  gpio_set_direction(LED_RED, GPIO_MODE_OUTPUT);

  printf("Hello, Wokwi!\n");

  /* Print chip information */
  esp_chip_info_t chip_info;
  uint32_t flash_size;
  esp_chip_info(&chip_info);
  printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
          CONFIG_IDF_TARGET,
          chip_info.cores,
          (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
          (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

  unsigned major_rev = chip_info.revision / 100;
  unsigned minor_rev = chip_info.revision % 100;
  printf("silicon revision v%d.%d, ", major_rev, minor_rev);
  if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
      printf("Get flash size failed");
      return;
  }

  printf("%luMB %s flash\n", flash_size / (1024 * 1024),
          (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

  printf("Minimum free heap size: %ld bytes\n", esp_get_minimum_free_heap_size());

  while (1)
  {
    gpio_set_level(LED_RED, 0);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    gpio_set_level(LED_RED, 1);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
