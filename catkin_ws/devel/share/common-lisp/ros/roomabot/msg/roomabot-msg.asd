
(cl:in-package :asdf)

(defsystem "roomabot-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "serviceCommand" :depends-on ("_package_serviceCommand"))
    (:file "_package_serviceCommand" :depends-on ("_package"))
  ))