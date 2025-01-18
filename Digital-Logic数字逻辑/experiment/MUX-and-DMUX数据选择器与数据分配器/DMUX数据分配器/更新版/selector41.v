`timescale 1ns / 1ns
module selector41(
input [3:0] iC0,
input [3:0] iC1,
input [3:0] iC2,
input [3:0] iC3,
input iS1,
input iS0,
output [3:0] oZ
    );
    assign oZ = (iS1==0&&iS0==0)?iC0:
               (iS1==0&&iS0==1)?iC1:
               (iS1==1&&iS0==0)?iC2:iC3;
endmodule
