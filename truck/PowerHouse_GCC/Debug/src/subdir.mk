################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/app.c \
../src/bat.c \
../src/interrupt.c \
../src/intgnd.c \
../src/led.c \
../src/main.c \
../src/version.c 

OBJS += \
./src/app.o \
./src/bat.o \
./src/interrupt.o \
./src/intgnd.o \
./src/led.o \
./src/main.o \
./src/version.o 

C_DEPS += \
./src/app.d \
./src/bat.d \
./src/interrupt.d \
./src/intgnd.d \
./src/led.d \
./src/main.d \
./src/version.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -I"../system/include/cmsis" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


