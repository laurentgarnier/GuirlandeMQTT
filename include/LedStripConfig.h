#include "FastLED.h"

#define NUM_LEDS 77
#define PIN_LEDS 2

CRGB leds[NUM_LEDS];


void creerRuban()
{
    pinMode(PIN_LEDS, OUTPUT);
    FastLED.addLeds<WS2811, PIN_LEDS, RGB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
}

// Fixe la couleur d'un pixel sans l'afficher
void setPixel(int Pixel, byte red, byte green, byte blue)
{
    // FastLED
    leds[Pixel].r = red;
    leds[Pixel].g = green;
    leds[Pixel].b = blue;
}

// Fixe la couleur de tous les pixels et les affiche
void setAll(byte red, byte green, byte blue)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        setPixel(i, red, green, blue);
    }
    FastLED.show();
}

void AttenuationVersNoir(int ledNo, byte fadeValue)
{
    leds[ledNo].fadeToBlackBy(fadeValue);
}
