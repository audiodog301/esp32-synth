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

typedef enum Midi_Note_or_Frequency_ { MIDI_NOTE, FREQUENCY } Midi_Note_or_Frequency;

typedef struct Note_ {
  Midi_Note_or_Frequency midi_note_or_frequency;
  int val;
} Note;

Note* new_Note(Midi_Note_or_Frequency midi_note_or_frequency, int val) {
  Note* new = malloc(sizeof(Note));

  new->midi_note_or_frequency = midi_note_or_frequency;
  new->val = val;

  return new;
}

struct Step {
  Note *note;
  struct Step *next;
};

struct Step* new_Step(Note *note, struct Step *next) {
  struct Step* new = malloc(sizeof(struct Step));
  
  new->note = note;
  new->next = next;

  return new;

}

typedef struct Sequencer_ {
  int length;
  int count;
  struct Step* current;
  int period;
  struct Step *steps[];
} Sequencer;

Sequencer* new_Sequencer(int length, int period) {
  Sequencer* new = malloc(sizeof(Sequencer) + (sizeof(struct Step)*length));

  for (int i = 0; i < length; i++) {
    new->steps[i] = new_Step(new_Note(FREQUENCY, -1), NULL);
  }

  for (int i = 0; i < length; i++) {
    new->steps[i]->next = new->steps[(i + 1)%length];
  }

  new->length = length;
  new->count = 0;
  new->current = new->steps[1];
  new->period = period;

  return new;
}

int sequencer_Next_Note(Sequencer* self) {
  int freq = -1;
  
  if (self->count > self->period) {
    
    if (self->current->note->midi_note_or_frequency == MIDI_NOTE) {
      freq = midi_To_Frequency(self->current->note->val);
      //freq = 5; //make this trivial, even tho it shouldnt be called in the first place even.
    } else {
      freq = self->current->note->val;
    }
    
    self->current = self->current->next;
    self->count = 0;
  } else {
    freq = -1;
  }
  
  self->count += 1;

  return freq;
}