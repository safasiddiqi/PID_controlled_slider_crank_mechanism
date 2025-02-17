#include <PID_v1.h>
#include <Servo.h>

const int trig_pin=3;
const int echo_pin=5;
const int servoPin = 9;
long distance,duration;
Servo servo;


double Setpoint, Output, Input;
double Kp = 2.5, Ki = 0, Kd = 0.4;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
int angle = 90;

void setup()
{
  Serial.begin(9600);
  servo.attach(servoPin);
  servo.write(angle);
  pinMode(trig_pin,OUTPUT);
  pinMode(echo_pin,INPUT);
  Setpoint = 5;
  myPID.SetMode(AUTOMATIC); 
  myPID.SetTunings(Kp,Ki,Kd);
  myPID.SetOutputLimits(-45,45);
}
void loop()
{
  digitalWrite(3,HIGH);
  delayMicroseconds(200);
  digitalWrite(3,LOW);
  delayMicroseconds(200);
  duration = pulseIn(echo_pin, HIGH); 
  distance= duration*0.034/2;
  Input = distance;
  angle = angle + round(30.0*Output/45.0);
  servo.write(angle);
  myPID.Compute();
  Serial.print("Input=");
  Serial.print(Input);
  Serial.print(" ");
  Serial.print("Setpoint=");
  Serial.print(Setpoint);
  Serial.print(" ");
  Serial.print("Output=");
  Serial.print(Output);
  Serial.println(",");
  
  delay(100);
}
