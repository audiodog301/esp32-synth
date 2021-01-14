#include <stdio.h>
#include "synth.h"

int main(int argc, char* argv[]) {
    int step_count = 999;
    
    Sequencer* sequencer = new_Sequencer(step_count);
    
    printf("%i\n", sequencer->steps[0]);
    printf("%i\n", sequencer->steps[step_count-1]);

    free(sequencer);
    
    return 0;
}