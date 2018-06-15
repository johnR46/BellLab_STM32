/****************************************Copyright (c)****************************************************
**
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Main.c
** Descriptions:            The ADC application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-10-30
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x.h"
#include "systick.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h> //strtol
#include "stm32f10x_spi.h"
#include <math.h>
#include <stdlib.h>



#define RCC_APB2Periph_GPIO_SPI_FLASH_CS      RCC_APB2Periph_GPIOD
#define SPI_DISPLAY_CS_PORT                     GPIOD
#define SPI_DISPLAY_CS_PIN                      GPIO_Pin_4

//--------------------------------spi display----------------------------------
#define SPI_DISPLAY_CS_LOW()       GPIO_ResetBits(GPIOD, GPIO_Pin_4) //SPI_FLASH_CS_LOW
#define SPI_DISPLAY_CS_HIGH()      GPIO_SetBits(GPIOD, GPIO_Pin_4)   //SPI_FLASH_CS_HIGH


//--------------------------------spi flash------------------------------------
#define SPI_FLASH_CS_LOW()     GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define SPI_FLASH_CS_HIGH()    GPIO_SetBits(GPIOA, GPIO_Pin_4)

void writeFlash(int address, int size);
void writeFlash2(int address, int size);
int addressWriteFlashTemp = 0x0;
int strLength = 0;
int countSector4096 = 0;
int countSector = 0;
int addressSector = 0x00;
int endReadFile = 0;
char buffer22Char[22];
int pointer22char = 0;
int pointerSector = 0;
int jumpLECR = 0;
int AmountSector = 0;
int AmountSectorT = 0;

uint16_t * str;
char buffer[6];
unsigned int BLEConBuffer[30];
int keyCodeRecieve[7];
int countKey = 0;
int seeHead = 0;
int maxData = 7;
//const char* bufferCharPointerForConvertToInt;
//const char *hexstring = &buffer[0];
//const unsigned char menu[] = " Welcome to CooCox!\r\n";
int i = 0, j = 0, k = 0;
int i1 = 0, j1 = 0, count1 = 0; //uart2
int uart2Buffer = 0;
int maxSize = 5;
int count = 0;
int count2 = 0;
int Hex;
int isHex = 0; // if equal 1 is hex, or equal 2 is Switch
int itFirst = 0;
int BLEConn = 0;
int pushToDisplay = 0;
int countConn = 0;

int bufferKey3digit[3] = {0};

int hexbuffer = 0;
int hexPrep = 0;
int SeeHead = 0;
int dataLength = 0;

//---------------------- menu variable ----------------------
int count_menu = 1;
int maxMenu = 8;
int menu[6] = {0x01, 0x02, 0x04, 0x80, 0x04, 0x02};

int countMenuInReadMode = 0;


int st_bluetooth[] = {0x43, 0x07, 0x25, 0x11, 0x1e, 0x15, 0x15, 0x1e, 0x13}; //bluetooth
int st_0[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
//0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
int st_notepad[] = {0x1d, 0x15, 0x1e, 0x11, 0x0f, 0x01, 0x19};//notepad
int st_notepad_mode[] = {0x1d, 0x15, 0x1e, 0x11, 0x0f, 0x01, 0x19, 0x00, 0x0d, 0x15, 0x19, 0x11};
int st_filemanage[] = {0x0b, 0x0a, 0x07, 0x11, 0x0d, 0x01, 0x1d, 0x01, 0x1b, 0x11};
int st_read[] = {0x17, 0x11, 0x01, 0x19};
int st_usbconnect[] = {0x25, 0x0e, 0x03, 0x00, 0x09, 0x15, 0x1d, 0x1d, 0x11, 0x09 , 0x1e};
int st_clock[] = {0x09, 0x07, 0x15, 0x09, 0x05};
int st_calcu[] = {0x09, 0x01, 0x07, 0x09, 0x25, 0x07, 0x01, 0x1e, 0x15, 0x17};
int st_tools[] = {0x1e, 0x15, 0x15, 0x07, 0x0e};
int fullScreen[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
int read_mode[] = {0x57, 0x51, 0x41, 0x59, 0x00, 0x4d, 0x55, 0x59, 0x51};
int bigL[] = {0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47, 0x47};
int mode_1[4] = {0x00, 0x01, 0x02};
int mode = 0 ; //1,2,3,4,5,6,7,8

int checkKeyError = 0;
int keyCode = 0;
int previousMode = 0;
//----------------------------------------- BLE data --------------------------------------------------//
////////////////////////////////////////////
//54 53 53 4d 20 56 31 2e 30  --TSSM V1.0 //
//53 4c 52 49 20 56 31 2e 30  --SLRI V1.0 //
////////////////////////////////////////////
int connectData[] = {0xff, 0xff, 0xa2, 0x0b, 0x16, 0x14, 0x10, 0x53 , 0x4c , 0x52 , 0x49 , 0x20 , 0x56 , 0x31 , 0x2e , 0x30};
int navRight[] = {0xff, 0xff, 0xa6, 0x03, 0x00, 0x08, 0x00};
int navLeft[] = {0xff, 0xff, 0xa6, 0x03, 0x00, 0x04, 0x00};

//-----------------------------------------End BLE data-----------------------------------------------//
//-----------------------------------------ch370s data------------------------------------------------//
int changeBaudRateByte[] = {0x00, 0x57, 0xab, 0x02, 0x03, 0xcc};
int countSector512 = 0;
int countRoundSector512 = 0;
int countCounitueRead = 0; //512 ,round =24
char bufferFromRead[25] = "";
char bufferPrevoisRead[1000][25];
int CountbufferFromRead = 0;
int startRead = 0;
int countPageWhenRead = 0;
int continueReadFile = 0;
int openFileStatus = 0;
int readstatus = 0;
int becon = 0;


//--readmode
char dataTemp512[512];
int countdataTemp512 = 0;
int waitEnd = 0; // 10
int lastAscii = 0;

int searchStep = 0;
int stepCount = 0;
int r_count = 0;
int nextAgain = 0;
int countFileLegth = 0;
char prepareNameToOpen[] = "";


int SetByteRead[] = {0x00, 0x57, 0xab, 0x3a, 0x80, 0x00}; //15 = 21 character
int SetByteRead6char[] = {0x00, 0x57, 0xab, 0x3a, 0x06, 0x00};
int ReadData[] = {0x00, 0x57, 0xAB, 0x27};
int continueRead[] = {0x00, 0x57, 0xab, 0x3b};
int command_ = 0;

int SwitchEndFileName = 0;
int endFileName = 0;
// SD Card  global Function

// SD Card global Value
int ResetAll[] = {0x57, 0xab, 0x05};
int checkConnection[] = {0x57, 0xab, 0x06, 0x57};
int setSDCard[] = {0x57, 0xab, 0x15, 0x03}; // SD Card Mode
int USBDiskMount[] = {0x57, 0xab, 0x31};
//int setFileName[] = {0x57, 0xab, 0x2f,0x2f,0x41,0x56,0x2E,0x54,0x58,0x54,0x00};   // 57,ab,//Filename.TXTNULL
int SF1[] = {0x57, 0xab};
char FileName[] = "//AV.TXT";
int SF2[] = {0x00};


int FileCreate[] = {0x57, 0xab, 0x34};
int FileOpen[] = {0x57, 0xab, 0x32};
int BYTE_WRITE[] = {0x57, 0xab, 0x3c, 0xFF, 0x00}; // >> 0x3c, dataLength,0x00 <<
int BY1_WRITE[] = {0x57, 0xab, 0x3c};
int BY2_WRITE[] = {0x00};
int BY_3[] = {0};


int WR_REQ_DATA[]   = {0x57, 0xAB, 0x2D}; // 57,AB,2D,Data
char DataToCH376[256]; // write data is 0 ot 255
int BYTE_LOCATE[] = {0x57, 0xAB, 0x39, 0xFF, 0xFF, 0xFF, 0xFF};
int BYTE_WR_GO[] = {0x57, 0xab, 0x3d};
int FileClose[] = {0x57, 0xab, 0x36, 0x01};

//int FileLength[] = {0x57, 0xab, 0x3c, 0x0d, 0x00};
int setFileNameLength = 5;

//int setFileNameA[] = {0x00, 0x57, 0xab, 0x2f, 0x2f, 0x41, 0x2e, 0x54, 0x58, 0x54, 0x00};
//int DiskconnectStatus[] = {0x00, 0x57, 0xab, 0x03}; //+
//int setAllName[] = {0x00, 0x57, 0xab, 0x2f, 0x2a, 0x2e, 0x54, 0x58, 0x54, 0x00};//*.TXT
//int setAllName2[] = {0x00, 0x57, 0xab, 0x2f, 0x41, 0x2e, 0x54, 0x58, 0x54, 0x00};//*.TXT
//int FileOpen[] = {0x57, 0xab, 0x32};
//int enumgo[] = {0x00, 0x57, 0xab, 0x33};
//int data0[] = {0x00, 0x57, 0xab, 0x27};
//int sendNull[] = {0};

//int FileUpdate[] = {0x00, 0x57, 0xab, 0x3d};

//int FilePointer[] = {0x00, 0x57, 0xab, 0x39, 0xff, 0xff, 0xff, 0xff};
//int setFileName3[] = {0x00, 0x57, 0xab, 0x2f, 0x2f, 0x59, 0x45, 0x41, 0x52, 0x32, 0x30, 0x30, 0x34, 0x00}; //A

//int FileWrite2[] = {0x00, 0x57, 0xab, 0x2d, 0x1e, 0x13, 0x0A, 0x0E, 0x20, 0x0E, 0x00, 0x01, 0x0F, 0x0F, 0x11, 0x1D, 0x19, 0x00, 0x0B, 0x0A, 0x07, 0x11};
//int FileLength2[] = {0x00, 0x57, 0xab, 0x3c, 0x12, 0x00};

/////////////////////////////////////////////////////////////////////////////////////////

int unicodeTable[] = {
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  /*32-47*/
  0x00, 0x2e, 0x10, 0x3c, 0x2b, 0x3f, 0x2f, 0x20, 0x37, 0x3e, 0x14, 0x16, 0x02, 0x24, 0x04, 0x32,
  /*0-9*/
  0x2c, 0x21, 0x23, 0x29, 0x39, 0x31, 0x2b, 0x3b, 0x33, 0x2a,

  0x12, 0x06, 0x30, 0x36, 0x18, 0x22, 0x5c,
  /*A-Z*/
  0x41, 0x43, 0x49, 0x59, 0x51, 0x4b, 0x5b, 0x53, 0x4a, 0x5a, 0x45, 0x47, 0x4d, 0x5d, 0x55, 0x4f,
  0x5f, 0x57, 0x4e, 0x5e, 0x65, 0x67, 0x7a, 0x6d, 0x7d, 0x75 /*Z*/,
  0x77, 0x4c, 0x7e, 0x6e, 0x78, 0x1c, /*symbol*/
  0x01, 0x03, 0x09, 0x19, 0x11, 0x0b, 0x1b, 0x13, 0x0a, 0x1a, 0x05, 0x07, 0x0d, 0x1d, 0x15, 0x0f,
  0x1f, 0x17, 0x0e, 0x1e, 0x25, 0x27, 0x3a, 0x2d, 0x3d, 0x35, /*z*/
  0x37, 0x33, 0x3e, 0x2e, 0xff /*{|}*/
};
//------------------------------------------ ch370t data ------------------------------------//'
char filelist[10][15];
int seaching = 1; //for seaching file
//-------------------------------------------------------------------------------------------//
//---------------------------------------------
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (opti
  on LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private define ------------------------------------------------------------*/
#define ADC1_DR_Address    ((u32)0x4001244C)

/* Private function prototypes -----------------------------------------------*/


///------------------------------------spi---------------------------------//
void keyboardMode(void);
void SendCommandToBLE2(int);
void Init_SPI(void);
void delay_SPI(void);
void sentdata_cell(int data);
void cell_sentdata(int cell);
uint8_t Flash_ReadWriteByte2(uint8_t data);
/*------------------------------------------------------------------------*/
void GPIO_Configuration(void);
void USART1_Configuration(void);
void USART2_Configuration(void);
void USART3_Configuration(void);
void USART3_Configuration2(void);
void UART4_Configuration(void);
void ADC_Configuration(void);
void sendUart(int);
void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount);
void Uart2ReceiveKeyCode(void);
void ConnectBLE(void);
void BluetoothMode(void);
void SendCommandToBLE(int data[], int sizeOfData);

