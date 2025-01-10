`timescale 1ns / 1ns
module de_selector14(
input iC, //输入信号 c
input iS1, //选择信号 s1 
input iS0, //选择信号 s0
output oZ0, //输出信号 z0
output oZ1, //输出信号 z1
output oZ2, //输出信号 z2
output oZ3 //输出信号 z3
    );
   assign oZ0=iS1 | iS0 | iC;
   assign oZ1=iS1 | ~iS0 | iC;
   assign oZ2=~iS1 | iS0 | iC;
   assign oZ3=~iS1 | ~iS0 | iC;
endmodule
