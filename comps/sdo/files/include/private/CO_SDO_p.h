
#ifndef __CO_SDO_PRIVATE_H__
#define __CO_SDO_PRIVATE_H__

#include <stdint.h>
#include <stdbool.h>

// use ntohs and htons functions
#ifndef WIN32
    #include <string.h>
    #include <netinet/in.h>
#else
    #include <winsock2.h>
#endif

#include <canopen/sdo/CO_SDO.h>

/** Max block size. */
#define CO_SDO_MAX_BLK_SIZE     (127)

/** Macro to erase whole CAN buffer */
#define CO_RESET_WHOLE_BUFFER(x)    memset(x, 0, CO_CAN_FRAME_DATA_MAX)

/** Size Indicator command mask (segments). */
#define CO_SDO_CMD_SEG_SZ_IND_MASK  (0x01<<0)

/** Size Indicator command mask (blocks). */
#define CO_SDO_CMD_BLK_SZ_IND_MASK  (0x01<<1)
 
/** Transfert Type command mask. */
#define CO_SDO_CMD_TRANSFERT_MASK   (0x01<<1)
 
/** Last Segment command mask. */
#define CO_SDO_CMD_LAST_SEG_MASK    (0x01<<0)

/** Last Segment command mask. */
#define CO_SDO_CMD_BLK_CRC_MASK     (0x01<<2)
 
/** Last Segment command mask. */
#define CO_SDO_CMD_TOGGLE_MASK      (0x01<<4) 

/** More Segments command mask. */
#define CO_SDO_CMD_BLK_MORE_MASK    (0x80)

/** SDO Block Download Last segment */
#define CO_SDO_CMD_BLK_ACK_MASK     (0x02)

/** SDO block Download End */
#define CO_SDO_CMD_BLK_END_MASK     (0x01)

/** SDO block Upload Start */
#define CO_SDO_CMD_BLK_START_MASK   (0x03)

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
#define CO_SDO_CMD_CCS_INIT_BDL_RQ  (0x06<<5)
 
/** Initiate Block Download command response from server. */
#define CO_SDO_CMD_SCS_INIT_BDL_RP  (0x05<<5)

/** Initiate Block Download command request from client. */
#define CO_SDO_CMD_SCS_BDL_RP       ((0x05<<5)+CO_SDO_CMD_BLK_ACK_MASK)

/** Initiate Block Download command request from client. */
#define CO_SDO_CMD_CCS_BDL_END_RQ   ((0x06<<5)+CO_SDO_CMD_BLK_END_MASK)

/** Initiate Block Download command request from client. */
#define CO_SDO_CMD_SCS_BDL_END_RP   ((0x05<<5)+CO_SDO_CMD_BLK_END_MASK)

/** Initiate Block Upload command request from client. */
#define CO_SDO_CMD_CCS_INIT_BUL_RQ (0x05<<5)

/** Initiate Block Upload command request from client. */
#define CO_SDO_CMD_CCS_INIT_BUL_RP (0x06<<5)

/** Block Upload Start command request from client. */
#define CO_SDO_CMD_CCS_START_BUL_RQ ((0x05<<5)+CO_SDO_CMD_BLK_START_MASK)

/** Block segment max size. */
#define CO_SDO_CMD_BLK_SEG_MAXC_SIZE    (7)

/** Block segment size type. */
typedef uint8_t CO_SDO_blk_size_t;

/** Block segment size type. */
typedef uint8_t CO_SDO_seg_size_t;

/** Block segment size type. */
typedef uint32_t CO_SDO_data_size_t;
 
/** Fill buffer (at index 0) with Object Directory index and subindex. */
extern int CO_index_fill(unsigned char* const data, 
    const OD_index_t idx, const OD_subindex_t subidx);

/** Extract Object Directory index and subindex from buffer (at index 0). */
extern int CO_index_extract(const unsigned char* const data, 
    OD_index_t* idx, OD_subindex_t* subidx);

