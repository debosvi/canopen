
#include <stdio.h>
#include <private/CO_SDO_p.h>

static unsigned char can_buff[CO_CAN_DATA_MAX];

static int compare_buffers(unsigned char* b1, unsigned char* b2) {
    int ret=0;

    if(!b1 || !b2) return CO_CAN_DATA_MAX;
    for(int i=0; i<CO_CAN_DATA_MAX; i++) {
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
    for(int i=0; i<CO_CAN_DATA_MAX; i++)
        fprintf(stderr, "%02x ", buf[i]);
    fprintf(stderr, "\n");
}

#define TEST_CASE(buf,toggle,exp,comp)              \
    ret=CO_SDO_build_dl_seg_rp(buf,toggle); \
    if(ret!=exp) {                                      \
        fprintf(stderr,                                 \
            "%d: CO_SDO_build_dl_seg_rp failed, error(%d), expected(%d)\n",    \
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

static const unsigned char compare_buf1[] = { 0x20, 0, 0, 0, 0, 0, 0, 0 } ;
static const unsigned char compare_buf2[] = { 0x30, 0, 0, 0, 0, 0, 0, 0 } ;
    
int main(void) {
    int ret=0;
        
    TEST_CASE(0, 0, CO_ERROR_NULL_PTR, 0)
    TEST_CASE(can_buff, 0, CO_ERROR_NONE, compare_buf1)
    TEST_CASE(can_buff, 1, CO_ERROR_NONE, compare_buf2)
    
    return 0;
}