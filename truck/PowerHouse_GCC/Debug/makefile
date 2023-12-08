################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include system/src/cmsis/subdir.mk
-include src/subdir.mk
-include module/WT6673/subdir.mk
-include module/MAX17201/subdir.mk
-include module/BQ25798/subdir.mk
-include Utility/subdir.mk
-include Interface/WDT/subdir.mk
-include Interface/UART/subdir.mk
-include Interface/Systick/subdir.mk
-include Interface/I2C/subdir.mk
-include Interface/GPIO/subdir.mk
-include Interface/FLASH/subdir.mk
-include Interface/ADC/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
PowerHouse_GCC.bin \

SECONDARY_SIZE += \
PowerHouse_GCC.siz \


# All Target
all: PowerHouse_GCC.elf secondary-outputs

# Tool invocations
PowerHouse_GCC.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM Cross C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -T "C:\Sonix\Sonix_GNU_MCU_Eclipse_V1_00\workspace\PowerHouse_GCC\ldscripts\SN32F760B.ld" -Xlinker --gc-sections -L"../ldscripts" -Wl,-Map,"PowerHouse_GCC.map" --specs=nano.specs -o "PowerHouse_GCC.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

PowerHouse_GCC.bin: PowerHouse_GCC.elf
	@echo 'Invoking: GNU ARM Cross Create Flash Image'
	arm-none-eabi-objcopy -O binary "PowerHouse_GCC.elf"  "PowerHouse_GCC.bin"
	@echo 'Finished building: $@'
	@echo ' '

PowerHouse_GCC.siz: PowerHouse_GCC.elf
	@echo 'Invoking: GNU ARM Cross Print Size'
	arm-none-eabi-size --format=berkeley "PowerHouse_GCC.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) PowerHouse_GCC.elf
	-@echo ' '

post-build:
	-HexConvert.exe SN32F760B "PowerHouse_GCC.hex" & srec_cat PowerHouse_GCC.hex -intel -output PowerHouse_GCC.hex -Intel -line-length=44 & arm-none-eabi-objcopy -O ihex PowerHouse_GCC.elf PowerHouse_GCC.hex
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents post-build

-include ../makefile.targets
