`timescale 1ns / 1ns
module alu(
input [31:0] a, //32 位输入，操作数 1
input [31:0] b, //32 位输入，操作数 2
input [3:0] aluc, //4 位输入，控制 alu 的操作
output  [31:0] r, //32 位输出，由 a、b 经过 aluc 指定的操作生成
output  zero, //0 标志位
output  carry, // 进位标志位
output  negative, // 负数标志位
output  overflow // 溢出标志位
    );
  wire [31:0] out0,out1,out2,out3,out4,out5,out6,out7,out8,out9,out10,out11,out12,out13;
  wire [13:0] mycarry,myzero,mynegative,myoverflow;
 //无符号加法
  assign {mycarry[0],out0}=a+b;
  assign myzero[0]=(out0==0)?1:0;
  assign mynegative[0]=out0[31];
  assign myoverflow[0]=0;
  //有符号加法
 assign  out1=a+b;
 assign myoverflow[1]=((a[31]==b[31])&&(~out1[31]==a[31]))?1:0;
 assign myzero[1]=(out1==0)?1:0;
  assign mynegative[1]=out1[31];
 assign mycarry[1]=0;
 //无符号减法
  assign {mycarry[2],out2}=a-b;
 assign myzero[2]=(out2==0)?1:0;
  assign mynegative[2]=out2[31];
  assign myoverflow[2]=0;
  //有符号减法
  assign out3=a-b;
                   //溢出情况是正数-负数，结果为负数--负数-正数，结果为正数
  assign myoverflow[3]=(a[31]==0&&b[31]==1&&out3[31]==1)||(a[31]==1&&b[31]==0&&out3[31]==0);
  assign myzero[3]=(out3==0)?1:0;
 assign  mycarry[3]=0;
 assign  mynegative[3]=out3[31];
 //按位与
  assign out4=a&b;
  assign myzero[4]=(out4==0)?1:0;
  assign mycarry[4]=0;
  assign  myoverflow[4]=0;
  assign  mynegative[4]=out4[31];
 //按位或
 assign out5=a|b;
  assign myzero[5]=(out5==0)?1:0;
  assign mycarry[5]=0;
  assign myoverflow[5]=0;
  assign mynegative[5]=out5[31];
 //异或
 assign out6=a^b;
 assign  myzero[6]=(out6==0)?1:0;
 assign mycarry[6]=0;
  assign myoverflow[6]=0;
  assign  mynegative[6]=out6[31];
 //nor
 assign out7=~(a|b);
 assign myzero[7]=(out7==0)?1:0;
 assign mycarry[7]=0;
 assign myoverflow[7]=0;
 assign mynegative[7]=out7[31];
 //lui
 assign  out8={b[15:0],16'b0};
 assign mycarry[8]=0;
 assign myoverflow[8]=0;
 assign mynegative[8]=out8[31];
 assign myzero[8]=(out8==0)?1:0;
 //有符号比大小
 assign out9=($signed(a)<$signed(b))?1:0;
 assign myoverflow[9]=0;
 assign mycarry[9]=0;
 assign mynegative[9]=($signed(a)<$signed(b))?1:0;
 assign myzero[9]=(a==b)?1:0;
 //无符号比大小
 assign out10=(a<b)?1:0;
 assign mycarry[10]=(out10==1)?1:0;
 assign myzero[10]=(a==b)?1:0;
  assign mynegative[10]=out10[31];
  assign myoverflow[10]=0;
 //算数右移
 assign out11=($signed(b)>>>a);
 assign mycarry[11]=(a>=1&&a<=32)?b[a-1]:b[31];
  assign myoverflow[11]=0;
  assign mynegative[11]=out11[31];
  assign myzero[11]=(out11==0)?1:0;
 //左移
 assign {mycarry[12],out12}=b<<a;
 assign myoverflow[12]=0;
 assign myzero[12]=(out12==0)?1:0;
 assign mynegative[12]=out12[31];
 //逻辑右移
 assign out13=b>>a;
 assign mycarry[13]=(a>=1&&a<=32)?b[a-1]:1'b0;
 assign  myoverflow[13]=0;
 assign myzero[13]=(out13==0)?1:0;
 assign mynegative[13]=out13[31];
 
 //下面是结果的赋值
 assign r=(aluc==4'b0000)?out0:
           (aluc==4'b0010)?out1:
           (aluc==4'b0001)?out2:
           (aluc==4'b0011)?out3:
           (aluc==4'b0100)?out4:
           (aluc==4'b0101)?out5:
           (aluc==4'b0110)?out6:
           (aluc==4'b0111)?out7:
           (aluc==4'b1000)?out8:
           (aluc==4'b1001)?out8:
           (aluc==4'b1011)?out9:
           (aluc==4'b1010)?out10:
           (aluc==4'b1100)?out11:
           (aluc==4'b1110)?out12:
           (aluc==4'b1111)?out12:
           out13;// (aluc==4'b1101)
        assign zero= (aluc==4'b0000)?myzero[0]:
                     (aluc==4'b0010)?myzero[1]:
                     (aluc==4'b0001)?myzero[2]:
                     (aluc==4'b0011)?myzero[3]:
                     (aluc==4'b0100)?myzero[4]:
                     (aluc==4'b0101)?myzero[5]:
                     (aluc==4'b0110)?myzero[6]:
                     (aluc==4'b0111)?myzero[7]:
                     (aluc==4'b1000)?myzero[8]:
                     (aluc==4'b1001)?myzero[8]:
                     (aluc==4'b1011)?myzero[9]:
                     (aluc==4'b1010)?myzero[10]:
                     (aluc==4'b1100)?myzero[11]:
                     (aluc==4'b1110)?myzero[12]:
                     (aluc==4'b1111)?myzero[12]:
                     myzero[13];// (aluc==4'b1101)         
 assign carry= (aluc==4'b0000)?mycarry[0]:
               (aluc==4'b0010)?mycarry[1]:
               (aluc==4'b0001)?mycarry[2]:
               (aluc==4'b0011)?mycarry[3]:
               (aluc==4'b0100)?mycarry[4]:
               (aluc==4'b0101)?mycarry[5]:
               (aluc==4'b0110)?mycarry[6]:
               (aluc==4'b0111)?mycarry[7]:
               (aluc==4'b1000)?mycarry[8]:
               (aluc==4'b1001)?mycarry[8]:
               (aluc==4'b1011)?mycarry[9]:
               (aluc==4'b1010)?mycarry[10]:
               (aluc==4'b1100)?mycarry[11]:
               (aluc==4'b1110)?mycarry[12]:
               (aluc==4'b1111)?mycarry[12]:
                mycarry[13];// (aluc==4'b1101)   
  assign negative= (aluc==4'b0000)?mynegative[0]:
                   (aluc==4'b0010)?mynegative[1]:
                   (aluc==4'b0001)?mynegative[2]:
                   (aluc==4'b0011)?mynegative[3]:
                   (aluc==4'b0100)?mynegative[4]:
                   (aluc==4'b0101)?mynegative[5]:
                   (aluc==4'b0110)?mynegative[6]:
                   (aluc==4'b0111)?mynegative[7]:
                   (aluc==4'b1000)?mynegative[8]:
                   (aluc==4'b1001)?mynegative[8]:
                   (aluc==4'b1011)?mynegative[9]:
                   (aluc==4'b1010)?mynegative[10]:
                   (aluc==4'b1100)?mynegative[11]:
                   (aluc==4'b1110)?mynegative[12]:
                   (aluc==4'b1111)?mynegative[12]:
                    mynegative[13];// (aluc==4'b1101)  
 assign overflow= (aluc==4'b0000)?myoverflow[0]:
              (aluc==4'b0010)?myoverflow[1]:
              (aluc==4'b0001)?myoverflow[2]:
              (aluc==4'b0011)?myoverflow[3]:
              (aluc==4'b0100)?myoverflow[4]:
              (aluc==4'b0101)?myoverflow[5]:
              (aluc==4'b0110)?myoverflow[6]:
              (aluc==4'b0111)?myoverflow[7]:
              (aluc==4'b1000)?myoverflow[8]:
              (aluc==4'b1001)?myoverflow[8]:
              (aluc==4'b1011)?myoverflow[9]:
              (aluc==4'b1010)?myoverflow[10]:
              (aluc==4'b1100)?myoverflow[11]:
              (aluc==4'b1110)?myoverflow[12]:
              (aluc==4'b1111)?myoverflow[12]:
               myoverflow[13];// (aluc==4'b1101)                                       
endmodule
