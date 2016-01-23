################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/abs.c \
../lib/atoi.c \
../lib/atol.c \
../lib/bzero.c \
../lib/ctype_.c \
../lib/doprnt.c \
../lib/doscan.c \
../lib/fdoprnt.c \
../lib/fgetc.c \
../lib/fgets.c \
../lib/fprintf.c \
../lib/fputc.c \
../lib/fputs.c \
../lib/fscanf.c \
../lib/getchar.c \
../lib/labs.c \
../lib/memchr.c \
../lib/memcmp.c \
../lib/memcpy.c \
../lib/memset.c \
../lib/printf.c \
../lib/putchar.c \
../lib/qsort.c \
../lib/rand.c \
../lib/sprintf.c \
../lib/sscanf.c \
../lib/strchr.c \
../lib/strcmp.c \
../lib/strcpy.c \
../lib/strlen.c \
../lib/strncat.c \
../lib/strncmp.c \
../lib/strncpy.c \
../lib/strnlen.c \
../lib/strrchr.c \
../lib/strstr.c 

OBJS += \
./lib/abs.o \
./lib/atoi.o \
./lib/atol.o \
./lib/bzero.o \
./lib/ctype_.o \
./lib/doprnt.o \
./lib/doscan.o \
./lib/fdoprnt.o \
./lib/fgetc.o \
./lib/fgets.o \
./lib/fprintf.o \
./lib/fputc.o \
./lib/fputs.o \
./lib/fscanf.o \
./lib/getchar.o \
./lib/labs.o \
./lib/memchr.o \
./lib/memcmp.o \
./lib/memcpy.o \
./lib/memset.o \
./lib/printf.o \
./lib/putchar.o \
./lib/qsort.o \
./lib/rand.o \
./lib/sprintf.o \
./lib/sscanf.o \
./lib/strchr.o \
./lib/strcmp.o \
./lib/strcpy.o \
./lib/strlen.o \
./lib/strncat.o \
./lib/strncmp.o \
./lib/strncpy.o \
./lib/strnlen.o \
./lib/strrchr.o \
./lib/strstr.o 

C_DEPS += \
./lib/abs.d \
./lib/atoi.d \
./lib/atol.d \
./lib/bzero.d \
./lib/ctype_.d \
./lib/doprnt.d \
./lib/doscan.d \
./lib/fdoprnt.d \
./lib/fgetc.d \
./lib/fgets.d \
./lib/fprintf.d \
./lib/fputc.d \
./lib/fputs.d \
./lib/fscanf.d \
./lib/getchar.d \
./lib/labs.d \
./lib/memchr.d \
./lib/memcmp.d \
./lib/memcpy.d \
./lib/memset.d \
./lib/printf.d \
./lib/putchar.d \
./lib/qsort.d \
./lib/rand.d \
./lib/sprintf.d \
./lib/sscanf.d \
./lib/strchr.d \
./lib/strcmp.d \
./lib/strcpy.d \
./lib/strlen.d \
./lib/strncat.d \
./lib/strncmp.d \
./lib/strncpy.d \
./lib/strnlen.d \
./lib/strrchr.d \
./lib/strstr.d 


# Each subdirectory must supply rules for building sources it contributes
lib/%.o: ../lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


