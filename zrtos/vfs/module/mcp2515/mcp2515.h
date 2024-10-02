/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_MCP2515_H
#define ZRTOS_VFS_MODULE_MCP2515_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/vfs_module.h>
#include <zrtos/mem.h>
#include <zrtos/va.h>

#define ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE(cfg1,cfg2,cfg3)\
	((cfg1) | ((cfg2)<<8) | ((cfg3)<<16))

typedef enum{
	 ZRTOS_VFS_MODULE_MCP2515_BITRATE__MIN            = ZRTOS_TYPES__UINT32_MIN
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__8MHz_1000kBPS  = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x00),(0x80),(0x80))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__8MHz_500kBPS   = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x00),(0x90), (0x82))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__8MHz_250kBPS   = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x00),(0xB1), (0x85))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__8MHz_200kBPS   = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x00),(0xB4), (0x86))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__8MHz_125kBPS   = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x01),(0xB1), (0x85))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__8MHz_100kBPS   = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x01),(0xB4), (0x86))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__8MHz_80kBPS    = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x01),(0xBF), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__8MHz_50kBPS    = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x03),(0xB4), (0x86))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__8MHz_40kBPS    = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x03),(0xBF), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__8MHz_33k3BPS   = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x47), (0xE2), (0x85))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__8MHz_31k25BPS  = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x07), (0xA4), (0x84))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__8MHz_20kBPS    = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x07),(0xBF), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__8MHz_10kBPS    = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x0F),(0xBF), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__8MHz_5kBPS     = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x1F),(0xBF), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__16MHz_1000kBPS = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x00),(0xD0), (0x82))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__16MHz_500kBPS  = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x00),(0xF0), (0x86))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__16MHz_250kBPS  = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x41),(0xF1), (0x85))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__16MHz_200kBPS  = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x01),(0xFA), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__16MHz_125kBPS  = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x03),(0xF0), (0x86))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__16MHz_100kBPS  = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x03),(0xFA), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__16MHz_95kBPS   = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x03),(0xAD), (0x07))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__16MHz_83k3BPS  = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x03), (0xBE), (0x07))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__16MHz_80kBPS   = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x03),(0xFF), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__16MHz_50kBPS   = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x07),(0xFA), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__16MHz_40kBPS   = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x07),(0xFF), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__16MHz_33k3BPS  = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x4E), (0xF1), (0x85))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__16MHz_20kBPS   = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x0F),(0xFF), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__16MHz_10kBPS   = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x1F),(0xFF), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__16MHz_5kBPS    = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x3F),(0xFF), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__20MHz_1000kBPS = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x00),(0xD9), (0x82))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__20MHz_500kBPS  = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x00),(0xFA), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__20MHz_250kBPS  = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x41),(0xFB), (0x86))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__20MHz_200kBPS  = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x01),(0xFF), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__20MHz_125kBPS  = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x03),(0xFA), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__20MHz_100kBPS  = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x04),(0xFA), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__20MHz_83k3BPS  = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x04), (0xFE), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__20MHz_80kBPS   = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x04),(0xFF), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__20MHz_50kBPS   = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x09),(0xFA), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__20MHz_40kBPS   = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x09),(0xFF), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__20MHz_33k3BPS  = ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE((0x0B), (0xFF), (0x87))
	,ZRTOS_VFS_MODULE_MCP2515_BITRATE__MAX            = ZRTOS_TYPES__UINT32_MAX
}zrtos_vfs_module_mcp2515_bitrate_t;

#undef ZRTOS_VFS_MODULE_MCP2515_BITRATE__COMBINE

uint8_t zrtos_vfs_module_mcp2515_bitrate__get_cfg1(zrtos_vfs_module_mcp2515_bitrate_t thiz){
	return thiz & 0xFF;
}

uint8_t zrtos_vfs_module_mcp2515_bitrate__get_cfg2(zrtos_vfs_module_mcp2515_bitrate_t thiz){
	return (thiz >> 8) & 0xFF;
}

uint8_t zrtos_vfs_module_mcp2515_bitrate__get_cfg3(zrtos_vfs_module_mcp2515_bitrate_t thiz){
	return (thiz >> 16) & 0xFF;
}

typedef enum{
	ZRTOS_VFS_MODULE_MCP2515_MASK__MASK0 = ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXM0SIDH,
	ZRTOS_VFS_MODULE_MCP2515_MASK__MASK1 = ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXM1SIDH
}zrtos_vfs_module_mcp2515_mask_t;

typedef enum/*enum zrtos_vfs_module_mcp2515_register_rxf_t */{
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXF__RXF0 = ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF0SIDH,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXF__RXF1 = ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF1SIDH,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXF__RXF2 = ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF2SIDH,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXF__RXF3 = ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF3SIDH,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXF__RXF4 = ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF4SIDH,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXF__RXF5 = ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF5SIDH
}zrtos_vfs_module_mcp2515_register_rxf_t;

typedef enum /*uint8_t*/{
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANINTF__RX0IF = 0x01,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANINTF__RX1IF = 0x02,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANINTF__TX0IF = 0x04,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANINTF__TX1IF = 0x08,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANINTF__TX2IF = 0x10,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANINTF__ERRIF = 0x20,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANINTF__WAKIF = 0x40,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANINTF__MERRF = 0x80
}zrtos_vfs_module_mcp2515_register_canintf_t;

typedef enum /*uint8_t*/{
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL__REQOP = 0xE0,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL__ABAT = 0x10,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL__OSM = 0x08,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL__CLKEN = 0x04,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL__CLKPRE = 0x03
}zrtos_vfs_module_mcp2515_register_canctrl_t;

typedef enum /*uint8_t*/{
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL_REQOP__NORMAL     = 0x00,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL_REQOP__SLEEP      = 0x20,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL_REQOP__LOOPBACK   = 0x40,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL_REQOP__LISTENONLY = 0x60,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL_REQOP__CONFIG     = 0x80,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL_REQOP__POWERUP    = 0xE0
}zrtos_vfs_module_mcp2515_register_canctrl_reqop_t;

