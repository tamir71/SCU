`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/06/2020 02:21:02 PM
// Design Name: 
// Module Name: ifid
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


module ifid(addr,clk,instruction, addrOut,instructionOut);

input [7:0]addr;
input clk;
input [31:0]instruction;

output reg [7:0]addrOut;
output reg [31:0]instructionOut;


always@(posedge clk)
begin

addrOut=addr;
instructionOut= instruction;

end
endmodule
