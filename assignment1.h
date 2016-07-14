#ifndef _ASSIGNMENT_BODY_
#define _ASSIGNMENT_BODY_

// A. Pin number definitions (DO NOT MODIFY)
// Important! USE the pin numbers and WIRE.
// We use 8 sensors.
//
// 1. Button
#define PIN_BUTTON 0

// 2. 2-Color LED
#define PIN_YELLOW 1

// 3. Temperature
#define PIN_TEMP 4

// 4. Tracking Sensor
#define PIN_TRACK 5

// 5. Shock Sensor
#define PIN_SHOCK 6

// 6. RGB(3-Color) LED
#define PIN_RED 7
#define PIN_GREEN 8
#define PIN_BLUE 9

// 7. Auto-flash Red
#define PIN_ALED 12

// 8. Buzzer
#define PIN_BUZZER 13

// B. Shared structure
// All thread fuctions get a shared variable of the structure
// as the function parameter.
// If needed, you can add anything in this structure.

//
#define INITIAL 0

#define DRIVING 1

#define NORMAL 0

#define EMERGENCY_TEMP 1

#define EMERGENCY_TRACK 2

#define EMERGENCY_SHOCK 3


typedef struct shared_variable {
  int bProgramExit; // Once it is set to 1, the program will be terminated.
  int bCurrentState;
  int bEmergencyState;
  int bPrevButtonState;
  int bTempState;
  long long bWCETMax[8];
  long long bCurrDeadLines[8];
  long long bTotalExecTime[8];
  int  bPrevSel;
  int bPrevFreq;
  long long bPrevTime;
} SharedVariable;


// C. Functions
// You need to implement following functions.
// Do not change any function name here.
void init_shared_variable(SharedVariable* sv);
void init_sensors(SharedVariable* sv);

void body_button(SharedVariable* sv);
void body_twocolor(SharedVariable* sv);
void body_temp(SharedVariable* sv);
void body_track(SharedVariable* sv);
void body_shock(SharedVariable* sv);
void body_rgbcolor(SharedVariable* sv);
void body_aled(SharedVariable* sv);
void body_buzzer(SharedVariable* sv);

#endif
