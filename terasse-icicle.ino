#define lampSwitchTimeout 4 //seconds
#define icicleSwitchTimeout 600 //seconds
#define autoSwitchoffTimer 10 //minutes
#define lightThresholdLamp 160 //lower is lighter, higher is darker
#define lightThresholdIcicle 195

#define iciclePin 12
#define lampPin 13
#define pirPin 2
#define lightSensorPin A4
#define ledPin 13

boolean lampState = false;
boolean iceState = false;
unsigned long lastMovement_millis = 10000000;
unsigned long lastIcicleSwitch_millis = 10000000;

unsigned long lastLightCheck_millis = 10000000;
long darknesscounter = 0;
long lightnesscounter = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(iciclePin, OUTPUT);
  digitalWrite(iciclePin, HIGH);
  pinMode(lampPin, OUTPUT);
  digitalWrite(lampPin, HIGH);  
  pinMode(pirPin, INPUT);
  pinMode(lightSensorPin, INPUT_PULLUP);
}

void loop() {
  //pir sensor terasse lamp switch on/off 
  if (lampState == false && digitalRead(pirPin) == HIGH && analogRead(lightSensorPin) > lightThresholdLamp && (millis() - lastMovement_millis) > ((unsigned long)lampSwitchTimeout * 1000)) {
    digitalWrite(lampPin, LOW); //turn ON terasse lamp
    lastMovement_millis = millis();
    lampState = true;
  }
  if ( lampState == true && digitalRead(pirPin) == HIGH && (millis() - lastMovement_millis) > ((unsigned long)lampSwitchTimeout * 1000) ) {
    digitalWrite(lampPin, HIGH); //turn OFF terasse lamp
    lastMovement_millis = millis();
    lampState = false;
  }
  if ( lampState == true && (millis() - lastMovement_millis) > ((unsigned long)autoSwitchoffTimer * 60 * 1000) ) { //lamp autoswitchoff
    digitalWrite(lampPin, HIGH); //turn OFF terasse lamp
    lampState = false;
  }





  if ( (millis() - lastLightCheck_millis) > 100 ) {
      lastLightCheck_millis = millis();
      if (analogRead(lightSensorPin) > lightThresholdIcicle) {//darkness
        darknesscounter = darknesscounter > 65500 ? 65500 : darknesscounter + 1 ;
      }
      else {//ligthness
        lightnesscounter = lightnesscounter > 65500 ? 65500 : lightnesscounter + 1 ;
      }
    }    
    
  if ( iceState == false ) {    
    if (darknesscounter > 30) {//turn ON icicle
      lightnesscounter = 0;
      darknesscounter = 0;
      digitalWrite(iciclePin, LOW);
      iceState = true;
    }
  }
  else {    
    if (darknesscounter > 10) {//prolonging the icicle with 5 minutes
      lightnesscounter = lightnesscounter <= 3000 ? 0 : lightnesscounter - 3000 ;
      darknesscounter = 0;
    }    
    
    if (lightnesscounter > 6000) {//turn OFF icicle // 6000 means 10 minutes
      lightnesscounter = 0;
      darknesscounter = -600; //1 minute extra switch delay
      digitalWrite(iciclePin, HIGH);
      iceState = false;
    }
  } 
  
  
} //end of main LOOP
