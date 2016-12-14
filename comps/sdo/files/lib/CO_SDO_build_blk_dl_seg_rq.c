
#include "private/CO_SDO_p.h"

///////////////////////////////////////////////////////////////////////////////
int CO_SDO_build_blk_dl_seg_rq(unsigned char* const buf, const bool more,
    const uint8_t seq, const unsigned char* const data, const uint8_t lg) {
    
    if(!buf) return CO_ERROR_NULL_PTR;
    if(!seq) return CO_ERROR_BAD_ARGS;
    if(seq>CO_CAN_MAX_BLK_SIZE) return CO_ERROR_DATA_OVERFLOW;
    if(data && !lg) return CO_ERROR_BAD_ARGS;
    if(!data && lg) return CO_ERROR_NULL_PTR;
    
    // reset whole buffer 
    CO_RESET_WHOLE_BUFFER(buf);
    
    // set command type
    buf[0] |= CO_SDO_CMD_BLK_MORE_MASK;
    
    // set sqe number
    buf[0] += seq;

    // set crc capability
    if(more) 
        buf[0] |= CO_SDO_CMD_BLK_MORE_MASK;
    else 
        buf[0] &= ~CO_SDO_CMD_BLK_MORE_MASK;
    
    // copy amout of data if so
    if(data && lg)
        memcpy(&buf[1], data, lg);    

    return CO_ERROR_NONE;
}

