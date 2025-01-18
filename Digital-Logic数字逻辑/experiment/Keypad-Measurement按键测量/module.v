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
    input [3:0] iData,      // 4位输入数据，表示要显示的数字
    output reg [6:0] oData  // 8位输出数据，包含DP（小数点控制）
);
    always @(*) begin
        // 根据输入的数字选择对应的7段显示管显示状态，DP默认关闭
        case(iData)
            4'd0: oData = 7'b1000000; // 显示0，DP关闭
            4'd1: oData = 7'b1111001; // 显示1，DP关闭
            4'd2: oData = 7'b0100100; // 显示2，DP关闭
            4'd3: oData = 7'b0110000; // 显示3，DP关闭
            4'd4: oData = 7'b0011001; // 显示4，DP关闭
            4'd5: oData = 7'b0010010; // 显示5，DP关闭
            4'd6: oData = 7'b0000010; // 显示6，DP关闭
            4'd7: oData = 7'b1111000; // 显示7，DP关闭
            4'd8: oData = 7'b0000000; // 显示8，DP关闭
            4'd9: oData = 7'b0010000; // 显示9，DP关闭
            default: oData = 7'b1111111; // 默认状态，所有段关闭
        endcase
    end
endmodule

// 分频器模块
module Divider (
    input I_CLK,            // 输入时钟信号
    input rst,              // 复位信号，高电平有效
    output reg O_CLK        // 输出分频后的时钟信号
    );

    reg [31:0] counter;     // 计数器，用于实现较大的分频

    initial begin
        counter = 1'b0;
        O_CLK = 1'b0;
    end

    parameter DIVISOR = 5000; // 默认分频倍数 

    always @(posedge I_CLK) begin
        if (rst) begin
            counter <= 0;
            O_CLK <= 0;
        end
        else begin
            if (counter == (DIVISOR / 2 - 1)) begin
                counter <= 0;
                O_CLK <= ~O_CLK;  // 翻转 O_CLK 以实现分频
            end
            else begin
                counter <= counter + 1;
            end
        end
    end
endmodule


