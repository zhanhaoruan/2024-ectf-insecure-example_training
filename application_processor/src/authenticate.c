#include <stdint.h>

typedef struct {
    uint32_t flash_magic;
    uint32_t component_cnt;
    uint32_t component_ids[32];
    uint8_t key[16];
} flash_entry;

extern flash_entry flash_status;

void XOR(char*oprand1, char* operand2, char* dest,int length){
    int i;
    for(i=0;i<length;++i){
        dest[i]=oprand1[i]^operand2[i];
    }
    
    return; //rtn x86, br RX arm cortex M4F
}

void key_update(char* newkey){
    ;
}

void gen_random(char* buffer, int length){
    ;
}

void enc(char* message, char* key){
    ;
}

int authenticate(i2c_addr_t device){
    ;
}













char auth_ap(i2c_addr_t device1 ,i2c_addr_t device2){
    return (authenticate(device1) & authenticate(device2));
}