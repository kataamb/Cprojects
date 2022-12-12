#ifndef _RETURN_CODES_H_
#define _RETURN_CODES_H_


enum return_codes
{
    OK = 0,
    ALLOC_ERROR = -1,
    INCORRECT_INDEX = -2,
    NAN_INPUT = -3,
    DIFFERENT_SIZES = -4,
    INCORRECT_SIZE_FORM = -5,
    INCORRECT_SIZE_VALUES = -6,
    NOT_CREATED = -7,
    UNKNOWN_COMMAND = -8,
    INIT_D_ARR_ERROR = -9,
    READ_ERROR = -10
};


#endif