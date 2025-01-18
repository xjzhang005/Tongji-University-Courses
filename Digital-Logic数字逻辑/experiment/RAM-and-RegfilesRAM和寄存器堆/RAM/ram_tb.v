`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/11/13 23:13:34
// Design Name: 
// Module Name: ram_tb
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
`timescale 1ns / 1ps

module ram_tb;

    // �����ź�
    reg clk;
    reg ena;
    reg wena;
    reg [4:0] addr;
    reg [31:0] data_in;

    // ����ź�
    wire [31:0] data_out;

    // ʵ����RAMģ��
    ram uut (
        .clk(clk),
        .ena(ena),
        .wena(wena),
        .addr(addr),
        .data_in(data_in),
        .data_out(data_out)
    );

    // ʱ������
    initial begin
        clk = 0;
        forever #5 clk = ~clk;  // 10ns����ʱ��
    end

    // ��������
    initial begin
        // ��ʼ���ź�
        ena = 0;
        wena = 0;
        addr = 0;
        data_in = 32'h00000000;

        // �ȴ�ʱ���ȶ�
        #10;

        // ������Ч�ź�
        ena = 0;
        wena = 0;
        addr = 5'b00000;
        data_in = 32'h12345678;
        #20;
        if (data_out !== 32'bz) $display("Error: Expected high impedance output when ena is low.");

        // ����д����
        ena = 1;
        wena = 1;
        addr = 5'b00001;
        data_in = 32'h12345678;
        #10;
        ena = 0;
        wena = 0;
        #10;

        // ���Զ�����
        ena = 1;
        wena = 0;
        addr = 5'b00001;
        #10;
        if (data_out !== 32'h12345678) $display("Error: Expected data_out to be 0x12345678 after write and read.");
        ena = 0;
        wena = 0;
        #10;

        // ������Ч�ź�
        ena = 0;
        wena = 0;
        addr = 5'b00001;
        #20;
        if (data_out !== 32'bz) $display("Error: Expected high impedance output when ena is low.");

        // ���Զ��д����
        ena = 1;
        wena = 1;
        addr = 5'b00010;
        data_in = 32'h87654321;
        #10;
        addr = 5'b00011;
        data_in = 32'hABCDEF01;
        #10;
        addr = 5'b00100;
        data_in = 32'h11223344;
        #10;
        ena = 0;
        wena = 0;
        #10;

        // ���Զ��������
        ena = 1;
        wena = 0;
        addr = 5'b00010;
        #10;
        if (data_out !== 32'h87654321) $display("Error: Expected data_out to be 0x87654321 after write and read.");
        addr = 5'b00011;
        #10;
        if (data_out !== 32'hABCDEF01) $display("Error: Expected data_out to be 0xABCDEF01 after write and read.");
        addr = 5'b00100;
        #10;
        if (data_out !== 32'h11223344) $display("Error: Expected data_out to be 0x11223344 after write and read.");
        ena = 0;
        wena = 0;
        #10;

        // ��������
        $display("Testbench completed.");
        $stop;
    end

endmodule