void printDot(int data[], int size);
void stringToUnicodeAndSendToDisplay(char * str);

void clearDot(void);
void menu_s(void);
void caseMenu(int);
void copy_string(char *target, char *source);


const char * fileName(void);

char DataForWrite[32] = "";
char DataForWrite_aftersort[32] = "";
const char* FileName_buffer = DataForWrite;

//--- sd card---//
void ReadFile(void);
void createFile(char *);

void searchFile(void);
void appendFile(void);
void SendCH370(int data[], int);
void changeBuatRate(void);
void keyboard(void);

// john function
void unicode_to_ASCII(void);
void notepad(void);
int mapCursor(int, int, int);
int checkBit(int);
void DataToWrite(void);
void SetFilename(void);
void FileWrite(char *name, char *str);
char str4096[4096];

// gobal value int start int end




//-----------------------------------mode--------------------------------//

/* Private variables ---------------------------------------------------------*/
float AD_value;
vu16 ADC_ConvertedValue;

//------------select uart---------/

int sendUart1 = 0;
int sendUart2 = 0;
int sendUart3 = 0;
int sendUart4 = 0;

/*-----------------------------spi flash------------------------------------------*/
extern void SPI_Flash_Init(void);

extern unsigned char SST25_buffer[];
extern unsigned char SST25_buffer99[];

unsigned char SST25_buffer88[] = {0x0a, 0x0d};
/* Private define ------------------------------------------------------------*/
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define RxBufferSize1   (countof(TxBuffer1) - 1)

/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/

uint8_t TxBuffer1[] = "SPI SST25VF016B Example: This is SPI DEMO, 999888888888888888888888888888";
uint8_t TxBuffer2[] = "SPI SST25VF016B Example: This is SPI DEMO, 875217272752542452542542542542";


uint8_t NbrOfDataToTransfer1 = TxBufferSize1;
void  Delay(uint32_t nCount); //--delay spi
//GPIO_InitTypeDef GPIO_InitStructure;
int16_t USART_FLAG;

extern void SST25_W_BLOCK(uint32_t addr, u8 *readbuff, uint16_t BlockSize);
extern void SST25_R_BLOCK(uint32_t addr, u8 *readbuff, uint16_t BlockSize);


// John global Value
char str1[4096];
char str2[20];
char ch[1];
int seeCur = 0;
int mapcur = 0;
int cur = 0;
int statusmid = 0;
char strfirst[20];
char strmiddle[20];
int Curmid = 0;
char strlast[20];
int tempcur;
int mapcur1;
int mapcur2;
int lenupdate = 0;
#define size_buff 255
int len = 0;
int start = 0;
char *p;
//int end = 4096;
// StrData




/*----------------------------------------------------------------------------*/

void configFlash(void) {
  SPI_InitTypeDef  SPI_InitStructure;
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);
}
void configDisplay(void) {
  SPI_InitTypeDef  SPI_InitStructure;
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Hard ;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);
}


/*******************************************************************************
  Function Name  : Main
  Description    : Main program
  Input          : None
  Output         : None
  Return         : None
  Attention      : None
*******************************************************************************/
void changeBuatRate() {
  SendCH370(changeBaudRateByte, sizeof(changeBaudRateByte));
  delay_ms(50);
  if (USART_GetITStatus(USART3, USART_IT_RXNE) ) {
    i1 = USART_ReceiveData(USART3);
    printf("%c\r\n", i1);
  }
  printf("change 115200\r\n");
}
int main(void)
{

  /* Configure the GPIO ports */
  GPIO_Configuration();             //if config this can't use printf
  //----------------------------------------------------------------------------------------------------------
  UART4_Configuration(); //9600



  USART2_Configuration(); //115200
  USART1_Configuration(); //115200


  USART3_Configuration(); //9600



  Init_SPI();
  delay_init();
  sendUart(1);
  configDisplay();

  /*GPIO_Configuration();
    UART4_Configuration();
    USART3_Configuration();
    USART2_Configuration();
    USART1_Configuration();
    Init_SPI();
    ADC_Configuration();
    delay_init();
    sendUart(1);*/
  SPI_DISPLAY_CS_LOW();
  printDot(st_0, sizeof(st_0));
  Delay(0xffff);
  delay_ms(2000);
  printDot(st_notepad, sizeof(st_notepad));
  //stringToUnicodeAndSendToDisplay("Notepad");
  SPI_DISPLAY_CS_HIGH();


  /*
    configFlash();
    SPI_FLASH_CS_LOW();
    SST25_R_BLOCK(0x1FEFF, SST25_buffer,4096);
    printf("---test-----%s",SST25_buffer);
    SPI_FLASH_CS_HIGH();

    delay_ms(2000);
    configDisplay();
    SPI_DISPLAY_CS_LOW();
    printDot(st_bluetooth, sizeof(st_bluetooth));
    Delay(0xffff);
    SPI_DISPLAY_CS_HIGH();  */
  //delay_ms(1000);

  //Delay(0xffff);
  //configFlash();

  // for(i=0; i<4095;i++) SST25_buffer[i]='1';

  //SST25_W_BLOCK(0x0000, SST25_buffer,4096);    //写入0页的数据
  //Delay(0xffff);


  /*for(i=0; i<4095;i++) SST25_buffer[i]='2';

    SST25_W_BLOCK(0x1FEFF, SST25_buffer,4096);     //写入0页的数据
    Delay(0xffff);
  */

  //printf("---test-----");

  //SST25_R_BLOCK(0x0000, SST25_buffer,4096);
  //USART_OUT(USART1,&SST25_buffer99[0],4096);
  //printf("%s",SST25_buffer);
  //Delay(0xffff);

  //USART_OUT(USART1,&SST25_buffer88[0],2);


  //SST25_R_BLOCK(0x1F6FF, SST25_buffer99,4096);
  //USART_OUT(USART1,&SST25_buffer99[0],4096);


  /* printf("**************************************************************\r\n");
    printf("*                                                            *\r\n");
    printf("*   Thank you for using Multi Media Development Board ！^_^  *\r\n");
    printf("*                                                            *\r\n");
    printf("**************************************************************\r\n");*/
  /* Infinite loop */
  //clearDot();
  //

  //  printf("SD Card Checking");
  /*
    checkConnection[]
    setSDCard[]
    USBDiskMount[]
    setFileName
  */
  //  stringToUnicodeAndSendToDisplay("abcdef ");

  //****************** check dot****************

  printf("Status 115200 ok \r\n");
  printf("ok");
  stringToUnicodeAndSendToDisplay("APC");
  command_ = 1;
  //command_ = 1;
  while (1) {
    // keyboard();
    // notepad();
    createFile("//AV.TXT");
    // UpdateFile();
  }



}


