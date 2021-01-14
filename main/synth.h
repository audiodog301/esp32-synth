#include <stdlib.h>

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
