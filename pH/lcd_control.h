// Define func for main program
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(
    LCD_ADDRESS,
    LCD_COLS,
    LCD_RAWS);

void LCD_setup()
{
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void print_lcd(int col, int row, String txt)
{

    lcd.setCursor(col, row);
    lcd.print(txt);
}

void check_max_min_menu(int min, int max)
{
    if (menu < min)
    {
        menu = min;
    }
    else if (menu > max)
    {
        menu = max;
    }
}
