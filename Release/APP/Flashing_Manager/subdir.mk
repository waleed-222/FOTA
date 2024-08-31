################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/Flashing_Manager/Flashing_Manger.c 

OBJS += \
./APP/Flashing_Manager/Flashing_Manger.o 

C_DEPS += \
./APP/Flashing_Manager/Flashing_Manger.d 


# Each subdirectory must supply rules for building sources it contributes
APP/Flashing_Manager/%.o: ../APP/Flashing_Manager/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=800000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