typedef enum /*uint8_t*/{
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANSTAT__OPMOD = 0xE0,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANSTAT__ICOD = 0x0E
}zrtos_vfs_module_mcp2515_register_canstat_t;

typedef enum /*class TXBnCTRL : uint8_t */{
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_TXBNCTRL__ABTF   = 0x40,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_TXBNCTRL__MLOA   = 0x20,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_TXBNCTRL__TXERR  = 0x10,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_TXBNCTRL__TXREQ  = 0x08,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_TXBNCTRL__TXIE   = 0x04,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER_TXBNCTRL__TXP    = 0x03
}zrtos_vfs_module_mcp2515_register_txbnctrl_t;

typedef enum /*uint8_t*/{
	 ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXBNCTRL__RXM_STD    = 0x20
	,ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXBNCTRL__RXM_EXT    = 0x40
	,ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXBNCTRL__RXM_STDEXT = 0x00
	,ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXBNCTRL__RXM_MASK   = 0x60
	,ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXBNCTRL__RTR        = 0x08
}zrtos_vfs_module_mcp2515_register_rxbnctrl_t;

typedef enum /*uint8_t*/{
	 ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXB0CTRL__BUKT        = 0x04
	,ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXB0CTRL__FILHIT_MASK = 0x03
	,ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXB0CTRL__FILHIT      = 0x00
}zrtos_vfs_module_mcp2515_register_rxb0ctrl_t;

typedef enum /*uint8_t*/{
	 ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXB1CTRL__FILHIT_MASK = 0x07
	,ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXB1CTRL__FILHIT      = 0x01
}zrtos_vfs_module_mcp2515_register_rxb1ctrl_t;

typedef enum /*uint8_t*/{
	 ZRTOS_VFS_MODULE_MCP2515_REGISTER_CNF3__SOF = 0x80
}zrtos_vfs_module_mcp2515_register_cnf3_t;

        static uint8_t  = 0x08;
typedef enum /*uint8_t */{
	 ZRTOS_VFS_MODULE_MCP2515_MCP_SIDL__TXB_EXIDE_MASK       = 0x08
}zrtos_vfs_module_mcp2515_mcp_sidl_t;

typedef enum /*uint8_t */{
	 ZRTOS_VFS_MODULE_MCP2515_MCP_DLC__RTR_MASK       = 0x40
	,ZRTOS_VFS_MODULE_MCP2515_MCP_DLC__DLC_MASK       = 0x0F
}zrtos_vfs_module_mcp2515_mcp_dlc_t;

typedef enum /*uint8_t */{
	 ZRTOS_VFS_MODULE_MCP2515_MCP__SIDH = 0
	,ZRTOS_VFS_MODULE_MCP2515_MCP__SIDL = 1
	,ZRTOS_VFS_MODULE_MCP2515_MCP__EID8 = 2
	,ZRTOS_VFS_MODULE_MCP2515_MCP__EID0 = 3
	,ZRTOS_VFS_MODULE_MCP2515_MCP__DLC  = 4
	,ZRTOS_VFS_MODULE_MCP2515_MCP__DATA = 5
}zrtos_vfs_module_mcp2515_mcp_t;

typedef enum /*uint8_t */{
	ZRTOS_VFS_MODULE_MCP2515_STATUS__RX0IF = (1<<0),
	ZRTOS_VFS_MODULE_MCP2515_STATUS__RX1IF = (1<<1),
	ZRTOS_VFS_MODULE_MCP2515_STATUS__RXIF_MASK = (
		  ZRTOS_VFS_MODULE_MCP2515_STATUS__RX0IF
		| ZRTOS_VFS_MODULE_MCP2515_STATUS__RX1IF
	)
}zrtos_vfs_module_mcp2515_status_t;

typedef enum{
	ZRTOS_VFS_MODULE_MCP2515_CLKOUT__MIN     = ZRTOS_TYPES__INT8_MIN,
	ZRTOS_VFS_MODULE_MCP2515_CLKOUT__DISABLE = -1,
	ZRTOS_VFS_MODULE_MCP2515_CLKOUT__DIV1    = 0x0,
	ZRTOS_VFS_MODULE_MCP2515_CLKOUT__DIV2    = 0x1,
	ZRTOS_VFS_MODULE_MCP2515_CLKOUT__DIV4    = 0x2,
	ZRTOS_VFS_MODULE_MCP2515_CLKOUT__DIV8    = 0x3,
	ZRTOS_VFS_MODULE_MCP2515_CLKOUT__MAX     = ZRTOS_TYPES__INT8_MAX
}zrtos_vfs_module_mcp2515_clkout_t;

typedef enum{
	ZRTOS_VFS_MODULE_MCP2515_ERROR_FLAG__MIN         = ZRTOS_TYPES__UINT8_MIN,
	ZRTOS_VFS_MODULE_MCP2515_ERROR_FLAG__RX1OVR = (1<<7),
	ZRTOS_VFS_MODULE_MCP2515_ERROR_FLAG__RX0OVR = (1<<6),
	ZRTOS_VFS_MODULE_MCP2515_ERROR_FLAG__TXBO   = (1<<5),
	ZRTOS_VFS_MODULE_MCP2515_ERROR_FLAG__TXEP   = (1<<4),
	ZRTOS_VFS_MODULE_MCP2515_ERROR_FLAG__RXEP   = (1<<3),
	ZRTOS_VFS_MODULE_MCP2515_ERROR_FLAG__TXWAR  = (1<<2),
	ZRTOS_VFS_MODULE_MCP2515_ERROR_FLAG__RXWAR  = (1<<1),
	ZRTOS_VFS_MODULE_MCP2515_ERROR_FLAG__EWARN  = (1<<0),
	ZRTOS_VFS_MODULE_MCP2515_ERROR_FLAG__ERRORMASK = (ZRTOS_VFS_MODULE_MCP2515_ERROR_FLAG__RX1OVR
                                            | ZRTOS_VFS_MODULE_MCP2515_ERROR_FLAG__RX0OVR
                                            | ZRTOS_VFS_MODULE_MCP2515_ERROR_FLAG__TXBO
                                            | ZRTOS_VFS_MODULE_MCP2515_ERROR_FLAG__TXEP
                                            | ZRTOS_VFS_MODULE_MCP2515_ERROR_FLAG__RXEP),
	ZRTOS_VFS_MODULE_MCP2515_ERROR_FLAG__MAX         = ZRTOS_TYPES__UINT8_MAX
}zrtos_vfs_module_mcp2515_error_flag_t;

