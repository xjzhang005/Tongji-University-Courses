`timescale 1ns / 1ns
module JK_FF_tb;
reg CLK;
reg J;
reg K;
reg RST_n;
wire Q1;
wire Q2;
JK_FF uut (.CLK(CLK),.J(J),.K(K),.RST_n(RST_n),.Q1(Q1),.Q2(Q2));
initial 
begin
CLK=0;
J=0;
K=0;
RST_n=1;
#10
CLK=1;
J=1;
K=0;
#10
CLK=0;
#10
CLK=1;
J=0;
K=0;
#10
CLK=0;
#10
CLK=1;
J=1;
K=1;
#10
CLK=0;
#10
CLK=1;
J=1;
K=1;
#10
CLK=0;
#10
CLK=1;
J=0;
K=1;
#10
CLK=0;
#10
CLK=1;
J=1;
K=1;
#10
RST_n=0;
end
endmodule
