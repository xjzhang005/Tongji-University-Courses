`timescale 1ns / 1ns
module DFF(
input ena,
input clk,
input D,
input rst,
output reg Q1,
output reg Q2
);
always @(posedge clk or rst)
begin
if(rst)//清零信号有效
begin 
Q1<=1'b0;
Q2<=1'b1;
end
else//清零信号无效
begin
if(ena)//只有当使能信号有效时才读入
begin
Q1<=D;
Q2<=~D;
end
end
end
endmodule

module pcreg(
input clk, //1 位输入，寄存器时钟信号，上升沿时为 PC 寄存器赋值
input rst, //1 位输入，异步重置信号，高电平时将 PC 寄存器清零
//注：当 ena 信号无效时，rst 也可以重置寄存器
input ena, //1 位输入,有效信号高电平时 PC 寄存器读入 data_in
//的值，否则保持原有输出
input [31:0] data_in, //32 位输入，输入数据将被存入寄存器内部
output reg [31:0] data_out //32 位输出，工作时始终输出 PC 
//寄存器内部存储的值
    );
/*
DFF out0 (ena,clk,data_in[0],rst,data_out[0],s[0]);
DFF out1 (ena,clk,data_in[1],rst,data_out[1],s[1]);
DFF out2 (ena,clk,data_in[2],rst,data_out[2],s[2]);
DFF out3 (ena,clk,data_in[3],rst,data_out[3],s[3]);
DFF out4 (ena,clk,data_in[4],rst,data_out[4],s[4]);
DFF out5 (ena,clk,data_in[5],rst,data_out[5],s[5]);
DFF out6 (ena,clk,data_in[6],rst,data_out[6],s[6]);
DFF out7 (ena,clk,data_in[7],rst,data_out[7],s[7]);
DFF out8 (ena,clk,data_in[8],rst,data_out[8],s[8]);
DFF out9 (ena,clk,data_in[9],rst,data_out[9],s[9]);
DFF out10 (ena,clk,data_in[10],rst,data_out[10],s[10]);
DFF out11 (ena,clk,data_in[11],rst,data_out[11],s[11]);
DFF out12 (ena,clk,data_in[12],rst,data_out[12],s[12]);
DFF out13 (ena,clk,data_in[13],rst,data_out[13],s[13]);
DFF out14 (ena,clk,data_in[14],rst,data_out[14],s[14]);
DFF out15 (ena,clk,data_in[15],rst,data_out[15],s[15]);
DFF out16 (ena,clk,data_in[16],rst,data_out[16],s[16]);
DFF out17 (ena,clk,data_in[17],rst,data_out[17],s[17]);
DFF out18 (ena,clk,data_in[18],rst,data_out[18],s[18]);
DFF out19 (ena,clk,data_in[19],rst,data_out[19],s[19]);
DFF out20 (ena,clk,data_in[20],rst,data_out[20],s[20]);
DFF out21 (ena,clk,data_in[21],rst,data_out[21],s[21]);
DFF out22 (ena,clk,data_in[22],rst,data_out[22],s[22]);
DFF out23 (ena,clk,data_in[23],rst,data_out[23],s[23]);
DFF out24 (ena,clk,data_in[24],rst,data_out[24],s[24]);
DFF out25 (ena,clk,data_in[25],rst,data_out[25],s[25]);
DFF out26 (ena,clk,data_in[26],rst,data_out[26],s[26]);
DFF out27 (ena,clk,data_in[27],rst,data_out[27],s[27]);
DFF out28 (ena,clk,data_in[28],rst,data_out[28],s[28]);
DFF out29 (ena,clk,data_in[29],rst,data_out[29],s[29]);
DFF out30 (ena,clk,data_in[30],rst,data_out[30],s[30]);
DFF out31 (ena,clk,data_in[31],rst,data_out[31],s[31]);*/

wire[31:0] s;
wire [31:0] s1;
DFF out0 (ena,clk,data_in[0],rst,s1[0],s[0]);
DFF out1 (ena,clk,data_in[1],rst,s1[1],s[1]);
DFF out2 (ena,clk,data_in[2],rst,s1[2],s[2]);
DFF out3 (ena,clk,data_in[3],rst,s1[3],s[3]);
DFF out4 (ena,clk,data_in[4],rst,s1[4],s[4]);
DFF out5 (ena,clk,data_in[5],rst,s1[5],s[5]);
DFF out6 (ena,clk,data_in[6],rst,s1[6],s[6]);
DFF out7 (ena,clk,data_in[7],rst,s1[7],s[7]);
DFF out8 (ena,clk,data_in[8],rst,s1[8],s[8]);
DFF out9 (ena,clk,data_in[9],rst,s1[9],s[9]);
DFF out10 (ena,clk,data_in[10],rst,s1[10],s[10]);
DFF out11 (ena,clk,data_in[11],rst,s1[11],s[11]);
DFF out12 (ena,clk,data_in[12],rst,s1[12],s[12]);
DFF out13 (ena,clk,data_in[13],rst,s1[13],s[13]);
DFF out14 (ena,clk,data_in[14],rst,s1[14],s[14]);
DFF out15 (ena,clk,data_in[15],rst,s1[15],s[15]);
DFF out16 (ena,clk,data_in[16],rst,s1[16],s[16]);
DFF out17 (ena,clk,data_in[17],rst,s1[17],s[17]);
DFF out18 (ena,clk,data_in[18],rst,s1[18],s[18]);
DFF out19 (ena,clk,data_in[19],rst,s1[19],s[19]);
DFF out20 (ena,clk,data_in[20],rst,s1[20],s[20]);
DFF out21 (ena,clk,data_in[21],rst,s1[21],s[21]);
DFF out22 (ena,clk,data_in[22],rst,s1[22],s[22]);
DFF out23 (ena,clk,data_in[23],rst,s1[23],s[23]);
DFF out24 (ena,clk,data_in[24],rst,s1[24],s[24]);
DFF out25 (ena,clk,data_in[25],rst,s1[25],s[25]);
DFF out26 (ena,clk,data_in[26],rst,s1[26],s[26]);
DFF out27 (ena,clk,data_in[27],rst,s1[27],s[27]);
DFF out28 (ena,clk,data_in[28],rst,s1[28],s[28]);
DFF out29 (ena,clk,data_in[29],rst,s1[29],s[29]);
DFF out30 (ena,clk,data_in[30],rst,s1[30],s[30]);
DFF out31 (ena,clk,data_in[31],rst,s1[31],s[31]);
always @(*)
begin
data_out=s1;
end
endmodule
