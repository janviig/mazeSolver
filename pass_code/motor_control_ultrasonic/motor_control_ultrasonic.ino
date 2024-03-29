
// defines pins numbers
const int echoPinLeft = 5;
const int trigPinLeft = 6;

const int echoPinFront = 11;
const int trigPinFront = 12;

const int echoPinRight = 2;
const int trigPinRight = 4;

// defines variables
long duration;
int distance;

int motorright = 9;                                                              
int motorrightdir  = 7;
int motorleft = 10;
int motorleftdir  = 8;

//For serial receive.
const byte numChars = 11;
char receivedChars[numChars]; // an array to store the received data
String received; //The data as a string
boolean newData = false;

void setup() {
  pinMode(motorright, OUTPUT);                                                      
  pinMode(motorleft, OUTPUT);     
  pinMode(motorrightdir, OUTPUT);  
  pinMode(motorleftdir, OUTPUT);  

  pinMode(trigPinLeft, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinLeft, INPUT); // Sets the echoPin as an Input
  pinMode(trigPinFront, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinFront, INPUT); // Sets the echoPin as an Input
  pinMode(trigPinRight, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinRight, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); //normal printing
}

void loop() 
{
  int left = ultrasonic(echoPinLeft,trigPinLeft);
  int front = ultrasonic(echoPinFront,trigPinFront);
  int right = ultrasonic(echoPinRight,trigPinRight);
  String message = "";
  message = message + "[" + left + "cm," + front + "cm," + right + "cm]\n";
  Serial.print(message);
  delay(100); //wait for 1/10th of a second.
  
  recvWithEndMarker();
  processCommand();              
}

int ultrasonic(int echoPin, int trigPin) {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
return distance;
}

void processCommand() {
 if (newData == true)
 {
  String instruction = received.substring(0,5);
  String data = received.substring(6,10);
  if(instruction == "MOVEF") forward(data.toInt());
  if(instruction == "MOVEB") backward(data.toInt());
  if(instruction == "TURNL") left(data.toInt());
  if(instruction == "TURNR") right(data.toInt());
  if(instruction == "CONTF") cont_fwd(data.toInt());
  if(instruction == "CONTB") cont_bwd(data.toInt());
  if(instruction == "SLOWF") slow(data.toInt());
  if(instruction == "STOPR") stop();
  newData = false;
 }
}

void recvWithEndMarker() 
{
 static byte ndx = 0;
 char endMarker = '\n';
 char rc;
 
 while (Serial.available() > 0 && newData == false) 
 {
  rc = Serial.read();

  if (rc != endMarker) 
  {
    receivedChars[ndx] = rc;
    ndx++;
    if (ndx >= numChars) 
    {
      ndx = numChars - 1;
    }
 }
 else 
  {
  receivedChars[ndx] = '\0'; // terminate the string
  received = String(receivedChars);
  ndx = 0;
  newData = true;
  }
 }
}

//direction is controlled by the digital pin 7 and 8.
// HIGH is backward, LOW is forward
// Pins 9 and 10 control speed.
// Length of time controls the distance

void forward(int time)
{
digitalWrite(motorrightdir, LOW);
analogWrite(motorright,180); 
digitalWrite(motorleftdir, LOW);
analogWrite(motorleft, 180); 
delay(time);
stop();
}

void backward(int time)
{
digitalWrite(motorrightdir, HIGH);
analogWrite(motorright,180); 
digitalWrite(motorleftdir, HIGH);
analogWrite(motorleft, 180);
delay(time);
stop();
}

void left(int time)
{
//analogWrite(motorleft,0); 
digitalWrite(motorrightdir, LOW);
analogWrite(motorright, 180); 
digitalWrite(motorrightdir, HIGH);
analogWrite(motorright, 180); 
delay(time);
stop();
}

void right(int time)
{
//analogWrite(motorright,0); 
digitalWrite(motorleftdir, LOW);
analogWrite(motorleft, 180); 
digitalWrite(motorleftdir, HIGH);
analogWrite(motorleft, 180); 
delay(time);
stop();
}

void uturn(int varspeed)
{
  digitalWrite(motorleftdir, HIGH);
  analogWrite(motorleft, varspeed);
  digitalWrite(motorrightdir, LOW);
  analogWrite(motorright, varspeed);
  delay(time);
  stop();
}

void cont_fwd(int varspeed)
{
digitalWrite(motorrightdir, LOW);
analogWrite(motorright,varspeed); 
digitalWrite(motorleftdir, LOW);
analogWrite(motorleft, varspeed); 
delay(time);
stop();
}

void cont_bwd(int varspeed)
{
digitalWrite(motorrightdir, HIGH);
analogWrite(motorright,varspeed); 
digitalWrite(motorleftdir, HIGH);
analogWrite(motorleft, varspeed); 
delay(time);
stop();
}

void slow(int time)
{
digitalWrite(motorrightdir, LOW);
analogWrite(motorright,50); 
digitalWrite(motorleftdir, LOW);
analogWrite(motorleft, 50); 
delay(time);
stop();
}

void stop()
{
analogWrite(motorright, 0); 
analogWrite(motorleft, 0);   
}
