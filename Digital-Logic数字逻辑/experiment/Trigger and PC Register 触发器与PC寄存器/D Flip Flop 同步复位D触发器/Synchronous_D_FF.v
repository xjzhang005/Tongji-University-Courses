`timescale 1ns / 1ns
module Synchronous_D_FF(
input CLK, //ʱ���źţ���������Ч
 input D, //�����ź� D
 input RST_n, //��λ�źţ��͵�ƽ��Ч
 output reg Q1, //����ź� Q
 output reg Q2//����ź�?~Q
    );
    always @(posedge CLK)//������������ʱ
    begin
    if(!RST_n)//�����λ�ź���Ч
    begin
    Q1<=1'b0;
    Q2<=1'b1;
    end
    else //�����λ�ź���Ч
    begin
    Q1<=D;
    Q2<=~D;
    end
    end
endmodule