module keying(
    input clk,                // 时钟信号，控制同步
    input rst_n,                // 复位信号，初始化模块状态
    input key,                // 按键输入信号
    output wire [6:0] led,    // 7段显示管的段控制信号，包括小数点DP
    output reg [7:0] an,      // 7段显示管的阳极控制信号，用于选择显示哪个数字
    output reg light          // 电灯控制信号，控制灯的开关
    
);
    wire div_clk;          // 分频后的时钟信号
    wire div_clk2;          // 分频后的时钟信号

    // 实例化分频器，设置分频倍数
    Divider #(.DIVISOR(100000)) divider_inst (//单位是1ms
   // Divider #(.DIVISOR(100)) divider_inst (
        .I_CLK(clk),
        .rst(!rst_n),       // 注意这里使用高电平有效的复位信号
        .O_CLK(div_clk)
    );
    //24999
    //100000
    Divider #(.DIVISOR(100)) divider_inst2 (
   // Divider #(.DIVISOR(10)) divider_inst2 (
        .I_CLK(clk),
        .rst(!rst_n),       // 注意这里使用高电平有效的复位信号
        .O_CLK(div_clk2)
    );


    // 定义按键按下的时间相关寄存器
    reg [31:0] key_press_time;    // 记录按键按下的持续时间
    reg [31:0] key_released_time; // 记录按键释放后的时间
    reg [31:0] light_time;        // 记录电灯点亮的时长
    reg key_pressed;              // 按键是否被按下的状态
    reg key_released;             // 按键是否释放的状态
    reg light_on;                 // 电灯是否开启的状态

    reg [31:0] num;               // 显示的数字，表示按键时长
    reg [3:0] display_counter;    // 显示选择计数器，用于选择哪个数字显示
    reg [3:0] digit_value;        // 当前显示的数字值，用于显示数字
    
    
    // 实例化七段显示管模块，输入当前的数字，输出对应的七段显示管的段控制信号
    display7 u_display7(
        .iData(digit_value),   // 输入要显示的数字
        .oData(led)            // 输出段控制信号，包括DP
    );
    /*initial begin
        display_counter = 1;
        end*/
    // 按键按下和释放的计时
    always @(posedge div_clk or negedge rst_n)
     begin
            if (!rst_n)
                begin
                    key_press_time <= 0;
                    key_released_time <= 0;  // 重置按键释放计时器
                end
            else
                begin   
                    if (key == 1 && !key_pressed) 
                    begin
                        key_press_time <= 0;  // 重置按键按下计时器
                        key_released_time <= 0;  // 重置按键释放计时器
                    end     
                    if (key_pressed)
                        key_press_time <= key_press_time + 1;
                    if (key_released)
                        key_released_time <= key_released_time + 1;
                end        
        end 
            
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            // 如果复位信号有效，重置所有寄存器
            key_pressed <= 0;
            key_released <= 0;
            light_time <= 0;
            light_on <= 0;
            
            num <= 0;
            light <= 0;
        end 
        else begin
            // 检测按键按下事件
            if (key == 1 && !key_pressed) begin
                key_pressed <= 1;  // 标记按键按下
                key_released <= 0;  // 重置按键释放状态
            end
            // 检测按键释放事件
            if (key == 0 && key_pressed) begin
                key_pressed <= 0;  // 标记按键释放
                key_released <= 1;  // 标记按键已释放
                light_time <= key_press_time;  // 将按键按下时长记录为电灯亮灯时间
                num <= key_press_time / 1000;  // 保存按键时长，用于显示
            end
            // 控制电灯开关
            if (key_released && !light_on) begin
                light_on <= 1;    // 开启电灯
                light <= 1;        // 电灯亮
            end
            if (light_on && key_released_time == light_time) begin
                light_on <= 0;    // 关闭电灯
                light <= 0;        // 电灯灭
                key_released <= 0; // 重置按键释放状态
            end
        end
    end

    // 显示按键时长的数字到七段显示管
    always @(posedge div_clk2 or negedge rst_n) begin
        if (!rst_n)
            begin
                display_counter <= 0; 
                an <= 8'b11111111; // 初始时，关闭所有数码管
                digit_value <= 4'b0000;
            end 
        else 
            begin
                display_counter <= display_counter + 1; // 增加显示计数器
                if(display_counter==8)
                    begin
                        display_counter = 0;
                    end
                // 选择当前激活的显示器
               case (display_counter)
                    3'd0: an <= 8'b11111110;  // 激活第 0 个数码管
                    3'd1: an <= 8'b11111101;  // 激活第 1 个数码管
                    3'd2: an <= 8'b11111011;  // 激活第 2 个数码管
                    3'd3: an <= 8'b11110111;  // 激活第 3 个数码管
                    3'd4: an <= 8'b11101111;  // 激活第 4 个数码管
                    3'd5: an <= 8'b11011111;  // 激活第 5 个数码管
                    3'd6: an <= 8'b10111111;  // 激活第 6 个数码管
                    3'd7: an <= 8'b01111111;  // 激活第 7 个数码管
                    default: an <= 8'b11111111;  // 默认情况下，关闭所有数码管
                endcase
                // 根据计数器值显示不同的数字位
                case (display_counter)
                    3'd0: digit_value <= num % 10;            // 显示个位数
                    3'd1: digit_value <= (num / 10) % 10;     // 显示十位数
                    3'd2: digit_value <= (num / 100) % 10;    // 显示百位数
                    3'd3: digit_value <= (num / 1000) % 10;   // 显示千位数
                    3'd4: digit_value <= (num / 10000) % 10;  // 显示万位数
                    3'd5: digit_value <= (num / 100000) % 10; // 显示十万位数
                    3'd6: digit_value <= (num / 1000000) % 10; // 显示百万位数
                    3'd7: digit_value <= (num / 10000000) % 10; // 显示千万位数
                    default: digit_value <= 4'b0000;
                endcase
            end
    end
    // assign语句赋值an
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
