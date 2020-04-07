`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/06/2020 02:29:59 PM
// Design Name: 
// Module Name: idex
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module idex(clk, iRegWrt,iMemToReg,iPCToReg,iBranchNeg,iBranchZero,
iJump,iJumpMem, ALUOP, MemRead,MemWrt,rs,rt,ird, iRegWrtOut, 
iMemToRegOut, iPCToRegOut, iBranchNegOut, iBranchZeroOut,iJumpOut,
 iJumpMemOut, ALUOPOut, MemReadOut,MemWrtOut,rsOut,
 rtOut, irdOut,alu2Out, idexalu2Out);
 
 // idexbuff(clk, ctrlOutRegWrt, ctrlOutMemToReg, ctrlOutPCtoReg, ctrlOutALUOp, ctrlOutMemRead, ctrlOutMemWrt, ctrlOutBranchNeg,
             //           ctrlOutBranchZero, ctrlOutJump, ctrlOutJumpMem, ctrlOutMemOut, regOutrs, regOutrt, ifidInstructionOut[27:22], idexOutRegWrt,idexOutMemToReg,idexOutPCtoReg, idexOutBranchNeg, 
              //          idexOutBranchZero, idexOutJump, idexOutJumpMem, idexOutALUOp, idexOutMemRead, idexOutMemWrt, idexOutrs, idexOutrt, idexOutrd,alu2Out, idexalu2Out);
 
input clk;
input iRegWrt;
input iMemToReg;
input iPCToReg;
input iBranchNeg;
input iBranchZero;
input iJump;
input iJumpMem;
input [3:0]ALUOP;
input MemRead;
input MemWrt;
input [31:0] rs;
input [31:0] rt;
input [5:0] ird;
input [31:0] alu2Out;

output reg [31:0] idexalu2Out;
output reg iRegWrtOut;
output reg iMemToRegOut;
output reg iPCToRegOut;
output reg iBranchNegOut;
output reg iBranchZeroOut;
output reg iJumpOut;
output reg iJumpMemOut;
output reg [3:0] ALUOPOut;
output reg MemReadOut;
output reg MemWrtOut;
output reg [31:0] rsOut;
output reg [31:0] rtOut;
output reg [5:0] irdOut;


always@(posedge clk)
begin
iRegWrtOut= iRegWrt;
iPCToRegOut=iPCToRegOut;
iBranchNegOut=iBranchNeg;
iBranchZeroOut=iBranchZero;
iJumpOut=iJump;
iJumpMemOut=iJumpMem;
ALUOPOut=ALUOP;
MemReadOut=MemRead;
MemWrtOut=MemWrt;
rsOut=rs;
rtOut=rt;
irdOut=ird;
idexalu2Out=alu2Out;


end  
endmodule
