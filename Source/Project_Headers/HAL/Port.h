/*
 * Port.h
 *
 *  Created on: 16/04/2017
 *      Author: dartz
 */

#ifndef PROJECT_HEADERS_HAL_PORT_H_
#define PROJECT_HEADERS_HAL_PORT_H_
/*************************************************************************************************/
/*********************						Includes						**********************/
/*************************************************************************************************/
#include <avr/io.h>

/*************************************************************************************************/
/*********************						Defines							**********************/
/*************************************************************************************************/
#define GPIO_DIR_IN        0   /* Used to configure the direction of the GPIO pins */
#define GPIO_DIR_OUT       1   /* Used to configure the direction of the GPIO pins */

/*************************************************************************************************/
/*********************						Typedefs						**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************			 	 Functions Like Macros					**********************/
/*************************************************************************************************/

/* DO NOT MODIFY OR USE THESE ********************************************************************/
#define GPIO_PORT(port)           				PORT##port                  /* Defines the port register name */
#define GPIO_PIN(pin)        					PIN##pin				    /* Defines the port-pin register name */
#define GPIO_DIR(dir)							DDR##dir					/* Defines the port direction register */
/*************************************************************************************************/

/* Macros to configure pin direction */
#define GPIO_CONFIG_OUT(port, pin)				GPIO_CONFIG_DIR_EXPANDED(port, pin, GPIO_DIR_OUT) /* Sets port-pin as output */
#define GPIO_CONFIG_IN(port, pin)				GPIO_CONFIG_DIR_EXPANDED(port, pin, GPIO_DIR_IN)  /* Sets port-pin as input */
#define GPIO_CONFIG_DIR_EXPANDED(port,pin,dir)  (GPIO_PIN_DD(port) = dir ? GPIO_PIN_DD(port) | _BV(pin) : GPIO_PIN_DD(port) & ~_BV(pin))

#define GPIO_CONFIG_PORT_OUT(port, startPin, size)		( GPIO_DIR(port) = (0xFF >> (8-size)  << startPin) )

/* Macros to output data */
#define GPIO_SET(port, pin)						(GPIO_PORT(port) |= _BV(pin))		/* Write a 1 to the port-pin */
#define GPIO_CLR(port, pin)						(GPIO_PORT(port) &= ~_BV(pin)) 		/* Write a 0 to the port-pin */
#define GPIO_TOGGLE_PIN(port, pin) 			    (GPIO_PIN(port) = _BV(pin))			/* Toggle port-pin */
#define GPIO_TOGGLE_PORT(port, val)    			(GPIO_PIN(port) = val)				/* Toggle port-pin */
#define GPIO_TOGGLE_ALL(port)	    			(GPIO_PIN(port) = 0xFF)				/* Toggle port-pin */
#define GPIO_WRITE_PORT(port, val)              (GPIO_PORT(port) = val)          	/* Write "val" to the port-pin */

/* Macros to input data */
#define GPIO_READ_PORT(port)					GPIO_PIN(port)	                 		  /* Reads port*/
#define GPIO_IS_SET(port, pin)					(0u != (GPIO_READ_PORT(port) & _BV(pin))) /* Test if pin is set */
#define GPIO_IS_CLR(port, pin)					(0u == (GPIO_READ_PORT(port) & _BV(pin))) /* Test if pin is cleared */

/*************************************************************************************************/
#endif /* PROJECT_HEADERS_HAL_PORT_H_ */
