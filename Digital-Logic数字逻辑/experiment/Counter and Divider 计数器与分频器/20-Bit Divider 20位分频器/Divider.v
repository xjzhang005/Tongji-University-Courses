`timescale 1ns / 1ns
module Divider(
input  I_CLK, //����ʱ���źţ���������Ч
input rst, //ͬ����λ�źţ��ߵ�ƽ��Ч
output reg O_CLK //���ʱ��
    );
    reg [4:0] cnt; 
    initial
    begin
    cnt=1'b0;
    O_CLK=1'b0;
    end
   // reg O_CLK;
    parameter N=20;
    always@(posedge I_CLK )//ͬ����λ����˼������Ҫ��ʱ���źţ��ٿ���λ�ź�
    begin
    if(rst)//�����λ�ź���Ч
    begin
    cnt<=0;
    O_CLK<=0;
  // assign  O_CLK=0;
    end
    else if(cnt==N/2-1)
    begin
    O_CLK<=~O_CLK;
    cnt<=0;
    end
    else
    begin
    cnt<=cnt+1'b1;
    end
    end
endmodule

