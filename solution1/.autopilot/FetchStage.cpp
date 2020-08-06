#include "RegisterFile.h"

void FetchStage(ap_uint<1> Jump, ap_uint<32> JumpSrc,
		ap_uint<1> Branch, ap_uint<32> BranchSrc,
		struct IF2ID *out){
	static ap_uint<32> InsMemory[32];
	static ap_uint<32> ProgramCounter;
	out(31, 0) = InsMemory[ProgramCounter];
	ap_uint<32> PCAdd = ProgramCounter +4;
	ProgramCounter = (Jump)? JumpSrc : ((Branch)? BranchSrc : PCAdd);
	out->counter = PCAdd;


}
