`timescale 1ns / 1ns
module JK_FF(
input CLK, //ʱ���źţ���������Ч
 input J, //�����ź� J
 input K, //�����ź� K
input RST_n, //��λ�źţ��͵�ƽ��Ч
 output reg Q1,//����ź� Q
 output reg Q2 //����ź�~Q
    );
    always @(posedge RST_n or posedge CLK or negedge RST_n)
    begin
    if(!RST_n)//ǿ��������Ч
    begin
    Q1<=1'b0;
    Q2<=1'b1;
    end
    else//ǿ��������Ч
    begin
    if(J==0 && K==0)
    begin
   // Q1<=Q1;
   // Q2<=Q2;
    end
    else if(J==0 && K==1)
    begin
    Q1<=1'b0;
    Q2<=1'b1;
    end
    else if(J==1 && K==0)
    begin
     Q1<=1'b1;
     Q2<=1'b0;
    end 
    else if(J==1 && K==1)
    begin
     //Q1<=Q2;
    // Q2<=Q1;
    Q1<=~Q1;
    Q2<=~Q2;
    end
    end
    end
endmodule

