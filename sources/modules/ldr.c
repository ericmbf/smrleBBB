/*
 * pir.c
 *
 *  Created on: 14 de abr de 2016
 *      Author: eric
 */

#include "ldr.h"
#include <stdio.h>

#define AIN_4_BBB_PATH  "cat /sys/bus/iio/devices/iio\\:device0/in_voltage4_raw"

uint16_t ldr_getVoltage()
{
    uint32_t ul_voltage = 0;
    uint16_t ui_retVolt = 0;

    FILE *fp;
    char response[10];

    /* Open the command for reading. */
    fp = popen(AIN_4_BBB_PATH, "r");
    if (fp == NULL)
    {
        printf("Failed to run command\n");
    }

    /* Read the output a line at a time - output it. */
    while (fgets(response, sizeof(response) - 1, fp) != NULL)
    {
        sscanf(response, "%d", &ul_voltage);
    }

    /* close */
    pclose(fp);

    ui_retVolt = (uint16_t) ul_voltage;

    return ui_retVolt;
}

