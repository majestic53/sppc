`SPPC` allows for reading and writing files between a PC and a Sharp pocket-PC (PCG8XX or similar), over USB to 11-pin serial.

### File layout

Source files can be found under the following directories:

|Directory          |Description             |
|:------------------|:-----------------------|
|`src/common`       |Common source files     |
|`src/`             |Application source files|

### Coding style

The source code generally conforms to the following coding standard:

#### Enumerations

    /*!
     * @enum sppc_xxx_e
     * @brief ...
     */
    typedef enum {
        XXX_A = 0,          /*!< Doxygen comment */
        XXX_B,              /*!< Doxygen comment */
        ...
    } sppc_xxx_e;

#### Structures

    /*!
     * @struct sppc_xxx_t
     * @brief ...
     */
    typedef struct {
        sppc_xxx_e val_0;   /*!< Doxygen comment */
        int val_1;          /*!< Doxygen comment */
        ...
    } sppc_xxx_t;

#### Functions

    #ifdef __cplusplus
    extern "C" {
    #endif /* __cplusplus */

    ...

    /*!
     * @brief ...
     * @param[in,out] arg_0 ...
     * @param[in] arg_1 ...
     * @return ...
     */
    int sppc_xxx_yyy(sppc_xxx_t *arg_0, sppc_xxx_e arg_1, ...)
    {
        int result = SPPC_SUCCESS;

        if(arg_0 == NULL) {
            result = SPPC_FAILURE;
            goto exit;
        }

        ...

    exit:
        return result;
    }

    ...

    #ifdef __cplusplus
    }
    #endif /* __cplusplus */
