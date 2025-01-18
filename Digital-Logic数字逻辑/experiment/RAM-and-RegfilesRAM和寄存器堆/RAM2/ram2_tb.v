`timescale 1ns / 1ns
module ram2_tb;
reg clk;
reg ena;
reg wena;
reg [4:0]addr;
wire [31:0] data ;
ram2 uut(.clk(clk),.ena(ena),.wena(wena),.addr(addr),.data(data));
reg [6:0]mid;
initial
begin
wena=1;
ena=1;
clk=0;
for(mid=0;mid<32;mid=mid+1)//赋初值
begin
addr=mid;
force data=5*mid;
#5 clk=1;
#5 clk=0;
end
#10 force data=0;
#10 release data;
#10 wena=0;
for(mid=0;mid<32;mid=mid+1)//读初值
begin
addr=mid;
#5 clk=1;
#5 clk=0;
end
wena=1;
addr =10;
force data=32'hffff0000;//写入一个检测值
#10 clk=1;
#10 clk=0;
release data;
#10 wena=0;//准备读
#10 clk=1;
#10 clk=0;
end
endmodule
