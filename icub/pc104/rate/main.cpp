#include <stdio.h>
#include <yarp/os/all.h>
#include <yarp/os/Stamp.h>
#include <yarp/sig/all.h>

using namespace yarp::os;
using namespace yarp::sig;

int main() {
  Network yarp;
  BufferedPort<ImageOf<PixelRgb> > p1, p2;
  p1.open("/paulfitz/left");
  p2.open("/paulfitz/right");
  yarp.connect("/icub/cam/left","/paulfitz/left","udp");
  yarp.connect("/icub/cam/right","/paulfitz/right","udp");
  double start = Time::now();
  double last_left = 0;
  double last_right = 0;
  int lct = 0;
  int rct = 0;
  while (true) {
    ImageOf<PixelRgb> *img1 = p1.read(false);
    ImageOf<PixelRgb> *img2 = p2.read(false);
    double now = Time::now()-start;
    if (img1) {
      Stamp s1;
      p1.getEnvelope(s1);
      //printf("0 %020.020g %020.020g\n", now, s1.getTime());
      last_left = s1.getTime();
      lct++;
    }
    if (img2) {
      Stamp s2;
      p2.getEnvelope(s2);
      //printf("1 %020.020g %020.020g\n", now, s2.getTime());
      last_right = s2.getTime();
      rct++;
    }
    double delta = last_right-last_left;
    static double last_show = 0;
    if (now-last_show>1) {
      bool ok = false;
      if (delta>=0 && delta<0.015) {
	//printf("%g\n",delta);
	ok = true;
      } else if (delta<0 && delta>-0.015) {
	//printf("%g\n",-delta);      
	//delta *= -1;
	ok = true;
      }
      if (ok) {
	printf("%g %g  (%d/%d)\n", now, delta, lct, rct);
	lct = 0;
	rct = 0;
	fflush(stdout);
	last_show = now;
      }
    }
    if (!(img1||img2)) {
      //printf("...\n");
    }
    Time::delay(0.001);
  }
}
