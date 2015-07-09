################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Main/cameraCalibration.cpp \
../src/Main/commonCvFunctions.cpp \
../src/Main/guiAR.cpp \
../src/Main/main.cpp \
../src/Main/orException.cpp \
../src/Main/utilFunctions.cpp 

OBJS += \
./src/Main/cameraCalibration.o \
./src/Main/commonCvFunctions.o \
./src/Main/guiAR.o \
./src/Main/main.o \
./src/Main/orException.o \
./src/Main/utilFunctions.o 

CPP_DEPS += \
./src/Main/cameraCalibration.d \
./src/Main/commonCvFunctions.d \
./src/Main/guiAR.d \
./src/Main/main.d \
./src/Main/orException.d \
./src/Main/utilFunctions.d 


# Each subdirectory must supply rules for building sources it contributes
src/Main/%.o: ../src/Main/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


