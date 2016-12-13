
#include <stdio.h>
#include <private/CO_SDO_p.h>

static unsigned char can_buff[CO_CAN_DATA_MAX];
static OD_index_t idx=0x1605;
static OD_subindex_t subidx=7;

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
    for(int i=0; i<CO_CAN_DATA_MAX; i++)
        fprintf(stderr, "%02x ", buf[i]);
    fprintf(stderr, "\n");
}

#define TEST_CASE(buf,idx,subidx,exp,comp)              \
    ret=CO_SDO_build_init_dl_rp(buf,idx,subidx); \
    if(ret!=exp) {                                      \
        fprintf(stderr,                                 \
            "%d: CO_SDO_build_init_dl_rp failed, error(%d), expected(%d)\n",    \
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

static const unsigned char compare_buf1[] = { 0x60, 0x05, 0x16, 0x07, 0x00, 0x00, 0x00, 0x00 } ;

    
int main(void) {
    int ret=0;
        
    // TEST_CASE(0, 0, 0, CO_ERROR_NULL_PTR,0)
    TEST_CASE(can_buff, idx, subidx, CO_ERROR_NONE, compare_buf1)
    
    return 0;
}