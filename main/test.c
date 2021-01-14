#include <stdio.h>
#include <time.h>
#include "synth.h"

//really stupid delay function
void delay(int number_of_seconds) { 
    // Converting time into milli_seconds 
    int milliseconds = 1000 * number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milliseconds) 
        ; 
} 

int main(int argc, char* argv[]) {
    int c = 16;
    
    Sequencer* sequencer = new_Sequencer(c, 120);

    for (int i = 0; i < sequencer->step_count; i += 1){
        sequencer_Set_Note(sequencer, i, i);
    }

    while (1) { 
        int note = sequencer_Next_Note(sequencer, 100);

        if (note != -1) {
            printf("%i\n", note);
        }
        
        delay(100);
    }

    free(sequencer);
    
    return 0;
}