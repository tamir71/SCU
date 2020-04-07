`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/23/2020 02:51:58 PM
// Design Name: 
// Module Name: RipCarry
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


module RipCarry(A,B,out, neg, zero);

    input [31:0] A,B;
    
    output  [31:0] out;
    output reg neg, zero;
    wire w0,w1,w2,w3,w5,w6,w7,w8,w9,w10,w11,w12,w13,w14,w15,w16,w17,w18,w19,w20,w21,w22,w23,w24,w25,w26,w27,w28,w29,w30,w31;
    
    FullAddrr add0(A[0],B[0], 1'b0, out[0],w0);
    FullAddrr add1(A[1],B[1], w0, out[1],w1);
    FullAddrr add2(A[2],B[2], w1, out[2],w2);
    FullAddrr add3(A[3],B[3], w2, out[3],w3);
    FullAddrr add4(A[4],B[4], w3, out[4],w4);
    FullAddrr add5(A[5],B[5], w4, out[5],w5);
    FullAddrr add6(A[6],B[6], w5, out[6],w6);
    FullAddrr add7(A[7],B[7], w6, out[7],w7);
    FullAddrr add8(A[8],B[8], w7, out[8],w8);
    FullAddrr add9(A[9],B[9], w8, out[9],w9);
    FullAddrr add10(A[10],B[10], w9, out[10],w10);
    FullAddrr add11(A[11],B[11], w10, out[11],w11);
    FullAddrr add12(A[12],B[12], w11, out[12],w12);
    FullAddrr add13(A[13],B[13], w12, out[13],w13);
    FullAddrr add14(A[14],B[14], w13, out[14],w14);
    FullAddrr add15(A[15],B[15], w14, out[15],w15);
    FullAddrr add16(A[16],B[16], w15, out[16],w16);
    FullAddrr add17(A[17],B[17], w16, out[17],w17);
    FullAddrr add18(A[18],B[18], w17, out[18],w18);
    FullAddrr add19(A[19],B[19], w18, out[19],w19);
    FullAddrr add20(A[20],B[20], w19, out[20],w20);
    FullAddrr add21(A[21],B[21], w20, out[21],w21);
    FullAddrr add22(A[22],B[22], w21, out[22],w22);
    FullAddrr add23(A[23],B[23], w22, out[23],w23);
    FullAddrr add24(A[24],B[24], w23, out[24],w24);
    FullAddrr add25(A[25],B[25], w24, out[25],w25);
    FullAddrr add26(A[26],B[26], w25, out[26],w26);
    FullAddrr add27(A[27],B[27], w26, out[27],w27);
    FullAddrr add28(A[28],B[28], w27, out[28],w28);
    FullAddrr add29(A[29],B[29], w28, out[29],w29);
    FullAddrr add30(A[30],B[30], w29, out[30],w30);
    FullAddrr add31(A[31],B[31], w30, out[31],w31);
    integer i;
 
    always@(out)
    begin
//    zero=0;
//    for ( i=0; i<32; i=i+1)
//    begin
//        zero= zero + out[i];
//    end
//    if(zero== 0)
//        zero=1;
//    else
//    zero=0;

    if(out==zero)
        zero = 1;
    else
        zero = 0;
    
    if(out[31]==1)
        neg=1;
    else 
        neg=0;
    end
    
endmodule
