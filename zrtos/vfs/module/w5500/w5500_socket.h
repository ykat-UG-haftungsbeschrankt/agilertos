/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_W5500_SOCKET_H
#define ZRTOS_VFS_MODULE_W5500_SOCKET_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/vfs_module.h>
#include <zrtos/vfs/module/network/network.h>

#include <zrtos/vfs/module/w5500/lib/w5500.h>

#define ZRTOS_VFS_MODULE_W5500_SOCKET__TX_BUFFER_BASE 0x4000
#define ZRTOS_VFS_MODULE_W5500_SOCKET__RX_BUFFER_BASE 0x6000
#define ZRTOS_VFS_MODULE_W5500_SOCKET__TX_BUFFER_MASK 0x07FF
#define ZRTOS_VFS_MODULE_W5500_SOCKET__RX_BUFFER_MASK 0x07FF
#define ZRTOS_VFS_MODULE_W5500_SOCKET__TX_BUFFER_SIZE 2048
#define ZRTOS_VFS_MODULE_W5500_SOCKET__RX_BUFFER_SIZE 2048
#define ZRTOS_VFS_MODULE_W5500_SOCKET__TX_BUFFER_ADDR(n)\
	(\
		  ZRTOS_VFS_MODULE_W5500_SOCKET__TX_BUFFER_BASE\
		+ (ZRTOS_VFS_MODULE_W5500_SOCKET__TX_BUFFER_SIZE * (n))\
	)
#define ZRTOS_VFS_MODULE_W5500_SOCKET__RX_BUFFER_ADDR(n)\
	(\
		  ZRTOS_VFS_MODULE_W5500_SOCKET__RX_BUFFER_BASE\
		+ (ZRTOS_VFS_MODULE_W5500_SOCKET__RX_BUFFER_SIZE * (n))\
	)

#define ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(addr,len)\
	((addr << 8) | (0x00 << 6) | len)
#define ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET(addr,len)\
	((addr << 8) | (0x01 << 6) | len)

typedef struct _ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL_t{
	 ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET_MODE                      = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET(0x00,1)
	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_MODE                      = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x00,1)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET_COMMAND                   = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET(0x01,1)
	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_COMMAND                   = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x01,1)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_INTERRUPT                 = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x02,1)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_SATUS                     = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x03,1)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET_SOURCE_PORT               = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET(0x04,2)
	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_SOURCE_PORT               = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x04,2)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET_DESTINATION_MAC_ADDRESS   = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET(0x06,6)
	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_DESTINATION_MAC_ADDRESS   = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x06,6)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET_DESTINATION_IP_ADDRESS    = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET(0x0C,4)
	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_DESTINATION_IP_ADDRESS    = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x0C,4)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET_DESTINATION_PORT          = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET(0x10,2)
	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_DESTINATION_PORT          = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x10,2)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET_MAXIMUM_SEGMENT_SIZE      = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET(0x12,2)
	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_MAXIMUM_SEGMENT_SIZE      = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x12,2)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET_IP_TOS                    = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET(0x15,1)
	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_IP_TOS                    = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x15,1)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET_IP_TTL                    = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET(0x16,1)
	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_IP_TTL                    = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x16,1)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET_RECEIVE_BUFFER_SIZE       = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET(0x1E,1)
	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_RECEIVE_BUFFER_SIZE       = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x1E,1)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET_TRANSMIT_BUFFER_SIZE      = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET(0x1F,1)
	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_TRANSMIT_BUFFER_SIZE      = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x1F,1)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_TX_FREE_SIZE              = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x20,2)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_TX_READ_POINTER           = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x22,2)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET_TX_WRITE_POINTER          = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET(0x24,2)
	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_TX_WRITE_POINTER          = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x24,2)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_RX_RECEIVED_SIZE          = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x26,2)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET_RX_READ_POINTER           = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET(0x28,2)
	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_RX_READ_POINTER           = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x28,2)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_RX_WRITE_POINTER          = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x2A,2)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET_INTERRUPT_MASK            = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET(0x2C,1)
	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_INTERRUPT_MASK            = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x2C,1)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET_FRAGMENT_OFFSET           = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET(0x2D,2)
	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_FRAGMENT_OFFSET           = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x2D,2)

	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET_KEEP_ALIVE_TIMER          = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET(0x2F,1)
	,ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET_KEEP_ALIVE_TIMER          = ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET(0x2F,1)
}ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL_t;

#undef ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__GET
#undef ZRTOS_VFS_MODULE_W5500_SOCKET_IOCTL__SET

typedef struct{
    uint8_t fd;
}zrtos_vfs_module_w5500_socket_file_t;

typedef struct{
	zrtos_vfs_fd_t fd;
}zrtos_vfs_module_w5500_socket_inode_t;

