 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_SPI_H
#define ZRTOS_VFS_MODULE_SPI_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/vfs_plugin.h>
#include <zrtos/malloc.h>
#include <zrtos/cbuffer.h>
#include <zrtos/clist.h>

#ifndef ZRTOS_VFS_MODULE_SPI__CFG_TRANSFER_LENGTH
#define ZRTOS_VFS_MODULE_SPI__CFG_TRANSFER_LENGTH ZRTOS_CBUFFER__CFG_DATA_LENGTH
#endif

typedef struct _zrtos_vfs_module_spi_file_t{
	zrtos_clist_node_t           node;
	zrtos_cbuffer_t              cbuffer_in;
	zrtos_cbuffer_t              cbuffer_out;
	zrtos_error_t                error;
	void                         *data;
}zrtos_vfs_module_spi_file_t;

typedef struct _zrtos_vfs_module_spi_t{
	zrtos_clist_t                root;
	zrtos_vfs_module_spi_file_t  *last;
	size_t                       count;
}zrtos_vfs_module_spi_t;

bool zrtos_vfs_module_spi_file__init(
	 zrtos_vfs_module_spi_file_t *thiz
	,void                        *data
){
	zrtos_clist_node__init(&thiz->node);
	thiz->error = ESUCCESS;
	thiz->data = data;
	if(zrtos_cbuffer__init(&thiz->cbuffer_in)){
		if(zrtos_cbuffer__init(&thiz->cbuffer_out)){
			return true;
		}
	}
	return false;
}

void zrtos_vfs_module_spi_file__deinit(zrtos_vfs_module_spi_file_t *thiz){
	zrtos_cbuffer__deinit(&thiz->cbuffer_in);
	zrtos_cbuffer__deinit(&thiz->cbuffer_out);
}

bool zrtos_vfs_module_spi__init(
	 zrtos_vfs_module_spi_t *thiz
){
	zrtos_clist__init(&thiz->root);
	thiz->last = 0;
	thiz->count = 0;
	return true;
}

void zrtos_vfs_module_spi__deinit(zrtos_vfs_module_spi_t *thiz){
}

static void zrtos_vfs_module_spi__get(
	 zrtos_vfs_module_spi_t *thiz
	,void                   *data
	,size_t                 len
)
	zrtos_clist_node_t *node = zrtos_clist__get_first_node(&thiz->root);
	if(node){
		zrtos_vfs_module_spi_file_t *first = zrtos_types__get_container_of(
			 node
			,zrtos_vfs_module_spi_file_t
			,node
		);
		zrtos_vfs_module_spi.last = first;

		if(zrtos_cbuffer__is_empty(&first->cbuffer_out)
		|| ++count > ZRTOS_VFS_MODULE_SPI__CFG_TRANSFER_LENGTH){
			count = 0;
			zrtos_clist__shift_and_push(&thiz->root);
		}

		ZRTOS_CLIST__EACH_BEGIN(
			 &thiz->root
			,node
			,zrtos_vfs_module_spi_file_t
			,node
		){
			if(!zrtos_cbuffer__is_empty(&first->cbuffer_out)){
				first->error = zrtos_cbuffer__get_ex(
					&last->cbuffer_out
					,data
					,len
					,outlen
				);
			}
		}ZRTOS_CLIST__EACH_END;
	}
}

static void zrtos_vfs_module_spi__put(
	 zrtos_vfs_module_spi_t *thiz
	,void                   *data
	,size_t                 len
){
	zrtos_vfs_module_spi_file_t *last = thiz->last;
	if(last
	&& zrtos_error__is_success(last->error)){
		size_t outlen;
		last->error = zrtos_cbuffer__put_ex(
			 &last->cbuffer_in
			,1
			,data
			,len
			,outlen
		);
	}
}

void zrtos_vfs_module_spi__transfer(
	 zrtos_vfs_module_spi_t *thiz
	,void                   *data_in
	,void                   *data_out
	,size_t                 len
){
	zrtos_vfs_module_spi__put(thiz,data_in,len);
	zrtos_vfs_module_spi__get(thiz,data_out,len);
}

zrtos_error_t zrtos_vfs_module_spi__on_open(
	 zrtos_vfs_file_t *thiz
	,char             *path
){
	zrtos_error_t ret = ENOMEM;
	zrtos_vfs_module_spi_file_t *file_data = zrtos_vfs_module_spi_file__new(
		thiz->
	);
	if(file_data){
		zrtos_vfs_file__set_data(thiz,file_data);
		ret = ESUCCESS;
	}
	return ret;
}

zrtos_error_t zrtos_vfs_module_spi__on_close(
	 zrtos_vfs_file_t *thiz
	,char             *path
){
	zrtos_vfs_module_spi_file_t *file_data = zrtos_vfs_file__get_data(thiz);
	zrtos_vfs_module_spi_file__free(file_data);
	return ESUCCESS;
}

zrtos_error_t zrtos_vfs_module_spi__on_read(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *outlen
){
	zrtos_vfs_module_spi_file_t *file_data = zrtos_vfs_file__get_data(
		thiz
	);
	return zrtos_cbuffer__get_ex(
		 &file_data->cbuffer_in
		,buf
		,len
		,outlen
	);
}

zrtos_error_t zrtos_vfs_module_spi__on_write(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_vfs_module_spi_file_t *file_data = zrtos_vfs_file__get_data(
		thiz
	);
	return zrtos_cbuffer__put_ex(
		 &file_data->cbuffer_out
		,buf
		,len
		,outlen
	);
}

zrtos_error_t zrtos_vfs_module_spi__on_can_read(
	 zrtos_vfs_file_t *thiz
	,char *path
){
	zrtos_vfs_module_spi_file_t *file_data = zrtos_vfs_file__get_data(
		thiz
	);
	return zrtos_cbuffer__is_empty(&file_data->cbuffer_in)
	     ? EAGAIN
	     : ESUCCESS
	;
}

zrtos_error_t zrtos_vfs_module_spi__on_can_write(
	 zrtos_vfs_file_t *thiz
	,char *path
){
	zrtos_vfs_module_spi_file_t *file_data = zrtos_vfs_file__get_data(
		thiz
	);
	return ESUCCESS;
}
/*
ZRTOS_VFS_PLUGIN__INIT(spi,
	ZRTOS_VFS_PLUGIN__ON_OPEN(zrtos_vfs_module_spi__on_open)
	ZRTOS_VFS_PLUGIN__ON_CLOSE(zrtos_vfs_module_spi__on_close)
	ZRTOS_VFS_PLUGIN__ON_READ(zrtos_vfs_module_spi__on_read)
	ZRTOS_VFS_PLUGIN__ON_WRITE(zrtos_vfs_module_spi__on_write)
	ZRTOS_VFS_PLUGIN__ON_CAN_READ(zrtos_vfs_module_spi__on_can_read)
	ZRTOS_VFS_PLUGIN__ON_CAN_WRITE(zrtos_vfs_module_spi__on_can_write)
);
*/

#ifdef __cplusplus
}
#endif
#endif
