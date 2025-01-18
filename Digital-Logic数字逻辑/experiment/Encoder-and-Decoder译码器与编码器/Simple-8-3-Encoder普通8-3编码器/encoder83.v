`timescale 1ns / 1ns
module encoder83(
input [7:0] iData, //��λ���� D7~D0,�ߵ�ƽ��Ч
output [2:0] oData //��λ������� Y2~Y0
    );
   // assign oData[0]=(iData[7]&~iData[6]&~iData[5]&~iData[4]&~iData[3]&~iData[2]&~iData[1]&~iData[0])|
    //                (~iData[7]&~iData[6]&iData[5]&~iData[4]&~iData[3]&~iData[2]&~iData[1]&~iData[0])|
    //                (~iData[7]&~iData[6]&~iData[5]&~iData[4]&iData[3]&~iData[2]&~iData[1]&~iData[0])|
    //                (~iData[7]&~iData[6]&~iData[5]&~iData[4]&~iData[3]&~iData[2]&iData[1]&~iData[0]);
   // assign oData[1]=(iData[7]&~iData[6]&~iData[5]&~iData[4]&~iData[3]&~iData[2]&~iData[1]&~iData[0])|
   //                 (~iData[7]&iData[6]&~iData[5]&~iData[4]&~iData[3]&~iData[2]&~iData[1]&~iData[0])|                
    //                (~iData[7]&~iData[6]&~iData[5]&~iData[4]&iData[3]&~iData[2]&~iData[1]&~iData[0])|
    //                (~iData[7]&~iData[6]&~iData[5]&~iData[4]&~iData[3]&iData[2]&~iData[1]&~iData[0]);
   // assign oData[2]=(iData[7]&~iData[6]&~iData[5]&~iData[4]&~iData[3]&~iData[2]&~iData[1]&~iData[0])|
    //                 (~iData[7]&iData[6]&~iData[5]&~iData[4]&~iData[3]&~iData[2]&~iData[1]&~iData[0])|
   //                  (~iData[7]&~iData[6]&iData[5]&~iData[4]&~iData[3]&~iData[2]&~iData[1]&~iData[0])|
    //                 (~iData[7]&~iData[6]&~iData[5]&iData[4]&~iData[3]&~iData[2]&~iData[1]&~iData[0]);  
    assign oData[0]=iData[1]|iData[3]|iData[5]|iData[7];
    assign oData[1]=iData[7]|iData[6]|iData[3]|iData[2];
    assign oData[2]=iData[7]|iData[6]|iData[5]|iData[4];                              
endmodule
