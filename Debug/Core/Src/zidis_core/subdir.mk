################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/zidis_core/dsp.c \
../Core/Src/zidis_core/mlp.c \
../Core/Src/zidis_core/protocol.c 

OBJS += \
./Core/Src/zidis_core/dsp.o \
./Core/Src/zidis_core/mlp.o \
./Core/Src/zidis_core/protocol.o 

C_DEPS += \
./Core/Src/zidis_core/dsp.d \
./Core/Src/zidis_core/mlp.d \
./Core/Src/zidis_core/protocol.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/zidis_core/%.o Core/Src/zidis_core/%.su Core/Src/zidis_core/%.cyclo: ../Core/Src/zidis_core/%.c Core/Src/zidis_core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG '-DKNL_SYSDEP_PATH=cpu/core/armv8m' '-DTARGET_DIR=cpu/core/armv8m' -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32H533xx '-DKNL_SYSDEP_PATH=cpu/core/armv8m' -c -I../Core/Inc -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/kernel/knlinc" -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/config" -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/include" -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32H5xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-zidis_core

clean-Core-2f-Src-2f-zidis_core:
	-$(RM) ./Core/Src/zidis_core/dsp.cyclo ./Core/Src/zidis_core/dsp.d ./Core/Src/zidis_core/dsp.o ./Core/Src/zidis_core/dsp.su ./Core/Src/zidis_core/mlp.cyclo ./Core/Src/zidis_core/mlp.d ./Core/Src/zidis_core/mlp.o ./Core/Src/zidis_core/mlp.su ./Core/Src/zidis_core/protocol.cyclo ./Core/Src/zidis_core/protocol.d ./Core/Src/zidis_core/protocol.o ./Core/Src/zidis_core/protocol.su

.PHONY: clean-Core-2f-Src-2f-zidis_core

