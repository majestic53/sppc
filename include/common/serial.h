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

#ifndef SPPC_SERIAL_H_
#define SPPC_SERIAL_H_

#include <define.h>

typedef uint8_t (*sppc_write_cb)(size_t, size_t, uint8_t);

typedef struct {
    sppc_write_cb callback;
    int port;
} sppc_serial_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void sppc_serial_close(sppc_serial_t *serial);

sppc_error_e sppc_serial_open(sppc_serial_t *serial, sppc_write_cb callback, const char *device, uint32_t baud);

sppc_error_e sppc_serial_write(sppc_serial_t *serial, sppc_buffer_t *buffer);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SPPC_SERIAL_H_ */
