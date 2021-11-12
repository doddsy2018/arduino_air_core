int sinPin1 =  10;    // sinPin1 connected to digital pin 13
int sinPin2=  11;    // sinPin2 connected to digital pin 13
int cosPin1 =  12;    // cosPin1 connected to digital pin 13
int cosPin2 =  13;    // cosPin2 connected to digital pin 13


int position=0;
int direction=1;
float pi=3.14159;
int scale=255;

int sin1Value=0;
int sin2Value=0;
int cos1Value=0;
int cos2Value=255;

void setPosition(int smoothness=5); //Declare default function value

void setup()
{
  pinMode(sinPin1, OUTPUT);    
  pinMode(sinPin2, OUTPUT);    
  pinMode(cosPin1, OUTPUT);    
  pinMode(cosPin2, OUTPUT);  

  // Cycle Gauge
  for (int i=0; i<=230;i++){
    calcValues(i);
    setPosition();   
  }
  delay(1000);
  for (int i=229; i>=0;i--){
    calcValues(i);
    setPosition(); 
  }
  delay(1000);
  
}


void loop(){
  if (position>=230){
    position=230;
    direction=-1;
  }
  if (position<=0){
    position=0;
    direction=1;
  }
  
  calcValues(position);
  setPosition(3);

  position=position+direction;

}



void setPosition(int smoothness){
  // Move air core gauge
  analogWrite(sinPin1, sin1Value);
  analogWrite(sinPin2, sin2Value);
  analogWrite(cosPin1, cos1Value);
  analogWrite(cosPin2, cos2Value);
  
  delay(smoothness);
}

int calcValues(int angle){
  // Compute pin values based on position
  float positionRad=angle*pi/180;
  float sinCalc=scale*sin(positionRad);
  float cosCalc=scale*cos(positionRad-pi); // handle 180 phase shift
  if (sinCalc>0){
    sin1Value=abs(sinCalc);
  }
  else{
    sin1Value=0;
  }
  if (sinCalc<0){
    sin2Value=abs(sinCalc);
  }
  else{
    sin2Value=0;
  }
  
  if (cosCalc>0){
    cos1Value=abs(cosCalc);
  }
  else{
    cos1Value=0;
  }
  if (cosCalc<0){
    cos2Value=abs(cosCalc);
  }
  else{
    cos2Value=0;
  }
}
