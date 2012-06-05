#include <stdio.h>
#include <stdlib.h>

#include <yarp/os/all.h>
#include <yarp/sig/all.h>

#include <yarp/sig/IntegralImage.h>

#include <vector>

#define USE_PORT 1
#define SHOW_INPUT 0

using namespace yarp::os;
using namespace yarp::sig;
using namespace std;

class Flicker {
private:
  int w;
  int h;
  ImageOf<PixelFloat> tick;
  ImageOf<PixelFloat> accum_xx,accum_yy,accum_mag;
  ImageOf<PixelFloat> accum_xx_ii,accum_yy_ii,accum_mag_ii;
  ImageOf<PixelFloat> accum_xx_sum,accum_yy_sum,accum_mag_sum;
  double last_out_time;
  BufferedPort<ImageOf<PixelRgb> > arrows;
  
public:
  Flicker(int w, int h) {
    this->w = w;
    this->h = h;
    tick.resize(w,h);
    IMGFOR(tick,x,y) {
      tick(x,y) = -100;
    }
    last_out_time = -100;
    if (USE_PORT) {
      arrows.open("/flicker");
    }
  }

  void apply(double t, int x, int y, bool polarity, bool cam);
};


void Flicker::apply(double t, int x, int y, bool polarity, bool cam) {
  if (cam!=0) return;  // cam 1 seems dodgy?

  tick(x,y) = t;

  // That's it.  We are done!
  // All that remains is to emit an occasional visualization

  if (t>last_out_time+0.002) {
    last_out_time = t;
    tick.safePixel(-1,-1) = -1000;

    ImageOf<PixelRgb>& screen = arrows.prepare();
    int scale = 4;
    screen.resize(tick.width()*scale,tick.height()*scale);

    PixelRgb pback(255,255,255);
    PixelRgb pline(0,0,0);
    IMGFOR(screen,x,y) {
      screen(x,y) = pback;
      screen(x,y).r = 250-50*((double)y/screen.height());
    }
    
    int ww = tick.width();
    int hh = tick.height();

    accum_xx.resize(tick);
    accum_yy.resize(tick);
    accum_mag.resize(tick);
    IMGFOR(tick,x,y) {
      double xx = 0, yy = 0, mag = 0;
      double ref = tick(x,y);
      if (x>=1 && y>=1 && x<ww-1 && y<hh-1) {
	for (int qx=-1; qx<=1; qx++) {
	  for (int qy=-1; qy<=1; qy++) {
	    if (qx==0&&qy==0) continue;
	    double cmp = tick.safePixel(x+qx,y+qy);
	    if (cmp<0) continue;
	    double m = cmp-ref;
	    double fresh = t-ref;
	    if (t-cmp>fresh) fresh = t-cmp;
	    fresh = 0.05/(0.05+fresh);
	    xx += qx*m*fresh;
	    yy += qy*m*fresh;
	    mag += fabs(m);
	  }
	}
      }
      accum_xx(x,y) = xx;
      accum_yy(x,y) = yy;
      accum_mag(x,y) = mag;
    }

    IntegralImage ii;
    int dd = 2;
    ii.GetSum(accum_xx,accum_xx_ii,accum_xx_sum,dd);
    ii.GetSum(accum_yy,accum_yy_ii,accum_yy_sum,dd);
    ii.GetSum(accum_mag,accum_mag_ii,accum_mag_sum,dd);
    IMGFOR(tick,x,y) {
      double xx = accum_xx_sum(x,y);
      double yy = accum_yy_sum(x,y);
      double mag = accum_mag_sum(x,y);
      /*
      for (int dx=-dd; dx<=dd; dx++) {
	for (int dy=-dd; dy<=dd; dy++) {
	  xx += accum_xx(x+dx,y+dy);
	  yy += accum_yy(x+dx,y+dy);
	  mag += accum_mag(x+dx,y+dy);
	}
      }
      */
      if (mag>0.0001) {
	xx /= mag;
	yy /= mag;
	double bx = x*scale;
	double by = y*scale;
	double len = sqrt(xx*xx+yy*yy);
	xx /= len;
	yy /= len;
	len *= (dd*dd);
	if (len>1) len = 1;
	if (len>0.3) {
	  if (x%2==y%2) {
	  
	    PixelRgb pix(255*((xx>0)?xx:0),255*((xx<0)?-xx:0),255*fabs((yy>0)?yy:0));
	    double f = 2;
	    double cx = xx*scale*len*f;
	    double cy = yy*scale*len*f;
	    draw::addSegment(screen,pix,bx,by,bx+cx,by+cy);
	    draw::addSegment(screen,pix,bx+cx,by+cy,
			     bx+cx*0.8+cy*0.2,by+cy*0.8-cx*0.2);
	    draw::addSegment(screen,pix,bx+cx,by+cy,
			     bx+cx*0.8-cy*0.2,by+cy*0.8+cx*0.2);
	  }
	}
      }
    }

    static double now = 0;
    Time::delay(t-now);
    now = t;

    arrows.write();
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
    if (SHOW_INPUT) {
      printf(">>> %6lx / %5lx => %010x  %020.6f : %s %03d %03d %s\n", 
	     timestamp, ocode,
	     accum_time,
	     now,
	     polarity?"ON ":"OFF", x, y,
	     cam?"RIGHT":"LEFT");
    }
    flick.apply(now,x,y,polarity,cam);
  }

  fclose(fin);
  fin = NULL;

  return 0;
}
