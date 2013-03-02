#ifndef LS1P_H
#define LS1P_H

/**
 *  LS1P > Message > Command :: Destination
 *  Destination field values for command messages (GS -> SAT).
 */
#define LS1P_CMD_DST__BITS    3
#define LS1P_CMD_DST_ARM      0
#define LS1P_CMD_DST_ARDUINO  1
#define LS1P_CMD_DST_EPS      2
#define LS1P_CMD_DST_GPS_NMEA 3
#define LS1P_CMD_DST_GPS_BIN  4

/**
 *  LS1P > Message > Command :: Code
 *  Command code field for the command messages (GS -> SAT).
 */
#define LS1P_CMD_CODE__BITS      5
#define LS1P_CMD_CODE_VOID       0
#define LS1P_CMD_CODE_CMDLOG     1
#define LS1P_CMD_CODE_GPS_ON     2
#define LS1P_CMD_CODE_GPS_OFF    3


#define LS1P_API_OK 0

int encode_cmd(uint8_t* buf, int* pos, uint8_t dest, uint8_t code, uint16_t mref);
int encode_uint8(uint8_t* buf, int* pos, uint8_t arg);
int encode_uint16(uint8_t* buf, int* pos, uint16_t arg);
int decode_cmd(uint8_t* buf, int* pos, uint8_t* dest, uint8_t* code, uint16_t* mref);
int decode_uint8(uint8_t* buf, int* pos, uint8_t* arg);
int decode_uint16(uint8_t* buf, int* pos, uint16_t* arg);

#endif
