#define lampSwitchTimeout 4 //seconds
#define icicleSwitchTimeout 60 //seconds
#define autoSwitchoffTimer 10 //minutes
#define lightThreshold 150 //lower is lighter, higher is darker

#define iciclePin 12
#define lampPin 13
#define pirPin 2
#define lightSensorPin A4
#define ledPin 13

boolean lampState = false;
unsigned long lastMovement_millis = 10000000;
unsigned long lastIcicleSwitch_millis = 10000000;

void setup()
{
  Serial.begin(9600);
  pinMode(iciclePin, OUTPUT);
  digitalWrite(iciclePin, HIGH);
  pinMode(lampPin, OUTPUT);
  digitalWrite(lampPin, HIGH);  
  pinMode(pirPin, INPUT);
  pinMode(lightSensorPin, INPUT_PULLUP);
  //pinMode(ledPin, OUTPUT);
  //digitalWrite(ledPin, LOW);  
}

void loop() {
  //pir sensor terasse lamp switch on/off 
  if (lampState == false && digitalRead(pirPin) == HIGH && analogRead(lightSensorPin) > lightThreshold && (millis() - lastMovement_millis) > ((unsigned long)lampSwitchTimeout * 1000)) {
    digitalWrite(lampPin, LOW); //turn ON terasse lamp
    lastMovement_millis = millis();
    lampState = true;
  }
  if (lampState == true && digitalRead(pirPin) == HIGH && (millis() - lastMovement_millis) > ((unsigned long)lampSwitchTimeout * 1000)) {
    digitalWrite(lampPin, HIGH); //turn OFF terasse lamp
    lastMovement_millis = millis();
    lampState = false;
  }
  if (lampState == true && (millis() - lastMovement_millis) > ((unsigned long)autoSwitchoffTimer * 60 * 1000)) {
    digitalWrite(lampPin, HIGH); //turn OFF terasse lamp
    lampState = false;
  }
  
  if (analogRead(lightSensorPin) > lightThreshold && (millis() - lastIcicleSwitch_millis) > ((unsigned long)icicleSwitchTimeout * 1000)) {
    digitalWrite(iciclePin, LOW); //turn ON icicle
    lastIcicleSwitch_millis = millis();
  }
  if (lampState == false && analogRead(lightSensorPin) <= lightThreshold && (millis() - lastIcicleSwitch_millis) > ((unsigned long)icicleSwitchTimeout * 1000)) {
    digitalWrite(iciclePin, HIGH); //turn OFF icicle
    lastIcicleSwitch_millis = millis();
  }
  //digitalWrite(ledPin, digitalRead(pirPin));
  //Serial.println(analogRead(lightSensorPin));  
  //delay(50);
  
  
} //end of main LOOP
