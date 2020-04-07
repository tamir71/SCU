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

// Clock
reg clk;

// Program Counter Wires in
wire [7:0] pcin, pcout;

// Instruction Memory Wires
wire [31:0] imemout;

// PC ALU/Increment Wires
wire [31:0] pcAdderOut;

// PC Mux Wires
wire [2:0] sel;
wire [2:0] ALUsel;
wire [31:0] A, B;
wire [31:0] exwbmuxOut;

// PC Buffer Wires
wire [7:0] pcBuffout;

// IF/ID Buffer Wires
wire [7:0] ifidaddrIn, ifidaddrOut;

wire [31:0] ALUout;
wire [31:0] ifidInstructionOut;
wire MUXout, zero, neg;
wire [31:0] B_out, A_comp, A_out;
wire [2:0] mux2to1, mux3to1;

// Sign Extender Wires
wire [31:0] seOut;

// ALU2 Wires
wire [31:0] alu2Out;

// Control Block Wires
wire ctrlOutRegWrt, ctrlOutMemToReg, ctrlOutPCtoReg, ctrlOutMemRead, ctrlOutMemWrt, 
ctrlOutBranchNeg, ctrlOutBranchZero, ctrlOutJump, ctrlOutJumpMem, ctrlOutMemOut;
wire [3:0] ctrlOutALUOp;

// Register File Wires
wire [31:0] regOutrs, regOutrt;

// ID/EX Buffer Wires
wire idexOutRegWrt, idexOutMemToReg, idexOutPCtoReg, idexOutMemRead, idexOutMemWrt, idexOutBranchNeg, idexOutBranchZero, idexOutJump, idexOutJumpMem, idexOutMemOut;
wire [3:0] idexOutALUOp;
wire [5:0] idexOutrd;
wire [31:0] idexOutrs, idexOutrt;

// Data Memory Wires
wire [31:0] dataOut;

// ALU 3 Wires
wire ALU3NOut, ALU3ZOut;
wire [31:0] ALU3Out;

// EX/WB Buffer Wires
wire exwbOutN, exwbOutZ, exwbOutRegWrt, exwbOutMemtoReg, exwbOutPCtoReg, exwbOutBranchNeg, exwbOutBranchZero, exwbOutJump, exwbOutJumpMem;
wire [5:0] exwbOutrd;
wire [31:0] exwbDataOut, exwbALU3Out;
wire [31:0] idexalu2Out, exwbalu2Out;

// Logic Gate Wires
wire logicOut;

