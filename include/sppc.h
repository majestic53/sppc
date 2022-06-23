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
 * @file sppc.h
 * @brief SPPC interface.
 */

#ifndef SPPC_H_
#define SPPC_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define SPPC_API_1 1        /*!< Interface version 1 */
#define SPPC_API SPPC_API_1 /*!< Current interface version */

/*!
 * @enum sppc_error_e
 * @brief SPPC error code.
 */
typedef enum {
    SPPC_FAILURE = -1,      /*!< Operation failed, call sppc_get_error */
    SPPC_SUCCESS,           /*!< Operation succeeded */
} sppc_error_e;

/*!
 * @struct sppc_t
 * @brief SPPC context.
 */
typedef struct {
    const char *device;     /*!< Constant pointer to device path */
    const char *file;       /*!< Constant pointer to file path */
    uint32_t baud;          /*!< Read/Write baud rate */
    bool read;              /*!< Read mode */
} sppc_t;

/*!
 * @struct sppc_version_t
 * @brief SPPC version.
 */
typedef struct {
    uint16_t major;         /*!< Major version */
    uint16_t minor;         /*!< Minor version */
    uint32_t patch;         /*!< Patch version */
} sppc_version_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Run SPPC with a caller defined SPPC context.
 * @param[in] context Constant pointer to caller defined SPPC context
 * @return SPPC_SUCCESS on success, SPPC_FAILURE otherwise
 */
sppc_error_e sppc(const sppc_t *context);

/*!
 * @brief Get SPPC error string.
 * @return Constant pointer to SPPC error string
 */
const char *sppc_error(void);

/*!
 * @brief Get SPPC version.
 * @return Constant pointer to SPPC version
 */
const sppc_version_t *sppc_version(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SPPC_H_ */
