/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_AVR_TIMEOUT3_H
#define ZRTOS_VFS_MODULE_AVR_TIMEOUT3_H
#ifdef __cplusplus
extern "C" {
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#include <zrtos/vfs/module/timeout/timeout.h>

zrtos_vfs_module_avr_timeout_args_t *zrtos_vfs_module_avr_timeout3;

ISR(TIMER3_OVF_vect){
	zrtos_vfs_module_avr_timeout3->callback(
		zrtos_vfs_module_avr_timeout3->callback_data
	);
}

zrtos_error_t zrtos_vfs_module_avr_timeout3__on_mount(zrtos_vfs_dentry_t *thiz){
	zrtos_vfs_module_avr_timeout3 = ZRTOS_CAST(
		 zrtos_vfs_module_avr_timeout_args_t*
		,zrtos_vfs_file__get_inode_data(thiz)
	);
	return ZRTOS_ERROR__SUCCESS;
}

zrtos_error_t zrtos_vfs_module_avr_timeout3__on_umount(zrtos_vfs_dentry_t *thiz){
	TIMSK3 = 0;
	//TIMSK3 &= ~(1<<TOIE3);
	return ZRTOS_ERROR__SUCCESS;
}

zrtos_error_t zrtos_vfs_module_avr_timeout3__on_ioctl(
	 zrtos_vfs_file_t *thiz
	,char *path
	,int request
	,va_list args
){
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;
	zrtos_vfs_module_avr_timeout_args_t *inode_data = ZRTOS_CAST(
		 zrtos_vfs_module_avr_timeout_args_t*
		,zrtos_vfs_file__get_inode_data(thiz)
	);

	switch(request){
		case ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__START:
			TCCR3A = 0;
			TCCR3B = (inode_data->prescaler) & 0xff;
			TIMSK3 = (1<<TOIE3);
			//TIMSK3 |= (1<<TOIE3);
		case ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__RESET:
			TCNT3 = inode_data->counter & 0xff;
		break;
		case ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__STOP:
			TIMSK3 = 0;
			//TIMSK3 &= ~(1<<TOIE3);
		break;
		case ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__SET_CALLBACK:
			zrtos_vfs_module_avr_timeout0__callback = zrtos_va__arg(
				 args
				,zrtos_vfs_module_timeout_callback_t
			);
			zrtos_vfs_module_avr_timeout0__data = zrtos_va__arg(args,void*);
		break;
		default:
			ret = ZRTOS_ERROR__INVAL;
		break;
	}

	return ret;
}

ZRTOS_VFS_PLUGIN__INIT(avr_timeout3,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT(zrtos_vfs_module_avr_timeout3__on_mount)
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT(zrtos_vfs_module_avr_timeout3__on_umount)
	ZRTOS_VFS_PLUGIN__4_ON_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__5_ON_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL(zrtos_vfs_module_avr_timeout3__on_ioctl)
);

#ifdef __cplusplus
}
#endif
#endif
