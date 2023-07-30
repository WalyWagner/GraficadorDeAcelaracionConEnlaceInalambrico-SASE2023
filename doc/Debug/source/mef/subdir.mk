################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/mef/mef_DeteccionTrama.c \
../source/mef/mef_Modo.c \
../source/mef/mef_Plot3D.c \
../source/mef/procPeticion.c 

C_DEPS += \
./source/mef/mef_DeteccionTrama.d \
./source/mef/mef_Modo.d \
./source/mef/mef_Plot3D.d \
./source/mef/procPeticion.d 

OBJS += \
./source/mef/mef_DeteccionTrama.o \
./source/mef/mef_Modo.o \
./source/mef/mef_Plot3D.o \
./source/mef/procPeticion.o 


# Each subdirectory must supply rules for building sources it contributes
source/mef/%.o: ../source/mef/%.c source/mef/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL46Z256VLH4_cm0plus -DCPU_MKL46Z256VLH4 -DCPU_MKL46Z256VLL4 -DFRDM_KL46Z -DFREEDOM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../source -I../ -I../drivers -I../CMSIS -I../startup -I../utilities -I../board/src -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-mef

clean-source-2f-mef:
	-$(RM) ./source/mef/mef_DeteccionTrama.d ./source/mef/mef_DeteccionTrama.o ./source/mef/mef_Modo.d ./source/mef/mef_Modo.o ./source/mef/mef_Plot3D.d ./source/mef/mef_Plot3D.o ./source/mef/procPeticion.d ./source/mef/procPeticion.o

.PHONY: clean-source-2f-mef

