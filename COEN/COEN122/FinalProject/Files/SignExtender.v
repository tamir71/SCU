`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Name: Tamir Enkhjargal
// Create Date: 02/13/2020
// Module Name: signExtender
//////////////////////////////////////////////////////////////////////////////////

module signExtender(dataIn, dataOut);

// Setting up variables: 
input [21:0] dataIn;
output reg [31:0] dataOut;

// Run these lines when testing and input changes
always@(dataIn)
begin
    dataOut[21:0]=dataIn;
    
    if(dataIn[21]==1)
    begin
        dataOut[31:22]=1;
    end
    else
    begin
        dataOut[31:22]=0;
    end
end
endmodule