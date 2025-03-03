/**
  ******************************************************************************
  * @file    usb_desc.c
  * @author  NONE
  * @version NONE
  * @date    NONE
  * @brief   NONE
  ******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "usb_desc.h"
#include "platform_config.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
uint8_t DFU_DeviceDescriptor[DFU_SIZ_DEVICE_DESC] =
  {
    0x12,   /* bLength */
    0x01,   /* bDescriptorType */
    0x00,   /* bcdUSB, version 1.00 */
    0x01,
    0x00,   /* bDeviceClass : See interface */
    0x00,   /* bDeviceSubClass : See interface*/
    0x00,   /* bDeviceProtocol : See interface */
    bMaxPacketSize0, /* bMaxPacketSize0 0x40 = 64 */
    0x83,   /* idVendor     (0483) */
    0x04,
    0x11,   /* idProduct (0xDF11) DFU PiD*/
    0xDF,
    0x00,   /* bcdDevice*/
    0x22,

    0x01,   /* iManufacturer : index of string Manufacturer  */
    0x02,   /* iProduct      : index of string descriptor of product*/
    0x03,   /* iSerialNumber : index of string serial number*/

    0x01    /*bNumConfigurations */
  };


uint8_t DFU_ConfigDescriptor[DFU_SIZ_CONFIG_DESC] =
  {
    0x09,   /* bLength: Configuration Descriptor size */
    0x02,   /* bDescriptorType: Configuration */
    DFU_SIZ_CONFIG_DESC, /* wTotalLength: Bytes returned */
    0x00,
    0x01,   /* bNumInterfaces: 1 interface */
    0x01,   /* bConfigurationValue: */
    /*      Configuration value */
    0x00,   /* iConfiguration: */
    /*      Index of string descriptor */
    /*      describing the configuration */
    0x80,   /* bmAttributes: */
    /*      bus powered */
    0x20,   /* MaxPower 100 mA: this current is used for detecting Vbus */
    /* 09 */

    /************ Descriptor of DFU interface 0 Alternate setting 0 *********/
    0x09,   /* bLength: Interface Descriptor size */
    0x04,   /* bDescriptorType: */
    /*      Interface descriptor type */
    0x00,   /* bInterfaceNumber: Number of Interface */
    0x00,   /* bAlternateSetting: Alternate setting */
    0x00,   /* bNumEndpoints*/
    0xFE,   /* bInterfaceClass: Application Specific Class Code */
    0x01,   /* bInterfaceSubClass : Device Firmware Upgrade Code */
    0x02,   /* nInterfaceProtocol: DFU mode protocol */
    0x04,   /* iInterface: */
    /* Index of string descriptor */
    /* 18 */
    
    /************ Descriptor of DFU interface 0 Alternate setting 1  **********/

    0x09,   /* bLength: Interface Descriptor size */
    0x04,   /* bDescriptorType: */
    /*      Interface descriptor type */
    0x00,   /* bInterfaceNumber: Number of Interface */
    0x01,   /* bAlternateSetting: Alternate setting */
    0x00,   /* bNumEndpoints*/
    0xFE,   /* bInterfaceClass: Application Specific Class Code */
    0x01,   /* bInterfaceSubClass : Device Firmware Upgrade Code */
    0x02,   /* nInterfaceProtocol: DFU mode protocol */
    0x05,   /* iInterface: */
    /* Index of string descriptor */
    /* 27 */    
    
    /******************** DFU Functional Descriptor********************/
    0x09,   /*blength = 9 Bytes*/
    0x21,   /* DFU Functional Descriptor*/
    0x0B,   /*bmAttribute

    bitCanDnload             = 1      (bit 0)
    bitCanUpload             = 1      (bit 1)
    bitManifestationTolerant = 0      (bit 2)
    bitWillDetach            = 1      (bit 3)
    Reserved                          (bit4-6)
    bitAcceleratedST         = 0      (bit 7)*/
    0xFF,   /*DetachTimeOut= 255 ms*/
    0x00,
    wTransferSizeB0,
    wTransferSizeB1,          /* TransferSize = 1024 Byte*/
    0x1A,                     /* bcdDFUVersion*/
    0x01
    /***********************************************************/
    /*36*/

  };

uint8_t DFU_StringLangId[DFU_SIZ_STRING_LANGID] =
  {
    DFU_SIZ_STRING_LANGID,
    0x03,
    0x09,
    0x04    /* LangID = 0x0409: U.S. English */
  };


uint8_t DFU_StringVendor[DFU_SIZ_STRING_VENDOR] =
  {
    DFU_SIZ_STRING_VENDOR,
    0x03,
    /* Manufacturer: "MHSEMICONDUCTOR " */
    'M', 0, 'E', 0, 'G', 0, 'A', 0, 'H', 0, 'U', 0, 'N', 0, 'T', 0,
  };

uint8_t DFU_StringProduct[DFU_SIZ_STRING_PRODUCT] =
  {
    DFU_SIZ_STRING_PRODUCT,
    0x03,
    /* Product name: "MH32 DFU" */
    'M', 0, 'H', 0, '3', 0, '2', 0, ' ', 0, 'D', 0, 'F', 0, 'U', 0
  };

uint8_t DFU_StringSerial[DFU_SIZ_STRING_SERIAL] =
  {
    DFU_SIZ_STRING_SERIAL,
    0x03,
    /* Serial number */
    'M', 0, 'H', 0, '3', 0, '2', 0  
  };

uint8_t DFU_StringInterface0[DFU_SIZ_STRING_INTERFACE0] =
  {
    DFU_SIZ_STRING_INTERFACE0,
    0x03,
    // Interface 0: "@Internal Flash   /0x08000000/128*002Kg"
    '@', 0, 'I', 0, 'n', 0, 't', 0, 'e', 0, 'r', 0, 'n', 0, 'a', 0, 'l', 0,  /* 18 */
    ' ', 0, 'F', 0, 'l', 0, 'a', 0, 's', 0, 'h', 0, ' ', 0, ' ', 0, /* 16 */
    '/', 0, '0', 0, 'x', 0, '0', 0, '8', 0, '0', 0, '0', 0, '0', 0, '0', 0, '0', 0, '0', 0, /* 22 */
    '/', 0, '1', 0, '2', 0, '8', 0, '*', 0, '0', 0, '0', 0, '2', 0, 'K', 0, 'g', 0,     /* 20 */
  };
uint8_t DFU_StringInterface1[DFU_SIZ_STRING_INTERFACE1] =
  {
    DFU_SIZ_STRING_INTERFACE1,
    0x03,
    // Interface 0: "@Option Bytes  /0x1FFFF800/01*016 e"
    '@', 0, 'O', 0, 'p', 0, 't', 0, 'i', 0, 'o', 0, 'n', 0, ' ', 0,  /* 16 */
    'B', 0, 'y', 0, 't', 0, 'e', 0, 's', 0, ' ', 0, ' ', 0,  /* 14 */
    '/', 0, '0', 0, 'x', 0, '1', 0, 'F', 0, 'F', 0, 'F', 0, 'F', 0, '8', 0, '0', 0, '0', 0,  /* 22 */
    '/', 0, '0', 0, '1', 0, '*', 0, '0', 0, '1', 0, '6', 0, ' ', 0, 'e', 0,  /* 18 */
  };

/******************* (C) COPYRIGHT  MHSEMICONDUCTOR *****END OF FILE****/
