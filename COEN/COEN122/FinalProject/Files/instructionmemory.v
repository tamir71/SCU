`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/30/2020 02:29:04 PM
// Design Name: 
// Module Name: instructionmemory
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


module instructionmemory(clock,addr,out);
input clock;
input [7:0] addr;
output reg [31:0] out;
wire [31:0] instruction[255:0];
assign instruction[0]=20;
always@(negedge clock) 
begin
out= instruction[addr];

end
endmodule
