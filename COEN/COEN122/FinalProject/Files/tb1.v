`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/20/2020 03:00:13 PM
// Design Name: 
// Module Name: instructionfetch
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

module instructionfetch();
reg clk;
reg [7:0] pcin, pcBuffin;
reg [7:0] imemin;
reg d1, d2, d3, d4, d5, d6;
reg [2:0] sel;
reg [2:0] ALUsel;
reg [31:0] A, B;
reg [31:0] instructionIn;
reg [7:0] ifidaddrIn;

wire [7:0] pcout;
wire [7:0] pcBuffout;
wire [7:0] ifidaddrOut;
wire [31:0] ALUout;
wire [31:0] imemout;
wire MUXout, out, zero, neg;
wire [31:0] B_out, A_comp, A_out;
wire [2:0] mux2to1, mux3to1;

programCounter      pc(clk, pcin, pcout);
pcBuffer            pcbuff(clk, pcout, ifidaddrIn);
instructionmemory   imem(clk, pcout, imemout);   //takes pcout always
mux                 pcmux(d1,,,,,,0, pcin); //commas act as empty or 0
 ALUmain             alu(pcout, 1, 4'b0001, d1 , , );
ifid                ifidbuff(ifidaddrIn, clk, imemout, ifidaddrOut, out);

// ControlBlock block1(clk, opcode, RegWrt, MemToReg, PCtoReg,ALUOp, MemRead, MemWrt, BranchNeg, BranchZero, Jump, JumpMem, MemOut);

initial begin
    clk = 0;
    forever #10 clk = ~clk;
end

initial begin
#500;
$finish;
end

endmodule
