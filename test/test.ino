#include "square_wave_player.c"

double note_freqs[13] =  {B4   ,Gb5,Gb5,E5 ,D5 ,Db5,Db5  ,D5 ,B4      ,B5,LA5,LA4,B4};
int note_lens[13] = {N4+N8,N8 ,N2 ,N8 ,N8, N8 ,N8+N4,N8 ,N8+N2+N4,N8,N8+N2+N4,N8,N8};

void led_on(int,int);
void led_off();
void draw();

void setup() {     
  //initalize sound module
  swp_init(13,100,note_freqs,note_lens,13);
  pinMode(13, OUTPUT);
  
  //x-coords
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  //y-coords
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  
}

// the loop routine runs over and over again forever:
void loop() {
  swp_play(&draw); 
}

void led_on(int x, int y)
{
  led_off();
  int led_x = x + 1;
  int led_y;
  switch(y)
  {
     case 1:led_y = A2;break;
     case 2:led_y = A3;break;
     case 3:led_y = A4;break;
     case 4:led_y = A5;break;
  }
  digitalWrite(led_y,HIGH);
  digitalWrite(led_x,LOW);
}
void led_off()
{
  digitalWrite(A2,LOW);
  digitalWrite(A3,LOW);
  digitalWrite(A4,LOW);
  digitalWrite(A5,LOW);

  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
}

void draw()
{
 for(int x = 1; x != 5; x++)
  {
    for(int y = 1; y !=5; y++)
    {
      led_on(x,y);
    }
  }
  led_off();
}



