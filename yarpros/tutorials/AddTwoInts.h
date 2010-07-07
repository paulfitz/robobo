/* Auto-generated by genmsg_cpp for file AddTwoInts.srv */
#ifndef HALLO_SERVICE_ADDTWOINTS_H
#define HALLO_SERVICE_ADDTWOINTS_H
#include <string>
#include <vector>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/message.h"
#include "ros/time.h"

#include "ros/service_traits.h"




namespace hallo
{
template <class ContainerAllocator>
struct AddTwoIntsRequest_ : public ros::Message
{
  typedef AddTwoIntsRequest_<ContainerAllocator> Type;

  AddTwoIntsRequest_()
  : a(0)
  , b(0)
  {
  }

  AddTwoIntsRequest_(const ContainerAllocator& _alloc)
  : a(0)
  , b(0)
  {
  }

  typedef int64_t _a_type;
  int64_t a;

  typedef int64_t _b_type;
  int64_t b;


private:
  static const char* __s_getDataType_() { return "hallo/AddTwoIntsRequest"; }
public:
  ROSCPP_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROSCPP_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "36d09b846be0b371c5f190354dd3153e"; }
public:
  ROSCPP_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROSCPP_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getServerMD5Sum_() { return "6a2e34150c00229791cc89ff309fff21"; }
public:
  ROSCPP_DEPRECATED static const std::string __s_getServerMD5Sum() { return __s_getServerMD5Sum_(); }

  ROSCPP_DEPRECATED const std::string __getServerMD5Sum() const { return __s_getServerMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "int64 a\n\
int64 b\n\
\n\
"; }
public:
  ROSCPP_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROSCPP_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROSCPP_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, a);
    ros::serialization::serialize(stream, b);
    return stream.getData();
  }

  ROSCPP_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, a);
    ros::serialization::deserialize(stream, b);
    return stream.getData();
  }

  ROSCPP_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(a);
    size += ros::serialization::serializationLength(b);
    return size;
  }

  typedef boost::shared_ptr<hallo::AddTwoIntsRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr<hallo::AddTwoIntsRequest_<ContainerAllocator>  const> ConstPtr;
}; // struct AddTwoIntsRequest
typedef hallo::AddTwoIntsRequest_<std::allocator<void> > AddTwoIntsRequest;

typedef boost::shared_ptr<hallo::AddTwoIntsRequest> AddTwoIntsRequestPtr;
typedef boost::shared_ptr<hallo::AddTwoIntsRequest const> AddTwoIntsRequestConstPtr;


template <class ContainerAllocator>
struct AddTwoIntsResponse_ : public ros::Message
{
  typedef AddTwoIntsResponse_<ContainerAllocator> Type;

  AddTwoIntsResponse_()
  : sum(0)
  {
  }

  AddTwoIntsResponse_(const ContainerAllocator& _alloc)
  : sum(0)
  {
  }

  typedef int64_t _sum_type;
  int64_t sum;


private:
  static const char* __s_getDataType_() { return "hallo/AddTwoIntsResponse"; }
public:
  ROSCPP_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROSCPP_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "b88405221c77b1878a3cbbfff53428d7"; }
public:
  ROSCPP_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROSCPP_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getServerMD5Sum_() { return "6a2e34150c00229791cc89ff309fff21"; }
public:
  ROSCPP_DEPRECATED static const std::string __s_getServerMD5Sum() { return __s_getServerMD5Sum_(); }

  ROSCPP_DEPRECATED const std::string __getServerMD5Sum() const { return __s_getServerMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "int64 sum\n\
\n\
\n\
"; }
public:
  ROSCPP_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROSCPP_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROSCPP_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, sum);
    return stream.getData();
  }

  ROSCPP_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, sum);
    return stream.getData();
  }

  ROSCPP_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(sum);
    return size;
  }

  typedef boost::shared_ptr<hallo::AddTwoIntsResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr<hallo::AddTwoIntsResponse_<ContainerAllocator>  const> ConstPtr;
}; // struct AddTwoIntsResponse
typedef hallo::AddTwoIntsResponse_<std::allocator<void> > AddTwoIntsResponse;

typedef boost::shared_ptr<hallo::AddTwoIntsResponse> AddTwoIntsResponsePtr;
typedef boost::shared_ptr<hallo::AddTwoIntsResponse const> AddTwoIntsResponseConstPtr;

struct AddTwoInts
{

typedef AddTwoIntsRequest Request;
typedef AddTwoIntsResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;
}; // struct AddTwoInts
} // namespace hallo

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator>
struct MD5Sum<hallo::AddTwoIntsRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "36d09b846be0b371c5f190354dd3153e";
  }

  static const char* value(const hallo::AddTwoIntsRequest_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x36d09b846be0b371ULL;
  static const uint64_t static_value2 = 0xc5f190354dd3153eULL;
};

template<class ContainerAllocator>
struct DataType<hallo::AddTwoIntsRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "hallo/AddTwoIntsRequest";
  }

  static const char* value(const hallo::AddTwoIntsRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition<hallo::AddTwoIntsRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "int64 a\n\
int64 b\n\
\n\
";
  }

  static const char* value(const hallo::AddTwoIntsRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize<hallo::AddTwoIntsRequest_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros


namespace ros
{
namespace message_traits
{
template<class ContainerAllocator>
struct MD5Sum<hallo::AddTwoIntsResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "b88405221c77b1878a3cbbfff53428d7";
  }

  static const char* value(const hallo::AddTwoIntsResponse_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xb88405221c77b187ULL;
  static const uint64_t static_value2 = 0x8a3cbbfff53428d7ULL;
};

template<class ContainerAllocator>
struct DataType<hallo::AddTwoIntsResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "hallo/AddTwoIntsResponse";
  }

  static const char* value(const hallo::AddTwoIntsResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition<hallo::AddTwoIntsResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "int64 sum\n\
\n\
\n\
";
  }

  static const char* value(const hallo::AddTwoIntsResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize<hallo::AddTwoIntsResponse_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer<hallo::AddTwoIntsRequest_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.a);
    stream.next(m.b);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct AddTwoIntsRequest_
} // namespace serialization
} // namespace ros


namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer<hallo::AddTwoIntsResponse_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.sum);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct AddTwoIntsResponse_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace service_traits
{
template<>
struct MD5Sum<hallo::AddTwoInts> {
  static const char* value() 
  {
    return "6a2e34150c00229791cc89ff309fff21";
  }

  static const char* value(const hallo::AddTwoInts&) { return value(); } 
};

template<>
struct DataType<hallo::AddTwoInts> {
  static const char* value() 
  {
    return "hallo/AddTwoInts";
  }

  static const char* value(const hallo::AddTwoInts&) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<hallo::AddTwoIntsRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "6a2e34150c00229791cc89ff309fff21";
  }

  static const char* value(const hallo::AddTwoIntsRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<hallo::AddTwoIntsRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "hallo/AddTwoInts";
  }

  static const char* value(const hallo::AddTwoIntsRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<hallo::AddTwoIntsResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "6a2e34150c00229791cc89ff309fff21";
  }

  static const char* value(const hallo::AddTwoIntsResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<hallo::AddTwoIntsResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "hallo/AddTwoInts";
  }

  static const char* value(const hallo::AddTwoIntsResponse_<ContainerAllocator> &) { return value(); } 
};

} // namespace service_traits
} // namespace ros

#endif // HALLO_SERVICE_ADDTWOINTS_H