typedef enum{
	ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__MIN         = ZRTOS_TYPES__UINT8_MIN,
	ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__WRITE       = 0x02,
	ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__READ        = 0x03,
	ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__BITMOD      = 0x05,
	ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__LOAD_TX0    = 0x40,
	ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__LOAD_TX1    = 0x42,
	ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__LOAD_TX2    = 0x44,
	ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__RTS_TX0     = 0x81,
	ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__RTS_TX1     = 0x82,
	ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__RTS_TX2     = 0x84,
	ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__RTS_ALL     = 0x87,
	ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__READ_RX0    = 0x90,
	ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__READ_RX1    = 0x94,
	ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__READ_STATUS = 0xA0,
	ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__RX_STATUS   = 0xB0,
	ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__RESET       = 0xC0,
	ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__MAX         = ZRTOS_TYPES__UINT8_MAX
}zrtos_vfs_module_mcp2515_instruction_t;

typedef enum{
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__MIN      = ZRTOS_TYPES__UINT8_MIN,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF0SIDH = 0x00,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF0SIDL = 0x01,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF0EID8 = 0x02,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF0EID0 = 0x03,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF1SIDH = 0x04,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF1SIDL = 0x05,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF1EID8 = 0x06,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF1EID0 = 0x07,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF2SIDH = 0x08,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF2SIDL = 0x09,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF2EID8 = 0x0A,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF2EID0 = 0x0B,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__CANSTAT  = 0x0E,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__CANCTRL  = 0x0F,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF3SIDH = 0x10,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF3SIDL = 0x11,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF3EID8 = 0x12,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF3EID0 = 0x13,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF4SIDH = 0x14,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF4SIDL = 0x15,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF4EID8 = 0x16,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF4EID0 = 0x17,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF5SIDH = 0x18,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF5SIDL = 0x19,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF5EID8 = 0x1A,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXF5EID0 = 0x1B,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TEC      = 0x1C,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__REC      = 0x1D,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXM0SIDH = 0x20,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXM0SIDL = 0x21,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXM0EID8 = 0x22,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXM0EID0 = 0x23,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXM1SIDH = 0x24,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXM1SIDL = 0x25,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXM1EID8 = 0x26,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXM1EID0 = 0x27,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__CNF3     = 0x28,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__CNF2     = 0x29,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__CNF1     = 0x2A,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__CANINTE  = 0x2B,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__CANINTF  = 0x2C,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__EFLG     = 0x2D,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB0CTRL = 0x30,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB0SIDH = 0x31,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB0SIDL = 0x32,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB0EID8 = 0x33,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB0EID0 = 0x34,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB0DLC  = 0x35,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB0DATA = 0x36,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB1CTRL = 0x40,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB1SIDH = 0x41,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB1SIDL = 0x42,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB1EID8 = 0x43,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB1EID0 = 0x44,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB1DLC  = 0x45,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB1DATA = 0x46,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB2CTRL = 0x50,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB2SIDH = 0x51,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB2SIDL = 0x52,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB2EID8 = 0x53,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB2EID0 = 0x54,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB2DLC  = 0x55,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB2DATA = 0x56,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB0CTRL = 0x60,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB0SIDH = 0x61,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB0SIDL = 0x62,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB0EID8 = 0x63,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB0EID0 = 0x64,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB0DLC  = 0x65,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB0DATA = 0x66,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB1CTRL = 0x70,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB1SIDH = 0x71,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB1SIDL = 0x72,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB1EID8 = 0x73,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB1EID0 = 0x74,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB1DLC  = 0x75,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB1DATA = 0x76,
	ZRTOS_VFS_MODULE_MCP2515_REGISTER__MAX      = ZRTOS_TYPES__UINT8_MAX
}zrtos_vfs_module_mcp2515_register_t;

typedef enum{
	ZRTOS_VFS_MODULE_MCP2515_RXBN__RXB0 = 0,
	ZRTOS_VFS_MODULE_MCP2515_RXBN__RXB1 = 1,
	ZRTOS_VFS_MODULE_MCP2515_RXBN__LENGTH = 2
}zrtos_vfs_module_mcp2515_rxbn_t;

typedef enum{
	ZRTOS_VFS_MODULE_MCP2515_TXBN__TXB0 = 0,
	ZRTOS_VFS_MODULE_MCP2515_TXBN__TXB1 = 1,
	ZRTOS_VFS_MODULE_MCP2515_TXBN__TXB2 = 2,
	ZRTOS_VFS_MODULE_MCP2515_TXBN__LENGTH = 3
}zrtos_vfs_module_mcp2515_txbn_t;

typedef struct{
	zrtos_vfs_module_mcp2515_register_t ctrl;
	zrtos_vfs_module_mcp2515_register_t sidh;
	zrtos_vfs_module_mcp2515_register_t data;
}zrtos_vfs_module_mcp2515_txbn_regs_t;

typedef struct{
	zrtos_vfs_module_mcp2515_register_t ctrl;
	zrtos_vfs_module_mcp2515_register_t sidh;
	zrtos_vfs_module_mcp2515_register_t data;
	zrtos_vfs_module_mcp2515_register_canintf_t rxnif;
}zrtos_vfs_module_mcp2515_rxbn_regs_t;

