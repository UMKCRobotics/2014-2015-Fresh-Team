const int A=2;
const int B=3;
const int C=4;
const int D=5;
 
void setup() 
{
  pinMode(A0, INPUT);
  pinMode(A, OUTPUT); //LSB
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT); //MSB
 
}
int count = 0; //the variable used to show the number
 
void loop() 
{
  if (digitalRead(A0) == LOW) // From here the line sensors will give me a value for the Analog read
    {
    count++; 
    if (count == 10) //we want to count from 0 to 9!
      count = 0;
    to_BCD(); //convert to binary
    }
    
  if (count == 10)
    count = 0;
   
}
 
void to_BCD()
{
    if (count == 0) //write 0000
    {
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
    }
     
    if (count == 1) //write 0001
    {
       digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
    }
     
    if (count == 2) //write 0010 (this value will change to reflect the square the robot is in 
    {
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
    }
     
    if (count == 3) //write 0011
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
    }
     
    if (count == 4) //write 0100
    {
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
    }
     
    if (count == 5) //write 0101
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
    }
     
    if (count == 6) //write 0110
    {
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
    }
     
    if (count == 7) //write 0111
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
    }
     
    if (count == 8) //write 1000
    {
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
    }
     
    if (count == 9) //write 1001
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
    } 
}
