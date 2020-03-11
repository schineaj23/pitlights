#include <FastLED.h>
#define DATA_PIN 6
#define DATA_PIN_STRING 5
#define NUM_LEDS 88
#define STRING_LEDS 200
#define LED_STRIPS 8
#define NUM_LED_PER_STRIP 11

CRGB leds[NUM_LEDS];
CRGB led_string[STRING_LEDS];

// Use this for converting images to arrays:
// https://www.digole.com/tools/PicturetoC_Hex_converter.php
// Make sure image is 8x11 and '256 Color RRRGGGBB' option selected
// all even y lines are reversed.


unsigned char smile[] = {
  0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc
  , 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc
  , 0xfc, 0xfc, 0x00, 0xfc, 0xfc, 0x00, 0xfc, 0xfc
  , 0xfc, 0xfc, 0x00, 0xfc, 0xfc, 0x00, 0xfc, 0xfc
  , 0xfc, 0xfc, 0x00, 0xfc, 0xfc, 0x00, 0xfc, 0xfc
  , 0xfc, 0xfc, 0x00, 0xfc, 0xfc, 0x00, 0xfc, 0xfc
  , 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc
  , 0xfc, 0x00, 0xfc, 0xfc, 0xfc, 0xfc, 0x00, 0xfc
  , 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc
  , 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc
  , 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc
};

unsigned char op_logo[] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
  , 0xff, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff
  , 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff
  , 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc, 0x2b, 0x2b, 0x2b, 0x2b, 0xff
  , 0xff, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x2b, 0xff, 0xff, 0x2b, 0xff
  , 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x2b, 0x2b, 0x2b, 0x2b, 0xff
  , 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x2b, 0xff, 0xff, 0xff, 0xff
  , 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff

};

unsigned char smoole[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  , 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00
  , 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00
  , 0x00, 0xe0, 0x00, 0xe0, 0x00, 0x00, 0xe0, 0x00, 0xe0, 0x00, 0x00
  , 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0x00, 0x00
  , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

unsigned char color[] = {
  0xe0, 0xec, 0xfc, 0x35, 0x17, 0x2b, 0xaa, 0x00, 0x00, 0x00, 0x00
  , 0xe0, 0xec, 0xfc, 0x35, 0x17, 0x2b, 0xaa, 0x00, 0x00, 0x00, 0x00
  , 0xe0, 0xec, 0xfc, 0x35, 0x17, 0x2b, 0xaa, 0x00, 0x00, 0x00, 0x00
  , 0xe0, 0xec, 0xfc, 0x35, 0x17, 0x2b, 0xaa, 0x00, 0x00, 0x00, 0x00
  , 0xe0, 0xec, 0xfc, 0x35, 0x17, 0x2b, 0xaa, 0xff, 0xff, 0xff, 0xff
  , 0xe0, 0xec, 0xfc, 0x35, 0x17, 0x2b, 0xaa, 0xff, 0xff, 0xff, 0xff
  , 0xe0, 0xec, 0xfc, 0x35, 0x17, 0x2b, 0xaa, 0xff, 0xff, 0xff, 0xff
  , 0xe0, 0xec, 0xfc, 0x35, 0x17, 0x2b, 0xaa, 0xff, 0xff, 0xff, 0xff

};


void bit_to_rgb(unsigned char c, int &r, int &g, int &b) {
  r   = (c >> 5) * 255 / 7;
  g = ((c >> 2) & 0x07) * 255 / 7;
  b  = (c & 0x03) * 255 / 3;
}

void correct_image_AAH(unsigned char img[]) {
  unsigned char new_img[NUM_LEDS];

  for (int i = 0; i < 3; i++) {
    int incr = i*16;

    for(int f = 0; f < NUM_LEDS; f += 1) {
      incr += 1;
      new_img[incr] = img[i * 16 + f];
    }
    for (int b = 7; b < NUM_LEDS; b += -1) {
      incr += 1;
      new_img[incr] = img[(i*16)+16+b];
    }

    img = new_img;
  }
}

void reverse_range(unsigned char* buf, int l, int r) {
  while(l < r) {
    unsigned char temp = buf[l];
    buf[l++] = buf[r];
    buf[r--] = temp;
  }
}

void correct_but_for_the_third_time(unsigned char img[]) {
  reverse_range(img, 0, 10);
  for(int i=1; i<4; i++) {
    int index = i*11*2;
    reverse_range(img, index, index + 10);
  }
}

void draw_img(unsigned char img[]) {
  for (int i = 0; i < NUM_LEDS; i++) {
    int r, g, b;
    bit_to_rgb(img[i], r, g, b);
    leds[i].setRGB(r, g, b);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812, DATA_PIN_STRING>(led_string, STRING_LEDS);
}

void loop() {
  // put your main code here, to run repeatedly:
  correct_but_for_the_third_time(color);
  draw_img(color);
  led_string[0].setRGB(0, 0, 255);
  FastLED.show();
}
