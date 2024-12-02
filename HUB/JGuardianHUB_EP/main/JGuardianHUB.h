/*
 * JGuardianHUB.h
 *
 *  Created on: Oct 21, 2024
 *      Author: biglap
 */

#ifndef MAIN_JGUARDIANHUB_H_
#define MAIN_JGUARDIANHUB_H_

#include "string.h"
#include "esp_check.h"
#include "modbus_params.h"  // for modbus parameters structures
#include "mbcontroller.h"
#include "sdkconfig.h"
#include "esp_http_server.h"
#include "utility.h"
#include "esp_mac.h"


#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include <netdb.h>
#include "nvs_flash.h"
#include "driver/gpio.h"

static const char *TAG = "JGUARDIAN_HUB_EP";



//************************* RELE ******************************//
#define GPIO_OUTPUT_IO_LED    21
#define GPIO_OUTPUT_PIN_SEL_LED  (1ULL<<GPIO_OUTPUT_IO_LED)

#define GPIO_OUTPUT_IO_1    32
#define GPIO_OUTPUT_PIN_SEL_0  (1ULL<<GPIO_OUTPUT_IO_1)

#define GPIO_OUTPUT_IO_2    33
#define GPIO_OUTPUT_PIN_SEL_1  (1ULL<<GPIO_OUTPUT_IO_2)

#define GPIO_OUTPUT_IO_3    25
#define GPIO_OUTPUT_PIN_SEL_2  (1ULL<<GPIO_OUTPUT_IO_3)

#define GPIO_OUTPUT_IO_4    26
#define GPIO_OUTPUT_PIN_SEL_3  (1ULL<<GPIO_OUTPUT_IO_4)




httpd_handle_t start_JGuardian_SERVER();

esp_err_t master_init(void);
void master_operation_func(void *arg);
int request_modbus_info(char* response);

void wifi_init_sta(void);

#endif /* MAIN_JGUARDIANHUB_H_ */
