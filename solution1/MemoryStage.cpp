/*
 * StageInput : struct EX2MEM
 * MemoryInput :
 * control[5] = RegWrite, Branch, MemRead, MemWrite, Mem2Reg
 * control[2] = RegWrite, Mem2Reg
 */
#include "RegisterFile.h"

void MemStage(struct EX2MEM in, struct MEM2WB *out,
		ap_uint<1> *PCSrc, ap_uint<32> *BranchSrc ){
	*PCSrc = in.Zero & in.control[3];
	*BranchSrc = in.BranchResult;
	ap_uint<2> *Ctrl = &(in.control(1,0));
	ap_uint<32> *ReadData = out->MemData;
	out->RegData = in.ALUResult;
	out->RegAddress = in.WriteAddress;
	out->control = in.control(4,3);
	MemCache(in.ALUResult, in.RdTransfer, Ctrl, ReadData);
}

void MemCache(ap_uint<32> address, ap_uint<32> WriteData,
		ap_uint<2> *Ctrl,
		ap_uint<32> *ReadData){
	static ap_uint<32> Memory[32]; // memory allocation
	if(Ctrl[1])*ReadData = Memory[address];
	if(Ctrl[0])Memory[address] = WriteData;
}
