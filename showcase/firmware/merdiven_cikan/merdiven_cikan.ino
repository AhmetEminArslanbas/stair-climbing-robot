#include <NewPing.h>
#include <Servo.h>
#include "AX12A.h"
#include "Adafruit_TCS34725.h" //RENK ENSÖRÜ İÇİN KÜTÜPHANE
#include <SoftwareSerial.h>

SoftwareSerial hc06 =  SoftwareSerial(6, 7);

#define DirectionPin   (2u)
#define BaudRate      (1000000ul)
NewPing on_sensor(11, 10, 200);
NewPing alt_sensor(8, 9, 200);
Servo myservo;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_1X);
float re,ge,be;
uint16_t r, g, b, c, colorTemp, lux;//RENK SENSÖRÜ İÇİN GEREKLİ OLAN DEĞİŞKENLER
double zaman=0;

#define led_r 13
#define led_g 12
#define led_b 11

float ileri_speed = 7;//4
float donus_speed = 3; //max veriği değer 500

byte araci_veri[16] = {0, 0, 100, 100, 0, 100, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0};

byte throttle = 100;
byte rol = 100;

byte throttle_2 = 100;

byte rt = 100;
byte lt = 100;

byte btn_rb = 1;
byte btn_lb = 1;

byte btn_y = 1;
byte btn_x = 1;
byte btn_b = 1;
byte btn_a = 1;

byte btn_right = 1;

double kol_zaman = 0;
double yukseklik_zaman = 0;
float el_1_derece = 512;
float el_2_derece = 512;
float el_speed = 1;
float kol_derece = 512;
float kol_speed = 5; // bunu arttırınca motorun dönüş hızını da arttır

bool manuel_durum = true;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
void setup() {
  //Serial.begin(9600);
  hc06.begin(9600);
  pinMode(6, INPUT);
  pinMode(7, OUTPUT);
  pinMode(led_r, OUTPUT);
  pinMode(led_g, OUTPUT);
  pinMode(led_b, OUTPUT);
  ax12a.begin(BaudRate, DirectionPin, &Serial);
  ax12a.moveSpeed(5, 512,1000);
  ax12a.moveSpeed(6, 512,1000);
  ax12a.moveSpeed(7, 512,1000);
  ax12a.moveSpeed(8, 512,1000);
  ax12a.moveSpeed(9, 512,1000);
  delay(2000);
  zaman=millis();
  manuel_durum = true;
}

int alt_mesafe=0;
int on_mesafe=0;
void loop() 
{
  while(manuel_durum) //pc nin bağlanmasını bekle
  {
    manuel();
    
  }
  digitalWrite(led_r, LOW);
  digitalWrite(led_g, LOW);
  digitalWrite(led_b, HIGH);

  el_1_derece = 512;
  el_2_derece = 512;
  kol_derece = 512;

  ax12a.moveSpeed(9, kol_derece, 1000);

  ax12a.moveSpeed(5, el_2_derece, 300);
  ax12a.moveSpeed(6, el_1_derece, 300);

  ax12a.moveSpeed(7, el_1_derece, 300);
  ax12a.moveSpeed(8, el_2_derece, 300);

  cikis();
  ileri_git(300, 300);
  delay(1500);
  manuel_durum = true;

  /*while(manuel_durum) //pc nin bağlanmasını bekle
  {
    manuel();
    
  }
  digitalWrite(led_r, LOW);
  digitalWrite(led_g, LOW);
  digitalWrite(led_b, HIGH);

  el_1_derece = 512;
  el_2_derece = 512;
  kol_derece = 512;

  ax12a.moveSpeed(9, kol_derece, 1000);

  ax12a.moveSpeed(5, el_2_derece, 300);
  ax12a.moveSpeed(6, el_1_derece, 300);

  ax12a.moveSpeed(7, el_1_derece, 300);
  ax12a.moveSpeed(8, el_2_derece, 300);

  cikis();
  cikis();
  cikis();
  cikis();
  //görüntü işledikten sonra
  el_1_derece = 512;
  el_2_derece = 512;
  kol_derece = 512;

  ax12a.moveSpeed(9, kol_derece, 1000);
  
  ax12a.moveSpeed(5, el_2_derece, 300);
  ax12a.moveSpeed(6, el_1_derece, 300);

  ax12a.moveSpeed(7, el_1_derece, 300);
  ax12a.moveSpeed(8, el_2_derece, 300);

  dur();
  while(!manuel_durum)
  {
    veri_oku();
    if(btn_a == 2)
    {
      while(btn_y == 1)
      {
        manuel_durum = true;
        manuel();
      }
      break;
    }
  }

  digitalWrite(led_r, LOW);
  digitalWrite(led_g, LOW);
  digitalWrite(led_b, HIGH);

  el_1_derece = 512;
  el_2_derece = 512;
  kol_derece = 512;

  ax12a.moveSpeed(9, kol_derece, 1000);
  
  ax12a.moveSpeed(5, el_2_derece, 300);
  ax12a.moveSpeed(6, el_1_derece, 300);

  ax12a.moveSpeed(7, el_1_derece, 300);
  ax12a.moveSpeed(8, el_2_derece, 300);


  //inis_2();

  inis();
  inis();
  inis();
  inis();

//  alt_mesafe=alt_sensor.ping_cm();
//  delay(10);
//  on_mesafe=on_sensor.ping_cm();
//  delay(10);
//  Serial.print(alt_mesafe);
//  Serial.print(" ");
//   Serial.println(on_mesafe);
//bir();  9 bos 8 + - 10 + 11 */
}




