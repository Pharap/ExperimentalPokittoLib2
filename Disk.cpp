#include "Disk.h"

#include "Macros.h"

constexpr uint32_t SDMosiPort = 0;
constexpr uint32_t SDMisoPort = 0;
constexpr uint32_t SDSckPort = 0;
constexpr uint32_t SDCsPort = 0;

constexpr uint32_t SDMosiPin = 9;
constexpr uint32_t SDMisoPin = 8;
constexpr uint32_t SDSckPin = 6;
constexpr uint32_t SDCsPin = 7;

SD_CODE_SECTION void initSDGpio(void)
{
	LPC_GPIO_PORT->DIR[SDMosiPort] |= (1 << SDMosiPin);
	LPC_GPIO_PORT->DIR[SDMisoPort] |= (1 << SDMisoPin);
	LPC_GPIO_PORT->DIR[SDSckPort] |= (1 << SDSckPin);
	LPC_GPIO_PORT->DIR[SDCsPort] |= (1 << SDCsPin);
}

PFFS::BYTE res;
PFFS::FATFS fs;            /* File system object */
PFFS::FATDIR dir;            /* Directory object */
PFFS::FILINFO fno;        /* File information */

//static FATFS *FatFs;    /* Pointer to the file system object (logical drive) */

bool diropened=false;

#define SPEAKER 3
//#define BUFFER_SIZE 256 // was 128
#define SONGLENGTH 0x1BFBCD // 1072223
#define FILESIZE 0x1BFBCD

uint8_t filemode = FILE_MODE_UNINITIALIZED;
char currentfile[15]; // holds current file's name

SPI device(CONNECT_MOSI,CONNECT_MISO,CONNECT_SCK);
//DigitalOut mmccs(CONNECT_CS);

SD_CODE_SECTION int initialiseSD(void)
{
	initSDGpio();
	
    /*res = PFFS::disk_initialize();
    //res = disk_initialize(0);
    res = (pf_mount(&fs));
    res = pf_opendir(&dir,"");
    if (res) diropened=false;
    else diropened=true;
return res;*/
}

const char * getFilenameExt(const char * filename)
{
	const char * dot = strrchar(filename, '.');
	if(dot == nullptr || dot == filename)
		return "";
	else
		return &dot[1];
}

