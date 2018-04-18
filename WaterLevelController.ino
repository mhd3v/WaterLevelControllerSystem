
int UpperMotorPin = 10;
int LowerMotorPin = 9;

int LowerTankLowPin;
int LowerTankHighPin;

int UpperTankLowPin;
int UpperTankHighPin;

void setup() {
  pinMode(UpperMotorPin, OUTPUT);
  pinMode(LowerMotorPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {

    LowerTankLowPin = analogRead(A0);
    LowerTankHighPin = analogRead(A1);
    
    UpperTankLowPin = analogRead(A4);
    UpperTankHighPin = analogRead(A5);


    if(LowerTankLowPin == 0) //lower tank water level low
        TurnOnLowerMotor();

    else{ //lower tank water level not low
      if(UpperTankLowPin == 0)
        TurnOnUpperMotor();
    }

  delay(100);        // delay in between reads for stability
    
}
  
void TurnOnLowerMotor(){

    Serial.println("Turning on lower motor");
  
    LowerTankHighPin = analogRead(A1);
  
    UpperTankLowPin = analogRead(A3);
  
    analogWrite(UpperMotorPin, LOW); //turn off upper motor
  
    analogWrite(LowerMotorPin, 100); //turn on lower motor
  
    while(LowerTankHighPin < 100){ //keep lower motor on till lower tank is full
       
      LowerTankHighPin = analogRead(A1); //update
      LowerTankLowPin = analogRead(A0); //update

      Serial.print("LowerTank High Pin: ");
      Serial.println(LowerTankHighPin);
      Serial.println("");
      Serial.print("LowerTank Lower Pin: ");
      Serial.println(LowerTankLowPin);
      Serial.println("===");
      
      delay(500);
    }
  
    analogWrite(LowerMotorPin, LOW); //turn off lower motor
  
    if(UpperTankLowPin < 100){ //upper tank water level low
         
          TurnOnUpperMotor();
    }

}


void TurnOnUpperMotor(){
    
    Serial.println("Turning on upper motor");
    
    LowerTankLowPin = analogRead(A0);
    
    UpperTankLowPin = analogRead(A4);
    UpperTankHighPin = analogRead(A5);

    analogWrite(UpperMotorPin, 100); //turn on upper motor
    
    while(UpperTankHighPin < 100){ //keep lower motor on till lower tank is full

        LowerTankLowPin = analogRead(A0); //update
        
        UpperTankLowPin = analogRead(A4); //update
        UpperTankHighPin = analogRead(A5); //update 
        
        Serial.print("UpperTank High Pin: ");
        Serial.println(UpperTankHighPin);
        Serial.println("");
        Serial.print("UpperTank Low Pin: ");
        Serial.println(UpperTankLowPin);
        Serial.println("===");

        if(LowerTankLowPin == 0){
          Serial.println("Turning on upper motor");
          //if low tank is empty while upper motor running
          TurnOnLowerMotor();
          break;
        }

        delay(500);
    }

    analogWrite(UpperMotorPin, LOW); //turn off upper motor

}

