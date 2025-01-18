`timescale 1ns / 1ns
module de_selector14_tb;
reg iC;
reg iS0;
reg iS1;
wire oZ0;
wire oZ1;
wire oZ2;
wire oZ3;
de_selector14 uut(.iC(iC),.iS1(iS1),.iS0(iS0),.oZ0(oZ0),.oZ1(oZ1),.oZ2(oZ2),.oZ3(oZ3));
initial
begin
iC=0;
#20 iC=0;
#20 iC=1;
#20 iC=0;
#20 iC=1;
#20 iC=0;
#20 iC=1;
#20 iC=0;
#20 iC=1;
end
initial 
begin
iS0=0;
#20 iS0=0;
#20 iS0=0;
#20 iS0=1;
#20 iS0=1;
#20 iS0=0;
#20 iS0=0;
#20 iS0=1;
#20 iS0=1;
end
initial
begin
iS1=0;
#20 iS1=0;
#20 iS1=0;
#20 iS1=0;
#20 iS1=0;
#20 iS1=1;
#20 iS1=1;
#20 iS1=1;
#20 iS1=1;
end
endmodule
