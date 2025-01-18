`timescale 1ns / 1ns
module DataCompare4_tb;
reg [3:0] iData_a;
reg [3:0] iData_b;
reg [2:0] iData;
wire [2:0] oData;
DataCompare4 uut(.iData_a(iData_a),.iData_b(iData_b),.iData(iData),.oData(oData));
initial 
begin
iData_a=4'b1000;
iData_b=4'b0000;
iData=3'b000;
#5
iData_a=4'b0000;
iData_b=4'b1000;
#5
iData_a=4'b1100;
iData_b=4'b1000;
#5
iData_a=4'b1000;
iData_b=4'b1100;
#5
iData_a=4'b1110;
iData_b=4'b1100;
#5
iData_a=4'b1100;
iData_b=4'b1110;
#5
iData_a=4'b1111;
iData_b=4'b1110;
#5
iData_a=4'b1110;
iData_b=4'b1111;
#5
iData_a=4'b1000;
iData_b=4'b1000;
iData=3'b100;
#5
iData_a=4'b1000;
iData_b=4'b1000;
iData=3'b010;
#5
iData_a=4'b1000;
iData_b=4'b1000;
iData=3'b001;
end
endmodule
