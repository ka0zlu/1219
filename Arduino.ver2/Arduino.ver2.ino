//네오픽셀
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN 7
#define NUMPIXELS 7
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//워터펌프
int AA = 10;
int AB = 6;

void setup() {
  // put your setup code here, to run once:
  //시리얼통신 시작
  Serial.begin(9600);

  //네오픽셀
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  pixels.begin();
  pixels.show();

  //핀모드
  pinMode(A1, INPUT);
  pinMode(AA, OUTPUT);
  pinMode(AB, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  //네오픽셀 off
  pixels.clear();

  //토양 수분 센서 값 읽기
  int Soil = analogRead(A0);

  if(0<= Soil && Soil <300){
    Serial.print("dry soil: ");
    Serial.println(Soil);
    delay(1000);
  }
  else if(300<Soil && Soil<700){
    Serial.print("humid soil: ");
    Serial.println(Soil);
    delay(1000);
  }
  else{
    Serial.print("in water or error: ");
    Serial.println(Soil);
    delay(1000);
  }

  //워터펌프 작동
  if(Soil<300){
    digitalWrite(AA, HIGH);
    digitalWrite(AB, LOW);
    delay(1000);
  }
  else{
    digitalWrite(AA, LOW);
    digitalWrite(AB, LOW);
    delay(1000);
  }

  //조도센서
  int Light = analogRead(A1);
  Serial.print("빛: ");
  Serial.println(Light);
  delay(1000);

  //네오픽셀
  if(Light<100){
    for(int i = 0; i<NUMPIXELS; i++){
      pixels.setPixelColor(i, pixels.Color(125,0,255));
      pixels.show();
    }}
  else{
    for(int i = 0; i<NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    pixels.show();
    }
  }
}
