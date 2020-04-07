`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/30/2020 02:56:10 PM
// Design Name: 
// Module Name: registerfile
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


module registerfile(rsout, rtout, clk ,wsig, rsin, rtin, rdin, wrtin);
input clk;
input wsig;
input [5:0] rsin, rtin, rdin;
input [31:0] wrtin;
reg [31:0] register [63:0];
output reg [31:0] rsout;
output reg [31:0] rtout;

always@(negedge clk)
begin
if (wsig==1)
    register[rdin]=wrtin;

rsout=register[rsin];
rtout=register[rtin];


end
endmodule
