`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/23/2020 03:46:22 PM
// Design Name: 
// Module Name: twoComp
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


module twoComp( A, out);

input [31:0] A;
output reg [31:0] out;
integer i;

always@ (A)
begin
//for (i=0; i<32; i=i+1)
//begin
//    out[i]= 1 ^ A[i];
//    end
//    i=0;
//while(i<32 && out[i]==1)
//begin
//    out[i]=0;
//    i=i+1;
//    end
//    if (i<32)
//        out[i]=1;
//    end
    
    out = (~A) + 1;
    end
endmodule
