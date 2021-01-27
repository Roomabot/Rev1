#!/usr/bin/env python3
# license removed for brevity
import rospy
from roomabot.msg import serviceCommand

def talker():
    pub = rospy.Publisher('service_request', serviceCommand, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    msg = serviceCommand()
	
    msg.command="hi"
    msg.arg1="bye1"
    msg.arg2="bye2"
	
    while not rospy.is_shutdown():
        tmp = input("Enter command");
        msg.command=tmp
        tmp = input("Enter arg1");
        msg.arg1=tmp
        tmp = input("Enter arg2");
        msg.arg2=tmp
        pub.publish(msg)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