typedef struct{
	uint8_t data[4];
}zrtos_vfs_module_mcp2515_id_t;

void *zrtos_vfs_module_mcp2515_id__get_buffer(zrtos_vfs_module_mcp2515_id_t *thiz){
	return thiz->data;
}

size_t zrtos_vfs_module_mcp2515_id__get_length(zrtos_vfs_module_mcp2515_id_t *thiz){
	return 4;
}

zrtos_error_t zrtos_vfs_module_mcp2515__read_registers(
	 zrtos_vfs_module_mcp2515_register_t reg
	,uint8_t *values
	,size_t  values_length
){
	uint8_t buffer[] = {
		 ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__READ
		,reg
	};
	
	zrtos_error_t ret = zrtos_vfs_fd__spi_transfer(
		 fd
		,2
		,buffer
		,ZRTOS_TYPES__GET_STATIC_ARRAY_LENGTH(buffer)
		,values
		,values_length
	);

	return ret;
}

zrtos_error_t zrtos_vfs_module_mcp2515__read_register(
	 zrtos_vfs_fd_t fd
	,zrtos_vfs_module_mcp2515_register_t reg
	,uint8_t *value
){
	return zrtos_vfs_module_mcp2515__read_registers(
		 fd
		,reg
		,value
		,1
	);
}

zrtos_error_t zrtos_vfs_module_mcp2515__set_registers(
	 zrtos_vfs_module_mcp2515_register_t reg
	,uint8_t *values
	,size_t values_length
){
	uint8_t buffer[] = {
		 ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__WRITE
		,reg
	};
	
	zrtos_error_t ret = zrtos_vfs_fd__spi_transfer(
		 fd
		,2
		,buffer
		,ZRTOS_TYPES__GET_STATIC_ARRAY_LENGTH(buffer)
		,values
		,values_length
	);

	return ret;
}

zrtos_error_t zrtos_vfs_module_mcp2515__set_register(
	zrtos_vfs_fd_t fd
	,zrtos_vfs_module_mcp2515_register_t reg
	,uint8_t value
){
	return zrtos_vfs_module_mcp2515__set_registers(
		 fd
		,reg
		,&value
		,1
	);
}

zrtos_error_t zrtos_vfs_module_mcp2515__modify_register(
	zrtos_vfs_fd_t fd
	,zrtos_vfs_module_mcp2515_register_t reg
	,uint8_t mask
	,uint8_t data
){
	uint8_t buffer[] = {
		 ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__BITMOD
		,reg
		,mask
		,data
	};

	zrtos_error_t ret = zrtos_vfs_fd__spi_transfer(
		 fd
		,1
		,buffer
		,ZRTOS_TYPES__GET_STATIC_ARRAY_LENGTH(buffer)
	);

	return ret;
}

uint8_t zrtos_vfs_module_mcp2515__get_status(
	zrtos_vfs_fd_t fd
	,uint8_t *res
){
	uint8_t buffer[] = {
		 ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__READ_STATUS
	};

	zrtos_error_t ret = zrtos_vfs_fd__spi_transfer(
		 fd
		,2
		,buffer
		,ZRTOS_TYPES__GET_STATIC_ARRAY_LENGTH(buffer)
		,res
		,1
	);

	return ret;
}

zrtos_error_t zrtos_vfs_module_mcp2515__set_mode(
	 zrtos_vfs_fd_t fd
	,zrtos_vfs_module_mcp2515_register_canctrl_reqop_t mode
){
	zrtos_error_t ret = zrtos_vfs_module_mcp2515__modify_register(
		 fd
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER__CANCTRL
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL__REQOP
		,mode
	);
	size_t l = 10;
	bool modeMatch = false;

	if(zrtos_error__is_success(ret)){
		while(l--){
			uint8_t newmode;
			ret = zrtos_vfs_module_mcp2515__read_register(
				fd
				,ZRTOS_VFS_MODULE_MCP2515_REGISTER__CANSTAT
				,&newmode
			);
			if(!zrtos_error__is_success(ret)
			|| (modeMatch = mode == (newmode & ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANSTAT__OPMOD))){
				break;
			}
		}
	}

	if(zrtos_error__is_success(ret)){
		ret = modeMatch
			? ZRTOS_ERROR__SUCCESS
			: ZRTOS_ERROR__ERROR
		;
	}

	return ret;
}

zrtos_error_t zrtos_vfs_module_mcp2515__set_config_mode(zrtos_vfs_fd_t fd){
	return zrtos_vfs_module_mcp2515__set_mode(
		fd
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL_REQOP__CONFIG
	);
}

zrtos_error_t zrtos_vfs_module_mcp2515__set_listen_only_mode(zrtos_vfs_fd_t fd){
	return zrtos_vfs_module_mcp2515__set_mode(
		fd
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL_REQOP__LISTENONLY
	);
}

zrtos_error_t zrtos_vfs_module_mcp2515__set_sleep_mode(zrtos_vfs_fd_t fd){
	return zrtos_vfs_module_mcp2515__set_mode(
		fd
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL_REQOP__SLEEP
	);
}

zrtos_error_t zrtos_vfs_module_mcp2515__set_loopback_mode(zrtos_vfs_fd_t fd){
	return zrtos_vfs_module_mcp2515__set_mode(
		fd
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL_REQOP__LOOPBACK
	);
}

zrtos_error_t zrtos_vfs_module_mcp2515__set_normal_mode(zrtos_vfs_fd_t fd){
	return zrtos_vfs_module_mcp2515__set_mode(
		fd
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL_REQOP__NORMAL
	);
}

