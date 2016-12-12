
#include <stdio.h>
#include <private/CO_SDO_p.h>

static char can_buff[8];
static OD_index_t idx=0x1A03;
static OD_subindex_t subidx=13;

static void print_buffer(char* buf) {
    for(int i=0; i<8; i++)
        fprintf(stderr, "%02x ", buf[i]);
    fprintf(stderr, "\n");
}

int main(void) {
    int ret=0;
        
    ret=CO_SDO_build_init_dl_rq(can_buff, 0, 1, idx, subidx, 0);
    if(ret!=2) {
        fprintf(stderr, "CO_SDO_build_init_dl_rq failed, error(%d), expected(2)\n", ret);
        return 1;
    }
    
    ret=CO_SDO_build_init_dl_rq(can_buff, 0, 0, idx, subidx, 1024);
    if(ret!=2) {
        fprintf(stderr, "CO_SDO_build_init_dl_rq failed, error(%d), expected(2)\n", ret);
        return 1;
    }
        
    ret=CO_SDO_build_init_dl_rq(can_buff, 0, 1, idx, subidx, 0x1234);
    if(ret) {
        fprintf(stderr, "CO_SDO_build_init_dl_rq failed, error(%d), expected(0)\n", ret);
        return 1;
    }
    print_buffer(can_buff);
    
    ret=CO_SDO_build_init_dl_rq(can_buff, 1, 1, idx, subidx, 0x12);
    if(ret) {
        fprintf(stderr, "CO_SDO_build_init_dl_rq failed, error(%d), expected(0)\n", ret);
        return 1;
    }
    print_buffer(can_buff);
    
    ret=CO_SDO_build_init_dl_rq(can_buff, 1, 1, idx, subidx, 0x12345);
    if(ret) {
        fprintf(stderr, "CO_SDO_build_init_dl_rq failed, error(%d), expected(0)\n", ret);
        return 1;
    }
    print_buffer(can_buff);
    
    ret=CO_SDO_build_init_dl_rq(can_buff, 1, 1, idx, subidx, 0x123456);
    if(ret) {
        fprintf(stderr, "CO_SDO_build_init_dl_rq failed, error(%d), expected(0)\n", ret);
        return 1;
    }
    print_buffer(can_buff);
    
    ret=CO_SDO_build_init_dl_rq(can_buff, 1, 1, idx, subidx, 0x1234567);
    if(ret) {
        fprintf(stderr, "CO_SDO_build_init_dl_rq failed, error(%d), expected(0)\n", ret);
        return 1;
    }
    print_buffer(can_buff);
    
    return 0;
}