#ifndef FTSlib_h
#define FTSlib_h

#include <Arduino.h>
#include <EEPROM.h> // lib for memory for saving calibration
#include <QTRSensors.h>
#include <SoftwareSerial.h>

class FTSlib
{
public:
  // constructor
  FTSlib(int pinarray[5]);
  //functions
  void accelerateAtBlackBarRight();
  void calibrate();
  void checkButtonpress();
  void decelerateAtBlackBarLeft();
  void isStopped();
  void stopAtLongBlackBar();
  void updateDirection();
  void setMotors(int motorspeed_l, int motorspeed_r);
  // void entfernungGD();
  void hitbreak();
  bool fts_button_break = true;

private:
  //functions
  void autoCalibration(int duration_cycles, bool enable_motors);
  int eepromRead(int address);
  void eepromWrite(int address, int value);
  void getOutOfBlackZone(int waitTime);
  void goFTS();
  void initializeCalibrationArrays();
  void showDebug();

  //variables
  //PID control
  int KP = 1;
  int KD = 5;
  //pins
  int IN1;
  int IN2;
  int IN3;
  int IN4;
  int BUTTON;
  //PWM
  const int PWM_LEFT = 3;
  const int PWM_RIGHT = 8;
  //speed
  int L_DECELERATED = 80;
  int L_MAXSPEED = 255;
  int L_MINSPEED = 0;
  int R_DECELERATED = 80;
  int R_MAXSPEED = 255;
  int R_MINSPEED = 0;
  int MAX_BRAKE = 255;
  //Infrarot sensors
  unsigned int blackBarSnsrs[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // probably not really necessary, used for finding black markings on the underground
  int calibration_values[8] = {708, 864, 812, 836, 784};
  //ultra sonic sensors
  long duration;
  int distance;
  //misc
  bool fts_go = true;
  long getOutOfBlackZoneTime = 500;
  long startup_delay = 5000;
  long waitAtBlackBarTime = 5000;
  int l_maxspeed = L_MAXSPEED;
  int r_maxspeed = R_MAXSPEED;

  //start values, do not change
  bool calibrated = 0;
  int address = 0;
  int cycles = 125;
  int error = 0;
  int last_error = 0;
  int motorSpeed = 0;
  int motorspeed_l;
  int motorspeed_r;
  int position = 0;
  unsigned int sensors[8]; // see QTR Doc .readline
  unsigned long last_millis;
};

class EEPROM;
class SoftwareSerial;
class QTRSensors;

#endif