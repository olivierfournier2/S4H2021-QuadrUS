#include <Arduino.h>
#include <unity.h>
#include <qd_hw_control.h>
#include <qd_hw_config.h>
#include <qd_hw_control.cpp>

void test_rad_to_deg(void) {
    TEST_ASSERT_EQUAL(90.0, radToDeg(PI/2));
}

void Test_analog_to_angle(void){
    // pt changer pulse min selon la fonction
    TEST_ASSERT_EQUAL(0, analogToDeg(67, 0));
}

void test_deg_to_pulse_mid(void){
    TEST_ASSERT_EQUAL(1475, degToPulse(135.0, 0));
}

void test_deg_to_pulse_min(void){
    TEST_ASSERT_EQUAL(555, degToPulse(0.0, 0));
}

void test_deg_to_pulse_max(void){
    TEST_ASSERT_EQUAL(2395, degToPulse(270.0, 0));
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
}

void loop() {
    RUN_TEST(test_rad_to_deg);
    RUN_TEST(test_deg_to_pulse_min);
    RUN_TEST(test_deg_to_pulse_mid);
    RUN_TEST(test_deg_to_pulse_max);
    RUN_TEST(Test_analog_to_angle);
    UNITY_END();
}