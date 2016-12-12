
#include "private/CO_SDO_p.h"

///////////////////////////////////////////////////////////////////////////////
int CO_SDO_build_init_dl_rp(char *const buf, 
        const OD_index_t idx, const OD_subindex_t subidx) {
    
    if(!buf) return CO_ERROR_NULL_PTR;   
    
    buf[0] = CO_SDO_CMD_SCS_INIT_DL_RP;
       
    if(CO_index_fill(&buf[1], idx, subidx))
        return CO_ERROR_BAD_IDX;
       
    return CO_ERROR_NONE;
}

