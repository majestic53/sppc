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
 * @file file.h
 * @brief Common file.
 */

#ifndef SPPC_FILE_H_
#define SPPC_FILE_H_

#include <buffer.h>

/*!
 * @struct sppc_file_t
 * @brief File context
 */
typedef struct {
    FILE *position; /*!< File byte position */
} sppc_file_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Close file.
 * @param[in,out] file Pointer to file context
 */
void sppc_file_close(sppc_file_t *file);

/*!
 * @brief Open file.
 * @param[in,out] file Pointer to file context
 * @param[in] path Constant pointer to file path
 * @param[in] mode Constant pointer to file mode
 * @return SPPC_SUCCESS on success, SPPC_FAILURE otherwise
 */
sppc_error_e sppc_file_open(sppc_file_t *file, const char *path, const char *mode);

/*!
 * @brief Read buffer from file.
 * @param[in,out] buffer Pointer to buffer context
 * @param[in] path Constant pointer to file path
 * @return SPPC_SUCCESS on success, SPPC_FAILURE otherwise
 */
sppc_error_e sppc_file_read(sppc_buffer_t *buffer, const char *path);

/*!
 * @brief Write buffer to file.
 * @param[in] buffer Constant pointer to buffer context
 * @param[in] path Constant pointer to file path
 * @return SPPC_SUCCESS on success, SPPC_FAILURE otherwise
 */
sppc_error_e sppc_file_write(const sppc_buffer_t *buffer, const char *path);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SPPC_FILE_H_ */
