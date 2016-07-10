/*
 * pir.c
 *
 *  Created on: 14 de abr de 2016
 *      Author: eric
 */

#include "pir.h"
#include <stdio.h>

#define SENSOR_PATH     "cat /dev/pirSensor"

uint8_t pir_getState()
{
    uint8_t uc_state = 0;

    FILE *fp;
    char response[3];

    /* Open the command for reading. */
    fp = popen(SENSOR_PATH, "r");
    if (fp == NULL)
    {
        printf("Failed to run command\n");
    }

    /* Read the output a line at a time - output it. */
    while (fgets(response, sizeof(response) - 1, fp) != NULL)
    {
        uc_state = response[0] - '0';
        break;
    }

    /* close */
    pclose(fp);

    return uc_state;
}

