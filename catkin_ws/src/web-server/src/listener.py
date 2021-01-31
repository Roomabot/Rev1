#!/usr/bin/env python

import rospy
import asyncio
import websockets
from std_msgs.msg import String
import pathlib
from roomabot.msg import serviceCommand
from nav_msgs.msg import OccupancyGrid 
import ssl
import json
PORT = 6001
ADDRESS=''

connected = set()
queue = asyncio.Queue()
serviceRequests = ['Start', 'Load', 'Save']

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



async def onUserConnect(websocket, path):
    # for now, we are not restricting number of UI clients connected
    # so, each will get all published data
    connected.add(websocket)
    userInputPub = rospy.Publisher('user_input', String, queue_size=1) 
    servicePub = rospy.Publisher('service_request', serviceCommand, queue_size=1)
    # listen for any messages from ui
    async for message in websocket:
        print('Receievd message: ', message)
        
        # TODO: refactor to remove ifs and let handlers do the job
        
        msg = json.loads(message)
        print('Parsed msg', msg)
        if msg['command'] == 'drive':
            userInputPub.publish(msg['data'])
        if msg['command'] in serviceRequests:
            req = serviceCommand()
            req.command = msg['command']
            # parse data
            req.arg1 = msg['arg1']
            req.arg2 = msg['arg2']
            servicePub.publish(req)
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

