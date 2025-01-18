`timescale 1ns / 1ns
//32位的地址译码器
module decoder(
input we,
input [4:0] waddr,
output [31:0] position
    );
    assign position=(we==0)?32'b0:
                    (we==1&&waddr==0)?32'h00000001:
                    (we==1&&waddr==1)?32'h00000002:
                    (we==1&&waddr==2)?32'h00000004:
                    (we==1&&waddr==3)?32'h00000008:
                    (we==1&&waddr==4)?32'h00000010:
                    (we==1&&waddr==5)?32'h00000020:
                    (we==1&&waddr==6)?32'h00000040:
                    (we==1&&waddr==7)?32'h00000080:
                    (we==1&&waddr==8)?32'h00000100:
                    (we==1&&waddr==9)?32'h00000200:
                    (we==1&&waddr==10)?32'h00000400:
                    (we==1&&waddr==11)?32'h00000800:
                    (we==1&&waddr==12)?32'h00001000:
                    (we==1&&waddr==13)?32'h00002000:
                    (we==1&&waddr==14)?32'h00004000:
                    (we==1&&waddr==15)?32'h00008000:
                    (we==1&&waddr==16)?32'h00010000:
                    (we==1&&waddr==17)?32'h00020000:
                    (we==1&&waddr==18)?32'h00040000:
                    (we==1&&waddr==19)?32'h00080000:
                    (we==1&&waddr==20)?32'h00100000:
                    (we==1&&waddr==21)?32'h00200000:
                    (we==1&&waddr==22)?32'h00400000:
                    (we==1&&waddr==23)?32'h00800000:
                    (we==1&&waddr==24)?32'h01000000:
                    (we==1&&waddr==25)?32'h02000000:
                    (we==1&&waddr==26)?32'h04000000:
                    (we==1&&waddr==27)?32'h08000000:
                    (we==1&&waddr==28)?32'h10000000:
                    (we==1&&waddr==29)?32'h20000000:
                    (we==1&&waddr==30)?32'h40000000:
                    32'h80000000;//(we==1&&waddr==31)
endmodule
//32选1的数据选择器
module selector321(
input [31:0] idata0,//这里是32位的输入数据
input [31:0] idata1,
input [31:0] idata2,
input [31:0] idata3,
input [31:0] idata4,
input [31:0] idata5,
input [31:0] idata6,
input [31:0] idata7,
input [31:0] idata8,
input [31:0] idata9,                    
input [31:0] idata10,
input [31:0] idata11,
input [31:0] idata12,
input [31:0] idata13,
input [31:0] idata14,
input [31:0] idata15,
input [31:0] idata16,
input [31:0] idata17,
input [31:0] idata18,
input [31:0] idata19,
input [31:0] idata20,
input [31:0] idata21,
input [31:0] idata22,
input [31:0] idata23,
input [31:0] idata24,
input [31:0] idata25,
input [31:0] idata26,
input [31:0] idata27,
input [31:0] idata28,
input [31:0] idata29,
input [31:0] idata30,
input [31:0] idata31,
input [4:0] raddr,
input notwe,//we为1时需要进行写操作，不需要读，也就是说当notwe=0时，不需要有正确的输出，输出z即可
            //we为0时需要进行读操作，不需要写，也就是说当notwe=1时，需要正确输出
output [31:0] odata
    );
    assign odata=(notwe==0)?32'bz:
                 (notwe==1&&raddr==0)?idata0:
                 (notwe==1&&raddr==1)?idata1:
                 (notwe==1&&raddr==2)?idata2:
                 (notwe==1&&raddr==3)?idata3:
                 (notwe==1&&raddr==4)?idata4:
                 (notwe==1&&raddr==5)?idata5:
                 (notwe==1&&raddr==6)?idata6:
                 (notwe==1&&raddr==7)?idata7:
                 (notwe==1&&raddr==8)?idata8:
                 (notwe==1&&raddr==9)?idata9:
                 (notwe==1&&raddr==10)?idata10:
                 (notwe==1&&raddr==11)?idata11:
                 (notwe==1&&raddr==12)?idata12:
                 (notwe==1&&raddr==13)?idata13:
                 (notwe==1&&raddr==14)?idata14:
                 (notwe==1&&raddr==15)?idata15:       
                 (notwe==1&&raddr==16)?idata16:
                 (notwe==1&&raddr==17)?idata17:
                 (notwe==1&&raddr==18)?idata18:
                 (notwe==1&&raddr==19)?idata19:
                 (notwe==1&&raddr==20)?idata20:
                 (notwe==1&&raddr==21)?idata21:
                 (notwe==1&&raddr==22)?idata22:
                 (notwe==1&&raddr==23)?idata23:  
                 (notwe==1&&raddr==24)?idata24:
                 (notwe==1&&raddr==25)?idata25:
                 (notwe==1&&raddr==26)?idata26:
                 (notwe==1&&raddr==27)?idata27:
                 (notwe==1&&raddr==28)?idata28:
                 (notwe==1&&raddr==29)?idata29:
                 (notwe==1&&raddr==30)?idata30:
                 idata31;//(notwe==1&&raddr==31)                       
endmodule
//32位的异步寄存器
//这里先需要D触发器
//因为是下降沿赋值，所以需要进行改变
module DFF(
input ena,
input clk,
input D,
input rst,
output reg Q1,
output reg Q2
);
always @(negedge clk or rst)//这里是新改变的部分，实现下降沿赋值
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
//32位的异步寄存器
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

module Regfiles(
input clk, //寄存器组时钟信号，下降沿写入数据
input rst, //reset 信号，异步复位，高电平时全部寄存器置零
 input we, //寄存器读写有效信号，高电平时允许寄存器写入数据，低电平时允许寄存器读出数据
input [4:0] raddr1, //所需读取的寄存器的地址
input [4:0] raddr2, //所需读取的寄存器的地址
input [4:0] waddr, //写寄存器的地址
input [31:0] wdata, //写寄存器数据，数据在 clk 下降沿时被写入
 output [31:0] rdata1, //raddr1 所对应寄存器的输出数据
output [31:0] rdata2 //raddr2 所对应寄存器的输出数据
    );
    //将上述器件链接好即可
    wire [31:0]position;//用来存放地址信号
    wire [31:0]midout[31:0];//这个二维数组用来存放寄存器输出的结果
    decoder myaddr(we,waddr,position);
    //下面是32个32位寄存器的实例化
    pcreg myreg0 (clk,rst,position[0],wdata,midout[0]);
    pcreg myreg1(clk,rst,position[1],wdata,midout[1]);
    pcreg myreg2 (clk,rst,position[2],wdata,midout[2]);
    pcreg myreg3 (clk,rst,position[3],wdata,midout[3]);
    pcreg myreg4 (clk,rst,position[4],wdata,midout[4]);
    pcreg myreg5 (clk,rst,position[5],wdata,midout[5]);
    pcreg myreg6 (clk,rst,position[6],wdata,midout[6]);
    pcreg myreg7 (clk,rst,position[7],wdata,midout[7]);
    pcreg myreg8 (clk,rst,position[8],wdata,midout[8]);
    pcreg myreg9 (clk,rst,position[9],wdata,midout[9]);
    pcreg myreg10 (clk,rst,position[10],wdata,midout[10]);
    pcreg myreg11(clk,rst,position[11],wdata,midout[11]);
    pcreg myreg12 (clk,rst,position[12],wdata,midout[12]);
    pcreg myreg13 (clk,rst,position[13],wdata,midout[13]);
    pcreg myreg14 (clk,rst,position[14],wdata,midout[14]);
    pcreg myreg15 (clk,rst,position[15],wdata,midout[15]);
    pcreg myreg16(clk,rst,position[16],wdata,midout[16]);
    pcreg myreg17 (clk,rst,position[17],wdata,midout[17]);
    pcreg myreg18 (clk,rst,position[18],wdata,midout[18]);
    pcreg myreg19 (clk,rst,position[19],wdata,midout[19]);
    pcreg myreg20 (clk,rst,position[20],wdata,midout[20]);
    pcreg myreg21(clk,rst,position[21],wdata,midout[21]);
    pcreg myreg22 (clk,rst,position[22],wdata,midout[22]);
    pcreg myreg23 (clk,rst,position[23],wdata,midout[23]);
    pcreg myreg24 (clk,rst,position[24],wdata,midout[24]);
    pcreg myreg25 (clk,rst,position[25],wdata,midout[25]);
    pcreg myreg26(clk,rst,position[26],wdata,midout[26]);
    pcreg myreg27 (clk,rst,position[27],wdata,midout[27]);
    pcreg myreg28 (clk,rst,position[28],wdata,midout[28]);
    pcreg myreg29 (clk,rst,position[29],wdata,midout[29]);
    pcreg myreg30 (clk,rst,position[30],wdata,midout[30]);
    pcreg myreg31(clk,rst,position[31],wdata,midout[31]); 
    //下面是两个32位数据选择器
    selector321 outone(midout[0],midout[1],midout[2],midout[3],midout[4],midout[5],
                       midout[6],midout[7],midout[8],midout[9],midout[10],midout[11],
                       midout[12],midout[13],midout[14],midout[15],midout[16],midout[17],
                       midout[18],midout[19],midout[20],midout[21],midout[22],midout[23],
                       midout[24],midout[25],midout[26],midout[27],midout[28],midout[29],
                       midout[30],midout[31],raddr1,~we,rdata1);
 selector321 outtwo(midout[0],midout[1],midout[2],midout[3],midout[4],midout[5],
                    midout[6],midout[7],midout[8],midout[9],midout[10],midout[11],
                    midout[12],midout[13],midout[14],midout[15],midout[16],midout[17],
                    midout[18],midout[19],midout[20],midout[21],midout[22],midout[23],
                    midout[24],midout[25],midout[26],midout[27],midout[28],midout[29],
                    midout[30],midout[31],raddr2,~we,rdata2);
endmodule
