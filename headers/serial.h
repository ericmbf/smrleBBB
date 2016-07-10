/*
 * serial.h
 *
 *  Created on: 18 de mai de 2016
 *      Author: eric
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include <stdbool.h>

void serial_setup();

void serial_write(uint8_t* puc_buf, uint8_t uc_len);

bool serial_read(uint8_t *uc_byte);

void serial_close();

#endif /* SERIAL_H_ */
