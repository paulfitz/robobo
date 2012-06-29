#ifndef EVENT_PATTERN_INC
#define EVENT_PATTERN_INC

#include <yarp/sig/Image.h>

class Pattern {
public:
  int code;
  double x, y;
  double mag;
  
  double pattern_rotation;
  double pattern_rx;
  double pattern_ry;

  Pattern() {
    code = -1;
    x = y = mag = 0;
    pattern_rx = pattern_ry = pattern_rotation = 0;
  }
};


class Patterns {
private:
  yarp::sig::ImageOf<yarp::sig::PixelFloat> ref;
public:

  bool load(const char *fname);

  Pattern evaluate(yarp::sig::ImageOf<yarp::sig::PixelFloat>& stamp,
		   int cx, int cy);

  Pattern evaluate1(yarp::sig::ImageOf<yarp::sig::PixelFloat>& stamp,
		   int cx, int cy);

  Pattern evaluate2(yarp::sig::ImageOf<yarp::sig::PixelFloat>& stamp,
		    int cx, int cy);

  bool isValid() const { return ref.height()>0; }

  static int getTop();
};

#endif

