# ------------------------------------------------
# @author Adrian Szczepanski
# @date 06-03-2022
# ------------------------------------------------

# platform
export PLATFORM := Pc32

# project
export project_name := libcli

# sysroot (for cross-compilation)
# export sysroot := 

# Directories
project_dir := .
make_dir := $(project_dir)/make

# Documentation directory
export docs_dir := docs

# External libraries
external_names = \
CppUTest \

external_build_options = \

# Project internal libraries
internal_library_names = \

# Project subprograms
program_names = \
cli-executor \

# Project libraries
library_names = \
cli

# optimalization flags
# export debug_optimalization := 
# export release_optimalization := 

# Append rest of Makefile from template
include $(make_dir)/Main.mk

# Enter the internal library or program dependencies (by directory name)
# 	E.g.: if libproject-a depends on libproject-b write the line above:
#	libproject-a: libproject-b

# Custom targets