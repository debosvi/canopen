
#include "private/CO_SDO_p.h"

///////////////////////////////////////////////////////////////////////////////
int CO_SDO_build_dl_seg_rp(unsigned char *const buf, const bool toggle) {
    
    if(!buf) return CO_ERROR_NULL_PTR;   
    
    // reset whole buffer 
    CO_RESET_WHOLE_BUFFER(buf);
    
    // set command type
    buf[0] = CO_SDO_CMD_SCS_DL_SEG_RP;
       
    // update 'toggle' bit
    if(toggle)
        buf[0] |= CO_SDO_CMD_TOGGLE_MASK;
    else 
        buf[0] &= ~CO_SDO_CMD_TOGGLE_MASK;
       
    return CO_ERROR_NONE;
}
