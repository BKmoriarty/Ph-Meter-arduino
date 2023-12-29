bool start_check_pH = true; // check pH sensor is start or not
int menu = 0;               // menu number
bool selecting = true;      // check select button is press or not
float esp_voltage = 5.0;    // esp voltage
float esp_adc = 4096.0;     // esp adc
float esp_error = 0.0;      // esp error

float pH_setPoint = 7.00;      // pH set point
float pH_setPoint_range = 0.5; // pH set point range
float pH_value = 0;            // pH value
float pH_value_show = 0;       // pH value show
int feed_time = 5;             // feed time
int stop_feed_time = 10;       // stop feed time
float back_home;               // back home time
int time_back_home = 60000;    // time to back home
float pH_calibrate_pH4 = 0;    // pH calibrate pH4
float pH_calibrate_pH7 = 0;    // pH calibrate pH7
float buffer_pH4 = 4.01;       // buffer pH4
float buffer_pH7 = 6.86;       // buffer pH7
bool steady_pH = false;        // check pH is steady or not

bool relay_1_status = false; // relay 1 status
bool relay_2_status = false; // relay 2 status
bool relay_3_status = false; // relay 3 status