zrtos_error_t zrtos_vfs_module_mcp2515__set_bitrate(
	 zrtos_vfs_fd_t fd
	,zrtos_vfs_module_mcp2515_bitrate_t bitrate
){
	zrtos_error_t ret;
	if(zrtos_error__is_success(ret = zrtos_vfs_module_mcp2515__set_config_mode(
		fd
	))
	&& zrtos_error__is_success(ret = zrtos_vfs_module_mcp2515__set_register(
		 fd
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER__CNF1
		,zrtos_vfs_module_mcp2515_bitrate__get_cfg1(bitrate)
	))
	&& zrtos_error__is_success(ret = zrtos_vfs_module_mcp2515__set_register(
		 fd
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER__CNF2
		,zrtos_vfs_module_mcp2515_bitrate__get_cfg2(bitrate)
	))
	&& zrtos_error__is_success(ret = zrtos_vfs_module_mcp2515__set_register(
		 fd
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER__CNF3
		,zrtos_vfs_module_mcp2515_bitrate__get_cfg3(bitrate)
	))){
		continue;
	}
	return ret;
}

zrtos_error_t zrtos_vfs_module_mcp2515__set_clk_out(
	 zrtos_vfs_fd_t fd
	,zrtos_vfs_module_mcp2515_clkout_t divisor
){
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;
	uint8_t clken;
	uint8_t cnf3;

	if(divisor == ZRTOS_VFS_MODULE_MCP2515_CLKOUT__DISABLE){
		clken = 0x00;//Turn off CLKEN
		cnf3 = ZRTOS_VFS_MODULE_MCP2515_REGISTER_CNF3__SOF;//Turn on CLKOUT for SOF
	}else{
		clken = ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL__CLKEN;//Turn on CLKEN
		cnf3 = 0x00;//Turn off CLKOUT for SOF

		//Set the prescaler (CLKPRE)
		ret = zrtos_vfs_module_mcp2515__modify_register(
			 fd
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__CANCTRL
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL__CLKPRE
			,divisor
		);
	}

	if(zrtos_error__is_success(ret)
	&& zrtos_error__is_success((
		ret = zrtos_vfs_module_mcp2515__modify_register(
				fd
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__CANCTRL
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANCTRL__CLKEN
			,clken
		)
	))
	&& zrtos_error__is_success((
		ret = zrtos_vfs_module_mcp2515__modify_register(
			fd
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__CNF3
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER_CNF3__SOF
			,cnf3
		)
	))){
		continue;
	}

	return ret;
}

zrtos_error_t zrtos_vfs_module_mcp2515_id__init(
	 zrtos_vfs_module_mcp2515_id_t *thiz
	,bool ext
	,uint32_t id
){
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;
	uint8_t *buffer = thiz->data;
	uint16_t canid = (uint16_t)(id & 0x0FFFF);

	if(ext){
		if(id <= 536870911){
			buffer[ZRTOS_VFS_MODULE_MCP2515_MCP__EID0] = (uint8_t) (canid & 0xFF);
			buffer[ZRTOS_VFS_MODULE_MCP2515_MCP__EID8] = (uint8_t) (canid >> 8);
			canid = (uint16_t)(id >> 16);
			buffer[ZRTOS_VFS_MODULE_MCP2515_MCP__SIDL] = (uint8_t) (canid & 0x03);
			buffer[ZRTOS_VFS_MODULE_MCP2515_MCP__SIDL] += (uint8_t) ((canid & 0x1C) << 3);
			buffer[ZRTOS_VFS_MODULE_MCP2515_MCP__SIDL] |= ZRTOS_VFS_MODULE_MCP2515_MCP_SIDL__TXB_EXIDE_MASK;
			buffer[ZRTOS_VFS_MODULE_MCP2515_MCP__SIDH] = (uint8_t) (canid >> 5);
			goto L_RETURN;
		}
	}else{
		if(id <= 2047){
			buffer[ZRTOS_VFS_MODULE_MCP2515_MCP__SIDH] = (uint8_t) (canid >> 3);
			buffer[ZRTOS_VFS_MODULE_MCP2515_MCP__SIDL] = (uint8_t) ((canid & 0x07 ) << 5);
			buffer[ZRTOS_VFS_MODULE_MCP2515_MCP__EID0] = 0;
			buffer[ZRTOS_VFS_MODULE_MCP2515_MCP__EID8] = 0;
			goto L_RETURN;
		}
	}

	ret = ZRTOS_ERROR__INVAL;
L_RETURN:
	return ret;
}

static zrtos_error_t zrtos_vfs_module_mcp2515__set_filter_ex(
	 zrtos_vfs_fd_t fd
	,uint8_t reg
	,bool ext
	,uint32_t ulData
){
	zrtos_vfs_module_mcp2515_id_t tbufdata;
	zrtos_error_t ret = zrtos_vfs_module_mcp2515__set_config_mode(fd);
	
	if(zrtos_error__is_success(ret)
	&& zrtos_error__is_success((
		ret = zrtos_vfs_module_mcp2515_id__init(&tbufdata, ext, ulData)
	))){
		ret = zrtos_vfs_module_mcp2515__set_registers(
			 reg
			,zrtos_vfs_module_mcp2515_id__get_buffer(&tbufdata)
			,zrtos_vfs_module_mcp2515_id__get_length(&tbufdata)
		);
	}

	return ret;
}

zrtos_error_t zrtos_vfs_module_mcp2515__set_filter_mask(
	 zrtos_vfs_fd_t fd
	,zrtos_vfs_module_mcp2515_mask_t reg
	,bool ext
	,uint32_t ulData
){
	return zrtos_vfs_module_mcp2515__set_filter_ex(
		 fd
		,reg
		,ext
		,ulData
	);
}

zrtos_error_t zrtos_vfs_module_mcp2515__set_filter(
	 zrtos_vfs_fd_t fd
	,zrtos_vfs_module_mcp2515_register_rxf_t reg
	,bool ext
	,uint32_t ulData
){
	return zrtos_vfs_module_mcp2515__set_filter_ex(
		 fd
		,reg
		,ext
		,ulData
	);
}

