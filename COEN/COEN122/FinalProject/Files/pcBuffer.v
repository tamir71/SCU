`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Name: Tamir Enkhjargal
// Create Date: 02/13/2020
// Module Name: pcBuffer
//////////////////////////////////////////////////////////////////////////////////

module pcBuffer(clock, in, out);

// Setting up variables: 
input clock;
input [7:0] in;
output reg [7:0] out;

// Run these lines when testing and input changes
always@(negedge clock)
begin
    out = in;
end
endmodule