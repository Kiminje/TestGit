/*
 * in execution stage,
 * Input : control[9], rt[5], rd[5], sign extension[32],
 * 			Rdata1[32], Rdata2[32]
 *
 * Output : control[5],
 *  control[9] = RegWrite, RegDst, AluSrc, Branch, MemRead,
 *  MemWrite, Mem2Reg, ALUOp[2]
 *  control[5] = RegWrite, Branch, MemRead, MemWrite, Mem2Reg
 */
#include <ap_int.h>
#include "RegisterFile.h"
#define ZEROMSK 0x00000000

void ExecutionStage(struct ID2EX in, struct EX2MEM *out){
	//wiring
	 out->BranchResult = in.counter+in.extension<< 2;
	 ap_uint<32> Src2 = in.control[6]?in.extension:in.rd2; //AluSrc
	 out->RdTransfer = in.rd2;
	 ap_uint<6> funct = in.extension(5,0);
	 out->WriteAddress = in.control[7]? in.ra_dst2: in.ra_dst1; // RegDst
	 out->control = (in.control[8], in.control(5,2));
	 //module
	 ap_uint<2> ALUOp = in.control(1,0);
	 ap_uint<1> ALUCtrl[3] = ALUControl(funct, ALUOp, ALUCtrl);
	 ALU(in.rd1, Src2, ALUCtrl, &out->Zero, &out->ALUResult);

}

void ALUControl(ap_uint<6> funct, ap_uint<2> ALUOp,
		ap_uint<1> Ctrl[3]){
	switch(ALUOp){
	case 0b00: *Ctrl = 0b010;break; //add
	case 0b01: *Ctrl = 0b110;break; //sub
	default:switch(funct){
	case 0b100000: *Ctrl = 0b010;break;	//add
	case 0b100010: *Ctrl = 0b110;break; // sub
	case 0b100100: *Ctrl = 0b000;break; // and
	case 0b100101: *Ctrl = 0b001;break;// or
	case 0b101011: *Ctrl = 0b111;break;// sltu
	default: *Ctrl = 0; // xxx
	}
	}
}

void ALU(ap_uint<32> Src1, ap_uint<32> Src2, ap_uint<1> Ctrl[3],
		ap_uint<1> *Zero, ap_uint<32> *Result){
	ap_uint<32> Sel1 = Ctrl[2]? ~Src2 : Src2;
	ap_uint<32> AND = Src1 & Sel1;
	ap_uint<32> OR = Src1 | Sel1;
	ap_uint<1> Carry; ap_uint<32> ADD;
	(Carry, ADD)= Sel1 + Src1 + Ctrl[2];
	ap_uint<32> SLTU = ZEROMSK | ~Carry;
	switch(Ctrl(1,0)){
	case 0b00: *Result = AND;break;
	case 0b01: *Result = OR;break;
	case 0b10: *Result = ADD;break;
	case 0b11: *Result = SLTU;break;
	}
}
