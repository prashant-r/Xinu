################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/nam/mount.c \
../device/nam/naminit.c \
../device/nam/nammap.c \
../device/nam/namopen.c 

OBJS += \
./device/nam/mount.o \
./device/nam/naminit.o \
./device/nam/nammap.o \
./device/nam/namopen.o 

C_DEPS += \
./device/nam/mount.d \
./device/nam/naminit.d \
./device/nam/nammap.d \
./device/nam/namopen.d 


# Each subdirectory must supply rules for building sources it contributes
device/nam/%.o: ../device/nam/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


