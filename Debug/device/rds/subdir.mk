################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/rds/rdsbufalloc.c \
../device/rds/rdsclose.c \
../device/rds/rdscomm.c \
../device/rds/rdscontrol.c \
../device/rds/rdsinit.c \
../device/rds/rdsopen.c \
../device/rds/rdsprocess.c \
../device/rds/rdsread.c \
../device/rds/rdswrite.c 

OBJS += \
./device/rds/rdsbufalloc.o \
./device/rds/rdsclose.o \
./device/rds/rdscomm.o \
./device/rds/rdscontrol.o \
./device/rds/rdsinit.o \
./device/rds/rdsopen.o \
./device/rds/rdsprocess.o \
./device/rds/rdsread.o \
./device/rds/rdswrite.o 

C_DEPS += \
./device/rds/rdsbufalloc.d \
./device/rds/rdsclose.d \
./device/rds/rdscomm.d \
./device/rds/rdscontrol.d \
./device/rds/rdsinit.d \
./device/rds/rdsopen.d \
./device/rds/rdsprocess.d \
./device/rds/rdsread.d \
./device/rds/rdswrite.d 


# Each subdirectory must supply rules for building sources it contributes
device/rds/%.o: ../device/rds/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


