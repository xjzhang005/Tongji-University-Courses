`timescale 1ns / 1ns
module selector41_tb;
reg iS1;
reg iS0;
reg [3:0] iC0;
reg [3:0] iC1;
reg [3:0] iC2;
reg [3:0] iC3;
wire [3:0] oZ;
selector41 uut (.iC0(iC0),.iC1(iC1),.iC2(iC2),.iC3(iC3),.iS1(iS1),.iS0(iS0),.oZ(oZ));
initial 
begin
iS1=0;
#20 iS1=0;
#20 iS1=1;
#20 iS1=0;
#20 iS1=1;
end
initial
begin
iS0=0;
#20 iS0=0;
#20 iS0=0;
#20 iS0=1;
#20 iS0=1;
end
initial
begin
iC0=4'b0000;
iC1=4'b0011;
iC2=4'b1100;
iC3=4'b1111;
end
endmodule
