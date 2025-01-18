`timescale 1ns / 1ns
module Adder_tb;
reg [7:0] iData_a;
reg [7:0] iData_b;
reg iC;
wire [7:0] oData;
wire oData_C;
Adder uut(.iData_a(iData_a),.iData_b(iData_b),.iC(iC),.oData(oData),.oData_C(oData_C));
initial
begin 
iData_a=8'b0000_0010;
iData_b=8'b0000_0001;
iC=1;
#10
iData_a=8'b0000_0000;
iData_b=8'b0000_1111;
iC=0;
#10
iData_a=8'b1111_0000;
iData_b=8'b0000_1111;
iC=0;
#10
iData_a=8'b0000_1000;
iData_b=8'b0000_0111;
iC=1;
end
endmodule
