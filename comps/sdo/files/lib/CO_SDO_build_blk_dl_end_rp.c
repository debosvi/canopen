
#include "private/CO_SDO_p.h"

///////////////////////////////////////////////////////////////////////////////
int CO_SDO_build_blk_dl_end_rp(unsigned char* const buf) {
    
    if(!buf) return CO_ERROR_NULL_PTR;
    
    // reset whole buffer 
    CO_RESET_WHOLE_BUFFER(buf);
    
    // set command type
    buf[0] = CO_SDO_CMD_SCS_BDL_END_RP;
    
    return CO_ERROR_NONE;
}

