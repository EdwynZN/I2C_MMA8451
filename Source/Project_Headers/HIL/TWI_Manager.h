/*
 * TWI_Manager.h
 *
 *  Created on: 14/04/2017
 *      Author: dartz
 */

#ifndef PROJECT_HEADERS_HIL_TWI_MANAGER_H_
#define PROJECT_HEADERS_HIL_TWI_MANAGER_H_
/*************************************************************************************************/
/*********************						Includes						**********************/
/*************************************************************************************************/
#include <avr/io.h>
#include "../Project_Headers/HAL/Port.h"

/*************************************************************************************************/
/*********************						Defines							**********************/
/*************************************************************************************************/
#define Enable_TWI_Bit				  _BV(TWEN)
#define Enable_TWI_Interrupt		  !_BV(TWIE)
#define Control_TWI					  (Enable_TWI_Bit | Enable_TWI_Interrupt)
#define Prescaler_TWI				  _BV(TWPS0)		//Fosc /(16 + 2*(Prescaler TWSR)*(TWBR))
#define Bit_Rate					  _BV(1)|_BV(0);	//Fosc /(16 + 2*(Prescaler TWSR)*(TWBR))
/*************************************************************************************************/
/*********************						Typedefs						**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************			 	 Functions Like Macros					**********************/
/*************************************************************************************************/
/* DO NOT MODIFY THESE ***************************************************************************/
/*************************************************************************************************/
/*Macros to control the 2-Wire Serial Interface **************************************************/
#define TWI_Bit_Rate_Register()								TWBR = Bit_Rate
#define TWCR_Register()										TWCR = Control_TWI
#define TWCR_Clear_Flag()									TWCR = (Control_TWI)|(_BV(TWINT))
#define TWCR_Read_Flag()									(TWCR & _BV(TWINT))
#define TWCR_Enable_Acknowledge()							TWCR = (Control_TWI)|(_BV(TWINT))|(_BV(TWEA))
#define TWCR_Disable_Acknowledge()							TWCR &= ~_BV(TWEA)
#define TWCR_Read_Acknowledge()								(TWCR & _BV(TWEA))
#define TWCR_Start_Condition()								TWCR = (Control_TWI)|(_BV(TWINT))|(_BV(TWSTA))
#define TWCR_Stop_Condition()								TWCR = (Control_TWI)|(_BV(TWINT))|(_BV(TWSTO))
#define TWCR_Read_Stop_Condition()							TWCR & _BV(TWSTO)
#define TWCR_Wrtie_Collision_Flag()							TWCR & _BV(TWWC)
#define TWSR_Register_Prescaler()							TWSR = Prescaler_TWI
#define TWSR_Register_Status()								(TWSR & 0xF8)
#define TWDR_Register_Write(Data_Register)					TWDR = Data_Register
#define TWDR_Register_Read()								(TWDR)
#define TWAR_Register(Adress_Register, General_Call)		TWAR = (Adress_Register << 1) | General_Call
#define TWAMR_Register(Adress_Mask_Register)				TWAMR = (Adress_Mask_Register << 1)
/*************************************************************************************************/
#define TWI_Init() 							  	  GPIO_WRITE_PORT(C, (_BV(PC4)|_BV(PC5)));\
												  TWI_Bit_Rate_Register();\
												  TWSR_Register_Prescaler();\
												  TWCR_Register();\

/*************************************************************************************************/
/*********************					Extern Variables					**********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************                  Extern Constants                    **********************/
/*************************************************************************************************/

/*************************************************************************************************/
/*********************					Function Prototypes					**********************/
/*************************************************************************************************/

/*************************************************************************************************/

#endif /* PROJECT_HEADERS_HIL_TWI_MANAGER_H_ */
