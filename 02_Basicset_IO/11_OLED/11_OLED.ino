#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> //by Adafruit

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
  Wire.begin(1, 3); //(SDA, SCL) 1,3:ConnectorA 5,4:ConnectorB

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for(;;); //Infinite loop when screen initialization fails
  }

  display.clearDisplay();

  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 5);
  display.print(F("HELLO!"));
  display.setCursor(0, 40);
  display.print(F("WELCOME"));
  display.setCursor(0, 65);
  display.print(F("JUNICHI"));
  display.startscrollright(0x00, 0x0F); //左から右
// display.startscrolldiagleft(0x0A, 0x0F); //右下から左上

  display.display();
}

// デフォルト
void loop()
{
}

// void loop()
// {
//   display.invertDisplay(true);  // 色を反転
//   delay(500);
//   display.invertDisplay(false); // 元に戻す
//   delay(500);
// }