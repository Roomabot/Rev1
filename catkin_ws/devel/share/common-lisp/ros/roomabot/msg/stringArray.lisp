; Auto-generated. Do not edit!


(cl:in-package roomabot-msg)


;//! \htmlinclude stringArray.msg.html

(cl:defclass <stringArray> (roslisp-msg-protocol:ros-message)
  ((command
    :reader command
    :initarg :command
    :type cl:string
    :initform "")
   (argument
    :reader argument
    :initarg :argument
    :type cl:string
    :initform ""))
)

(cl:defclass stringArray (<stringArray>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <stringArray>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'stringArray)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name roomabot-msg:<stringArray> is deprecated: use roomabot-msg:stringArray instead.")))

(cl:ensure-generic-function 'command-val :lambda-list '(m))
(cl:defmethod command-val ((m <stringArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader roomabot-msg:command-val is deprecated.  Use roomabot-msg:command instead.")
  (command m))

(cl:ensure-generic-function 'argument-val :lambda-list '(m))
(cl:defmethod argument-val ((m <stringArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader roomabot-msg:argument-val is deprecated.  Use roomabot-msg:argument instead.")
  (argument m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <stringArray>) ostream)
  "Serializes a message object of type '<stringArray>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'command))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'command))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'argument))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'argument))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <stringArray>) istream)
  "Deserializes a message object of type '<stringArray>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'command) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'command) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'argument) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'argument) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<stringArray>)))
  "Returns string type for a message object of type '<stringArray>"
  "roomabot/stringArray")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'stringArray)))
  "Returns string type for a message object of type 'stringArray"
  "roomabot/stringArray")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<stringArray>)))
  "Returns md5sum for a message object of type '<stringArray>"
  "89ea12cd1f3864199e2c936705472021")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'stringArray)))
  "Returns md5sum for a message object of type 'stringArray"
  "89ea12cd1f3864199e2c936705472021")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<stringArray>)))
  "Returns full string definition for message of type '<stringArray>"
  (cl:format cl:nil "string command~%string argument~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'stringArray)))
  "Returns full string definition for message of type 'stringArray"
  (cl:format cl:nil "string command~%string argument~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <stringArray>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'command))
     4 (cl:length (cl:slot-value msg 'argument))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <stringArray>))
  "Converts a ROS message object to a list"
  (cl:list 'stringArray
    (cl:cons ':command (command msg))
    (cl:cons ':argument (argument msg))
))
