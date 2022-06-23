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

/*!
 * @file serial.h
 * @brief Common serial.
 */

#ifndef SPPC_SERIAL_H_
#define SPPC_SERIAL_H_

#include <define.h>

/*!
 * @struct sppc_serial_t
 * @brief Serial context
 */
typedef struct {
    int port;   /*!< Serial port */
} sppc_serial_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Close serial.
 * @param[in,out] serial Pointer to serial context
 */
void sppc_serial_close(sppc_serial_t *serial);

/*!
 * @brief Open serial.
 * @param[in,out] serial Pointer to serial context
 * @param[in] device Constant pointer to device path
 * @param[in] baud Read/Write baud rate
 * @return SPPC_SUCCESS on success, SPPC_FAILURE otherwise
 */
sppc_error_e sppc_serial_open(sppc_serial_t *serial, const char *device, uint32_t baud);

/*!
 * @brief Read buffer from serial.
 * @param[in,out] serial Pointer to serial context
 * @param[in,out] buffer Pointer to buffer context
 * @return SPPC_SUCCESS on success, SPPC_FAILURE otherwise
 */
sppc_error_e sppc_serial_read(sppc_serial_t *serial, sppc_buffer_t *buffer);

/*!
 * @brief Write buffer to serial.
 * @param[in,out] serial Pointer to serial context
 * @param[in] buffer Constant pointer to buffer context
 * @return SPPC_SUCCESS on success, SPPC_FAILURE otherwise
 */
sppc_error_e sppc_serial_write(sppc_serial_t *serial, const sppc_buffer_t *buffer);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SPPC_SERIAL_H_ */
