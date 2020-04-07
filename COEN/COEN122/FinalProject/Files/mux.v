`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/16/2020 02:26:09 PM
// Design Name: 
// Module Name: mux
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


module mux(d1, d2, d3, d4, d5, d6, sel, out);
input [31:0] d1, d2, d3, d4, d5, d6;

input[2:0] sel;

output reg [31:0] out;

always@(d1,d2, d3, d4, d5, d6, sel)
begin

    if( sel==3'b000)
        out=d1;
    else if (sel==3'b001)
        out=d2;
    else if(sel==3'b010)
        out=d3;
    else if(sel==3'b011)
        out=d4;
    else if (sel==3'b100)
        out=d5;
    else if (sel==3'b101)
        out=d6;
end
    
endmodule
