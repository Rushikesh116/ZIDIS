################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mtkernal/lib/libtm/libtm.c \
../mtkernal/lib/libtm/libtm_printf.c 

OBJS += \
./mtkernal/lib/libtm/libtm.o \
./mtkernal/lib/libtm/libtm_printf.o 

C_DEPS += \
./mtkernal/lib/libtm/libtm.d \
./mtkernal/lib/libtm/libtm_printf.d 


# Each subdirectory must supply rules for building sources it contributes
mtkernal/lib/libtm/%.o mtkernal/lib/libtm/%.su mtkernal/lib/libtm/%.cyclo: ../mtkernal/lib/libtm/%.c mtkernal/lib/libtm/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG '-DKNL_SYSDEP_PATH=cpu/core/armv8m' '-DTARGET_DIR=cpu/core/armv8m' -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32H533xx '-DKNL_SYSDEP_PATH=cpu/core/armv8m' -c -I../Core/Inc -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/kernel/knlinc" -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/config" -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/include" -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32H5xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-mtkernal-2f-lib-2f-libtm

clean-mtkernal-2f-lib-2f-libtm:
	-$(RM) ./mtkernal/lib/libtm/libtm.cyclo ./mtkernal/lib/libtm/libtm.d ./mtkernal/lib/libtm/libtm.o ./mtkernal/lib/libtm/libtm.su ./mtkernal/lib/libtm/libtm_printf.cyclo ./mtkernal/lib/libtm/libtm_printf.d ./mtkernal/lib/libtm/libtm_printf.o ./mtkernal/lib/libtm/libtm_printf.su

.PHONY: clean-mtkernal-2f-lib-2f-libtm

