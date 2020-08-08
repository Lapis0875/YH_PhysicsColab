#define TRIG 7
#define ECHO 9

// 4 ~6 : A~C, 10~13 : D~G
int SegmentPins[] = {4,5,6,10,11,12,13};
bool SegementNumbers[10][7] = {
  {true, true, true, true, true, true, false},
  {false, true, true, false, false, false, false},
  {true, true, false, true, true, false, true},
  {true, true, true, true, false, false, true},
  {false, true, true, false, false, true, true},
  {true, false, true, true, false, true, true},
  {true, true, true, true, true, false, true},
  {true, true, true, false, false, true, false},
  {true, true, true, true, true, true, true},
  {true, true, true, false, false, true, true}
};

void setup() {
  // Initial setup code.
  Serial.begin(9600); // Set serial port speed to 9600.
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  for(int i; i< 7; i++){
    pinMode(SegmentPins[i], OUTPUT);  
  }
}

void loop() {
  // Infinite loop.
  int cm = UltrasonicWave();
  delay(500);
  UW_Detect(cm);
}

int UltrasonicWave(){
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long input = pulseIn(ECHO, HIGH);
  Serial.println((String) "In : " + input);
  int cm = input / 58.0;
  Serial.println((String) cm + "cm");
  return cm;
}

void UW_Detect(int cm){
  if (cm < 10){
    SegmentModify(1);
  } else if (cm < 20) {
    SegmentModify(2);
  } else if (cm < 30){
    SegmentModify(3);
  } else if (cm < 40){
    SegmentModify(4);
  } else if (cm < 50){
    SegmentModify(5);
  } else {
    SegmentModify(0);
  }
}

void SegmentModify(int number){
  if (number < 0 || number > 9){
    return;
  }
  for(int i; i < 7; i++){
    digitalWrite(SegmentPins[i], SegementNumbers[number][i] ? HIGH : LOW);
  }
}
