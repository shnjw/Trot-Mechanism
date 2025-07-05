#include <SoftwareSerial.h>    // 블루투스 시리얼 통신 라이브러리 추가
#include <Servo.h>             // 서보모터 제어 라이브러리 추가

Servo myservo;                 // (사용되지 않음) 기본 서보 객체 생성
SoftwareSerial BTSerial(2, 3); // 소프트웨어 시리얼: 블루투스 (Tx = 2, Rx = 3)
Servo servomotor1;  // 서보모터1 객체 (기본 움직임 제어 - 방향)
Servo servomotor2;  // 서보모터2 객체 (기본 움직임 제어 - 방향)
Servo servomotor3;  // 서보모터3 객체 (집게 제어)
Servo servomotor4;  // 서보모터4 객체 (상하 이동 제어)

int currentAngle = 170;

void setup() {
  BTSerial.begin(9600);      // 블루투스 통신 시작
  Serial.begin(9600);        // PC와 시리얼 통신 시작

  servomotor1.attach(9);     // 서보모터1을 9번 핀에 연결
  servomotor2.attach(8);     // 서보모터2를 8번 핀에 연결
  servomotor3.attach(4);     // 서보모터3을 4번 핀에 연결
  servomotor4.attach(5);     // 서보모터4를 5번 핀에 연결

  // 초기 위치 설정
  servomotor1.write(88);     
  servomotor2.write(88);
}
void loop() {
  if (BTSerial.available()) {      // 블루투스에서 데이터가 들어왔는지 확인
    char bt = BTSerial.read();     // 한 문자 읽기
    Serial.println(bt);            // 입력된 문자 PC로 출력

    if (bt == '1') {               // '1' 입력 시: 앞쪽으로 이동 (전진)
      servomotor1.write(115);      // 모터1 오른쪽 회전
      servomotor2.write(110);      // 모터2 오른쪽 회전
    } 
    else if (bt == '2') {          // '2' 입력 시: 뒤로 이동 (후진)
      servomotor1.write(20);       
      servomotor2.write(20);
    } 
    else if (bt == '4') {          // '4' 입력 시: 좌회전
      servomotor1.write(10);
      servomotor2.write(110);
    } 
    else if (bt == '3') {          // '3' 입력 시: 우회전
      servomotor1.write(110);
      servomotor2.write(10);
    } 
    else if (bt == '5') {          // '5' 입력 시: 집게 닫기
      servomotor3.write(0);
    } 
    else if (bt == '6') {          // '6' 입력 시: 집게 열기
      servomotor3.write(60);
    } 
    else if (bt == '7') {          // '7' 입력 시: 팔 올리기
      currentAngle = 170;
      servomotor4.write(170);
    } 
    else if (bt == '8') {          // '8' 입력 시: 팔 내리기
     if (currentAngle > 0) {
        currentAngle -= 10;
        servomotor4.write(currentAngle);
      }
    } 
    else if (bt == '0') {          // '0' 입력 시: 중립 위치로
      servomotor1.write(90);
      servomotor2.write(90);
    }
  }
  delay(100);  // 다음 명령을 받기 전 잠깐 대기
}
