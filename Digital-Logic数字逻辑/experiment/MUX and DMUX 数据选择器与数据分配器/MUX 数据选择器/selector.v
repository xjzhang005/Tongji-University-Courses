`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/09/23 16:31:38
// Design Name: 
// Module Name: selector
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


module selector41(
    input [3:0] iC0,
    input [3:0] iC1,
    input [3:0] iC2,
    input [3:0] iC3,
    input iS1,
    input iS0,
    output [3:0] oZ
    );
assign oZ = iS1?(iS0 ? iC3:iC2):(iS0 ? iC1:iC0);
//��{iS1,iS0}=11 ����� iC3;��{iS1,iS0}=10 ����� iC2;��{iS1,iS0}=01 ����� iC1;
//��{iS1,iS0}=00 ����� iC0
endmodule
