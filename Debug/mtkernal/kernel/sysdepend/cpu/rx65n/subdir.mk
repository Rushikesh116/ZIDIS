################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mtkernal/kernel/sysdepend/cpu/rx65n/group_int.c \
../mtkernal/kernel/sysdepend/cpu/rx65n/hllint_tbl.c \
../mtkernal/kernel/sysdepend/cpu/rx65n/intvect_tbl.c 

S_UPPER_SRCS += \
../mtkernal/kernel/sysdepend/cpu/rx65n/hllint_ent.S 

OBJS += \
./mtkernal/kernel/sysdepend/cpu/rx65n/group_int.o \
./mtkernal/kernel/sysdepend/cpu/rx65n/hllint_ent.o \
./mtkernal/kernel/sysdepend/cpu/rx65n/hllint_tbl.o \
./mtkernal/kernel/sysdepend/cpu/rx65n/intvect_tbl.o 

S_UPPER_DEPS += \
./mtkernal/kernel/sysdepend/cpu/rx65n/hllint_ent.d 

C_DEPS += \
./mtkernal/kernel/sysdepend/cpu/rx65n/group_int.d \
./mtkernal/kernel/sysdepend/cpu/rx65n/hllint_tbl.d \
./mtkernal/kernel/sysdepend/cpu/rx65n/intvect_tbl.d 


# Each subdirectory must supply rules for building sources it contributes
mtkernal/kernel/sysdepend/cpu/rx65n/%.o mtkernal/kernel/sysdepend/cpu/rx65n/%.su mtkernal/kernel/sysdepend/cpu/rx65n/%.cyclo: ../mtkernal/kernel/sysdepend/cpu/rx65n/%.c mtkernal/kernel/sysdepend/cpu/rx65n/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG '-DKNL_SYSDEP_PATH=cpu/core/armv8m' '-DTARGET_DIR=cpu/core/armv8m' -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32H533xx '-DKNL_SYSDEP_PATH=cpu/core/armv8m' -c -I../Core/Inc -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/kernel/knlinc" -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/config" -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/include" -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32H5xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
mtkernal/kernel/sysdepend/cpu/rx65n/%.o: ../mtkernal/kernel/sysdepend/cpu/rx65n/%.S mtkernal/kernel/sysdepend/cpu/rx65n/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m33 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-mtkernal-2f-kernel-2f-sysdepend-2f-cpu-2f-rx65n

clean-mtkernal-2f-kernel-2f-sysdepend-2f-cpu-2f-rx65n:
	-$(RM) ./mtkernal/kernel/sysdepend/cpu/rx65n/group_int.cyclo ./mtkernal/kernel/sysdepend/cpu/rx65n/group_int.d ./mtkernal/kernel/sysdepend/cpu/rx65n/group_int.o ./mtkernal/kernel/sysdepend/cpu/rx65n/group_int.su ./mtkernal/kernel/sysdepend/cpu/rx65n/hllint_ent.d ./mtkernal/kernel/sysdepend/cpu/rx65n/hllint_ent.o ./mtkernal/kernel/sysdepend/cpu/rx65n/hllint_tbl.cyclo ./mtkernal/kernel/sysdepend/cpu/rx65n/hllint_tbl.d ./mtkernal/kernel/sysdepend/cpu/rx65n/hllint_tbl.o ./mtkernal/kernel/sysdepend/cpu/rx65n/hllint_tbl.su ./mtkernal/kernel/sysdepend/cpu/rx65n/intvect_tbl.cyclo ./mtkernal/kernel/sysdepend/cpu/rx65n/intvect_tbl.d ./mtkernal/kernel/sysdepend/cpu/rx65n/intvect_tbl.o ./mtkernal/kernel/sysdepend/cpu/rx65n/intvect_tbl.su

.PHONY: clean-mtkernal-2f-kernel-2f-sysdepend-2f-cpu-2f-rx65n

