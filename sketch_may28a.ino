#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define VRX 34
#define VRY 35
#define SW 32

Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire);

#define MAX_SNAKE_LENGTH 100
#define SIZE 4
#define MIN_FOOD_DIST 20

int snakeX[MAX_SNAKE_LENGTH];
int snakeY[MAX_SNAKE_LENGTH];
int snakeLength = 3;

int foodX = -99;
int foodY = -99;
int score = 0;
int dirX = SIZE;
int dirY = 0;
bool gameOver = false;

void spawnFood() {
  int newFX, newFY;
  bool tooClose;
  int attempts = 0;

  do {
    newFX = random(5, 120);
    newFY = random(12, 58);
    tooClose = false;

    for (int i = 0; i < snakeLength; i++) {
      if (abs(newFX - snakeX[i]) < MIN_FOOD_DIST &&
          abs(newFY - snakeY[i]) < MIN_FOOD_DIST) {
        tooClose = true;
        break;
      }
    }

    if (newFX == foodX && newFY == foodY) tooClose = true;

    attempts++;
    if (attempts > 200) break;

  } while (tooClose);

  foodX = newFX;
  foodY = newFY;
}

void restartGame() {
  snakeLength = 3;
  score = 0;
  gameOver = false;
  snakeX[0] = 64; snakeY[0] = 32;
  snakeX[1] = 60; snakeY[1] = 32;
  snakeX[2] = 56; snakeY[2] = 32;
  dirX = SIZE;
  dirY = 0;
  foodX = -99;
  foodY = -99;
  spawnFood();
}

void setup() {
  pinMode(SW, INPUT_PULLUP);
  display.begin(0x3C, true);
  display.clearDisplay();
  randomSeed(esp_random());
  restartGame();
}

void loop() {
  if (gameOver) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(10, 15);
    display.println("GAME");
    display.setCursor(10, 35);
    display.println("OVER");
    display.setTextSize(1);
    display.setCursor(0, 55);
    display.print("Score:");
    display.print(score);
    display.display();
    if (digitalRead(SW) == LOW) {
      delay(300);
      restartGame();
    }
    return;
  }

  int x = analogRead(VRX);
  int y = analogRead(VRY);

  if      (y > 3000 && dirX == 0) { dirX = -SIZE; dirY = 0; }
  else if (y < 1000 && dirX == 0) { dirX =  SIZE; dirY = 0; }
  else if (x < 1000 && dirY == 0) { dirX = 0; dirY = -SIZE; }
  else if (x > 3000 && dirY == 0) { dirX = 0; dirY =  SIZE; }

  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  snakeX[0] += dirX;
  snakeY[0] += dirY;

  if (snakeX[0] < 0 || snakeX[0] > 127 ||
      snakeY[0] < 8  || snakeY[0] > 63) {
    gameOver = true;
    return;
  }

  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gameOver = true;
      return;
    }
  }

  // Check eat but don't spawn yet
  bool eaten = false;
  int headCX = snakeX[0] + SIZE / 2;
  int headCY = snakeY[0] + SIZE / 2;
  if (abs(headCX - foodX) < SIZE && abs(headCY - foodY) < SIZE) {
    if (snakeLength < MAX_SNAKE_LENGTH) snakeLength++;
    score++;
    eaten = true;
  }

  // Draw everything
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Score:");
  display.print(score);
  display.fillCircle(foodX, foodY, 2, SH110X_WHITE);
  for (int i = 0; i < snakeLength; i++) {
    display.fillRect(snakeX[i], snakeY[i], SIZE, SIZE, SH110X_WHITE);
  }
  display.display();

  // Spawn new food AFTER drawing so two apples never appear in same frame
  if (eaten) spawnFood();

  delay(120);
}