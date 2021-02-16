/* 
 *  3D2-Project1 - Light & Motion
 *  Modified by Yushi Li - Feb 2021
 *  
 *  Neopixel randomized colours for 3 neopixels.
 *  
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> 
#endif
#define LED_PIN    6
#define LED_COUNT 3

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  
  strip.begin();          
  strip.show(); 
  strip.setBrightness(30); 
}

void loop() {
  colorWipe(strip.Color(255,   0,   0), 50); 
  colorWipe(strip.Color(  0, 255,   0), 50); 
  colorWipe(strip.Color(  0,   0, 255), 50); 

  theaterChase(strip.Color(127, 127, 127), 50); 
  theaterChase(strip.Color(127,   0,   0), 50); 
  theaterChase(strip.Color(  0,   0, 127), 50); 

  rainbow(10);            
  theaterChaseRainbow(50); 
}


void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, color);        
    strip.show();                          
    delay(100);                
  }
}

void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  
    for(int b=0; b<3; b++) { 
      strip.clear();       
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); 
      }
      strip.show(); 
      delay(80); 
    }
  }
}

void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...    
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); 
    delay(100);  
  }
}

void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;   
  for(int a=0; a<30; a++) { 
    for(int b=0; b<3; b++) { 
      strip.clear();      
      for(int c=b; c<strip.numPixels(); c += 3) {
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); 
      }
      strip.show();                
      delay(100);                
      firstPixelHue += 65536 / 90; 
    }
  }
}
