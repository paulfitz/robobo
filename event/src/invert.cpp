#include <stdio.h> 
#include <stdlib.h> 

#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <vector>
#include <map>

#include "Pattern.h"

#define SCALE 3

#define PATTERN_LENGTH 50


static double noise_level = 0.0;

//#define VERBOSE

using namespace yarp::sig;
using namespace yarp::os;
using namespace std;

class Summary {
public:
  double x, y;
  double mag;

  Summary() {
    x = y = mag = 0;
  }
};


class Sim {
public:
  Patterns patterns;

  ImageOf<PixelFloat> view;
  ImageOf<PixelFloat> ref;
  ImageOf<PixelFloat> stamp;
  double angle;
  //double angle2;
  double v;
  //double vscale;
  float pattern[PATTERN_LENGTH];
  
  void setup(bool full = false);

  void draw(double t);

  void evaluate(double t);

  void run();

  void learn();
};

// t goes from 0 to 1
void Sim::draw(double t) {
  double dx = cos(angle);
  double dy = sin(angle);

  double offset = (t-0.5)*2*SCALE;
  //view.zero();
  double xx = SCALE/2.0 + offset*dx;
  double yy = SCALE/2.0 + offset*dy;

  IMGFOR(view,x,y) {
    double at = (x-xx)*dx + (y-yy)*dy;
    at *= -1;
    if (at<0) continue;
    if (noise_level>0.0001) {
      if (Random::uniform()<noise_level) {
	view(x,y) = 255*Random::uniform();
	continue;
      }
    }
    double r = 0;
    int a = (int)at;
    double f = at-a;
    r = (1-f)*pattern[a]+f*pattern[a+1];
    view(x,y) = r;
  }
}

void Sim::setup(bool full) {
  view.resize(SCALE,SCALE);
  ref.resize(SCALE,SCALE);
  stamp.resize(SCALE,SCALE);
  if (full) {
    view.zero();
    ref.zero();
    stamp.zero();
  }
  angle = 2*Random::uniform()*M_PI;
  //angle2 = 2*Random::uniform()*M_PI;
  //vscale = 2*Random::uniform()-1;
  v = 1;
  pattern[0] = 0;
  for (int i=1; i<PATTERN_LENGTH; i++) {
    pattern[i] = 255; //255*Random::uniform();

  }
}

void Sim::learn() {
  static int good = 0;
  static int bad = 0;

  if (SCALE!=3) {
    fprintf(stderr,"learning is set for 3x3 boxes\n");
    exit(1);
  }
  Pattern pat = patterns.evaluate(stamp,1,1);
  int index = pat.code;
  if (index==-1) return;

  static int ct = 0;
  static int top = 0;
  static map<int,Summary> seen;
  double now = Time::now();
  static double last_new = now;
  bool xmore = false;
  if (seen.find(index)==seen.end()) {
    ct++;
    seen[index] = Summary();
    xmore = true;
    last_new = now;
  }

  /*
  if (now-last_new>0.5) {
    noise_level = noise_level + 0.0000001*(1-noise_level);
  }
  */

  Summary& sum = seen[index];

  double angle2 = angle;
  //printf("angle %g %g\n", cos(angle2), sin(angle2));
  double xx = cos(angle2-pat.pattern_rotation);
  double yy = sin(angle2-pat.pattern_rotation);
  if (sum.mag>3 && sum.mag<20) {
    double px = pat.pattern_rx*sum.x - pat.pattern_ry*sum.y;
    double py = pat.pattern_ry*sum.x + pat.pattern_rx*sum.y;
    double m2 = sqrt(px*px+py*py);
    if (m2>0.001) {
      if ((px*cos(angle2)+py*sin(angle2))/m2<0.9) {
	bad++;
	//printf("CONTRARY good %d bad %d\n", good, bad);
      } else {
	good++;
      }
    }
  }
  
  sum.x += xx; //pat.pattern_rx*xx - pat.pattern_ry*yy;
  sum.y += yy; //pat.pattern_ry*xx + pat.pattern_rx*yy;
  sum.mag++;
  
  if (index>top) {
    top = index;
  }
  if (xmore) {
    printf("index (%d) %d   peak %d   noise %g  /// %d %d\n", ct, index, top,
	   noise_level, good, bad);
    double total = 0;
    for (int y=0; y<3; y++) {
      printf("  ");
      for (int x=0; x<3; x++) {
	printf("[%d]%g ", y*3+x, stamp(x,y));
	total += stamp(x,y);
      }
      printf("\n\n");
    }
    /*
    printf("order: ");
    for (int k=0; k<9; k++) {
      printf("%d ", order[k]);
    }
    printf("\n\n");
    */

  }

  static int periodic = 0;
  if (periodic%1000000==0) {
    ImageOf<PixelFloat> tag;
    int h = Patterns::getTop();
    int w = 4;
    tag.resize(w,h);
    tag.zero();
    for (int i=0; i<h; i++) {
      tag(0,i) = i;
      if (seen.find(i)==seen.end()) continue;
      Summary& sum = seen[i];
      tag(1,i) = sum.x;
      tag(2,i) = sum.y;
      tag(3,i) = sum.mag;
    }
    printf("*** WRITING %g ***\n", noise_level);
    file::write(tag,"log.txt");
    printf("*** DONE WRITING %g ***\n", noise_level);
  }
  periodic++;

}

