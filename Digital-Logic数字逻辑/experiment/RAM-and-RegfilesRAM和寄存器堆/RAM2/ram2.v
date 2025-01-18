`timescale 1ns / 1ns
module ram2(
input clk, //�洢��ʱ���źţ�������ʱ�� ram �ڲ�д������
 input ena, //�洢����Ч�źţ��ߵ�ƽʱ�洢�������У�������� z
 input wena, //�洢����д��Ч�źţ��ߵ�ƽΪд��Ч���͵�ƽΪ����Ч����ena ͬʱ��Чʱ�ſɶԴ洢�����ж�д
 input [4:0] addr, //�����ַ��ָ�����ݶ�д�ĵ�ַ
 inout [31:0] data //�洢�������ߣ��ɴ���洢��������д������ݡ�д��������� clk ������ʱ��д��
    );
    reg [31:0] mydata [31:0];
    reg [31:0] temp;
   //������Ҫ����Ŀ�����
  always@(posedge clk)
  begin
  if(ena)//�洢����Ч
  begin
  if(wena)//д�ź���Ч
  begin
  mydata[addr]=data;
  end
  else//���ź�
  begin
  temp=mydata[addr];
  end
  end
  else//�洢����Ч
  begin
  temp=32'hzzzzzzzz;
  end
  end
 assign  data=(wena==0&&ena==1)?temp:32'hzzzzzzzz;
endmodule
