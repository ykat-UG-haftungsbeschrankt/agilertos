/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_W5500_H
#define ZRTOS_VFS_MODULE_W5500_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/vfs_module.h>
#include <zrtos/vfs/module/network/network.h>

#include <zrtos/vfs/module/w5500/lib/w5500.h>

#ifndef ZRTOS_VFS_MODULE_W5500__CFG_STARTUP_DELAY
#define ZRTOS_VFS_MODULE_W5500__CFG_STARTUP_DELAY 600
#endif

//W5500 should support up to 33,3Mhz
#ifndef ZRTOS_VFS_MODULE_W5500__CFG_SPI_CLOCK_RATE
#if ZRTOS_ARCH__CPU_CLOCK_HZ <= 4000000L
#define ZRTOS_VFS_MODULE_W5500__CFG_SPI_CLOCK_RATE\
	ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__CLOCK_RATE_4
#elif ZRTOS_ARCH__CPU_CLOCK_HZ <= 16000000L
#define ZRTOS_VFS_MODULE_W5500__CFG_SPI_CLOCK_RATE\
	ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__CLOCK_RATE_16
#elif ZRTOS_ARCH__CPU_CLOCK_HZ <= 64000000L
#define ZRTOS_VFS_MODULE_W5500__CFG_SPI_CLOCK_RATE\
	ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__CLOCK_RATE_64
#elif ZRTOS_ARCH__CPU_CLOCK_HZ <= 128000000L
#define ZRTOS_VFS_MODULE_W5500__CFG_SPI_CLOCK_RATE\
	ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__CLOCK_RATE_128
#else
#error "not supported cpu clock"
#endif
#endif

#define ZRTOS_VFS_MODULE_W5500__CFG_SPI_CONTROL\
	(ZRTOS_VFS_MODULE_W5500__CFG_SPI_CLOCK_RATE\
	|ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__MODE_MASTER\
	|ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__BITORDER_MSB\
	|ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__PP_0)


#define ZRTOS_VFS_MODULE_W5500_IOCTL__GET(addr,len)\
	((addr << 8) | (0x00 << 6) | len)
#define ZRTOS_VFS_MODULE_W5500_IOCTL__SET(addr,len)\
	((addr << 8) | (0x01 << 6) | len)

