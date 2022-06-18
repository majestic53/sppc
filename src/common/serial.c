/*
 * SPPC
 * Copyright (C) 2022 David Jolly
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <common.h>

typedef struct {
    uint32_t baud;
    speed_t speed;
} sppc_baud_map_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static sppc_error_e sppc_serial_baud_map(uint32_t baud, speed_t *speed)
{
    size_t index;
    sppc_error_e result = SPPC_SUCCESS;
    const sppc_baud_map_t map[] = {
        { 9600, B9600 },
        { 115200, B115200 },
        };

    for(index = 0; index < sizeof(map) / sizeof(*map); ++index) {

        if(baud == map[index].baud) {
            *speed = map[index].speed;
            break;
        }
    }

    if(index == sizeof(map) / sizeof(*map)) {
        result = SPPC_ERROR("Unsupported serial baud rate -- %u", baud);
        goto exit;
    }

exit:
    return result;
}

void sppc_serial_close(sppc_serial_t *serial)
{

    if(serial->port) {
        close(serial->port);
    }

    memset(serial, 0, sizeof(*serial));
}

sppc_error_e sppc_serial_open(sppc_serial_t *serial, const char *device, uint32_t baud)
{
    sppc_error_e result;
    speed_t speed = B9600;
    struct termios terminal = {};

    if((result = sppc_serial_baud_map(baud, &speed)) != SPPC_SUCCESS) {
        goto exit;
    }

    if((serial->port = open(device, O_WRONLY | O_NOCTTY)) < 0) {
        result = SPPC_ERROR("Failed to open device -- %s", device);
        goto exit;
    }

    if(fcntl(serial->port, F_SETFL, O_SYNC) == -1) {
        result = SPPC_ERROR("Failed to setup device -- %s", device);
        goto exit;
    }

    if(tcgetattr(serial->port, &terminal)) {
        result = SPPC_ERROR("Failed to get terminal parameters -- %s", device);
        goto exit;
    }

    if(cfgetispeed(&terminal) != speed) {

        if(cfsetispeed(&terminal, speed)) {
            result = SPPC_ERROR("Failed to set terminal input speed -- %s", device);
            goto exit;
        }
    }

    if(cfgetospeed(&terminal) != speed) {

        if(cfsetospeed(&terminal, speed)) {
            result = SPPC_ERROR("Failed to set terminal output speed -- %s", device);
            goto exit;
        }
    }

    terminal.c_oflag |= (ONLCR | CREAD | CS8);
    terminal.c_cflag &= ~(CSIZE | CSTOPB | CRTSCTS | PARENB);

    if(tcsetattr(serial->port, TCSANOW, &terminal)) {
        result = SPPC_ERROR("Failed to set terminal parameters -- %s", device);
        goto exit;
    }

    if(tcflush(serial->port, TCOFLUSH)) {
        result = SPPC_ERROR("Failed to flush terminal -- %s", device);
        goto exit;
    }

exit:
    return result;
}

sppc_error_e sppc_serial_read(sppc_serial_t *serial, sppc_buffer_t *buffer)
{
    fd_set input;
    sppc_error_e result = SPPC_SUCCESS;

    FD_ZERO(&input);
    FD_SET(serial->port, &input);

    for(;;) {

        if(select(serial->port + 1, &input, NULL, NULL, NULL) < 0) {
            result = SPPC_ERROR("Select failed -- %u", errno);
            goto exit;
        }

        if(FD_ISSET(serial->port, &input)) {
            int length = 0;

            if(ioctl(serial->port, FIONREAD, &length) == -1) {
                result = SPPC_ERROR("Ioctl failed -- %u", errno);
                goto exit;
            }

            if(length > 0) {

                /* TODO */

            }
        }
    }

exit:
    return result;
}

sppc_error_e sppc_serial_write(sppc_serial_t *serial, const sppc_buffer_t *buffer)
{
    uint8_t terminator = SPPC_EOF;
    sppc_error_e result = SPPC_SUCCESS;

    if(write(serial->port, buffer->data, buffer->length) != buffer->length) {
        result = SPPC_ERROR("Failed to write to port -- %i", serial->port);
        goto exit;
    }

    if(write(serial->port, &terminator, 1) != 1) {
        result = SPPC_ERROR("Failed to write to port -- %i", serial->port);
        goto exit;
    }

exit:
    return result;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
