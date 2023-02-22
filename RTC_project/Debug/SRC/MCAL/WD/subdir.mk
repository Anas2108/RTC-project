################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SRC/MCAL/WD/WD.c 

OBJS += \
./SRC/MCAL/WD/WD.o 

C_DEPS += \
./SRC/MCAL/WD/WD.d 


# Each subdirectory must supply rules for building sources it contributes
SRC/MCAL/WD/%.o: ../SRC/MCAL/WD/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


