/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_AVR_TIMEOUT4_H
#define ZRTOS_VFS_MODULE_AVR_TIMEOUT4_H
#ifdef __cplusplus
extern "C" {
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#include <zrtos/vfs/module/timeout/timeout.h>

ZRTOS_ASSERT__STATIC(
	sizeof(zrtos_vfs_offset_t) >= sizeof(zrtos_vfs_module_timeout_microseconds_t)
);

zrtos_vfs_module_timeout_inode_t zrtos_vfs_module_avr_timeout4;

ISR(TIMER4_OVF_vect){
	zrtos_vfs_module_avr_timeout4.callback(
		zrtos_vfs_module_avr_timeout4.callback_data
	);
}

zrtos_error_t zrtos_vfs_module_avr_timeout4__on_open(
	 zrtos_vfs_file_t *thiz
){
	return zrtos_vfs_file__get_dentry_count(thiz) == 1
	     ? ZRTOS_ERROR__SUCCESS
	     : ZRTOS_ERROR__MFILE
	;
}

zrtos_error_t zrtos_vfs_module_avr_timeout4__on_mount(zrtos_vfs_dentry_t *thiz){
	TIMSK4 = 0;
	return ZRTOS_ERROR__SUCCESS;
}

zrtos_error_t zrtos_vfs_module_avr_timeout4__on_umount(zrtos_vfs_dentry_t *thiz){
	TIMSK4 = 0;
	//TIMSK4 &= ~_BV(TOIE4);
	return ZRTOS_ERROR__SUCCESS;
}

zrtos_error_t zrtos_vfs_module_avr_timeout4__on_ioctl(
	 zrtos_vfs_file_t *thiz
	,char *path
	,int request
	,va_list args
){
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;

	switch(request){
		case ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__START:
			TCCR4A = 0;
			//TCCR4B = (inode_data->prescaler) & 0xff;
			TCCR4B = _BV(CS42) | _BV(CS41) | _BV(CS40);//prescaler 1024
			TIMSK4 = _BV(TOIE4);
			//TIMSK4 |= _BV(TOIE4);
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
			TCNT4 = zrtos_vfs_file__get_offset(thiz);
		break;
		case ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__STOP:
			TIMSK4 = 0;
			//TIMSK4 &= ~_BV(TOIE4);
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

ZRTOS_VFS_PLUGIN__INIT(avr_timeout4,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN(zrtos_vfs_module_avr_timeout4__on_open)
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT(zrtos_vfs_module_avr_timeout4__on_mount)
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT(zrtos_vfs_module_avr_timeout4__on_umount)
	ZRTOS_VFS_PLUGIN__4_ON_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__5_ON_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL(zrtos_vfs_module_avr_timeout4__on_ioctl)
);

#ifdef __cplusplus
}
#endif
#endif