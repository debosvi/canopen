
#include "private/CO_SDO_p.h"

#define MAX_SEGMENT_DATA    (7)

///////////////////////////////////////////////////////////////////////////////
int CO_SDO_build_dl_seg_rq(unsigned char *const buf, const bool last, const bool toggle,
        const char* const data, const uint8_t lg) {
    
    
    if(!buf) return CO_ERROR_NULL_PTR;
    if(lg>MAX_SEGMENT_DATA) return CO_ERROR_BAD_ARGS;
    
    // reset whole buffer 
    CO_RESET_WHOLE_BUFFER(buf);
    
    // set command type
    buf[0] = CO_SDO_CMD_CCS_DL_SEG_RQ;
    
    // update 'last segment' bit
    if(last)
        buf[0] |= CO_SDO_CMD_LAST_SEG_MASK;
    else 
        buf[0] &= ~CO_SDO_CMD_LAST_SEG_MASK;
    
    // update 'toggle' bit
    if(toggle)
        buf[0] |= CO_SDO_CMD_TOGGLE_MASK;
    else 
        buf[0] &= ~CO_SDO_CMD_TOGGLE_MASK;
    
    // update unused bytes in buffer
    {
        uint8_t n=0;
        n=MAX_SEGMENT_DATA-lg;
        n=(n<<1);
        buf[0] |= n;
    }
    
    // copy amout of data
    memcpy(&buf[1], data, lg);
    
    return CO_ERROR_NONE;
}

