`timescale 1ns / 1ns
module Divider(
input  I_CLK, //输入时钟信号，上升沿有效
input rst, //同步复位信号，高电平有效
output reg O_CLK //输出时钟
    );
    reg [4:0] cnt; 
    initial
    begin
    cnt=1'b0;
    O_CLK=1'b0;
    end
   // reg O_CLK;
    parameter N=20;
    always@(posedge I_CLK )//同步复位的意思是先需要看时钟信号，再看复位信号
    begin
    if(rst)//如果复位信号有效
    begin
    cnt<=0;
    O_CLK<=0;
  // assign  O_CLK=0;
    end
    else if(cnt==N/2-1)
    begin
    O_CLK<=~O_CLK;
    cnt<=0;
    end
    else
    begin
    cnt<=cnt+1'b1;
    end
    end
endmodule

