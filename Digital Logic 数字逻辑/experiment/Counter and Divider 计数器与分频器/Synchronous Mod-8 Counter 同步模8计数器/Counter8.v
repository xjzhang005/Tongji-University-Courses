`timescale 1ns / 1ns
//下面是JK触发器的modulesim
module JK_FF(
input CLK, //时钟信号，上升沿有效
 input J, //输入信号 J
 input K, //输入信号 K
input RST_n, //复位信号，低电平有效
 output reg Q1,//输出信号 Q
 output reg Q2 //输出信号~Q
    );
    initial
    begin
    Q1<=0;
    Q2<=1;
    end
    always @( posedge CLK or negedge RST_n)
    begin
    if(!RST_n)//强制清零有效
    begin
    Q1<=1'b0;
    Q2<=1'b1;
    end
    else//强制清零无效
    begin
    if(J==0 && K==0)
    begin
   // Q1<=Q1;
   // Q2<=Q2;
    end
    else if(J==0 && K==1)
    begin
    Q1<=1'b0;
    Q2<=1'b1;
    end
    else if(J==1 && K==0)
    begin
     Q1<=1'b1;
     Q2<=1'b0;
    end 
    else if(J==1 && K==1)
    begin
    Q1<=~Q1;
    Q2<=~Q2;
    end
    end
    end
endmodule
//下面是七段数码管的modulesim
module display7(
input [3:0] iData,//四位输入 D3~D0
output [6:0] oData //七位译码输出 g~a
    );
   assign oData[6]=(~iData[0]&~iData[1]&~iData[2]&~iData[3])|
                   (iData[0]&~iData[1]&~iData[2]&~iData[3])|
                   (iData[0]&iData[1]&iData[2]&~iData[3]);
    assign oData[5]=(iData[0]&~iData[1]&~iData[2]&~iData[3])|
                    (~iData[0]&iData[1]&~iData[2]&~iData[3])|
                    (iData[0]&iData[1]&~iData[2]&~iData[3])|
                    (iData[0]&iData[1]&iData[2]&~iData[3]);
    assign oData[4]=(iData[0]&~iData[1]&~iData[2]&~iData[3])|
                     (iData[0]&iData[1]&~iData[2]&~iData[3])|
                     (~iData[0]&~iData[1]&iData[2]&~iData[3])|
                     (iData[0]&~iData[1]&iData[2]&~iData[3])|
                     (iData[0]&iData[1]&iData[2]&~iData[3])|
                     (iData[0]&~iData[1]&~iData[2]&iData[3]);
    assign oData[3]=(iData[0]&~iData[1]&~iData[2]&~iData[3])|
                     (~iData[0]&~iData[1]&iData[2]&~iData[3])|
                     (iData[0]&iData[1]&iData[2]&~iData[3]);
   assign oData[2]=(~iData[0]&iData[1]&~iData[2]&~iData[3]);
   assign oData[1]=(iData[0]&~iData[1]&iData[2]&~iData[3])|
                   (~iData[0]&iData[1]&iData[2]&~iData[3]);
   assign oData[0]=(iData[0]&~iData[1]&~iData[2]&~iData[3])|
                    (~iData[0]&~iData[1]&iData[2]&~iData[3]);
endmodule
module Counter8(
input CLK, //时钟信号，上升沿有效
input rst_n, //复位信号，低电平有效//异步复位信号
output reg [2:0] oQ, //二进制计数器输出
output  [6:0] oDisplay //七段数字显示管输出
    );
    wire [3:0]outQ;//JK触发器的输出辅助信号
    wire [2:0]foutQ;//JK触发器的反输出辅助信号
   // reg [3:0]idata;//输出信号
   assign outQ[3]=1'b0;
    JK_FF uut1(.CLK(CLK),.J(1'b1),.K(1'b1),.RST_n(rst_n),.Q1(outQ[0]),.Q2(foutQ[0]));
    JK_FF uut2(.CLK(CLK),.J(outQ[0]),.K(outQ[0]),.RST_n(rst_n),.Q1(outQ[1]),.Q2(foutQ[1]));
    JK_FF uut3(.CLK(CLK),.J(outQ[0]&&outQ[1]),.K(outQ[0]&&outQ[1]),.RST_n(rst_n),.Q1(outQ[2]),.Q2(foutQ[2]));
     display7 uut4 (.iData(outQ),.oData(oDisplay));
   // always @(outQ or negedge rst_n or posedge CLK)
  // always @(posedge CLK  or negedge rst_n)
   always @(outQ )
    begin
   // if(rst_n)
  //  begin
    oQ[0]<=outQ[0];
    oQ[1]<=outQ[1];
    oQ[2]<=outQ[2];
   // idata={1'b0,oQ};
  //  if(rst_n==0)
  //  begin
   // oQ=3'b000;
  //  idata<=4'b0000;
 //   end
  //  end
  //  else
  //  begin
   //  idata<=4'b0000;
 //  if(rst_n==0)
   //      oQ<=3'b000;
 //   end
    end
   // always @(negedge rst_n)
   //    begin
   //      idata=4'b0000;
   //      oQ=3'b000;
  //     end
  endmodule  
  //  wire [3:0]mid;
  //  wire [2:0] fQ;
  //  wire bone;
  //     assign hone=1'b1;
  //     assign mid[3]=1'b0;
  //     assign mid[0]=oQ[0];
   //    assign mid[1]=oQ[1];
   //    assign mid[2]=oQ[2];
   //          JK_FF uut0 (CLK,hone,hone,rst_n,oQ[0],fQ[0]);
   //          JK_FF uut1 (CLK,oQ[0],oQ[0],rst_n,oQ[1],fQ[1]);
  //           JK_FF uut2 (CLK,oQ[0]&&oQ[1],oQ[0]&&oQ[1],rst_n,oQ[2],fQ[2]);
   //           display7 uut3(mid,oDisplay);
   

