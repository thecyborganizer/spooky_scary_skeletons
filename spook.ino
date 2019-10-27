#include <FastLED.h>

#define NUM_LEDS 30
#define DATA_PIN 6
#define DELAY_TIME 125

char text[] = "SPOOKYSCARYSKELETONSANDSHIVERSDOWNYOURSPINEEEEE";
//char text[] = "SPOOKYSCARY";
int index = 0;

CRGB leds[NUM_LEDS];

#define NUM_BITS ((sizeof(text) - 1) * sizeof(char) * 8)

bool index_to_bit(int index) {
    char c = text[index/(sizeof(char)*8)];
    int mask = ((1 << 7) >> (index % 8));
    return (mask & ((int) c)) != 0;
}

void populate_leds(int s) {
    for (int i = 0; i < NUM_LEDS; i++) {
        int bit_index = (i + s) % NUM_BITS;

        if(index_to_bit(bit_index)) {
            leds[i] = CRGB::OrangeRed;
        } else {
            leds[i] = CRGB::Purple;
        }
    }
    FastLED.show();
}

void setup() {    
    text[sizeof(text) - 5] = 0xFF;
    text[sizeof(text) - 4] = 0x00;
    text[sizeof(text) - 3] = 0xFF;
    text[sizeof(text) - 2] = 0x00;
    Serial.begin(9600);
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    populate_leds(index);
    FastLED.delay(DELAY_TIME);
}

void loop() {    
    index++;
    populate_leds(index);
    FastLED.delay(DELAY_TIME);
}