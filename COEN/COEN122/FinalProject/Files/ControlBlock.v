`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/13/2020 03:01:51 PM
// Design Name: 
// Module Name: ControlBlock
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


module ControlBlock(clk,opcode,RegWrt, MemToReg, PCtoReg,ALUOp, MemRead, MemWrt,
 BranchNeg, BranchZero, Jump, JumpMem, MemOut);
input [3:0] opcode;
input clk;
output reg RegWrt;
output reg MemToReg;
output reg PCtoReg;
output reg [3:0]ALUOp;
output reg MemRead;
output reg MemWrt;
output reg BranchNeg;
output reg BranchZero;
output reg Jump;
output reg JumpMem;

output reg [6:0]MemOut;

always@(negedge clk)

begin
RegWrt=0;
MemToReg=0;
PCtoReg=0;
ALUOp=4'b0100;
MemRead=0;
MemWrt=0;
BranchNeg=0;
BranchZero=0;
Jump=0;
JumpMem=0;

//NOP keep everything @ zero

//SavePC
if(opcode==4'b1111)
    begin
    ALUOp=4'b0011;
    RegWrt=1;
    MemToReg=1;
    PCtoReg=1;
    MemRead=1;
    end
//Load
else if(opcode==4'b1110)
    begin
    RegWrt=1;
    MemToReg=1;
    PCtoReg=1;
    MemRead=1;
    end

//Store
else if (opcode==4'b0011)
    begin
    MemToReg=1;
    MemWrt=1;
    end

//Add
else if(opcode==4'b0100)
    begin
    ALUOp=4'b0000;
    RegWrt=1;
    end
//Increment
else if(opcode==4'b0101)
    begin
    RegWrt=1;
    ALUOp=4'b0010;
    end
//Negate
else if(opcode==4'b0110)
    begin
    RegWrt=1;
    ALUOp=4'b0010;
    end
//Subtract
else if(opcode==4'b0111)
    begin
    RegWrt=1;
    ALUOp=4'b0011;
    end
//Jump
else if(opcode==4'b1000)
    begin
    Jump=1;
    end
//BranchifZero
else if(opcode==4'b1001)
    begin
    BranchZero=1;
    end
//JumpMemory
else if(opcode==4'b1010)
    begin
    MemRead=1;
    JumpMem=1;
    end
//BranchifNegitive
else if(opcode==4'b1011)
    begin
    BranchNeg=1;
    end
//MAX
else if(opcode==4'b0001)
    begin
    RegWrt=1;
    MemRead=1;
    end
end

endmodule