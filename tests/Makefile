# ------------------------------------------------
# @author Adrian Szczepanski
# @date 23-07-2021
# ------------------------------------------------

# Target
TARGET = testCli

# debug
DEBUG = 1
OPT = -O0

# directories
BUILD_DIR = ../build/$(TARGET)
LIB_DIR = ../lib
TEST_DIR = ../test
TEST_LIB_DIR = ../external/CppUTest

# libraries
LIBRARY_INCLUDES = \
-I.. \
-I$(TEST_LIB_DIR)/include \

LIBRARY_FLAGS = \
-lCliWin32\
-lCppUTest \

LIBRARY_SEARCH_PATH = \
-L$(LIB_DIR) \
-L$(TEST_LIB_DIR)/lib/Win32 \

# toolchain
CXX = g++
AS = gcc -x assembler-with-cpp
CP = objcopy
SZ = size
AR = ar
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

# mcu definition
MCU = -m32

# sources 
CXX_SOURCES =  \
$(wildcard *.cpp) \
$(wildcard Utils/*.cpp) \
$(wildcard Mock/*.cpp) \
$(wildcard Template/*.cpp) \
$(wildcard Model/*.cpp) \
$(wildcard Internal/*.cpp) \
$(wildcard Internal/IO/*.cpp) \
$(wildcard Internal/IO/Container/*.cpp) \

# includes
CXX_INCLUDES =  \
$(LIBRARY_INCLUDES) \

# libraries
LIBRARIES = $(LIBRARY_FLAGS)

# gcc flags
CXXFLAGS = $(MCU) $(CXX_DEFS) $(CXX_INCLUDES) $(OPT) -Wall -std=c++17
LDFLAGS = $(MCU) $(LIBRARY_SEARCH_PATH)  $(LIBRARIES) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

ifeq ($(DEBUG), 1)
CXXFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CXXFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

.PHONY: binary print clean

# build all
binary: $(TEST_DIR)/$(TARGET).elf
	$(TEST_DIR)/$(TARGET).elf

print-%: ; @echo $* = $($*)

# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(CXX_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CXX_SOURCES)))

# build objects
$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	@echo Compiling $<
	@$(CXX) -c $(CXXFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

# build elf
$(TEST_DIR)/$(TARGET).elf: $(OBJECTS) Makefile | $(TEST_DIR)
	@echo Linking $@
	@$(CXX) $(OBJECTS) $(LDFLAGS) -o $@
	@$(SZ) $@	

# create directories
$(BUILD_DIR):
	mkdir -p $@		

$(TEST_DIR):
	mkdir -p $@

# clean up
clean:
	rm -rf $(BUILD_DIR)
  
# dependencies
-include $(wildcard $(BUILD_DIR)/*.d)