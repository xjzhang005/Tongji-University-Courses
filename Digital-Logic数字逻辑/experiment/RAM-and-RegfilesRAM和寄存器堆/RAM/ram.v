`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/11/13 22:54:28
// Design Name: 
// Module Name: ram
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


//module ram (
//    input clk, //�洢��ʱ���źţ�������ʱ�� ram �ڲ�д������
//    input ena, //�洢����Ч�źţ��ߵ�ƽʱ�洢�������У�������� z
//    input wena, //�洢����д��Ч�źţ��ߵ�ƽΪд��Ч���͵�ƽΪ����Ч���� enaͬʱ��Чʱ�ſɶԴ洢�����ж�д
//    input [4:0] addr, //�����ַ��ָ�����ݶ�д�ĵ�ַ
//    input [31:0] data_in, //�洢��д������ݣ��� clk ������ʱ��д��
//    output [31:0] data_out //�洢������������
//);

//endmodule

module ram (
    input clk,        // �洢��ʱ���źţ�������ʱ�� RAM �ڲ�д������
    input ena,        // �洢����Ч�źţ��ߵ�ƽʱ�洢�������У�������� z
    input wena,       // �洢����д��Ч�źţ��ߵ�ƽΪд��Ч���͵�ƽΪ����Ч
    input [4:0] addr, // �����ַ��ָ�����ݶ�д�ĵ�ַ
    input [31:0] data_in, // �洢��д������ݣ��� clk ������ʱ��д��
    output [31:0] data_out // �洢������������
);

    // ����RAM�洢��Ԫ
    reg [31:0] mem [0:31];
    //������
    assign data_out = (ena && !wena)?mem[addr]:32'bz;
    
    // д����
    always @(posedge clk) begin
        if (ena && wena) begin
            mem[addr] <= data_in;  // д����
        end
    end

endmodule