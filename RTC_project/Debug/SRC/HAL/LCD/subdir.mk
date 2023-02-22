################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SRC/HAL/LCD/Lcd.c \
../SRC/HAL/LCD/Lcd_cfg.c 

OBJS += \
./SRC/HAL/LCD/Lcd.o \
./SRC/HAL/LCD/Lcd_cfg.o 

C_DEPS += \
./SRC/HAL/LCD/Lcd.d \
./SRC/HAL/LCD/Lcd_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
SRC/HAL/LCD/%.o: ../SRC/HAL/LCD/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


