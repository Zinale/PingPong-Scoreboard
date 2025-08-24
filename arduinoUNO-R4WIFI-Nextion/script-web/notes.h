#ifndef NOTES_H
#define NOTES_H


struct Song {
  const int* melody;
  const short int* noteDurations;
  short int notes;
};

extern Song superMario; 
extern Song gameUp;
extern Song levelUp ;
extern Song levelDown ;
extern Song alertLong ;
extern Song alertShort ;
extern Song conan ;
extern Song pokemon ;
extern Song dragonball;

void playSong(int buzz, Song song);

#endif