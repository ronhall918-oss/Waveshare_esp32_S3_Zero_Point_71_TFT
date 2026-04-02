#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft); // Create the virtual screen

void setup() {
    Serial.begin(115200);
    
    // Backlight ON
    pinMode(3, OUTPUT);
    digitalWrite(3, HIGH); 

    tft.init();
    tft.setRotation(0); 
    
    // 1. Allocate ESP32 RAM for a 160x160 virtual screen
    // (This uses about 51KB of RAM, the C3 has plenty!)
    spr.createSprite(160, 160);
    
    // ----------------------------------------------------
    // ALL DRAWING NOW HAPPENS IN THE ESP32's PERFECT RAM
    // ----------------------------------------------------
    
    // Clear virtual screen
    spr.fillSprite(TFT_BLACK);
    
    // Draw the circles virtually
    spr.drawCircle(80, 80, 30, TFT_RED);
    spr.drawCircle(80, 80, 29, TFT_RED); 
    
    // Draw the crosshairs virtually
    spr.drawLine(80, 0, 80, 160, TFT_GREEN); 
    spr.drawLine(0, 80, 160, 80, TFT_GREEN); 
    
    // Print the text virtually
    spr.setTextColor(TFT_WHITE, TFT_BLACK);
    spr.drawCentreString("VIRTUAL RAM", 80, 70, 2);
    
    // ----------------------------------------------------
    // PUSH THE FINISHED MASTERPIECE TO THE SCREEN IN ONE SHOT
    // ----------------------------------------------------
    spr.pushSprite(0, 0);
}

void loop() {
    delay(1000);
}