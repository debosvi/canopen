
#include "private/CO_SDO_p.h"

#define MAX_SEGMENT_DATA    (7)

///////////////////////////////////////////////////////////////////////////////
int CO_SDO_build_ul_seg_rp(unsigned char *const buf, const bool last, const bool toggle,
        const unsigned char* const data, const CO_SDO_seg_size_t size) {
    
    
    if(!buf) return CO_ERROR_NULL_PTR;
    if(size>MAX_SEGMENT_DATA) return CO_ERROR_DATA_OVERFLOW;
    if(!data && size) return CO_ERROR_BAD_ARGS;
    if(data && !size) return CO_ERROR_BAD_ARGS;
    
    // reset whole buffer 
    CO_RESET_WHOLE_BUFFER(buf);
    
    // set command type
    buf[0] = CO_SDO_CMD_SCS_UL_SEG_RP;
    
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
        n=MAX_SEGMENT_DATA-size;
        n=(n<<1);
        buf[0] |= n;
    }
    
    // copy amout of data if so
    if(data && size)
        memcpy(&buf[1], data, size);
    
    return CO_ERROR_NONE;
}
