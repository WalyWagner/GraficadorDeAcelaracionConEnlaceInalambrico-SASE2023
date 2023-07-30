################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/env_rec_KL46/ringBuffer.c \
../source/env_rec_KL46/uart_ringBufer.c 

C_DEPS += \
./source/env_rec_KL46/ringBuffer.d \
./source/env_rec_KL46/uart_ringBufer.d 

OBJS += \
./source/env_rec_KL46/ringBuffer.o \
./source/env_rec_KL46/uart_ringBufer.o 


# Each subdirectory must supply rules for building sources it contributes
source/env_rec_KL46/%.o: ../source/env_rec_KL46/%.c source/env_rec_KL46/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL46Z256VLH4_cm0plus -DCPU_MKL46Z256VLH4 -DCPU_MKL46Z256VLL4 -DFRDM_KL46Z -DFREEDOM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../source -I../ -I../drivers -I../CMSIS -I../startup -I../utilities -I../board/src -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-env_rec_KL46

clean-source-2f-env_rec_KL46:
	-$(RM) ./source/env_rec_KL46/ringBuffer.d ./source/env_rec_KL46/ringBuffer.o ./source/env_rec_KL46/uart_ringBufer.d ./source/env_rec_KL46/uart_ringBufer.o

.PHONY: clean-source-2f-env_rec_KL46

