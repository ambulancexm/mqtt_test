#include "pitches.h"

int inPin = D1;

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};
 

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {  4, 8, 8, 4,4,4,4,4 };

void play(){
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < sizeof(melody)/sizeof(int); thisNote++) {
    int noteDuration = 1000/noteDurations[thisNote];
    tone(inPin, melody[thisNote],noteDuration);
    
    int pauseBetweenNotes = noteDuration * 1.10;
    delay(pauseBetweenNotes);
  }
}
