# ------------------------------------------------
# @author Adrian Szczepanski
# @date 23-07-2021
# ------------------------------------------------

# Target
target = libCppUTest
platform := Pc32
supported_platforms := Pc32 ArmM4 ArmM7

ifeq (platform, Pc32)
target += Pc32
endif

# debug
DEBUG := 1
opt := -Og

# directories
build_root_dir := build
lib_root_dir := lib
build_dir := $(build_root_dir)/$(platform)
lib_dir := $(lib_root_dir)/$(platform)

# toolchain
ifeq ($(platform), Pc32)
prefix := 
else
prefix := arm-none-eabi-
endif

CC := $(prefix)gcc
CXX := $(prefix)g++
AS := $(prefix)gcc -x assembler-with-cpp
CP := $(prefix)objcopy
SZ := $(prefix)size
AR := $(prefix)ar
HEX := $(CP) -O ihex
BIN := $(CP) -O binary -S

# mcu definition
ifeq ($(platform), Pc32)
mcu := -m32
else ifeq ($(platform), ArmM4)
cpu := -mcpu=cortex-m4
fpu := -mfpu=fpv4-sp-d16
float-abi := -mfloat-abi=hard
mcu := $(cpu) -mthumb $(fpu) $(float-abi)
else ifeq ($(platform), ArmM7)
cpu := -mcpu=cortex-m7
fpu := -mfpu=fpv5-sp-d16
float-abi := -mfloat-abi=hard
mcu := $(cpu) -mthumb $(fpu) $(float-abi)
else
$(error "Platform $(platform) not supported!")
endif 

# sources 
cxx_sources :=  \
$(wildcard src/CppUTest/*.cpp) \

# includes
cxx_includes :=  \
-Iinclude \

#defines
ifeq ($(platform), Pc32)
use_std_lib := 1
else
use_std_lib := 0
endif

cxx_defs := \
-DCPPUTEST_USE_STD_CPP_LIB=$(use_std_lib)

# gcc flags
cxxflags = $(mcu) $(cxx_defs) $(cxx_includes) $(opt) -std=c++17

ifneq ($(platform), Pc32)
cxxflags += -fdata-sections -ffunction-sections -ffreestanding -fno-exceptions -nostdlib
endif

ifeq ($(DEBUG), 1)
cxxflags += -g -gdwarf-2
endif

# Generate dependency information
cxxflags += -MMD -MP -MF"$(@:%.o=%.d)"


.PHONY: all $(supported_platforms) clean mrproper distclean

all: $(supported_platforms)

$(supported_platforms):
	+@$(MAKE) --directory=. library platform=$@

library: $(lib_dir)/$(target).a

print-%: ; @echo $* = $($*)

# list of C++ objects
objects := $(addprefix $(build_dir)/,$(notdir $(cxx_sources:.cpp=.o)))
vpath %.cpp $(sort $(dir $(cxx_sources)))

# build C++ objects
$(build_dir)/%.o: %.cpp Makefile | $(build_dir)
	@echo Compiling $<
	@$(CXX) -c $(cxxflags) -Wa,-a,-ad,-alms=$(build_dir)/$(notdir $(<:.cpp=.lst)) $< -o $@

# build library
$(lib_dir)/$(target).a: $(objects) Makefile | $(lib_dir)
	@echo Creating library $@
	@$(AR) rcs $@ $(objects) 

# create directories
$(build_dir):
	mkdir -p $@		

$(lib_dir):
	mkdir -p $@

# clean up
clean:
	@echo Cleaning build directory
	@rm -rf $(build_root_dir)

mrproper distclean: clean
	@echo Cleaning lib directory
	@rm -rf $(lib_root_dir)
  
# dependencies
-include $(wildcard $(build_dir)/*.d)