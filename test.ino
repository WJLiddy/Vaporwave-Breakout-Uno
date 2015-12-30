#include "square_wave_player.c"

double note_freqs[13] =  {B4   ,Gb5,Gb5,E5 ,D5 ,Db5,Db5  ,D5 ,B4      ,B5,LA5,LA4,B4};
int note_lens[13] = {N4+N8,N8 ,N2 ,N8 ,N8, N8 ,N8+N4,N8 ,N8+N2+N4,N8,N8+N2+N4,N8,N8};

void setup() {     
  swp_init(7,100,note_freqs,note_lens,13);
  pinMode(7, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  swp_play();
}
