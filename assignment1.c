#include "assignment1.h"
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdint.h>

void init_shared_variable(SharedVariable* sv) {
	// You can initialize the shared variable if needed.
  sv->bProgramExit = 0;
  sv->bCurrentState = INITIAL;
  sv->bEmergencyState = NORMAL;
  sv->bPrevButtonState = LOW;
  sv->bTempState = LOW;

  int i;

  for (i =0; i<8 ; i++) {
    sv->bWCETMax[i] =0;
    sv->bCurrDeadLines[i] =0;
    sv->bTotalExecTime[i] =0;
  }
  sv->bPrevTime = 0;
  sv->bPrevSel =0;
  sv->bPrevFreq =0;
}

void init_sensors(SharedVariable* sv) {

  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_YELLOW, OUTPUT);
  pinMode(PIN_TEMP, INPUT);
  pinMode(PIN_TRACK, INPUT);
  pinMode(PIN_SHOCK, INPUT);
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(PIN_ALED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);


  softPwmCreate(PIN_RED, 0, 0xff);
  softPwmCreate(PIN_GREEN, 0, 0xff);
  softPwmCreate(PIN_BLUE, 0, 0xff);

  
}

void body_button(SharedVariable* sv) {
  //sv->bProgramExit = 1;

  int currButtonState = digitalRead(PIN_BUTTON);

  if ( (sv->bCurrentState == INITIAL ) && (currButtonState == HIGH) && (currButtonState != sv->bPrevButtonState) ) {
    sv->bCurrentState = DRIVING;
  } else if ( (sv->bCurrentState == DRIVING) && (currButtonState == HIGH) && (currButtonState != sv->bPrevButtonState) && (sv->bEmergencyState != NORMAL) ) {
    sv->bCurrentState = INITIAL;
    sv->bEmergencyState = NORMAL;
  } else if ( currButtonState == HIGH && (currButtonState != sv->bPrevButtonState) ) { 
    sv->bCurrentState = INITIAL;
  }

  sv->bPrevButtonState = currButtonState;
}

void body_twocolor(SharedVariable* sv) {

  if (sv->bCurrentState == INITIAL) {
    digitalWrite(PIN_YELLOW, LOW);
  } else if (sv->bCurrentState == DRIVING) {
    digitalWrite(PIN_YELLOW, HIGH);
  }
  
}

void body_temp(SharedVariable* sv) {

  if ( (sv->bCurrentState == DRIVING) && (digitalRead(PIN_TEMP) == HIGH)) {
    sv->bTempState = HIGH;
  } else if ( digitalRead(PIN_TEMP) == LOW) {
    sv->bTempState = LOW;
  }
}

void body_track(SharedVariable* sv) {

  if ( (sv->bCurrentState == DRIVING) && ( digitalRead(PIN_TRACK) == LOW) ) {
    sv->bEmergencyState = EMERGENCY_TRACK;
  }
}

void body_shock(SharedVariable* sv) {

  if ( (sv->bCurrentState == DRIVING) && (digitalRead(PIN_SHOCK) == LOW) ) {
    sv->bEmergencyState = EMERGENCY_SHOCK;
  }
}

void body_rgbcolor(SharedVariable* sv) {

  if (sv->bCurrentState == INITIAL) {
    softPwmWrite(PIN_RED, LOW);
    softPwmWrite(PIN_GREEN, LOW);
    softPwmWrite(PIN_BLUE, HIGH);
  } else if ( sv->bCurrentState == DRIVING) {

    if ( sv->bEmergencyState == NORMAL) {
    softPwmWrite(PIN_RED, LOW);
    softPwmWrite(PIN_GREEN, HIGH);
    softPwmWrite(PIN_BLUE, LOW);
    } else if (sv->bEmergencyState == EMERGENCY_TRACK) {
      softPwmWrite(PIN_RED, 0x76);
      softPwmWrite(PIN_GREEN, 0x00);
      softPwmWrite(PIN_BLUE, 0xee);
    } else if ( sv->bEmergencyState == EMERGENCY_SHOCK) {
      softPwmWrite(PIN_RED, HIGH);
      softPwmWrite(PIN_GREEN, LOW);
      softPwmWrite(PIN_BLUE, LOW);
    }
    
  }
}

void body_aled(SharedVariable* sv) {

  if (sv->bCurrentState == INITIAL) {
    digitalWrite(PIN_ALED, LOW);
  } else if ( (sv->bCurrentState == DRIVING) && (sv->bTempState == HIGH)) {
    digitalWrite(PIN_ALED, HIGH);
  } else if ( (sv->bCurrentState == DRIVING) && (sv->bTempState == LOW)) {
    digitalWrite(PIN_ALED, LOW);
  }
  
}

void body_buzzer(SharedVariable* sv) {

  if (sv->bCurrentState ==INITIAL) {
    digitalWrite(PIN_BUZZER, LOW);
  } else if ( (sv->bCurrentState == DRIVING) && (sv->bTempState == HIGH) ){
    digitalWrite(PIN_BUZZER, HIGH);
  } else if ( (sv->bCurrentState == DRIVING) && (sv->bTempState ==LOW)) {
    digitalWrite(PIN_BUZZER,LOW);
  }
}
