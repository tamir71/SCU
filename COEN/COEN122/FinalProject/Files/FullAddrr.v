`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/28/2020 11:16:46 AM
// Design Name: 
// Module Name: FullAddrr
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


module FullAddrr(A, B, Cin, sum, Cout);

input A, B, Cin;

output reg sum, Cout;

always@(A,B,Cin)
begin
    sum= A^B^Cin;
    Cout= (A&B) | (A&Cin) | (B&Cin);
    end
    
endmodule