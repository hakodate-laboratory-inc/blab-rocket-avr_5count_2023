/* #概要
 *  このコードは、Arduino UNO を経由して、ATmega8 にプログラムを書き込む際に使ったものです。
 *  使うツール(ボードマネージャー)は、MiniCore です。詳しい使い方は、GitHubの該当適宜検索してみてください。
 *  作ったものとしては、ゴム鉄砲の要領で飛んでいく、ロケットの発射台の装置(ボタン、サーボモーター、ブザー)で、
 *  こちらの制御を行うプログラムとなっております。
 * 
 * #ブートローダーの設定
 * * ボード:        "ATmega8"
 * * Clock:        "Internal 8 MHz"
 * * BOD:          "BOD disabled"
 * * EEPROM:       "EEPROM retained"
 * * Compiler LTO: "LTO disabled"
 * * Bootloader:   "No bootloader"
 * 
 * #Arduino のその他の設定
 * * 書込装置:      "Arduino as ISP"
 * 
 * 上記の設定をした上で、
 * ポート番号を接続している Arduino UNO 等のポートに設定して、
 * 「ブートローダを書き込む」を押してください。
 */

#define BTN 7  //Arduinoピン7 、ポートピンPD7、物理ピン番号13。ボタン用
#define SRV 15 //Arduinoピン15、ポートピンPC1、物理ピン番号24。サーボモーター用
#define BZZ 16 //Arduinoピン16、ポートピンPC2、物理ピン番号25。ブザー用

void buzzer_count1(){
  unsigned char j; //0～255
  for(j=0;j<250;j++)
  {
    digitalWrite(BZZ,HIGH);
    delayMicroseconds(1000);
    digitalWrite(BZZ,LOW);
    delayMicroseconds(1000);
  }
  delay(500);
}

void setup(){
  pinMode(BTN,INPUT);
  pinMode(BZZ,OUTPUT);
  pinMode(SRV,OUTPUT);
  DDRB = 0b11111111;   //Bポートの入出力設定(方向レジスタ)
}

void loop(){

  unsigned char i; //カウントダウンの秒数。num[]の順番の指定に使う
  unsigned char num[6] = {0b00111111,0b00000110,0b10011011,0b10001111,0b10100110,0b10101101}; //0～5の7セグ点灯パターン
  unsigned int j;


  for(j=0;j<50;j++) //サーボモータを初期位置に
  {
    digitalWrite(SRV,HIGH);
    delayMicroseconds(2400);
    digitalWrite(SRV,LOW);
    delay(2);
  } 
 
  while(digitalRead(BTN)==0); //ボタンを押すまで待つ  

  for(i=5;i>0;i--) //カウントダウン(5～0へ)
  {
    PORTB=num[i];   //7セグLEDでカウントダウン
    buzzer_count1(); //音を鳴らして約1秒待つ
  }
  PORTB=num[i];     //カウント0表示

  for(j=0;j<800;j++) //ブザーを長めに鳴らす
  {
    digitalWrite(BZZ,HIGH);
    delayMicroseconds(500);
    digitalWrite(BZZ,LOW);
    delayMicroseconds(500);
  }
 
  for(j=0;j<50;j++) //サーボモーターの角を発射角度へ
  {
    digitalWrite(SRV,HIGH);
    delayMicroseconds(500);
    digitalWrite(SRV,LOW);
    delay(2);
  } 
  delay(1000); //安全のため、念のため待ちます
}
