#ifndef _ROS_roomabot_serviceCommand_h
#define _ROS_roomabot_serviceCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace roomabot
{

  class serviceCommand : public ros::Msg
  {
    public:
      typedef const char* _command_type;
      _command_type command;
      typedef const char* _arg1_type;
      _arg1_type arg1;
      typedef const char* _arg2_type;
      _arg2_type arg2;

    serviceCommand():
      command(""),
      arg1(""),
      arg2("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      uint32_t length_command = strlen(this->command);
      varToArr(outbuffer + offset, length_command);
      offset += 4;
      memcpy(outbuffer + offset, this->command, length_command);
      offset += length_command;
      uint32_t length_arg1 = strlen(this->arg1);
      varToArr(outbuffer + offset, length_arg1);
      offset += 4;
      memcpy(outbuffer + offset, this->arg1, length_arg1);
      offset += length_arg1;
      uint32_t length_arg2 = strlen(this->arg2);
      varToArr(outbuffer + offset, length_arg2);
      offset += 4;
      memcpy(outbuffer + offset, this->arg2, length_arg2);
      offset += length_arg2;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t length_command;
      arrToVar(length_command, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_command; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_command-1]=0;
      this->command = (char *)(inbuffer + offset-1);
      offset += length_command;
      uint32_t length_arg1;
      arrToVar(length_arg1, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_arg1; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_arg1-1]=0;
      this->arg1 = (char *)(inbuffer + offset-1);
      offset += length_arg1;
      uint32_t length_arg2;
      arrToVar(length_arg2, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_arg2; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_arg2-1]=0;
      this->arg2 = (char *)(inbuffer + offset-1);
      offset += length_arg2;
     return offset;
    }

    virtual const char * getType() override { return "roomabot/serviceCommand"; };
    virtual const char * getMD5() override { return "7addab281efdf18482237e77c6129c86"; };

  };

}
#endif
