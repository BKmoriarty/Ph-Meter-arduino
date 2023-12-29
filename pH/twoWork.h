#include <TickTwo.h>

const int numDataPoints = 10;
float sensorData[numDataPoints];
int currentIndex = 0;

int count = 0;

bool stop_feed1 = false;
bool stop_feed2 = false;
bool stop_all = false;

String convert_steady_state(bool status)
{
    if (status)
    {
        return " ";
    }
    else
    {
        return "'";
    }
}

void run_stop_feed1()
{

    if (count < stop_feed_time)
    {
        start_check_pH = false;
        count++;
        Serial.println("Stop Feed 1 : " + String(count) + "/" + String(stop_feed_time));
    }
    else
    {
        start_check_pH = true;
        count = 0;
        relay_1_status = false;
        stop_feed1 = false;
        stop_all = true;
        Serial.println("Start Feed 1 : OK");
    }
}

void run_stop_feed2()
{

    if (count < stop_feed_time)
    {
        start_check_pH = false;
        count++;
        Serial.println("Stop Feed 2 : " + String(count) + "/" + String(stop_feed_time));
    }
    else
    {
        start_check_pH = true;
        count = 0;
        relay_2_status = false;
        stop_feed2 = false;
        stop_all = true;
        Serial.println("Start Feed 2 : OK");
    }
}

void run_feed_time1()
{

    if (count < feed_time)
    {
        digitalWrite(relay_1_pin, LOW);
        count++;
        start_check_pH = false;
        Serial.println("Relay 1 ON: " + String(count) + "/" + String(feed_time));
    }
    else
    {
        digitalWrite(relay_1_pin, HIGH);
        count = 0;
        relay_1_status = false;
        start_check_pH = false;
        stop_feed1 = true;
        Serial.println("Relay 1 OFF");
    }
}

void run_feed_time2()
{

    if (count < feed_time)
    {
        digitalWrite(relay_2_pin, LOW);
        count++;
        start_check_pH = true;
        Serial.println("Relay 2 ON: " + String(count) + "/" + String(feed_time));
    }
    else
    {
        digitalWrite(relay_2_pin, HIGH);
        count = 0;
        relay_2_status = false;
        start_check_pH = false;
        stop_feed2 = true;
        Serial.println("Relay 2 OFF");
    }
}

void calculate_pH()
{
    if (pH_value < pH_setPoint - pH_setPoint_range)
    {
        if (relay_1_status == false)
        {
            relay_1_status = true;
            start_check_pH = false;
            Serial.println("Relay 1 ON");
        }
    }
    else if (pH_value > pH_setPoint + pH_setPoint_range)
    {
        if (relay_2_status == false)
        {
            relay_2_status = true;
            start_check_pH = false;
            Serial.println("Relay 2 ON");
        }
    }
    else
    {
        if (stop_all)
        {
            digitalWrite(relay_3_pin, LOW);
            relay_3_status = true;
            while (true)
            {
                /* code */
            }
        }
    }
}
float calculateAverage(float values[], int numValues)
{
    float total = 0.0;

    // Calculate the sum of all values in the array
    for (int i = 0; i < numValues; i++)
    {
        total += values[i];
    }

    // Calculate the average
    float average = total / numValues;

    return average;
}

unsigned long time_now = 0;
float pH_volt;

void monitor_pH()
{

    if (millis() - time_now > 1000)
    {
        time_now = millis();

        float pH_analog = analogRead(pH_pin);
        pH_volt = pH_analog * esp_voltage / esp_adc + esp_error;
        float slope = (buffer_pH7 - buffer_pH4) / (pH_calibrate_pH7 - pH_calibrate_pH4);
        float intercept = buffer_pH4 - (slope * pH_calibrate_pH4);
        float pH_values = slope * pH_volt + intercept;

        // test

        // Store the data in the array
        sensorData[currentIndex] = pH_values;

        // Increment the index and wrap around if necessary
        currentIndex = (currentIndex + 1) % numDataPoints;

        // Calculate the slope using a simple difference
        int prevIndex = (currentIndex + numDataPoints - 1) % numDataPoints;
        int slopes = sensorData[currentIndex] - sensorData[prevIndex];

        int numValues = sizeof(sensorData) / sizeof(sensorData[0]);
        // pH_value_show = calculateAverage(sensorData, numValues);

        if (slopes > 0)
        {
            Serial.println("pH is rising");
            pH_value_show = pH_values;
            steady_pH = false;
        }
        else if (slopes < 0)
        {
            Serial.println("pH is falling");
            pH_value_show = pH_values;
            steady_pH = false;
        }
        else
        {
            steady_pH = true;
            double x = calculateAverage(sensorData, numValues);
            if (x > 0 && x < 14)
            {
                pH_value = x;
                pH_value_show = x;
                if (start_check_pH)
                    calculate_pH();
            }
            else
            {
                Serial.println("pH is out of range");
                pH_value = nan("");
                pH_value_show = nan("");
            }
        }

        if (relay_1_status)
        {
            run_feed_time1();
        }
        else
        {
            digitalWrite(relay_1_pin, HIGH);
        }
        if (relay_2_status)
        {
            run_feed_time2();
        }
        else
        {
            digitalWrite(relay_2_pin, HIGH);
        }
        if (stop_feed1)
        {
            run_stop_feed1();
            digitalWrite(relay_1_pin, HIGH);
        }
        if (stop_feed2)
        {
            run_stop_feed2();
            digitalWrite(relay_2_pin, HIGH);
        }

        Serial.println("pH: " + String(pH_values) + convert_steady_state(steady_pH) + " Slope: " + String(slopes) + " pH_volt: " + String(pH_volt) + " mV pH_analog: " + String(pH_analog));
    }

    if (relay_1_status && !stop_all)
    {
        digitalWrite(relay_1_pin, LOW);
        relay_3_status = true;
    }
    if (relay_2_status && !stop_all)
    {
        digitalWrite(relay_2_pin, LOW);
        relay_3_status = true;
    }
    if (relay_1_status == false && relay_2_status == false && stop_feed1 == false && stop_feed2 == false && start_check_pH)
    {
    }
    else
    {
        digitalWrite(relay_3_pin, HIGH);
        relay_3_status = false;
    }
}
