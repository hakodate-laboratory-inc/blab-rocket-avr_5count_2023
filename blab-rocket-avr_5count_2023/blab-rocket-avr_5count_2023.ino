#define BTN 7
#define SER 15
#define SOU 16

int k=1;

void SOUND(){
  int j=0;  
  for(j=0;j<250;j++)
  {
    digitalWrite(SOU,HIGH);
    delayMicroseconds(1000);
    digitalWrite(SOU,LOW);
    delayMicroseconds(1000);
  }
  delay(500);
}

void setup() {
  pinMode(BTN,INPUT);
  pinMode(SOU,OUTPUT);
  pinMode(SER,OUTPUT);
  PORTB=0b11111111;
}

void loop() {
 
 char i=5;
 char nom[6]={0b00111111,0b00000110,0b10011011,0b10001111,0b10100110,0b10101101};
 int j;

 for(j=0;j<50;j++)
 {
   digitalWrite(SER,HIGH);
   delayMicroseconds(2400);
   digitalWrite(SER,LOW);
   delay(2);
 } 
 
 while(digitalRead(BTN)==0);

 for(i=5;i>0;i--)
 {
  DDRB=nom[i];
  SOUND();
 }
 DDRB=nom[i];

 for(j=0;j<800;j++)
 {
   digitalWrite(SOU,HIGH);
   delayMicroseconds(500);
   digitalWrite(SOU,LOW);
   delayMicroseconds(500);
 }
 
 for(j=0;j<50;j++)
 {
   digitalWrite(SER,HIGH);
   delayMicroseconds(500);
   digitalWrite(SER,LOW);
   delay(2);
 } 
 delay(1000);
}
