
#include <stdio.h>
#include <private/CO_SDO_p.h>

static unsigned char can_buff[CO_CAN_DATA_MAX];
static OD_index_t idx=0x1A03;
static OD_subindex_t subidx=13;

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

#define TEST_CASE(buf,t,s,idx,subidx,lg,exp,comp)            \
    ret=CO_SDO_build_init_dl_rq(buf,t,s,idx,subidx,lg); \
    if(ret!=exp) {                                      \
        fprintf(stderr,                                 \
            "%d: CO_SDO_build_init_dl_rq failed, error(%d), expected(%d)\n",    \
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
    

static const unsigned char compare_buf1[] = { 0x21, 0x03, 0x1a, 0x0d, 0x34, 0x12, 0x00, 0x00 } ;
static const unsigned char compare_buf2[] = { 0x21, 0x03, 0x1a, 0x0d, 0x12, 0x00, 0x00, 0x00 } ;
static const unsigned char compare_buf3[] = { 0x21, 0x03, 0x1a, 0x0d, 0x45, 0x23, 0x01, 0x00 } ;
static const unsigned char compare_buf4[] = { 0x21, 0x03, 0x1a, 0x0d, 0x56, 0x34, 0x12, 0x00 } ;
static const unsigned char compare_buf5[] = { 0x21, 0x03, 0x1a, 0x0d, 0x67, 0x45, 0x23, 0x01 } ;
static const unsigned char compare_buf6[] = { 0x2F, 0x03, 0x1a, 0x0d, 0x01, 0x00, 0x00, 0x00 } ;
    
int main(void) {
    int ret=0;
        
    TEST_CASE(0, 0, 0, 0, 0, 0, CO_ERROR_NULL_PTR, 0)
    TEST_CASE(can_buff, 0, 1, idx, subidx, 0, CO_ERROR_BAD_ARGS, 0)
    TEST_CASE(can_buff, 0, 0, idx, subidx, 1024, CO_ERROR_BAD_ARGS, 0)
    TEST_CASE(can_buff, 0, 1, idx, subidx, 0x1234, CO_ERROR_NONE, compare_buf1)
    TEST_CASE(can_buff, 0, 1, idx, subidx, 0x12, CO_ERROR_NONE, compare_buf2)
    TEST_CASE(can_buff, 0, 1, idx, subidx, 0x12345, CO_ERROR_NONE, compare_buf3)
    TEST_CASE(can_buff, 0, 1, idx, subidx, 0x123456, CO_ERROR_NONE, compare_buf4)
    TEST_CASE(can_buff, 0, 1, idx, subidx, 0x1234567, CO_ERROR_NONE, compare_buf5)
    TEST_CASE(can_buff, 1, 1, idx, subidx, 0x01, CO_ERROR_NONE, compare_buf6)
    
    return 0;
}
