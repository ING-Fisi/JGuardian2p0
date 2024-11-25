#include "gpio.h"



typedef enum
{
    APP_OPT_GPIO_LIST,
    APP_OPT_GPIO_READ,
    APP_OPT_GPIO_WRITE,
    APP_OPT_GPIO_POLL,
    APP_OPT_UNKNOWN
} app_mode_t;

typedef struct
{
    char *dev;
    int offset;
    uint8_t val;
    app_mode_t mode;
} app_opt_t;

 void gpio_list(const char *dev_name)
{
    struct gpiochip_info info;
    struct gpioline_info line_info;
    int fd, ret;
    fd = open(dev_name, O_RDONLY);
    if (fd < 0)
    {
        printf("Unabled to open %s: %s", dev_name, strerror(errno));
        return;
    }
    ret = ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, &info);
    if (ret == -1)
    {
        printf("Unable to get chip info from ioctl: %s", strerror(errno));
        close(fd);
        return;
    }
    printf("Chip name: %s\n", info.name);
    printf("Chip label: %s\n", info.label);
    printf("Number of lines: %d\n", info.lines);

    for (int i = 0; i < info.lines; i++)
    {
        line_info.line_offset = i;
        ret = ioctl(fd, GPIO_GET_LINEINFO_IOCTL, &line_info);
        if (ret == -1)
        {
            printf("Unable to get line info from offset %d: %s", i, strerror(errno));
        }
        else
        {
            printf("offset: %d, name: %s, consumer: %s. Flags:\t[%s]\t[%s]\t[%s]\t[%s]\t[%s]\n",
                   i,
                   line_info.name,
                   line_info.consumer,
                   (line_info.flags & GPIOLINE_FLAG_IS_OUT) ? "OUTPUT" : "INPUT",
                   (line_info.flags & GPIOLINE_FLAG_ACTIVE_LOW) ? "ACTIVE_LOW" : "ACTIVE_HIGHT",
                   (line_info.flags & GPIOLINE_FLAG_OPEN_DRAIN) ? "OPEN_DRAIN" : "...",
                   (line_info.flags & GPIOLINE_FLAG_OPEN_SOURCE) ? "OPENSOURCE" : "...",
                   (line_info.flags & GPIOLINE_FLAG_KERNEL) ? "KERNEL" : "");
        }
    }
    close(fd);
}

 void gpio_write(const char *dev_name, int offset, uint8_t value)
{
    struct gpiohandle_request rq;
    struct gpiohandle_data data;
    int fd, ret;
    //printf("Write value %%d to GPIO at offset %%d (OUTPUT mode) on chip %%s\n", value, offset, dev_name);
    fd = open(dev_name, O_RDONLY);
    if (fd < 0)
    {
        printf("Unabled to open %%s: %%s", dev_name, strerror(errno));
        return;
    }
    rq.lineoffsets[0] = offset;
    rq.flags = GPIOHANDLE_REQUEST_OUTPUT;
    rq.lines = 1;
    ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &rq);
    close(fd);
    if (ret == -1)
    {
        printf("Unable to line handle from ioctl : %%s", strerror(errno));
        return;
    }
    data.values[0] = value;
    ret = ioctl(rq.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    if (ret == -1)
    {
        printf("Unable to set line value using ioctl : %%s", strerror(errno));
    }
    else
    {
         usleep(100000);
    }
    close(rq.fd);
}

 void gpio_read(const char *dev_name, int offset)
{
    struct gpiohandle_request rq;
    struct gpiohandle_data data;
    int fd, ret;
    fd = open(dev_name, O_RDONLY);
    if (fd < 0)
    {
        printf("Unabled to open %%s: %%s", dev_name, strerror(errno));
        return;
    }
    rq.lineoffsets[0] = offset;
    rq.flags = GPIOHANDLE_REQUEST_INPUT;
    rq.lines = 1;
    ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &rq);
    close(fd);
    if (ret == -1)
    {
        printf("Unable to get line handle from ioctl : %%s", strerror(errno));
        return;
    }
    ret = ioctl(rq.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
    if (ret == -1)
    {
        printf("Unable to get line value using ioctl : %%s", strerror(errno));
    }
    else
    {
        printf("Value of GPIO at offset %%d (INPUT mode) on chip %%s: %%d\n", offset, dev_name, data.values[0]);
    }
    close(rq.fd);

}

 void gpio_poll(const char *dev_name, int offset)
{
    struct gpioevent_request rq;
    struct pollfd pfd;
    int fd, ret;
    fd = open(dev_name, O_RDONLY);
    if (fd < 0)
    {
        printf("Unabled to open %%s: %%s", dev_name, strerror(errno));
        return;
    }
    rq.lineoffset = offset;
    rq.eventflags = GPIOEVENT_EVENT_RISING_EDGE;
    ret = ioctl(fd, GPIO_GET_LINEEVENT_IOCTL, &rq);
    close(fd);
    if (ret == -1)
    {
        printf("Unable to get line event from ioctl : %%s", strerror(errno));
        close(fd);
        return;
    }
    pfd.fd = rq.fd;
    pfd.events = POLLIN;
    ret = poll(&pfd, 1, -1);
    if (ret == -1)
    {
        printf("Error while polling event from GPIO: %%s", strerror(errno));
    }
    else if (pfd.revents & POLLIN)
    {
        printf("Rising edge event on GPIO offset: %%d, of %%s\n", offset, dev_name);
    }
    close(rq.fd);
}

 void help(const char *app)
{
    fprintf(stderr,
            "Usage: %%s options dev_name.\n"
            "Options:\n"
            "\t -i: print gpio chip info\n"
            "\t -r <offset>: Read GPIO value at offset (INPUT mode)\n"
            "\t -w <offset>: Write GPIO value at offset (OUTPUT mode). Option -v should be set\n"
            "\t -v <0|1>: value that should be written to the GPIO, used only with option -w\n"
            "\t -p <offset>: Polling raising event on the GPIO at offset\n",
            app);
}
