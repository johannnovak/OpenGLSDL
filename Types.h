#ifndef __TYPES__
#define __TYPES__


#include <stdio.h>      // for NULL pointer


typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long int uint64;

typedef float float32;
typedef double float64;
typedef long double float80;


#define INT8_MIN_VALUE		-128
#define INT8_MAX_VALUE		127
#define UINT8_MAX_VALUE		255

#define INT16_MIN_VALUE		-32768
#define INT16_MAX_VALUE		32767
#define UINT16_MAX_VALUE	65535

#define INT32_MIN_VALUE		-2147483648
#define INT32_MAX_VALUE		2147483647
#define UINT32_MAX_VALUE	4294967295

#define FLOAT32_MIN_VALUE 	-3.4e+38f
#define FLOAT32_MAX_VALUE 	3.4e+38f

#define FLOAT64_MIN_VALUE 	-1.7e+308
#define FLOAT64_MAX_VALUE 	1.7e+308


#endif
