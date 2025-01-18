`timescale 1ns / 1ns
module barrelshifter32_tb;
reg [31:0] a;//32 位原始输入数据
reg [4:0] b; //5 位输入信号，控制移位的位数
reg [1:0] aluc; //2 位输入信号，控制移位的方式
wire [31:0] c; //32 位移位后的输出数据
 barrelshifter32 uut(.a(a),.b(b),.aluc(aluc),.c(c));
initial
begin
b=5'b00111;
#10 a=32'b10101010101010101010101010101010;
#10 aluc=2'b00;
#20 aluc=2'b01;
#20 aluc=2'b10;
#20 aluc=2'b11;
#20 aluc=2'b00;
end

endmodule
