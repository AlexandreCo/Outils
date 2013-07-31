int oLed = 13;
int iExt0 = 2;
int iExt1 = 3;
int inButton=7;
int i;
volatile int state = LOW;
typedef struct{
  unsigned long Us;
  unsigned long Min;
  unsigned long Max;
}t_mes;

typedef struct{
  t_mes tH2L;
  t_mes tL2H;
  unsigned long ulHigh;
  unsigned long ulLow;
}t_interrupt;

t_interrupt tInt[2];

unsigned long ulUs;

void vRaz()
{
  for(i=0;i<2;i++){
    tInt[i].tH2L.Min=(unsigned long)-1;
    tInt[i].tH2L.Max=0;
    
    tInt[i].tL2H.Min=(unsigned long)-1;
    tInt[i].tL2H.Max=0;
  }
}
void setup()
{
  pinMode(oLed, OUTPUT);
  pinMode(inButton, INPUT);
  attachInterrupt(0, vMesure0, CHANGE);
  attachInterrupt(1, vMesure1, CHANGE);
  Serial.begin(9600);
  vRaz();
}


void loop()
{
  //digitalWrite(oLed, state);
  for(i=0;i<2;i++){
    Serial.print(" pin ");
    Serial.print(i+2);
    Serial.print(" Low->High: ");
    Serial.print(tInt[i].tL2H.Min);
    Serial.print(",");
    Serial.print(tInt[i].tL2H.Max);
    Serial.print(",");
    Serial.print(tInt[i].tL2H.Us);
    Serial.print(" High->Low: ");
    Serial.print(tInt[i].tH2L.Min);
    Serial.print(",");
    Serial.print(tInt[i].tH2L.Max);
    Serial.print(",");
    Serial.print(tInt[i].tH2L.Us);
  }
  Serial.println();
  
  if(digitalRead(inButton)){
     Serial.println("Raz");
    vRaz();
  }
  delay(1000);
}

void vMesure0()
{
  char chInState;
  ulUs=micros();
  
  chInState = digitalRead(iExt0);
  if(chInState==HIGH){
    tInt[0].ulHigh=ulUs;
    tInt[0].tL2H.Us=tInt[0].ulHigh-tInt[0].ulLow;
    if(tInt[0].tL2H.Min>tInt[0].tL2H.Us){
      tInt[0].tL2H.Min=tInt[0].tL2H.Us;
    }
    
    if(tInt[0].tL2H.Max<tInt[0].tL2H.Us){
      tInt[0].tL2H.Max=tInt[0].tL2H.Us;
    }
  }
  else{
    tInt[0].ulLow=ulUs;
    tInt[0].tH2L.Us=tInt[0].ulLow-tInt[0].ulHigh; 
    if(tInt[0].tH2L.Min>tInt[0].tH2L.Us){
      tInt[0].tH2L.Min=tInt[0].tH2L.Us;
    }
    
    if(tInt[0].tH2L.Max<tInt[0].tH2L.Us){
      tInt[0].tH2L.Max=tInt[0].tH2L.Us;
    }
  }
}


void vMesure1()
{
  char chInState;
  ulUs=micros();
  
  chInState = digitalRead(iExt1);
  if(chInState==HIGH){
    tInt[1].ulHigh=ulUs;
    tInt[1].tL2H.Us=tInt[1].ulHigh-tInt[1].ulLow;
    if(tInt[1].tL2H.Min>tInt[1].tL2H.Us){
      tInt[1].tL2H.Min=tInt[1].tL2H.Us;
    }
    
    if(tInt[1].tL2H.Max<tInt[1].tL2H.Us){
      tInt[1].tL2H.Max=tInt[1].tL2H.Us;
    }
  }
  else{
    tInt[1].ulLow=ulUs;
    tInt[1].tH2L.Us=tInt[1].ulLow-tInt[1].ulHigh; 
    if(tInt[1].tH2L.Min>tInt[1].tH2L.Us){
      tInt[1].tH2L.Min=tInt[1].tH2L.Us;
    }
    
    if(tInt[1].tH2L.Max<tInt[1].tH2L.Us){
      tInt[1].tH2L.Max=tInt[1].tH2L.Us;
    }
  }
}

