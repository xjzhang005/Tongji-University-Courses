`timescale 1ns/1ns 
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/09/25 20:32:49
// Design Name: 
// Module Name: logic_gates_1
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


module logic_gates_1(iA,iB,oAnd,oOr,oNot); 
input iA, iB; 
output oAnd,oOr,oNot; 
and and_inst(oAnd, iA,iB); 
or or_inst(oOr, iA,iB); 
not not_inst(oNot, iA); 
endmodule
