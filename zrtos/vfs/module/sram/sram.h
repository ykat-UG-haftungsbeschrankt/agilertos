/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_SRAM_H
#define ZRTOS_VFS_MODULE_SRAM_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/vfs_module.h>


typedef struct _zrtos_vfs_module_sram_args_t{
	void *start_addr;
	void *end_addr;
}zrtos_vfs_module_sram_args_t;

zrtos_error_t zrtos_vfs_module_sram__rw(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
	,bool is_write_op
){
	zrtos_error_t ret = EFAULT;
	zrtos_vfs_module_sram_args_t *mod = ZRTOS_CAST(
		 zrtos_vfs_module_sram_args_t *
		,zrtos_vfs_file__get_inode_data(
			thiz
		)
	);
	size_t start_offset = (size_t)offset;
	uint8_t *data_ptr = ZRTOS_CAST(uint8_t *,buf);

	if(offset > ZRTOS_TYPES__SIZE_MAX){
		ret = EINVAL;
		goto L_OUT;
	}

	if(zrtos_types__ptr_is_valid_address_range(
		 mod->start_addr
		,mod->end_addr
		,start_offset
		,&len
	)){
		uint8_t *start_ptr = ZRTOS_CAST(
			 uint8_t*
			,zrtos_types__ptr_add(
				 mod->start_addr
				,start_offset
			)
		);

		*out = len;

		if(is_write_op){
			ZRTOS_TYPES__SWAP(data_ptr,start_ptr);
		}

		zrtos_mem__cpy(data_ptr,start_ptr,len);

		ret = ESUCCESS;
	}

L_OUT:
	return ret;
}


zrtos_error_t zrtos_vfs_module_sram__on_read(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	return zrtos_vfs_module_sram__rw(
		 thiz
		,path
		,buf
		,len
		,offset
		,out
		,false
	);
}

zrtos_error_t zrtos_vfs_module_sram__on_write(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	return zrtos_vfs_module_sram__rw(
		 thiz
		,path
		,buf
		,len
		,offset
		,out
		,true
	);
}

ZRTOS_VFS_PLUGIN__INIT(sram,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__4_ON_READ(zrtos_vfs_module_sram__on_read)
	ZRTOS_VFS_PLUGIN__5_ON_WRITE(zrtos_vfs_module_sram__on_write)
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL_DEFAULT()
);


#ifdef __cplusplus
}
#endif
#endif
