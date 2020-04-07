`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/06/2020 02:55:20 PM
// Design Name: 
// Module Name: exwb
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


module exwb(DataMemory,DataMemoryOut,ALU,ALUOut, clk,N,Z,RegWrt,MemToReg,PCToReg,BranchNeg,BranchZero,Jump,JumpMem,NOut,ZOut,RegWrtOut,MemToRegOut,PCToRegOut,BranchNegOut,BranchZeroOut,JumpOut,JumpMemOut,rd,rdOut,idexalu2Out,exwbalu2Out);


input clk;
input N;
input Z;
input RegWrt;
input MemToReg;
input PCToReg;
input BranchNeg;
input BranchZero;
input Jump;
input JumpMem;
input [5:0] rd;
input [31:0] ALU;
input [31:0]DataMemory;
input [31:0]idexalu2Out;

output reg [31:0]exwbalu2Out;
output reg NOut;
output reg ZOut;
output reg RegWrtOut;
output reg MemToRegOut;
output reg PCToRegOut;
output reg BranchNegOut;
output reg BranchZeroOut;
output reg JumpOut;
output reg JumpMemOut;
output reg  [5:0] rdOut;
output reg [31:0] ALUOut;
output reg [31:0] DataMemoryOut;

always@(posedge clk)
begin
NOut=N;
ZOut=Z;
RegWrtOut=RegWrt;
MemToRegOut=MemToReg;
PCToRegOut=PCToReg;
BranchNegOut=BranchNeg;
BranchZeroOut=BranchZero;
JumpOut=Jump;
JumpMemOut=JumpMem;
rdOut=rd;
ALUOut=ALU;
DataMemoryOut=DataMemory;
exwbalu2Out=idexalu2Out;

end
endmodule





