#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_DotStarMatrix.h>
#include <Adafruit_DotStar.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "nums.h"
#include "secrets.h"

#define WIDTH       16
#define HEIGHT      16
#define DATAPIN     19
#define CLOCKPIN    18
#define BRIGHTNESS  30

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

int status = WL_IDLE_STATUS;
const int networkTimeout = 30*1000;
const int networkDelay = 1000;
const int updateRate = 15000;

int current_leader = 0;

int numberArray[]={
  0,
  1,
  2,
  3,
  4,
  6,
  7,
  8,
  9,
  10,
  11,
  12,
  13,
  14,
  15,
  17,
  18,
  19,
  20,
  21,
  22,
  24,
  27,
  32,
  34,
  37,
  38,
  41,
  42,
  43,
  47,
  48,
  51,
  52,
  53,
  54,
  62,
  66,
  77,
  88
};

const int (*numberPointerArray[40])[3]= {
   doublezero,
   one,
   two,
   three,
   four,
   six,
   seven,
   eight,
   nine,
   ten,
   eleven,
   twelve,
   thirteen,
   fourteen,
   fifteen,
   seventeen,
   eighteen,
   nineteen,
   twenty,
   twentyone,
   twentytwo,
   twentyfour,
   twentyseven,
   thirtytwo,
   thirtyfour,
   thirtyseven,
   thirtyeight,
   fortyone,
   fortytwo,
   fortythree,
   fortyseven,
   fortyeight,
   fiftyone,
   fiftytwo,
   fiftythree,
   fiftyfour,
   sixtytwo,
   sixtysix,
   seventyseven,
   eightyeight
};

Adafruit_DotStarMatrix pixo = Adafruit_DotStarMatrix(
                                  16, 16, DATAPIN, CLOCKPIN,
                                  DS_MATRIX_TOP + DS_MATRIX_LEFT +
                                  DS_MATRIX_ROWS + DS_MATRIX_PROGRESSIVE,
                                  DOTSTAR_BGR);

const uint16_t colors[] = {
  pixo.Color(100, 100, 100), pixo.Color(0, 255, 0), pixo.Color(0, 0, 255)
};

int x = pixo.width();
int col = 0;

void setup() {
  heap_caps_malloc(75000, MALLOC_CAP_8BIT);
  Serial.begin(115200);
  pixo.begin();
  pixo.setTextWrap(false);
  pixo.setBrightness(BRIGHTNESS);
  //pixo.setFont(&FreeSans9pt7b);
  pixo.setTextColor(colors[col]);

  WiFi.enableSTA(true);
  
  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    delay(500);
  }

  Serial.print("Connected to the network");

  update_number(stageflag);
}

void check_race_status() {

  int _past_leader = current_leader;

  HTTPClient http;

  http.useHTTP10(true);
  http.begin("https://www.nascar.com/live/feeds/series_1/4992/live_feed.json");
  int httpCode = http.GET();

  StaticJsonDocument<64> filter;
  filter["flag_state"] = true;
  filter["vehicles"][0]["vehicle_number"] = true;

  DynamicJsonDocument doc(2048);
  deserializeJson(doc, http.getStream(), DeserializationOption::Filter(filter));

  current_leader = doc["vehicles"][0]["vehicle_number"].as<int>();

  Serial.println(current_leader);

  http.end();

  if (current_leader != _past_leader) {
    update_number(current_leader);
  }
}

void update_number(int current_leader) {
  int index;
  Serial.print("Current_leader :");
  Serial.println(current_leader);
  for (int l = 0; l < 40; l++) {
    if (numberArray[l] == current_leader) {
      index = l;
      break;
    }
  }

  pixo.fillScreen(0);
  
  slide_in_from_right(numberPointerArray[index]);
  
}

void loop() {
  // Test individual number display through serial montor
  if (Serial.available()) {
    int read = Serial.parseInt();
    if (read != 0){
      update_number(read);
    }
  }
  
  check_race_status();
  delay(updateRate);


  // Uncomment section to test numbers display
  
  //  for (int i = 0; i < 40; i++) {
  //    slide_in_from_right(numberPointerArray[i]);
  //    delay(30);
  //  }
  //  slide_in_from_right(checkeredflag);
  //  delay(3000);
  //  slide_in_from_right(stageflag);
}

//Slides given image in from right side of Pixo
void slide_in_from_right(const int image[256][3]) {
  for (int j = 15; j >= 0; j--) {
      int curs = 16 - j;
      for (int i = 0; i < 16; i++)
      {
        for (int c = 0; c < curs; c++) {
          pixo.setPixelColor(j + c + (i * 16), image[(i * 16) + c][0], image[(i * 16) + c][1], image[(i * 16) + c][2]); 
        }
      }
        pixo.show();
        delay(75);
    }
}
