#include <Servo.h>

const int servoPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int numServos = 8;
Servo servos[numServos];

unsigned long lastBatonTime = 0;
unsigned long batonInterval[4] = {5000, 3000 ,2000 , 1000}; // 5 seconds
const unsigned long mrDelay = 10000; //initial delay
bool allBatonThrown = false;
bool batonsThrown[numServos] = {false}; // Array to track which batons have been thrown
unsigned long intervalIndex = random(4);
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  randomSeed(analogRead(A0));
  // Initialize servos
  for (int i = 0; i < numServos; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(0); // Set initial position
  }

  Serial.println("The game will start in 10 Seconds");
  delay(mrDelay); //10 Seconds delay before starting the game
  lastBatonTime = millis();
}

void loop() {
  unsigned long currentTime = millis();

  // Check if it's time to throw a baton
  if (!allBatonThrown && currentTime - lastBatonTime >= batonInterval[intervalIndex]) {
    throwBaton();
    lastBatonTime = currentTime;
  }
  // Check if it's time to start the next round
  if (allBatonThrown) {
    startNextRound();
  }
}

void throwBaton() {
  // Find a baton that has not been thrown yet
  int batonIndex = -1;
  do {
    batonIndex = random(numServos);
  } while (batonsThrown[batonIndex]);

  // Rotate the selected servo to drop the baton
  servos[batonIndex].write(90);
  Serial.print("Baton ");
  Serial.print(batonIndex + 1);
  Serial.println(" thrown!");

  // Mark the baton as thrown
  batonsThrown[batonIndex] = true;
  intervalIndex = random(4);


  // Check if all batons have been thrown
  allBatonThrown = true;
  for (int i = 0; i < numServos; i++) {
    if (!batonsThrown[i]) {
      allBatonThrown = false;
      break;
    }
  }

}

void resetBatons() {
  // Rotate all servos to their initial positions
  for (int i = 0; i < numServos; i++) {
    servos[i].write(0);
    delay(500);
    batonsThrown[i] = false; // Reset baton state
  }

  // Reset all batons thrown flag
  allBatonThrown = false;
}

void startNextRound() {
  Serial.println("The servos will reset in 5 seconds");
  delay(5000);
  // Reset batons for the next round
  resetBatons();
  Serial.println("The Next game will start after pressing RESET");
  while(1){
    continue;
  }
}
