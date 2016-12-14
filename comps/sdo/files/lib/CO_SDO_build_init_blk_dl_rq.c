
#include "private/CO_SDO_p.h"

///////////////////////////////////////////////////////////////////////////////
int CO_SDO_build_init_blk_dl_rq(unsigned char* const buf, 
        const bool crc, const bool s, 
        const OD_index_t idx, const OD_subindex_t subidx, const uint32_t size) {
    
    int ret=CO_ERROR_NONE;
    
    if(!buf) return CO_ERROR_NULL_PTR;
    if(s && !size) return CO_ERROR_BAD_ARGS;
    if(!s && size) return CO_ERROR_BAD_ARGS;
    
    // reset whole buffer 
    CO_RESET_WHOLE_BUFFER(buf);
    
    // set command type
    buf[0] = CO_SDO_CMD_CCS_INIT_BDL_RQ;

    // set size presence
    if(s) 
        buf[0] |= CO_SDO_CMD_BLK_SZ_IND_MASK;
    else 
        buf[0] &= ~CO_SDO_CMD_BLK_SZ_IND_MASK;

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
        
    // put data depending on arguments combination
    {
        uint32_t l=size;
        for(int i=0; i<4; i++) {
            buf[4+i] = (l&0xFF);
            l = l>>8;
        }
    }
    
exit:
    if(ret!=CO_ERROR_NONE) {
        CO_RESET_WHOLE_BUFFER(buf);
    }
    return ret;
}

