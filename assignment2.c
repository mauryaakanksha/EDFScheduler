

#include "assignment1.h"
#include "assignment2.h"
#include "workload.h"
#include "scheduler.h"
#include "governor.h"

// Note: Deadline of each workload is defined in the "workloadDeadlines" variable.
// i.e., You can access the dealine of the BUTTON thread using workloadDeadlines[BUTTON]
// See also deadlines.c and workload.h

// Assignment: You need to implement the following two functions.

// learn_workloads(SharedVariable* v):
// This function is called at the start part of the program before actual scheduling
// - Parameters
// sv: The variable which is shared for every function over all threads
void learn_workloads(SharedVariable* sv) {
  // TODO: Fill the body
  // This function is executed before the scheduling simulation.
  // You need to calculate the execution time of each thread here.
  
  // Thread functions for workloads: 
  // thread_button, thread_twocolor, thread_temp, thread_track,
  // thread_shock, thread_rgbcolor, thread_aled, thread_buzzer
  
  // Tip 1. You can call each workload function here like:
  // thread_button();
  
  // Tip 2. You can get the current time here like:
  // long long curTime = get_current_time_us();
  

  // Calculate the worst case execution time for each threads

  long long startTime, curTime, totalExecTime;
  int count =0;
  
  set_by_min_freq();

  count =0;

  while ( count <100 ) {
    
    startTime = get_current_time_us();
    thread_button(&sv);
    curTime = get_current_time_us();
    totalExecTime = curTime - startTime;
    
    if ( sv->bWCETMax[BUTTON] < totalExecTime) {
      sv->bWCETMax[BUTTON] = totalExecTime;
    }
    count++;    
  }

  count =0;

  while ( count <100 ) {

    startTime = get_current_time_us();
    thread_twocolor(&sv);
    curTime = get_current_time_us();
    totalExecTime = curTime - startTime;

    if ( sv->bWCETMax[TWOCOLOR] < totalExecTime) {
      sv->bWCETMax[TWOCOLOR] = totalExecTime;
    }
    count++;
  }

  count =0;

  while ( count <100 ) {

    startTime = get_current_time_us();
    thread_temp(&sv);
    curTime = get_current_time_us();
    totalExecTime = curTime - startTime;

    if ( sv->bWCETMax[TEMP] < totalExecTime) {
      sv->bWCETMax[TEMP] = totalExecTime;
    }
    count++;
  }

  count =0;

  while ( count <100 ) {

    startTime = get_current_time_us();
    thread_track(&sv);
    curTime = get_current_time_us();
    totalExecTime = curTime - startTime;

    if ( sv->bWCETMax[TRACK] < totalExecTime) {
      sv->bWCETMax[TRACK] = totalExecTime;
    }
    count++;
  }

  count =0;

  while ( count <100 ) {

    startTime = get_current_time_us();
    thread_shock(&sv);
    curTime = get_current_time_us();
    totalExecTime = curTime - startTime;

    if ( sv->bWCETMax[SHOCK] < totalExecTime) {
      sv->bWCETMax[SHOCK] = totalExecTime;
    }
    count++;
  }

  count =0;

  while ( count <100 ) {

    startTime = get_current_time_us();
    thread_rgbcolor(&sv);
    curTime = get_current_time_us();
    totalExecTime = curTime - startTime;

    if ( sv->bWCETMax[RGBCOLOR] < totalExecTime) {
      sv->bWCETMax[RGBCOLOR] = totalExecTime;
    }
    count++;
  }

  count =0;

  while ( count <100 ) {

    startTime = get_current_time_us();
    thread_aled(&sv);
    curTime = get_current_time_us();
    totalExecTime = curTime - startTime;

    if ( sv->bWCETMax[ALED] < totalExecTime) {
      sv->bWCETMax[ALED] = totalExecTime;
    }
    count++;
  }

  count =0;

  while ( count <100 ) {

    startTime = get_current_time_us();
    thread_buzzer(&sv);
    curTime = get_current_time_us();
    totalExecTime = curTime - startTime;

    if ( sv->bWCETMax[BUZZER] < totalExecTime) {
      sv->bWCETMax[BUZZER] = totalExecTime;
    }
    count++;
  }

  
   int i =0;
   for (i=0; i< 8; i++) {
     sv->bCurrDeadLines[i] = workloadDeadlines[i];
   }
  
}


// select_task(SharedVariable* sv, const int* aliveTasks):
// This function is called while runnning the actual scheduler
// - Parameters
// sv: The variable which is shared for every function over all threads
// aliveTasks: an array where each element indicates whether the corresponed task is alive(1) or not(0).
// idleTime: a time duration in microsecond. You can know how much time was waiting without any workload
//           (i.e., it's larger than 0 only when all threads are finished and not reache the next preiod.)
// - Return value
// TaskSelection structure which indicates the scheduled task and the CPU frequency
TaskSelection select_task(SharedVariable* sv, const int* aliveTasks, long long idleTime) {
  // TODO: Fill the body
  // This function is executed inside of the scheduling simulation.
  // You need to implement an energy-efficient EDF (Earliest Deadline First) scheduler.
  
  // Tip 1. You may get the current time elapsed in the scheduler here like:
  // long long curTime = get_scheduler_elapsed_time_us();
  
  // Also, do not make any interruptable / IO tasks in this function.
  // You can use printfDBG instead of printf.
  
  // Sample scheduler: Round robin
  // It selects a next thread using aliveTasks.
  
  
  long long currTime = get_scheduler_elapsed_time_us();
  int selection =0;
  int i = 0;
  long long execTime = currTime - sv->bPrevTime;
  long long minDeadLine = 9223372036854775807;

  
  for ( i =0; i< 8 ; i++) {
    
    if ( aliveTasks[i] ==1 ) {
      sv->bCurrDeadLines[i] = sv->bCurrDeadLines[i] - execTime;
    } else {
      sv->bCurrDeadLines[i] = workloadDeadlines[i];
      sv->bTotalExecTime[sv->bPrevSel]= 0;
    }
    
  }

  sv->bPrevTime = currTime;
  sv->bTotalExecTime[sv->bPrevSel] += execTime;
  
  for ( i =0; i < 8 ; i++) {

    if ( (aliveTasks[i] == 1) && (sv->bCurrDeadLines[i] < minDeadLine) ) {
      minDeadLine = sv->bCurrDeadLines[i];
      selection = i;
    }
  }
 
  sv->bPrevSel = selection;;

  
  int freq = 0;
  
  for ( i =0; i<8 ; i++) {
    
    if ( aliveTasks[i] ==  0 ) {      
      if ( sv->bWCETMax[i] + ((sv->bWCETMax[selection]) - sv->bTotalExecTime[selection])  >=  sv->bCurrDeadLines[selection]) {
	freq = 1;
	break;
      }      
    } else {
      if ( sv->bWCETMax[i] - sv->bTotalExecTime[i] >=  sv->bCurrDeadLines[i]) {
	freq =1;
	break;
      }
    }
  }
  

  sv->bPrevFreq = freq;

  /*
  static long long energy=0;
  
  if ( sv->bPrevFreq == 1 ) {
    energy += 800*(execTime - idleTime) + 50*idleTime;
  }else {
    energy += 400*(execTime - idleTime) + 50*idleTime;
  }
  
  printf(" Energy : %lld \n", energy);
  */
  
  // The retun value can be specified like this:
  TaskSelection sel;
  sel.task = selection; // The thread ID which will be scheduled. i.e., 0(BUTTON) ~ 7(BUZZER)
  sel.freq = freq; // Request the maximum frequency (if you want the minimum frequency, use 0 instead.)

  return sel;
}
