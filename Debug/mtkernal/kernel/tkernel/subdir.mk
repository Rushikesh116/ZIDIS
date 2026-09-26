################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mtkernal/kernel/tkernel/cpuctl.c \
../mtkernal/kernel/tkernel/device.c \
../mtkernal/kernel/tkernel/deviceio.c \
../mtkernal/kernel/tkernel/eventflag.c \
../mtkernal/kernel/tkernel/int.c \
../mtkernal/kernel/tkernel/klock.c \
../mtkernal/kernel/tkernel/mailbox.c \
../mtkernal/kernel/tkernel/memory.c \
../mtkernal/kernel/tkernel/mempfix.c \
../mtkernal/kernel/tkernel/mempool.c \
../mtkernal/kernel/tkernel/messagebuf.c \
../mtkernal/kernel/tkernel/misc_calls.c \
../mtkernal/kernel/tkernel/mutex.c \
../mtkernal/kernel/tkernel/objname.c \
../mtkernal/kernel/tkernel/power.c \
../mtkernal/kernel/tkernel/rendezvous.c \
../mtkernal/kernel/tkernel/semaphore.c \
../mtkernal/kernel/tkernel/task.c \
../mtkernal/kernel/tkernel/task_manage.c \
../mtkernal/kernel/tkernel/task_sync.c \
../mtkernal/kernel/tkernel/time_calls.c \
../mtkernal/kernel/tkernel/timer.c \
../mtkernal/kernel/tkernel/tkinit.c \
../mtkernal/kernel/tkernel/wait.c 

OBJS += \
./mtkernal/kernel/tkernel/cpuctl.o \
./mtkernal/kernel/tkernel/device.o \
./mtkernal/kernel/tkernel/deviceio.o \
./mtkernal/kernel/tkernel/eventflag.o \
./mtkernal/kernel/tkernel/int.o \
./mtkernal/kernel/tkernel/klock.o \
./mtkernal/kernel/tkernel/mailbox.o \
./mtkernal/kernel/tkernel/memory.o \
./mtkernal/kernel/tkernel/mempfix.o \
./mtkernal/kernel/tkernel/mempool.o \
./mtkernal/kernel/tkernel/messagebuf.o \
./mtkernal/kernel/tkernel/misc_calls.o \
./mtkernal/kernel/tkernel/mutex.o \
./mtkernal/kernel/tkernel/objname.o \
./mtkernal/kernel/tkernel/power.o \
./mtkernal/kernel/tkernel/rendezvous.o \
./mtkernal/kernel/tkernel/semaphore.o \
./mtkernal/kernel/tkernel/task.o \
./mtkernal/kernel/tkernel/task_manage.o \
./mtkernal/kernel/tkernel/task_sync.o \
./mtkernal/kernel/tkernel/time_calls.o \
./mtkernal/kernel/tkernel/timer.o \
./mtkernal/kernel/tkernel/tkinit.o \
./mtkernal/kernel/tkernel/wait.o 

C_DEPS += \
./mtkernal/kernel/tkernel/cpuctl.d \
./mtkernal/kernel/tkernel/device.d \
./mtkernal/kernel/tkernel/deviceio.d \
./mtkernal/kernel/tkernel/eventflag.d \
./mtkernal/kernel/tkernel/int.d \
./mtkernal/kernel/tkernel/klock.d \
./mtkernal/kernel/tkernel/mailbox.d \
./mtkernal/kernel/tkernel/memory.d \
./mtkernal/kernel/tkernel/mempfix.d \
./mtkernal/kernel/tkernel/mempool.d \
./mtkernal/kernel/tkernel/messagebuf.d \
./mtkernal/kernel/tkernel/misc_calls.d \
./mtkernal/kernel/tkernel/mutex.d \
./mtkernal/kernel/tkernel/objname.d \
./mtkernal/kernel/tkernel/power.d \
./mtkernal/kernel/tkernel/rendezvous.d \
./mtkernal/kernel/tkernel/semaphore.d \
./mtkernal/kernel/tkernel/task.d \
./mtkernal/kernel/tkernel/task_manage.d \
./mtkernal/kernel/tkernel/task_sync.d \
./mtkernal/kernel/tkernel/time_calls.d \
./mtkernal/kernel/tkernel/timer.d \
./mtkernal/kernel/tkernel/tkinit.d \
./mtkernal/kernel/tkernel/wait.d 


# Each subdirectory must supply rules for building sources it contributes
mtkernal/kernel/tkernel/%.o mtkernal/kernel/tkernel/%.su mtkernal/kernel/tkernel/%.cyclo: ../mtkernal/kernel/tkernel/%.c mtkernal/kernel/tkernel/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG '-DKNL_SYSDEP_PATH=cpu/core/armv8m' '-DTARGET_DIR=cpu/core/armv8m' -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32H533xx '-DKNL_SYSDEP_PATH=cpu/core/armv8m' -c -I../Core/Inc -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/kernel/knlinc" -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/config" -I"C:/Users/Raamrithik/OneDrive/Documents/ZIDIS_Node/mtkernal/include" -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32H5xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-mtkernal-2f-kernel-2f-tkernel