programCounter      pc(clk, pcin[7:0], pcout);
pcBuffer            pcbuff(clk, pcout, pcBuffout);
instructionmemory   imem(clk, pcout, imemout);
mux                 pcmux(pcAdderOut,,,,,,0, pcin);
ALUmain             alu1({24'b0, pcout}, 1, 4'b0000, pcAdderOut,,);
ifid                ifidbuff(ifidaddrIn, clk, imemout, ifidaddrOut, ifidInstructionOut);
ControlBlock        block1(clk, ifidInstructionOut[31:28], ctrlOutRegWrt, ctrlOutMemToReg, ctrlOutPCtoReg, ctrlOutALUOp, ctrlOutMemRead, ctrlOutMemWrt,
                        ctrlOutBranchNeg, ctrlOutBranchZero, ctrlOutJump, ctrlOutJumpMem, ctrlOutMemOut);
registerfile        reg1(regOutrs, regOutrt, clk, exwbOutRegWrt, ifidInstructionOut[21:16], ifidInstructionOut[15:10], exwbmuxOut, exwbOutrd);// [Need to implement MUX before completing]
signExtender        sgext(ifidInstructionOut[21:0], seOut);
ALUmain             alu2({24'b0, pcBuffout}, seOut, 4'b0000, alu2Out, , );
idex                idexbuff(clk, ctrlOutRegWrt, ctrlOutMemToReg, ctrlOutPCtoReg, ctrlOutALUOp, ctrlOutMemRead, ctrlOutMemWrt, ctrlOutBranchNeg,
                        ctrlOutBranchZero, ctrlOutJump, ctrlOutJumpMem, ctrlOutMemOut, regOutrs, regOutrt, ifidInstructionOut[27:22], idexOutRegWrt,idexOutMemToReg,idexOutPCtoReg, idexOutBranchNeg, 
                        idexOutBranchZero, idexOutJump, idexOutJumpMem, idexOutALUOp, idexOutMemRead, idexOutMemWrt, idexOutrs, idexOutrt, idexOutrd,alu2Out, idexalu2Out);
datamemory          datamem(clk, idexOutMemWrt, idexOutMemRead, idexOutrs, idexOutrt, dataOut);
ALUmain             alu3(idexOutrs,idexOutrt,idexOutALUOp,ALU3Out,ALU3ZOut,ALU3NOut);//A,B,operation, out, zero, neg); [Not sure which A,B, and ops to use]
exwb                exwbbuff(dataOut, exwbDataOut, ALU3Out, exwbALU3Out, clk, ALU3NOut, ALU3ZOut, idexOutRegWrt, idexOutMemToReg, idexOutPCtoReg, idexOutBranchNeg,
                        idexOutBranchZero, idexOutJump, idexOutJumpMem, exwbOutN, exwbOutZ, exwbOutRegWrt, exwbOutMemtoReg, exwbOutPCtoReg,
                        exwbOutBranchNeg, exwbOutBranchZero, exwbOutJump, exwbOutJumpMem, idexOutrd, exwbOutrd, idexalu2Out ,exwbalu2Out);
mux                 writemux(exwbALU3Out,exwbDataOut, exwbalu2Out,{exwbOutPCtoReg,exwbOutMemtoReg},,,exwbmuxOut);  //d1, d2, d3, d4, d5, d6, sel, out); [Not sure which Outputs to allow and selects]
LogicGates          logicgate(exwbOutN, exwbOutBranchNeg, exwbOutZ, exwbOutJump, exwbOutBranchZero, logicOut);

initial begin
    clk = 0;
    forever #10 clk = ~clk;
end

initial begin
    #500;
    $finish;
end

endmodule


/*
LDPC    $1,  0x0FF = 
32'b11110000010000000000000011111111;

NOP =  
32'b00000000000000000000000000000000;

INC $r2,    $r1 = 
32'b01010000100000010000000000000000;

NEG $r3,    $r1 = 
32'b01100000110000010000000000000000;

LDCPC   $r10,   label1 = 
32'b11110010100000000000000000001000;

NOP = 
32'b00000000000000000000000000000000;

NOP = 
32'b00000000000000000000000000000000;

BRN $10 = 
32'b10110000000010100000000000000000;

NOP = 
32'b00000000000000000000000000000000;

INC $r2,    $r2=
32'b01010000100000100000000000000000;

ST  $r1,    $r1 =
32'b00110000000000010000010000000000;

NOP = 
32'b00000000000000000000000000000000;

NOP = 
32'b00000000000000000000000000000000;

LD  $r4,    $r1= 
32'b11100001000000010000000000000000;

NOP = 
32'b00000000000000000000000000000000;

NOP = 
32'b00000000000000000000000000000000;

ADD $r5 $r1 = 
32'b01000001010000010000100000000000;

SUB $r6,    $r4= 
32'b01110001100001000000010000000000;

LDPC    $11,    label2= 
32'b11110010110000000000000000001000;

NOP = 
32'b00000000000000000000000000000000;

NOP = 
32'b00000000000000000000000000000000;

BRZ $r11 = 
32'b10010000000010110000000000000000;

NOP = 
32'b00000000000000000000000000000000;

NOP = 
32'b00000000000000000000000000000000;

 [28] = 32'b01010000100000100000000000000000;




*/