`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/27/2020 04:06:31 PM
// Design Name: 
// Module Name: ALUmain
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


module ALUmain(A,B,operation, out, zero, neg);
input [31:0] A, B;
input [2:0] operation;
output [31:0] out;
output zero, neg;
wire [31:0] B_out, A_comp, A_out;
reg [2:0] mux2to1;
reg[2:0] mux3to1;

SixToOneMux mux(B,0,0,0,0,0, mux2to1, B_out);

twoComp twos(A, A_comp);

SixToOneMux mux2(A,1,A_comp,0,0,0,mux3to1,A_out);

RipCarry rip(A_out, B_out,out,neg,zero);

always@(operation,A,B)
begin
    if(operation==4'b0000)  // Add
    begin
    mux2to1 = 3'b000;
    mux3to1 = 3'b000;
    end
    if(operation==4'b0001)  // Increment
    begin
    mux2to1 = 3'b000;
    mux3to1 = 3'b001;
    end
    if(operation==4'b0010)  // Negate
    begin
    mux2to1 = 3'b001;
    mux3to1 = 3'b010;
    end
    if(operation==4'b0011)  // Subtract
    begin
    mux2to1 = 3'b000;
    mux3to1 = 3'b010;
    end
    if(operation==4'b0100)  // Pass A
    begin
    mux2to1 = 3'b001; 
    mux3to1 = 3'b000;
    end
end
endmodule