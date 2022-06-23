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
 * @file buffer.h
 * @brief Common buffer.
 */

#ifndef SPPC_BUFFER_H_
#define SPPC_BUFFER_H_

#include <define.h>

/*!
 * @struct sppc_buffer_t
 * @brief Buffer context
 */
typedef struct {
    uint8_t *data;      /*!< Pointer to buffer data */
    size_t capacity;    /*!< Buffer capacity, in bytes */
    size_t length;      /*!< Buffer length, in bytes */
} sppc_buffer_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Allocate buffer.
 * @param[in,out] buffer Pointer to buffer context
 * @param[in] length Buffer length, in bytes
 * @return SPPC_SUCCESS on success, SPPC_FAILURE otherwise
 */
sppc_error_e sppc_buffer_allocate(sppc_buffer_t *buffer, size_t length);

/*!
 * @brief Free buffer.
 * @param[in,out] buffer Pointer to buffer context
 */
void sppc_buffer_free(sppc_buffer_t *buffer);

/*!
 * @brief Reallocate buffer.
 * @param[in,out] buffer Pointer to buffer context
 * @param[in] length Buffer length, in bytes
 * @return SPPC_SUCCESS on success, SPPC_FAILURE otherwise
 */
sppc_error_e sppc_buffer_reallocate(sppc_buffer_t *buffer, size_t length);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SPPC_BUFFER_H_ */
