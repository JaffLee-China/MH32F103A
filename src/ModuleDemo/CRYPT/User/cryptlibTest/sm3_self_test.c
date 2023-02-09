#include <string.h>
#include <stdio.h>
#include "mh32f10x.h"
#include "mh_sm3.h"
#define c_sm3_len       16
#define c_sm3_msg       "0102030405060708090a0b0c0d0e0f10"
#define c_sm3_hash      "25C9D66ED547714E981BC825B969CC71ACD338F90A4E0F75E789EF71C0921666"



void SM3_Up_Test()
{
    uint16_t  i;
    MHSM3_Context Ctx;
   
    uint8_t buf0[64];
    uint8_t digest[32] = {0};
    printf("Test the sm3 function...\r\n");
    memset(buf0,'a',sizeof(buf0));
    memset(digest,0,32);
    MHSM3_Starts(&Ctx);
    MHSM3_Update(&Ctx,buf0, sizeof(buf0));
    MHSM3_Update(&Ctx,buf0, sizeof(buf0));
    MHSM3_Finish(&Ctx,digest);
//    while(1);
}

uint32_t SM3_local_check(void)
{   
    uint32_t ret = 0;
    
    uint32_t t,i;
    uint8_t Message[16] = {0};
    uint8_t Hash[32] = {0};
    uint8_t _Hash[32] = {0}; 

    bn_read_string_to_bytes(Message, sizeof(Message), c_sm3_msg);
    bn_read_string_to_bytes(_Hash, sizeof(_Hash), c_sm3_hash);
                        
    MHSM3_Cal(Hash, Message, c_sm3_len);
                        
    t = memcmp(Hash, _Hash, sizeof(_Hash));
    
    if(0 != t)
    {
        ret = 1;
        //printf("\nSM3_check check fault!\n");
    }
    
    return ret;
}


void SM3_Test(void)
{
	SM3_Up_Test();
	SM3_local_check();
}












#if 0
void test_SM3(void)
{
    uint32_t t, len;
    char s[40] = {0};
    uint8_t Message0[] = "abc";
    uint8_t Message1[] = "abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcd";
    uint8_t Hash[32];
    uint8_t Len;
    uint8_t mHash0[] = {0x66, 0xC7, 0xF0, 0xF4, 0x62, 0xEE, 0xED, 0xD9, 0xD1, 0xF2, 0xD4, 0x6B, 0xDC, 0x10, 0xE4, 0xE2,
                        0x41, 0x67, 0xC4, 0x87, 0x5C, 0xF2, 0xF7, 0xA2, 0x29, 0x7D, 0xA0, 0x2B, 0x8F, 0x4B, 0xA8, 0xE0}; 
    uint8_t mHash1[] = {0xde, 0xbe, 0x9f, 0xf9, 0x22, 0x75, 0xb8, 0xa1, 0x38, 0x60, 0x48, 0x89, 0xc1, 0x8e, 0x5a, 0x4d,
                        0x6f, 0xdb, 0x70, 0xe5, 0x38, 0x7e, 0x57, 0x65, 0x29, 0x3d, 0xcb, 0xa3, 0x9c, 0x0c, 0x57, 0x32}; 

                        
    uint8_t *pu8In;
    MHSM3_Context ctx;
                        
    DBG_PRINT("\nSM3 Test In\n");
                        
    Len = sizeof(Message0) - 1;
    MHSM3_Cal(Hash, Message0, Len);
    sprintf(s, "SM3 mh_sm3 Test %d\n", Len * 8);
    t = (!memcmp(Hash, mHash0, sizeof(mHash0)));
    r_printf(t, s);

    Len = sizeof(Message1) - 1;
    mh_sm3(Hash, Message1, Len);
    sprintf(s, "SM3 mh_sm3 Test %d\n", Len * 8);
    t = (!memcmp(Hash, mHash1, sizeof(mHash1)));
    r_printf(t, s);
    
                        
    memset(Hash, 0, sizeof(Hash));
    pu8In = Message0;
    len = sizeof(Message0) - 1;                    
    MHSM3_Starts(&ctx);
    MHSM3_Update(&ctx, pu8In, len);
    MHSM3_Finish(&ctx, Hash);
    sprintf(s, "SM3 mh_sm3 Test %d\n", Len * 8);
    t = (!memcmp(Hash, mHash0, sizeof(mHash1)));
    r_printf(t, s);
    
    
    memset(Hash, 0, sizeof(Hash));
    pu8In = Message1;
    len = sizeof(Message1) - 1;                    
    MHSM3_Starts(&ctx);
    MHSM3_Update(&ctx, pu8In, 8);
    MHSM3_Update(&ctx, pu8In + 8, len - 8);
    MHSM3_Finish(&ctx, Hash);
    
    sprintf(s, "SM3 MHSM3_Finish Test %d\n", Len * 8);
    t = (!memcmp(Hash, mHash1, sizeof(mHash1)));
    r_printf(t, s);
    
    //print_hex("Hash:", Hash, sizeof(Hash));
#if USE_TIME_DEBUG
    BEGIN_TEST();
    MHSM3_Cal(Hash, Message0, Len);
    END_TEST();
    DBG_PRINT("Hash_time = %dus\n", t/FCLK);
#endif
}
#endif


