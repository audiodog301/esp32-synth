#include <stdio.h>
#include <assert.h>
#include "synth.h"

int main(int argc, char* argv[]) {
    //test that the constructor function makes the Saw properly
    printf("Testing saw contructor. . .\n");
    
    Saw* saw = new_Saw(440);

    assert(saw->frequency == 440);
    assert(saw->count == 0);
    assert(saw->val == 0.0);

    printf("Saw constructor works!\n");

    //test that saw_Set_Frequency() changes frequency properly, and ONLY changes frequency
    printf("Testing saw_Set_Frequency(). . .\n");
    saw_Set_Frequency(saw, 660);

    assert(saw->frequency == 660);
    assert(saw->count == 0);
    assert(saw->val == 0.0);

    printf("saw_Set_Frequency() works!\n");

    //test that when you ask for a new sample with a count of 0, your output is 255, your count increments by 1, and your value is 1.0
    printf("Testing saw_Next_Sample(). . .\n");
    
    unsigned char sample = saw_Next_Sample(saw, 40000);

    assert(sample == 255);
    assert(saw->count == 1);
    assert(saw->val = 1.0);

    printf("saw_Next_Sample() works!\n");

    return 0;
}