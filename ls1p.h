#ifndef LS1P_H
#define LS1P_H

/**
 * The primary goal for this protocol is to be as simple as possible.
 * Intentionally, there is no session support, routing capabilities
 * or guaranteed delivery. The communication with the SAT is based on
 * asynchronous message passing. Timeouts are employed to add robustness
 * to the protocol.
 *
 * Two types of messages exist in the LS1 protocol:
 *
 *  1. Command messages. They are sent from the ground station to the SAT.
 *     These messages have the following structure:
 *
 *         <DestinationAddress><CommandCode><MessageReferenceId>[<Argument>*]
 *
 *     where
 *
 *       - <DestinationAddress> [3 bits]  describes subsystem, that should handle the command.
 *       - <CommandCode> [5 bits] stands for identifies particular command (type of the command).
 *       - <MessageReferenceId> [16 bits] identifies particular insance of the command.
 *       - <Argument> argument for the command, dependent on <CommandCode>.
 *
 *  2. Data messages, sent from the SAT to the ground station. They are always
 *     requested by the ground station by issuing apropriate command. Data messages
 *     are of the following structure:
 *
 *         <SourceAddress><MessageCode><MessageReferenceId><ResponseFragmentNo><Data>
 *
 *     where
 *
 *       - <SourceAddress> [3 bits] stands for the subsystem sending the message.
 *       - <MessageCode> [5 bits] identifies type of the message.
 *       - <MessageReferenceId> [16 bits] identifies a command, the response if for.
 *       - <ResponseFragmentNo> [16 bits] response fragment number.
 *       - <Data> command specific data.
 */

#define LS1P_ADDR__BITS    3
#define LS1P_CODE__BITS    5


/**
 *  LS1P > Message > Command :: Destination
 *  Destination field values for command messages (GS -> SAT).
 */
#define LS1P_ADDR_ARM      0
#define LS1P_ADDR_ARDUINO  1
#define LS1P_ADDR_EPS      2
#define LS1P_ADDR_GPS_NMEA 3
#define LS1P_ADDR_GPS_BIN  4

/**
 *  LS1P > Message > Request :: Code
 *  Code field for the request messages (GS -> SAT).
 */
#define LS1P_REQ_CODE_UNDEFINED  0
#define LS1P_REQ_CODE_CMDLOG     1
#define LS1P_REQ_CODE_GPS_ON     2
#define LS1P_REQ_CODE_GPS_OFF    3

/**
 *  LS1P > Message > Response :: Code
 *  Code field for the response messages (SAT -> GS).
 */
#define LS1P_RES_CODE__BITS      8
#define LS1P_RES_CODE_UNDEFINED  0
#define LS1P_RES_CODE_ACK        1
#define LS1P_RES_CODE_CMDLOG     2




#define LS1P_API_OK 0

int encode_cmd(uint8_t* buf, int* pos, uint8_t dest, uint8_t code, uint16_t mref);
int encode_uint8(uint8_t* buf, int* pos, uint8_t arg);
int encode_uint16(uint8_t* buf, int* pos, uint16_t arg);
int decode_cmd(uint8_t* buf, int* pos, uint8_t* dest, uint8_t* code, uint16_t* mref);
int decode_uint8(uint8_t* buf, int* pos, uint8_t* arg);
int decode_uint16(uint8_t* buf, int* pos, uint16_t* arg);

#endif
