
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

#define TEST_CASE(buf,last,toggle,data,lg,exp,comp)              \
    ret=CO_SDO_build_dl_seg_rq(buf,last,toggle,data,lg); \
    if(ret!=exp) {                                      \
        fprintf(stderr,                                 \
            "%d: CO_SDO_build_dl_seg_rq failed, error(%d), expected(%d)\n",    \
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

static const unsigned char fill_data[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

static const unsigned char compare_buf1[] = { 0x0E, 0, 0, 0, 0, 0, 0, 0 } ;
static const unsigned char compare_buf2[] = { 0x00, 0, 1, 2, 3, 4, 5, 6 } ;
static const unsigned char compare_buf3[] = { 0x07, 1, 2, 3, 4, 0, 0, 0 } ;
static const unsigned char compare_buf4[] = { 0x14, 2, 3, 4, 5, 6, 0, 0 } ;
static const unsigned char compare_buf5[] = { 0x1D, 3, 0, 0, 0, 0, 0, 0 } ;
    
int main(void) {
    int ret=0;
        
    TEST_CASE(0, 0, 0, 0, 0, CO_ERROR_NULL_PTR, 0)
    TEST_CASE(can_buff, 0, 0, 0, 0, CO_ERROR_NONE, compare_buf1)
    TEST_CASE(can_buff, 0, 0, fill_data, 10, CO_ERROR_DATA_OVERFLOW, 0)
    TEST_CASE(can_buff, 0, 0, fill_data, 0, CO_ERROR_BAD_ARGS, 0)
    TEST_CASE(can_buff, 0, 0, 0, 6, CO_ERROR_BAD_ARGS, 0)
    TEST_CASE(can_buff, 0, 0, fill_data, 7, CO_ERROR_NONE, compare_buf2)
    TEST_CASE(can_buff, 1, 0, fill_data+1, 4, CO_ERROR_NONE, compare_buf3)
    TEST_CASE(can_buff, 0, 1, fill_data+2, 5, CO_ERROR_NONE, compare_buf4)
    TEST_CASE(can_buff, 1, 1, fill_data+3, 1, CO_ERROR_NONE, compare_buf5)
    
    return 0;
}