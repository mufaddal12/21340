################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/assign-1-binary\ tree.cpp 

OBJS += \
./src/assign-1-binary\ tree.o 

CPP_DEPS += \
./src/assign-1-binary\ tree.d 


# Each subdirectory must supply rules for building sources it contributes
src/assign-1-binary\ tree.o: ../src/assign-1-binary\ tree.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/assign-1-binary tree.d" -MT"src/assign-1-binary\ tree.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


