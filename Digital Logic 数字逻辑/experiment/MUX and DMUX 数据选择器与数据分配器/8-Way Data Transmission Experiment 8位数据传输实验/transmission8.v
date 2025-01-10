`timescale 1ns / 1ns
module selector81(
input [7:0] iData, //输入信号 D7~D0
input A,B,C, //选择信号 S2~S0 
output iZ
);
assign iZ=(A==0&&B==0&&C==0)?iData[0]:
          (A==0&&B==0&&C==1)?iData[1]:
          (A==0&&B==1&&C==0)?iData[2]:
          (A==0&&B==1&&C==1)?iData[3]:
          (A==1&&B==0&&C==0)?iData[4]:
          (A==1&&B==0&&C==1)?iData[5]:
          (A==1&&B==1&&C==0)?iData[6]:iData[7];
endmodule

module de_selector18(
input A,B,C, //选择信号 S2~S0 
input iZ,
output [7:0] oData //输出信号 f0~f7 
);
     assign oData[0]=A|B|C|iZ;
     assign oData[1]=A|B|~C|iZ;
     assign oData[2]=A|~B|C|iZ;
     assign oData[3]=A|~B|~C|iZ;
     assign oData[4]=~A|B|C|iZ;
     assign oData[5]=~A|B|~C|iZ;
     assign oData[6]=~A|~B|C|iZ;
     assign oData[7]=~A|~B|~C|iZ;
endmodule

module transmission8(
 input [7:0] iData, //输入信号 D7~D0
input A,B,C, //选择信号 S2~S0 
output [7:0] oData //输出信号 f0~f7 
    );
    wire  iZ;
  selector81 u1( iData, A,B,C,iZ);
  de_selector18 u2(A,B,C,iZ,oData);
endmodule
