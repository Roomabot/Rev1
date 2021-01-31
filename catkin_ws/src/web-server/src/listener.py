#!/usr/bin/env python
# Software License Agreement (BSD License)
#
# Copyright (c) 2008, Willow Garage, Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials provided
#    with the distribution.
#  * Neither the name of Willow Garage, Inc. nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# Revision $Id$

## Simple talker demo that listens to std_msgs/Strings published 
## to the 'chatter' topic

import rospy
import asyncio
import websockets
from std_msgs.msg import String
import pathlib
from roomabot.msg import serviceCommand
from nav_msgs.msg import OccupancyGrid 
import ssl
PORT = 6001
ADDRESS=''

connected = set()
queue = asyncio.Queue()

async def brodcast(data):
    if connected:
        await asyncio.wait([user.send(str(data)) for user in connected])

def callback(data):
    # run brodcast task for each callback
    asyncio.run(brodcast(data))

def listener():
    print('listening')
    rospy.init_node('listener', anonymous=True)

    rospy.Subscriber('map', OccupancyGrid, callback)
    rospy.Subscriber('status', serviceCommand, callback)
    
    # don't need ros spin for since node will keep running the server instance
    # rospy.spin()


userInputPublisher = rospy.Publisher('user_input', String, queue_size=1) 

async def onUserConnect(websocket, path):
    # for now, we are not restricting number of UI clients connected
    # so, each will get all published data
    connected.add(websocket)

    # listen for any messages from ui
    async for message in websocket:
        print('Receievd message: ', message)
        # TODO: refactor
        if message.command == 'drive':
            userInputPub.publish(message)
        if message.command == 'serviceRequest':
            # parse data
            print('sending data')
            # servicePub.publish(message)
    print('closing for: ', websocket)

def getSSLContext():
    ssl_context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
    localhost_pem = pathlib.Path(__file__).with_name('mycert.pem')
    ssl_context.load_cert_chain(localhost_pem)
    return ssl_context

if __name__ == '__main__':
    listener()
    ssl_context = getSSLContext()
    start_server = websockets.serve(onUserConnect, ADDRESS, PORT, ssl=ssl_context)
    asyncio.get_event_loop().run_until_complete(start_server)
    print('started server')
    asyncio.get_event_loop().run_forever()

