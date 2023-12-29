void setFeedTime()
{
    int feed_time_dummy = feed_time;
    while (true)
    {
        if (digitalRead(button_left_pin) == LOW)
        {
            feed_time_dummy -= 1;
            check_max_min_menu(0, 300);
            selecting = false;
            delay(200);
        }
        else if (digitalRead(button_right_pin) == LOW)
        {
            feed_time_dummy += 1;
            check_max_min_menu(0, 300);
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
            feed_time = feed_time_dummy;
            EEPROM_loop();
            break;
            delay(200);
        }

        Serial.println(feed_time_dummy);
        print_lcd(0, 1, "Feed: " + String(feed_time_dummy) + " s " + "  <>");
    }
    // select_menu(menu);
}