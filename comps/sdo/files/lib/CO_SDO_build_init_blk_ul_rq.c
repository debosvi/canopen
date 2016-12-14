
#include "private/CO_SDO_p.h"

///////////////////////////////////////////////////////////////////////////////
int CO_SDO_build_init_blk_ul_rq(unsigned char* const buf, const bool crc, 
        const OD_index_t idx, const OD_subindex_t subidx, 
        const CO_SDO_blk_size_t blk_sz, const CO_SDO_blk_size_t pst) {
    
    int ret=CO_ERROR_NONE;
    
    if(!buf) return CO_ERROR_NULL_PTR;
    if(!blk_sz) return CO_ERROR_BAD_ARGS;
    if(blk_sz>CO_SDO_MAX_BLK_SIZE) return CO_ERROR_DATA_OVERFLOW;
    
    // reset whole buffer 
    CO_RESET_WHOLE_BUFFER(buf);
    
    // set command type
    buf[0] = CO_SDO_CMD_CCS_INIT_BUL_RQ;

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
        
    // set PST
    buf[5] = pst;
    
exit:
    if(ret!=CO_ERROR_NONE) {
        CO_RESET_WHOLE_BUFFER(buf);
    }
    return ret;
}

