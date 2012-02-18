#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xa2, 0xda, 0x0c, 0x00, 0xaf };
int toneFrequency = 20000;
int unitLength = 150;

EthernetServer server(23);

void setup()
{
  Serial.begin(9600);
  
  Ethernet.begin(mac);
  
  Serial.print("Ethernet set up with IP ");
  Serial.println(Ethernet.localIP());
  
  server.begin();
}

int in;

char *getMorseSignal(char c)
{
  switch(c) {
    case 'a':
      return "._";
    break;
    case 'b':
      return "_...";
    break;
    case 'c':
      return "_._.";
    case 'd':
      return "_..";
    case 'e':
      return ".";
    case 'f':
      return ".._.";
    case 'g':
      return "__.";
    case 'h':
      return "....";
    case 'i':
      return "..";
    case 'j':
      return ".___";
    case 'k':
      return "_._";
    case 'l':
      return "._..";
    case 'm':
      return "__";
    case 'n':
      return "_.";
    case 'o':
      return "___";
    case 'p':
      return ".__.";
    case 'q':
      return "__._";
    case 'r':
      return "._.";
    case 's':
      return "...";
    case 't':
      return "_";
    case 'u':
      return ".._";
    case 'v':
      return "..._";
    case 'w':
      return ".__";
    case 'x':
      return "_.._";
    case 'y':
      return "_.__";
    case 'z':
      return "__..";
    case ' ':
      return " ";
    case '+':
      toneFrequency *= 2;
      break;
    case '-':
      toneFrequency /= 2;
      break;  
  }
  return "";
}

void playLong()
{
  tone(8, toneFrequency);
  delay(unitLength * 3);
  noTone(8);
  delay(unitLength);
}

void playShort()
{
  tone(8, toneFrequency);
  delay(unitLength);
  noTone(8);
  delay(unitLength);
}

void playSpace()
{
  noTone(8);
  delay(unitLength * 7);
}

void playMorseLetter(char *signal)
{ 
  while (*signal)
  {
    if(*signal == '.') playShort();
    else if (*signal == ' ') playSpace();
    else if (*signal == '_') playLong();    
    ++signal;
  }
  
  delay(unitLength * 3);
}

void loop()
{
  EthernetClient client = server.available();
  if (client)
  {
    in = client.read();
    char c = (char)in;
    Serial.println(c);
    playMorseLetter(getMorseSignal(c));
  }
}
