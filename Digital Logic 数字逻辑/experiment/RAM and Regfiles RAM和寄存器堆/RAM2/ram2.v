`timescale 1ns / 1ns
module ram2(
input clk, //存储器时钟信号，上升沿时向 ram 内部写入数据
 input ena, //存储器有效信号，高电平时存储器才运行，否则输出 z
 input wena, //存储器读写有效信号，高电平为写有效，低电平为读有效，与ena 同时有效时才可对存储器进行读写
 input [4:0] addr, //输入地址，指定数据读写的地址
 inout [31:0] data //存储器数据线，可传输存储器读出或写入的数据。写入的数据在 clk 上升沿时被写入
    );
    reg [31:0] mydata [31:0];
    reg [31:0] temp;
   //这里需要用三目运算符
  always@(posedge clk)
  begin
  if(ena)//存储器有效
  begin
  if(wena)//写信号有效
  begin
  mydata[addr]=data;
  end
  else//读信号
  begin
  temp=mydata[addr];
  end
  end
  else//存储器无效
  begin
  temp=32'hzzzzzzzz;
  end
  end
 assign  data=(wena==0&&ena==1)?temp:32'hzzzzzzzz;
endmodule