clean-mtkernal-2f-kernel-2f-tkernel:
	-$(RM) ./mtkernal/kernel/tkernel/cpuctl.cyclo ./mtkernal/kernel/tkernel/cpuctl.d ./mtkernal/kernel/tkernel/cpuctl.o ./mtkernal/kernel/tkernel/cpuctl.su ./mtkernal/kernel/tkernel/device.cyclo ./mtkernal/kernel/tkernel/device.d ./mtkernal/kernel/tkernel/device.o ./mtkernal/kernel/tkernel/device.su ./mtkernal/kernel/tkernel/deviceio.cyclo ./mtkernal/kernel/tkernel/deviceio.d ./mtkernal/kernel/tkernel/deviceio.o ./mtkernal/kernel/tkernel/deviceio.su ./mtkernal/kernel/tkernel/eventflag.cyclo ./mtkernal/kernel/tkernel/eventflag.d ./mtkernal/kernel/tkernel/eventflag.o ./mtkernal/kernel/tkernel/eventflag.su ./mtkernal/kernel/tkernel/int.cyclo ./mtkernal/kernel/tkernel/int.d ./mtkernal/kernel/tkernel/int.o ./mtkernal/kernel/tkernel/int.su ./mtkernal/kernel/tkernel/klock.cyclo ./mtkernal/kernel/tkernel/klock.d ./mtkernal/kernel/tkernel/klock.o ./mtkernal/kernel/tkernel/klock.su ./mtkernal/kernel/tkernel/mailbox.cyclo ./mtkernal/kernel/tkernel/mailbox.d ./mtkernal/kernel/tkernel/mailbox.o ./mtkernal/kernel/tkernel/mailbox.su ./mtkernal/kernel/tkernel/memory.cyclo ./mtkernal/kernel/tkernel/memory.d ./mtkernal/kernel/tkernel/memory.o ./mtkernal/kernel/tkernel/memory.su ./mtkernal/kernel/tkernel/mempfix.cyclo ./mtkernal/kernel/tkernel/mempfix.d ./mtkernal/kernel/tkernel/mempfix.o ./mtkernal/kernel/tkernel/mempfix.su ./mtkernal/kernel/tkernel/mempool.cyclo ./mtkernal/kernel/tkernel/mempool.d ./mtkernal/kernel/tkernel/mempool.o ./mtkernal/kernel/tkernel/mempool.su ./mtkernal/kernel/tkernel/messagebuf.cyclo ./mtkernal/kernel/tkernel/messagebuf.d ./mtkernal/kernel/tkernel/messagebuf.o ./mtkernal/kernel/tkernel/messagebuf.su ./mtkernal/kernel/tkernel/misc_calls.cyclo ./mtkernal/kernel/tkernel/misc_calls.d ./mtkernal/kernel/tkernel/misc_calls.o ./mtkernal/kernel/tkernel/misc_calls.su ./mtkernal/kernel/tkernel/mutex.cyclo ./mtkernal/kernel/tkernel/mutex.d ./mtkernal/kernel/tkernel/mutex.o ./mtkernal/kernel/tkernel/mutex.su ./mtkernal/kernel/tkernel/objname.cyclo ./mtkernal/kernel/tkernel/objname.d ./mtkernal/kernel/tkernel/objname.o ./mtkernal/kernel/tkernel/objname.su ./mtkernal/kernel/tkernel/power.cyclo ./mtkernal/kernel/tkernel/power.d ./mtkernal/kernel/tkernel/power.o ./mtkernal/kernel/tkernel/power.su ./mtkernal/kernel/tkernel/rendezvous.cyclo ./mtkernal/kernel/tkernel/rendezvous.d ./mtkernal/kernel/tkernel/rendezvous.o ./mtkernal/kernel/tkernel/rendezvous.su ./mtkernal/kernel/tkernel/semaphore.cyclo ./mtkernal/kernel/tkernel/semaphore.d ./mtkernal/kernel/tkernel/semaphore.o ./mtkernal/kernel/tkernel/semaphore.su ./mtkernal/kernel/tkernel/task.cyclo ./mtkernal/kernel/tkernel/task.d ./mtkernal/kernel/tkernel/task.o ./mtkernal/kernel/tkernel/task.su ./mtkernal/kernel/tkernel/task_manage.cyclo ./mtkernal/kernel/tkernel/task_manage.d ./mtkernal/kernel/tkernel/task_manage.o ./mtkernal/kernel/tkernel/task_manage.su ./mtkernal/kernel/tkernel/task_sync.cyclo ./mtkernal/kernel/tkernel/task_sync.d ./mtkernal/kernel/tkernel/task_sync.o ./mtkernal/kernel/tkernel/task_sync.su ./mtkernal/kernel/tkernel/time_calls.cyclo ./mtkernal/kernel/tkernel/time_calls.d ./mtkernal/kernel/tkernel/time_calls.o ./mtkernal/kernel/tkernel/time_calls.su ./mtkernal/kernel/tkernel/timer.cyclo ./mtkernal/kernel/tkernel/timer.d ./mtkernal/kernel/tkernel/timer.o ./mtkernal/kernel/tkernel/timer.su ./mtkernal/kernel/tkernel/tkinit.cyclo ./mtkernal/kernel/tkernel/tkinit.d ./mtkernal/kernel/tkernel/tkinit.o ./mtkernal/kernel/tkernel/tkinit.su ./mtkernal/kernel/tkernel/wait.cyclo ./mtkernal/kernel/tkernel/wait.d ./mtkernal/kernel/tkernel/wait.o ./mtkernal/kernel/tkernel/wait.su

.PHONY: clean-mtkernal-2f-kernel-2f-tkernel

