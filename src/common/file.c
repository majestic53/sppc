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

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void sppc_file_close(sppc_file_t *file)
{

    if(file->position) {
        fclose(file->position);
    }

    memset(file, 0, sizeof(*file));
}

sppc_error_e sppc_file_open(sppc_file_t *file, const char *path, const char *mode)
{
    sppc_error_e result = SPPC_SUCCESS;

    if(!(file->position = fopen(path, mode))) {
        result = SPPC_ERROR("Failed to open file -- %s", path);
        goto exit;
    }

exit:
    return result;
}

sppc_error_e sppc_file_read(sppc_buffer_t *buffer, const char *path)
{
    int length;
    sppc_error_e result;
    sppc_file_t file = {};

    if((result = sppc_file_open(&file, path, "rb")) != SPPC_SUCCESS) {
        goto exit;
    }

    fseek(file.position, 0, SEEK_END);
    length = ftell(file.position);
    fseek(file.position, 0, SEEK_SET);

    if(length <= 0) {
        result = SPPC_ERROR("Empty file -- %s", path);
        goto exit;
    }

    if((result = sppc_buffer_allocate(buffer, length)) != SPPC_SUCCESS) {
        goto exit;
    }

    if(fread(buffer->data, sizeof(*buffer->data), buffer->length, file.position) != buffer->length) {
        result = SPPC_ERROR("Failed to read file -- %s", path);
        goto exit;
    }

exit:

    if(result != SPPC_SUCCESS) {
        sppc_buffer_free(buffer);
    }

    sppc_file_close(&file);

    return result;
}

sppc_error_e sppc_file_write(const sppc_buffer_t *buffer, const char *path)
{
    sppc_error_e result;
    sppc_file_t file = {};

    if((result = sppc_file_open(&file, path, "wb")) != SPPC_SUCCESS) {
        goto exit;
    }

    if(buffer->length) {

        if(fwrite(buffer->data, sizeof(*buffer->data), buffer->length - 1, file.position) != buffer->length - 1) {
            result = SPPC_ERROR("Failed to write file -- %s", path);
            goto exit;
        }
    }

exit:
    sppc_file_close(&file);

    return result;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
