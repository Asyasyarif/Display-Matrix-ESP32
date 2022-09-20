#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <Adafruit_GFX.h>

#define PANEL_RES_X 64      // Number of pixels wide of each INDIVIDUAL panel module.
#define PANEL_RES_Y 32     // Number of pixels tall of each INDIVIDUAL panel module.
#define PANEL_CHAIN 1      // Total number of panels chained one to another

#define R1_PIN 19
#define G1_PIN 13
#define B1_PIN 18
#define R2_PIN 5
#define G2_PIN 12
#define B2_PIN 17
#define A_PIN 16
#define B_PIN 14
#define C_PIN 4
#define D_PIN 27
#define E_PIN -1 // required for 1/32 scan panels, like 64x64. Any available pin would do, i.e. IO32
#define LAT_PIN 26
#define OE_PIN 15
#define CLK_PIN 2

//MatrixPanel_I2S_DMA dma_display;
MatrixPanel_I2S_DMA *matrix = nullptr;
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
// From: https://gist.github.com/davidegironi/3144efdc6d67e5df55438cc3cba613c8

uint16_t myBLACK = matrix->color565(0, 0, 0);
uint16_t myWHITE = matrix->color565(255, 255, 255);
uint16_t myRED = matrix->color565(255, 0, 0);
uint16_t myGREEN = matrix->color565(0, 255, 0);
uint16_t myBLUE = matrix->color565(0, 0, 255);

void setup() {
  Serial.begin(115220);
  Serial.println("ada");


  HUB75_I2S_CFG::i2s_pins _pins={R1_PIN, G1_PIN, B1_PIN, R2_PIN, G2_PIN, B2_PIN, A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, LAT_PIN, OE_PIN, CLK_PIN};
  HUB75_I2S_CFG mxconfig(
    PANEL_RES_X,   // module width
    PANEL_RES_Y,   // module height
    PANEL_CHAIN,    // Chain length
    _pins
  );

  //mxconfig.gpio.e = 18;
  mxconfig.clkphase = false;
  //mxconfig.driver = HUB75_I2S_CFG::FM6126A;

  // Display Setup
  matrix = new MatrixPanel_I2S_DMA(mxconfig);
  matrix->begin();
  matrix->setBrightness8(90); //0-255
  matrix->clearScreen();

  matrix->fillScreen(myRED);

  delay(1500);
  matrix->fillScreen(myBLUE);

  delay(1500);
  matrix->fillScreen(myGREEN);

  delay(1500);
  //drawText(0);

  matrix->clearScreen();
  matrix->fillScreen(myBLACK);
  matrix->setCursor(0,0);
  matrix->print("IMSAK");
}

void loop() {
}