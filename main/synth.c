#include <stdio.h>
#include <stdlib.h>
#include "driver/dac.h"
#include "driver/timer.h"

//define a Saw type to hold some data
typedef struct Saw_ {
  int frequency;
  int count;
  double val;
} Saw;

//constructor function for a new Saw
Saw* new_Saw(int frequency) {
  Saw* result = malloc(sizeof(Saw)); //allocate a certain number of bytes to hold the new Saw and
  //store the pointer to that memory in result (result is a pointer to a Saw)

  //populate the new Saw 
  result->frequency = frequency;
  result->count = 0;
  result->val = 0.0;

  //and finally return it!
  return result;
}

//set the frequency of a Saw
void saw_Set_Frequency(Saw* self, int frequency) {
  self->frequency = frequency;
}

//produce the next sample of the sawtooth wave
unsigned char saw_Next_Sample(Saw* self, int sample_rate) {

  //keep track of how many samples have passed. reset once phase is 0 again.
  if (self->count >= (int) (sample_rate / self->frequency)) {
    self->count = 0;
  } else {
    self->count += 1;
  }

  if (self->count == 0) { //if phase is 0
    self->val = 1.0; //then set the value to be 1 (the spike at the beginning of the wave)
  } else {
    self->val -= 1.0 / (sample_rate / self->frequency); //otherwise ramp down
  }

  return (unsigned char) (self->val * 255); //return the value, but mapped to 0-255 instead of 0-1
}

Saw* saw;

static intr_handle_t interrupt_handle;

void interrupt_for_sample(void* arg) { // function that gets called upon timer interrupt 
    
  // clear the interrupt status bit
  TIMERG0.int_clr_timers.t0 = 1;
  TIMERG0.hw_timer[0].config.alarm_en = 1;

  dac_output_voltage(DAC_CHANNEL_2, saw_Next_Sample(saw, 40000));
}

timer_config_t config = { // define the timer configuation we want to use.
  .alarm_en = true, // alarm is enabled
  .counter_en = false,
  .divider = 2, // incoming 80 mHz clock gets divided by 2 for a 40 mHz clock.
  .auto_reload = true,
  .counter_dir = TIMER_COUNT_UP,
  .intr_type = TIMER_INTR_LEVEL // interrupt is triggered upon alarm
};

void app_main(void)
{    
  dac_output_enable(DAC_CHANNEL_2); // enable output on the first DAC
  saw = new_Saw(100); //make a new sawtooth oscillator
    
  timer_init(TIMER_GROUP_0, TIMER_0, &config); // initialize the first timer of the first timer group with the configuration defined above
  timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0);
  timer_set_alarm_value(TIMER_GROUP_0, TIMER_0, 999); // trigger alarm when it counts to 1000 (should technically be 999 since we're starting from 0). But this is the last step in making a 40kHz clock.
  timer_enable_intr(TIMER_GROUP_0, TIMER_0); // enable interrupts for the first timer of the first timer group
  timer_isr_register(TIMER_GROUP_0, TIMER_0, &interrupt_for_sample, NULL, 0, &interrupt_handle); // register a timer interrupt for timer 0 of timer group 0 that will call interrupt_for_sample() with no arguments, no flags used to handle the interrupt, and a handle for the interrupt to do something with.
  
  timer_start(TIMER_GROUP_0, TIMER_0);

  //while (1) { vTaskDelay(1 / portTICK_PERIOD_MS / 10); }

  //while (1) { vTaskDelay(1000 / portTICK_PERIOD_MS); } // for some reason this stops rtos task scheduling from yelling at me
}
