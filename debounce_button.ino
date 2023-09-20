/* Tested on Arduino Nano Familty boards */

#include <Arduino_LSM6DS3.h>

const int RED = A0;
const int GREEN = A2;
const int BLUE = A1;
const int LED = 9;
const int BUTTON = 3;
boolean lastButton = LOW;
boolean currentButton = LOW;
boolean ledOn = false;
float x, y, z;
int ix,iy,iz;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  // Turn OFF RGB Led
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);

  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }
  
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in g's");
  Serial.println("X\tY\tZ");

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
  if (Serial.available() > 0)
  {
    int val1 = Serial.parseInt();
    int val2 = Serial.parseInt();
    int val3 = Serial.parseInt();

    // Discard all other Serial garbage from buffer
    while(Serial.available())
    {      
      Serial.read();
    }

    int val1c = constrain(val1, 0, 100);
    int val2c = constrain(val2, 0, 100);
    int val3c = constrain(val3, 0, 100);

    int rval = map(val1c, 0, 100, 0, 255);
    int gval = map(val2c, 0, 100, 0, 255);
    int bval = map(val3c, 0, 100, 0, 255);

    // set led brightness
    analogWrite(RED, rval);
    analogWrite(GREEN, gval);
    analogWrite(BLUE, bval);

    Serial.println("Red:  " + String(val1c) + "%");
    Serial.println("Green " + String(val2c) + "%");
    Serial.println("Blue: " + String(val3c) + "%");

  }

  if (IMU.accelerationAvailable())
  {
    IMU.readAcceleration(x, y, z);
    ix = x * 100;
    iy = y * 100;
    iz = z * 100;

    int xval = map(ix, 0, 100, 0, 255);
    int yval = map(iy, 0, 100, 0, 255);
    int zval = map(iz, 0, 100, 0, 255);

    // set led brightness
    analogWrite(RED, xval);
    analogWrite(GREEN, yval);
    analogWrite(BLUE, zval);

  }

  currentButton = debounce(lastButton);

  if(lastButton == LOW && currentButton == HIGH)
    ledOn = !ledOn;

  lastButton = currentButton;

  digitalWrite(LED, ledOn);
}