int  mapCursor(int P1, int P2, int P3) {
  if (P1 != 0) {
    return  checkBit(P1);
  }
  else if (P2 != 0) {
    return  checkBit(P2) + 8;
  }
  else if (P3 != 0) {
    return  checkBit(P3) + 16;
  } else {
    return 0;
  }
}
int checkBit(int input) {
  int i;
  for (i = 0; i <= 8; i++) {
    if (input == 1)
      break;
    input = input >> 1;
  }
  return i;
}

void notepad() {

  if (cur == 20) {
    strcat(str1, str2);
    memset(str2, '\0', strlen(str2));

    cur = 0;
    mapcur1 = 0;
    printf(" str size it  %d  is %s \n", strlen(str1), str1);

  }
  if (USART_GetITStatus(USART2, USART_IT_RXNE)) {
    //----------------------------- uart to key--------------------------------
    uart2Buffer = USART_ReceiveData(USART2);                                //-
    if (uart2Buffer == 0xff && SeeHead == 0) {                              //-
      SeeHead = 1;                                                          //-
      countKey = 0;                                                         //-
    }
    //-
    if (countKey == 2 && uart2Buffer == 0xa4) {
      seeCur = 1;
    }
    if (countKey >= 4 && countKey <= 6) {                                   //-
      bufferKey3digit[countKey - 4] = uart2Buffer;                          //-
    }
    if (countKey == 2) //checkKeyError
    {
      checkKeyError = uart2Buffer;
    }
    countKey++;
    // ---------------------------- end uart to key ----------------------------
    // printf("[%x]\r\n",uart2Buffer);
  }
  if (countKey >= maxData) { //Recieve & checking key
    seeHead = 0;
    // printf("See key %x,%x,%x\r\n", bufferKey3digit[0], bufferKey3digit[1], bufferKey3digit[2]);

    //printf("checkKey :%x\r\n",checkKeyError);
    if (checkKeyError == 0xff) { //check error key
      //printf("Key Error");
      countKey = 0;
      SeeHead = 0;
    }

    //printf("%d\r\n",sizeof(mode_1)/sizeof(int));
    //////////////////////////////////menu selector ///////////////////////////////////

    if (bufferKey3digit[1] != 0 || bufferKey3digit[2] != 0) { //joy menu
      // ---------------------------- to key code -----------------------------
      if (bufferKey3digit[2] == 1 || bufferKey3digit[2] == 0x20) { // joy is down
        keyCode = 40; // arrow down
        // command_++;
      }
      else if (bufferKey3digit[1] == 1 || bufferKey3digit[1] == 3 || bufferKey3digit[1] == 2) { // joy is up
        keyCode = 55;  // arrow up
      }
    }

    if (bufferKey3digit[1] == 3  && bufferKey3digit[0] == 0) { // joy is up
      keyCode = 32;  // arrow up
    }

    if (seeCur == 1) {
      mapcur =  mapCursor(bufferKey3digit[0], bufferKey3digit[1], bufferKey3digit[2]);
      if (mapcur <=  cur) {
        mapcur1 = mapcur;
        statusmid = 1;

      }
      else {

        mapcur1 = cur;
      }
      printf(" mapcur = %d \n ", mapcur1);

    }

    if (bufferKey3digit[0] == 0x80 && seeCur != 1) {
      if (statusmid != 1) {
        if (cur != 0) {
          str2[cur] = '\0';
          cur--;
        }
      }
    }

    if ((bufferKey3digit[0] != 0 ||   keyCode == 32   )) {
      for ( i = 0; i < 255; i++) {
        if (bufferKey3digit[0]  == unicodeTable[(char) i]) {
          if (statusmid != 1 && keyCode != 32 && bufferKey3digit[0] != 0x80  && seeCur != 1 ) {
            str2[cur] = i;
            cur++;
          }
          if (statusmid == 1  ) {
            printf("cursor = %d \t mapcur1 = %d\t  \n", cur, mapcur1);
            strncpy(strfirst, str2, mapcur1);
            strncpy(strlast, str2 + mapcur1, strlen(str2) - mapcur1);
            if (keyCode == 32) {
              ch[0] = 32;
              mapcur1++;
              cur++;
            }
            if (bufferKey3digit[0] == 0x80  && seeCur != 1) {
              ch[0] = '\0';
              if (mapcur1 != 0) {
                memset(strfirst + strlen(strfirst) - 1, '\0', strlen(strfirst));
                cur--;
                mapcur1--;
              }
            }

            if (keyCode != 32 && bufferKey3digit[0] != 0x80  && seeCur != 1 ) {
              ch[0] = i;
              mapcur1++;
              cur++;
            }
            strcat(strfirst, ch);
            strcat(strfirst, strlast);
            strcpy(str2, strfirst);
            memset(strfirst, '\0', strlen(strfirst));
            memset(strlast, '\0', strlen(strlast));
            memset(ch, '\0', strlen(ch));
          }

          break;
        }
      }

      if (mapcur1 >= cur) {
        statusmid = 0;
      }
    }


    if (keyCode == 32 && statusmid != 1 ) {
      str2[cur] = 32;
      cur++;
    }

    printf("str2: %s : len %d\r\n", str2, strlen(str2));
    stringToUnicodeAndSendToDisplay(str2);
    countKey = 0;
    keyCode = 0;
    seeCur = 0;
  }

}

void unicode_to_ASCII() {
  for ( i = 0; i < 255; i++) {
    if (bufferKey3digit[0]  == unicodeTable[(char) i]) {


      break;
    }
  }

}

void stringToUnicodeAndSendToDisplay(char *string) {
  int strleng = 0;
  configDisplay();
  for (j = 0; j < 20 && string[j] != '\0' && string[j] != 0x0a; j++) {
    strleng++;
  }
  printf("| %s \r\n", string);
  for (j = 20; j >= 0; j--) {
    if (j < strleng) {
      cell_sentdata(~unicodeTable[((int) * (string + j))]); //send to display
      printf(" %c unicode:%x ascii:%x lum: %d\r\n", *(string + j), unicodeTable[((int) * (string + j))], (int) * (string + j), j);
    }
    else {
      cell_sentdata(0xff); // null dot send to display
      //printf("00\r\n");
    }
  }
  //  printf("%s length: %d\r\n",string,);
}
/*void appendFile() {
  if (command_ == 1) {
    SendCH370(checkConnection, sizeof(checkConnection));
    command_++; //2
    printf("Check Connection\r\n");
  } else if (command_ == 3) {
    SendCH370(setSDCard, sizeof(setSDCard));
    printf("Set SD Card Mode\r\n");
    command_++; //4
  } else if (command_ == 5) {
    SendCH370(USBDiskMount, sizeof(USBDiskMount));
    printf(" DiskMount R:%d\r\n", command_);
    command_++; //6
  } else if (command_ == 7) {
    SendCH370(setFileName, sizeof(setFileName));
    printf("Set File Name\r\n");
    command_++; //8
  } else if (command_ == 9) {
    SendCH370(FileOpen, sizeof(FileOpen));
    printf("File Open\r\n");
    command_++; //10
  }
  else if (command_ == 11) {
    SendCH370(FilePointer, sizeof(FilePointer));
    printf("Pointer\n");
    command_++; //12
  } else if (command_ == 13) {
    SendCH370(FileLength, sizeof(FileLength));
    printf("File Length\r\n");
    command_++; //14
  }
  else if (command_ == 15) {
    SendCH370(FileWrite, sizeof(FileWrite));
    printf("File Write\r\n");
    command_++; //16
  }
  else if (command_ == 17) {
    SendCH370(FileUpdate, sizeof(FileUpdate));
    printf("File Update\r\n");
    command_++; //18
  }
  else if (command_ == 19) {
    SendCH370(FileClose, sizeof(FileClose));
    printf("File Closed\r\n");
    command_++; //20
  }
  menu_s();
  //  SendCH370(checkConnection,sizeof(checkConnection));
  if (USART_GetITStatus(USART3, USART_IT_RXNE) ) {
    i1 = USART_ReceiveData(USART3);
    printf("%x\r\n", i1);
    if (i1 == 0xa8) {
      printf("OK\r\n");
    } else if (i1 == 0x51) {
      printf("Set SD Card OK\r\n");
    } else if (i1 == 0x14) {
      printf("Success\r\n");
    } else if (i1 == 0x82) {
      printf("Error\r\n");
    }
  }
  } */

/*
  void NextFile() {
  SendCH370(enumgo, sizeof(enumgo));
  //delay_ms(10);
  SendCH370(data0, sizeof(data0));
  //delay_ms(10);
  printf("Next File\r\n");
  }*/

