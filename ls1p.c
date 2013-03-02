#include <stdint.h>
#include "ls1p.h"


int encode_cmd(uint8_t* buf, int* pos, uint8_t dest, uint8_t code, uint16_t mref)
{
    *pos = 0;
    encode_uint8(buf, pos, (dest << LS1P_CODE__BITS) | code);
    encode_uint16(buf, pos, mref);
    return LS1P_API_OK;
}

int encode_uint8(uint8_t* buf, int* pos, uint8_t arg) {
    buf[(*pos)++] = arg;
    return LS1P_API_OK;
}

int encode_uint16(uint8_t* buf, int* pos, uint16_t arg) {
    buf[(*pos)++] = (uint8_t) (arg >> 8);
    buf[(*pos)++] = (uint8_t) (arg & 0x00FF);
    return LS1P_API_OK;
}


int decode_cmd(uint8_t* buf, int* pos, uint8_t* dest, uint8_t* code, uint16_t* mref)
{
    uint8_t cmd;
    *pos = 0;
    decode_uint8(buf, pos, &cmd);
    *dest = cmd >> LS1P_CODE__BITS;
    *code = cmd & 0x1F;
    decode_uint16(buf, pos, mref);
    return LS1P_API_OK;
}

int decode_uint8(uint8_t* buf, int* pos, uint8_t* arg) {
    *arg = buf[(*pos)++];
    return LS1P_API_OK;
}

int decode_uint16(uint8_t* buf, int* pos, uint16_t* arg) {
    *arg = ((uint16_t) buf[(*pos)++]) << 8;
    *arg = *arg | buf[(*pos)++];
    return LS1P_API_OK;
}
