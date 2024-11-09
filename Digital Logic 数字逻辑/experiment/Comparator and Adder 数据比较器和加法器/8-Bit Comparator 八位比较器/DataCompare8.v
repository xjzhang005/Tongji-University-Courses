`timescale 1ns / 1ns
module DataCompare4(
   input [3:0] iData_a, //输入数据 a
   input [3:0] iData_b, //输入数据 b
   input [2:0] iData, //级联输入a>b、a<b、a=b
   output [2:0] oData //结果输出 A>B、A<B、A=B
    );
   assign oData[2]=(iData_a[3]>iData_b[3])
                 ||((iData_a[3]==iData_b[3])&&(iData_a[2]>iData_b[2]))
                 ||((iData_a[3]==iData_b[3])&&(iData_a[2]==iData_b[2])&&(iData_a[1]>iData_b[1]))
                 ||((iData_a[3]==iData_b[3])&&(iData_a[2]==iData_b[2])&&(iData_a[1]==iData_b[1])&&(iData_a[0]>iData_b[0]))
                 ||((iData_a[3]==iData_b[3])&&(iData_a[2]==iData_b[2])&&(iData_a[1]==iData_b[1])&&(iData_a[0]==iData_b[0])&&(iData[2]==1));
   assign oData[1]=(iData_a[3]<iData_b[3])
                 ||((iData_a[3]==iData_b[3])&&(iData_a[2]<iData_b[2]))
                 ||((iData_a[3]==iData_b[3])&&(iData_a[2]==iData_b[2])&&(iData_a[1]<iData_b[1]))
                 ||((iData_a[3]==iData_b[3])&&(iData_a[2]==iData_b[2])&&(iData_a[1]==iData_b[1])&&(iData_a[0]<iData_b[0]))
                 ||((iData_a[3]==iData_b[3])&&(iData_a[2]==iData_b[2])&&(iData_a[1]==iData_b[1])&&(iData_a[0]==iData_b[0])&&(iData[1]==1));
   assign oData[0]=((iData_a[3]==iData_b[3])&&(iData_a[2]==iData_b[2])&&(iData_a[1]==iData_b[1])&&(iData_a[0]==iData_b[0])&&(iData[0]==1));
endmodule

module DataCompare8(
    input [7:0] iData_a, //输入数据 a
    input [7:0] iData_b, //输入数据 b
    output [2:0] oData //结果输出
    );
    wire [2:0]iData_low;
    wire [2:0]oData_low;
    wire [3:0]iData_low_a;
    wire [3:0]iData_low_b;
    wire [3:0]iData_high_a;
    wire [3:0]iData_high_b;
  // assign  iData_low_a=iData_a[3:0];
  assign iData_low_a[3]=iData_a[3];
  assign iData_low_a[2]=iData_a[2];
  assign iData_low_a[1]=iData_a[1];
  assign iData_low_a[0]=iData_a[0];
 //  assign iData_low_b=iData_b[3:0];
  assign iData_low_b[3]=iData_b[3];
 assign iData_low_b[2]=iData_b[2];
 assign iData_low_b[1]=iData_b[1];
 assign iData_low_b[0]=iData_b[0];
 
  // assign  iData_high_a=iData_a[7:4];
  assign iData_high_a[3]=iData_a[7];
  assign iData_high_a[2]=iData_a[6];
  assign iData_high_a[1]=iData_a[5];
  assign iData_high_a[0]=iData_a[4];
  
 //  assign iData_high_b=iData_b[7:4];   
  assign iData_high_b[3]=iData_b[7];
  assign iData_high_b[2]=iData_b[6];
  assign iData_high_b[1]=iData_b[5];
  assign iData_high_b[0]=iData_b[4];
 //  assign iData_low=3'b001;
 assign iData_low[0]=1;
 assign iData_low[1]=0;
 assign iData_low[2]=0;
      DataCompare4 low( iData_low_a,iData_low_b,iData_low,oData_low);
      DataCompare4 high( iData_high_a,iData_high_b,oData_low,oData);
endmodule