/*
  void searchFile() {
  command_ = 0;
  r_count = 0;
  SendCH370(ResetAll, sizeof(ResetAll)); //reset chip
  printf("reset all\r\n");
  delay_ms(50);
  command_++;
  while (seaching == 1) {
    if (command_ == 1) {
      searchStep++;//1
      SendCH370(checkConnection, sizeof(checkConnection));
      printf("Check Connection str %s\r\n", FileName_buffer);
      command_++; //2
      delay_ms(50);
    } else if (command_ == 2) {
      searchStep++;//2
      SendCH370(setSDCard, sizeof(setSDCard));
      printf("Set SD Card Mode\r\n");
      command_++; //4
      delay_ms(50);
    } else if (command_ == 3) {
      searchStep++;//3
      SendCH370(USBDiskMount, sizeof(USBDiskMount));
      printf(" USB Disk Mount\r\n");
      command_++; //
      delay_ms(50);
    } else if (command_ == 4) {
      searchStep++;//5
      SendCH370(setAllName, sizeof(setAllName));
      printf("Set File Name\r\n");
      command_++; //8
      delay_ms(50);
    } else if (command_ == 5) { ///FileOpen
      searchStep++;//6
      SendCH370(FileOpen, sizeof(FileOpen));
      printf("File Open\r\n");
      command_++; //7
      delay_ms(50);
    }
    else if (command_ == 6) {
      searchStep++;
      NextFile();
      stepCount = 0;
      countFileLegth = 0;
      command_++;
      //delay_ms(50);
    } else if (command_ == 99) {
      command_ = 6;
      searchStep = 5;
      countFileLegth = 0;
    }
    menu_s();
    if (USART_GetITStatus(USART3, USART_IT_RXNE) ) {
      i1 = USART_ReceiveData(USART3);
      //printf("%x -%d-\r\n", i1,countFileLegth);
      stepCount++;
      if (i1 == 0x42 && countFileLegth == 0) { // end file
        printf("End read %d file\r\n", r_count);
        if (r_count == 0) {
          strcpy(filelist[0], "Back and enter again");
          r_count = 1;
        }
        printf("=======================================\r\n");
        for (i = 0; i < r_count; i++) {
          printf("%s\r\n", filelist[i]);
          //stringToUnicodeAndSendToDisplay(filelist[i]);
        }
        printf("=======================================\r\n");
        //seaching = 0;
      }
      if (i1 == 0x1d && countFileLegth == 0) { // if see file
        nextAgain = 1;
        DataForWrite[0] = 42;
      }
      if ((int)i1 >= 32 && (int)i1 <= 126) {
        DataForWrite[countFileLegth] = i1;
      } else {
        DataForWrite[countFileLegth] = 42;
      }
      countFileLegth++;
      if (i1 == 0xa8) {
        printf("OK\r\n");
      } else if (i1 == 0x51) {
        printf(" Set SD Card OK\r\n");
      } else if (i1 == 0x14) {
        printf("Success\r\n");
      } else if (i1 == 0x82) {
        printf("Error\r\n");
        //strcpy(filelist[0], "Please check your SD");
        r_count = 1;
      } else if (i1 == 0xFF) {
        printf("Success\r\n");
      }
      if (searchStep == 3 && i1 == 0x82)
        printf("Not found SD-Card\r\n");
    }
    if (countFileLegth == 32) {
      strcpy(filelist[r_count], fileName());
      //copy_string(filelist[r_count],(char*)fileName());
      printf("End file this string:%s\r\n", fileName());
      while (countFileLegth > 0) {
        DataForWrite[countFileLegth--] = 0;
      }
      r_count++;
      if (nextAgain == 1) { //if have file
        nextAgain = 0;
        command_ = 99;
        //printf("Preprrrr");
      }
    }

  }
  printf("breaked\r\n");
  }

*/

void copy_string(char *target, char *source) {
  while (*source) {
    *target = *source;
    source++;
    target++;
  }
  *target = '\0';
}
void writeFlash(int address, int size) {
  configFlash();
  SPI_FLASH_CS_LOW();
  SST25_W_BLOCK(address, SST25_buffer, 4096);
  //printf("---test-----%s",SST25_buffer);
  SPI_FLASH_CS_HIGH();
}
void writeFlash2(int address, int size) {
  configFlash();
  SPI_FLASH_CS_LOW();
  SST25_W_BLOCK(address, SST25_buffer99, 4096);
  //printf("---test-----%s",SST25_buffer);
  SPI_FLASH_CS_HIGH();
}
void ReadFile() { //readf
  stringToUnicodeAndSendToDisplay("Reading....");
  command_ = 0;
  r_count = 0;
  //SendCH370(ResetAll, sizeof(ResetAll)); //reset chip
  printf("reset all\r\n");
  delay_ms(50);
  command_++;
  while (readstatus == 1) {
    if (command_ == 1) {
      SendCH370(checkConnection, sizeof(checkConnection));
      command_++; //2
      delay_ms(50);
      // printf("Check Connection str %d\r\n",myFunction());
    } else if (command_ == 2) {
      SendCH370(setSDCard, sizeof(setSDCard));
      printf("Set SD Card Mode\r\n");
      command_++; //3
      delay_ms(50);
    } else if (command_ == 3) {
      SendCH370(USBDiskMount, sizeof(USBDiskMount));
      printf("USB Disk Mount\r\n");
      command_++; //4
      delay_ms(50);
    } else if (command_ == 4) {

      SendCH370(SF1, sizeof(SF1));

      printf("Set file Name\r\n");
      command_++; //5
      delay_ms(50);
    } else if (command_ == 5) { ///FileOpen
      SendCH370(FileOpen, sizeof(FileOpen));
      printf("File Open\r\n");
      command_++; //6
      delay_ms(50);

    } else if (command_ == 6) {
      SendCH370(SetByteRead, sizeof(SetByteRead)); //result 1D can read
      //printf("Check for reading File\r\n");
      command_ = 99;
      //delay_ms(50);
    } else if (command_ == 95) { //left (prevois line)
      SendCH370(continueRead, sizeof(continueRead));
      //printf("continue Read\r\n");
      command_++; //96
    }
    else if (command_ == 98) { //right (next line)
      command_ = 6;
    } else if (command_ == 99) {
      SendCH370(ReadData, sizeof(ReadData));
      // printf("Reading File\r\n");
      command_++;
    }
    menu_s();
    if (USART_GetITStatus(USART3, USART_IT_RXNE) ) {
      i1 = USART_ReceiveData(USART3);
      //printf("%x-%d\r\n", i1, i1);
      if (command_ == 96 && i1 == 0x14) {
        command_ = 6;
        printf("\r\n----------read New Sector-------------------- \r\n");
      }
      if (i1 == 0x80 || i1 == 0x14) {
        // printf("funk\r\n");
      }
      else if (command_ == 100 && countSector512 < 4 && countdataTemp512 < 512) {
        if (i1 == '\0') {
          printf("End of File\r\n");
        }
        else if (countdataTemp512 < ((128) * (countSector512 + 1)) - 1) { //128
          dataTemp512[countdataTemp512] = i1;
          countdataTemp512++;
          strLength++;
          waitEnd = 0;
          lastAscii = i1;
        } else {
          countSector512++;
          dataTemp512[countdataTemp512] = i1;
          countdataTemp512++;
          // printf("`````````````````````````one sector %d````````````````\r\n%s\r\n", countdataTemp512, dataTemp512);

          if (countSector512 >= 4) { //512

            /*dataTemp512[countdataTemp512] = i1;
              countdataTemp512++;*/
            // printf("`````````````````````````one sector````````````````\r\n%s\r\n", dataTemp512);
            // printf("---------------------------------------------------\r\n");
            command_ = 95;
            //push to flash

            for (i = addressWriteFlashTemp; i < addressWriteFlashTemp + 512; i++) {
              SST25_buffer[i - (4096 * countSector)] = dataTemp512[i - addressWriteFlashTemp];
            }
            countSector4096++;
            //writeFlash(addressWriteFlashTemp);
            addressWriteFlashTemp += countdataTemp512;
            if (countSector4096 >= 8) { // 8
              // write to flash here
              writeFlash(addressSector, 4096);
              Delay(0xffff);
              stringToUnicodeAndSendToDisplay("Reading....");
              addressSector += 4096;
              countSector4096 = 0;
              //--------------------------------------------------------------------------------------------
              //check this value `addressWriteFlashTemp`--
              //--------------------------------------------------------------------------------------------
              countSector++;
              // printf("/////////////////////////////////////////////////////%s\r\n////////////////////////", SST25_buffer);
              // printf("****************address:%d********************", addressSector);
              //while(1){}
            }
            //  printf("-------------------------%d--------------------------\r\n", addressWriteFlashTemp);

            //--- reset temp sector---//
            countdataTemp512 = 0;
            countSector512 = 0;
          } else {
            command_ = 6;
          }

          /*printf("data is :%s\r\n",dataTemp512);
            printf("----------------------------read sector------------------\r\n");*/

        }
      }/*else if(countSector512>=4){
           printf("`````````````````````````one sector````````````````\r\n%s\r\n",dataTemp512);
           printf("---------------------------------------------------\r\n");
      }*/
      if (i1 == 0xa8) {
        printf("OK\r\n");
      } else if (i1 == 0x51) {
        printf("Set SD Card OK\r\n");
      } else if (i1 == 0x14) {
        printf("Success\r\n");
      } else if (i1 == 0x82) {
        printf("Error\r\n");
      } else if (i1 == 0xFF) {
        printf("Endf\r\n");
      }
      /*if(command_==100&&i1!=0x1d){ //check continue read
        printf("Endf*************-*-*-*-*-*-*-\r\n");
        command_ = 101;
        }*/
    } else {
      if (lastAscii == i1) {
        waitEnd++;
        if (waitEnd == 100 * 100) {
          for (i = addressWriteFlashTemp; i < addressWriteFlashTemp + 512; i++) {
            SST25_buffer[i - (4096 * countSector)] = dataTemp512[i - addressWriteFlashTemp];
          }
          //
          configFlash();
          //printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$addressSector:%d $$$$$$$$$$$$$$$$$$$$$$$$$\r\n", addressSector);
          writeFlash(addressSector, 4096);
          addressWriteFlashTemp += countdataTemp512;


          //addressWriteFlashTemp += countdataTemp512;


          printf("wait\r\n");
          waitEnd++;
          SPI_FLASH_CS_LOW();
          SST25_R_BLOCK(0, SST25_buffer99, 4096);
          SPI_FLASH_CS_HIGH();
          Delay(0xffff);
          // printf("``%d```````````````````````end all sector````````````````\r\n\r\n", strLength);
          //printf("%s\r\n&&&&&&&&&&&&&",SST25_buffer);
          //while(1){}

          endReadFile = 1;
          for (i = pointer22char; SST25_buffer99[i] != 0x0d; i++) {
            buffer22Char[i - pointer22char] = SST25_buffer99[i];
          }
          stringToUnicodeAndSendToDisplay(buffer22Char);
          pointer22char += 23;
          printf("\r\n----------------------end---%d-----------------------\r\n", addressWriteFlashTemp);
          AmountSector = addressWriteFlashTemp / 4096;
          AmountSectorT = addressWriteFlashTemp % 4096;
          printf("d::::%s---**\r\n", SST25_buffer99);
          while (endReadFile == 1) { //readfe
            menu_s();
          }


        }
      }
    }

  }
}
void SetFilename() {
  int i = 0;


}


