
#include "private/CO_SDO_p.h"

///////////////////////////////////////////////////////////////////////////////
int CO_SDO_build_start_blk_ul_rq(unsigned char* const buf) {
    
    if(!buf) return CO_ERROR_NULL_PTR;
    
    // reset whole buffer 
    CO_RESET_WHOLE_BUFFER(buf);
    
    // set command type
    buf[0] = CO_SDO_CMD_CCS_START_BUL_RQ;
    
    return CO_ERROR_NONE;
}

