`timescale 1ns / 1ns
module Counter8_tb;
reg CLK;
reg rst_n;
wire [3:0] oQ;
wire [6:0] oDisplay;
Counter8 uut(.CLK(CLK),.rst_n(rst_n),.oQ(oQ),.oDisplay(oDisplay));
initial 
begin
CLK=1'b0;
rst_n=1'b0;
#10
rst_n=1'b1;
#45
rst_n=1'b0;
#5
rst_n=1'b1;
end
always #5 CLK=~CLK;
endmodule