void DataToWrite() {
  int i = 0;

  sendUart(3);



  for ( i = 0; i < 255; i++) {
    printf("%c", DataToCH376[i]);

  }




}
void FileWrite(char *name, char *str) {
  sendUart(1);
  p = str;
  len = strlen(str);
	
	printf("str is len = %d\n\n",len);
  if (len < 255 ) {

    memset(DataToCH376, 0, strlen(DataToCH376)); // clear data TO CH376
    strncpy(DataToCH376, p, len);
		len-=size_buff;
    //  printf("string dest = %d\n",strlen(DataToCH376));
    SendCH370(SF1, sizeof(SF1));
    sendUart(3);
    // for ( i = 0; i < strlen(FileName); i++) {
   printf("%s", FileName);
    //}
    sendUart(1);
    SendCH370(SF2, sizeof(SF2));
    //    printf("Set File Name\r\n");
    
    delay_ms(50);

    SendCH370(FileOpen, sizeof(FileOpen));
    delay_ms(50);
    SendCH370(BYTE_LOCATE, sizeof(BYTE_LOCATE)); // FF FF FF FF
    // printf("File Update\r\n");

    delay_ms(50);


    sendUart(1);
    SendCH370(BY1_WRITE, sizeof(BY1_WRITE));
    // sendUart(3);
    //for ( i = 0; i < strlen(FileName); i++) {
    BY_3[0] = len;
    // printf("%x",len);
    SendCH370(BY_3, sizeof(BY_3));
    //}
    sendUart(1);
    SendCH370(BY2_WRITE, sizeof(BY2_WRITE));
    // printf("Set File Name\r\n");
    delay_ms(50);



    // SendCH370(BYTE_WRITE, sizeof(BYTE_WRITE));
    // printf("Setting data length\r\n");
    delay_ms(50);
    //delay_ms(50);
    SendCH370(WR_REQ_DATA, sizeof(WR_REQ_DATA));
    delay_ms(50);
    sendUart(3);
    //  for ( i = 0; i < strlen(DataToCH376); i++) {
    printf("%s", DataToCH376);
    //  }

    sendUart(1);
    //    printf("Writing data\r\n");
    delay_ms(50);

    SendCH370(BYTE_WR_GO, sizeof(BYTE_WR_GO));
    //printf("File Update\r\n");
    delay_ms(50);


    SendCH370(FileClose, sizeof(FileClose));
    //  printf("File Close\r\n");
    delay_ms(50);

 printf("strlen is DatatoCH376 = %d\r\n",strlen(DataToCH376));
 printf("len is str = %d\n",len);
 
 command_++;
  }

  while (len >= size_buff ) {
    memset(DataToCH376, 0, strlen(DataToCH376)); // clear data TO CH376
    strncpy(DataToCH376,p, size_buff+1);
     //printf("%s\n",DataToCH376);
    //  printf("string dest = %d\n",strlen(DataToCH376));
    //  printf("string it is  = %d\n",k);

    SendCH370(SF1, sizeof(SF1));
    sendUart(3);
    //for ( i = 0; i < strlen(FileName); i++) {
    printf("%s", FileName);
    //}
    sendUart(1);
    SendCH370(SF2, sizeof(SF2));
    // printf("Set File Name\r\n");
    delay_ms(50);

    SendCH370(FileOpen, sizeof(FileOpen));
    delay_ms(100);
    SendCH370(BYTE_LOCATE, sizeof(BYTE_LOCATE)); // FF FF FF FF
    //  printf("File Update\r\n");

    delay_ms(100);

    SendCH370(BYTE_WRITE, sizeof(BYTE_WRITE));
    printf("Setting data length\r\n");
    delay_ms(100);
    //delay_ms(50);
    SendCH370(WR_REQ_DATA, sizeof(WR_REQ_DATA));
    delay_ms(100);
    sendUart(3);
    //for ( i = 0; i < strlen(DataToCH376); i++) {
    printf("%s", DataToCH376);
    //}

    sendUart(1);
    //   printf("Writing data\r\n");
    delay_ms(100);

    SendCH370(BYTE_WR_GO, sizeof(BYTE_WR_GO));
    //  printf("File Update\r\n");
    delay_ms(100);


    SendCH370(FileClose, sizeof(FileClose));
    //  printf("File Close\r\n");
    delay_ms(100);

 command_++;

	 p += size_buff;
   len -= size_buff;
	 
 printf("\nstrlen2 = %d\r\n",strlen(DataToCH376));
 printf("len2 = %d\n",len);
 



  }
  if (len > 0) {

    memset(DataToCH376, 0, strlen(DataToCH376)); // clear data TO CH376
    strncpy(DataToCH376,p, len);
		p+=len;
		
    //  printf("string dest = %d\n",strlen(DataToCH376));
    SendCH370(SF1, sizeof(SF1));
    sendUart(3);
    // for ( i = 0; i < strlen(FileName); i++) {
    printf("%s", FileName);
    //}
    sendUart(1);
    SendCH370(SF2, sizeof(SF2));
    //    printf("Set File Name\r\n");
    delay_ms(50);

    SendCH370(FileOpen, sizeof(FileOpen));
    delay_ms(50);
    SendCH370(BYTE_LOCATE, sizeof(BYTE_LOCATE)); // FF FF FF FF
    // printf("File Update\r\n");

    delay_ms(50); //10


    sendUart(1);
    SendCH370(BY1_WRITE, sizeof(BY1_WRITE));
    // sendUart(3);
    //for ( i = 0; i < strlen(FileName); i++) {
    BY_3[0] = len;
    // printf("%x",len);
    SendCH370(BY_3, sizeof(BY_3));
    //}
    sendUart(1);
    SendCH370(BY2_WRITE, sizeof(BY2_WRITE));
    // printf("Set File Name\r\n");
    
    delay_ms(50);



    // SendCH370(BYTE_WRITE, sizeof(BYTE_WRITE));
    // printf("Setting data length\r\n");
    delay_ms(50);
    //delay_ms(50);
    SendCH370(WR_REQ_DATA, sizeof(WR_REQ_DATA));
    delay_ms(50);
    sendUart(3);
    //  for ( i = 0; i < strlen(DataToCH376); i++) {
    printf("%s", DataToCH376);
    //  }

    sendUart(1);
    //    printf("Writing data\r\n");
    delay_ms(50);

    SendCH370(BYTE_WR_GO, sizeof(BYTE_WR_GO));
    //printf("File Update\r\n");
    delay_ms(50);


    SendCH370(FileClose, sizeof(FileClose));
    //  printf("File Close\r\n");
    delay_ms(50);
   printf("strlen3  = %d\r\n",strlen(DataToCH376));
		printf("len3  = %d\n",len);
 command_++;

	}










}