zrtos_error_t zrtos_vfs_module_mcp2515__reset(zrtos_vfs_fd_t fd){
	uint8_t zeros[14] = {};
	zrtos_vfs_module_mcp2515_register_rxf_t filters[] = {
		 ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXF__RXF0
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXF__RXF1
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXF__RXF2
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXF__RXF3
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXF__RXF4
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXF__RXF5
	};
	zrtos_vfs_module_mcp2515_mask_t masks[] = {
		 ZRTOS_VFS_MODULE_MCP2515_MASK__MASK0
		,ZRTOS_VFS_MODULE_MCP2515_MASK__MASK1
	};
	uint8_t buffer[] = {
		 ZRTOS_VFS_MODULE_MCP2515_INSTRUCTION__RESET
	};
	zrtos_error_t ret = zrtos_vfs_fd__spi_transfer(
		 fd
		,1
		,buffer
		,ZRTOS_TYPES__GET_STATIC_ARRAY_LENGTH(buffer)
	);

	zrtos_gpio__delay_milliseconds(10);

	if(zrtos_error__is_success(ret)
	&& zrtos_error__is_success((
		ret = zrtos_vfs_module_mcp2515__set_registers(
			 fd
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB0CTRL
			,zeros
			,14
		)
	))
	&& zrtos_error__is_success((
		ret = zrtos_vfs_module_mcp2515__set_registers(
			 fd
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB1CTRL
			,zeros
			,14
		)
	))
	&& zrtos_error__is_success((
		ret = zrtos_vfs_module_mcp2515__set_registers(
			 fd
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB2CTRL
			,zeros
			,14
		)
	))
	&& zrtos_error__is_success((
		ret = zrtos_vfs_module_mcp2515__set_register(
			 fd
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB0CTRL
			,0
		)
	))
	&& zrtos_error__is_success((
		ret = zrtos_vfs_module_mcp2515__set_register(
			 fd
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB1CTRL
			,0
		)
	))
	&& zrtos_error__is_success((
		ret = zrtos_vfs_module_mcp2515__set_register(
			 fd
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__CANINTE
			,(
				  ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANINTF__RX0IF
				| ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANINTF__RX1IF
				| ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANINTF__ERRIF
				| ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANINTF__MERRF
			)
		)
	))
	&& zrtos_error__is_success((
		ret = zrtos_vfs_module_mcp2515__modify_register(
			 fd
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB0CTRL
			,(
				  ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXBNCTRL__RXM_MASK
				| ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXB0CTRL__BUKT
				| ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXB0CTRL__FILHIT_MASK
			),(
				  ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXBNCTRL__RXM_STDEXT
				| ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXB0CTRL__BUKT
				| ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXB0CTRL__FILHIT
			)
		)
	))
	&& zrtos_error__is_success((
		ret = zrtos_vfs_module_mcp2515__modify_register(
			 fd
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB1CTRL
			,(
				  ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXBNCTRL__RXM_MASK
				| ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXB1CTRL__FILHIT_MASK
			),(
				  ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXBNCTRL__RXM_STDEXT
				| ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXB1CTRL__FILHIT
			)
		)
	))){
		for(size_t i=0; i<ZRTOS_TYPES__GET_STATIC_ARRAY_LENGTH(filters); i++){
			ret = zrtos_vfs_module_mcp2515__set_filter(fd,filters[i],(i == 1),0);
			if(zrtos_error__is_error(ret)){
				goto L_RETURN;
			}
		}

		for(size_t i=0; i<ZRTOS_TYPES__GET_STATIC_ARRAY_LENGTH(masks); i++){
			ret = zrtos_vfs_module_mcp2515__set_filter_mask(masks[i], true, 0);
			if(zrtos_error__is_error(ret)){
				goto L_RETURN;
			}
		}
	}

L_RETURN:
	return ret;
}

zrtos_error_t zrtos_vfs_module_mcp2515__send_message_ex(
	 zrtos_vfs_fd_t fd
	,zrtos_vfs_module_mcp2515_txbn_regs_t txbn_regs
	,struct can_frame *frame
){
	zrtos_error_t ret;
	zrtos_vfs_module_mcp2515_id_t iddata;
	uint8_t data[13];
	bool ext;
	bool rtr;
	uint32_t id;
	uint8_t ctrl;

	if(frame->can_dlc <= CAN_MAX_DLEN){
		ext = (frame->can_id & CAN_EFF_FLAG);
		rtr = (frame->can_id & CAN_RTR_FLAG);
		id = (frame->can_id & (ext ? CAN_EFF_MASK : CAN_SFF_MASK));

		ret = zrtos_vfs_module_mcp2515_id__init(&iddata, ext, id);
		if(zrtos_error__is_success(ret)){
			memcpy(
				 &data[0]
				,zrtos_vfs_module_mcp2515_id__get_buffer(&iddata)
				,zrtos_vfs_module_mcp2515_id__get_length(&iddata)
			);

			data[ZRTOS_VFS_MODULE_MCP2515_MCP__DLC] = rtr
				? (
					  frame->can_dlc
					| ZRTOS_VFS_MODULE_MCP2515_MCP_DLC__RTR_MASK
				)
				: frame->can_dlc
			;

			memcpy(
				 &data[ZRTOS_VFS_MODULE_MCP2515_MCP__DATA]
				,frame->data
				,frame->can_dlc
			);

			if(zrtos_error__is_success((
				ret = zrtos_vfs_module_mcp2515__set_registers(
					 fd
					,txbn_regs.sidh
					,data
					,5 + frame->can_dlc
				)
			))
			&& zrtos_error__is_success((
				ret = zrtos_vfs_module_mcp2515__modify_register(
					 fd
					,txbn_regs.ctrl
					,ZRTOS_VFS_MODULE_MCP2515_REGISTER_TXBNCTRL__TXREQ
					,ZRTOS_VFS_MODULE_MCP2515_REGISTER_TXBNCTRL__TXREQ
				)
			))
			&& zrtos_error__is_success((
				ret = zrtos_vfs_module_mcp2515__read_register(
					 fd
					,txbn_regs.ctrl
					,&ctrl
				)
			))){
				if((ctrl & (
					  ZRTOS_VFS_MODULE_MCP2515_REGISTER_TXBNCTRL__ABTF
					| ZRTOS_VFS_MODULE_MCP2515_REGISTER_TXBNCTRL__MLOA
					| ZRTOS_VFS_MODULE_MCP2515_REGISTER_TXBNCTRL__TXERR
				)) != 0){
					ret = ZRTOS_ERROR__IO;
				}
			}
		}
	}else{
		ret = ZRTOS_ERROR__IO;
	}

	return ret;
}

