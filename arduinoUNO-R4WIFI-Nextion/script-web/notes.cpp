#include "notes.h"
#include "pitches.h"
#include <Arduino.h>

const int superMario_melody[]= {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
const short int superMario_noteDurations[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  // parte B
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12
};

const int melodyGameUp[] = {
  NOTE_C5, NOTE_E5, NOTE_G5, NOTE_C6
}; 
const short int noteDurationsGameUp[] = {
  200, 200, 200, 400
};

const int melodyLevelUp[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_G5, NOTE_C6
};
const short int noteDurationsLevelUp[] = {12, 12, 12, 12, 12};

const int melodyLevelDown[] = { NOTE_C6, NOTE_G5, NOTE_E5, NOTE_C5 };
const short int noteDurationsLevelDown[] = { 12, 12, 12, 12 };

const int melodyAlertLong[] = { NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4 };
const short int durationsAlertLong[] = { 12, 12, 12, 12 };

const int melodyAlertShort[] = { NOTE_C5, NOTE_C5 };
const short int durationsAlertShort[] = { 12, 12 };

const int conan_melody[] = {
  NOTE_E5, NOTE_G5, NOTE_A5, 0,
  NOTE_E5, NOTE_G5, NOTE_A5, 0,
  NOTE_E5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6, 0,
  NOTE_B5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_E5, 0,

  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, 0,
  NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, 0,
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, 0,
  NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6, 0,

  NOTE_B5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, 0,
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, 0,
  NOTE_E5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6, NOTE_D6, 0
};
const short int conan_noteDurations[] = {
  8, 8, 4, 8,
  8, 8, 4, 8,
  8, 8, 8, 8, 2, 8,
  4, 8, 8, 8, 4, 8,

  8, 8, 8, 4, 8,
  4, 8, 8, 4, 8,
  8, 8, 8, 4, 8,
  8, 8, 8, 2, 8,

  8, 8, 8, 8, 4, 8,
  8, 8, 8, 8, 2, 8,
  8, 8, 8, 8, 4, 2, 8
};

const int pokemon_melody[] = {
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_C5, NOTE_E5, NOTE_G5, 0,
  NOTE_G4, 0, NOTE_C5, 0, NOTE_G4, 0, NOTE_E4, 0,

  NOTE_A4, NOTE_A4, NOTE_A4, NOTE_F4, NOTE_A4, NOTE_C5, 0,
  NOTE_C4, 0, NOTE_F4, 0, NOTE_C4, 0, NOTE_A3, 0,

  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_B4, 0,
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, 0,
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_C5, NOTE_E5, NOTE_G5, 0,
  NOTE_G4, 0, NOTE_C5, 0, NOTE_G4, 0, NOTE_E4, 0
};
const short int pokemon_noteDurations[] = {
  8, 8, 8, 8, 8, 4, 8,
  2, 8, 4, 8, 4, 8, 4, 8,

  8, 8, 8, 8, 8, 4, 8,
  2, 8, 4, 8, 4, 8, 4, 8,

  8, 8, 8, 8, 8, 4, 8,
  8, 8, 8, 2, 8,
  8, 8, 8, 8, 8, 4, 8,
  2, 8, 4, 8, 4, 8, 4, 8
};

const int dragonball_melody[] = {
  NOTE_G4, NOTE_C5, NOTE_E5, NOTE_G5, NOTE_A5, 0,
  NOTE_A5, NOTE_A5, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_G4, 0,

  NOTE_G4, NOTE_C5, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6, 0,
  NOTE_C6, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_G4, 0,

  NOTE_G4, NOTE_C5, NOTE_E5, NOTE_G5, NOTE_A5, 0,
  NOTE_A5, NOTE_A5, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_G4, 0,
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, 0,
  NOTE_A5, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_E6, NOTE_C6, 0
};
const short int dragonball_noteDurations[] = {
  8, 8, 8, 8, 4, 8,
  8, 8, 8, 8, 4, 2, 8,

  8, 8, 8, 8, 8, 8, 4, 8,
  4, 8, 8, 8, 8, 4, 2, 8,

  8, 8, 8, 8, 4, 8,
  8, 8, 8, 8, 4, 2, 8,
  8, 8, 8, 8, 4, 8,
  8, 8, 8, 8, 4, 2, 8
};


Song superMario = {superMario_melody,superMario_noteDurations, sizeof(superMario_melody) / sizeof(superMario_melody[0])};
Song gameUp = {melodyGameUp, noteDurationsGameUp,sizeof(melodyGameUp) / sizeof(melodyGameUp[0])};
Song levelUp = {melodyLevelUp, noteDurationsLevelUp, sizeof(melodyLevelUp) / sizeof(melodyLevelUp[0])};
Song levelDown = {melodyLevelDown, noteDurationsLevelDown,sizeof(melodyLevelDown) / sizeof(melodyLevelDown[0])};
Song alertLong = {melodyAlertLong, durationsAlertLong,sizeof(melodyAlertLong) / sizeof(melodyAlertLong[0])};
Song alertShort = {melodyAlertShort, durationsAlertShort,sizeof(melodyAlertShort) / sizeof(melodyAlertShort[0])};
Song conan = {conan_melody, conan_noteDurations,sizeof(conan_melody) / sizeof(conan_melody[0])};
Song pokemon = {pokemon_melody, pokemon_noteDurations,sizeof(pokemon_melody) / sizeof(pokemon_melody[0])};
Song dragonball = {dragonball_melody, dragonball_noteDurations,sizeof(dragonball_melody) / sizeof(dragonball_melody[0])};


void playSong(int buzz, Song song) {
  Serial.println("Playing music!!!");

  for (int thisNote = 0; thisNote < song.notes; thisNote++) {
    int duration = 1000 / song.noteDurations[thisNote];
    int note = song.melody[thisNote];

    if (note > 0) tone(buzz, note, duration);

    delay(duration * 1.30);
    noTone(buzz);
  }
}
