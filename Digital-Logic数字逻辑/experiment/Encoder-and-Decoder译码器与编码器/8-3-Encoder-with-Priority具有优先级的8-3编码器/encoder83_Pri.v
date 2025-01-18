`timescale 1ns / 1ns
module encoder83_Pri(iData,iEI,oData,oEO
//input [7:0] iData, //��λ����??7~??0,�͵�ƽ��Ч
//input iEI, //ѡͨ�����ź� EI,�͵�ƽ��Ч
//output [2:0] oData, //��λ�������?3
//output oEO //��չ����ź� EO,�ߵ�ƽ��Ч
    );
    input [7:0] iData; //��λ����??7~??0,�͵�ƽ��Ч
    input iEI; //ѡͨ�����ź� EI,�͵�ƽ��Ч
    output [2:0] oData; //��λ�������?3
    output oEO; //��չ����ź� EO,�ߵ�ƽ��Ч
    reg [2:0] oData ;
    reg oEO;
    always @(*)
    begin//always begin
    if(iEI==1)
    begin //if iEI==1 begin
    oData=3'b111;
    oEO=1;
   end// if iEI==1 end
   else//iEI==0 
   begin//iEI==0 begin
   if(iData==8'b11111111)
   begin//if iData=11111111 begin 
   oData=3'b111;
   oEO=0;
     end//if iData=11111111 end
     else//iEI==0��iData!=1*8
     begin///iEI==0��iData!=1*8 begin
     oEO=1;
     casex(iData)
    // 8'b0zzzzzzz:
    8'b0???????:
     begin
      //oData=3'b000;
      oData[0]=0;
      oData[1]=0;
      oData[2]=0;
      end
    // 8'b10zzzzzz:
    8'b10??????:
     begin
     // oData=3'b001;
     oData[0]=1;
     oData[1]=0;
     oData[2]=0;
      end
    // 8'b110zzzzz: 
    8'b110?????:
     begin
    // oData=3'b010;
    oData[0]=0;
    oData[1]=1;
    oData[2]=0;
     end
   //  8'b1110zzzz: 
   8'b1110????:
     begin
    // oData=3'b011;
    oData[0]=1;
    oData[1]=1;
    oData[2]=0;    
     end
    // 8'b11110zzz: 
    8'b11110???:
     begin
    // oData=3'b100;
    oData[0]=0;
    oData[1]=0;
    oData[2]=1;
     end
   //  8'b111110zz: 
   8'b111110??:
     begin
    // oData=3'b101;
    oData[0]=1;
   oData[1]=0;
    oData[2]=1;
     end
     8'b1111110?:
     begin
    //  oData=3'b110;
    oData[0]=0;
    oData[1]=1;
    oData[2]=1;
     end
   //  8'b11111110:
   8'b11111110:
     begin
     //oData=3'b111;
     oData[0]=1;
     oData[1]=1;
     oData[2]=1;
     end
     default :  oData=3'b111;
     endcase
     end///iEI==0��iData!=1*8 end
     end///iEI==0 end    
     end//always end
endmodule
