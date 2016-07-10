/*
 * serial.c

 *
 *  Created on: 18 de mai de 2016
 *      Author: eric
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdint.h>

#include "serial.h"

static int tty_fd;
static struct termios tio;
static struct termios stdio;
static struct termios old_stdio;

void serial_setup()
{
    tcgetattr(STDOUT_FILENO, &old_stdio);

    printf("Please start with /dev/ttyGS0 \n");
    memset(&stdio, 0, sizeof(stdio));
    stdio.c_iflag = 0;
    stdio.c_oflag = 0;
    stdio.c_cflag = 0;
    stdio.c_lflag = 0;
    stdio.c_cc[VMIN] = 1;
    stdio.c_cc[VTIME] = 0;
    tcsetattr(STDOUT_FILENO, TCSANOW, &stdio);
    tcsetattr(STDOUT_FILENO, TCSAFLUSH, &stdio);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);     // make the reads non-blocking

    memset(&tio, 0, sizeof(tio));
    tio.c_iflag = 0;
    tio.c_oflag = 0;
    tio.c_cflag = CS8 | CREAD | CLOCAL; // 8n1, see termios.h for more information
    tio.c_lflag = 0;
    tio.c_cc[VMIN] = 1;
    tio.c_cc[VTIME] = 5;

    tty_fd = open("/dev/ttyGS0", O_RDWR | O_NONBLOCK);
    cfsetospeed(&tio, B115200);            // 115200 baud
    cfsetispeed(&tio, B115200);            // 115200 baud
    tcsetattr(tty_fd, TCSANOW, &tio);
}

void serial_write(uint8_t *puc_buf, uint8_t uc_len)
{
    write(tty_fd, puc_buf, uc_len);
}

bool serial_read(uint8_t *uc_byte)
{
    bool b_ret = false;

    if (read(tty_fd, uc_byte, 1) > 0)
    {
        b_ret = true;
    }

    return b_ret;
}

void serial_close()
{
    close(tty_fd);
    tcsetattr(STDOUT_FILENO, TCSANOW, &old_stdio);
}
