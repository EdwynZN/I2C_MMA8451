/*
 * I2C_MMA8451.cpp
 *
 *  Created on: 09/04/2017
 *      Author: dartz
 */

#include <avr/io.h>
#include "../Project_Headers/HIL/I2C_MMA8451.h"

unsigned char Address_Write = (MMA8451_DEFAULT_ADDRESS << 1) | 0,
			  Address_Read  = (MMA8451_DEFAULT_ADDRESS << 1) | 1,
			  G_Force = (G_FORCE >> 2) & 0x03,
			  Ctrl_Reg1;
signed int x_g, y_g, z_g;

//inicializaci�n del m�dulo TWI I2C AVR en el ATMEL STUDIO en una funci�n////
//para el ATMEGA88 como maestro a 400KHz con un oscilador de 16Mhz
//Fosc /(16 + 2*(Prescarler TWSR)*(TWRB))

void I2C_Init(){
	/*PORTC |= _BV(PC4)|_BV(PC5); //activa resistencias pull up para SCL y SDA
	TWSR   = _BV(TWPS0);		  //prescaler 4 (prescaler 4^n)
	TWBR   = _BV(1)|_BV(0);   	  //velocidad 400Khz, Fosc 16Mhz, prescaler de 1
	TWCR  |= _BV(TWEN);           //m�dulo TWI iniciado*/

	MMA8451_Standby();
	Write_Register(XYZ_DATA_CFG_REGISTER,G_Force);
	MMA8451_Active();
}

////////////////////////////////////////////////////////////
// Funci�n de espera: mientras el bit7 o bit TWINT del registro
// TWCR sea 0, el IC2 AVR se esperar�
// antes de realizar alg�n trabajo


void I2C_Wait(){
	while ((TWCR & _BV(TWINT)) == 0);//espera mientras el  bit de interrupcion sea 0
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// Funci�n de inicio de la comunicaci�n I2C AVR

void I2C_Init_Com() {
	TWCR = _BV(TWINT)|_BV(TWSTA)|_BV(TWEN);//bandera de interrupci�n a 1, start, habilita I2C AVR
	I2C_Wait();       //espera mientras el bit TWINT sea 0
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// Funci�n de parada de la comunicaci�n I2C I2C

void I2C_Stop_Com() {
	TWCR = _BV(TWINT)|_BV(TWSTO)|_BV(TWEN);		//bandera de interrupci�n a 1, detener, habilita I2C AVR
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
//Funci�n de transmisi�n de datos del maestro al esclavo

void I2C_Sent_Byte(unsigned char dato) {
	TWDR = dato;
	TWCR = _BV(TWINT)|_BV(TWEN);	//para empezar a enviar el dato
	I2C_Wait();						//cuando TWINT se ponga a 1 se habr� terminado de enviar el dato
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
//Funci�n de recepci�n de datos enviados por el esclavo al maestro
//esta funci�n es para leer los datos que est�n en el esclavo
//en forma continua, esto es tras leer uno se volver� a leer otro

unsigned char I2C_Receive_Byte_ACK(){
	TWCR = _BV(TWINT)|_BV(TWEN)|_BV(TWEA); //maestro envia ack para seguir recibiendo mas datos
	I2C_Wait();
	return TWDR;
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
//Funci�n de recepci�n de datos enviados por el esclavo al maestro
//esta funci�n es para leer solo un dato desde el esclavo
//esto es tras leer uno ya no se volver� a leer otro

unsigned char I2C_Receive_Byte_NACK(){
	TWCR = _BV(TWINT)|_BV(TWEN); //maestro no envia ack para no seguir recibiendo mas datos
	I2C_Wait();
	return TWDR;
}

void Write_Register(unsigned char Register_Adress, unsigned char Data){
	I2C_Init_Com();
	I2C_Sent_Byte(Address_Write);
	I2C_Sent_Byte(Register_Adress);
	I2C_Sent_Byte(Data);
	I2C_Stop_Com();
}

void Read_Register(unsigned char Register_Adress){
	I2C_Init_Com();
	I2C_Sent_Byte(Address_Write);
	I2C_Sent_Byte(Register_Adress);
	I2C_Init_Com();
	I2C_Sent_Byte(Address_Read);
}

unsigned char Read_Single_Register(unsigned char Register_Adress){
	unsigned char Register;
	Read_Register(Register_Adress);
	Register = I2C_Receive_Byte_NACK();
	I2C_Stop_Com();
	return Register;
}

void MMA8451_Standby(){
	Ctrl_Reg1 = Read_Single_Register(CTRL_REG1) & ~ACTIVE_MASK;
	Write_Register(CTRL_REG1, Ctrl_Reg1);
}

void MMA8451_Active(){
	Ctrl_Reg1 = Read_Single_Register(CTRL_REG1) | ACTIVE_MASK;
	Write_Register(CTRL_REG1, Ctrl_Reg1);
}
