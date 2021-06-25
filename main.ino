

int trigPinL = 11;
int echoPinL = 12;
int trigPinR = 3;
int echoPinR = 2;

int piezo = 4;

int rossoL = 10;
int gialloL = 9;
int verdeL = 8;

int rossoR = 5;
int gialloR = 6;
int verdeR = 7;

long durationL, cmL, durationR, cmR;

void setup()
{
  Serial.begin(9600);

  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
  for (int i = 5; i < 11; i++)
    pinMode(i, OUTPUT);
}

void loop()
{

  //LEFT SENSOR
  digitalWrite(rossoL, LOW);
  digitalWrite(gialloL, LOW);
  digitalWrite(verdeL, LOW);

  digitalWrite(trigPinL, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  durationL = pulseIn(echoPinL, HIGH);

  //RIGHT SENSOR
  digitalWrite(rossoR, LOW);
  digitalWrite(gialloR, LOW);
  digitalWrite(verdeR, LOW);

  digitalWrite(trigPinR, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);
  durationR = pulseIn(echoPinR, HIGH);

  //cm = time/2 * speed of sound
  cmL = (durationL / 2) * 0.0343;
  cmR = (durationR / 2) * 0.0343;

  if (cmL < 334)
  {
    Serial.print(cmL);
    Serial.println();

    //ho rilevato qualcosa, ho un oggetto nel range
    if (cmL > 200)
    {
      digitalWrite(verdeL, HIGH);
    }
    else if (cmL < 200 && cmL > 50)
    {
      digitalWrite(gialloL, HIGH);
    }
    else if (cmL < 50)
    {
      digitalWrite(rossoL, HIGH);
    }
  }
  if (cmR < 334)
  {
    Serial.print(cmR);
    Serial.println();

    //ho rilevato qualcosa, ho un oggetto nel range
    if (cmR > 200)
    {
      digitalWrite(verdeR, HIGH);
    }
    else if (cmR < 200 && cmR > 50)
    {
      digitalWrite(gialloR, HIGH);
    }
    else if (cmR < 50)
    {
      digitalWrite(rossoR, HIGH);
    }
  }
  if (cmR < cmL)
    tone(piezo, 900, cmR);
  else
    tone(piezo, 900, cmL);
  delay(500);
}
