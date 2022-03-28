/* Provide SNTP support for an SSP-IDF based applicatio0n.
* Heavily cribbed from examples/protocols/sntp/main/sntp_example_main.c
*/

extern "C" {
#include <time.h>
#include <sys/time.h>
#include <esp_system.h>
#include <esp_sntp.h>
#include <esp_log.h>
}

#include "sntp.h"
/* The following include is excluded from the git project and
   must be crafted to meet your needs. It must define

#define SSID "your_SSID"
#define  PWD "your_password"
#define sntp_server "pfsense.localdomain"
*/
#include "secrets.h" // user provided include

static const char *TAG = "sntp";

static void obtain_time(void);
static void initialize_sntp(void);

void time_sync_notification_cb(struct timeval *tv)
{
    ESP_LOGI(TAG, "Notification of a time synchronization event");
}

/*
TBD add 
    ++boot_count;
    ESP_LOGI(TAG, "Boot count: %d", boot_count);
*/

time_t init_sntp(void)
{
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    // Is time set? If not, tm_year will be (1970 - 1900).
    if (timeinfo.tm_year < (2016 - 1900)) {
        ESP_LOGI(TAG, "Time is not set yet. Connecting to WiFi and getting time over NTP.");
        obtain_time();
        // update 'now' variable with current time
        time(&now);
    }
    return now;
}

static void obtain_time(void)
{
    sntp_servermode_dhcp(1);      // accept NTP offers from DHCP server, if any
    initialize_sntp();

    // wait for time to be set
    time_t now = 0;
    struct tm timeinfo = {};
    int retry = 0;
    const int retry_count = 15;
    while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && ++retry < retry_count) {
        ESP_LOGI(TAG, "Waiting for system time to be set... (%d/%d)", retry, retry_count);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    time(&now);
    localtime_r(&now, &timeinfo);
}

static void initialize_sntp(void)
{
    ESP_LOGI(TAG, "Initializing SNTP");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);

    sntp_setservername(0,  sntp_server);
    sntp_set_time_sync_notification_cb(time_sync_notification_cb);
    sntp_init();
}