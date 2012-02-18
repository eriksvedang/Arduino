int in;

void setup()
{
  Serial.begin(9600);
}

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
    break;
  }
}

const int toneFrequency = 25000;
int unitLength = 150;

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
    else playLong();
    
    ++signal;
  }
  
  delay(unitLength * 3);
}

void loop()
{
  while((in = Serial.read()) == -1) {}
  char c = (char)in;
  playMorseLetter(getMorseSignal(c));
}
