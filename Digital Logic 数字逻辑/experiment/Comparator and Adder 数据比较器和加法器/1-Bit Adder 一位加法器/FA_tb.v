`timescale 1ns / 1ns
module FA_tb;
reg iA;
reg iB;
reg iC;
wire oS;
wire oC;
FA uut(.iA(iA),.iB(iB),.iC(iC),.oS(oS),.oC(oC));
initial
begin
iA=0;
iB=0;
iC=0;
#10 
iA=0;
iB=0;
iC=1;
#10 
iA=0;
iB=1;
iC=0;
#10
iA=0;
iB=1;
iC=1;
#10
iA=1;
iB=0;
iC=0;
#10
iA=1;
iB=0;
iC=1;
#10
iA=1;
iB=1;
iC=0;
#10
iA=1;
iB=1;
iC=1;
end
endmodule
