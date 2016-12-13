
#include "private/CO_SDO_p.h"

///////////////////////////////////////////////////////////////////////////////
int CO_SDO_build_init_dl_rp(unsigned char *const buf, 
        const OD_index_t idx, const OD_subindex_t subidx) {
    
    int ret=CO_ERROR_NONE;
        
    if(!buf) return CO_ERROR_NULL_PTR;   
    
    // reset whole buffer 
    CO_RESET_WHOLE_BUFFER(buf);
    
    // set command type
    buf[0] = CO_SDO_CMD_SCS_INIT_DL_RP;
       
    // fill indexes
    if(CO_index_fill(&buf[1], idx, subidx)) {
        ret=CO_ERROR_BAD_IDX;
        goto exit;
    }
       
exit:
    if(ret!=CO_ERROR_NONE) {
        // reset whole buffer 
        CO_RESET_WHOLE_BUFFER(buf);
    }
    return ret;
}

