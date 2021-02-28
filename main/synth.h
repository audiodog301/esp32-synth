#include <stdlib.h>
#include <math.h>

//return a value in hertz when given a note
int midi_To_Frequency(int midi) {
  return (pow(2, ((midi - 69) / 12)) * 440);
}

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
  
  if (self->count == 0) { //if phase is 0
    self->val = 1.0; //then set the value to be 1 (the spike at the beginning of the wave)
  } else {
    self->val -= 1.0 / (sample_rate / self->frequency); //otherwise ramp down
  }
  
  //keep track of how many samples have passed. reset once phase is 0 again.
  if (self->count >= (int) (sample_rate / self->frequency)) {
    self->count = 0;
  } else {
    self->count += 1;
  }

  return (unsigned char) (self->val * 255); //return the value, but mapped to 0-255 instead of 0-1
}

//define a Sequencer type to hold some data
typedef struct Sequencer_ {
    int step_count;
    int where;
    int count;
    int bpm;
    int steps[];
} Sequencer;

//constructor function for a new Sequencer
Sequencer* new_Sequencer(int step_count, int bpm) {
    Sequencer* sequencer = malloc(4*sizeof(int) + step_count*sizeof(int)); //three integers plus the array of integers

    sequencer->step_count = step_count;
    sequencer->where = 0;
    sequencer->count = 0;
    sequencer->bpm = bpm;
    
    for (int i = 0; i < step_count; i++) {
        sequencer->steps[i] = 500;  //500 - no note
    }

    return sequencer;
}

//get the midi note value of an arbitrary step
int sequencer_Get_Note(Sequencer* sequencer, int index) {
    if (index > (sequencer->step_count - 1) || index < 0) {
        return -1; //return -1 if you ask for an out of bounds index
    } else {
        return sequencer->steps[index]; //otherwise return what is expected
    }
}

//set the midi note value of an arbitrary step
int sequencer_Set_Note(Sequencer* sequencer, int index, int val) {
    if (index > (sequencer->step_count - 1) || index < 0) {
        return -1; //return -1 if you ask for an out of bounds index
    } else {
       sequencer->steps[index] = val;
       return 0; //otherwise set the value and return 0 for success
    }
}

//get a new notes
int sequencer_Next_Note(Sequencer* sequencer, int sample_rate) {
    sequencer->count = sequencer->count + 1;
    printf("incremented sequencer count\n");
    
    if (sequencer->where > (sequencer->step_count - 1)) {
            sequencer->where = 0;
        }
    
    if (sequencer->count > sequencer->bpm/60/sample_rate) {
        int note = sequencer_Get_Note(sequencer, sequencer->where); //get the next note
        sequencer->where += 1;
        sequencer->count = 0;
        return note;
    } else {
        return -1; //return -1 if no new note yet
    }
}