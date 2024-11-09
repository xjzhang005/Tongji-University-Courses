`timescale 1ns / 1ns
`timescale 1ns / 1ns
module FA(
input iA, //1 位二进制加数
 input iB, //1 位二进制被加数
 input iC, //低位的进位信号
 output oS, //1 位和数
 output oC //向高位的进位信号
    );
    assign oS=iA^iB^iC;
    assign oC=iA&iB|iA&iC|iB&iC;
endmodule

module Adder(
input [7:0] iData_a, //8 位二进制加数
 input [7:0] iData_b, //8 位二进制被加数
input iC, //低位的进位信号
 output [7:0] oData, //8 位和数
 output oData_C //向高位的进位信号
    );
    wire iC0;
   FA bit1(iData_a[0],iData_b[0],iC,oData[0],iC0);
    wire iC1;
    FA bit2(iData_a[1],iData_b[1],iC0,oData[1],iC1);
    wire iC2;
    FA bit3(iData_a[2],iData_b[2],iC1,oData[2],iC2);
    wire iC3;
    FA bit4(iData_a[3],iData_b[3],iC2,oData[3],iC3);
    wire iC4;
    FA bit5(iData_a[4],iData_b[4],iC3,oData[4],iC4);
    wire iC5;
    FA bit6(iData_a[5],iData_b[5],iC4,oData[5],iC5);
    wire iC6;
    FA bit7(iData_a[6],iData_b[6],iC5,oData[6],iC6);

    FA bit8(iData_a[7],iData_b[7],iC6,oData[7],oData_C);
    
endmodule