zrtos_error_t rtos_vfs_module_w5500_socket__read_data(
	 zrtos_vfs_fd_t fd
	,uint8_t n
	,uint16_t src
	,uint8_t *dest
	,uint16_t len
){
	uint16_t size;
	uint16_t src_mask;
	uint16_t addr;
	size_t l;
	uint8_t ctl = ZRTOS_VFS_MODULE_W5500_CTL__READ;
	
	src_mask = src & ZRTOS_VFS_MODULE_W5500_SOCKET__RX_BUFFER_MASK;
	addr = zrtos_types__htobe16(ZRTOS_VFS_MODULE_W5500_SOCKET__RX_BUFFER_ADDR(n) + src_mask);
	l = ZRTOS_VFS_MODULE_W5500_SOCKET__RX_BUFFER_SIZE - src_mask;

	do{
		ret = zrtos_vfs_fd__spi_transfer(
			 fd
			,3
			,addr
			,sizeof(addr)
			,&ctl
			,sizeof(ctl)
			,dest
			,l
		);
		dest += l;
		addr = zrtos_types__htobe16(ZRTOS_VFS_MODULE_W5500_SOCKET__RX_BUFFER_ADDR(n));
		l = len - l;
	}while(zrtos_error__is_success(ret) && l);

	return ret;
}

zrtos_error_t rtos_vfs_module_w5500_socket__write_data(
	 zrtos_vfs_fd_t fd
	,uint8_t n
	,uint16_t src
	,uint8_t *dest
	,uint16_t len
){
	uint16_t addr = zrtos_types__htobe16(ZRTOS_VFS_MODULE_W5500_SOCKET__TX_BUFFER_ADDR(n));
	uint8_t ctl = ZRTOS_VFS_MODULE_W5500_CTL__WRITE;

	return zrtos_vfs_fd__spi_transfer(
		 fd
		,3
		,addr
		,sizeof(addr)
		,&ctl
		,sizeof(ctl)
		,dest
		,len
	);
}

zrtos_error_t rtos_vfs_module_w5500_socket__on_read(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_vfs_module_w5500_socket_inode_t *inode_data = ZRTOS_CAST(
		 zrtos_vfs_module_w5500_socket_inode_t*
		,zrtos_vfs_file__get_inode_data(thiz)
	);
	zrtos_vfs_module_w5500_socket_file_t *file_data = ZRTOS_CAST(
		 zrtos_vfs_module_w5500_socket_file_t*
		,zrtos_vfs_file__get_data(thiz)
	);
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;
	uint16_t ptr;
	uint16_t rx_len;
	uint16_t rx_base_addr;

	if(zrtos_error__is_success((ret = zrtos_vfs_module_w5500__spi_transfer_uint16(
		 inode_data->fd
		,ZRTOS_VFS_MODULE_W5500_SOCKET_REGISTER__RX_RSR
		,ZRTOS_VFS_MODULE_W5500_CTL__SOCKET_READ(file_data->fd)
		,&rx_len
	)))
	&& zrtos_error__is_success((ret = zrtos_vfs_module_w5500__spi_transfer_uint16(
		 inode_data->fd
		,ZRTOS_VFS_MODULE_W5500_SOCKET_REGISTER__RX_RD
		,ZRTOS_VFS_MODULE_W5500_CTL__SOCKET_READ(file_data->fd)
		,ptr
	)))){
		rx_len = ZRTOS_TYPES__MIN(len,rx_len);
		if(zrtos_error__is_success((ret = rtos_vfs_module_w5500_socket__read_data(
			 inode_data->fd
			,file_data->fd
			,ptr
			,(uint8_t*)buf
			,rx_len
		)))){
			ptr += rx_len;
			ret = zrtos_vfs_module_w5500__spi_transfer_uint16(
				 inode_data->fd
				,ZRTOS_VFS_MODULE_W5500_SOCKET_REGISTER__RX_RD
				,ZRTOS_VFS_MODULE_W5500_CTL__SOCKET_WRITE(file_data->fd)
				,ptr
			);
		}
	}

	return ret;
}

