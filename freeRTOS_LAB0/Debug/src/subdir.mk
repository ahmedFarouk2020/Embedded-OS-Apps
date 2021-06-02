################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DIO_program.c \
../src/RCC_program.c \
../src/croutine.c \
../src/event_groups.c \
../src/heap_2.c \
../src/list.c \
../src/main.c \
../src/port.c \
../src/queue.c \
../src/stream_buffer.c \
../src/tasks.c \
../src/timers.c 

OBJS += \
./src/DIO_program.o \
./src/RCC_program.o \
./src/croutine.o \
./src/event_groups.o \
./src/heap_2.o \
./src/list.o \
./src/main.o \
./src/port.o \
./src/queue.o \
./src/stream_buffer.o \
./src/tasks.o \
./src/timers.o 

C_DEPS += \
./src/DIO_program.d \
./src/RCC_program.d \
./src/croutine.d \
./src/event_groups.d \
./src/heap_2.d \
./src/list.d \
./src/main.d \
./src/port.d \
./src/queue.d \
./src/stream_buffer.d \
./src/tasks.d \
./src/timers.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


