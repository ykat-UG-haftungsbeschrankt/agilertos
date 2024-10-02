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


typedef struct _zrtos_vfs_module_w5500_ioctl_t{
	 ZRTOS_VFS_MODULE_W5500_IOCTL__SET_GATEWAY_IP
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_GATEWAY_IP
	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_SUBNET_MASK
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_SUBNET_MASK
	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_IP_ADDRESS
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_IP_ADDRESS
	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_MAC_ADDRESS
	,ZRTOS_VFS_MODULE_W5500_IOCTL__GET_MAC_ADDRESS
	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_RETRANSMISSION_TIME
	,ZRTOS_VFS_MODULE_W5500_IOCTL__SET_RETRANSMISSION_COUNT
}zrtos_vfs_module_w5500_ioctl_t;


typedef struct _zrtos_vfs_module_sram_inode_t{
	void *start_addr;
	void *end_addr;
}zrtos_vfs_module_sram_inode_t;

zrtos_error_t zrtos_vfs_module_w5500__on_ioctl(
	 zrtos_vfs_file_t *thiz
	,char *path
	,int request
	,va_list args
){
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;

	switch(ZRTOS_CAST__REINTERPRET(
		 zrtos_vfs_module_timeout_ioctl_t
		,request
	)){
		case ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__START:
			TCCR5A = 0;
			//TCCR5B = (inode_data->prescaler) & 0xff;
			TCCR5B = _BV(CS52) | _BV(CS51) | _BV(CS50);//prescaler 1024
			TIMSK5 = _BV(TOIE5);
			//TIMSK5 |= _BV(TOIE5);
			zrtos_vfs_file__set_offset(
				 thiz
				,zrtos_vfs_module_timeout__get_overflow_counter_value(
					zrtos_va__arg(
						args
						,zrtos_vfs_module_timeout_microseconds_t
					)
					,1024
				)
			);
		case ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__RESET:
			TCNT5 = zrtos_vfs_file__get_offset(thiz);
		break;
		case ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__STOP:
			TIMSK5 = 0;
			//TIMSK5 &= ~_BV(TOIE5);
		break;
		case ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__SET_CALLBACK:
			zrtos_vfs_module_avr_timeout0.callback = zrtos_va__arg(
				 args
				,zrtos_vfs_module_timeout_callback_t
			);
			zrtos_vfs_module_avr_timeout0.callback_data = zrtos_va__arg(
				 args
				,void*
			);
		break;
		default:
			ret = ZRTOS_ERROR__INVAL;
		break;
	}

	return ret;
}

ZRTOS_VFS_PLUGIN__INIT(w5500,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT_DEFAULT()
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
