#ifndef COMMANDS_H_
#define COMMANDS_H_

// string definitions of commands
#define DEBUG   "debug"
#define LED1    "led1"
#define LED2    "led2"
#define PRINT   "print"
#define TRACE   "trace"

// uint8_t commands
#define CMDC_RESPONSE 0xFF
#define CMDC_UNDEFINED 0x00
#define CMDC_DEBUG 0x01
#define CMDC_LED1 0x02
#define CMDC_LED2 0x03
#define CMDC_PRINT 0x04
#define CMDC_TRACE 0x05

// response strings
#define RESP_OK "ok"
#define RESP_MISSING "missing data"
#define RESP_UNDEFINED "undefined command"

// string definitions of some data fields
#define D_ON "on"
#define D_OFF "off"

// strings
#define NEW_LINE    "\r\n"
#define RESPONSE    "response:"
#define NOT_FOUND   "device not found"
#define HOPS_NO     " ,hops: "
#define TRACE_RES   "trace: "
#endif /* COMMANDS_H_ */
