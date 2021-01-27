// Auto-generated. Do not edit!

// (in-package roomabot.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class stringArray {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.command = null;
      this.argument = null;
    }
    else {
      if (initObj.hasOwnProperty('command')) {
        this.command = initObj.command
      }
      else {
        this.command = '';
      }
      if (initObj.hasOwnProperty('argument')) {
        this.argument = initObj.argument
      }
      else {
        this.argument = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type stringArray
    // Serialize message field [command]
    bufferOffset = _serializer.string(obj.command, buffer, bufferOffset);
    // Serialize message field [argument]
    bufferOffset = _serializer.string(obj.argument, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type stringArray
    let len;
    let data = new stringArray(null);
    // Deserialize message field [command]
    data.command = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [argument]
    data.argument = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.command);
    length += _getByteLength(object.argument);
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'roomabot/stringArray';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '89ea12cd1f3864199e2c936705472021';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string command
    string argument
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new stringArray(null);
    if (msg.command !== undefined) {
      resolved.command = msg.command;
    }
    else {
      resolved.command = ''
    }

    if (msg.argument !== undefined) {
      resolved.argument = msg.argument;
    }
    else {
      resolved.argument = ''
    }

    return resolved;
    }
};

module.exports = stringArray;
