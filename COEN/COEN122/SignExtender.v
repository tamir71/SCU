`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Name: Tamir Enkhjargal
// Create Date: 02/13/2020
// Module Name: signExtender
//////////////////////////////////////////////////////////////////////////////////

module signExtender(dataIn, dataOut);

// Setting up variables: 
input [31:0] dataIn;
output reg [63:0] dataOut;

// Run these lines when testing and input changes
always@(dataIn)
begin
    dataOut[63:0] <= { {32{dataIn[31]}}, dataIn[31:0] };
end
endmodule