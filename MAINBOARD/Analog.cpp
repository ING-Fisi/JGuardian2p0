/*
 * Analog.cpp
 *
 *  Created on: Oct 18, 2023
 *      Author: cristian
 */


#include "Analog.h"

int read_ADvalue_row_ch0(char * device_name, int *value){
    int count,ret,fd,tmp;
    char buf[20];
    char filename[80];
    sprintf(filename,"/sys/bus/iio/devices/iio:device0/%s",device_name);

    memset(buf,0,sizeof(buf));

    fd =open(filename,O_RDONLY);
    count = read(fd, buf, sizeof(buf));
    close(fd);
    if(count > 0 ){
         sscanf( buf, "%d", value );
         tmp = tmp & 0x0FFF;
         return 1;
    }else{
         printf("get AD error\n");
         return -1;
    }

}


int read_ADvalue_row_ch1(char * device_name, int *value){
    int count,ret,fd,tmp;
    char buf[20];
    char filename[80];
    sprintf(filename,"/sys/bus/iio/devices/iio:device1/%s",device_name);

    memset(buf,0,sizeof(buf));

    fd =open(filename,O_RDONLY);
    count = read(fd, buf, sizeof(buf));
    close(fd);
    if(count > 0 ){
         sscanf( buf, "%d", value );
         tmp = tmp & 0x0FFF;
         return 1;
    }else{
         printf("get AD error\n");
         return -1;
    }

}

int read_ADvalue_ch0(char * device_name, float *value){
    int count,ret,fd,tmp;
    char buf[20];
    char filename[80];
    sprintf(filename,"/sys/bus/iio/devices/iio:device0/%s",device_name);

    memset(buf,0,sizeof(buf));

    fd =open(filename,O_RDONLY);
    count = read(fd, buf, sizeof(buf));
    close(fd);
    if(count > 0 ){
         sscanf( buf, "%d", &tmp );
         tmp = tmp & 0x0FFF;
         //printf("AD  : %s \n", buf);
         //*value = ((float)tmp/4096.0)*1.8;
         *value = ((float)tmp/4096.0)*3.3;
         return 1;
    }else{
         printf("get AD error\n");
         return -1;
    }

}


int read_ADvalue_ch1(char * device_name, float *value){
    int count,ret,fd,tmp;
    char buf[20];
    char filename[80];
    sprintf(filename,"/sys/bus/iio/devices/iio:device1/%s",device_name);

    memset(buf,0,sizeof(buf));

    fd =open(filename,O_RDONLY);
    count = read(fd, buf, sizeof(buf));
    close(fd);
    if(count > 0 ){
         sscanf( buf, "%d", &tmp );
         tmp = tmp & 0x0FFF;
         //printf("AD  : %s \n", buf);
         //*value = ((float)tmp/4096.0)*1.8;
         *value = ((float)tmp/4096.0)*3.3;
         return 1;
    }else{
         printf("get AD error\n");
         return -1;
    }

}
