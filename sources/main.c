//=============================================================================
/*!
* Eric Hall
* All rights reserved
*
* @brief        Home Supervisory Control Embedded Linux
* @file         main.c
* @author       Eric Hall
* @date         05/01/2016
* @details      This module implements a Home Supervisory Control Embedded
*               Linux.
*
*/
//=============================================================================

/******************************************************************************
* Includes
*****************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdbool.h>
#include <stdint.h>

#include "serial.h"

#include "ldr.h"
#include "pir.h"
#include "w1.h"
#include "ir_emitter.h"
#include "led.h"

/******************************************************************************
* Definitions
*****************************************************************************/
#define HEADER_LEN		2
#define CMD_LEN         1

#define PIR_RESP_LEN    1
#define LDR_RESP_LEN    2
#define TEMP_RESP_LEN   4

// Protol:
//Byte 0: Command
//Byte 1: Payload Length
//Byte 2 .. 255: Payload

/******************************************************************************
* Enumerations
*****************************************************************************/
typedef enum E_MODULE
{
    E_MODULE_MOVEMENT = 0x00,
    E_MODULE_LIGHT,
    E_MODULE_TEMP,
    E_MODULE_LED,
    E_MODULE_IR_EMITTER,
} E_MODULE_t;

/******************************************************************************
* Structures
*****************************************************************************/

/******************************************************************************
* Prototypes
*****************************************************************************/
void smrle_stateMachine(uint8_t* puc_msg);

/******************************************************************************
* Global Variables
*****************************************************************************/
uint8_t guc_byte;
uint8_t gauc_msgBuffer[4];
uint8_t guc_msgIndex = 0;
bool gb_blockReceive = false;

/******************************************************************************
* Private Functions
*****************************************************************************/
int main(int argc, char** argv)
{

    serial_setup();

    while (true)
    {
        if (serial_read(&guc_byte))
        {
#if 1
            if ('\n' == guc_byte)
            {
                guc_msgIndex = 0;
            }
#endif
            else
            {
                gauc_msgBuffer[guc_msgIndex++] = (uint8_t) guc_byte;

            }

            if (HEADER_LEN <= guc_msgIndex)
            {
                if (!gauc_msgBuffer[1])
                {
                    smrle_stateMachine(gauc_msgBuffer);
                    guc_msgIndex = 0;

                }
                else
                {
                    if (guc_msgIndex == (gauc_msgBuffer[1] + HEADER_LEN))
                    {
                        smrle_stateMachine(gauc_msgBuffer);
                        guc_msgIndex = 0;
                    }
                }
            }

#if 0
            if (!gb_blockReceive)
            {

            }
            else
            {
                if (0 == guc_msgIndex--)
                {
                    gb_blockReceive = false;
                    guc_msgIndex = 0;
                }
            }
#endif
        }
    }

    serial_close();

    return EXIT_SUCCESS;
}

void smrle_stateMachine(uint8_t* puc_msg)
{
    uint8_t auc_msgResp[255];
    uint16_t ui_ldr;
    uint32_t ul_temp;

    auc_msgResp[0] = puc_msg[0];

    uint8_t uc_len = HEADER_LEN;

    switch (puc_msg[0])
    {
        case E_MODULE_MOVEMENT:

            auc_msgResp[1] = PIR_RESP_LEN;
            auc_msgResp[2] = pir_getState();

            uc_len += PIR_RESP_LEN;

            serial_write(auc_msgResp, uc_len);
        break;

        case E_MODULE_LIGHT:
            ui_ldr = ldr_getVoltage();

            auc_msgResp[1] = LDR_RESP_LEN;
            auc_msgResp[2] = (ui_ldr >> 8);
            auc_msgResp[3] = (ui_ldr & 0xFF);

            uc_len += LDR_RESP_LEN;

            serial_write(auc_msgResp, uc_len);

        break;

        case E_MODULE_TEMP:

            ul_temp = w1_getTemperatue();

            auc_msgResp[1] = TEMP_RESP_LEN;
            auc_msgResp[2] = (ul_temp >> 24) & 0xFF;
            auc_msgResp[3] = (ul_temp >> 16) & 0xFF;
            auc_msgResp[4] = (ul_temp >> 8) & 0xFF;
            auc_msgResp[5] = ul_temp & 0xFF;

            uc_len += TEMP_RESP_LEN;

            serial_write(auc_msgResp, uc_len);
        break;

        case E_MODULE_LED:
            led_toogle(puc_msg[2]);
        break;

        case E_MODULE_IR_EMITTER:
            ir_turnAlarm(puc_msg[2]);
        break;

        default:
        break;
    }



}

