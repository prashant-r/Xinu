################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../shell/addargs.c \
../shell/lexan.c \
../shell/shell.c \
../shell/xsh_argecho.c \
../shell/xsh_arp.c \
../shell/xsh_cat.c \
../shell/xsh_clear.c \
../shell/xsh_date.c \
../shell/xsh_devdump.c \
../shell/xsh_echo.c \
../shell/xsh_exit.c \
../shell/xsh_help.c \
../shell/xsh_ipaddr.c \
../shell/xsh_kill.c \
../shell/xsh_memdump.c \
../shell/xsh_memstat.c \
../shell/xsh_ping.c \
../shell/xsh_ps.c \
../shell/xsh_rdstest.c \
../shell/xsh_sleep.c \
../shell/xsh_udpdump.c \
../shell/xsh_udpecho.c \
../shell/xsh_udpeserver.c \
../shell/xsh_uptime.c 

OBJS += \
./shell/addargs.o \
./shell/lexan.o \
./shell/shell.o \
./shell/xsh_argecho.o \
./shell/xsh_arp.o \
./shell/xsh_cat.o \
./shell/xsh_clear.o \
./shell/xsh_date.o \
./shell/xsh_devdump.o \
./shell/xsh_echo.o \
./shell/xsh_exit.o \
./shell/xsh_help.o \
./shell/xsh_ipaddr.o \
./shell/xsh_kill.o \
./shell/xsh_memdump.o \
./shell/xsh_memstat.o \
./shell/xsh_ping.o \
./shell/xsh_ps.o \
./shell/xsh_rdstest.o \
./shell/xsh_sleep.o \
./shell/xsh_udpdump.o \
./shell/xsh_udpecho.o \
./shell/xsh_udpeserver.o \
./shell/xsh_uptime.o 

C_DEPS += \
./shell/addargs.d \
./shell/lexan.d \
./shell/shell.d \
./shell/xsh_argecho.d \
./shell/xsh_arp.d \
./shell/xsh_cat.d \
./shell/xsh_clear.d \
./shell/xsh_date.d \
./shell/xsh_devdump.d \
./shell/xsh_echo.d \
./shell/xsh_exit.d \
./shell/xsh_help.d \
./shell/xsh_ipaddr.d \
./shell/xsh_kill.d \
./shell/xsh_memdump.d \
./shell/xsh_memstat.d \
./shell/xsh_ping.d \
./shell/xsh_ps.d \
./shell/xsh_rdstest.d \
./shell/xsh_sleep.d \
./shell/xsh_udpdump.d \
./shell/xsh_udpecho.d \
./shell/xsh_udpeserver.d \
./shell/xsh_uptime.d 


# Each subdirectory must supply rules for building sources it contributes
shell/%.o: ../shell/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


