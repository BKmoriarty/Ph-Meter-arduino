void setPoint()
{
    float pH_setPoint_dummy = pH_setPoint;
    while (true)
    {
        if (digitalRead(button_left_pin) == LOW)
        {
            pH_setPoint_dummy -= 0.05;
            selecting = false;
            delay(200);
        }
        else if (digitalRead(button_right_pin) == LOW)
        {
            pH_setPoint_dummy += 0.05;
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
            pH_setPoint = pH_setPoint_dummy;
            EEPROM_loop();

            break;
            delay(200);
        }

        Serial.println(pH_setPoint_dummy);
        print_lcd(0, 1, "pH: " + String(pH_setPoint_dummy) + "  <>");
    }
    // select_menu(menu);
}