typedef enum{
	 ZRTOS_VFS_MODULE_W5500_IOCTL__SET_MODE                      = ZRTOS_VFS_MODULE_W5500_IOCTL__SET(0x00,1)
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_MODE                      = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x00,1)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_GATEWAY_ADDRESS           = ZRTOS_VFS_MODULE_W5500_IOCTL__SET(0x01,4)
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_GATEWAY_ADDRESS           = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x01,4)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_SUBNET_MASK               = ZRTOS_VFS_MODULE_W5500_IOCTL__SET(0x05,4)
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_SUBNET_MASK               = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x05,4)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_SOURCE_MAC_ADDRESS        = ZRTOS_VFS_MODULE_W5500_IOCTL__SET(0x09,6)
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_SOURCE_MAC_ADDRESS        = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x09,6)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_SOURCE_IP_ADDRESS         = ZRTOS_VFS_MODULE_W5500_IOCTL__SET(0x0F,4)
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_SOURCE_IP_ADDRESS         = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x0F,4)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_INTERRUPT_LOW_LEVEL_TIMER = ZRTOS_VFS_MODULE_W5500_IOCTL__SET(0x13,2)
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_INTERRUPT_LOW_LEVEL_TIMER = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x13,2)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_INTERRUPT                 = ZRTOS_VFS_MODULE_W5500_IOCTL__SET(0x15,1)
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_INTERRUPT                 = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x15,1)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_INTERRUPT_MASK            = ZRTOS_VFS_MODULE_W5500_IOCTL__SET(0x16,1)
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_INTERRUPT_MASK            = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x16,1)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_SOCKET_INTERRUPT          = ZRTOS_VFS_MODULE_W5500_IOCTL__SET(0x17,1)
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_SOCKET_INTERRUPT          = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x17,1)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_SOCKET_INTERRUPT_MASK     = ZRTOS_VFS_MODULE_W5500_IOCTL__SET(0x18,1)
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_SOCKET_INTERRUPT_MASK     = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x18,1)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_RETRY_TIME                = ZRTOS_VFS_MODULE_W5500_IOCTL__SET(0x19,2)
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_RETRY_TIME                = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x19,2)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_RETRY_COUNT               = ZRTOS_VFS_MODULE_W5500_IOCTL__SET(0x1B,1)
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_RETRY_COUNT               = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x1B,1)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_PPP_LCP_REQUEST_TIMER     = ZRTOS_VFS_MODULE_W5500_IOCTL__SET(0x1C,1)
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_PPP_LCP_REQUEST_TIMER     = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x1C,1)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_PPP_LCP_MAGIC_NUMBER      = ZRTOS_VFS_MODULE_W5500_IOCTL__SET(0x1D,1)
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_PPP_LCP_MAGIC_NUMBER      = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x1D,1)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_PPP_DESTINATION_MAC       = ZRTOS_VFS_MODULE_W5500_IOCTL__SET(0x1E,6)
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_PPP_DESTINATION_MAC       = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x1E,6)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_PPP_SESSION_ID            = ZRTOS_VFS_MODULE_W5500_IOCTL__SET(0x24,2)
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_PPP_SESSION_ID            = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x24,2)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_PPP_MAXIMUM_SEGMENT_SIZE  = ZRTOS_VFS_MODULE_W5500_IOCTL__SET(0x26,2)
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_PPP_MAXIMUM_SEGMENT_SIZE  = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x26,2)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_UNREACHABLE_IP            = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x28,4)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_UNREACHABLE_PORT          = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x2C,2)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_PHY_CONFIG                = ZRTOS_VFS_MODULE_W5500_IOCTL__SET(0x2E,1)
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_PHY_CONFIG                = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x2E,1)

	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_CHIP_VERSION              = ZRTOS_VFS_MODULE_W5500_IOCTL__GET(0x39,1)
}zrtos_vfs_module_w5500_ioctl_t;

#undef ZRTOS_VFS_MODULE_W5500_IOCTL__GET
#undef ZRTOS_VFS_MODULE_W5500_IOCTL__SET

typedef struct _zrtos_vfs_module_w5500_inode_t{
	zrtos_vfs_fd_t fd;
}zrtos_vfs_module_w5500_inode_t;

zrtos_error_t zrtos_vfs_module_w5500__spi_transfer_uint8(
	 zrtos_vfs_fd_t fd
	,uint16_t addr
	,uint8_t ctl
	,uint8_t *val
){
	addr = zrtos_types__htobe16(addr);
	return zrtos_vfs_fd__spi_transfer(
		 fd
		,3
		,&addr
		,sizeof(addr)
		,&ctl
		,sizeof(ctl)
		,val
		,sizeof(*val)
	);
}

zrtos_error_t zrtos_vfs_module_w5500__spi_transfer_uint16(
	 zrtos_vfs_fd_t fd
	,uint16_t addr
	,uint8_t ctl
	,uint16_t *val
){
	addr = zrtos_types__htobe16(addr);
	return zrtos_vfs_fd__spi_transfer(
		 fd
		,3
		,&addr
		,sizeof(addr)
		,&ctl
		,sizeof(ctl)
		,val
		,sizeof(*val)
	);
}

