#include <stdlib.h>
#include <yarp/os/all.h>
#include "yarp/Point.h"

using namespace yarp::os;

int main(int argc, char *argv[]) {
  Network yarp;
  BufferedPort<Point> port;
  if (!port.open("/yarp_pt_listener-#/pt_chatter")) {
    fprintf(stderr,"Failed to open port\n");
    exit(1);
  }

  while (true) {
    Point *pt = port.read();
    if (!pt) continue;
    printf("Read point %g %g %g\n", pt->x, pt->y, pt->z);
  }

  return 0;
}
