################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/fsm/frameProcessor/frameProcessor.c 

C_DEPS += \
./source/fsm/frameProcessor/frameProcessor.d 

OBJS += \
./source/fsm/frameProcessor/frameProcessor.o 


# Each subdirectory must supply rules for building sources it contributes
source/fsm/frameProcessor/%.o: ../source/fsm/frameProcessor/%.c source/fsm/frameProcessor/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL46Z256VLH4_cm0plus -DCPU_MKL46Z256VLH4 -DCPU_MKL46Z256VLL4 -DFRDM_KL46Z -DFREEDOM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../source -I../ -I../drivers -I../CMSIS -I../startup -I../utilities -I../board/src -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-fsm-2f-frameProcessor

clean-source-2f-fsm-2f-frameProcessor:
	-$(RM) ./source/fsm/frameProcessor/frameProcessor.d ./source/fsm/frameProcessor/frameProcessor.o

.PHONY: clean-source-2f-fsm-2f-frameProcessor

