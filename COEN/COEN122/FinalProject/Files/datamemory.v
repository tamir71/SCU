`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/30/2020 02:55:10 PM
// Design Name: 
// Module Name: datamemory
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


module datamemory(clk,writesig,readsig,writeto,datain,dataout);
input clk;
input writesig;
input readsig;


input [31:0] datain;
input [31:0] writeto;
output reg [31:0] dataout;
reg [31:0] mem [65535:0];

always@(negedge clk)
begin
if (readsig==1)
begin
    dataout=mem[writeto[15:0]];
end

if(writesig==1)
begin
mem[writeto[15:0]]=datain;
end



end
endmodule

