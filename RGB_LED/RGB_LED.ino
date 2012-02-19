
const int rPin = 9;
const int gPin = 10;
const int bPin = 11;


void setup()
{
  
}

void loop()
{
   float t = millis() / 1000.0f;

  analogWrite(rPin, 128 + sin(t * 0.5f) * 128);
  analogWrite(gPin, 128 + cos(t) * 128);
  analogWrite(bPin, 128 + sin(t * 4) * 128);
  
  delay(10);
}
