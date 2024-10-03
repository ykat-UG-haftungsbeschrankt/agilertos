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
#include <zrtos/vfs/network/network.h>

#include <zrtos/vfs/w5500/lib/w5500.h>

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

typedef struct _zrtos_vfs_module_w5500_ioctl_t{
	 ZRTOS_VFS_MODULE_W5500_IOCTL__SET_GATEWAY_IP           = ((GAR)   | (_W5500_SPI_WRITE_))
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_GATEWAY_IP           = ((GAR)   | (_W5500_SPI_READ_) )
	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_SUBNET_MASK          = ((SUBR)  | (_W5500_SPI_WRITE_))
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_SUBNET_MASK          = ((SUBR)  | (_W5500_SPI_READ_) )
	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_IP_ADDRESS           = ((SIPR)  | (_W5500_SPI_WRITE_))
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_IP_ADDRESS           = ((SIPR)  | (_W5500_SPI_READ_) )
	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_MAC_ADDRESS          = ((SHAR)  | (_W5500_SPI_WRITE_))
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_MAC_ADDRESS          = ((SHAR)  | (_W5500_SPI_READ_) )
	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_RETRANSMISSION_TIME  = ((_RTR_) | (_W5500_SPI_WRITE_))
	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_RETRANSMISSION_COUNT = ((_RCR_) | (_W5500_SPI_WRITE_))
}zrtos_vfs_module_w5500_ioctl_t;

typedef struct _zrtos_vfs_module_w5500_inode_t{
	zrtos_vfs_fd_t fd;
}zrtos_vfs_module_w5500_inode_t;

zrtos_error_t zrtos_vfs_module_w5500__reset(
	zrtos_vfs_fd_t fd
){
	zrtos_error_t ret;
	size_t llimit = 1;
	uint16_t cmd = zrtos_types__htobe16(MR);
	uint8_t ctl = _W5500_SPI_WRITE_;
	uint8_t mode = MR_RST;
	
	for(size_t l = 1;l--;){
		while(llimit-- && zrtos_error__is_success((ret = zrtos_vfs_fd__spi_transfer(
			inode_data->fd
			,3
			,&cmd
			,sizeof(cmd)
			,&ctl
			,sizeof(ctl)
			,&mode
			,sizeof(mode)
		))) && (mode & MR_RST) != 0){
			continue;
		}

		ctl = _W5500_SPI_READ_;
		llimit = ZRTOS_TYPES__SIZE_MAX;
	}

	return zrtos_error__is_success(ret)
	     ? (
			  (mode & MR_RST) == 0
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

ZRTOS_ASSERT__STATIC(sizeof(int) >= sizeof(uint32_t));

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
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;
	uint32_t req = ZRTOS_CAST__REINTERPRET(
		 zrtos_vfs_module_w5500_ioctl_t
		,request
	);
	uint16_t addr = zrtos_types__htobe16(req >> 8);
	uint8_t ctl = req & 0xFF;
	void *value;
	size_t value_length = 0;
	union{
		zrtos_vfs_module_network_ip4_t *ip;
		zrtos_vfs_module_network_mac_t *mac;
		zrtos_vfs_module_network_subnet_mask_t *subnet_mask;
		uint8_t rtr;
		uint16_t rcr;
	}data;

	switch(ZRTOS_CAST__REINTERPRET(
		 zrtos_vfs_module_w5500_ioctl_t
		,request
	)){
		case ZRTOS_VFS_MODULE_W5500_IOCTL__SET_GATEWAY_IP:
		case ZRTOS_VFS_MODULE_W5500_IOCTL__GET_GATEWAY_IP:
		case ZRTOS_VFS_MODULE_W5500_IOCTL__SET_IP_ADDRESS:
		case ZRTOS_VFS_MODULE_W5500_IOCTL__GET_IP_ADDRESS:
		 	data.ip = zrtos_va__arg(
				 args
				,zrtos_vfs_module_network_ip4_t*
			);
			value = data.ip;
			value_length = sizeof(data.ip[0]);
		break;
		case ZRTOS_VFS_MODULE_W5500_IOCTL__SET_SUBNET_MASK:
		case ZRTOS_VFS_MODULE_W5500_IOCTL__GET_SUBNET_MASK:
			data.subnet_mask = zrtos_va__arg(
				 args
				,zrtos_vfs_module_network_subnet_mask_t*
			);
			value = data.subnet_mask;
			value_length = sizeof(data.subnet_mask[0]);
		break;
		case ZRTOS_VFS_MODULE_W5500_IOCTL__SET_MAC_ADDRESS:
		case ZRTOS_VFS_MODULE_W5500_IOCTL__GET_MAC_ADDRESS:
			data.mac = zrtos_va__arg(
				 args
				,zrtos_vfs_module_network_mac_t*
			);
			value = data.mac;
			value_length = sizeof(data.mac[0]);
		break;
		case ZRTOS_VFS_MODULE_W5500_IOCTL__SET_RETRANSMISSION_TIME:
			data.rtr = zrtos_va__arg(
				 args
				,uint8_t
			);
			value = &data.rtr;
			value_length = sizeof(data.rtr);
		break;
		case ZRTOS_VFS_MODULE_W5500_IOCTL__SET_RETRANSMISSION_COUNT:
			data.rcr = zrtos_va__arg(
				 args
				,uint8_t
			);
			value = &data.rcr;
			value_length = sizeof(data.rcr);
		break;
		default:
			ret = ZRTOS_ERROR__INVAL;
			goto L_OUT;
		break;
	}
	
	//@todo verify endianness
	ret = zrtos_vfs_fd__spi_transfer(
		 inode_data->fd
		,3
		,&addr
		,sizeof(addr)
		,&ctl
		,sizeof(ctl)
		,value
		,value_length
	);

L_OUT:
	return ret;
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
