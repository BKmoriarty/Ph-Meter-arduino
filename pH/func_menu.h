
String convert_status_relay(bool status)
{
    if (status)
    {
        return "ON ";
    }
    else
    {
        return "OFF";
    }
}

void select_menu(int menu_select)
{
    lcd.clear();
    back_home = millis();
    switch (menu_select)
    {
    case 0:
        // Home show pH value and status of relay
        print_lcd(0, 0, "pH: " + String(pH_value_show) + convert_steady_state(steady_pH));
        print_lcd(0, 1, "R1: " + convert_status_relay(relay_1_status) + "     R2: " + convert_status_relay(relay_2_status));
        break;
    case 1:
        print_lcd(0, 0, "Set point normal");
        print_lcd(0, 1, "pH: " + String(pH_setPoint));
        break;
    case 2:
        print_lcd(0, 0, "Set Range normal");
        print_lcd(0, 1, "+-: " + String(pH_setPoint_range));
        break;
    case 3:
        print_lcd(0, 0, "Feed Time");
        print_lcd(0, 1, "Time: " + String(feed_time) + " s");
        break;
    case 4:
        print_lcd(0, 0, "Calibrate pH");
        break;
    default:
        break;
    }
}

void run_select(int menu_select)
{
    switch (menu_select)
    {
    case 0:
        // Home show pH value and status of relay
        Serial.println("Menu: 0");

        break;
    case 1:
        print_lcd(18, 0, "<>");
        delay(500);
        setPoint();
        select_menu(menu);
        break;
    case 2:
        print_lcd(18, 0, "<>");
        delay(500);
        setRange();
        select_menu(menu);
        break;
    case 3:
        print_lcd(18, 0, "<>");
        delay(500);
        setFeedTime();
        select_menu(menu);
        break;
    case 4:
        print_lcd(18, 0, "<>");
        delay(500);
        calibrate_pH();
        select_menu(menu);
        break;
    default:
        break;
    }
}

void run_menu()
{
    int delay_time = 500;
    if (digitalRead(button_select_pin) == LOW)
    {
        if (menu != 0)
        {
            selecting = false;
            run_select(menu);
            Serial.println("Select");
            delay(1000);
        }
    }
    else if (digitalRead(button_back_pin) == LOW)
    {
        if (menu != 0)
        {
            Serial.println("Back");
            selecting = true;
            menu = 0;
            select_menu(menu);
            delay(delay_time);
        }
    }
    else if (digitalRead(button_left_pin) == LOW)
    {
        if (selecting)
        {
            menu--;
            check_max_min_menu(0, 4);
            select_menu(menu); // run menu
            Serial.println("Left");
            delay(delay_time);
        }
    }
    else if (digitalRead(button_right_pin) == LOW)
    {
        if (selecting)
        {
            menu++;
            check_max_min_menu(0, 4);
            select_menu(menu); // run menu
            Serial.println("Right");
            delay(delay_time);
        }
    }

    if (menu == 0)
    {
        // Home show pH value and status of relay
        print_lcd(0, 0, "pH: " + String(pH_value_show) + convert_steady_state(steady_pH));
        print_lcd(0, 1, "R1: " + convert_status_relay(relay_1_status) + " R2: " + convert_status_relay(relay_2_status));
    }

    if (millis() - back_home > time_back_home)
    {
        menu = 0;
        select_menu(menu);
    }
}

void newUpdate_LCD()
{
    lcd.init();
    select_menu(menu);
}