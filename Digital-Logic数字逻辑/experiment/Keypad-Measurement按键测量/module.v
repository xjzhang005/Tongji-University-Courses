`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/12/02 18:39:57
// Design Name: 
// Module Name: module
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

module display7(
    input [3:0] iData,      // 4λ�������ݣ���ʾҪ��ʾ������
    output reg [6:0] oData  // 8λ������ݣ�����DP��С������ƣ�
);
    always @(*) begin
        // �������������ѡ���Ӧ��7����ʾ����ʾ״̬��DPĬ�Ϲر�
        case(iData)
            4'd0: oData = 7'b1000000; // ��ʾ0��DP�ر�
            4'd1: oData = 7'b1111001; // ��ʾ1��DP�ر�
            4'd2: oData = 7'b0100100; // ��ʾ2��DP�ر�
            4'd3: oData = 7'b0110000; // ��ʾ3��DP�ر�
            4'd4: oData = 7'b0011001; // ��ʾ4��DP�ر�
            4'd5: oData = 7'b0010010; // ��ʾ5��DP�ر�
            4'd6: oData = 7'b0000010; // ��ʾ6��DP�ر�
            4'd7: oData = 7'b1111000; // ��ʾ7��DP�ر�
            4'd8: oData = 7'b0000000; // ��ʾ8��DP�ر�
            4'd9: oData = 7'b0010000; // ��ʾ9��DP�ر�
            default: oData = 7'b1111111; // Ĭ��״̬�����жιر�
        endcase
    end
endmodule

// ��Ƶ��ģ��
module Divider (
    input I_CLK,            // ����ʱ���ź�
    input rst,              // ��λ�źţ��ߵ�ƽ��Ч
    output reg O_CLK        // �����Ƶ���ʱ���ź�
    );

    reg [31:0] counter;     // ������������ʵ�ֽϴ�ķ�Ƶ

    initial begin
        counter = 1'b0;
        O_CLK = 1'b0;
    end

    parameter DIVISOR = 5000; // Ĭ�Ϸ�Ƶ���� 

    always @(posedge I_CLK) begin
        if (rst) begin
            counter <= 0;
            O_CLK <= 0;
        end
        else begin
            if (counter == (DIVISOR / 2 - 1)) begin
                counter <= 0;
                O_CLK <= ~O_CLK;  // ��ת O_CLK ��ʵ�ַ�Ƶ
            end
            else begin
                counter <= counter + 1;
            end
        end
    end
endmodule


module keying(
    input clk,                // ʱ���źţ�����ͬ��
    input rst_n,                // ��λ�źţ���ʼ��ģ��״̬
    input key,                // ���������ź�
    output wire [6:0] led,    // 7����ʾ�ܵĶο����źţ�����С����DP
    output reg [7:0] an,      // 7����ʾ�ܵ����������źţ�����ѡ����ʾ�ĸ�����
    output reg light          // ��ƿ����źţ����ƵƵĿ���
    
);
    wire div_clk;          // ��Ƶ���ʱ���ź�
    wire div_clk2;          // ��Ƶ���ʱ���ź�

    // ʵ������Ƶ�������÷�Ƶ����
    Divider #(.DIVISOR(100000)) divider_inst (//��λ��1ms
   // Divider #(.DIVISOR(100)) divider_inst (
        .I_CLK(clk),
        .rst(!rst_n),       // ע������ʹ�øߵ�ƽ��Ч�ĸ�λ�ź�
        .O_CLK(div_clk)
    );
    //24999
    //100000
    Divider #(.DIVISOR(100)) divider_inst2 (
   // Divider #(.DIVISOR(10)) divider_inst2 (
        .I_CLK(clk),
        .rst(!rst_n),       // ע������ʹ�øߵ�ƽ��Ч�ĸ�λ�ź�
        .O_CLK(div_clk2)
    );


    // ���尴�����µ�ʱ����ؼĴ���
    reg [31:0] key_press_time;    // ��¼�������µĳ���ʱ��
    reg [31:0] key_released_time; // ��¼�����ͷź��ʱ��
    reg [31:0] light_time;        // ��¼��Ƶ�����ʱ��
    reg key_pressed;              // �����Ƿ񱻰��µ�״̬
    reg key_released;             // �����Ƿ��ͷŵ�״̬
    reg light_on;                 // ����Ƿ�����״̬

    reg [31:0] num;               // ��ʾ�����֣���ʾ����ʱ��
    reg [3:0] display_counter;    // ��ʾѡ�������������ѡ���ĸ�������ʾ
    reg [3:0] digit_value;        // ��ǰ��ʾ������ֵ��������ʾ����
    
    
    // ʵ�����߶���ʾ��ģ�飬���뵱ǰ�����֣������Ӧ���߶���ʾ�ܵĶο����ź�
    display7 u_display7(
        .iData(digit_value),   // ����Ҫ��ʾ������
        .oData(led)            // ����ο����źţ�����DP
    );
    /*initial begin
        display_counter = 1;
        end*/
    // �������º��ͷŵļ�ʱ
    always @(posedge div_clk or negedge rst_n)
     begin
            if (!rst_n)
                begin
                    key_press_time <= 0;
                    key_released_time <= 0;  // ���ð����ͷż�ʱ��
                end
            else
                begin   
                    if (key == 1 && !key_pressed) 
                    begin
                        key_press_time <= 0;  // ���ð������¼�ʱ��
                        key_released_time <= 0;  // ���ð����ͷż�ʱ��
                    end     
                    if (key_pressed)
                        key_press_time <= key_press_time + 1;
                    if (key_released)
                        key_released_time <= key_released_time + 1;
                end        
        end 
            
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            // �����λ�ź���Ч���������мĴ���
            key_pressed <= 0;
            key_released <= 0;
            light_time <= 0;
            light_on <= 0;
            
            num <= 0;
            light <= 0;
        end 
        else begin
            // ��ⰴ�������¼�
            if (key == 1 && !key_pressed) begin
                key_pressed <= 1;  // ��ǰ�������
                key_released <= 0;  // ���ð����ͷ�״̬
            end
            // ��ⰴ���ͷ��¼�
            if (key == 0 && key_pressed) begin
                key_pressed <= 0;  // ��ǰ����ͷ�
                key_released <= 1;  // ��ǰ������ͷ�
                light_time <= key_press_time;  // ����������ʱ����¼Ϊ�������ʱ��
                num <= key_press_time / 1000;  // ���水��ʱ����������ʾ
            end
            // ���Ƶ�ƿ���
            if (key_released && !light_on) begin
                light_on <= 1;    // �������
                light <= 1;        // �����
            end
            if (light_on && key_released_time == light_time) begin
                light_on <= 0;    // �رյ��
                light <= 0;        // �����
                key_released <= 0; // ���ð����ͷ�״̬
            end
        end
    end

    // ��ʾ����ʱ�������ֵ��߶���ʾ��
    always @(posedge div_clk2 or negedge rst_n) begin
        if (!rst_n)
            begin
                display_counter <= 0; 
                an <= 8'b11111111; // ��ʼʱ���ر����������
                digit_value <= 4'b0000;
            end 
        else 
            begin
                display_counter <= display_counter + 1; // ������ʾ������
                if(display_counter==8)
                    begin
                        display_counter = 0;
                    end
                // ѡ��ǰ�������ʾ��
               case (display_counter)
                    3'd0: an <= 8'b11111110;  // ����� 0 �������
                    3'd1: an <= 8'b11111101;  // ����� 1 �������
                    3'd2: an <= 8'b11111011;  // ����� 2 �������
                    3'd3: an <= 8'b11110111;  // ����� 3 �������
                    3'd4: an <= 8'b11101111;  // ����� 4 �������
                    3'd5: an <= 8'b11011111;  // ����� 5 �������
                    3'd6: an <= 8'b10111111;  // ����� 6 �������
                    3'd7: an <= 8'b01111111;  // ����� 7 �������
                    default: an <= 8'b11111111;  // Ĭ������£��ر����������
                endcase
                // ���ݼ�����ֵ��ʾ��ͬ������λ
                case (display_counter)
                    3'd0: digit_value <= num % 10;            // ��ʾ��λ��
                    3'd1: digit_value <= (num / 10) % 10;     // ��ʾʮλ��
                    3'd2: digit_value <= (num / 100) % 10;    // ��ʾ��λ��
                    3'd3: digit_value <= (num / 1000) % 10;   // ��ʾǧλ��
                    3'd4: digit_value <= (num / 10000) % 10;  // ��ʾ��λ��
                    3'd5: digit_value <= (num / 100000) % 10; // ��ʾʮ��λ��
                    3'd6: digit_value <= (num / 1000000) % 10; // ��ʾ����λ��
                    3'd7: digit_value <= (num / 10000000) % 10; // ��ʾǧ��λ��
                    default: digit_value <= 4'b0000;
                endcase
            end
    end
    // assign��丳ֵan
   /* assign an = (!rst_n) ? 8'b11111111 : 
                (display_counter == 3'd0) ? 8'b11111110 :
                (display_counter == 3'd1) ? 8'b11111101 :
                (display_counter == 3'd2) ? 8'b11111011 :
                (display_counter == 3'd3) ? 8'b11110111 :
                (display_counter == 3'd4) ? 8'b11101111 :
                (display_counter == 3'd5) ? 8'b11011111 :
                (display_counter == 3'd6) ? 8'b10111111 :
                (display_counter == 3'd7) ? 8'b01111111 :
                8'b11111111;*/
    

endmodule
