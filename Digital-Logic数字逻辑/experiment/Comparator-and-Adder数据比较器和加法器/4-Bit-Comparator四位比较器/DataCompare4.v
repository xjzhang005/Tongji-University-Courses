`timescale 1ns / 1ns
module DataCompare4(
   input [3:0] iData_a, //�������� a
   input [3:0] iData_b, //�������� b
   input [2:0] iData, //��������a>b��a<b��a=b
   output [2:0] oData //������ A>B��A<B��A=B
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
