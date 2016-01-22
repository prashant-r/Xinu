################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/tty/ttycontrol.c \
../device/tty/ttygetc.c \
../device/tty/ttyhandle_in.c \
../device/tty/ttyhandle_out.c \
../device/tty/ttyhandler.c \
../device/tty/ttyinit.c \
../device/tty/ttykickout.c \
../device/tty/ttyputc.c \
../device/tty/ttyread.c \
../device/tty/ttywrite.c 

S_UPPER_SRCS += \
../device/tty/ttydispatch.S 

OBJS += \
./device/tty/ttycontrol.o \
./device/tty/ttydispatch.o \
./device/tty/ttygetc.o \
./device/tty/ttyhandle_in.o \
./device/tty/ttyhandle_out.o \
./device/tty/ttyhandler.o \
./device/tty/ttyinit.o \
./device/tty/ttykickout.o \
./device/tty/ttyputc.o \
./device/tty/ttyread.o \
./device/tty/ttywrite.o 

C_DEPS += \
./device/tty/ttycontrol.d \
./device/tty/ttygetc.d \
./device/tty/ttyhandle_in.d \
./device/tty/ttyhandle_out.d \
./device/tty/ttyhandler.d \
./device/tty/ttyinit.d \
./device/tty/ttykickout.d \
./device/tty/ttyputc.d \
./device/tty/ttyread.d \
./device/tty/ttywrite.d 


# Each subdirectory must supply rules for building sources it contributes
device/tty/%.o: ../device/tty/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

device/tty/%.o: ../device/tty/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