zrtos_error_t zrtos_vfs_module_w5500__reset(
	zrtos_vfs_fd_t fd
){
	zrtos_error_t ret;
	size_t llimit = 1;
	uint16_t cmd = ZRTOS_VFS_MODULE_W5500_SOCKET_REGISTER__MODE;
	uint8_t ctl = ZRTOS_VFS_MODULE_W5500_CTL__WRITE;
	uint8_t mode = ZRTOS_VFS_MODULE_W5500_REGISTER_MODE__RST;
	
	for(size_t l = 2;l--;){
		while(llimit-- && zrtos_error__is_success((ret = zrtos_vfs_module_w5500__spi_transfer_uint8(
			 fd
			,cmd
			,ctl
			,&mode
		))) && (mode & ZRTOS_VFS_MODULE_W5500_REGISTER_MODE__RST) != 0){
			continue;
		}

		ctl = ZRTOS_VFS_MODULE_W5500_CTL__READ;
		llimit = ZRTOS_TYPES__SIZE_MAX;
	}

	return zrtos_error__is_success(ret)
	     ? (
			  (mode & ZRTOS_VFS_MODULE_W5500_REGISTER_MODE__RST) == 0
			? ZRTOS_ERROR__SUCCESS
			: ZRTOS_ERROR__AGAIN
		 )
		 : ret
	;
}

zrtos_error_t zrtos_vfs_module_w5500__on_mount(zrtos_vfs_dentry_t *thiz){
	zrtos_vfs_module_w5500_inode_t *inode_data = ZRTOS_CAST(
		 zrtos_vfs_module_w5500_inode_t*
		,zrtos_vfs_dentry__get_data(thiz)
	);
	
	zrtos_gpio__delay_milliseconds(ZRTOS_VFS_MODULE_W5500__CFG_STARTUP_DELAY);

	return zrtos_vfs_module_w5500__reset(inode_data->fd);
}

zrtos_error_t zrtos_vfs_module_w5500__on_umount(zrtos_vfs_dentry_t *thiz){
	return ZRTOS_ERROR__SUCCESS;
}

ZRTOS_ASSERT__STATIC(sizeof(int) >= sizeof(uint16_t));

zrtos_error_t zrtos_vfs_module_w5500__on_ioctl_helper(
	 zrtos_vfs_fd_t fd
	,char *path
	,int request
	,va_list args
	,uint8_t ctl_bsb
	,bool (*validate)(uint16_t addr,size_t length)
){
	zrtos_error_t ret;
	uint16_t req = ZRTOS_CAST__REINTERPRET(
		 int
		,request
	);
	uint16_t addr;
	uint8_t ctl;
	size_t length;
	void *value = zrtos_va__arg_ptr(
		 args
		,void*
	);
	size_t value_length = zrtos_va__arg_ptr(
		 args
		,size_t
	);

	length = req & 0xF;
	req >>= 4;
	ctl = req & 0xF | ctl_bsb;
	req >>= 4;
	addr = zrtos_types__htobe16(req);

	//@todo verify endianness
	if(length == value_length
	&& validate(addr,length)
	){
		ret = zrtos_vfs_fd__spi_transfer(
			 fd
			,3
			,&addr
			,sizeof(addr)
			,&ctl
			,sizeof(ctl)
			,value
			,value_length
		);
	}else{
		ret = ZRTOS_ERROR__INVAL;
	}

	return ret;
}

bool zrtos_vfs_module_w5500__on_ioctl_helper_validate_addr(uint16_t addr,size_t length){
	return (
		   (addr + length < 0x2F)
		|| (addr == 0x39 && length == 1)
	);
}

zrtos_error_t zrtos_vfs_module_w5500__on_ioctl(
	 zrtos_vfs_file_t *thiz
	,char *path
	,int request
	,va_list args
){
	zrtos_vfs_module_w5500_inode_t *inode_data = ZRTOS_CAST(
		 zrtos_vfs_module_w5500_inode_t*
		,zrtos_vfs_file__get_inode_data(thiz)
	);
	return zrtos_vfs_module_w5500__on_ioctl_helper(
		 inode_data->fd
		,path
		,request
		,args
		,0
		,zrtos_vfs_module_w5500__on_ioctl_helper_validate_addr
	);
}

ZRTOS_VFS_PLUGIN__INIT(w5500,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT(zrtos_vfs_module_w5500__on_mount)
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT(zrtos_vfs_module_w5500__on_umount)
	ZRTOS_VFS_PLUGIN__4_ON_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__5_ON_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL(zrtos_vfs_module_w5500__on_ioctl)
);


#ifdef __cplusplus
}
#endif
#endif
