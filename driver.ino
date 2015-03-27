void setup() {
  Serial.begin(9600);
}

void loop() {

  int currentMode = modeSelect();
  boolean readyToGo = false;
  delay(1000);
  do {
    delay(20);
    // Set status light blue for ready to go
    updateStatusLight(0, 0, 255);
    Serial.println("waiting for ready to go");
    if (digitalRead(3) == HIGH)readyToGo = true;
  } while (!readyToGo);

  //StartTrials
  boolean buttonHit = false;
  if (currentMode) {
    for (int i = 0; i < 40; i++) {
      delay(500);
      updateStatusLight(0, 255, 0);
      delay(250);
      updateStatusLight(0, 0, 0);
      //Get whether or not user hit signal button
      buttonHit = listenForButtonHit();
      executeMode1(buttonHit);
    }
  } else {
    for (int i = 0; i < 40; i++) {
      delay(500);
      updateStatusLight(0, 255, 0);
      delay(250);
      updateStatusLight(0, 0, 0);

      buttonHit = listenForButtonHit(); //Still listen just for delay
      executeMode2();
    }
  }

}

int modeSelect() {

  int currentMode = 1;
  //Set status light to orange
  updateStatusLight(255, 132, 0);
  do {
    if (digitalRead(13) == HIGH) {
      currentMode ^= 1; //Toggle current mode
      if (currentMode) {
        // Set status light to purple
        updateStatusLight(140, 46, 255);
      } else {
        //Set mode light to orange
        updateStatusLight(255, 132, 0);
      }
    }
    if (digitalRead(3) == HIGH) return currentMode;
    delay(150);
  } while (true);
}

boolean listenForButtonHit() {
  boolean hit = false;
  int time = 0;
  do {
    if (digitalRead(3) == HIGH) {
      hit = true;
    }
    delay(10);
    time += 10;
    if (time == 2000) {
      return hit;
    }
  } while (true);
}

void executeMode1(boolean hit) {
  long randPercentage = random(100);
  if ((hit && randPercentage > 25) || (!hit && randPercentage > 75 )) {
    //Light up light
    //Light up light
    updateSignalLight(0, 155, 15);
  }
  delay(1000);
  updateSignalLight(0, 0, 0);
}

void executeMode2() {
  long randPercentage = random(100);
  if (randPercentage > 25) {
    //Light up light
    updateSignalLight(0, 155, 15);
  }
  delay(1000);
  updateSignalLight(0, 0, 0);
}

void updateStatusLight(int red, int green, int blue) {
  analogWrite(12, red);
  analogWrite(9, green);
  analogWrite(10, blue);
}

void updateSignalLight(int red, int green, int blue) {
  analogWrite(7, red);
  analogWrite(4, green);
  analogWrite(5, blue);
}

