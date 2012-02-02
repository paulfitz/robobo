#include <stdlib.h>
#include <yarp/os/all.h>
#include "yarp/Point.h"

using namespace yarp::os;

int main(int argc, char *argv[]) {
  Network yarp;
  BufferedPort<Point> port;
  if (!port.open("/yarp_pt_talker+#/pt_chatter")) {
    fprintf(stderr,"Failed to open port\n");
    exit(1);
  }

  while (true) {
    Point& pt = port.prepare();
    pt.x = 10;
    pt.y = 20;
    pt.z = 30;
    printf("Wrote point %g %g %g\n", pt.x, pt.y, pt.z);
    port.write();
    Time::delay(0.5);
  }

  return 0;
}
