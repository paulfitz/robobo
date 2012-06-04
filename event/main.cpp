#include <stdio.h>
#include <stdlib.h>

#include <yarp/os/all.h>
#include <yarp/sig/all.h>

#include <vector>

#define USE_PORT 1

using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::sig;
using namespace std;

class Point {
public:
  int x, y;
};

class Flicker {
private:
  int w;
  int h;
  ImageOf<PixelFloat> accum;
  double last_out_time;
  BufferedPort<ImageOf<PixelRgb> > port;
  
public:
  Flicker(int w, int h) {
    this->w = w;
    this->h = h;
    accum.resize(w,h);
    accum.zero();
    last_out_time = -100;
    if (USE_PORT) {
      port.open("/flicker");
    }
  }

  void apply(double t, int x, int y, bool polarity, bool cam);
};

void Flicker::apply(double t, int x, int y, bool polarity, bool cam) {
  if (cam!=0) return;  // cam 1 seems dodgy?
  accum(x,y)++;
  if (t>last_out_time+0.0002) {
    last_out_time = t;
    ImageOf<PixelRgb> view;
    view.resize(accum);
    view.zero();
    IMGFOR(view,x,y) {
      int v = int(accum(x,y)+0.5);
      if (v>0) {
	double theta = v;
	double dx = cos(theta);
	double dy = sin(theta);
	view(x,y) = PixelRgb((int)(dx*120)+128,(int)(dy*120)+128,
			     (int)((dx+dy)*62)+128);
      }
    }
    /*
    ImageOf<PixelFloat> norm;
    norm = accum;
    double top = 0.001;
    IMGFOR(norm,x,y) {
      if (norm(x,y)>top) top = norm(x,y);
    }
    IMGFOR(norm,x,y) {
      norm(x,y) *= (255.0/top);
      accum(x,y) *= 0.99;
    }
    view.copy(norm);
    */
    if (!USE_PORT) {
      static int ct = 0;
      char buf[256];
      sprintf(buf,"view%06d.ppm",ct);
      ct++;
      file::write(view,buf);
      if (ct>640) exit(0);
    } else {
      static double now = 0;
      Time::delay((t-now)*500);
      now = t;
      port.prepare() = view;
      port.write();
    }
  }
}

int main(int argc, char *argv[]) {
  Network yarp;

  if (argc!=2) return 1;
  const char *fname = argv[1];
  
  FILE *fin = fopen(fname,"r");
  if (!fin) return 1;

  Flicker flick(128,128);

  long int ot = -1;
  long int accum_time = 0;
  long int prev_time = -1;
  while (!feof(fin)) {
    long int timestamp = 0;
    unsigned long int code = 0;
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
      ot = (long int)code;
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

    unsigned long int ocode = code;

    code = code & 0xffff;

    //code = ((code & 0xff)<<8) | ((code & 0xff00)>>8);

    int polarity = (int)(code & 1);
    code = code >> 1;
    int x = (int)(code & 0x7f);
    code = code >> 7;
    int y = (int)(code & 0x7f);
    code = code >> 7;
    int cam = (int)(code & 1);
    code = code >> 1;

    double now = accum_time*0.000001;
    printf(">>> %6lx / %5lx => %010x  %020.6f : %s %03d %03d %s\n", 
	   timestamp, ocode,
	   accum_time,
	   now,
	   polarity?"ON ":"OFF", x, y,
	   cam?"RIGHT":"LEFT");
    flick.apply(now,x,y,polarity,cam);
  }

  fclose(fin);
  fin = NULL;

  return 0;
}
