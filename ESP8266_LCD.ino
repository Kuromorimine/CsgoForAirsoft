#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//ledandbuzzerAtGPIO10

#define LED_BUZZER_PIN 15

unsigned long curr_millis;
unsigned long total_count_down_ms = 30 * 1000;
unsigned int time_sec, time_min;
long count_down;

// for LED
unsigned long led_total_interval_ms = 1000;
unsigned long led_interval_ms = 1000;
unsigned long led_beep_interval_ms = 100;
long led_ms = 0;

char buff[4];

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  lcd.init();       // Initialize the LCD
  lcd.backlight();  // Turn on the backlight
  lcd.clear();      // Clear the LCD screen
  pinMode(LED_BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print(" Time Remaing.. ");
}
void loop() {
  curr_millis = millis();

  digitalWrite(LED_BUZZER_PIN, curr_millis - led_ms < led_beep_interval_ms);
  if (curr_millis - led_ms > led_interval_ms) {
    led_ms = curr_millis;
  }

  count_down = total_count_down_ms - curr_millis;
  if (count_down < 0) {

    digitalWrite(LED_BUZZER_PIN, count_down >= -3000);
  } else {
    led_interval_ms = 1.0 * count_down / total_count_down_ms * led_total_interval_ms;

    time_min = floor(count_down / 1000 / 60);
    time_sec = floor(count_down / 1000) - (time_min * 60);

    lcd.setCursor(0, 1);
    lcd.print(time_min);

    lcd.setCursor(2, 1);
    lcd.print(":");

    lcd.setCursor(3, 1);
    sprintf(buff, "%02d", time_sec);
    lcd.print(buff);
  }

}