//void mh_SM3_update_len(uint8_t *pu8Buff, uint32_t u32Size, uint8_t pu8HashRes[32])
//{
//    uint32_t t, len, i, j, u32P, u32R;
//    uint8_t *pu8In, au8Hash[32];
//    char s[40] = {0};
//    MHSM3_Context ctx;
//    uint8_t au8M[] = {1, 2, 3, 5}; //Test update step table.

//    for(j = 0; j < sizeof(au8M); j++)
//    {
//        pu8In = pu8Buff;
//        memset(au8Hash, 0, sizeof(au8Hash));

//        //Round
//        u32P = u32Size / au8M[j];
//        //Remaind data, left in tail.
//        u32R = u32Size % au8M[j];
//        MHSM3_Starts(&ctx);
//        for(i = 0; i < u32P; i++)
//        {
//            MHSM3_Update(&ctx, pu8In + i * au8M[j], au8M[j]);
//        }
//        MHSM3_Update(&ctx, pu8In + i * au8M[j], u32R);
//        
//        MHSM3_Finish(&ctx, au8Hash);
//        sprintf(s, "SM3 update Test len %d step %d\n", u32Size, au8M[j]);
//        t = (!memcmp(au8Hash, pu8HashRes, sizeof(au8Hash)));
//        r_printf(t, s);
//    }
//}

//void test_SM3(void)
//{
//    uint32_t t, len, i, u32P, u32R, u32M;
//    char s[40] = {0};
//        
//    uint8_t Hash[32];
//    uint8_t *pu8In;
//    MHSM3_Context ctx;
//    
//    
//    uint8_t const au8Message0[] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
//                                    0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
//                                    0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
//                                    0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
//                                    0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
//                                    0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,
//                                    0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
//                                    0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f,
//                                    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,
//                                    0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,
//                                    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,
//                                    0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,
//                                    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,
//                                    0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf,
//                                    0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef,
//                                    0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff,
//                                    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
//                                    0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
//                                    0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
//                                    0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
//                                    0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
//                                    0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,
//                                    0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
//                                    0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f,
//                                    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f};

