`timescale 1ns / 1ns
module DataCompare8_tb;
   reg [7:0] iData_a;
   reg [7:0] iData_b;
   wire[2:0] oData;
   DataCompare8 test(.iData_a(iData_a),.iData_b(iData_b),.oData(oData));
   initial
   begin
   iData_a=8'b0000_0000;
   iData_b=8'b0000_0000;
   #10 
   iData_a=8'b0000_0000;
   iData_b=8'b0000_0001;
      #10
   iData_a=8'b1000_0000;
   iData_b=8'b1000_0000;
   #10
       iData_a=8'b0000_0001;
       iData_b=8'b0000_0001;
      #10
       iData_a=8'b1100_0000;
       iData_b=8'b1000_0000;
      #10
       iData_a=8'b1000_0000;
       iData_b=8'b1100_0000;
       #10
       iData_a=8'b1110_0000;
       iData_b=8'b1100_0000;
       #10
       iData_a=8'b1100_0000;
       iData_b=8'b1110_0000;
       #10
       iData_a=8'b1111_0000;
       iData_b=8'b1110_0000;
       #10
       iData_a=8'b1110_0000;
       iData_b=8'b1111_0000;
       #10
       iData_a=8'b1111_1000;
       iData_b=8'b1111_0000;
       #10
       iData_a=8'b1111_0000;
       iData_b=8'b1111_1000;
       #10
       iData_a=8'b1111_1100;
       iData_b=8'b1111_1000;
       #10
       iData_a=8'b1111_1000;
       iData_b=8'b1111_1100;
       #10
       iData_a=8'b1111_1110;
       iData_b=8'b1111_1100;
       #10
       iData_a=8'b1111_1100;
       iData_b=8'b1111_1110;   
       #10
       iData_a=8'b1111_1111;
       iData_b=8'b1111_1110;
       #10
       iData_a=8'b1111_1110;
       iData_b=8'b1111_1111;   
       #10
        iData_a=8'b1111_1111;
        iData_b=8'b1111_1111;   
    end
endmodule
