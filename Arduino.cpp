void setup() 
{

  Serial.begin(9600); //initialize serial communication at a 9600 baud rate

}

void loop() {

Serial.write(66);

  delay(1000)
  
  if (Serial.available() > 0) 
  {
  

     Serial.print(" - I received: ");

    Serial.print(Serial.read());

Serial.println(" cm");

}

}
