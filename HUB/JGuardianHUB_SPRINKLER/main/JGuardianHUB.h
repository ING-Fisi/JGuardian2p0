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



#define SPRINKLER3

#ifdef SPRINKLER1
static const char *TAG = "JGUARDIAN_HUB_SPRINKLER1";
#endif
#ifdef SPRINKLER2
static const char *TAG = "JGUARDIAN_HUB_SPRINKLER2";
#endif
#ifdef SPRINKLER3
static const char *TAG = "JGUARDIAN_HUB_SPRINKLER3";
#endif
#ifdef SPRINKLER4
static const char *TAG = "JGUARDIAN_HUB_SPRINKLER4";
#endif



//************************* RELE ******************************//
#define GPIO_OUTPUT_IO_LED    38
#define GPIO_OUTPUT_PIN_SEL_LED  (1ULL<<GPIO_OUTPUT_IO_LED)

#define GPIO_OUTPUT_IO_1    1
#define GPIO_OUTPUT_PIN_SEL_0  (1ULL<<GPIO_OUTPUT_IO_1)

#define GPIO_OUTPUT_IO_2    2
#define GPIO_OUTPUT_PIN_SEL_1  (1ULL<<GPIO_OUTPUT_IO_2)

#define GPIO_OUTPUT_IO_3    41
#define GPIO_OUTPUT_PIN_SEL_2  (1ULL<<GPIO_OUTPUT_IO_3)

#define GPIO_OUTPUT_IO_4    42
#define GPIO_OUTPUT_PIN_SEL_3  (1ULL<<GPIO_OUTPUT_IO_4)

#define GPIO_OUTPUT_IO_5    45
#define GPIO_OUTPUT_PIN_SEL_4  (1ULL<<GPIO_OUTPUT_IO_5)

#define GPIO_OUTPUT_IO_6    46
#define GPIO_OUTPUT_PIN_SEL_5  (1ULL<<GPIO_OUTPUT_IO_6)


httpd_handle_t start_JGuardian_SERVER();

esp_err_t master_init(void);
void master_operation_func(void *arg);
int request_modbus_info(char* response);

void wifi_init_sta(void);

#endif /* MAIN_JGUARDIANHUB_H_ */
