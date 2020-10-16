// Generated by gencpp from file vel_joint_motors/VelJoint.msg
// DO NOT EDIT!


#ifndef VEL_JOINT_MOTORS_MESSAGE_VELJOINT_H
#define VEL_JOINT_MOTORS_MESSAGE_VELJOINT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace vel_joint_motors
{
template <class ContainerAllocator>
struct VelJoint_
{
  typedef VelJoint_<ContainerAllocator> Type;

  VelJoint_()
    : left_vel(0.0)
    , right_vel(0.0)  {
    }
  VelJoint_(const ContainerAllocator& _alloc)
    : left_vel(0.0)
    , right_vel(0.0)  {
  (void)_alloc;
    }



   typedef float _left_vel_type;
  _left_vel_type left_vel;

   typedef float _right_vel_type;
  _right_vel_type right_vel;





  typedef boost::shared_ptr< ::vel_joint_motors::VelJoint_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::vel_joint_motors::VelJoint_<ContainerAllocator> const> ConstPtr;

}; // struct VelJoint_

typedef ::vel_joint_motors::VelJoint_<std::allocator<void> > VelJoint;

typedef boost::shared_ptr< ::vel_joint_motors::VelJoint > VelJointPtr;
typedef boost::shared_ptr< ::vel_joint_motors::VelJoint const> VelJointConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::vel_joint_motors::VelJoint_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::vel_joint_motors::VelJoint_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::vel_joint_motors::VelJoint_<ContainerAllocator1> & lhs, const ::vel_joint_motors::VelJoint_<ContainerAllocator2> & rhs)
{
  return lhs.left_vel == rhs.left_vel &&
    lhs.right_vel == rhs.right_vel;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::vel_joint_motors::VelJoint_<ContainerAllocator1> & lhs, const ::vel_joint_motors::VelJoint_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace vel_joint_motors

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::vel_joint_motors::VelJoint_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::vel_joint_motors::VelJoint_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::vel_joint_motors::VelJoint_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::vel_joint_motors::VelJoint_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::vel_joint_motors::VelJoint_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::vel_joint_motors::VelJoint_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::vel_joint_motors::VelJoint_<ContainerAllocator> >
{
  static const char* value()
  {
    return "74ad8f7ea4d888606e4f41069cec47ff";
  }

  static const char* value(const ::vel_joint_motors::VelJoint_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x74ad8f7ea4d88860ULL;
  static const uint64_t static_value2 = 0x6e4f41069cec47ffULL;
};

template<class ContainerAllocator>
struct DataType< ::vel_joint_motors::VelJoint_<ContainerAllocator> >
{
  static const char* value()
  {
    return "vel_joint_motors/VelJoint";
  }

  static const char* value(const ::vel_joint_motors::VelJoint_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::vel_joint_motors::VelJoint_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float32 left_vel\n"
"float32 right_vel\n"
;
  }

  static const char* value(const ::vel_joint_motors::VelJoint_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::vel_joint_motors::VelJoint_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.left_vel);
      stream.next(m.right_vel);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct VelJoint_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::vel_joint_motors::VelJoint_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::vel_joint_motors::VelJoint_<ContainerAllocator>& v)
  {
    s << indent << "left_vel: ";
    Printer<float>::stream(s, indent + "  ", v.left_vel);
    s << indent << "right_vel: ";
    Printer<float>::stream(s, indent + "  ", v.right_vel);
  }
};

} // namespace message_operations
} // namespace ros

#endif // VEL_JOINT_MOTORS_MESSAGE_VELJOINT_H
