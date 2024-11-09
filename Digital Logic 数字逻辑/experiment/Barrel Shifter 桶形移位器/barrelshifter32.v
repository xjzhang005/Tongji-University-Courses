`timescale 1ns / 1ns
module barrelshifter32(
input [31:0] a, //32 位原始输入数据
input [4:0] b, //5 位输入信号，控制移位的位数
input [1:0] aluc, //2 位输入信号，控制移位的方式
output reg [31:0] c //32 位移位后的输出数据
    );
    reg [31:0] temp;
    always @(a or b or aluc)
    begin
    case (aluc)
    2'b00://算术右移
    begin//00开始
    temp =b[0]?{{a[31]},a[31:1]}:a;
    temp=b[1]?{{2{temp[31]}},temp[31:2]}:temp;
    temp=b[2]?{{4{temp[31]}},temp[31:4]}:temp;
    temp=b[3]?{{8{temp[31]}},temp[31:8]}:temp;
    temp=b[4]?{{16{temp[31]}},temp[31:16]}:temp;
    end
    2'b10://逻辑右移
    begin
    temp=b[0]?{1'b0,a[31:1]}:a;
    temp=b[1]?{2'b0,temp[31:2]}:temp;
    temp=b[2]?{4'b0,temp[31:4]}:temp;
    temp=b[3]?{8'b0,temp[31:8]}:temp;
    temp=b[4]?{16'b0,temp[31:16]}:temp;
    end
    2'b01,2'b11:
    begin
    temp=b[0]?{a[30:0],1'b0}:a;
    temp=b[1]?{temp[29:0],2'b0}:temp;
    temp=b[2]?{temp[27:0],4'b0}:temp;
    temp=b[3]?{temp[23:0],8'b0}:temp;
    temp=b[4]?{temp[15:0],16'b0}:temp;
    end
    endcase
    c=temp;
    end   
endmodule