void createFile(char *name) {

  strcpy(str4096, "California Princeton University Genre Sword and planet Notable works Gor novel series Spouse Bernice L. Green (1956杙resent) Children John David Jennifer Relatives John Frederick Lange, Sr. (father) Almyra D. Lange n閑 Taylor (mother) John Norman is the pen name of John Frederick Lange, Jr. (born June 3, 1931), who is the author of the Gor series of fantasy novels, and a professor of philosophy.Contents 1 Background 2 Academic career 3 Writing career 4 Themes 4.1 Gorean subculture 5 Works 5.1 Fiction 5.1.1 Gor series 5.1.2 Telnarian Histories series 5.1.3 Other novels 5.1.4 Short-story collections 5.2 Nonfiction 6 Notes 7 External links Background John Lange was born in Chicago, Illinois, to John Frederick Lange and Almyra D. Lange n閑 Taylor.He began his academic career in the early 1950s, earning a Bachelor of Arts degree from the University of Nebraska in 1953, and his Master of Arts degree from the University of Southern California in 1957. While at USC he married Bernice L. Green on January 14, 1956. The couple have three children: John, David, and Jennifer.");

  memset(FileName, '\0', strlen(FileName)); // clear name
  strcpy(FileName, name);                 // set name
  //  command_ = 1;
  if (command_ == 1) {
    SendCH370(checkConnection, sizeof(checkConnection));
    command_++; //2
    printf("Check Connection\r\n");
    delay_ms(50);
  } else if (command_ == 2) {
    SendCH370(setSDCard, sizeof(setSDCard));
    printf("Set SD Card Mode\r\n");
    command_++; //4
    delay_ms(50);
  } else if (command_ == 3) {
    SendCH370(USBDiskMount, sizeof(USBDiskMount));
    printf(" SendCommand R:%d\r\n", command_);
    command_++; //6
    delay_ms(50);
  } else if (command_ == 4) {
    SendCH370(SF1, sizeof(SF1));
    sendUart(3);
    for ( i = 0; i < strlen(FileName); i++) {
      printf("%c", FileName[i]);
    }
    sendUart(1);
    SendCH370(SF2, sizeof(SF2));
    printf("Set File Name\r\n");
    command_++; //8
    delay_ms(50);
  } else if (command_ == 5) {
    SendCH370(FileCreate, sizeof(FileCreate));
    // SendCH370(FileClose,sizeof(FileClose));
    printf("File Create\r\n"); //FileClose
    //  delay_ms(50);
    //  SendCH370(BYTE_LOCATE, sizeof(BYTE_LOCATE));

    delay_ms(500);
    command_++; //10
  }
  //else if (command_ == 6) {
  //  SendCH370(BYTE_WRITE, sizeof(BYTE_WRITE));
  // printf("Setting data length\r\n");
  // command_++; //12
  //delay_ms(50);
  //}
  // else if (command_ == 7) {
  //  DataToWrite();
  //  SendCH370(WR_REQ_DATA, sizeof(WR_REQ_DATA));
  //  DataToWrite();
  //  printf("Writing data\r\n");
  //command_++; //14
  //  delay_ms(200);
  // } else if (command_ == 8) {
  //  SendCH370(BYTE_WR_GO, sizeof(BYTE_WR_GO));
  //  printf("File Update\r\n");
  // command_++; //16
  //  delay_ms(50);
  // }
  else if (command_ == 6) {
    SendCH370(FileClose, sizeof(FileClose));
    printf("File Close\r\n");
    command_++; //18
    delay_ms(50);
  }

  else if (command_ == 7) {
    FileWrite("\\AV.TxT", str4096);
    printf("File update complete\r\n");
  }

  menu_s();
  //  SendCH370(checkConnection,sizeof(checkConnection));
  if (USART_GetITStatus(USART3, USART_IT_RXNE) ) {
    i1 = USART_ReceiveData(USART3);
    printf("%x\r\n", i1);
    if (i1 == 0xa8) {
      printf(" status OK\r\n");
    } else if (i1 == 0x51) {
      printf(" Set SD Card OK\r\n");
    } else if (i1 == 0x14) {
      printf(" Mount Success\r\n");
    } else if (i1 == 0x82) {
      printf(" Mount Error\r\n");
    }
  } //checkConnection
}
const char * fileName()
{
  int loop = 0;
  int count_char = 0;
  int seeT = 0;
  for (loop = 0; loop < 32; loop++) {
    if (((int)DataForWrite[loop] >= 33 && (int)DataForWrite[loop] <= 126) && DataForWrite[loop] != 42 && loop < 12) { //end of 12
      DataForWrite_aftersort[count_char] = DataForWrite[loop];
      count_char++;
    }
  }
  while (count_char < 32) {
    DataForWrite_aftersort[count_char] = 0;
    count_char++;
  }
  count_char = 0;
  while (DataForWrite_aftersort[count_char] != '\0') {
    if (DataForWrite_aftersort[count_char] == 'T' && seeT == 0) {
      if (DataForWrite_aftersort[count_char + 1] == 'B' && DataForWrite_aftersort[count_char + 2] == 'T') {
        seeT = 1;
        DataForWrite_aftersort[count_char] = '.';
        DataForWrite_aftersort[count_char + 1] = 'T';
        DataForWrite_aftersort[count_char + 2] = 'B';
        DataForWrite_aftersort[count_char + 3] = 'T';
        count_char += 3;
      }
    } else if (seeT || DataForWrite_aftersort[count_char] == 42) {
      DataForWrite_aftersort[count_char] = 0;
    }
    count_char++;
  }
  if (seeT == 1) {
    printf("this's tbt file\r\n");
  }
  return DataForWrite_aftersort;
}
void menu_s() {
  if (USART_GetITStatus(USART2, USART_IT_RXNE)) {
    //----------------------------- uart to key--------------------------------
    uart2Buffer = USART_ReceiveData(USART2);                                //-
    if (uart2Buffer == 0xff && SeeHead == 0) {                              //-
      SeeHead = 1;                                                          //-
      countKey = 0;                                                         //-
    }                                                                       //-

    if (countKey >= 4 && countKey <= 6) {                                   //-
      bufferKey3digit[countKey - 4] = uart2Buffer;                          //-
    }

    if (countKey == 2) //checkKeyError
    {
      checkKeyError = uart2Buffer;
    }
    countKey++;
    // ---------------------------- end uart to key ----------------------------
    // printf("[%x]\r\n",uart2Buffer);
  }
  if (countKey >= maxData) { //Recieve & checking key
    seeHead = 0;
    printf("See key %x,%d,%x\r\n", bufferKey3digit[0], bufferKey3digit[1], bufferKey3digit[2]);
    //printf("checkKey :%x\r\n",checkKeyError);
    if (checkKeyError == 0xff) { //check error key
      //printf("Key Error");
      countKey = 0;
      SeeHead = 0;
    }
    printf("current mode:%d\r\n", mode);
    //printf("%d\r\n",sizeof(mode_1)/sizeof(int));
    //////////////////////////////////menu selector ///////////////////////////////////
    if (bufferKey3digit[1] != 0 || bufferKey3digit[2] != 0) { //joy menu
      // ---------------------------- to key code -----------------------------
      if (bufferKey3digit[2] == 1 || bufferKey3digit[2] == 0x20) { // joy is down
        keyCode = 40; // arrow down
        // command_++;
      }
      else if (bufferKey3digit[1] == 1 || bufferKey3digit[1] == 3 || bufferKey3digit[1] == 2) { // joy is up
        keyCode = 55;  // arrow up
      }
      else if (bufferKey3digit[1] == 128 || bufferKey3digit[2] == 0x10) { // joy is up
        keyCode = 38;  //
        //  command_=8;
      }
      else if (bufferKey3digit[1] == 64 || bufferKey3digit[2] == 8) {
        keyCode = 13; // enter
      }
      else if (bufferKey3digit[1] == 32 || bufferKey3digit[2] == 4) {
        keyCode = 8; // backspace
        ///command_ = 99;
      }
      else if (bufferKey3digit[1] == 4 ) {
        keyCode = 38; // left
        //  command_ = 97;
        //command_ = 95; //before delete
      }
      else if (bufferKey3digit[1] == 8) {
        keyCode = 40; // right
        // command_ = 98;
      }
      if (bufferKey3digit[0] == 0x9f) {
        printf("new Folder\r\n");
      }
    }

    //---------------------------------end joy event--------------------------------
    ////////////////////////////////////////////////////////////////////////////////
    //                                                                            //
    //                                                                            //
    //------------------------------- mode selector --------------------------------
    //                                                                            //
    //                                                                            //
    ////////////////////////////////////////////////////////////////////////////////
    //------------------------------- mode (1) -------------------------------------
    if (count_menu >= 1 && count_menu <= maxMenu && mode == 0) { //select menu //modemenu
      if (keyCode == 40) { //up
        if (count_menu != maxMenu) {
          count_menu++;
        }
      }
      else if (keyCode == 38) { //down
        if (count_menu != 1) {
          count_menu -= 1;
        }
      }
    }
    // --------------------------- end mode (1) -----------------------------
    if (count_menu >= 1 && count_menu <= maxMenu && mode == 1) {

    }
    // ----------------------------- mode (5) -------------------------------
    if (count_menu >= 1 && count_menu <= maxMenu && mode == 5) {
      printf("bluetooth Mode\r\n");
    }
    // ----------------------------- end mode (5) ---------------------------
    if (keyCode == 8) { // enter mode && previousMode != mode
      if (mode == 3 && openFileStatus == 1) {
        command_ = 0;
        seaching = 1;
        //mode = 0;
        openFileStatus = 0;
        readstatus = 0;
      } else if (mode == 3) {
        command_ = 0;
        seaching = 0;
        mode = 0;
      }
      else {
        mode = 0;
      }
      printf("back c = %d mode = %d\r\n", command_, mode);
    } // back
    if (keyCode == 13) { //enter
      //  previousMode
      if (mode == 0) { //on menu
        previousMode = mode;
        mode = count_menu;
        printf("enter mode(%d)\r\n", count_menu);
        if (mode == 3) {
          seaching = 1;
          countMenuInReadMode = 0;
        }
      } else if (mode == 3 && endReadFile != 1) { //openf
        strcpy(prepareNameToOpen, filelist[countMenuInReadMode - 1]);
        printf("Open %s\r\n", prepareNameToOpen);
        i = 0;
        setFileNameLength = 5;
        while (prepareNameToOpen[i] != '\0') {
          setFileNameLength++;
          //  setFileName[i + 5] = (int)prepareNameToOpen[i];
          //   printf("- %x ", setFileName[i + 5]);
          i++;
        }
        setFileNameLength++;
        //   setFileName[i + 5] = 0x00;
        i = 0;
        seaching = 0;
        openFileStatus = 1;
        readstatus = 1;
      }
    }

    /////////////////////////////// --- end mode --- ////////////////////////////////
    printf("%d\r\n", count_menu); //mode menu
    // -----------------------  visible menu with braille display ---- Mode (1) -----
    switch (mode) { //in list menu mode
      case 0:
        caseMenu(count_menu);
        break;
      case 3: //mode 3 read mode

        if (endReadFile != 1) {
          if (keyCode == 38) { //up
            if (countMenuInReadMode > 1) {
              countMenuInReadMode -= 1;
            }
          } else if (keyCode == 40) { //down
            if (countMenuInReadMode != r_count) {
              countMenuInReadMode += 1;
            }
          }

          if (countMenuInReadMode == 0) {
            stringToUnicodeAndSendToDisplay("Read mode");
            printf("******print (Read mode) to dot *********\r\n");
          } else {
            stringToUnicodeAndSendToDisplay(filelist[countMenuInReadMode - 1]);
            printf("******print (%s) to dot ********\r\n", filelist[countMenuInReadMode - 1]);
          }   //prepareNameToOpen
        } else {
          if (keyCode == 38 || keyCode == 40 && endReadFile == 1) { //readfg

            for (i = pointer22char; i < (pointer22char + 22 < addressWriteFlashTemp ? pointer22char + 22 : addressWriteFlashTemp - pointer22char) && SST25_buffer99[i] != 0x0a ; i++) {
              if (SST25_buffer99[i] != NULL) {
                buffer22Char[i - pointer22char] = SST25_buffer99[i];
                printf("%c/", SST25_buffer99[i]);
              }
            }

            stringToUnicodeAndSendToDisplay(buffer22Char);
            printf("send: %d %s -\r\n", pointer22char, buffer22Char);
            if (keyCode == 40) {
              /* if(pointer22char+22<4096&&pointer22char<addressWriteFlashTemp){
                pointer22char+=22;
                }else{
                pointer22char+=4096-pointer22char;
                }*/
              /*
                countSector
                pointer22char
                addressWriteFlashTemp
              */

            } else if (keyCode == 38) {
              if (pointer22char >= 22) {
                pointer22char -= 22;
              }
            }

            //buffer22Char[]
            /*for(i = 0; i < countSector+1;i++){ //----------------end read file form rom-------------------
              SPI_FLASH_CS_LOW();
              SST25_R_BLOCK(i*4096, SST25_buffer99, 4096);
              SPI_FLASH_CS_HIGH();
              Delay(0xffff);
              if(i==countSector){
                  for(j=0;j<(addressWriteFlashTemp-(countSector*4096))-1;j++){
                    printf("%c",SST25_buffer99[j]);
                  }
                  //printf("12121212121212121212end @@@@@@@@@@@@@@@@@@@\r\n");
              }
              else{
                  printf("%s\r\n---------------------------------------\r\n",SST25_buffer99);

              }
              //for(i=0;i<countdataTemp512;i++){
              //printf("---asd-%s", SST25_buffer99);
              }//
            */
          }
        }
        break;
      case 5:
        stringToUnicodeAndSendToDisplay("STM Braille SLRI");
        break;
    }
    //------------------------------ end case menu ------------------------
    countKey = 0;
    keyCode = 0;
  }
}
void keyboard() {
  if (USART_GetITStatus(USART2, USART_IT_RXNE)) {
    //----------------------------- uart to key--------------------------------
    uart2Buffer = USART_ReceiveData(USART2);                                //-
    if (uart2Buffer == 0xff && SeeHead == 0) {                              //-
      SeeHead = 1;                                                          //-
      countKey = 0;                                                         //-
    }                                                                       //-

    if (countKey >= 4 && countKey <= 6) {                                   //-
      bufferKey3digit[countKey - 4] = uart2Buffer;                          //-
    }
    if (countKey == 2) //checkKeyError
    {
      checkKeyError = uart2Buffer;
    }
    countKey++;
    // ---------------------------- end uart to key ----------------------------
    // printf("[%x]\r\n",uart2Buffer);
  }
  if (countKey >= maxData) { //Recieve & checking key
    seeHead = 0;
    printf("See key %x,%d,%x\r\n", bufferKey3digit[0], bufferKey3digit[1], bufferKey3digit[2]);

    //printf("checkKey :%x\r\n",checkKeyError);
    if (checkKeyError == 0xff) { //check error key
      //printf("Key Error");
      countKey = 0;
      SeeHead = 0;
    }
    //printf("%d\r\n",sizeof(mode_1)/sizeof(int));
    //////////////////////////////////menu selector ///////////////////////////////////
    if (bufferKey3digit[1] != 0 || bufferKey3digit[2] != 0) { //joy menu
      // ---------------------------- to key code -----------------------------
      if (bufferKey3digit[2] == 1 || bufferKey3digit[2] == 0x20) { // joy is down
        keyCode = 40; // arrow down
        // command_++;
      }
      else if (bufferKey3digit[1] == 1 || bufferKey3digit[1] == 3 || bufferKey3digit[1] == 2) { // joy is up
        keyCode = 55;  // arrow up
      }
    }
    if (sizeof(bufferKey3digit[0] != 0)) {
      for ( i = 0; i < 255; i++) {
        if (bufferKey3digit[0] == unicodeTable[(char) i]) {
          printf("%c", i);
          break;
        }
      }
    }
    countKey = 0;
    keyCode = 0;
  }
}
void caseMenu(int count_menu) {
  switch (count_menu) {
    case 1:
      printDot(st_notepad, sizeof(st_notepad));
      break;
    case 2:
      printDot(st_filemanage, sizeof(st_filemanage));
      break;
    case 3:
      printDot(st_read, sizeof(st_read));
      break;
    case 4:
      printDot(st_usbconnect, sizeof(st_usbconnect));
      break;
    case 5:
      printDot(st_bluetooth, sizeof(st_bluetooth));
      break;
    case 6:
      printDot(st_clock, sizeof(st_clock));
      break;
    case 7:
      printDot(st_calcu, sizeof(st_calcu));
      break;
    case 8:
      printDot(st_tools, sizeof(st_tools));
      break;
  }
}

