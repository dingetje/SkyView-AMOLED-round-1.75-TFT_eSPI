#include "SkyView.h"
#include "TFTHelper.h"
#include "NMEAHelper.h"
#include "TrafficHelper.h"
#include "Compas466x466.h"
#include "SatDish.h"
#include "Speed.h"
#include "altitude2.h"

extern xSemaphoreHandle spiMutex;
extern TFT_eSPI tft;
extern TFT_eSprite sprite;
extern TFT_eSprite compasSprite;
extern TFT_eSprite compas2Sprite;
    

void TFT_compass_loop() {
    if (isTimeToDisplay() && show_compass) {
        compasSprite.fillSprite(TFT_BLACK);
        sprite.fillSprite(TFT_BLACK);
        compasSprite.pushImage(0, 0, 466, 466, Compas466x466);
        compasSprite.setPivot(233, 233);
        sprite.setPivot(233, 233);
        compas2Sprite.fillSprite(TFT_BLACK);
        
        compas2Sprite.fillTriangle(215, 125, 235, 90, 255, 125, TFT_WHITE);
        compas2Sprite.setCursor(220, 230, 4);
        compas2Sprite.printf("%d kmh", (int)((ThisAircraft.GroundSpeed) * 1.85));
        compas2Sprite.setSwapBytes(true);
        compas2Sprite.pushImage(180, 230, 32, 24, Speed);
        compas2Sprite.pushImage(135, 280, 32, 32, SatDishpng);
        compas2Sprite.setCursor(180, 290, 4);
        if (nmea.satellites.isValid()) {
            int satelliteCount = nmea.satellites.value();
            compas2Sprite.printf("%d", satelliteCount);
        }
        else {
            compas2Sprite.setTextColor(TFT_RED, TFT_BLACK);
            compas2Sprite.printf("NO FIX");
            compas2Sprite.setTextColor(TFT_WHITE, TFT_BLACK);
        }

        compas2Sprite.pushImage(265, 280, 32, 32, altitude2);
        compas2Sprite.setCursor(310, 290, 4);
        compas2Sprite.printf("%d ft", (int)(ThisAircraft.altitude * 3.28084));
        compasSprite.pushRotated(&sprite, 360 - ThisAircraft.Track, TFT_BLACK);
        compas2Sprite.setCursor(190, 160, 7);
        compas2Sprite.printf("%d", ThisAircraft.Track, TFT_BLACK);
        compas2Sprite.pushToSprite(&sprite, 0, 0, TFT_BLACK);
        if (xSemaphoreTake(spiMutex, portMAX_DELAY)) {
            // lcd_set_colour_enhance();
            lcd_PushColors(6, 0, 466, 466, (uint16_t*)sprite.getPointer());
            lcd_brightness(255);
            xSemaphoreGive(spiMutex);
          } else {
            Serial.println("Failed to acquire SPI semaphore!");
          }
}

}