`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/09/25 23:45:47
// Design Name: 
// Module Name: logic_gates_3
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

module logic_gates_3(iA,iB,oAnd,oOr,oNot); 
input iA, iB; 
output oAnd,oOr,oNot; 
reg oAnd, oOr, oNot; 
  always @ (*) 
  begin 
  oAnd = iA & iB; 
  oOr = iA | iB; 
  oNot = ~ iA; 
   end 
endmodule