//    uint8_t au8Hash_300Bytes[32] = {0x11,0xf3,0x94,0x0f,0x10,0xce,0x70,0xef,0x1f,0x7b,0xd8,0x03,0x2b,0x0a,0x72,0x8b,0x11,0x24,0xe5,0x2c,0xe7,0x8c,0x04,0x8f,0x10,0x90,0x36,0x77,0x76,0xfe,0xb2,0xe4};
//    uint8_t au8Hash_54Bytes[32] = {0x1b,0xb1,0xb5,0x92,0x23,0x94,0x47,0xb5,0xde,0x03,0x95,0xd9,0x41,0x59,0x99,0x6e,0xa7,0xcc,0x4f,0xcc,0x7b,0x9f,0x66,0xcc,0xc5,0xf0,0xcf,0xdc,0x89,0x58,0x67,0x82};
//    uint8_t au8Hash_55Bytes[32] = {0xa7,0x9c,0xf9,0xdc,0xee,0x34,0x04,0xab,0xf7,0xf7,0x69,0x69,0x82,0x01,0x64,0x7f,0xd9,0xd3,0xff,0x61,0xd6,0x29,0xd0,0xf5,0x8b,0xb4,0xb5,0x57,0x9a,0x42,0x7d,0xb8};
//    uint8_t au8Hash_56Bytes[32] = {0x62,0xf7,0x36,0x3b,0x15,0xf4,0xde,0x76,0xdd,0x92,0x5c,0x49,0x3b,0x9d,0x6d,0x00,0xd4,0xba,0x0e,0xf2,0xa1,0xf3,0x34,0xc1,0xd0,0xf1,0x3b,0x29,0x3a,0xeb,0x40,0xd1};
//    uint8_t au8Hash_57Bytes[32] = {0x44,0x1F,0x67,0xCC,0x31,0x78,0x1D,0xD2,0x98,0x6F,0xC6,0x12,0xB9,0x2D,0xFA,0xDE,0x87,0x1D,0x81,0x35,0x7F,0x24,0x87,0xF5,0xC8,0x6D,0x94,0xA8,0xC6,0x77,0x8D,0x82};
//    uint8_t au8Hash_64Bytes[32] = {0x93,0x56,0x6F,0x23,0x6D,0x15,0x7A,0xAE,0x07,0x8D,0x1D,0xDB,0x5C,0xEB,0xDB,0xBA,0x15,0x20,0xB5,0x14,0x2E,0x22,0xA8,0x91,0x55,0x64,0x34,0x5B,0xA2,0xAE,0x1D,0x63};
//    uint8_t au8Hash_64_4_54Bytes[32] = {0x5e,0x3c,0x51,0x50,0xf9,0x9f,0x92,0x1a,0x18,0xc8,0x4a,0x25,0x19,0xed,0xc6,0x25,0xe8,0xd5,0xc7,0x21,0x25,0x18,0x02,0x17,0x8d,0xa7,0x90,0x83,0x53,0xbe,0xd0,0xfe};
//    uint8_t au8Hash_64_4_55Bytes[32] = {0xbd,0xc8,0xf8,0x3e,0xbb,0xcd,0x14,0x02,0xbe,0x68,0xab,0x38,0x87,0x98,0x71,0x30,0x18,0xf0,0x40,0x30,0x15,0x92,0x18,0xf2,0x4e,0xe2,0xd7,0xc6,0xd7,0x1c,0xa1,0xf2};
//    uint8_t au8Hash_64_4_56Bytes[32] = {0x53,0xc5,0x7a,0xa4,0xaa,0xd0,0x18,0x0c,0xe1,0x07,0x01,0x73,0x96,0x0e,0xfb,0x0f,0xe0,0xd2,0x40,0xe4,0x57,0x42,0x66,0x3c,0x20,0x2e,0x48,0xe9,0x96,0x14,0xde,0x73};
//    uint8_t au8Hash_64_4_57Bytes[32] = {0xEF,0x11,0x6B,0xEE,0x6D,0xB8,0x6A,0x7E,0x04,0x9A,0x63,0x27,0x60,0x2F,0xA0,0x4A,0x36,0xAC,0xC2,0xB3,0xEE,0x0C,0xB5,0xD2,0x81,0x62,0xE9,0x76,0x8F,0x0A,0x27,0x74};
//    
//    
//    
//        
//    DBG_PRINTF("\n%s\n",__func__);
//            
//    memset(Hash, 0, sizeof(Hash));
//    MHSM3_Cal(Hash, (uint8_t *)au8Message0, 300);
//    sprintf(s, "SM3 mh_sm3 Test %d\n", 300 * 8);
//    t = (!memcmp(Hash, au8Hash_300Bytes, sizeof(Hash)));
//    r_printf(t, s);

