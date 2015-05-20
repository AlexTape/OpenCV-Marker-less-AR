################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Overlay/modelObjectFactory.cpp \
../src/Overlay/mqoModelObject.cpp \
../src/Overlay/mqoSeqModelObject.cpp \
../src/Overlay/slideModelObject.cpp \
../src/Overlay/viewModel.cpp 

C_SRCS += \
../src/Overlay/GLMetaseq.c 

OBJS += \
./src/Overlay/GLMetaseq.o \
./src/Overlay/modelObjectFactory.o \
./src/Overlay/mqoModelObject.o \
./src/Overlay/mqoSeqModelObject.o \
./src/Overlay/slideModelObject.o \
./src/Overlay/viewModel.o 

C_DEPS += \
./src/Overlay/GLMetaseq.d 

CPP_DEPS += \
./src/Overlay/modelObjectFactory.d \
./src/Overlay/mqoModelObject.d \
./src/Overlay/mqoSeqModelObject.d \
./src/Overlay/slideModelObject.d \
./src/Overlay/viewModel.d 


# Each subdirectory must supply rules for building sources it contributes
src/Overlay/%.o: ../src/Overlay/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Overlay/%.o: ../src/Overlay/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


