#include <stdio.h>
#include <assert.h>
#include "synth.h"

int main(int argc, char* argv[]) {
    //test that midi_To_Frequency() does the right math
    printf("Testing midi_To_Frequency(). . .\n");
    
    int frequency = midi_To_Frequency(69);
    
    assert(frequency == 440);

    printf("midi_To_Frequency() works!\n\n");
    
    //test that the constructor function makes the Saw properly
    printf("Testing Saw contructor. . .\n");
    
    Saw* saw = new_Saw(440);

    assert(saw->frequency == 440);
    assert(saw->count == 0);
    assert(saw->val == 0.0);

    printf("Saw constructor works!\n\n");

    //test that saw_Set_Frequency() changes frequency properly, and ONLY changes frequency
    printf("Testing saw_Set_Frequency(). . .\n");
    
    saw_Set_Frequency(saw, 660);

    assert(saw->frequency == 660);
    assert(saw->count == 0);
    assert(saw->val == 0.0);

    printf("saw_Set_Frequency() works!\n\n");

    //test that when you ask for a new sample with a count of 0, your output is 255, your count increments by 1, and your value is 1.0
    printf("Testing saw_Next_Sample(). . .\n");
    
    unsigned char sample = saw_Next_Sample(saw, 40000);

    assert(sample == 255);
    assert(saw->count == 1);
    assert(saw->val = 1.0);

    printf("saw_Next_Sample() works!\n\n");

    free(saw);

    //test that the constructor function makes the Sequencer properly.
    printf("Testing Sequencer constructor. . .\n");
    
    Sequencer* sequencer = new_Sequencer(16, 120);

    //test that constructor function properly populates new Sequencer
    assert(sequencer->bpm == 120);
    assert(sequencer->step_count == 16);
    assert(sequencer->where == 0);
    assert(sequencer->count == 0);

    printf("Sequencer contructor works!\n");

    printf("Testing other sequencer functions. . .\n");
    for (int i = 0; i < 16; i++) {
        assert(sequencer->steps[i] == 500); //tests that steps are filled with 500 - no note
    }

    for (int i = 0; i < 16; i++) {
        assert(sequencer_Get_Note(sequencer, i) == 500); //tests that sequencer_Get_Note() works
    }

    for (int i = 0; i < 16; i++) {
        sequencer_Set_Note(sequencer, i, 127);
        assert(sequencer_Get_Note(sequencer, i) == 127); //tests that sequencer_Set_Note() works
    }

    int note = sequencer_Next_Note(sequencer, 40000);
    note = sequencer_Next_Note(sequencer, 40000);

    assert(note == 127); //test that sequencer_Next_Note() gets the note properly

    //test that the sequencer incremente properly
    //assert(sequencer->count == 1);
    printf("%i\n", sequencer->count);

    free(sequencer);

    return 0;
}