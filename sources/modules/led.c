/*
 * pir.c
 *
 *  Created on: 14 de abr de 2016
 *      Author: eric
 */

#include "led.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define LED_RED             " > /sys/class/gpio/gpio66/value\0"
#define LED_GREEN           " > /sys/class/gpio/gpio68/value\0"
#define LED_BLUE            " > /sys/class/gpio/gpio67/value\0"

#define LED_SUFIX_LEN       sizeof(LED_RED) - 1

#define PREFIX              "echo "
#define PREFIX_LEN          sizeof(PREFIX) - 1

#define TURN_ON             1
#define TURN_OFF            0

#define TEMP_LEN            5
#define TEMP_HEADER         28


void led_toogle(bool b_state)
{
    FILE *fp;
    char command[38];
    uint8_t uc_index;
    char value = 0;

    if(b_state)
    {
        value = 49;
    }
    else
    {
        value = 48;
    }

    memcpy(command, PREFIX, PREFIX_LEN);

    for (uc_index = 0; uc_index < 3; ++uc_index)
    {
        command[PREFIX_LEN] = value;

        if (uc_index == 0)
        {
            memcpy(&command[PREFIX_LEN + 1], LED_RED, LED_SUFIX_LEN);

        }

        else if (1 == uc_index)
        {
            memcpy(&command[PREFIX_LEN + 1], LED_GREEN, LED_SUFIX_LEN);
        }

        else
        {
            memcpy(&command[PREFIX_LEN + 1], LED_BLUE, LED_SUFIX_LEN);
        }

        system(command);

//        /* Open the command for reading. */
//        fp = popen(command, "r");
//        if (fp == NULL)
//        {
//            printf("Failed to run command\n");
//        }

//        /* close */
//        pclose(fp);

    }



}

