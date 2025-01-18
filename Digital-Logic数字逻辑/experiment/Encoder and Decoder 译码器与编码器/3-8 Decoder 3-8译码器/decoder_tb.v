`timescale 1ns / 1ns
module decoder_tb;
reg [2:0] iData; //三位输入 D2,D1,D0   //D0=iData[0],D1=iData[1],D2=iData[2]
reg [1:0] iEna; //使能信号 G1,G2       //G1=iEna[1],G2=iEna[0]
wire [7:0] oData; //八位译码输出? 7    //八位依次对应
decoder uut (.iData(iData),.iEna(iEna),.oData(oData));
initial
begin
//iEna[0]=0;
//iEna[1]=1;
iEna[0]=1;
iEna[1]=0;
//#10 iEna[0]=1;
//    iEna[1]=0;
#10 iEna[0]=0;
    iEna[1]=1;
end
initial
begin
iData[0]=0;
#10 iData[0]=0;
#10 iData[0]=1;   
#10 iData[0]=0;
#10 iData[0]=1; 
#10 iData[0]=0;
#10 iData[0]=1; 
#10 iData[0]=0;
#10 iData[0]=1; 
end
initial
begin 
iData[1]=0;
#10 iData[1]=0;
#10 iData[1]=0;
#10 iData[1]=1;
#10 iData[1]=1;
#10 iData[1]=0;
#10 iData[1]=0;
#10 iData[1]=1;
#10 iData[1]=1;
end
initial
begin
iData[2]=0;
#10 iData[2]=0;
#10 iData[2]=0;
#10 iData[2]=0;
#10 iData[2]=0;
#10 iData[2]=1;
#10 iData[2]=1;
#10 iData[2]=1;
#10 iData[2]=1;
end
endmodule
