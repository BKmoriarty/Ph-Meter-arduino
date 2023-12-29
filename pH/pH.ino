#include "init_pin.h";
#include "init_variable.h";
#include "init_eeprom.h";
#include "twoWork.h";
#include "lcd_control.h";
#include "func_set_point.h";
#include "func_set_range.h";
#include "func_set_feed.h";
#include "func_set_stop_feed.h";
#include "func_calibrate.h";
#include "func_menu.h";

TickTwo timer7(newUpdate_LCD, 10000, 0);

void setup()
{
    Serial.begin(115200); // start serial for output
    Serial.println("Start Program");
    delay(1000);

    // init EEPROM
    EEPROM_setup();
    EEPROM_readInit();
    EEPROM_loop();

    // init pin for button
    pinMode(button_select_pin, INPUT_PULLUP);
    pinMode(button_back_pin, INPUT_PULLUP);
    pinMode(button_left_pin, INPUT_PULLUP);
    pinMode(button_right_pin, INPUT_PULLUP);

    // init pin for pH sensor
    pinMode(pH_pin, INPUT);

    // init pin for Relay 3 channel
    pinMode(relay_1_pin, OUTPUT);
    pinMode(relay_2_pin, OUTPUT);
    pinMode(relay_3_pin, OUTPUT);

    digitalWrite(relay_1_pin, HIGH);
    digitalWrite(relay_2_pin, HIGH);
    digitalWrite(relay_3_pin, HIGH);

    // init pin for screen
    LCD_setup();

    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print("Welcome Loading..");
    delay(3000);
    lcd.clear();
    select_menu(0);

    // init pin for timer
    timer7.start();
}

void loop()
{
    // test area

    // end test area

    monitor_pH();

    timer7.update();

    run_menu();
}
