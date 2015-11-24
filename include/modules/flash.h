/**
 * @file	flash.h
 * @author  Eriks Zaharans
 * @date    24 Nov 2015
 *
 * @section DESCRIPTION
 *
 * Flash memory library header file.
 */

#ifndef __FLASH_H
#define __FLASH_H

/* -- Includes -- */

/* -- Defines -- */

#define s_FLASH__NSS_PORT		GPIOB
#define s_FLASH__NSS			GPIO_PIN_11
#define s_FLASH__NSS_SET()		s_FLASH__NSS_PORT->BSRR = s_FLASH__NSS
#define s_FLASH__NSS_RESET()	s_FLASH__NSS_PORT->BSRR = s_FLASH__NSS << 16



#define s_FLASH__PARAMETER_SECTOR_SIZE			4096
#define s_FLASH__PARAMETER_SECTOR_COUNT			16
#define s_FLASH__PARAMETER_BLOCK_SIZE			(s_FLASH__PARAMETER_SECTOR_SIZE * s_FLASH__PARAMETER_SECTOR_COUNT)

#define s_FLASH__DATA_SECTOR_SIZE				65536
#define s_FLASH__DATA_SECTOR_COUNT				255


// Flash Instructions
#define s_FLASH__CMD_WR_ENABLE					0x06
#define s_FLASH__CMD_WR_ENABLE_STATUS_REG		0x50
#define s_FLASH__CMD_WR_DISABLE					0x04
#define s_FLASH__CMD_RD_STATUS_REG1          	0x05
#define s_FLASH__CMD_RD_STATUS_REG2          	0x35
#define s_FLASH__CMD_WR_STATUS_REG           	0x01
#define s_FLASH__CMD_PAGE_PROGRAM            	0x02
#define s_FLASH__CMD_QUAD_PAGE_PROGRAM       	0x32
#define s_FLASH__CMD_SECTOR_ERASE_4KB          	0x20        // 4KB
#define s_FLASH__CMD_BULK_ERASE		      		0x60
#define s_FLASH__CMD_SECTOR_ERASE_64KB  		0xD8
#define s_FLASH__CMD_CHIP_ERASE              	0xC7        // Alternative: 0x60
#define s_FLASH__CMD_ERASE_PROGRAM_SUSPEND   	0x75
#define s_FLASH__CMD_ERASE_PROGRAM_RESUME    	0x7A
#define s_FLASH__CMD_POWER_DOWN              	0xB9
#define s_FLASH__CMD_CONT_READ_MODE_RST      	0xFF        // Need to be sent twice

#define s_FLASH__CMD_RD_DATA                 0x03
#define s_FLASH__CMD_FAST_RD                 0x0B
#define s_FLASH__CMD_FAST_RD_DUAL_O          0x3B
#define s_FLASH__CMD_FAST_RD_QUAD_O          0x6B
#define s_FLASH__CMD_FAST_RD_DUAL_IO         0xBB
#define s_FLASH__CMD_FAST_RD_QUAD_IO         0xEB
#define s_FLASH__CMD_WORD_RD_QUAD_IO         0xE7
#define s_FLASH__CMD_OCTAL_WORD_RD_QUAD_IO   0xE3
#define s_FLASH__CMD_SET_BURST_WITH_WRAP     0x77

#define s_FLASH__CMD_RELEASE_PWRDOWN_DEV_ID  0xAB
#define s_FLASH__CMD_MANUF_DEV_ID            0x90
#define s_FLASH__CMD_MANUF_DEV_ID_DUAL_IO    0x92
#define s_FLASH__CMD_MANUF_DEV_IF_QUAD_IO    0x94
#define s_FLASH__CMD_JEDEC_ID                0x9F
#define s_FLASH__CMD_RD_UNIQUE_ID            0x4B
#define s_FLASH__CMD_RD_SFDP_REG             0x48        // Alternative: 0x5A
#define s_FLASH__CMD_ERASE_SECURITY_REG      0x44
#define s_FLASH__CMD_PROGRAM_SECURITY_REG    0x42
#define s_FLASH__CMD_READD_SECURITY_REG      0x48


// Status Register 1 Bits
#define s_FLASH__STATUS_REG1_BUSY            0x01    // Erase/Program in progress
#define s_FLASH__STATUS_REG1_WEL             0x02    // Write Enable Latch
#define s_FLASH__STATUS_REG1_BP0             0x04    // Block Protect Bit 0 (nv)
#define s_FLASH__STATUS_REG1_BP1             0x08    // Block Protect Bit 1 (nv)
#define s_FLASH__STATUS_REG1_BP2             0x10    // Block Protect Bit 2 (nv)
#define s_FLASH__STATUS_REG1_TB              0x20    // Top/Bottom Prottect (nv)
#define s_FLASH__STATUS_REG1_SEC             0x40    // Sector Protect (nv)
#define s_FLASH__STATUS_REG1_SRP0            0x80    // Status Register Protect 0 (nv)

// Status Register 2 Bits
#define s_FLASH__STATUS_REG2_SRP1            0x01    // Status Register Protect 1 (nv)
#define s_FLASH__STATUS_REG2_QE              0x02    // Quad Enable (nv)
#define s_FLASH__STATUS_REG2_LB1             0x08    // Security Register Lock Bit 1 (nv OTP)
#define s_FLASH__STATUS_REG2_LB2             0x10    // Security Register Lock Bit 2 (nv OTP)
#define s_FLASH__STATUS_REG2_LB3             0x20    // Security Register Lock Bit 3 (nv OTP)
#define s_FLASH__STATUS_REG2_CMP             0x40    // Complement Protect (nv)
#define s_FLASH__STATUS_REG2_SUS             0x80    // Suspend Status

/* -- Constants -- */

/* -- Enumerations -- */

// Enumerations
typedef enum
{
	s_FLASH_ERASE_4KB = 0,
	s_FLASH_ERASE_64KB,
	s_FLASH_ERASE_ALL
}  FlashEraseSize_t;

/* -- Types -- */

// Structures
typedef struct
{
	uint8_t manufacturer_id;
	uint8_t dev_id;
	uint8_t unique_id[8];
} FlashInfo_t;

/* -- Extern -- */


/* -- Function Prototypes -- */

void Flash_Init(void);
void Flash_Deinit(void);

void Flash_Command(uint8_t Cmd);
void Flash_WaitBusy(void);
void Flash_Program(uint32_t Addr, uint8_t *Data, uint8_t Size);
void Flash_Read(uint32_t Addr, uint8_t *Data, uint8_t Size);
void Flash_EraseSector(uint16_t Sector);
void Flash_EraseChip(void);
void Flash_ReadInfo(FlashInfo_t *Info);



#endif /* __COMM_H */
