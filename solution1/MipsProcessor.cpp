/*
 * global port = jump + src, branch + src, regwrite, writeaddress, writedata
 *
 */
#include "RegisterFile.h"

void CPU(){
	static struct IF2ID IF2ID;
	static struct ID2EX ID2EX;
	static struct EX2MEM EX2MEM;
	static struct MEM2WB MEM2WB;

	ap_uint<1> Jump, Branch, RegWrite;
	ap_uint<5> WriteAddress;
	ap_uint<32> WriteData, JumpSrc, BranchSrc;

	FetchStage(Jump, JumpSrc, Branch, BranchSrc, &IF2ID);
	DispatchStage(IF2ID, WriteAddress, WriteData, RegWrite,
			&ID2EX, &Jump, &JumpSrc);
	ExecutionStage(ID2EX, &EX2MEM);
	MemStage(EX2MEM, &MEM2WB, &Branch, &BranchSrc);
	WriteBack(MEM2WB, &RegWrite, &WriteData, &WriteAddress);


}
