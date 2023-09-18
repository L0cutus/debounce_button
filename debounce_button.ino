/* Tested on Arduino Nano Familty boards */

const int LED=9;
const int BUTTON=3;
boolean lastButton = LOW;
boolean currentButton = LOW;
boolean ledOn = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);

}

boolean debounce(boolean last)
{
  boolean current = digitalRead(BUTTON);
  if(last != current)
  {
    delay(5);
    current = digitalRead(BUTTON);
  }
  return current;
}

void loop() {
  currentButton = debounce(lastButton);

  if(lastButton == LOW && currentButton == HIGH)
    ledOn = !ledOn;

  lastButton = currentButton;

  digitalWrite(LED, ledOn);
}
