################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mtkernal/lib/libtk/sysdepend/cpu/core/armv7a/int_armv7a.c \
../mtkernal/lib/libtk/sysdepend/cpu/core/armv7a/wusec_armv7a.c 

OBJS += \
./mtkernal/lib/libtk/sysdepend/cpu/core/armv7a/int_armv7a.o \
./mtkernal/lib/libtk/sysdepend/cpu/core/armv7a/wusec_armv7a.o 

C_DEPS += \
./mtkernal/lib/libtk/sysdepend/cpu/core/armv7a/int_armv7a.d \
./mtkernal/lib/libtk/sysdepend/cpu/core/armv7a/wusec_armv7a.d 


# Each subdirectory must supply rules for building sources it contributes
mtkernal/lib/libtk/sysdepend/cpu/core/armv7a/%.o mtkernal/lib/libtk/sysdepend/cpu/core/armv7a/%.su mtkernal/lib/libtk/sysdepend/cpu/core/armv7a/%.cyclo: ../mtkernal/lib/libtk/sysdepend/cpu/core/armv7a/%.c mtkernal/lib/libtk/sysdepend/cpu/core/armv7a/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32H533xx -c -I../Core/Inc -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/include" -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32H5xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-mtkernal-2f-lib-2f-libtk-2f-sysdepend-2f-cpu-2f-core-2f-armv7a

clean-mtkernal-2f-lib-2f-libtk-2f-sysdepend-2f-cpu-2f-core-2f-armv7a:
	-$(RM) ./mtkernal/lib/libtk/sysdepend/cpu/core/armv7a/int_armv7a.cyclo ./mtkernal/lib/libtk/sysdepend/cpu/core/armv7a/int_armv7a.d ./mtkernal/lib/libtk/sysdepend/cpu/core/armv7a/int_armv7a.o ./mtkernal/lib/libtk/sysdepend/cpu/core/armv7a/int_armv7a.su ./mtkernal/lib/libtk/sysdepend/cpu/core/armv7a/wusec_armv7a.cyclo ./mtkernal/lib/libtk/sysdepend/cpu/core/armv7a/wusec_armv7a.d ./mtkernal/lib/libtk/sysdepend/cpu/core/armv7a/wusec_armv7a.o ./mtkernal/lib/libtk/sysdepend/cpu/core/armv7a/wusec_armv7a.su

.PHONY: clean-mtkernal-2f-lib-2f-libtk-2f-sysdepend-2f-cpu-2f-core-2f-armv7a

