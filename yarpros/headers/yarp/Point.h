// This is an automatically generated file.
// Generated from this Point.msg definition:
//   # This contains the position of a point in free space
//   float64 x
//   float64 y
//   float64 z
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARPMSG_TYPE_Point
#define YARPMSG_TYPE_Point

#include <string>
#include <vector>
#include <yarp/os/Portable.h>
#include <yarp/os/ConstString.h>
#include <yarp/os/NetInt32.h>
#include <yarp/os/NetInt64.h>
#include <yarp/os/NetFloat32.h>
#include <yarp/os/NetFloat64.h>

class Point : public yarp::os::Portable {
public:
  yarp::os::ConstString getTypeName() const {
    return "Point";
  }

  yarp::os::NetFloat64 x;
  yarp::os::NetFloat64 y;
  yarp::os::NetFloat64 z;

  bool read(yarp::os::ConnectionReader& connection) {
    // *** x ***
    x = connection.expectDouble();

    // *** y ***
    y = connection.expectDouble();

    // *** z ***
    z = connection.expectDouble();
    return !connection.isError();
  }

  bool write(yarp::os::ConnectionWriter& connection) {
    // *** x ***
    connection.appendDouble(x);

    // *** y ***
    connection.appendDouble(y);

    // *** z ***
    connection.appendDouble(z);
    return !connection.isError();
  }
};

#endif
