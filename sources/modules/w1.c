/*
 * pir.c
 *
 *  Created on: 14 de abr de 2016
 *      Author: eric
 */

#include "w1.h"
#include <stdio.h>
#include <string.h>

#define TEMP_SENSOR_PATH    "cat /sys/bus/w1/devices/28-04146902a3ff/w1_slave"
#define TEMP_LEN            5
#define TEMP_HEADER         28

uint32_t w1_getTemperatue()
{
    uint32_t ul_temperature = 0;

    FILE *fp;
    char response[42];
    char temp[TEMP_LEN];

    uint8_t uc_msgLen = sizeof(response) - 1;

    /* Open the command for reading. */
    fp = popen(TEMP_SENSOR_PATH, "r");
    if (fp == NULL)
    {
        printf("Failed to run command\n");
    }

    /* Read the output a line at a time - output it. */
    while (fgets(response, sizeof(response) - 1, fp) != NULL)
    {
        memcpy(temp, &response[TEMP_HEADER + 1], TEMP_LEN);
        sscanf(temp, "%d", &ul_temperature);
    }

    /* close */
    pclose(fp);

    return ul_temperature;
}

