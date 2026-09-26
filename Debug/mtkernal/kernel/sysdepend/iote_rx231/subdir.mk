################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mtkernal/kernel/sysdepend/iote_rx231/cpu_clock.c \
../mtkernal/kernel/sysdepend/iote_rx231/devinit.c \
../mtkernal/kernel/sysdepend/iote_rx231/hw_setting.c \
../mtkernal/kernel/sysdepend/iote_rx231/power_save.c 

OBJS += \
./mtkernal/kernel/sysdepend/iote_rx231/cpu_clock.o \
./mtkernal/kernel/sysdepend/iote_rx231/devinit.o \
./mtkernal/kernel/sysdepend/iote_rx231/hw_setting.o \
./mtkernal/kernel/sysdepend/iote_rx231/power_save.o 

C_DEPS += \
./mtkernal/kernel/sysdepend/iote_rx231/cpu_clock.d \
./mtkernal/kernel/sysdepend/iote_rx231/devinit.d \
./mtkernal/kernel/sysdepend/iote_rx231/hw_setting.d \
./mtkernal/kernel/sysdepend/iote_rx231/power_save.d 


# Each subdirectory must supply rules for building sources it contributes
mtkernal/kernel/sysdepend/iote_rx231/%.o mtkernal/kernel/sysdepend/iote_rx231/%.su mtkernal/kernel/sysdepend/iote_rx231/%.cyclo: ../mtkernal/kernel/sysdepend/iote_rx231/%.c mtkernal/kernel/sysdepend/iote_rx231/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG '-DKNL_SYSDEP_PATH=cpu/core/armv8m' '-DTARGET_DIR=cpu/core/armv8m' -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32H533xx '-DKNL_SYSDEP_PATH=cpu/core/armv8m' -c -I../Core/Inc -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/kernel/knlinc" -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/config" -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/include" -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32H5xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-mtkernal-2f-kernel-2f-sysdepend-2f-iote_rx231

clean-mtkernal-2f-kernel-2f-sysdepend-2f-iote_rx231:
	-$(RM) ./mtkernal/kernel/sysdepend/iote_rx231/cpu_clock.cyclo ./mtkernal/kernel/sysdepend/iote_rx231/cpu_clock.d ./mtkernal/kernel/sysdepend/iote_rx231/cpu_clock.o ./mtkernal/kernel/sysdepend/iote_rx231/cpu_clock.su ./mtkernal/kernel/sysdepend/iote_rx231/devinit.cyclo ./mtkernal/kernel/sysdepend/iote_rx231/devinit.d ./mtkernal/kernel/sysdepend/iote_rx231/devinit.o ./mtkernal/kernel/sysdepend/iote_rx231/devinit.su ./mtkernal/kernel/sysdepend/iote_rx231/hw_setting.cyclo ./mtkernal/kernel/sysdepend/iote_rx231/hw_setting.d ./mtkernal/kernel/sysdepend/iote_rx231/hw_setting.o ./mtkernal/kernel/sysdepend/iote_rx231/hw_setting.su ./mtkernal/kernel/sysdepend/iote_rx231/power_save.cyclo ./mtkernal/kernel/sysdepend/iote_rx231/power_save.d ./mtkernal/kernel/sysdepend/iote_rx231/power_save.o ./mtkernal/kernel/sysdepend/iote_rx231/power_save.su

.PHONY: clean-mtkernal-2f-kernel-2f-sysdepend-2f-iote_rx231

