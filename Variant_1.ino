#include <Servo.h>

const int numServos = 8;
const int servoPins[numServos] = {2, 3, 4, 5, 6, 7, 8, 9};

Servo servos[numServos];

unsigned long lastBatonTime = 0;
const unsigned long batonInterval = 5000; // 5 seconds
const unsigned long mrDelay = 9000; // The delay to load batons and bring next player

bool allBatonsThrown = false;
bool batonsThrown[numServos]; // Array to track which batons have been thrown

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  randomSeed(analogRead(A0));

  // Initialize servos
  for (int i = 0; i < numServos; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(0); // Set initial position
  }

  Serial.println("The game will start after 90 seconds");
  delay(mrDelay); // Delay before starting the 1st round
  lastBatonTime = millis();
}

void loop() {
  unsigned long currentTime = millis();

  // Check if it's time to throw a baton
  if (!allBatonsThrown && currentTime - lastBatonTime >= batonInterval) {
    throwBaton();
    lastBatonTime = currentTime;
  }

  // Check if it's time to start the next round
  if (allBatonsThrown) {
    startNextRound();
  }
}

void throwBaton() {
  int randomIndex = getRandomAvailableBaton();

  // Rotate the selected servo to drop the baton
  servos[randomIndex].write(90);
  Serial.print("Baton ");
  Serial.print(randomIndex + 1);
  Serial.println(" thrown!");

  // Mark the baton as thrown
  batonsThrown[randomIndex] = true;

  // Check if all batons have been thrown
  allBatonsThrown = true;
  for (int i = 0; i < numServos; i++) {
    if (!batonsThrown[i]) {
      allBatonsThrown = false;
      break;
    }
  }
}

int getRandomAvailableBaton() {
  int randomIndex;
  do {
    randomIndex = random(numServos);
  } while (batonsThrown[randomIndex]);
  return randomIndex;
}

void resetBatons() {
  // Rotate all servos to their initial positions
  for (int i = 0; i < numServos; i++) {
    servos[i].write(0);
    delay(500);
    batonsThrown[i] = false; // Reset baton state
  }
  allBatonsThrown = false;
}

void startNextRound() {
  Serial.println("The servos will reset in 10 seconds");
  delay(10000);
  resetBatons();
  Serial.println("The Next game will start after 90 seconds");
  delay(mrDelay);
  delay(batonInterval);
}
