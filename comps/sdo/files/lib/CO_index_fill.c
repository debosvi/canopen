
#include "private/CO_SDO_p.h"

///////////////////////////////////////////////////////////////////////////////
int CO_index_fill(char * const data, const OD_index_t idx, const OD_subindex_t subidx) {
    
    if(!data) return CO_ERROR_NULL_PTR;
    
    OD_index_t idx_le=0;
    
    idx_le=htons(idx);
    
    data[0]=(idx_le>>8)&0xFF;
    data[1]=idx_le&0xFF;
    data[2]=subidx;
    
    return CO_ERROR_NONE;
}

