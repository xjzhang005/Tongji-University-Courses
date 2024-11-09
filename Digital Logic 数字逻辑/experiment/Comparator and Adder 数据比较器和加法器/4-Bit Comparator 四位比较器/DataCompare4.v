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