void printDot(int data[], int size) {
  int tsize = size / sizeof(int);
  //  printf("%d", sizeof(testarray[0]) / sizeof(int));
  for (j = 20; j >= 0; j--) {
    if (j < tsize)
      cell_sentdata(~data[j]);
    else
      cell_sentdata(0xff); // null dot
  }

}
void clearDot() {
  for (j = 20; j >= 0; j--) {
    cell_sentdata(0xff);
  }
}
void  Delay(uint32_t nCount)
{
  for (; nCount != 0; nCount--);
}
uint8_t Flash_ReadWriteByte2(uint8_t data)
{
  /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(SPI1, data);

  /* Wait to receive a byte */
  //while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(SPI1);
}
void Init_SPI(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_SPI_FLASH_CS, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; //dot display 10MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; //dot display
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; //spi flash
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  SPI_FLASH_CS_HIGH();
  SPI_DISPLAY_CS_HIGH();
  /* SPI1 Config -------------------------------------------------------------*/

  /* Enable SPI1 */
  SPI_Cmd(SPI1, ENABLE);
  SPI_I2S_ClearFlag(SPI1, SPI_I2S_FLAG_TXE);
  //SPI_DISPLAY_CS_LOW();
}
void sentdata_cell(int data) {
  for (i = 0; i < 1; i++) {
    Flash_ReadWriteByte2(data);
    Delay(0x25F);
  }
}
void cell_sentdata(int cell) {
  SPI_DISPLAY_CS_LOW();
  Delay(0x55F);
  sentdata_cell(cell);
  //    Delay(0x005e0);
  SPI_DISPLAY_CS_HIGH();
  Delay(0x55F);
}
void delay_SPI() {
  Delay(0xfffff);
}
void Uart2ReceiveKeyCode() {
  sendUart(1);
  if ( USART_GetITStatus(USART2, USART_IT_RXNE) ) {
    i1 = USART_ReceiveData(USART2);
    //printf("%c", k);
    if (i1 == 'H') { //check first byte
      isHex = 1;   //equal 1 is hex
    } else if (i1 == 'S') {
      isHex = 2; // equal 2 is Switch
    }
    if (i1 != 'F' && i1 != '\r' && i1 != '\n') {
      if (i1 != 'S' && i1 != 'H') {

        buffer[count1++] = (char)i1;

        //printf("%c", i);
      }
    } else { //after store buffer
      if (isHex == 2) {
        printf("Switch input : %s\r\n", buffer); //debug via USART 1

        //Example Switch
        // index 0 is '0' use index 1 for check condition
        if (buffer[1] == '3') {
          printf("Nav Left\r\n");
          SendCommandToBLE(navLeft, sizeof(navLeft));
        }
        if (buffer[1] == 'C') {
          printf("Nav Right\r\n");
          SendCommandToBLE(navRight, sizeof(navRight));
        }
        // do  something
        //
        //
        //
        //
        //
        //
        //
      } else if (isHex == 1) {
        // converts to hex//
        while (buffer[j1] != '\0') {
          if (buffer != 0) {
            Hex = buffer[j1];
          }
          j1++;
          if (j1 > 6) {
            break;
          }
        }
        j1 = 0;
        // end converst
        printf("Hex input : %s Hex is %x \r\n", buffer, Hex);
        // do something with hex
        //
        //
        //
        //
        //
        //
        //
      }
      //printf("%s",buffer);
      //** clear buffer string **//
      itFirst = 0;
      count1 = 0;
      isHex = 0;
      memset(buffer, 0, sizeof(buffer));
      //////////////////////////////
    }
  }
  sendUart(0);
  //printf("%s\r\n",buffer);
  //memset(buffer, 0, sizeof(buffer));
  //  printf("%c",USART_ReceiveData(USART2));
  //  printf("%c",USART_ReceiveData(USART2));
  //
}
void keyboardMode() {
  sendUart(1);
  if (USART_GetITStatus(USART2, USART_IT_RXNE) ) {
    i1 = USART_ReceiveData(USART2);
    if (i1 == 0xff && seeHead == 0) {
      seeHead = 1;
      countKey = 0;
    }
    keyCodeRecieve[countKey++] = i1;
    //printf("%x",i1);
    //SendCommandToBLE2(i1);
  }
  if (countKey >= maxData) {
    SendCommandToBLE(keyCodeRecieve, sizeof(keyCodeRecieve));
    seeHead = 0;
    //int navLeft[] = {0xff, 0xff, 0xa6, 0x03, 0x00, 0x04, 0x00};
    for ( j = 0 ; j < 7 ; j++) {
      printf("%c", keyCodeRecieve[j]);
    }
    countKey = 0;
  }
}
void BluetoothMode() {
  if (USART_GetITStatus(UART4, USART_IT_RXNE)) { //if serial available
    hexbuffer = USART_ReceiveData(UART4);
    //sendUart(1);
    //printf("%c",i);
    //cell_sentdata(~i);
    if (hexbuffer == 0xff && SeeHead == 0) {
      SeeHead = 1;
      count = 0;
      dataLength = 0;
    }
    if (count >= 23 && SeeHead == 1) {
      SeeHead = 0;
      pushToDisplay = 1;
    }
    BLEConBuffer[count] = hexbuffer;
    count++;
    if (count > 1 && BLEConn == 0) { //
      if (BLEConBuffer[0] == 0xff && BLEConBuffer[1] == 0xff && BLEConBuffer[2] == 0xa1 && BLEConn == 0) { //connect
        ConnectBLE();
        //memset(BLEConBuffer, 0, sizeof(BLEConBuffer));
        countConn++;
        if (countConn == 2) {
          BLEConn = 1;
          becon = 1;
        }
        count = 0;
      }
    }
    //cell_sentdata(~i);
    /*  if(count==18&&BLEConn==0){
          printf("%d",count);
          BLEConn = 1;
          count = 0;
      }
        sendUart(0);*/
  } else {
    sendUart(1);
    if (pushToDisplay == 1) {
      for (j = 20; j >= 0; j--) {
        cell_sentdata(0xff);
      }
      for (j = 23; j >= 0; j--) {
        //  abort//clear data
        if (USART_GetITStatus(UART4, USART_IT_RXNE)) {
          if (BLEConn != 0) {
            /*if(count>24){
              //SeeHead = 0;
              count = 0;
              }*/
            count = 0;
          }
          break;
        } else { //------------------ send to braille display ----------------------
          hexPrep = BLEConBuffer[j];
          //  cell_sentdata(~0x01);
          //  delay_ms(50);
          if (hexPrep != 0xff && hexPrep != 0xa3 && hexPrep != 0x14) { //ff ff 3a
            cell_sentdata(~hexPrep);
            //delay_ms(10);
          }
        }
      }
      pushToDisplay = 0;
      count = 0;
      //  printf("\r\n");
    }
  }
}
void ConnectBLE() {
  int x = 0;
  while (x < sizeof(connectData) / sizeof(int))
  {
    USART_SendData(UART4, connectData[x++]);
    while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)
    {
    }
  }
}
void SendCommandToBLE2(int data) {
  USART_SendData(UART4, data);
  while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)
  {
  }
}
void SendCH370(int data[], int sizeOfData) {
  int x  = 0;
  while (x < sizeOfData / sizeof(int))
  {
    USART_SendData(USART3, data[x++]);
    while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
    {
    }
  }
}
void SendCommandToBLE(int data[], int sizeOfData) {
  int x  = 0;
  while (x < sizeOfData / sizeof(int))
  {
    USART_SendData(UART4, data[x++]);
    while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)
    {
    }
  }
}
void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount)  //UARTSend(menu,sizeof(menu));
{
  while (ulCount--)
  {
    USART_SendData(USART1, *pucBuffer++);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
    }
  }
}

