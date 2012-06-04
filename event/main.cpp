#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc!=2) return 1;
  const char *fname = argv[1];
  
  FILE *fin = fopen(fname,"r");
  if (!fin) return 1;

  long int ot = -1;
  long int accum_time = 0;
  long int prev_time = -1;
  while (!feof(fin)) {
    long int timestamp = 0;
    long int code = 0;
    if (ot<0) {
      fscanf(fin,"%lx",&timestamp);
    } else {
      timestamp = ot;
      ot = -1;
    }
    if (timestamp==0) break;
    timestamp = timestamp & 0x00ffffffL;
    fscanf(fin,"%lx",&code);
    //printf(">>> %lx / %lx\n", timestamp, code);
    if (code>0x1FFFF) {
      printf("(format glitch)\n");
      ot = code;
      continue;
    }

    if (prev_time<0) {
      prev_time = timestamp;
    }
    while (timestamp<prev_time) {
      // There are wraparounds, but also:
      // the timestamp seems glitchy, or recordings or glitchy, or something.
      prev_time -= 0x1000;
    }
    long int diff_time = timestamp-prev_time;
    accum_time += diff_time;
    prev_time = timestamp;

    long int ocode = code;

    int polarity = (int)(code % 2);
    code = code >> 1;
    int x = (int)(code%0x7f);
    code = code >> 7;
    int y = (int)(code%0x7f);
    code = code >> 7;
    int cam = (int)(code%2);

    double now = accum_time*0.000001;
    printf(">>> %6lx / %5lx => %010x  %020.6f : %s %03d %03d\n", 
	   timestamp, ocode,
	   accum_time,
	   now,
	   polarity?"ON ":"OFF", x, y);
  }

  fclose(fin);
  fin = NULL;

  return 0;
}
