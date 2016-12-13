
#include "private/CO_SDO_p.h"

///////////////////////////////////////////////////////////////////////////////
int CO_SDO_build_abort_transfert(unsigned char* const buf, 
    const OD_index_t idx, const OD_subindex_t subidx, 
    const uint32_t code) {
    
    int ret=CO_ERROR_NONE;
    
    if(!buf) return CO_ERROR_NULL_PTR;
           
    // reset whole buffer 
    CO_RESET_WHOLE_BUFFER(buf);
    
    // set command type
    buf[0] = CO_SDO_CMD_CS_ABORT;

    // fill indexes
    if(CO_index_fill(&buf[1], idx, subidx)) {
        ret=CO_ERROR_BAD_IDX;
        goto exit;
    }
    
    {
        uint32_t c=htonl(code);
        memcpy(&buf[4], &c, 4);
    }
        
exit:
    if(ret!=CO_ERROR_NONE) {
        CO_RESET_WHOLE_BUFFER(buf);
    }
    return ret;
}

