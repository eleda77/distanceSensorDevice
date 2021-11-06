//code for device that senses distance from user's face
//device should be attached to phone case

//declare initial variables
int output = 10;
int input = 9;
int buzz = 8;
int led = 5;
int voice = 11;
long duration, cm, inches;

void setup() {
  // setup code
  Serial.begin(9600);
  pinMode(output, OUTPUT);
  pinMode(input, INPUT);
  pinMode(buzz, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(voice, OUTPUT);
  digitalWrite(voice, LOW);
}

void loop() {
  // Sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse
  digitalWrite(voice, LOW);
  digitalWrite(output, LOW);
  delayMicroseconds(5);
  digitalWrite(output, HIGH);
  delayMicroseconds(10);
  digitalWrite(output, LOW);

  // Read signal from sensor: a HIGH pulse whose duration is the time
  // (in microseconds) from the sending of the ping to the reception of its
  // echo off of an object
  duration = pulseIn(input, HIGH);
  // Convert time into distance
  cm = (duration / 2) / 29.1;
  inches = (duration / 2) / 74;
  int alertLength = cm * 8;
  Serial.print(inches); //testing to see if distance is correct
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  Serial.println(duration);

  delay(250);
  if(cm < 10) { //if less than 10, triger voice recording
    digitalWrite(voice, HIGH);
    delay(200);
    digitalWrite(voice, LOW);
    delay(5000);
  } else if (cm < 30) {      //if less than 30, trigger beeps with
    digitalWrite(led, HIGH); // distance between depending on distance
    Serial.println("less than 30");
    noTone(buzz);
    tone(buzz, 698);
    delay(100);
    noTone(buzz);
    alertLength = cm * 8;
    delay(alertLength);
  } else { //if too far, do notb alert user
    noTone(buzz);
    Serial.println("very far");
    digitalWrite(led, LOW);
  }
}
