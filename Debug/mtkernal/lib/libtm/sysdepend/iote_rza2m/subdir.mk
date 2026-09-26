################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mtkernal/lib/libtm/sysdepend/iote_rza2m/tm_com.c 

OBJS += \
./mtkernal/lib/libtm/sysdepend/iote_rza2m/tm_com.o 

C_DEPS += \
./mtkernal/lib/libtm/sysdepend/iote_rza2m/tm_com.d 


# Each subdirectory must supply rules for building sources it contributes
mtkernal/lib/libtm/sysdepend/iote_rza2m/%.o mtkernal/lib/libtm/sysdepend/iote_rza2m/%.su mtkernal/lib/libtm/sysdepend/iote_rza2m/%.cyclo: ../mtkernal/lib/libtm/sysdepend/iote_rza2m/%.c mtkernal/lib/libtm/sysdepend/iote_rza2m/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32H533xx -c -I../Core/Inc -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/include" -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32H5xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-mtkernal-2f-lib-2f-libtm-2f-sysdepend-2f-iote_rza2m

clean-mtkernal-2f-lib-2f-libtm-2f-sysdepend-2f-iote_rza2m:
	-$(RM) ./mtkernal/lib/libtm/sysdepend/iote_rza2m/tm_com.cyclo ./mtkernal/lib/libtm/sysdepend/iote_rza2m/tm_com.d ./mtkernal/lib/libtm/sysdepend/iote_rza2m/tm_com.o ./mtkernal/lib/libtm/sysdepend/iote_rza2m/tm_com.su

.PHONY: clean-mtkernal-2f-lib-2f-libtm-2f-sysdepend-2f-iote_rza2m

