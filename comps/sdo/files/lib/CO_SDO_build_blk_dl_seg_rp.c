
#include "private/CO_SDO_p.h"

///////////////////////////////////////////////////////////////////////////////
int CO_SDO_build_blk_dl_seg_rp(unsigned char* const buf, 
    const uint8_t seq, const uint8_t blk_sz) {
    
    if(!buf) return CO_ERROR_NULL_PTR;
    if(!seq) return CO_ERROR_BAD_ARGS;
    if(seq>CO_CAN_MAX_BLK_SIZE) return CO_ERROR_DATA_OVERFLOW;
    if(!blk_sz) return CO_ERROR_BAD_ARGS;
    if(blk_sz>CO_CAN_MAX_BLK_SIZE) return CO_ERROR_DATA_OVERFLOW;
    
    // reset whole buffer 
    CO_RESET_WHOLE_BUFFER(buf);
    
    // set command type
    buf[0] = CO_SDO_CMD_SCS_BDL_RP;
    
    // set seq number
    buf[1] = seq;
    
    // set block size
    buf[2] = blk_sz;

    return CO_ERROR_NONE;
}

