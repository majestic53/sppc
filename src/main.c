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
 * @file main.c
 * @brief Application.
 */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sppc.h>

static const struct option OPTION[] = {
    { "baud", required_argument, NULL, 'b' },
    { "device", required_argument, NULL, 'd' },
    { "help", no_argument, NULL, 'h' },
    { "read", no_argument, NULL, 'r' },
    { "version", no_argument, NULL, 'v' },
    { NULL, 0, NULL, 0 },
    };

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Show help information.
 * @param[in] base Constant pointer to base path
 */
static void show_help(const char *base)
{
    size_t flag = 0;

    fprintf(stdout, "Usage: %s [options] file...\n\n", base);
    fprintf(stdout, "Options:\n");

    while(OPTION[flag].name) {
        char message[22] = {};
        const char *description[] = {
            "Specify baud rate", "Specify device", "Show help information", "Specify read mode", "Show version information",
            };

        snprintf(message, sizeof(message), "   -%c, --%s", OPTION[flag].val, OPTION[flag].name);

        for(size_t index = strlen(message); index < sizeof(message); ++index) {
            message[index] = ' ';
        }

        fprintf(stdout, "%s%s\n", message, description[flag]);
        ++flag;
    }
}

/*!
 * @brief Show version information.
 */
static void show_version(void)
{
    const sppc_version_t *version = sppc_version();

    fprintf(stdout, "%u.%u-%X\n", version->major, version->minor, version->patch);
}

int main(int argc, char *argv[])
{
    int option, option_index;
    sppc_t context = {};
    sppc_error_e result = SPPC_SUCCESS;

    opterr = 1;

    while((option = getopt_long(argc, argv, "b:d:hrv", OPTION, &option_index)) != -1) {

        switch(option) {
            case 'b':

                if(context.baud) {
                    fprintf(stderr, "%s: Redefined baud rate -- %s\n", argv[0], optarg);
                    goto exit;
                }

                if(!(context.baud = strtol(optarg, NULL, 10))) {
                    fprintf(stderr, "%s: Invalid baud rate -- %u\n", argv[0], context.baud);
                    goto exit;
                }
                break;
            case 'd':

                if(context.device) {
                    fprintf(stderr, "%s: Redefined device -- %s\n", argv[0], optarg);
                    goto exit;
                }

                context.device = optarg;
                break;
            case 'h':
                show_help(argv[0]);
                goto exit;
            case 'r':
                context.read = true;
                break;
            case 'v':
                show_version();
                goto exit;
            case '?':
            default:
                result = SPPC_FAILURE;
                goto exit;
        }
    }

    for(option = optind; option < argc; ++option) {

        if(context.file) {
            fprintf(stderr, "%s: Redefined file path -- %s\n", argv[0], argv[option]);
            goto exit;
        }

        context.file = argv[option];
    }

    if(!context.file) {
        fprintf(stderr, "%s: Undefined file path\n", argv[0]);
        goto exit;
    }

    if((result = sppc(&context)) == SPPC_FAILURE) {
        fprintf(stderr, "%s: %s\n", argv[0], sppc_error());
        goto exit;
    }

exit:
    return result;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
