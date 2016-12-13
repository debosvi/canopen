
#ifndef __CO_SDO_PRIVATE_H__
#define __CO_SDO_PRIVATE_H__

#include <stdint.h>
#include <stdbool.h>

// use ntohs and htons functions
#ifndef WIN32
    #include <netinet/in.h>
#else
    #include <winsock2.h>
#endif

#include <canopen/sdo/CO_SDO.h>

/** Macro to erase whole CAN buffer */
#define CO_RESET_WHOLE_BUFFER(x)    memset(x, 0, CO_CAN_DATA_MAX)

/** Size Indicator command mask. */
#define CO_SDO_CMD_SZ_INDIC_MASK    (0x01<<0)
 
/** Transfert Type command mask. */
#define CO_SDO_CMD_TRANSFERT_MASK   (0x01<<1)
 
/** Last Segment command mask. */
#define CO_SDO_CMD_LAST_SEG_MASK    (0x01<<0)
 
/** Last Segment command mask. */
#define CO_SDO_CMD_TOGGLE_MASK      (0x01<<4)

/** Initiate Download command request from client. */
#define CO_SDO_CMD_CCS_INIT_DL_RQ   (0x01<<5)
 
/** Initiate Download command response from server. */
#define CO_SDO_CMD_SCS_INIT_DL_RP   (0x03<<5)

/** Download Segment command request from client. */
#define CO_SDO_CMD_CCS_DL_SEG_RQ    (0x00<<5)

/** Download Segment command response from server. */
#define CO_SDO_CMD_SCS_DL_SEG_RP    (0x01<<5)

/** Initiate Upload command request from client. */
#define CO_SDO_CMD_CCS_INIT_UL_RQ   (0x02<<5)

/** Initiate Upload command response from server. */
#define CO_SDO_CMD_SCS_INIT_UL_RP   (0x02<<5)

/** Upload Segment command request from client. */
#define CO_SDO_CMD_CCS_UL_SEG_RQ    (0x03<<5)

/** Upload Segment command response from server. */
#define CO_SDO_CMD_SCS_UL_SEG_RP    (0x00<<5)

/** Upload Segment command response from server. */
#define CO_SDO_CMD_CS_ABORT         (0x04<<5)

/** Initiate Block Download command request from client. */
#define CO_SDO_CMD_CCS_INIT_BDL_RQ   (0x06<<5)
 
/** Initiate Block Download command response from server. */
#define CO_SDO_CMD_SCS_INIT_BDL_RP   (0x05<<5)

/** Fill buffer (at index 0) with Object Directory index and subindex. */
extern int CO_index_fill(unsigned char* const data, 
    const OD_index_t idx, const OD_subindex_t subidx);

/** Extract Object Directory index and subindex from buffer (at index 0). */
extern int CO_index_extract(const unsigned char* const data, 
    OD_index_t* idx, OD_subindex_t* subidx);

/** Build a can frame buffer with command request 'Initiate SDO Download'. */
extern int CO_SDO_build_init_dl_rq(unsigned char* const buf, 
    const bool e, const bool s, 
    const OD_index_t idx, const OD_subindex_t subidx, const uint32_t lg);

/** Build a can frame buffer with command response 'Initiate SDO Download'. */
extern int CO_SDO_build_init_dl_rp(unsigned char* const buf, 
    const OD_index_t idx, const OD_subindex_t subidx);

/** Build a can frame buffer with command request 'Segment SDO Download'. */
extern int CO_SDO_build_dl_seg_rq(unsigned char* const buf, 
    const bool last, const bool toggle, 
    const unsigned char* const data, const uint8_t lg);

/** Build a can frame buffer with command response 'Segment SDO Download'. */
extern int CO_SDO_build_dl_seg_rp(unsigned char* const buf, 
    const bool toggle);

/** Build a can frame buffer with command request 'Initiate SDO Upload'. */
extern int CO_SDO_build_init_ul_rq(unsigned char* const buf, 
    const OD_index_t idx, const OD_subindex_t subidx);

/** Build a can frame buffer with command response 'Initiate SDO Upload'. */
extern int CO_SDO_build_init_ul_rp(unsigned char* const buf, 
    const bool e, const bool s, 
    const OD_index_t idx, const OD_subindex_t subidx, 
    const uint32_t lg);

/** Build a can frame buffer with command request 'Segment SDO Upload'. */
extern int CO_SDO_build_ul_seg_rq(unsigned char* const buf, 
    const bool toggle);

/** Build a can frame buffer with command response 'Segment SDO Upload'. */
extern int CO_SDO_build_ul_seg_rp(unsigned char* const buf, 
    const bool last, const bool toggle, 
    const unsigned char* const data, const uint8_t lg);
    
/** Build a can frame buffer with command 'Abort Transfert'. */
extern int CO_SDO_build_abort_transfert(unsigned char* const buf, 
    const OD_index_t idx, const OD_subindex_t subidx, 
    const uint32_t code);

#endif // __CO_SDO_PRIVATE_H__

