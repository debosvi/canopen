
#include <stdio.h>
#include <private/CO_SDO_p.h>

static unsigned char can_buff[CO_CAN_FRAME_DATA_MAX];
static OD_index_t idx=0x18F7;
static OD_subindex_t subidx=1;

static int compare_buffers(unsigned char* b1, unsigned char* b2) {
    int ret=0;

    if(!b1 || !b2) return CO_CAN_FRAME_DATA_MAX;
    for(int i=0; i<CO_CAN_FRAME_DATA_MAX; i++) {
        if(b1[i]!=b2[i]) {
            fprintf(stderr, " ^ ");
            ret++;
        }
        else { 
            fprintf(stderr, "   ");
        }
    }
    fprintf(stderr, "\n");
    return ret;
}

static void print_buffer(unsigned char* buf) {
    if(!buf) return;
    for(int i=0; i<CO_CAN_FRAME_DATA_MAX; i++)
        fprintf(stderr, "%02x ", buf[i]);
    fprintf(stderr, "\n");
}

#define TEST_CASE(buf,crc,idx,subidx,sz,exp,comp)              \
    ret=CO_SDO_build_init_blk_dl_rp(buf,crc,idx,subidx,sz); \
    if(ret!=exp) {                                      \
        fprintf(stderr,                                 \
            "%d: CO_SDO_build_init_blk_dl_rp failed, error(%d), expected(%d)\n",    \
            __LINE__, ret, exp);                        \
        return 1;                                       \
    }                                                   \
    else {                                              \
        int diff=0;                                     \
        print_buffer(buf);                              \
        if(ret==CO_ERROR_NONE)                          \
            diff=compare_buffers(buf, (unsigned char*)comp); \
        if(diff) {                                      \
            fprintf(stderr,                             \
            "%d: buffers differs with (%d) mismatches\n",    \
            __LINE__, diff);                            \
            fprintf(stderr, "%d: test KO\n", __LINE__); \
        }                                               \
        else {                                          \
            fprintf(stderr, "%d: test OK\n", __LINE__); \
        }                                               \
    }                                                     

static const unsigned char compare_buf1[] = { 0xC0, 0xF7, 0x18, 0x01, 0xC5, 0x00, 0x00, 0x00 } ;
static const unsigned char compare_buf2[] = { 0xC4, 0xF7, 0x18, 0x01, 0xF4, 0x00, 0x00, 0x00 } ;
    
int main(void) {
    int ret=0;
        
    TEST_CASE(0, 0, 0, 0, 0, CO_ERROR_NULL_PTR, 0)
    TEST_CASE(can_buff, 0, idx, subidx, 0, CO_ERROR_BAD_ARGS, 0)
    TEST_CASE(can_buff, 1, idx, subidx, 0, CO_ERROR_BAD_ARGS, 0)
    TEST_CASE(can_buff, 0, idx, subidx, 0xC5, CO_ERROR_NONE, compare_buf1)
    TEST_CASE(can_buff, 1, idx, subidx, 0xF4, CO_ERROR_NONE, compare_buf2)
    
    return 0;
}
