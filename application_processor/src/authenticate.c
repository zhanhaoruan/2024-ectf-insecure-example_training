#include <stdint.h>
#include <string.h>
#include "board_link.h"
#include "mxc_device.h"
#include "nvic_table.h"
#include "trng.h"

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

void key_update(char* random, char* old_key){
    /*
    
    XOR the old key with the random, which passed in from the new_key_buffer
    Write the result of this XOR to the old_key location
    return
    */
    char new_key[16];
    new_key = old_key ^ random;
    strncpy(old_key, new_key, 16);
    return;
}

void gen_random(char* buffer, int length){
    uint8_t var_rnd_no[length] = { 0 };
    MXC_TRNG_Init();
    MXC_TRNG_Random(var_rnd_no, length);

    //write back to the buffer
    strncpy(buffer,var_rnd_no,length);
}

void enc(char* message, char* key){
    //complete byt John 
    ;
}

void dec(char* cipher, char* key){
    //complete byt John 
    ;
}

int authenticate(uint32_t deviceid, char* key, char* rand){
    /*
    1. send out the random buffer
    2. wait for devices' response
    3. check device ID 
    */

   char* message[16];
   strncpy(message,rand,16);

   //convert deviceID to I2CAddr
    i2c_addr_t addr= component_id_to_i2c_addr(deviceid);

   //send out the random_number
    enc(message,key);
    send_packet(addr, 16, message);

    //wait to receive the packet
    poll_and_receive_packet(addr, message);
    dec(message,key);

    //check ID
    return strncmp(message,(char*) &deviceid, 4);
}













char auth_ap(uint32_t componentID1 ,uint32_t componentID1, char* key){
    char* buffer[16]; //this completes the key updating process
    char* rand_buffer[16]; //this is to send random to the devices
    gen_random(buffer,16);
    strncpy(rand_buffer,buffer,16);
    key_update(buffer,key);
    return (authenticate(device1,key,rand_buffer) & authenticate(device2,key,rand_buffer));
}