#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <inttypes.h>
#include "ls1p.h"

void test_command_with_args();
void test_nonzero_dest();


int main(int argn, char** argv)
{
    test_command_with_args();
    test_nonzero_dest();
    printf("Tests passed.\n");
    return EXIT_SUCCESS;
}

void test_command_with_args() {
    uint8_t buf[255];
    int pos = 0;
    int rc;
    uint8_t dest;
    uint8_t code;
    uint16_t mref;

    rc = encode_cmd(buf, &pos, LS1P_CMD_DST_ARM, LS1P_CMD_CODE_CMDLOG, 314);
    assert(rc == LS1P_API_OK);
    assert(pos == 3);
    assert(buf[0] == 0x01);

    rc = encode_uint8(buf, &pos, 123);
    assert(rc == LS1P_API_OK);
    assert(pos == 4);

    rc = encode_uint16(buf, &pos, 4023);
    assert(rc == LS1P_API_OK);
    assert(pos == 6);

    assert(buf[0] == 0x01);
    assert(buf[1] == 0x01);
    assert(buf[2] == 0x3A);
    assert(buf[3] == 0x7B);
    assert(buf[4] == 0x0F);
    assert(buf[5] == 0xB7);

    rc = decode_cmd(buf, &pos, &dest, &code, &mref);
    assert(rc == LS1P_API_OK);
    assert(dest == LS1P_CMD_DST_ARM);
    assert(code == LS1P_CMD_CODE_CMDLOG);
    assert(mref == 314);
    assert(pos == 3);
}

void test_nonzero_dest()
{
    uint8_t buf[255];
    int pos = 0;
    int rc;

    rc = encode_cmd(buf, &pos, LS1P_CMD_DST_ARDUINO, LS1P_CMD_CODE_VOID, 315);
    assert(rc == LS1P_API_OK);
    assert(pos == 3);
    assert(buf[0] == 0x20);
}

