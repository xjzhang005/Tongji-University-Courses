`timescale 1ns / 1ns
module Asynchronous_D_FF_tb;
reg CLK;
reg D;
reg RST_n;
wire Q1;
wire Q2;
Asynchronous_D_FF uut (.CLK(CLK),.D(D),.RST_n(RST_n),.Q1(Q1),.Q2(Q2));
initial
begin
CLK=0;
D=0;
RST_n=1;
#10
CLK=1;
D=1;
#10
CLK=0;
#10
CLK=1;
D=0;
#10
CLK=0;
#10
CLK=1;
D=1;
RST_n=0;
#10
CLK=0;
#10
CLK=1;
D=1;
RST_n=1;
#10
RST_n=0;
end
endmodule
