; Auto-generated. Do not edit!


(cl:in-package roomabot-msg)


;//! \htmlinclude serviceCommand.msg.html

(cl:defclass <serviceCommand> (roslisp-msg-protocol:ros-message)
  ((command
    :reader command
    :initarg :command
    :type cl:string
    :initform "")
   (arg1
    :reader arg1
    :initarg :arg1
    :type cl:string
    :initform "")
   (arg2
    :reader arg2
    :initarg :arg2
    :type cl:string
    :initform ""))
)

(cl:defclass serviceCommand (<serviceCommand>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <serviceCommand>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'serviceCommand)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name roomabot-msg:<serviceCommand> is deprecated: use roomabot-msg:serviceCommand instead.")))

(cl:ensure-generic-function 'command-val :lambda-list '(m))
(cl:defmethod command-val ((m <serviceCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader roomabot-msg:command-val is deprecated.  Use roomabot-msg:command instead.")
  (command m))

(cl:ensure-generic-function 'arg1-val :lambda-list '(m))
(cl:defmethod arg1-val ((m <serviceCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader roomabot-msg:arg1-val is deprecated.  Use roomabot-msg:arg1 instead.")
  (arg1 m))

(cl:ensure-generic-function 'arg2-val :lambda-list '(m))
(cl:defmethod arg2-val ((m <serviceCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader roomabot-msg:arg2-val is deprecated.  Use roomabot-msg:arg2 instead.")
  (arg2 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <serviceCommand>) ostream)
  "Serializes a message object of type '<serviceCommand>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'command))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'command))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'arg1))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'arg1))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'arg2))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'arg2))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <serviceCommand>) istream)
  "Deserializes a message object of type '<serviceCommand>"
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
      (cl:setf (cl:slot-value msg 'arg1) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'arg1) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'arg2) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'arg2) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<serviceCommand>)))
  "Returns string type for a message object of type '<serviceCommand>"
  "roomabot/serviceCommand")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'serviceCommand)))
  "Returns string type for a message object of type 'serviceCommand"
  "roomabot/serviceCommand")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<serviceCommand>)))
  "Returns md5sum for a message object of type '<serviceCommand>"
  "7addab281efdf18482237e77c6129c86")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'serviceCommand)))
  "Returns md5sum for a message object of type 'serviceCommand"
  "7addab281efdf18482237e77c6129c86")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<serviceCommand>)))
  "Returns full string definition for message of type '<serviceCommand>"
  (cl:format cl:nil "string command~%string arg1~%string arg2~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'serviceCommand)))
  "Returns full string definition for message of type 'serviceCommand"
  (cl:format cl:nil "string command~%string arg1~%string arg2~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <serviceCommand>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'command))
     4 (cl:length (cl:slot-value msg 'arg1))
     4 (cl:length (cl:slot-value msg 'arg2))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <serviceCommand>))
  "Converts a ROS message object to a list"
  (cl:list 'serviceCommand
    (cl:cons ':command (command msg))
    (cl:cons ':arg1 (arg1 msg))
    (cl:cons ':arg2 (arg2 msg))
))
