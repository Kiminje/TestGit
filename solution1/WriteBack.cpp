/*	Input = MEM/WB
 * 	Output = RegWrite, WriteAddress, WriteData
 * control[2] = RegWrite, Mem2Reg
 */
#include "RegisterFile.h"

void WriteBack(struct MEM2WB in,
		ap_uint<1> *RegWrite, ap_uint<32> *WriteData, ap_uint<5> *WriteAddress){

	*WriteData = (in.control[0])?in.MemData: in.RegData;
	*WriteAddress = in.RegAddress;
	*RegWrite = in.control[1];

}
