
#include "private/CO_SDO_p.h"

///////////////////////////////////////////////////////////////////////////////
int CO_SDO_build_init_blk_dl_rp(unsigned char* const buf, const bool crc, 
    const OD_index_t idx, const OD_subindex_t subidx, const uint8_t blk_sz) {
    
    int ret=CO_ERROR_NONE;
    
    if(!buf) return CO_ERROR_NULL_PTR;
    if(!blk_sz) return CO_ERROR_BAD_ARGS;
    
    // reset whole buffer 
    CO_RESET_WHOLE_BUFFER(buf);
    
    // set command type
    buf[0] = CO_SDO_CMD_CCS_INIT_BDL_RQ;

    // set crc capability
    if(crc) 
        buf[0] |= CO_SDO_CMD_BLK_CRC_MASK;
    else 
        buf[0] &= ~CO_SDO_CMD_BLK_CRC_MASK;
    
    // fill indexes
    if(CO_index_fill(&buf[1], idx, subidx)) {
        ret=CO_ERROR_BAD_IDX;
        goto exit;
    }
        
    // set block size
    buf[4] = blk_sz;
    
exit:
    if(ret!=CO_ERROR_NONE) {
        CO_RESET_WHOLE_BUFFER(buf);
    }
    return ret;
}

