
#include "modules/buzzer.h"
#include "Arduino.h"
#include "config/configuration.h"
#include "modules/pitches.h"

int start_melody_notes[] = {

    NOTE_C6, NOTE_F6, NOTE_G6, NOTE_B6
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int start_melody_durations[] = {

    4, 4, 4, 4
};

void button_click_beep()
{
    tone(BUZZER_PIN, 523, 50);
}

void error_beep()
{
    tone(BUZZER_PIN, 600, 100);
    tone(BUZZER_PIN, 900, 100);
    tone(BUZZER_PIN, 1000, 1000);
}

void start_melody()
{
    for (int thisNote = 0; thisNote < 8; thisNote++) {

        int noteDuration = 1000 / start_melody_durations[thisNote];

        tone(BUZZER_PIN, start_melody_notes[thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;

        delay(pauseBetweenNotes);

        noTone(BUZZER_PIN);
    }
}
