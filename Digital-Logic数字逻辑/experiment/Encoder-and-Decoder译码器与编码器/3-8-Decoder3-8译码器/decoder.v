`timescale 1ns / 1ns
module decoder(
input [2:0] iData, //��λ���� D2,D1,D0   //D0=iData[0],D1=iData[1],D2=iData[2]
input [1:0] iEna, //ʹ���ź� G1,G2       //G1=iEna[1],G2=Iena[0]
output [7:0] oData //��λ�������? 7    //��λ���ζ�Ӧ
    );
  //  assign oData[0]=~iEna[0]|iEna[1]|iData[0]|iData[1]|iData[2];//~G1+G2+D1+D2+D3
  //  assign oData[1]=~iEna[0]|iEna[1]|~iData[0]|iData[1]|iData[2];//~G1+G2+D1+D2+~D3
  //  assign oData[2]=~iEna[0]|iEna[1]|iData[0]|~iData[1]|iData[2];//~G1+G2+D1+~D2+D3
  //  assign oData[3]=~iEna[0]|iEna[1]|~iData[0]|~iData[1]|iData[2];//~G1+G2+D1+~D2+~D3
  //  assign oData[4]=~iEna[0]|iEna[1]|iData[0]|iData[1]|~iData[2];//~G1+G2+~D1+D2+D3
 //   assign oData[5]=~iEna[0]|iEna[1]|~iData[0]|iData[1]|~iData[2];//~G1+G2+~D1+D2+~D3
 //   assign oData[6]=~iEna[0]|iEna[1]|iData[0]|~iData[1]|~iData[2];//~G1+G2+~D1+~D2+D3
  //  assign oData[7]=~iEna[0]|iEna[1]|~iData[0]|~iData[1]|~iData[2];//~G1+G2+~D1+~D2+~D3
   assign oData[0]=iEna[0]|~iEna[1]|iData[0]|iData[1]|iData[2];//~G1+G2+D1+D2+D3
     assign oData[1]=iEna[0]|~iEna[1]|~iData[0]|iData[1]|iData[2];//~G1+G2+D1+D2+~D3
     assign oData[2]=iEna[0]|~iEna[1]|iData[0]|~iData[1]|iData[2];//~G1+G2+D1+~D2+D3
     assign oData[3]=iEna[0]|~iEna[1]|~iData[0]|~iData[1]|iData[2];//~G1+G2+D1+~D2+~D3
     assign oData[4]=iEna[0]|~iEna[1]|iData[0]|iData[1]|~iData[2];//~G1+G2+~D1+D2+D3
     assign oData[5]=iEna[0]|~iEna[1]|~iData[0]|iData[1]|~iData[2];//~G1+G2+~D1+D2+~D3
     assign oData[6]=iEna[0]|~iEna[1]|iData[0]|~iData[1]|~iData[2];//~G1+G2+~D1+~D2+D3
     assign oData[7]=iEna[0]|~iEna[1]|~iData[0]|~iData[1]|~iData[2];//~G1+G2+~D1+~D2+~D3
endmodule
