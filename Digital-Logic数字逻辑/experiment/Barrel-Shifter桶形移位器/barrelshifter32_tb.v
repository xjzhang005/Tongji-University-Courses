`timescale 1ns / 1ns
module barrelshifter32_tb;
reg [31:0] a;//32 λԭʼ��������
reg [4:0] b; //5 λ�����źţ�������λ��λ��
reg [1:0] aluc; //2 λ�����źţ�������λ�ķ�ʽ
wire [31:0] c; //32 λ��λ����������
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
