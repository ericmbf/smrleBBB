/*
 * pir.c
 *
 *  Created on: 14 de abr de 2016
 *      Author: eric
 */

#include "ir_emitter.h"
#include <stdio.h>

#define ALARM_TURN_ON   "for i in {1..3}; do irsend SEND_ONCE Samsung_BN59-00940A KEY_POWER; done"

#define ALARM_TURN_OFF  "for i in {1..3}; do irsend SEND_ONCE Samsung_BN59-00940A KEY_MUTE; done"

void ir_turnAlarm(bool b_state)
{
    FILE *fp;

    if (b_state)
    {
        //Open the command for reading.
        fp = popen(ALARM_TURN_ON, "r");
        if (fp == NULL)
        {
            printf("Failed to run command\n");
        }
        pclose(fp);
    }

    else
    {
        //Open the command for reading.
        fp = popen(ALARM_TURN_OFF, "r");
        if (fp == NULL)
        {
            printf("Failed to run command\n");
        }
        pclose(fp);
    }

}