zrtos_vfs_module_mcp2515_txbn_regs_t zrtos_vfs_module_mcp2515__get_txb(
	zrtos_vfs_module_mcp2515__txbn_t txbn
){
	zrtos_vfs_module_mcp2515_txbn_regs_t data[] = {
		{
			ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB0CTRL
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB0SIDH
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB0DATA
		}
		,{
			ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB1CTRL
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB1SIDH
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB1DATA
		}
		,{
			ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB2CTRL
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB2SIDH
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__TXB2DATA
		}
	};

	return data[txbn];
}

zrtos_error_t zrtos_vfs_module_mcp2515__get_available_txb(
	 zrtos_vfs_fd_t fd
	,zrtos_vfs_module_mcp2515_txbn_regs_t *txbn_regs
){
	zrtos_error_t ret;
	uint8_t ctrlval;

	for(size_t i=0; i<ZRTOS_VFS_MODULE_MCP2515_TXBN__LENGTH; i++){
		*txbn_regs = zrtos_vfs_module_mcp2515__get_txb(i);
		if(zrtos_error__is_success((
			ret = zrtos_vfs_module_mcp2515__read_register(
				 fd
				,txbn_regs->ctrl
				,&ctrlval
			)
		))
		&& (ctrlval & ZRTOS_VFS_MODULE_MCP2515_REGISTER_TXBNCTRL__TXREQ) == 0
		){
			goto L_RETURN;
		}
	}

	ret = ZRTOS_ERROR__AGAIN;

L_RETURN:
	return ret;
}

zrtos_error_t zrtos_vfs_module_mcp2515__send_message(
	 zrtos_vfs_fd_t fd
	,struct can_frame *frame
){
	zrtos_error_t ret;
	zrtos_vfs_module_mcp2515_txbn_regs_t txbn_regs;

	if(zrtos_error__is_success((
		ret = zrtos_vfs_module_mcp2515__get_available_txb(fd,&txbn_regs)
	))){
		ret = zrtos_vfs_module_mcp2515__send_message_ex(
			 fd
			,txbn_regs
			,frame
		);
	}

	return ret;
}

zrtos_error_t zrtos_vfs_module_mcp2515__read_message_ex(
	zrtos_vfs_module_mcp2515_rxbn_t rxbn
	, struct can_frame *frame
){
	zrtos_error_t ret;
	zrtos_vfs_module_mcp2515_rxbn_regs_t rxbn_regs[] = {
		{
			 ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB0CTRL
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB0SIDH
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB0DATA
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANINTF__RX0IF
		}
		,{
			 ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB1CTRL
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB1SIDH
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER__RXB1DATA
			,ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANINTF__RX1IF
		}
	};
	zrtos_vfs_module_mcp2515_rxbn_regs_t *rxb = &rxbn_regs[rxbn];
	uint8_t tbufdata[5];

	if(zrtos_error__is_success((
		ret = zrtos_vfs_module_mcp2515__read_registers(
			 fd
			,rxb->sidh
			,tbufdata
			,5
		)
	))){
		uint32_t id = (tbufdata[ZRTOS_VFS_MODULE_MCP2515_MCP__SIDH]<<3) + (tbufdata[ZRTOS_VFS_MODULE_MCP2515_MCP__SIDL]>>5);

		if ( (tbufdata[ZRTOS_VFS_MODULE_MCP2515_MCP__SIDL] & ZRTOS_VFS_MODULE_MCP2515_MCP_SIDL__TXB_EXIDE_MASK) ==  ZRTOS_VFS_MODULE_MCP2515_MCP_SIDL__TXB_EXIDE_MASK ) {
			id = (id<<2) + (tbufdata[ZRTOS_VFS_MODULE_MCP2515_MCP__SIDL] & 0x03);
			id = (id<<8) + tbufdata[ZRTOS_VFS_MODULE_MCP2515_MCP__EID8];
			id = (id<<8) + tbufdata[ZRTOS_VFS_MODULE_MCP2515_MCP__EID0];
			id |= CAN_EFF_FLAG;
		}

		uint8_t dlc = (
			  tbufdata[ZRTOS_VFS_MODULE_MCP2515_MCP__DLC]
			& ZRTOS_VFS_MODULE_MCP2515_MCP_DLC__DLC_MASK
		);
		if(dlc <= CAN_MAX_DLEN){
			uint8_t ctrl;
			ret = zrtos_vfs_module_mcp2515__read_register(fd,rxb->ctrl,&ctrl);
			if(zrtos_error__is_success(ret)){
				if (ctrl & ZRTOS_VFS_MODULE_MCP2515_REGISTER_RXBNCTRL__RTR) {
					id |= CAN_RTR_FLAG;
				}

				frame->can_id = id;
				frame->can_dlc = dlc;

				ret = zrtos_vfs_module_mcp2515__read_registers(
					 fd
					,rxb->data
					,frame->data
					,dlc
				);
				if(zrtos_error__is_success(ret)){
					ret = zrtos_vfs_module_mcp2515__modify_register(
						fd
						,ZRTOS_VFS_MODULE_MCP2515_REGISTER__CANINTF
						,rxb->rxnif
						,0
					);
				}
			}
		}else{
			ret = ZRTOS_ERROR__IO;
		}
	}

	return ret;
}

