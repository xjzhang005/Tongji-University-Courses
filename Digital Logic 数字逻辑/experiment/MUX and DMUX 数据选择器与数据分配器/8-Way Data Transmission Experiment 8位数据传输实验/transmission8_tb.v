`timescale 1ns / 1ns
module transmission8_tb;
reg A,B,C;
reg [7:0]iData;
wire [7:0]oData;
transmission8 uut(.iData(iData),.A(A),.B(B),.C(C),.oData(oData));
initial
begin
A=0;
#20 A=0;
#20 A=0;        
#20 A=0;
#20 A=0;
#20 A=1;
#20 A=1;
#20 A=1;
#20 A=1;
end
initial
begin
B=0;
#20 B=0;
#20 B=0;
#20 B=1;
#20 B=1;
#20 B=0;
#20 B=0;
#20 B=1;
#20 B=1;
end
initial
begin
C=0;
#20 C=0;
#20 C=1;
#20 C=0;
#20 C=1;
#20 C=0;
#20 C=1;
#20 C=0;
#20 C=1;
end
initial
begin
iData=8'b00000000;
end
endmodule
