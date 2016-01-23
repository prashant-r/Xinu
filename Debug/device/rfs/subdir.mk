################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/rfs/rflclose.c \
../device/rfs/rflgetc.c \
../device/rfs/rflinit.c \
../device/rfs/rflputc.c \
../device/rfs/rflread.c \
../device/rfs/rflseek.c \
../device/rfs/rflwrite.c \
../device/rfs/rfscomm.c \
../device/rfs/rfscontrol.c \
../device/rfs/rfsgetmode.c \
../device/rfs/rfsinit.c \
../device/rfs/rfsndmsg.c \
../device/rfs/rfsopen.c 

OBJS += \
./device/rfs/rflclose.o \
./device/rfs/rflgetc.o \
./device/rfs/rflinit.o \
./device/rfs/rflputc.o \
./device/rfs/rflread.o \
./device/rfs/rflseek.o \
./device/rfs/rflwrite.o \
./device/rfs/rfscomm.o \
./device/rfs/rfscontrol.o \
./device/rfs/rfsgetmode.o \
./device/rfs/rfsinit.o \
./device/rfs/rfsndmsg.o \
./device/rfs/rfsopen.o 

C_DEPS += \
./device/rfs/rflclose.d \
./device/rfs/rflgetc.d \
./device/rfs/rflinit.d \
./device/rfs/rflputc.d \
./device/rfs/rflread.d \
./device/rfs/rflseek.d \
./device/rfs/rflwrite.d \
./device/rfs/rfscomm.d \
./device/rfs/rfscontrol.d \
./device/rfs/rfsgetmode.d \
./device/rfs/rfsinit.d \
./device/rfs/rfsndmsg.d \
./device/rfs/rfsopen.d 


# Each subdirectory must supply rules for building sources it contributes
device/rfs/%.o: ../device/rfs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