zrtos_error_t zrtos_vfs_module_mcp2515__read_message(
	 zrtos_vfs_fd_t fd
	,struct can_frame *frame
){
	uint8_t res;
	zrtos_error_t ret = zrtos_vfs_module_mcp2515__get_status(fd,&res);

	if(zrtos_error__is_success(ret)){
		if(ret & (
			  ZRTOS_VFS_MODULE_MCP2515_STATUS__RX0IF
			| ZRTOS_VFS_MODULE_MCP2515_STATUS__RX1IF
		)){
			ret = zrtos_vfs_module_mcp2515__read_message_ex(
				 fd
				,(
					(ret & ZRTOS_VFS_MODULE_MCP2515_STATUS__RX0IF)
					? ZRTOS_VFS_MODULE_MCP2515_RXBN__RXB0
					: ZRTOS_VFS_MODULE_MCP2515_RXBN__RXB1
				)
				,frame
			);
		}else{
			ret = ZRTOS_ERROR__NOMSG;
		}
	}

	return ret;
}

zrtos_error_t zrtos_vfs_module_mcp2515__check_receive(zrtos_vfs_fd_t fd){
	uint8_t res;
	zrtos_error_t ret = zrtos_vfs_module_mcp2515__get_status(fd,&res);

	if(zrtos_error__is_success(ret)){
		ret = (res & ZRTOS_VFS_MODULE_MCP2515_STATUS__RXIF_MASK)
		    ? ZRTOS_ERROR__SUCCESS
		    : ZRTOS_ERROR__NODATA
		;
	}

	return res;
}

zrtos_error_t zrtos_vfs_module_mcp2515__check_error(zrtos_vfs_fd_t fd){
	uint8_t res;
	zrtos_error_t ret = zrtos_vfs_module_mcp2515__get_error_flags(fd,&res);

	if(zrtos_error__is_success(ret)){
		ret = (res & ZRTOS_VFS_MODULE_MCP2515_ERROR_FLAG__ERRORMASK)
		    ? ZRTOS_ERROR__ERROR
		    : ZRTOS_ERROR__SUCCESS
		;
	}

	return ret;
}

zrtos_error_t zrtos_vfs_module_mcp2515__get_error_flags(
	 zrtos_vfs_fd_t fd
	,uint8_t *res
){
	return zrtos_vfs_module_mcp2515__read_register(
		fd
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER__EFLG
		,res
	);
}

zrtos_error_t zrtos_vfs_module_mcp2515__clear_rx_and_ovr_flags(
	zrtos_vfs_fd_t fd
){
	return zrtos_vfs_module_mcp2515__modify_register(
		fd
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER__EFLG
		,(
			  ZRTOS_VFS_MODULE_MCP2515_ERROR_FLAG__RX0OVR
			| ZRTOS_VFS_MODULE_MCP2515_ERROR_FLAG__RX1OVR
		)
		,0
	);
}

zrtos_error_t zrtos_vfs_module_mcp2515__get_interrupts(
	 zrtos_vfs_fd_t fd
	,uint8_t *res
){
	return zrtos_vfs_module_mcp2515__read_register(
		fd
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER__CANINTF
		,res
	);
}

zrtos_error_t zrtos_vfs_module_mcp2515__clear_interrupts(zrtos_vfs_fd_t fd){
	return zrtos_vfs_module_mcp2515__set_register(
		fd
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER__CANINTF
		,0
	);
}

zrtos_error_t zrtos_vfs_module_mcp2515__get_interrupt_mask(
	 zrtos_vfs_fd_t fd
	,uint8_t *res
){
	return zrtos_vfs_module_mcp2515__read_register(
		fd
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER__CANINTE
		,res
	);
}

zrtos_error_t zrtos_vfs_module_mcp2515__clear_tx_interrupts(zrtos_vfs_fd_t fd){
	return zrtos_vfs_module_mcp2515__modify_register(
		fd
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER__CANINTF
		,(
			  ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANINTF__TX0IF
			| ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANINTF__TX1IF
			| ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANINTF__TX2IF
		)
		,0
	);
}

zrtos_error_t zrtos_vfs_module_mcp2515__clear_rx_and_ovr(zrtos_vfs_fd_t fd){
	uint8_t eflg;
	zrtos_error_t ret;

	if(zrtos_error__is_success(
		(ret = zrtos_vfs_module_mcp2515__get_error_flags(fd,&eflg))
	)
	&& eflg != 0
	&& zrtos_error__is_success(
		(ret = zrtos_vfs_module_mcp2515__clear_rx_and_ovr_flags(fd))
	)
	&& zrtos_error__is_success(
		(ret = zrtos_vfs_module_mcp2515__clear_interrupts(fd))
	)){
		break;
	}

	return ret;
}

zrtos_error_t zrtos_vfs_module_mcp2515__clear_merr(zrtos_vfs_fd_t fd){
	return zrtos_vfs_module_mcp2515__modify_register(
		fd
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER__CANINTF
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANINTF__MERRF
		,0
	);
}

zrtos_error_t zrtos_vfs_module_mcp2515__clear_errif(zrtos_vfs_fd_t fd){
	return zrtos_vfs_module_mcp2515__modify_register(
		fd
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER__CANINTF
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER_CANINTF__ERRIF
		,0
	);
}

zrtos_error_t zrtos_vfs_module_mcp2515__get_error_count_rx(
	 zrtos_vfs_fd_t fd
	,uint8_t *res
){
	return zrtos_vfs_module_mcp2515__read_register(
		fd
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER__REC
		,res
	);
}

zrtos_error_t zrtos_vfs_module_mcp2515__get_error_count_tx(
	 zrtos_vfs_fd_t fd
	,uint8_t *res
){
	return zrtos_vfs_module_mcp2515__read_register(
		fd
		,ZRTOS_VFS_MODULE_MCP2515_REGISTER__TEC
		,res
	);
}

#ifdef __cplusplus
}
#endif
#endif
