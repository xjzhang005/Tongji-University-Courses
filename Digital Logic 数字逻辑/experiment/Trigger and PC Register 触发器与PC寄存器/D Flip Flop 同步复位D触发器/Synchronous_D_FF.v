`timescale 1ns / 1ns
module Synchronous_D_FF(
input CLK, //时钟信号，上升沿有效
 input D, //输入信号 D
 input RST_n, //复位信号，低电平有效
 output reg Q1, //输出信号 Q
 output reg Q2//输出信号?~Q
    );
    always @(posedge CLK)//当上升沿来临时
    begin
    if(!RST_n)//如果复位信号有效
    begin
    Q1<=1'b0;
    Q2<=1'b1;
    end
    else //如果复位信号无效
    begin
    Q1<=D;
    Q2<=~D;
    end
    end
endmodule
