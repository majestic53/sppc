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
 * @file buffer.c
 * @brief Common buffer.
 */

#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

sppc_error_e sppc_buffer_allocate(sppc_buffer_t *buffer, size_t capacity)
{
    sppc_error_e result = SPPC_SUCCESS;

    if(!(buffer->data = calloc(capacity, sizeof(uint8_t)))) {
        result = SPPC_ERROR("Failed to allocate buffer -- %.02f KB (%u bytes)", capacity / 1024.f, capacity);
        goto exit;
    }

    buffer->capacity = capacity;
    buffer->length = 0;

exit:
    return result;
}

void sppc_buffer_free(sppc_buffer_t *buffer)
{
    free(buffer->data);
    memset(buffer, 0, sizeof(*buffer));
}

sppc_error_e sppc_buffer_reallocate(sppc_buffer_t *buffer, size_t capacity)
{
    sppc_error_e result = SPPC_SUCCESS;

    if(!(buffer->data = realloc(buffer->data, capacity))) {
        result = SPPC_ERROR("Failed to reallocate buffer -- %.02f KB (%u bytes)", capacity / 1024.f, capacity);
        goto exit;
    }

    buffer->capacity = capacity;

exit:
    return result;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
