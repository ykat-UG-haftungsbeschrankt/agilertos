/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_TIMEOUT_H
#define ZRTOS_VFS_MODULE_TIMEOUT_H
#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
	 ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__START
	,ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__STOP
	,ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__RESET
	,ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__SET_CALLBACK
}zrtos_vfs_module_timeout_ioctl_t;

typedef void (*zrtos_vfs_module_timeout_callback_t)(void *data);

typedef struct{
	zrtos_vfs_module_timeout_callback_t callback;
	void                                *callback_data;
}zrtos_vfs_module_timeout_inode_t;
/*
zrtos_error_t zrtos_vfs_module_spi__on_ioctl(
	 zrtos_vfs_file_t *thiz
	,char *path
	,int request
	,va_list args
){
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;

	switch(request){
		case ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__START:
			// Timer 0 konfigurieren
			TCCR0 = zrtos_va__arg(args,uint8_t);//(1<<CS01); // Prescaler 8
			TCNT0 = zrtos_va__arg(args,uint8_t);
			// Overflow Interrupt erlauben
			TIMSK |= (1<<TOIE0);
		break;
		case ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__STOP:
			TIMSK &= ~(1<<TOIE0);
		break;
		case ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__RESET:
			TCNT0 = zrtos_va__arg(args,uint8_t);
		break;
		case ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__SET_CALLBACK:
			zrtos_vfs_module_timeout__callback = zrtos_va__arg(
				 args
				,zrtos_vfs_module_timeout_callback_t
			);
			zrtos_vfs_module_timeout__data = zrtos_va__arg(args,void*);
		break;
		default:
			ret = ZRTOS_ERROR__INVAL;
		break;
	}

	return ret;
}

ZRTOS_VFS_PLUGIN__INIT(avr_timeout5,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT(zrtos_vfs_module_avr_timeout5__on_mount)
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT(zrtos_vfs_module_avr_timeout5__on_umount)
	ZRTOS_VFS_PLUGIN__4_ON_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__5_ON_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL_DEFAULT()
);
*/

#ifdef __cplusplus
}
#endif
#endif
