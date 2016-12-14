
#include "private/CO_SDO_p.h"

///////////////////////////////////////////////////////////////////////////////
int CO_SDO_build_blk_dl_end_rq(unsigned char* const buf, 
        const uint8_t empty, const uint16_t crc) {
    
    if(!buf) return CO_ERROR_NULL_PTR;
    if(empty>CO_SDO_CMD_BLK_SEG_MAXC_SIZE) return CO_ERROR_DATA_OVERFLOW;
    
    // reset whole buffer 
    CO_RESET_WHOLE_BUFFER(buf);
    
    // set command type
    buf[0] = CO_SDO_CMD_CCS_BDL_END_RQ;
    
    // set empty bytes tail size
    buf[0] += (empty<<2);
    
    // set block size
    *(uint16_t*)&buf[1] = htons(crc);

    return CO_ERROR_NONE;
}

