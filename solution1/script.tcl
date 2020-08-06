############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project HLS_MIPS_module_RF
set_top CPU
add_files HLS_MIPS_module_RF/solution1/Execution.cpp
add_files HLS_MIPS_module_RF/solution1/.autopilot/FetchStage.cpp
add_files HLS_MIPS_module_RF/solution1/MemoryStage.cpp
add_files HLS_MIPS_module_RF/solution1/MipsProcessor.cpp
add_files HLS_MIPS_module_RF/solution1/.tcls/RegisterFile.h
add_files HLS_MIPS_module_RF/solution1/RegisterFlie.cpp
add_files HLS_MIPS_module_RF/solution1/WriteBack.cpp
open_solution "solution1"
set_part {xcu200-fsgd2104-2-e}
create_clock -period 10 -name default
#source "./HLS_MIPS_module_RF/solution1/directives.tcl"
#csim_design
csynth_design
#cosim_design
export_design -format ip_catalog
