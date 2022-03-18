/* Starting point. Will eventually include
 * * blinking LED
 * * WiFi support - associate with AP
 * * MQTT support  - publish
 * * NTP support - synchronize time
 *
 * Some code shamelessly copied from
 * * expidf-blink example.
 * */

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const gpio_num_t blink_led = 2;

void setup_LED(gpio_num_t gpio)
{
    gpio_pad_select_gpio(gpio);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(gpio, GPIO_MODE_OUTPUT);
}

void blink_led_task(void *param)
{
    while(1) {
        /* Blink off (output low) */
        printf("Turning off the LED\n");
        gpio_set_level(blink_led, 0);
        vTaskDelay(990 / portTICK_PERIOD_MS);
        /* Blink on (output high) */
	    printf("Turning on the LED\n");
        gpio_set_level(blink_led, 1);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    setup_LED(blink_led);

    // Note: 512 is insufficient stack for blink_led_task
    xTaskCreate(&blink_led_task, "blink_led_task", 1024, NULL, 5, NULL);

    // Following loop is superfluous. App continues to execute
    // even if app_main() exits
    while(1) {
        // Blink off (output low) 
	    printf("looping main\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}