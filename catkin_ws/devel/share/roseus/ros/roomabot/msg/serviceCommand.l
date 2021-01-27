;; Auto-generated. Do not edit!


(when (boundp 'roomabot::serviceCommand)
  (if (not (find-package "ROOMABOT"))
    (make-package "ROOMABOT"))
  (shadow 'serviceCommand (find-package "ROOMABOT")))
(unless (find-package "ROOMABOT::SERVICECOMMAND")
  (make-package "ROOMABOT::SERVICECOMMAND"))

(in-package "ROS")
;;//! \htmlinclude serviceCommand.msg.html


(defclass roomabot::serviceCommand
  :super ros::object
  :slots (_command _arg1 _arg2 ))

(defmethod roomabot::serviceCommand
  (:init
   (&key
    ((:command __command) "")
    ((:arg1 __arg1) "")
    ((:arg2 __arg2) "")
    )
   (send-super :init)
   (setq _command (string __command))
   (setq _arg1 (string __arg1))
   (setq _arg2 (string __arg2))
   self)
  (:command
   (&optional __command)
   (if __command (setq _command __command)) _command)
  (:arg1
   (&optional __arg1)
   (if __arg1 (setq _arg1 __arg1)) _arg1)
  (:arg2
   (&optional __arg2)
   (if __arg2 (setq _arg2 __arg2)) _arg2)
  (:serialization-length
   ()
   (+
    ;; string _command
    4 (length _command)
    ;; string _arg1
    4 (length _arg1)
    ;; string _arg2
    4 (length _arg2)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _command
       (write-long (length _command) s) (princ _command s)
     ;; string _arg1
       (write-long (length _arg1) s) (princ _arg1 s)
     ;; string _arg2
       (write-long (length _arg2) s) (princ _arg2 s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _command
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _command (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _arg1
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _arg1 (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _arg2
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _arg2 (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get roomabot::serviceCommand :md5sum-) "7addab281efdf18482237e77c6129c86")
(setf (get roomabot::serviceCommand :datatype-) "roomabot/serviceCommand")
(setf (get roomabot::serviceCommand :definition-)
      "string command
string arg1
string arg2

")



(provide :roomabot/serviceCommand "7addab281efdf18482237e77c6129c86")


