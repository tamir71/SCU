`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/13/2020 02:40:39 PM
// Design Name: 
// Module Name: LogicGates
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


module LogicGates(nOut,BranchNeg,zOut,Jump,BranchZero, logicOut);
input BranchNeg;
input Jump;
input BranchZero;
input nOut;
input zOut;

output reg logicOut;


always@(BranchNeg,Jump,BranchZero,nOut,zOut)
begin
logicOut=(nOut && BranchNeg) || (zOut && BranchZero) || Jump;
end
endmodule



