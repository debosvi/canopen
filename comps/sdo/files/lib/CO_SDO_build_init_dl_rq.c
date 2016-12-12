
#include "private/CO_SDO_p.h"

#define ERROR_BAD_BUF           (1)
#define ERROR_ARGS              (2)
#define ERROR_BAD_IDX           (3)
#define ERROR_UNIMPLEMENTED     (4)

///////////////////////////////////////////////////////////////////////////////
int CO_SDO_build_init_dl_rq(char *const buf, const bool e, const bool s, 
        const OD_index_t idx, const OD_subindex_t subidx, const uint32_t lg) {
    
    if(!buf) return ERROR_BAD_BUF;
    if(s && !lg) return ERROR_ARGS;
    if(!s && lg) return ERROR_ARGS;
    
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
        return ERROR_BAD_IDX;
        
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
    else return ERROR_UNIMPLEMENTED;
    
    return 0;
}

