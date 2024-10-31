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
