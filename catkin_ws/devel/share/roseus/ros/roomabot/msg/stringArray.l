;; Auto-generated. Do not edit!


(when (boundp 'roomabot::stringArray)
  (if (not (find-package "ROOMABOT"))
    (make-package "ROOMABOT"))
  (shadow 'stringArray (find-package "ROOMABOT")))
(unless (find-package "ROOMABOT::STRINGARRAY")
  (make-package "ROOMABOT::STRINGARRAY"))

(in-package "ROS")
;;//! \htmlinclude stringArray.msg.html


(defclass roomabot::stringArray
  :super ros::object
  :slots (_command _argument ))

(defmethod roomabot::stringArray
  (:init
   (&key
    ((:command __command) "")
    ((:argument __argument) "")
    )
   (send-super :init)
   (setq _command (string __command))
   (setq _argument (string __argument))
   self)
  (:command
   (&optional __command)
   (if __command (setq _command __command)) _command)
  (:argument
   (&optional __argument)
   (if __argument (setq _argument __argument)) _argument)
  (:serialization-length
   ()
   (+
    ;; string _command
    4 (length _command)
    ;; string _argument
    4 (length _argument)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _command
       (write-long (length _command) s) (princ _command s)
     ;; string _argument
       (write-long (length _argument) s) (princ _argument s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _command
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _command (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _argument
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _argument (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get roomabot::stringArray :md5sum-) "89ea12cd1f3864199e2c936705472021")
(setf (get roomabot::stringArray :datatype-) "roomabot/stringArray")
(setf (get roomabot::stringArray :definition-)
      "string command
string argument

")



(provide :roomabot/stringArray "89ea12cd1f3864199e2c936705472021")


