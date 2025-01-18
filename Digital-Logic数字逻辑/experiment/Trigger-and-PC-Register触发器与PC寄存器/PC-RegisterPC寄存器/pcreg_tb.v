`timescale 1ns / 1ns
module pcreg_tb;
reg clk;
reg rst;
reg ena;
reg [31:0] data_in;
wire [31:0] data_out;
pcreg uut (.clk(clk),.rst(rst),.ena(ena),.data_in(data_in),.data_out(data_out));
initial
begin
clk=0;
rst=0;
ena=0;
data_in=32'b0;
#10
clk=1;
ena=1;
data_in=32'b0000_0000_0000_0000_0000_0000_1111_1111;
#10
clk=0;
rst=1;
#10
clk=1;
rst=0;
ena=0;
data_in=32'b0000_0000_0000_0000_1111_1111_1111_1111;
#10
clk=0;
#10
clk=1;
ena=1;
end
endmodule
