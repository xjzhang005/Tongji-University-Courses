`timescale 1ns / 1ns
module encoder83_tb;
reg [7:0] iData;
wire [2:0] oData;
encoder83 uut (.iData(iData),.oData(oData));
initial
begin
iData=8'b00000000;
#20 iData[7]=1;
#20 iData[7]=0;
    iData[6]=1;
#20 iData[6]=0;
    iData[5]=1;
#20 iData[5]=0;
    iData[4]=1;
#20 iData[4]=0;
    iData[3]=1;
#20 iData[3]=0;
   iData[2]=1;
#20 iData[2]=0;
   iData[1]=1;
#20 iData[1]=0;
    iData[0]=1;
#20 iData[0]=0;
end
endmodule
