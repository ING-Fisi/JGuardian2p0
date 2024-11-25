#ifndef GPIO_H
#define GPIO_H


#include <linux/gpio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdint.h>
#include <getopt.h>
#include <stdlib.h>
#include <sys/poll.h>

void gpio_list(const char *dev_name);

void gpio_write(const char *dev_name, int offset, uint8_t value);

void gpio_read(const char *dev_name, int offset);

void gpio_poll(const char *dev_name, int offset);

void help(const char *app);

#endif // GPIO_H
