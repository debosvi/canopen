
#include "private/CO_SDO_p.h"

///////////////////////////////////////////////////////////////////////////////
int CO_SDO_build_init_blk_ul_rp(unsigned char* const buf, const bool crc, 
        const OD_index_t idx, const OD_subindex_t subidx, 
        const CO_SDO_data_size_t size) {
    
    int ret=CO_ERROR_NONE;
    
    if(!buf) return CO_ERROR_NULL_PTR;
       
    // reset whole buffer 
    CO_RESET_WHOLE_BUFFER(buf);
    
    // set command type
    buf[0] = CO_SDO_CMD_CCS_INIT_BUL_RP;

    // set crc capability
    if(crc) 
        buf[0] |= CO_SDO_CMD_BLK_CRC_MASK;
    else 
        buf[0] &= ~CO_SDO_CMD_BLK_CRC_MASK;

    // set size indicator
    if(size) 
        buf[0] |= CO_SDO_CMD_BLK_SZ_IND_MASK;
    
    // fill indexes
    if(CO_index_fill(&buf[1], idx, subidx)) {
        ret=CO_ERROR_BAD_IDX;
        goto exit;
    }
        
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

