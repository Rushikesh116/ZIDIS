################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mtkernal/kernel/sysdepend/cpu/core/armv7m/cpu_cntl.c \
../mtkernal/kernel/sysdepend/cpu/core/armv7m/exc_hdr.c \
../mtkernal/kernel/sysdepend/cpu/core/armv7m/interrupt.c \
../mtkernal/kernel/sysdepend/cpu/core/armv7m/reset_hdl.c 

S_UPPER_SRCS += \
../mtkernal/kernel/sysdepend/cpu/core/armv7m/dispatch.S 

OBJS += \
./mtkernal/kernel/sysdepend/cpu/core/armv7m/cpu_cntl.o \
./mtkernal/kernel/sysdepend/cpu/core/armv7m/dispatch.o \
./mtkernal/kernel/sysdepend/cpu/core/armv7m/exc_hdr.o \
./mtkernal/kernel/sysdepend/cpu/core/armv7m/interrupt.o \
./mtkernal/kernel/sysdepend/cpu/core/armv7m/reset_hdl.o 

S_UPPER_DEPS += \
./mtkernal/kernel/sysdepend/cpu/core/armv7m/dispatch.d 

C_DEPS += \
./mtkernal/kernel/sysdepend/cpu/core/armv7m/cpu_cntl.d \
./mtkernal/kernel/sysdepend/cpu/core/armv7m/exc_hdr.d \
./mtkernal/kernel/sysdepend/cpu/core/armv7m/interrupt.d \
./mtkernal/kernel/sysdepend/cpu/core/armv7m/reset_hdl.d 


# Each subdirectory must supply rules for building sources it contributes
mtkernal/kernel/sysdepend/cpu/core/armv7m/%.o mtkernal/kernel/sysdepend/cpu/core/armv7m/%.su mtkernal/kernel/sysdepend/cpu/core/armv7m/%.cyclo: ../mtkernal/kernel/sysdepend/cpu/core/armv7m/%.c mtkernal/kernel/sysdepend/cpu/core/armv7m/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG '-DKNL_SYSDEP_PATH=cpu/core/armv8m' '-DTARGET_DIR=cpu/core/armv8m' -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32H533xx '-DKNL_SYSDEP_PATH=cpu/core/armv8m' -c -I../Core/Inc -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/kernel/knlinc" -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/config" -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/include" -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32H5xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
mtkernal/kernel/sysdepend/cpu/core/armv7m/%.o: ../mtkernal/kernel/sysdepend/cpu/core/armv7m/%.S mtkernal/kernel/sysdepend/cpu/core/armv7m/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m33 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-mtkernal-2f-kernel-2f-sysdepend-2f-cpu-2f-core-2f-armv7m

clean-mtkernal-2f-kernel-2f-sysdepend-2f-cpu-2f-core-2f-armv7m:
	-$(RM) ./mtkernal/kernel/sysdepend/cpu/core/armv7m/cpu_cntl.cyclo ./mtkernal/kernel/sysdepend/cpu/core/armv7m/cpu_cntl.d ./mtkernal/kernel/sysdepend/cpu/core/armv7m/cpu_cntl.o ./mtkernal/kernel/sysdepend/cpu/core/armv7m/cpu_cntl.su ./mtkernal/kernel/sysdepend/cpu/core/armv7m/dispatch.d ./mtkernal/kernel/sysdepend/cpu/core/armv7m/dispatch.o ./mtkernal/kernel/sysdepend/cpu/core/armv7m/exc_hdr.cyclo ./mtkernal/kernel/sysdepend/cpu/core/armv7m/exc_hdr.d ./mtkernal/kernel/sysdepend/cpu/core/armv7m/exc_hdr.o ./mtkernal/kernel/sysdepend/cpu/core/armv7m/exc_hdr.su ./mtkernal/kernel/sysdepend/cpu/core/armv7m/interrupt.cyclo ./mtkernal/kernel/sysdepend/cpu/core/armv7m/interrupt.d ./mtkernal/kernel/sysdepend/cpu/core/armv7m/interrupt.o ./mtkernal/kernel/sysdepend/cpu/core/armv7m/interrupt.su ./mtkernal/kernel/sysdepend/cpu/core/armv7m/reset_hdl.cyclo ./mtkernal/kernel/sysdepend/cpu/core/armv7m/reset_hdl.d ./mtkernal/kernel/sysdepend/cpu/core/armv7m/reset_hdl.o ./mtkernal/kernel/sysdepend/cpu/core/armv7m/reset_hdl.su

.PHONY: clean-mtkernal-2f-kernel-2f-sysdepend-2f-cpu-2f-core-2f-armv7m

