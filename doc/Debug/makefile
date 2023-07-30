################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/onBoard_KL46/subdir.mk
-include source/offBoard_KL46/Oled/subdir.mk
-include source/mef/subdir.mk
-include source/env_rec_KL46/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include board/src/subdir.mk
-include board/subdir.mk
-include CMSIS/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := SD2_UART0_ejemploTramas
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: SD2_UART0_ejemploTramas.axf

# Tool invocations
SD2_UART0_ejemploTramas.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="SD2_UART0_ejemploTramas.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -mcpu=cortex-m0plus -mthumb -T SD2_UART0_lpsci_interrupt_Debug.ld -o "SD2_UART0_ejemploTramas.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) SD2_UART0_ejemploTramas.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "SD2_UART0_ejemploTramas.axf"; # arm-none-eabi-objcopy -v -O binary "SD2_UART0_ejemploTramas.axf" "SD2_UART0_ejemploTramas.bin" ; # checksum -p MKL46Z256xxx4 -d "SD2_UART0_ejemploTramas.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
