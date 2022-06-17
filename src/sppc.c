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

static sppc_error_e sppc_read(const sppc_t *context)
{
    sppc_error_e result;
    sppc_buffer_t buffer = {};
    sppc_serial_t serial = {};

    if((result = sppc_serial_open(&serial, context->device, context->baud)) != SPPC_SUCCESS) {
        goto exit;
    }

    if((result = sppc_serial_read(&serial, &buffer)) != SPPC_SUCCESS) {
        goto exit;
    }

    fprintf(stdout, "Read %.02f KB (%lu bytes)\n", buffer.length / 1024.f, buffer.length);

    if((result = sppc_file_write(&buffer, context->file)) != SPPC_SUCCESS) {
        goto exit;
    }

exit:
    sppc_serial_close(&serial);
    sppc_buffer_free(&buffer);

    return result;
}

static sppc_error_e sppc_write(const sppc_t *context)
{
    sppc_error_e result;
    sppc_buffer_t buffer = {};
    sppc_serial_t serial = {};

    if((result = sppc_file_read(&buffer, context->file)) != SPPC_SUCCESS) {
        goto exit;
    }

    if((result = sppc_serial_open(&serial, context->device, context->baud)) != SPPC_SUCCESS) {
        goto exit;
    }

    fprintf(stdout, "Writing %.02f KB (%lu bytes)\n", buffer.length / 1024.f, buffer.length);

    if((result = sppc_serial_write(&serial, &buffer)) != SPPC_SUCCESS) {
        goto exit;
    }

exit:
    sppc_serial_close(&serial);
    sppc_buffer_free(&buffer);

    return result;
}

sppc_error_e sppc(const sppc_t *context)
{
    sppc_error_e result = SPPC_SUCCESS;

    fprintf(stdout, "File   -- %s\n", context->file);
    fprintf(stdout, "Device -- %s\n", context->device);
    fprintf(stdout, "Baud   -- %u\n\n", context->baud);

    if(context->read) {

        if((result = sppc_read(context)) != SPPC_SUCCESS) {
            goto exit;
        }
    } else if((result = sppc_write(context)) != SPPC_SUCCESS) {
        goto exit;
    }

    fprintf(stdout, "Done.\n");

exit:
    return result;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
