#include <Servo.h>

const int servoPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int numServos = 8;
Servo servos[numServos];

unsigned long lastBatonTime = 0;
unsigned long batonInterval = 5000; // 5 seconds
const unsigned long timeBetweenRounds = 30000; // 30 seconds time interval between rounds
const unsigned long mrDelay = 90000; // The delay to load batons and bring the next player
bool allBatonThrown = false;
bool batonsThrown[numServos] = {false}; // Array to track which batons have been thrown

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  randomSeed(analogRead(A0));

  // Initialize servos
  for (int i = 0; i < numServos; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(0); // Set initial position
  }

  delay(mrDelay); //3 minute delay before starting the 1st round
  // Start the first round
  lastBatonTime = millis();
}

void loop() {
  unsigned long currentTime = millis();

  // Check if it's time to throw a baton
  if (!allBatonThrown && currentTime - lastBatonTime >= batonInterval) {
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
    batonsThrown[i] = false; // Reset baton state
  }

  // Reset all batons thrown flag
  allBatonThrown = false;
}

void startNextRound() {
  delay(2000);
  // Reset batons for the next round
  resetBatons();
  programLevels();
  delay(timeBetweenRounds);
  delay(batonInterval);
}

void programLevels() {

  if (batonInterval > 2000) batonInterval -= 1500;
  else if (batonInterval == 2000) batonInterval -= 1000;
  else if (batonInterval == 1000) batonInterval -= 500;
  else {
    batonInterval = 5000;
    delay(mrDelay-timeBetweenRounds);
  }
}