zrtos_error_t rtos_vfs_module_w5500_socket__on_write(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_vfs_module_w5500_socket_inode_t *inode_data = ZRTOS_CAST(
		 zrtos_vfs_module_w5500_socket_inode_t*
		,zrtos_vfs_file__get_inode_data(thiz)
	);
	zrtos_vfs_module_w5500_socket_file_t *file_data = ZRTOS_CAST(
		 zrtos_vfs_module_w5500_socket_file_t*
		,zrtos_vfs_file__get_data(thiz)
	);
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;
	uint16_t ptr;
	uint16_t tx_len;
	uint16_t tx_base_addr;

	if(zrtos_error__is_success((ret = zrtos_vfs_module_w5500__spi_transfer_uint16(
		 inode_data->fd
		,ZRTOS_VFS_MODULE_W5500_SOCKET_REGISTER__TX_FSR
		,ZRTOS_VFS_MODULE_W5500_CTL__SOCKET_READ(file_data->fd)
		,&tx_len
	)))
	&& zrtos_error__is_success((ret = zrtos_vfs_module_w5500__spi_transfer_uint16(
		 inode_data->fd
		,ZRTOS_VFS_MODULE_W5500_SOCKET_REGISTER__TX_WR
		,ZRTOS_VFS_MODULE_W5500_CTL__SOCKET_READ(file_data->fd)
		,ptr
	)))){
		tx_len = ZRTOS_TYPES__MIN(len,tx_len);
		if(zrtos_error__is_success((ret = rtos_vfs_module_w5500_socket__write_data(
			 inode_data->fd
			,file_data->fd
			,ptr
			,(uint8_t*)buf
			,tx_len
		)))){
			ptr += tx_len;
			ret = zrtos_vfs_module_w5500__spi_transfer_uint16(
				 inode_data->fd
				,ZRTOS_VFS_MODULE_W5500_SOCKET_REGISTER__TX_WR
				,ZRTOS_VFS_MODULE_W5500_CTL__SOCKET_WRITE(file_data->fd)
				,ptr
			);
		}
	}

	return ret;
/*
    uint16_t ptr = readSnTX_WR(s);
    uint8_t cntl_byte = (0x14+(s<<5));
    ptr += data_offset;
    write(ptr, cntl_byte, data, len);
    ptr += len;
    writeSnTX_WR(s, ptr);
*/
}

zrtos_error_t rtos_vfs_module_w5500_socket__on_can_read_write_helper(
	 zrtos_vfs_file_t *thiz
	,uint16_t addr
){
	zrtos_vfs_module_w5500_socket_inode_t *inode_data = ZRTOS_CAST(
		 zrtos_vfs_module_w5500_socket_inode_t*
		,zrtos_vfs_file__get_inode_data(thiz)
	);
	zrtos_vfs_module_w5500_socket_file_t *file_data = ZRTOS_CAST(
		 zrtos_vfs_module_w5500_socket_file_t*
		,zrtos_vfs_file__get_data(thiz)
	);
	zrtos_error_t ret;
	uint16_t val;

	if(zrtos_error__is_success((ret = zrtos_vfs_module_w5500__spi_transfer_uint16(
		 inode_data->fd
		,addr
		,ZRTOS_VFS_MODULE_W5500_CTL__SOCKET_READ(file_data->fd)
		,&val
	)))){
		ret = val > 0
			? ZRTOS_ERROR__SUCCESS
			: ZRTOS_ERROR__AGAIN
		;
	}

	return ret;
}

zrtos_error_t rtos_vfs_module_w5500_socket__on_can_read(
	 zrtos_vfs_file_t *thiz
	,char *path
){
	return rtos_vfs_module_w5500_socket__on_can_read_write_helper(
		 thiz
		,ZRTOS_VFS_MODULE_W5500_SOCKET_REGISTER__RX_RSR
	);
}

zrtos_error_t rtos_vfs_module_w5500_socket__on_can_write(
	 zrtos_vfs_file_t *thiz
	,char *path
){
	return rtos_vfs_module_w5500_socket__on_can_read_write_helper(
		 thiz
		,ZRTOS_VFS_MODULE_W5500_SOCKET_REGISTER__TX_FSR
	);
}

bool zrtos_vfs_module_w5500_socket__on_ioctl_helper_validate_addr(uint16_t addr,size_t length){
	return (
		   (addr + length < 0x14)
		|| ((addr == 0x15 || addr == 0x16) && length == 1)
		|| (addr >= 0x1E && (addr + length < 0x30))
	);
}

zrtos_error_t zrtos_vfs_module_w5500_socket__on_ioctl(
	 zrtos_vfs_file_t *thiz
	,char *path
	,int request
	,va_list args
){
	zrtos_vfs_module_w5500_socket_inode_t *inode_data = ZRTOS_CAST(
		 zrtos_vfs_module_w5500_socket_inode_t*
		,zrtos_vfs_file__get_inode_data(thiz)
	);
	zrtos_vfs_module_w5500_socket_file_t *file_data = ZRTOS_CAST(
		 zrtos_vfs_module_w5500_socket_file_t*
		,zrtos_vfs_file__get_data(thiz)
	);
	return zrtos_vfs_module_w5500__on_ioctl_helper(
		 inode_data->fd
		,path
		,request
		,args
		,WIZCHIP_SREG_BLOCK(file_data->fd)
		,zrtos_vfs_module_w5500_socket__on_ioctl_helper_validate_addr
	);
}

ZRTOS_VFS_PLUGIN__INIT(w5500_socket,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__4_ON_READ_DEFAULT(rtos_vfs_module_w5500_socket__on_read)
	ZRTOS_VFS_PLUGIN__5_ON_WRITE_DEFAULT(rtos_vfs_module_w5500_socket__on_write)
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ(rtos_vfs_module_w5500_socket__on_can_read)
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE(rtos_vfs_module_w5500_socket__on_can_write)
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL(zrtos_vfs_module_w5500_socket__on_ioctl)
);

#ifdef __cplusplus
}
#endif
#endif
