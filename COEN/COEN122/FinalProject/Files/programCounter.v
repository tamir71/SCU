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
initial begin
    address = 0;
end
always@(negedge clock)
begin
    if(in) begin
    address = in;
    end
end
endmodule