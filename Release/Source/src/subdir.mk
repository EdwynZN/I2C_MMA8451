################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/src/I2C_MMA8451.cpp \
../Source/src/main.cpp 

OBJS += \
./Source/src/I2C_MMA8451.o \
./Source/src/main.o 

CPP_DEPS += \
./Source/src/I2C_MMA8451.d \
./Source/src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Source/src/%.o: ../Source/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\Users\dartz\EclipseWorkspace\I2C\Source\Project_Headers" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


