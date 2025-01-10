`timescale 1ns / 1ns
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
