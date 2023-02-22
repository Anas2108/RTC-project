################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SRC/HAL/LED/Led.c \
../SRC/HAL/LED/Led_cfg.c 

OBJS += \
./SRC/HAL/LED/Led.o \
./SRC/HAL/LED/Led_cfg.o 

C_DEPS += \
./SRC/HAL/LED/Led.d \
./SRC/HAL/LED/Led_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
SRC/HAL/LED/%.o: ../SRC/HAL/LED/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


