
#include <Servo.h>
Servo myservo;  
/*Khai bao*/
int btn_stt = 0;  // chua gia tri trang thai chuc nang dieu khien bang bluetooh
/*Cac chan vi dieu khien duoc noi nhu khai bao gia tri ben duoi*/
const int trig = 12;     
const int echo = 13;   
const int btn=2;  
int inA1=6;           
int inB1=9;           
int inA2=8;            
int inB2=10;
int enA=5;
int enB=11;            
int dongCoServo=4;     
/*Khai bao bien*/
int gioiHan = 15;
unsigned long thoigian = 0; 
int khoangCach = 0;           
int khoangCachTrai = 0, khoangCachPhai = 0; // luu gia tri khoang cach
char bt = ''; 
/*========================API=======================*/
/*Ham thuc hien chuc nang do khoang cach tu cam bien toi vat can*/
void DoKhoangCach();
/*Xe di thang*/
void DiThang();
/*Xe re trai*/
void DiSangTrai();
/*Xe re phai*/
void DiSangPhai();
/*Xe di lui*/
void DiLui();
/*Reset dong co*/
void ResetDongCo();
/*Cam bien quay sang phai va do khoang cach toi vat can*/
void QuaycbSangPhai();
/*Cam bien quay sang trai va do khoang cach toi vat can*/
void QuaycbSangTrai();
/*Motor A tien*/
void motorA_tien();
/*Motor A lui*/
void motorA_lui();
/*Motor A tat*/
void motorA_dung();
/*Motor B tien*/
void motorB_tien();
/*Motor B dung*/
void motorB_dung();
/*Motor B lui*/
void motorB_lui();
/*Ham co chuc nang xe tu dong di chuyen tranh vat can*/
void TranhVatCan();
/*Ham co chuc nang xe di chuyen bang cach dieu khien qua bluetooh*/
void BlueTooh();
/**/
void Check(char bt);
/*Ham khai bao chuc nang cac chan cua vi dieu khien*/
void setup() {
    myservo.attach(4);
    pinMode(sensorLeft, INPUT);
    pinMode(sensorRight,INPUT);  

    pinMode(trig,OUTPUT);   
    pinMode(echo,INPUT);    
    
    pinMode(inA1,OUTPUT); 
    pinMode(inA2,OUTPUT); 

    pinMode(inB1,OUTPUT); 
    pinMode(inB2,OUTPUT); 

    pinMode(enA,OUTPUT);
    pinMode(enB,OUTPUT);

    pinMode(btn,INPUT);
    digitalWrite(btn,HIGH);
    Serial.begin(9600);
    myservo.write(90);    
    delay(500);  
}
/*Ham thuc hien chuc nang tranh vat can hoac dieu khien qua bluetooh*/
void loop() 
{
  btn_stt = digitalRead(btn); // kiem tra trang thai nut nhan
  if(btn_stt == 0){
    TranhVatCan();  // xe o che do tu dong di chuyen tranh vat can
  }
  else
  {  
    BlueTooh();    // xe o che do dieu khien bang bluetooh
  } 
Serial.println(btn_stt);
}
/*========================FUNTION========================*/
void motorA_dung(){
  digitalWrite(inA1,LOW);
  digitalWrite(inA2,LOW);
}
void motorA_tien(){
  digitalWrite(inA1,HIGH);
  digitalWrite(inA2,LOW);
  analogWrite(enA,85); // dieu chinh toc do dong co
}
void motorA_lui(){
  digitalWrite(inA1,LOW);
  digitalWrite(inA2,HIGH);
  analogWrite(enA,85);// dieu chinh toc do dong co
}
void motorB_dung(){
  digitalWrite(inB1,LOW);
  digitalWrite(inB2,LOW);
}
void motorB_tien(){
  digitalWrite(inB1,HIGH);
  digitalWrite(inB2,LOW);
  analogWrite(enB,85);// dieu chinh toc do dong co
}
void motorB_lui(){
  digitalWrite(inB1,LOW);
  digitalWrite(inB2,HIGH);
  analogWrite(enB,85);// dieu chinh toc do dong co
}
void DiThang()
{ 
  motorA_tien();
  motorB_tien();
}         

void DiSangTrai()
{
  resetDongCo();
  motorA_tien();
  motorB_lui();
  delay(250);   
}
void DiSangPhai()
{
  resetDongCo();
  motorB_tien();
  motorA_lui();
  delay(250); 
  
}
void DiLui()
{
resetDongCo();
motorA_lui();
motorB_lui();
delay(250);
}

void ResetDongCo()
{
  digitalWrite(inA1,LOW);
  digitalWrite(inB1,LOW);
  digitalWrite(inA2,LOW);
  digitalWrite(inB2,LOW);
}

void DoKhoangCach()
{
    digitalWrite(trig,0);   // tat chan trig
    delayMicroseconds(2);
    digitalWrite(trig,1);   // phat xung chan trig
    delayMicroseconds(10);   // xung dai 5microseconds
    digitalWrite(trig,0);   // tat chan trig
    //Do do rong xung HIGH o chan echo 
    thoigian = pulseIn(echo,HIGH);  
    //Tinh khoang cach den vat
    khoangCach = int(thoigian/2/29.412);
}
void QuaycbSangTrai()
{
    myservo.write(20);              
    delay(1000);
    DoKhoangCach();
    myservo.write(90);               
}
void QuaycbSangPhai()
{
    myservo.write(180);              
    delay(1000);
    DoKhoangCach();
    myservo.write(90);             
}
void Check(char bt){
  if(bt=='R')
    {

        DiSangPhai();
    }
   if(bt=='L')
    {

        DiSangTrai();
    }
    if(bt=='F')
    {
        DiThang();
    }
    if(bt=='B')
    {

        DiLui();
    }
     if(bt=='S')
    {
       ResetDongCo();
    }
  }

void TranhVatCan(){ 
    khoangCach=0;
    DoKhoangCach();
    if(khoangCach > gioiHan||khoangCach == 0) 
    {
      DiThang();    
    }
    else
    {
      resetdongco();
      QuaycbSangTrai();
      khoangCachTrai= khoangCach;
      QuaycbSangPhai();
      khoangCachPhai = khoangCach;
      if(khoangCachPhai < 10 && khoangCachTrai < 10){
        DiLui();
        }
      else
      {
        if(KhoangCachPhai > KhoangCachTrai) 
          {
            DiSangPhai();
            delay(1500);
          }
        if(KhoangCachPhai < KhoangCachTrai) 
          {
            DiSangTrai();
            delay(1500);
          }
      }
    }
    Serial.println(khoangCach);
}
void BlueTooh(){
  bt = Serial.read();
  Serial.println(bt);
  Check(bt);
  DoKhoangCach();
  if(khoangcach < 10)
  {
  DiLui();
  delay(200);
  ResetDongCo();
  }
  bt  =' ';
}


