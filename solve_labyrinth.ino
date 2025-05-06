#define R1 A0
#define R2 A1
#define L1 A2
#define L2 A3

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
  //Ben trai
  pinMode(trig2,OUTPUT);
  pinMode(echo2,INPUT);
  //Ben phai
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

//Cach ben trai
int left() {
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

//Dung dong co
void stop() {
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
}

//Cach ben phai
int right() {
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

//Re trai
void turnLeft() {
  digitalWrite(L1, LOW);   
  digitalWrite(L2, HIGH);

  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
}

//Re phai
void turnRight() {
  digitalWrite(L1, HIGH);   
  digitalWrite(L2, LOW);

  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
}

//Di thang
void goAhead() {
  digitalWrite(L1, HIGH);   
  digitalWrite(L2, LOW);

  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
}

//Quay dau
void turnAround() {
  digitalWrite(L1, LOW);   
  digitalWrite(L2, HIGH);

  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);

  delay(1000);
  stop();
}

void loop() {
  int truoc = ahead();
  int trai = left();
  int phai = right();

  //In khoang cach de kiem tra
  Serial.print("Phia truoc cach: ");
  Serial.print(truoc);
  Serial.print(" cm\t\t\t"); 

  Serial.print("Phia ben trai cach: ");
  Serial.print(trai);
  Serial.print(" cm\t\t\t");

  Serial.print("Phia ben phai cach: ");
  Serial.print(phai);
  Serial.println(" cm");

  if (trai > 5) {
    turnLeft();
  }
  else if (truoc > 5) {
    goAhead();
  }
  else if (phai > 5) {
    turnRight();
  }
  else {
    turnAround();
  }
  //Chu y nay, ma chac anh Viet cung co noi thoi, sau moi lan re se co delay de cho dung quay bao nhieu do a, nen nho test roi chon delay cho phu hop
  //Con vi sao lai khong phai cu di thang, gap ngo cut moi re
  //Tai vi lam the se xay ra truong hop xe co the di toi di lui mot duong thang neu khong luu lai duong minh da di
  //Vi the cu uu tien re trai neu ben trai dang trong truoc (theo Left Hand-rule)
  //Nho bay lai t cai code sau khi chinh nghe =)))))
}