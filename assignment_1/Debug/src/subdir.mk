################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/assignment1_main.c \
../src/helpAndPrint.c \
../src/sortAndShuffle.c 

C_DEPS += \
./src/assignment1_main.d \
./src/helpAndPrint.d \
./src/sortAndShuffle.d 

OBJS += \
./src/assignment1_main.o \
./src/helpAndPrint.o \
./src/sortAndShuffle.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/assignment1_main.d ./src/assignment1_main.o ./src/helpAndPrint.d ./src/helpAndPrint.o ./src/sortAndShuffle.d ./src/sortAndShuffle.o

.PHONY: clean-src

