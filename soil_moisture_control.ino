#define SENSOR A0
#define RELAY_PIN 8
#define RED 7
#define GREEN 4

int moisture = 0;
int dryThreshold = 700;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    String input=Serial.readStringUntil('\n');
    input.trim();
    int newThreshold = input.toInt();
    if(newThreshold>0&&newThreshold<=1023){
      dryThreshold=newThreshold;
      Serial.println(newThreshold);
    }
  }
  moisture = analogRead(SENSOR);
  Serial.println(moisture);

  if (moisture > dryThreshold) {
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
    Serial.println("Pump on");
    delay(100);
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    Serial.println("Pump off");
  }
  delay(500);

}
