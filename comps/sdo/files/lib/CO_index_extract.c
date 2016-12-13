
#include "private/CO_SDO_p.h"

///////////////////////////////////////////////////////////////////////////////
int CO_index_extract(const unsigned char* const data, OD_index_t* idx, OD_subindex_t* subidx) {
    
    if(!data || !idx || !subidx) return CO_ERROR_NULL_PTR;
    
    OD_index_t idx_le=0;
    
    idx_le += (data[0]<<8);
    idx_le += data[1];
    
    (*idx)=ntohs(idx_le);
    (*subidx) = data[2];    
    
    return CO_ERROR_NONE;
}

