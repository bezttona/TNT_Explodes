#define L1 A0
#define L2 A1
#define R1 A2
#define R2 A3

int a[3]={0,0,0};

//Cam bien 1 (dang truoc)
const int trig1 = 11;
const int echo1 = 12;

//Cam bien 2 (ben trai)
const int trig2 = 8;
const int echo2 = 9;

//Cam bien 3 (ben phai)
const int trig3 = 6;
const int echo3 = 7;

void setup() {
  Serial.begin(9600);
  //Dang truoc
  pinMode(trig1,OUTPUT);
  pinMode(echo1,INPUT);
  //Ben phai
  pinMode(trig2,OUTPUT);
  pinMode(echo2,INPUT);
  //Ben trai
  pinMode(trig3,OUTPUT);
  pinMode(echo3,INPUT);
  //Banh trai
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  //Banh phai
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
}

//Cach phia truoc
int ahead() {
  unsigned long duration; 
  int distance;           
    
  digitalWrite(trig1,0);  
  delayMicroseconds(2);
  digitalWrite(trig1,1);   
  delayMicroseconds(5);  
  digitalWrite(trig1,0);   
    
  duration = pulseIn(echo1,HIGH);  
  distance = int((duration/2) * 0.034);

  return distance;
}

//Cach ben phai
int right() {
  unsigned long duration; 
  int distance;           
    
  digitalWrite(trig2,0);  
  delayMicroseconds(2);
  digitalWrite(trig2,1);   
  delayMicroseconds(5);  
  digitalWrite(trig2,0);   
    
  duration = pulseIn(echo2,HIGH);  
  distance = int((duration/2) * 0.034);
  
  return distance;
}

//Cach ben trai
int left() {
  unsigned long duration; 
  int distance;           
    
  digitalWrite(trig3,0);  
  delayMicroseconds(2);
  digitalWrite(trig3,1);   
  delayMicroseconds(5);  
  digitalWrite(trig3,0);   
    
  duration = pulseIn(echo3,HIGH);  
  distance = int((duration/2) * 0.034);
  
  return distance;
}

//Dung dong co
void stop() {
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
}

//Di thang
void goAhead() {
  digitalWrite(L1, HIGH);   
  digitalWrite(L2, LOW);

  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);

  delay(70);
  stop();
  delay(500);
}

//Di thang vao nga re
void go() {
  digitalWrite(L1, HIGH);   
  digitalWrite(L2, LOW);

  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);

  delay(250);
  stop();
  delay(500);
}

//Re trai
void turnLeft() {
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);

  digitalWrite(L1, LOW);   
  digitalWrite(L2, LOW);

  delay(1000);
  stop();
  delay(500);

  go();
}

//Re phai
void turnRight() {
  digitalWrite(L1, HIGH);   
  digitalWrite(L2, LOW);

  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);

  delay(1000);
  stop();
  delay(500);

  go();
}

//Quay dau
void turnAround() {
  digitalWrite(L1, LOW);   
  digitalWrite(L2, HIGH);

  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);

  delay(1000);
  stop();
  delay(500);
}

void update_st(){
  int a0=left();
  int a1=ahead();
  int a2=right();

  Serial.print("Phia truoc cach: ");
  Serial.print(a1);
  Serial.print(" cm\t\t\t"); 

  Serial.print("Phia ben trai cach: ");
  Serial.print(a0);
  Serial.println(" cm\t\t\t");

  if(a0<23) a[0]=0;
  else a[0]=1;
  if(a1<10) a[1]=0;
  else a[1]=1;
  if(a2<23) a[2]=0;
  else a[2]=1;
}

void solve_labyrinth() {
  update_st();
  if (a[0] == 1) {
    turnLeft();
  }
  else {
    if (a[1] == 1) {
      goAhead();
    }
    else {
      if (a[2] == 1) {
        turnRight();
      }
      else {
        turnAround();
      }
    }
  }
}

void loop() {
  solve_labyrinth();
}