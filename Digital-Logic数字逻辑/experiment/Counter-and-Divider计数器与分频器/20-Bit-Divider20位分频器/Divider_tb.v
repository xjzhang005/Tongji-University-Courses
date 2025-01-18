`timescale 1ns / 1ns
module Divider_tb;
reg I_CLK;
reg rst;
wire O_CLK;
Divider uut(.I_CLK(I_CLK),.rst(rst),.O_CLK(O_CLK));
initial
begin
I_CLK=1'b0;
rst=1'b1;
#10 rst=1'b0;
#10 rst=1'b1;
#10 rst=1'b0;
end
always #2 I_CLK=~I_CLK;
endmodule

