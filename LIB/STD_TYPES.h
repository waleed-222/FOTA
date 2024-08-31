/*
 * STD_types.h
 *
 *  Created on: Aug 15, 2022
 *      Author: hp
 */

#ifndef LIB_STD_TYPES_H_
#define LIB_STD_TYPES_H_
/*
 * Signed Data Types
 */
typedef unsigned char           u8;
typedef unsigned short int      u16;
typedef unsigned long int       u32;

/*
 * Unsigned Data Types
 */
typedef signed char             s8;
typedef signed short int        s16;
typedef signed long int         s32;

/*
 * Floating point Types
 */
typedef float                   f32;
typedef double                  f64;

/*
 * Address NULL
 */
#define ADDRESS_NULL ( (void *) 0x00)

typedef  u8 boolean ;

#define TRUE	((boolean)0x01)
#define FALSE	((boolean)0x00)

typedef void (*ptr_fun_IvOv_t)(void);
typedef void (*ptr_fun_IvOu16_t)(u16);



#endif /* LIB_STD_TYPES_H_ */
