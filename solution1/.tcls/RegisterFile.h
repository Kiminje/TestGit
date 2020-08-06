#include <ap_int.h>

//Fetch Stage
void FetchStage(ap_uint<1> Jump, ap_uint<32> JumpSrc,
		ap_uint<1> Branch, ap_uint<32> BranchSrc,
		struct IF2ID *out);
//Decode Stage
void DispatchStage(static struct IF2ID in, static ap_uint<5> waddr, static ap_uint<32> wdata, static ap_uint<1> wr_reg,
		static struct ID2EX *out, ap_uint<1> *Jump, ap_uint<32> *JumpSrc);
void Control(static ap_uint<6> opcode,
		static ap_uint<10> *out_ctrl);
void RegisterFile(static ap_uint<32> RF[32], static ap_uint<5> rs, static ap_uint<5> rd,
		static ap_uint<5> waddr, static ap_uint<32> wdata,
		static ap_uint<5> *WrRd,	static ap_uint<5> *WrRt, ap_uint<1> wr_sig);
//Execution Stage
void ExecutionStage(struct ID2EX in, struct EX2MEM *out);
void ALUControl(ap_uint<6> funct, ap_uint<2> ALUOp,
		ap_uint<1> Ctrl[3]);
void ALU(ap_uint<32> Src1, ap_uint<32> Src2, ap_uint<1> Ctrl[3],
		ap_uint<1> *Zero, ap_uint<32> *Result);
//Memory Stage
void MemStage(struct EX2MEM in, struct MEM2WB *out,
		ap_uint<1> *PCSrc, ap_uint<32> *BranchSrc );
void MemCache(ap_uint<32> address, ap_uint<32> WriteData,
		ap_uint<2> *Ctrl,
		ap_uint<32> *ReadData);
//WriteBack Stage
void WriteBack(struct MEM2WB in, ap_uint<1> *RegWrite,
		ap_uint<32> *WriteData, ap_uint<5> *WriteAddress);

// 32+32
static typedef struct IF2ID{
	ap_uint<32> counter;
	ap_uint<6> opcode;
	ap_uint<5> rs;
	ap_uint<5> rd;
	ap_uint<5> rt;
	ap_uint<5> shamt;
	ap_uint<6> funct;
};
// 32 + 32 + 32 + 27
static typedef struct ID2EX{
	ap_uint<32> rd1;
	ap_uint<32> rd2;
	ap_int<32> extension;
	ap_uint<32> counter;
	ap_uint<1> control[9];
	ap_uint<5> ra_dst1;
	ap_uint<5> ra_dst2;
};
//5 + 32 + 32 + 32 + 6
static typedef struct EX2MEM{
	ap_uint<1> control[5];
	ap_uint<32> BranchResult;
	ap_uint<1> Zero;
	ap_uint<32> ALUResult;
	ap_uint<32> RdTransfer;
	ap_uint<5> WriteAddress;
};
// 2 + 32 + 32
static typedef struct MEM2WB{
	ap_uint<1> control[2];
	ap_uint<32> MemData;
	ap_uint<32> RegData;
	ap_uint<5> RegAddress;
};
