# Rev0
Rev0 code for Roomabot


## Rosbridge Setup

#### Install
```
sudo apt-get install ros-<rosdistro>-rosbridge-server
```

#### SSL Setup
1. Go into the rosbridge_server installation directory
```
cd $(rospack find rosbridge_server)
```
2. Create self-signed cert and keys
```
sudo openssl genrsa -out server_key.pem 2048
sudo openssl req -new -key server_key.pem -out server_csr.pem
sudo openssl x509 -req -days 1825 -in server_csr.pem -signkey server_key.pem -out server_cert.pem
sudo chmod +r server_cert.pem
sudo chmod +r server_key.pem
```
3. Update `rosbridge_websocket.launch` file with ssl certs
 
Note: `{path}` here is the directory you are in (run `pwd` to find this) 
```xml
<launch>
  <arg name="port" default="9090" />
  <arg name="address" default="0.0.0.0" />
  <arg name="ssl" default="true" />
  <arg name="certfile" default="{path}/server_cert.pem"/>
  <arg name="keyfile" default="{path}/server_key.pem" />
  
  ...  rest  of the file unchanged ...
```

#### Run
``` 
roslaunch rosbridge_server rosbridge_websocket.launch
```