void Sim::evaluate(double t) {
  IMGFOR(ref,x,y) {
    PixelFloat& v1 = ref(x,y);
    PixelFloat& v2 = view(x,y);
    if (v2>v1*1.1 || v2<v1*0.9) {
      v1 = v2;
      stamp(x,y) = t - Random::uniform()*0.0001;
    }
  }
}

void Sim::run() {
  double t = 0;

  int round = 0;
  setup(true);
  while (true) {
    //printf("Round %d\n", round);
    setup(false);
    int N = int(10+10*Random::uniform());
    N *= 4;
    for (int i=0; i<=N; i++) {
      if (Random::uniform()<0.2/N) {
	// occasionally stop halfway
	break;
      }
      double t0 = ((double)i)/N;
      t0 = ((t0-0.5)*3);
      draw(t0);
      evaluate(t+t0);
      learn();
      {
	static int idx = 0;
	if (idx<10) {
	  char buf[256];
	  ImageOf<PixelRgb> out;
	  out.copy(view,300,300);
	  sprintf(buf,"%06d.ppm",idx);
	  file::write(out,buf);
	  idx++;
	}
      }
    }
    t += 1;
    round++;
  }
}

void tests() {
  double x0 = 0.1, y0 = 0.2;
  double a = 1;
  double x1 = cos(a)*x0 - sin(a)*y0;
  double y1 = sin(a)*x0 + cos(a)*y0;
  double x2 = cos(a)*x1 + sin(a)*y1;
  double y2 = -sin(a)*x1 + cos(a)*y1;
  printf("%g %g / %g %g / %g %g\n",
	 x0, y0, x1, y1, x2, y2);


  Patterns pat;

  ImageOf<PixelFloat> img;
  img.resize(3,3);
  {
    for (int y=0; y<3; y++) {
      for (int x=0; x<3; x++) {
	img(x,y) = y*3+x;
      } 
    }
    Pattern p = pat.evaluate(img,1,1);
    printf("code %d // %g %g\n", p.code, p.pattern_rx, p.pattern_ry);
  }
  {
    for (int y=0; y<3; y++) {
      for (int x=0; x<3; x++) {
	img(x,y) = x*3+(2-y);
      } 
    }
    Pattern p = pat.evaluate(img,1,1);
    printf("code %d // %g %g\n", p.code, p.pattern_rx, p.pattern_ry);
  }

}


int main(int argc, char *argv[]) {
  //tests();
  //return 0;

  Sim sim;
  sim.run();
  return 0;
}
