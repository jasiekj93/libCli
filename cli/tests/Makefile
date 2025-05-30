# ------------------------------------------------
# @author Adrian Szczepanski
# @date 06-03-2023
# ------------------------------------------------

# Target
tested_library_name := cli

# Directories
project_dir ?= ../..
make_dir := $(project_dir)/make
external_dir := $(project_dir)/external

# Sources 
cxx_sources :=  \
$(wildcard *.cpp) \
$(wildcard utils/*.cpp) \
$(wildcard mock/*.cpp) \
$(wildcard templates/*.cpp) \
$(wildcard model/*.cpp) \
$(wildcard internal/*.cpp) \
$(wildcard internal/io/*.cpp) \
$(wildcard internal/io/container/*.cpp) \

# Includes
cxx_includes := \
-I. \

# Defines
cxx_defs := \

# Append rest of Makefile from template
include $(make_dir)/SoftwareTestLib.mk