
#include "private/CO_SDO_p.h"

///////////////////////////////////////////////////////////////////////////////
int CO_SDO_build_init_dl_rq(char *const buf, const bool e, const bool s, 
        const OD_index_t idx, const OD_subindex_t subidx, const uint32_t lg) {
    
    if(!buf) return CO_ERROR_NULL_PTR;
    if(s && !lg) return CO_ERROR_BAD_ARGS;
    if(!s && lg) return CO_ERROR_BAD_ARGS;
    
    buf[0] = CO_SDO_CMD_CCS_INIT_DL_RQ;
    if(e)
        buf[0] |= CO_SDO_CMD_TRANSFERT_MASK;
    else 
        buf[0] &= ~CO_SDO_CMD_TRANSFERT_MASK;

    if(s) 
        buf[0] |= CO_SDO_CMD_SZ_INDIC_MASK;
    else 
        buf[0] &= ~CO_SDO_CMD_SZ_INDIC_MASK;
    
    if(CO_index_fill(&buf[1], idx, subidx))
        return CO_ERROR_BAD_IDX;
        
    if(e && s) {
        uint8_t n=0;
        if((lg&0xFF)==lg) n=3;
        else if((lg&0xFFFF)==lg) n=2;
        else if((lg&0xFFFFFF)==lg) n=1;
        
        buf[0] |= (n<<2);
        uint32_t l=lg;
        for(int i=0; i<(4-n); i++) {
            buf[4+i] = (l&0xFF);
            l = l>>8;
        }
    }
    else if(!e && s) {
        uint32_t l=lg;
        for(int i=0; i<4; i++) {
            buf[4+i] = (l&0xFF);
            l = l>>8;
        }
    }
    else return CO_ERROR_UNIMPLEMENTED;
    
    return CO_ERROR_NONE;
}

