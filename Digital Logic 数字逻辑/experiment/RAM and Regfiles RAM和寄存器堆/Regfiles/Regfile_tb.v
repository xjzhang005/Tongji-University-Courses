`timescale 1ns / 1ps
module Regfile_tb;
reg clk;
reg rst;
reg we;
reg [4:0] raddr1;
reg [4:0] raddr2;
reg [4:0] waddr;
reg [31:0] wdata;
wire [31:0] rdata1;
wire [31:0] rdata2;
Regfiles uut(.clk(clk),.rst(rst),.we(we),.raddr1(raddr1),.raddr2(raddr2),.waddr(waddr),.wdata(wdata),.rdata1(rdata1),.rdata2(rdata2));
reg [6:0] mid;
initial
begin
clk=1;//时钟下降沿有效
we=1;//写有效
rst=1;//先全部清零
raddr1=0;
raddr2=0;
waddr=0;
wdata=0;
#5
rst=0;
#5
for(mid=0;mid<32;mid=mid+1)//写入数据
begin
waddr=mid;
wdata=mid*5;
#5 clk=0;
#5 clk=1;
end
//下面是读数据
#5 we=0;
for(mid=0;mid<32;mid=mid+1)
begin
raddr1=mid;
raddr2=mid;
#5 clk=0;
#5 clk=1;
end
#5 we=1;
#5 rst=1;
#5 rst=0;
#5 we=0;
for(mid=0;mid<32;mid=mid+1)
begin
raddr1=mid;
raddr2=mid;
#5 clk=0;
#5 clk=1;
end
/*waddr=5;
wdata=32'hffff8888;
#5 clk=0;
#5 clk=1;
#5 we=0;
raddr1=waddr;
raddr2=waddr;
#5 clk=0;
#5 clk=1;*/
/*for(mid=0;mid<32;mid=mid+1)//写入数据
begin
waddr=mid;
wdata=mid*2;
#5 clk=0;
#5 clk=1;
end*/
//下面是读数据
/*#5 we=0;
for(mid=0;mid<32;mid=mid+1)
begin
raddr1=mid;
raddr2=mid;
#5 clk=0;
#5 clk=1;
end*/
end
endmodule
