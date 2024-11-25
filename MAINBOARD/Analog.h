/*
 * Analog.hpp
 *
 *  Created on: Oct 18, 2023
 *      Author: cristian
 */

#ifndef SRC_ANALOG_HPP_
#define SRC_ANALOG_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>
#include <unistd.h>


int read_ADvalue_row_ch0(char * device_name, int *value);
int read_ADvalue_row_ch1(char * device_name, int *value);

int read_ADvalue_ch0(char * device_name, float *value);
int read_ADvalue_ch1(char * device_name, float *value);


#endif /* SRC_ANALOG_HPP_ */
