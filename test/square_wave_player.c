// See that A is renamed LA to avoid conflict with arduino pin names
#define REST 0
#define C2  65.41
#define Db2 69.30
#define D2  73.42
#define Eb2 77.78
#define E2  82.41
#define F2  87.31
#define Gb2 92.50
#define G2  98.00
#define Ab2 103.83
#define LA2 110.00
#define Bb2 116.54
#define B2  123.47
#define C3  130.81
#define Db3 138.59
#define D3  146.83
#define Eb3 155.56
#define E3  164.81
#define F3  174.61
#define Gb3 185.00
#define G3  196.00
#define Ab3 207.65
#define LA3 220.00
#define Bb3 233.08
#define B3  246.94
#define C4  261.63
#define Db4 277.18
#define D4  293.66
#define Eb4 311.13
#define E4  329.63
#define F4  349.23
#define Gb4 369.99
#define G4  392.00
#define Ab4 415.30
#define LA4 440.00
#define Bb4 466.16
#define B4  493.88
#define C5  523.25
#define Db5 554.37
#define D5  587.33
#define Eb5 622.25
#define E5  659.26
#define F5  698.46
#define Gb5 739.99
#define G5  783.99
#define Ab5 830.61
#define LA5 880.00
#define Bb5 932.33
#define B5  987.77
#define C6  1046.50
#define Db6 1108.73
#define D6  1174.66
#define Eb6 1244.51
#define E6  1318.51
#define F6  1396.91
#define Gb6 1479.98
#define G6  1567.98
#define Ab6 1661.22
#define LA6 1760.00
#define Bb6 1864.66
#define B6  1975.53
#define C7  2093.00
#define Db7 2217.46
#define D7  2349.32
#define Eb7 2489.02
#define E7  2637.02
#define F7  2793.83
#define Gb7 2959.96
#define G7  3135.96
#define Ab7 3322.44
#define LA7 3520.01
#define Bb7 3729.31
#define B7  3951.07
#define C8  4186.01

// Note lengths
#define N32 1
#define N16 2
#define N8 4 
#define N4 8
#define N2 16
#define N1 32

struct square_wave_player
{
  // The pin that the buzzer is on
  int pin;
  // Length of a thirty second note, in milliseconds
  int thirty_second_note_length;
  // Points to the current note being played
  int note_ptr;
  // Amount of 32nd notes left in the note.
  int note_length_left;
  // Pointer to a list of note frequencies
  double* note_freqs;
  // How long to play each note
  int* note_lengths;
  // Count of all notes
  int note_count;
} swp;

void swp_init(int pin, int bpm, double* note_freqs, int* note_lengths, int note_list_length)
{
  swp.pin = pin;
  //This represents the length of the 32nd note, which also signifies the length of a frame.
  swp.thirty_second_note_length = (7500)/bpm;
  //at a tempo of 120 bpm, each frame is 62.5 ms = 16 fps 
  swp.note_ptr = -1;
  swp.note_length_left = 1;
  swp.note_freqs = note_freqs;
  swp.note_lengths = note_lengths;
  swp.note_count = note_list_length;
}

void swp_play(void (*functionPtr)()) 
{
  // A whole cycle has passed
  swp.note_length_left--;
  if(swp.note_length_left == 0)
  {
    swp.note_ptr = (swp.note_ptr + 1) % swp.note_count;
    noTone(swp.pin);
    swp.note_length_left = swp.note_lengths[swp.note_ptr];
    tone(swp.pin,swp.note_freqs[swp.note_ptr]); 
  }
  unsigned long start_update_time = millis();
  while(start_update_time + ((unsigned long)swp.thirty_second_note_length) > millis() )
  {
    (*functionPtr)();
    delay(1);
  }
}

