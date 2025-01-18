`timescale 1ns / 1ns
module encoder83_Pri_tb;
reg [7:0]iData;
reg iEI;
wire [2:0]oData;
wire oEO;
encoder83_Pri uut(.iData(iData),.iEI(iEI),.oData(oData),.oEO(oEO));
initial
begin
iEI=1;
#10 iEI=0;
     iData=8'b11111111;    
#10 iData[7]=0;
#10 iData[7]=1;
    iData[6]=0;
#10 iData[6]=1;
    iData[5]=0;
#10 iData[5]=1;
   iData[4]=0;
#10 iData[4]=1;
    iData[3]=0;
#10 iData[3]=1;
    iData[2]=0;
#10 iData[2]=1;
   iData[1]=0;
#10 iData[1]=1;
    iData[0]=0;
#10 iData[0]=1;
end    
endmodule
