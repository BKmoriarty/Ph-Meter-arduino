float pH_calibrate_pH4_show = 0;
float pH_calibrate_pH7_show = 0;

void calibrate_pH()
{
    float pH_calibrate_pH4_dummy = 0;
    float pH_calibrate_pH7_dummy = 0;
    while (true)
    {
        // monitor_pH_timer.update();
        start_check_pH = false;
        monitor_pH();
        print_lcd(0, 1, "pH4: " + String(pH_volt) + " mV" + convert_steady_state(steady_pH));

        if (digitalRead(button_select_pin) == LOW)
        {
            pH_calibrate_pH4_dummy = pH_volt;
            pH_calibrate_pH4_show = pH_value_show;
            delay(500);
            break;
        }
        else if (digitalRead(button_back_pin) == LOW)
        {
            start_check_pH = true;
            delay(500);
            return;
            break;
        }
    }

    while (true)
    {
        // monitor_pH_timer.update();
        start_check_pH = false;
        monitor_pH();
        print_lcd(0, 1, "pH7: " + String(pH_volt) + " mV" + convert_steady_state(steady_pH));

        if (digitalRead(button_select_pin) == LOW)
        {
            pH_calibrate_pH7_dummy = pH_volt;
            pH_calibrate_pH7_show = pH_value_show;
            delay(500);
            break;
        }
        else if (digitalRead(button_back_pin) == LOW)
        {
            start_check_pH = true;
            delay(500);
            return;
            break;
        }
    }

    while (true)
    {
        print_lcd(0, 1, "pH4:" + String(pH_calibrate_pH4_dummy) + ",pH7: " + String(pH_calibrate_pH7_dummy));

        if (digitalRead(button_select_pin) == LOW)
        {
            pH_calibrate_pH4 = pH_calibrate_pH4_dummy;
            pH_calibrate_pH7 = pH_calibrate_pH7_dummy;
            EEPROM_loop();
            EEPROM_savePH();
            start_check_pH = true;
            delay(500);
            break;
        }
        else if (digitalRead(button_back_pin) == LOW)
        {
            start_check_pH = true;
            delay(500);
            return;
            break;
        }
    }
}