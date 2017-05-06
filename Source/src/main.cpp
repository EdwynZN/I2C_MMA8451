/*
 * main.cpp
 *
 *  Created on: 10/04/2017
 *      Author: dartz
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../Project_Headers/HIL/I2C_MMA8451.h"
#include "../Project_Headers/HIL/TWI_Manager.h"
#include "../Project_Headers/HAL/Port.h"

int main(void){
		unsigned int time_delay = 500, LEDX, LEDY, LEDZ;
		TWI_Init();
		I2C_Init();
		GPIO_SET(C,_BV(PINC5)|_BV(PINC4));
		//DDRB = _BV(PINB3) | _BV(PINB4) | _BV(PINB5); //Pin B5 Salida

		while(1){
			Read_Register(OUT_X_MSB);
			x_g = (I2C_Receive_Byte_ACK() << 6) + (I2C_Receive_Byte_ACK() >> 2);
			y_g = (I2C_Receive_Byte_ACK() << 6) + (I2C_Receive_Byte_ACK() >> 2);
			z_g = (I2C_Receive_Byte_ACK() << 6) + (I2C_Receive_Byte_NACK() >> 2);
			I2C_Stop_Com();

			LEDX = x_g > 0 ? _BV(PINB3) : 0x00;
			LEDY = y_g > 0 ? _BV(PINB4) : 0x00;
			LEDZ = z_g > 0 ? _BV(PINB5) : 0x00;
			GPIO_WRITE_PORT(B, LEDX | LEDY | LEDZ);
			//PORTB = LEDX | LEDY | LEDZ;
			_delay_ms(time_delay);
		}
}
