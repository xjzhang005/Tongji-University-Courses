`timescale 1ns / 1ns
module alu_tb;
reg [31:0]a;
reg [31:0]b;
reg [3:0]aluc;
wire[31:0]r;
wire zero,carry,negative,overflow;
alu uut(.a(a),.b(b),.aluc(aluc),.r(r),.zero(zero),.carry(carry),.negative(negative),.overflow(overflow));
initial
begin
a=32'h0000001f;
b=32'h0000ffff;
aluc=4'b1110;
#10
aluc=4'b0010;
#10
aluc=4'b0001;
#10
aluc=4'b0011;
#10
aluc=4'b0100;
#10
aluc=4'b0101;
#10
aluc=4'b0110;
#10
aluc=4'b0111;
#10
aluc=4'b1000;
#10
aluc=4'b1001;
#10
aluc=4'b1011;
#10
aluc=4'b1010;
#10
aluc=4'b1100;
#10
aluc=4'b1110;
#10
aluc=4'b1111;
#10
aluc=4'b1101;
end
endmodule
