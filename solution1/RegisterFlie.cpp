#include <ap_int.h>
#include <stdio.h>
#include "RegisterFile.h"
typedef ap_uint<8> PC;
#define IF2IDSIZE 32
#define LSBMSK 0b0000000001



//void Control(static ap_uint<6>, static ap_uint<5>, static ap_uint<6> );
//void RegisterFile(static ap_uint<5>, static ap_uint<5>, static ap_uint<5>, ap_uint<32>, ap_uint<32>, ap_uint<32>, ap_uint<1>);
void DispatchStage(static struct IF2ID in, static ap_uint<5> waddr, static ap_uint<32> wdata, static ap_uint<1> wr_reg,
		static struct ID2EX *out, ap_uint<1> *Jump, ap_uint<32> *JumpSrc){
	ap_uint<32> RF[32];
	out->counter = in.counter;
	out->ra_dst1 = in.rd;
	out->ra_dst2 = in.rt;
	out->extension = (in.rt, in.shamt, in.funct);
	ap_uint<5> *WrRd = &(out->rd1);
	ap_uint<5> *WrRt = &(out->rd2);
	RegisterFile(RF, in.rs, in.rd, waddr, wdata,
			WrRd, WrRt, wr_reg);
	//need array partition
	ap_uint<10> *Ctrl;
	Control(in.opcode, Ctrl);
	ap_uint<28> JumpImm = in(25,0) << 2;
	(out->control, *Jump) = *Ctrl;
	*JumpSrc = (in.counter(31,28), JumpImm);
}


void RegisterFile(static ap_uint<32> RF[], static ap_uint<5> rs, static ap_uint<5> rd, static ap_uint<5> waddr, static ap_uint<32> wdata,
		static ap_uint<5> *WrRd,	static ap_uint<5> *WrRt, ap_uint<1> wr_sig){
	*WrRd = RF[rs];
	*WrRt = RF[rd];
	if(wr_sig){
		RF[waddr] = wdata;
	}
}

/*
 * input opcode, main decoder decodes opcode to 6bit length control signal for output control[8:3]
 * ALU decoder decodes alu signal[1:0] and funct to output ALU control[2:0] at execution stage
 * control[10] = RegWrite, RegDst, AluSrc, Branch,MemRead,
 *  MemWrite, Mem2Reg, ALUOp[2], Jump
 *  control[9] = RegWrite, RegDst, AluSrc, Branch, MemRead,
 *  MemWrite, Mem2Reg, ALUOp[2]
 */
void Control(static ap_uint<6> opcode, static ap_uint<1> control[10]){
#pragma HLS INTERFACE ap_ctrl_none
	switch(opcode){
	case 0b000000: *control = 0b1100000100;	break; // R-type
	case 0b100011: *control = 0b1010101000;	break;//lw
	case 0b101011: *control = 0b0010010000; break;// sw
	case 0b000100: *control = 0b0000100010; break;// beq
	case 0b001000: *control = 0b1010000000; break;// addi
	case 0b000010: *control = 0b0000000001; break;// j
	default: *control = 0b0000000000; // ???
	}
}





