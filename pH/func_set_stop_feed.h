void setStopFeed()
{
    int stop_feed_time_dummy = stop_feed_time;
    while (true)
    {
        if (digitalRead(button_left_pin) == LOW)
        {
            stop_feed_time_dummy -= 5;
            check_max_min_menu(0, 3600);
            selecting = false;
            delay(200);
        }
        else if (digitalRead(button_right_pin) == LOW)
        {
            stop_feed_time_dummy += 5;
            check_max_min_menu(0, 3600);
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
            stop_feed_time = stop_feed_time_dummy;
            EEPROM_loop();
            break;
            delay(200);
        }

        Serial.println(stop_feed_time_dummy);
        print_lcd(0, 1, "Stop: " + String(stop_feed_time_dummy) + " s ");
    }
    // select_menu(menu);
}