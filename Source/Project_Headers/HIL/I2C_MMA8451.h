/*
 * I2C_MMA8451.h
 *
 *  Created on: 09/04/2017
 *      Author: dartz
 */

#ifndef I2C_MMA8451_H_
#define I2C_MMA8451_H_

/*********************						Defines							**********************/
/*************************************************************************************************/
#define ACTIVE_MASK					(0x01)	  // MASK for Active MMA8451Q

#define F_STATUS					(0x00)	  // Register STATUS/F_STATUS
#define OUT_X_MSB					(0x01)	  // Register X_MSB
#define OUT_X_LSB					(0x02)	  // Register X_LSB
#define OUT_Y_MSB					(0x03)	  // Register Y_MSB
#define OUT_Y_LSB					(0x04)	  // Register Y_LSB
#define OUT_Z_MSB					(0x05)	  // Register Z_MSB
#define OUT_Z_LSB					(0x06)	  // Register Z_LSB
#define F_SETUP						(0x09)	  // Register FIFO SETUP
#define TRIG_CFG					(0x0A)	  // Register MAP OF FIFO DATA CAPTURE EVENTS
#define SYSMOD						(0x0B)	  // Register CURRENT SYSTEM MOD
#define INT_SOURCE					(0x0C)	  // Register INTERRUPT STATUS
#define WHO_AM_I					(0x0D)	  // Register DEVICE ID (0X1A)
#define XYZ_DATA_CFG_REGISTER		(0x0E)    // Register DYNAMIC RANGE SETTINGS
#define HP_FILTER_CUTOFF			(0x0F)    // Register CUTOFF FREQUENCY IS SET TO 16HZ @ 800 HZ
#define PL_STATUS					(0x10)	  // Register LANDSCAPE/PORTRAIT ORIENTATION STATUS
#define PL_CFG						(0x11)	  // Register LANDSCAPE/PORTRAIT CONFIGURATION
#define PL_COUNT					(0x12)	  // Register LANDSCAPE/PORTRATI DEBOUNCE COUNTER
#define PL_BF_ZCOMP					(0x13)	  // Register BACK/FRONT, Z-LOCK TRIP TRESHOLD
#define P_L_THS_REG					(0x14)	  // Register PORTRAIT TO LANDSCAPE TRIP ANGLE IS 29°
#define FF_MT_CFG					(0x15)	  // Register FREFALL/MOTION FUNCTIONAL BLOCK CONFIGURATION
#define FF_MT_SRC					(0x16)	  // Register FREFALL/MOTION EVENT SOURCE REGISTER
#define FF_MT_THS					(0x17)	  // Register FREFALL/MOTION THRESHOLD
#define FF_MT_COUNT					(0x18)	  // Register FREFALL/MOTION DEBOUNCE COUNTER
#define TRANSIENT_CFG				(0x1D)	  // Register TRANSIENT FUNCTIONAL BLOCK CONFIGURATION
#define TRANSIENT_SCR				(0x1E)	  // Register TRANSIENT EVENT STATUS REGISTER
#define TRANSIENT_THS				(0x1F)	  // Register TRANSIENT EVENT THRESHOLD
#define TRANSIENT_COUNT				(0x20)	  // Register TRANSIENT DEBOUNCE COUNTER
#define PULSE_CFG					(0x21)	  // Register ELE, DOUBLE_XYZ OR SINGLE_XYZ
#define PULSE_SCR					(0x22)	  // Register EA, DOUBLE_XYZ OR SINGLE_XYZ
#define PULSE_THSX					(0x23)	  // Register X PULSE THRESHOLD
#define PULSE_THSY					(0x24)	  // Register Y PULSE THRESHOLD
#define PULSE_THSZ					(0x25)	  // Register Z PULSE THRESHOLD
#define PULSE_TMLT					(0x26)	  // Register TIME LIMIT FOR PULSE
#define PULSE_LTCY					(0x27)	  // Register LATENCY TIME FOR 2ND PULSE
#define PULSE_WIND					(0x28)	  // Register WINDOW TIME FOR 2ND PULSE
#define ASLP_COUNT					(0x29)	  // Register COUNTER SETTING FOR AUTO SLEEP
#define CTRL_REG1					(0x2A)	  // Register CTRL_REG1
#define CTRL_REG2					(0x2B)	  // Register CTRL_REG2
#define CTRL_REG3					(0x2C)	  // Register CTRL_REG3
#define CTRL_REG4					(0x2D)	  // Register CTRL_REG4
#define CTRL_REG5					(0x2E)	  // Register CTRL_REG5
#define OFF_X						(0x2F)	  // Register X-AXIS OFFSET ADJUST
#define OFF_Y						(0x30)	  // Register Y-AXIS OFFSET ADJUST
#define OFF_Z						(0x31)	  // Register Z-AXIS OFFSET ADJUST

#define MMA8451_DEFAULT_ADDRESS		(0x1D)    // if A is GND, its 0x1C, If not its 0x1D
#define G_FORCE						(0x02)    // G_Force
/*************************************************************************************************/

/*************************************************************************************************/
/*********************			 	 Functions Like Macros					**********************/
/*************************************************************************************************/
#define I2C_MMA8451_Init()				MMA8451_Standby();\
										Write_Register(XYZ_DATA_CFG_REGISTER,G_Force);\
										MMA8451_Active();\			//Work in progress

/*************************************************************************************************/
/*********************					Extern Variables					**********************/

extern unsigned char Address_Write, Address_Read, G_Force, Ctrl_Reg1;
extern signed int x_g, y_g, z_g;

/*************************************************************************************************/
/*********************					Function Prototypes					**********************/
/*************************************************************************************************/

void I2C_Init();      //función para iniciar el módulo TWI I2C AVR
void I2C_Wait();      //función de espera
void I2C_Init_Com();  //función que inicia la comunicación I2C AVR
void I2C_Stop_Com();  //función que detiene la comunicación I2C AVR

void I2C_Sent_Byte(unsigned char dato);    //función para enviar o escribir
                                       	   //datos en el esclavo
unsigned char I2C_Receive_Byte_ACK();      //función para recibir o leer datos del esclavo
                                       	   //enviando el bit ACK si se quiere leer mas datos
									   	   //después del último leído
unsigned char I2C_Receive_Byte_NACK(); 	   //función para recibir o leer datos del esclavo
                                       	   //sin enviar el bit ACK si no se quiere leer mas datos
									   	   //después del último leido

unsigned char Read_Single_Register(unsigned char Register_Adress); //Return a single register byte

void MMA8451_Standby(); //CTRL_REG1 system control 1 register to standby (0)

void MMA8451_Active();  //CTRL_REG1 system control 1 register to active (1)

void Write_Register(unsigned char Register_Adress, unsigned char Data); //Change register data

void Read_Register(unsigned char Register_Adress); //Read register data

#endif /* I2C_MMA8451_H_ */