void UART4Send(const unsigned char *pucBuffer, unsigned long ulCount)  //UARTSend(menu,sizeof(menu));
{
  while (ulCount--)
  {
    USART_SendData(UART4, *pucBuffer++);
    while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)
    {
    }
  }
}
/*******************************************************************************
  Function Name  : GPIO_Configuration
  Description    : Configures the different GPIO ports.
  Input          : None
  Output         : None
  Return         : None
  Attention    : None
*******************************************************************************/
void sendUart(int data) {
  switch (data) {
    case 1: sendUart1 = 1; break;
    case 2: sendUart2 = 1; break;
    case 3: sendUart3 = 1; break;
    case 4: sendUart4 = 1; break;
    default :
      sendUart1 = 0;
      sendUart2 = 0;
      sendUart3 = 0;
      sendUart4 = 0;
      break;
  }
}

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE);
  /* Configure PB.02 (ADC Channel8) as analog input -------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*******************************************************************************
  Function Name  : USART_Configuration
  Description    : Configure USART1
  Input          : None
  Output         : None
  Return         : None
  Attention    : None
*******************************************************************************/
void UART4_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  /* RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,DISABLE);
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);*/

  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
  /*
     USART1_TX -> PA9 , USART1_RX ->  PA10
  */
  /* tx */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  /* rx */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(UART4, &USART_InitStructure);
  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
  USART_ITConfig(UART4, USART_IT_TXE, ENABLE);
  USART_ClearFlag(UART4, USART_FLAG_TC);
  USART_Cmd(UART4, ENABLE);
}
void USART1_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
  /*
     USART1_TX -> PA9 , USART1_RX ->  PA10
  */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART1, &USART_InitStructure);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
  USART_ClearFlag(USART1, USART_FLAG_TC);
  USART_Cmd(USART1, ENABLE);
}
void USART3_Configuration(void)
{

  GPIO_InitTypeDef GPIO_InitStructure31;
  USART_InitTypeDef USART_InitStructure31;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  /*
     USART1_TX -> PA9 , USART1_RX ->  PA10
  */
  GPIO_InitStructure31.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure31.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure31.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure31);

  GPIO_InitStructure31.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure31.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure31.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure31);

  USART_InitStructure31.USART_BaudRate = 9600;
  USART_InitStructure31.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure31.USART_StopBits = USART_StopBits_1;
  USART_InitStructure31.USART_Parity = USART_Parity_No;
  USART_InitStructure31.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure31.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART3, &USART_InitStructure31);
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
  USART_ClearFlag(USART3, USART_FLAG_TC);
  USART_Cmd(USART3, ENABLE);
}
void USART3_Configuration2(void)
{
  GPIO_InitTypeDef GPIO_InitStructure3;
  USART_InitTypeDef USART_InitStructure3;


  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  /*
     USART1_TX -> PA9 , USART1_RX ->  PA10
  */
  GPIO_InitStructure3.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure3.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure3.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure3);

  GPIO_InitStructure3.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure3.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure3.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure3);

  USART_InitStructure3.USART_BaudRate = 115200;
  USART_InitStructure3.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure3.USART_StopBits = USART_StopBits_1;
  USART_InitStructure3.USART_Parity = USART_Parity_No;
  USART_InitStructure3.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure3.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART3, &USART_InitStructure3);
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
  USART_ClearFlag(USART3, USART_FLAG_TC);
  USART_Cmd(USART3, ENABLE);
}
void USART2_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  /*
     USART1_TX -> PA9 , USART1_RX ->  PA10
  */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART2, &USART_InitStructure);
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
  USART_ClearFlag(USART2, USART_FLAG_TC);
  USART_Cmd(USART2, ENABLE);
}
/*******************************************************************************
  Function Name  : ADC_Configuration
  Description    : Configure the ADC.
  Input          : None
  Output         : None
  Return         : None
  Attention    : None
*******************************************************************************/
void ADC_Configuration(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  DMA_InitTypeDef DMA_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_AFIO, ENABLE);
  /* DMA channel1 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);

  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);

  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel8 configuration */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);

  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibaration register */
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while (ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibaration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while (ADC_GetCalibrationStatus(ADC1));

  /* Start ADC1 Software Conversion */
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

/**
    @brief  Retargets the C library printf function to the USART.
    @param  None
    @retval None
*/
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  //USART_SendData(UART4, (uint8_t) ch);
  if (sendUart1 == 1) {
    USART_SendData(USART1, (uint8_t) ch);
  }
  if (sendUart2 == 1) {
    USART_SendData(USART2, (uint8_t) ch);
  }
  if (sendUart3 == 1) {
    USART_SendData(USART3, (uint8_t) ch);
  }
  //USART_SendData(UART4, (uint8_t) ch);
  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
  {}
  while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
  {}
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}
  return ch;
}

#ifdef  USE_FULL_ASSERT

/**
    @brief  Reports the name of the source file and the source line number
      where the assert_param error has occurred.
    @param  file: pointer to the source file name
    @param  line: assert_param error line source number
    @retval None
*/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
