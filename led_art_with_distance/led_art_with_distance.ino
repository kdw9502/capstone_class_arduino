#define red_pin 33
#define yellow_pin 23
#define blue_pin 19

#define echo 17
#define trig 16



void setup() {
  pinMode(yellow_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  pinMode(red_pin, OUTPUT);

  // additional gnd
  pinMode(25, OUTPUT);
  digitalWrite(25, 0);
  
  pinMode(5, OUTPUT);
  digitalWrite(5, 0);

  //
  pinMode(trig, OUTPUT);    // 트리거 핀 출력으로 선언
  pinMode(echo, INPUT);     // 에코 핀 입력으로 선언
  
  Serial.begin(115200);
}
int i = 30;
void loop() {
  Serial.print("i : ");
  Serial.println(i);


  float distance_in_mm = get_distance();
  
  float _delay = 2 * distance_in_mm;

  if (_delay < 50)
    _delay = 50;
  if (_delay > 1000)
    _delay = 1000;
  Serial.print("delay : ");
  Serial.println(_delay);
  
  if (i% 5 == 0)  
    digitalWrite(red_pin, 1);
  if (i% 3 == 0)
    digitalWrite(yellow_pin, 1);
  if (i% 2 == 0)
    digitalWrite(blue_pin, 1);
  delay(_delay);
  
  digitalWrite(red_pin, 0);
  digitalWrite(yellow_pin, 0);
  digitalWrite(blue_pin, 0);
  delay(_delay);


  
  i--;
  if (i==0)
  {
    i = 30;
  }
}

float get_distance()
{
    long duration, distance;    // 거리 측정을 위한 변수 선언
  // 트리거 핀으로 10us 동안 펄스 출력
  digitalWrite(trig, LOW);        // Trig 핀 Low
  delayMicroseconds(2);            // 2us 딜레이
  digitalWrite(trig, HIGH);    // Trig 핀 High
  delayMicroseconds(10);            // 10us 딜레이
  digitalWrite(trig, LOW);        // Trig 핀 Low
   /*
       에코핀에서 받은 펄스 값을 pulseIn함수를 호출하여
       펄스가 입력될 때까지의 시간을 us단위로 duration에 저장
       pulseln() 함수는 핀에서 펄스(HIGH or LOW)를 읽어서 마이크로초 단위로 반환
  */
  duration = pulseIn(echo, HIGH); 
  /*
       음파의 속도는 초당 340m, 왕복하였으니 나누기 2를하면 170m이고,
       mm단위로 바꾸면 170,000mm.
       duration에 저장된 값은 us단위이므로 1,000,000으로 나누어 주고,
       정리해서 distance에 저장
  */
  distance = duration * 170 / 1000;
  return distance;
}
