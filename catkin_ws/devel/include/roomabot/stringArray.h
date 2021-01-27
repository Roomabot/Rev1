// Generated by gencpp from file roomabot/stringArray.msg
// DO NOT EDIT!


#ifndef ROOMABOT_MESSAGE_STRINGARRAY_H
#define ROOMABOT_MESSAGE_STRINGARRAY_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace roomabot
{
template <class ContainerAllocator>
struct stringArray_
{
  typedef stringArray_<ContainerAllocator> Type;

  stringArray_()
    : command()
    , argument()  {
    }
  stringArray_(const ContainerAllocator& _alloc)
    : command(_alloc)
    , argument(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _command_type;
  _command_type command;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _argument_type;
  _argument_type argument;





  typedef boost::shared_ptr< ::roomabot::stringArray_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::roomabot::stringArray_<ContainerAllocator> const> ConstPtr;

}; // struct stringArray_

typedef ::roomabot::stringArray_<std::allocator<void> > stringArray;

typedef boost::shared_ptr< ::roomabot::stringArray > stringArrayPtr;
typedef boost::shared_ptr< ::roomabot::stringArray const> stringArrayConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::roomabot::stringArray_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::roomabot::stringArray_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::roomabot::stringArray_<ContainerAllocator1> & lhs, const ::roomabot::stringArray_<ContainerAllocator2> & rhs)
{
  return lhs.command == rhs.command &&
    lhs.argument == rhs.argument;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::roomabot::stringArray_<ContainerAllocator1> & lhs, const ::roomabot::stringArray_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace roomabot

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::roomabot::stringArray_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::roomabot::stringArray_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::roomabot::stringArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::roomabot::stringArray_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::roomabot::stringArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::roomabot::stringArray_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::roomabot::stringArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "89ea12cd1f3864199e2c936705472021";
  }

  static const char* value(const ::roomabot::stringArray_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x89ea12cd1f386419ULL;
  static const uint64_t static_value2 = 0x9e2c936705472021ULL;
};

template<class ContainerAllocator>
struct DataType< ::roomabot::stringArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "roomabot/stringArray";
  }

  static const char* value(const ::roomabot::stringArray_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::roomabot::stringArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string command\n"
"string argument\n"
;
  }

  static const char* value(const ::roomabot::stringArray_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::roomabot::stringArray_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.command);
      stream.next(m.argument);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct stringArray_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::roomabot::stringArray_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::roomabot::stringArray_<ContainerAllocator>& v)
  {
    s << indent << "command: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.command);
    s << indent << "argument: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.argument);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROOMABOT_MESSAGE_STRINGARRAY_H
