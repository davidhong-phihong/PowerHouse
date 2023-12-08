################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Interface/UART/UART0.c \
../Interface/UART/UART1.c \
../Interface/UART/UART2.c 

OBJS += \
./Interface/UART/UART0.o \
./Interface/UART/UART1.o \
./Interface/UART/UART2.o 

C_DEPS += \
./Interface/UART/UART0.d \
./Interface/UART/UART1.d \
./Interface/UART/UART2.d 


# Each subdirectory must supply rules for building sources it contributes
Interface/UART/%.o: ../Interface/UART/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -I"../system/include/cmsis" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


