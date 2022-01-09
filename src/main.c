#include <SDL2/SDL.h>

#include <stdbool.h> 
#include <stdint.h>
#include <stdio.h> 
#include <math.h>

// https://wiki.osdev.org/PC_Speaker

static int currentFrequency = 0;
static SDL_AudioSpec spec = {0};

#define SAMPLE_RATE 44100 

static double squareWave(double time, int freq, int squareness) {
  double val = sin(time * freq);
  double harmonic = 3;
  for (int i = 0; i <= squareness; i++) {
    val += sin(time * freq * harmonic) / harmonic; 
    harmonic += 2;
  }
  return val;
}

static uint64_t sample_nr = 0;
static void audio_generate(void *userdata, Uint8* stream, int len) {
  Sint16* buffer = (Sint16*) stream;
  len /= 2;
  
  for(uint64_t i = 0; i < len; i++, sample_nr++) {
    double time = (double) sample_nr / (double) SAMPLE_RATE;
    buffer[i] = (Sint16) (squareWave(time, currentFrequency, 20) * INT16_MAX); 
    
    sample_nr = sample_nr % SAMPLE_RATE;
  } 
}

int main() {
  // We only want the audio subsystem
  SDL_Init(SDL_INIT_AUDIO);
  
  spec.callback = audio_generate;
  spec.format = AUDIO_S16SYS;
  spec.channels = 1;
  spec.freq = SAMPLE_RATE;
  
  // Require some tweaking???
  spec.samples = 2048;
  
  if (SDL_OpenAudio(&spec, NULL) != 0) 
    goto cleanup_fail;
  
  SDL_PauseAudio(0);
  
  // Loop until EOF received
  while (!feof(stdin)) {
    int divider = 0;
    int res = scanf("%d", &divider);
    
    if (res > 0 && res != EOF) {
      if (divider <= 65535 && divider >= 0) {
        // https://wiki.osdev.org/Programmable_Interval_Timer#The_Oscillator
        // 1193182 Hz is oscillator frequency that used by PIT
        if (divider == 0) {
          currentFrequency = 1193182 / 65536;
        } else {
          currentFrequency = 1193182 / divider;
        }
      }
    }
    
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    if (ch == EOF) break;
  };
  
  goto cleanup;
  
  cleanup_fail:
  fprintf(stderr, "Can't open audio: %s\n", SDL_GetError());
  
  cleanup:
  SDL_CloseAudio();
  SDL_Quit();
}

