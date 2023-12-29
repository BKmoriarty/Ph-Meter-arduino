void setRange()
{
    float pH_setPoint_range_dummy = pH_setPoint_range;
    while (true)
    {
        if (digitalRead(button_left_pin) == LOW)
        {
            pH_setPoint_range_dummy -= 0.05;
            selecting = false;
            delay(200);
        }
        else if (digitalRead(button_right_pin) == LOW)
        {
            pH_setPoint_range_dummy += 0.05;
            selecting = false;
            delay(200);
        }
        else if (digitalRead(button_back_pin) == LOW)
        {
            selecting = true;
            break;
            delay(200);
        }
        else if (digitalRead(button_select_pin) == LOW)
        {
            selecting = true;
            pH_setPoint_range = pH_setPoint_range_dummy;
            EEPROM_loop();
            break;
            delay(200);
        }

        Serial.println(pH_setPoint_range_dummy);
        print_lcd(0, 1, "+-: " + String(pH_setPoint_range_dummy) + "  <>");
        // print_lcd(0, 1, "Work: " + String(pH_setPoint - pH_setPoint_range_dummy) + " to " + String(pH_setPoint + pH_setPoint_range_dummy));
    }
    // select_menu(menu);
}