//    memset(Hash, 0, sizeof(Hash));
//    MHSM3_Cal(Hash, (uint8_t *)au8Message0, 54);
//    sprintf(s, "SM3 mh_sm3 Test %d\n", 54 * 8);
//    t = (!memcmp(Hash, au8Hash_54Bytes, sizeof(Hash)));
//    r_printf(t, s);
//        
//    memset(Hash, 0, sizeof(Hash));
//    MHSM3_Cal(Hash, (uint8_t *)au8Message0, 55);
//    sprintf(s, "SM3 mh_sm3 Test %d\n", 55 * 8);
//    t = (!memcmp(Hash, au8Hash_55Bytes, sizeof(Hash)));
//    r_printf(t, s);
//    
//    memset(Hash, 0, sizeof(Hash));
//    MHSM3_Cal(Hash, (uint8_t *)au8Message0, 56);
//    sprintf(s, "SM3 mh_sm3 Test %d\n", 56 * 8);
//    t = (!memcmp(Hash, au8Hash_56Bytes, sizeof(Hash)));
//    r_printf(t, s);
//    
//    memset(Hash, 0, sizeof(Hash));
//    MHSM3_Cal(Hash, (uint8_t *)au8Message0, 57);
//    ouputArrayHex("sm3 57\n", Hash, 32);
//    sprintf(s, "SM3 mh_sm3 Test %d\n", 57 * 8);
//    t = (!memcmp(Hash, au8Hash_57Bytes, sizeof(Hash)));
//    r_printf(t, s);
//    
//    memset(Hash, 0, sizeof(Hash));
//    MHSM3_Cal(Hash, (uint8_t *)au8Message0, 64);
//    ouputArrayHex("sm3 64\n", Hash, 32);
//    sprintf(s, "SM3 mh_sm3 Test %d\n", 64 * 8);
//    t = (!memcmp(Hash, au8Hash_64Bytes, sizeof(Hash)));
//    r_printf(t, s);
//    
//    memset(Hash, 0, sizeof(Hash));
//    MHSM3_Cal(Hash, (uint8_t *)au8Message0, 64*4+54);
//    sprintf(s, "SM3 mh_sm3 Test %d\n", (64*4+54) * 8);
//    t = (!memcmp(Hash, au8Hash_64_4_54Bytes, sizeof(Hash)));
//    r_printf(t, s);
//    
//    memset(Hash, 0, sizeof(Hash));
//    MHSM3_Cal(Hash, (uint8_t *)au8Message0, 64*4+55);
//    sprintf(s, "SM3 mh_sm3 Test %d\n", (64*4+55) * 8);
//    t = (!memcmp(Hash, au8Hash_64_4_55Bytes, sizeof(Hash)));
//    r_printf(t, s);
//    
//    memset(Hash, 0, sizeof(Hash));
//    MHSM3_Cal(Hash, (uint8_t *)au8Message0, 64*4+56);
//    sprintf(s, "SM3 mh_sm3 Test %d\n", (64*4+56) * 8);
//    t = (!memcmp(Hash, au8Hash_64_4_56Bytes, sizeof(Hash)));
//    r_printf(t, s);
//    
//    memset(Hash, 0, sizeof(Hash));
//    MHSM3_Cal(Hash, (uint8_t *)au8Message0, 64*4+57);
//    ouputArrayHex("sm3 64 * 4 + 57\n", Hash, 32);
//    sprintf(s, "SM3 mh_sm3 Test %d\n", (64*4+57) * 8);
//    t = (!memcmp(Hash, au8Hash_64_4_57Bytes, sizeof(Hash)));
//    r_printf(t, s);
//    
//    
//    mh_SM3_update_len((uint8_t *)au8Message0, 54, au8Hash_54Bytes);
//    mh_SM3_update_len((uint8_t *)au8Message0, 55, au8Hash_55Bytes);
//    mh_SM3_update_len((uint8_t *)au8Message0, 56, au8Hash_56Bytes);
//    mh_SM3_update_len((uint8_t *)au8Message0, 57, au8Hash_57Bytes);
//    
//    mh_SM3_update_len((uint8_t *)au8Message0, 64*4+54, au8Hash_64_4_54Bytes);
//    mh_SM3_update_len((uint8_t *)au8Message0, 64*4+55, au8Hash_64_4_55Bytes);
//    mh_SM3_update_len((uint8_t *)au8Message0, 64*4+56, au8Hash_64_4_56Bytes);
//    mh_SM3_update_len((uint8_t *)au8Message0, 64*4+57, au8Hash_64_4_57Bytes);
//    
//}