/** Build a can frame buffer with command request 'Initiate SDO Download'. */
extern int CO_SDO_build_init_dl_rq(unsigned char* const buf, 
    const bool e, const bool s, 
    const OD_index_t idx, const OD_subindex_t subidx, const CO_SDO_data_size_t size);

/** Build a can frame buffer with command response 'Initiate SDO Download'. */
extern int CO_SDO_build_init_dl_rp(unsigned char* const buf, 
    const OD_index_t idx, const OD_subindex_t subidx);

/** Build a can frame buffer with command request 'Segment SDO Download'. */
extern int CO_SDO_build_dl_seg_rq(unsigned char* const buf, 
    const bool last, const bool toggle, 
    const unsigned char* const data, const CO_SDO_seg_size_t size);

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
    const CO_SDO_data_size_t size);

/** Build a can frame buffer with command request 'Segment SDO Upload'. */
extern int CO_SDO_build_ul_seg_rq(unsigned char* const buf, 
    const bool toggle);

/** Build a can frame buffer with command response 'Segment SDO Upload'. */
extern int CO_SDO_build_ul_seg_rp(unsigned char* const buf, 
    const bool last, const bool toggle, 
    const unsigned char* const data, const CO_SDO_seg_size_t size);
    
/** Build a can frame buffer with command 'Abort Transfert'. */
extern int CO_SDO_build_abort_transfert(unsigned char* const buf, 
    const OD_index_t idx, const OD_subindex_t subidx, 
    const uint32_t code);

/** Build a can frame buffer with command request 'Initiate SDO Block Download'. */
extern int CO_SDO_build_init_blk_dl_rq(unsigned char* const buf, 
    const bool crc, const bool s, 
    const OD_index_t idx, const OD_subindex_t subidx, const CO_SDO_data_size_t size);

/** Build a can frame buffer with command response 'Initiate SDO Block Download'. */
extern int CO_SDO_build_init_blk_dl_rp(unsigned char* const buf, const bool crc, 
    const OD_index_t idx, const OD_subindex_t subidx, const CO_SDO_blk_size_t blk_sz);

/** Build a can frame buffer with command request 'SDO Download Block Segment'. */
extern int CO_SDO_build_blk_dl_seg_rq(unsigned char* const buf, const bool more,
    const uint8_t seq, const unsigned char* const data, const uint8_t lg);

/** Build a can frame buffer with command response 'SDO Download Block Segment'. */
extern int CO_SDO_build_blk_dl_seg_rp(unsigned char* const buf, 
    const uint8_t seq, const CO_SDO_blk_size_t blk_sz);

/** Build a can frame buffer with command request 'SDO Download Block End'. */
extern int CO_SDO_build_blk_dl_end_rq(unsigned char* const buf, 
    const uint8_t empty, const uint16_t crc);
    
/** Build a can frame buffer with command response 'SDO Download Block End'. */
extern int CO_SDO_build_blk_dl_end_rp(unsigned char* const buf);

/** Build a can frame buffer with command request 'Initiate SDO Block Upload'. */
extern int CO_SDO_build_init_blk_ul_rq(unsigned char* const buf, const bool crc, 
        const OD_index_t idx, const OD_subindex_t subidx, 
        const CO_SDO_blk_size_t blk_sz, const CO_SDO_blk_size_t pst);

/** Build a can frame buffer with command response 'Initiate SDO Block Upload'. */
extern int CO_SDO_build_init_blk_ul_rp(unsigned char* const buf, const bool crc, 
        const OD_index_t idx, const OD_subindex_t subidx, 
        const CO_SDO_data_size_t size);

/** Build a can frame buffer with command request 'Start SDO Block Upload'. */
extern int CO_SDO_build_start_blk_ul_rq(unsigned char* const buf);
        
    
#endif // __CO_SDO_PRIVATE_H__

