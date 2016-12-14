
#include <stdio.h>
#include <private/CO_SDO_p.h>

static unsigned char can_buff[CO_CAN_FRAME_DATA_MAX];

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

#define TEST_CASE(buf,seq,size,exp,comp)            \
    ret=CO_SDO_build_blk_dl_seg_rp(buf,seq,size); \
    if(ret!=exp) {                                      \
        fprintf(stderr,                                 \
            "%d: CO_SDO_build_blk_dl_seg_rp failed, error(%d), expected(%d)\n",    \
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
    
static const unsigned char compare_buf1[] = { 0xA2, 54, 0x5F, 0, 0, 0, 0, 0 } ;
static const unsigned char compare_buf2[] = { 0xA2, 65, 0x7E, 0, 0, 0, 0, 0 } ;
static const unsigned char compare_buf3[] = { 0xA2, 100, 0x6A, 0, 0, 0, 0, 0 } ;
static const unsigned char compare_buf4[] = { 0xA2, 127, 0x3B, 0, 0, 0, 0, 0 } ;
    
int main(void) {
    int ret=0;
        
    TEST_CASE(0, 0, 0, CO_ERROR_NULL_PTR, 0)
    TEST_CASE(can_buff, 0, 0, CO_ERROR_BAD_ARGS, 0)
    TEST_CASE(can_buff, 128, 0, CO_ERROR_DATA_OVERFLOW, 0)
    TEST_CASE(can_buff, 34, 0, CO_ERROR_BAD_ARGS, 0)
    TEST_CASE(can_buff, 34, 128, CO_ERROR_DATA_OVERFLOW, 0)

    TEST_CASE(can_buff, 54, 0x5F, CO_ERROR_NONE, compare_buf1)
    TEST_CASE(can_buff, 65, 0x7E, CO_ERROR_NONE, compare_buf2)
    TEST_CASE(can_buff, 100, 0x6A, CO_ERROR_NONE, compare_buf3)
    TEST_CASE(can_buff, 127, 0x3B, CO_ERROR_NONE, compare_buf4)
    
    return 0;
}
