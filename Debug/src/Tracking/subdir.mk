################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Tracking/kltTrackingOBJ.cpp \
../src/Tracking/trackingOBJ.cpp 

OBJS += \
./src/Tracking/kltTrackingOBJ.o \
./src/Tracking/trackingOBJ.o 

CPP_DEPS += \
./src/Tracking/kltTrackingOBJ.d \
./src/Tracking/trackingOBJ.d 


# Each subdirectory must supply rules for building sources it contributes
src/Tracking/%.o: ../src/Tracking/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


