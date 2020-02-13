`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Name: Tamir Enkhjargal
// Create Date: 02/13/2020
// Module Name: programCounter
//////////////////////////////////////////////////////////////////////////////////

module programCounter(clock, in, address);

// Setting up variables: 
input clock;
input [7:0] in;
output reg [7:0] address;

// Run these lines when testing and input changes
always@(posedge clock)
begin
    address = in;
end
endmodule