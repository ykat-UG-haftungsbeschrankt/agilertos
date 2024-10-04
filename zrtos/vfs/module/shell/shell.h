/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_SHELL_H
#define ZRTOS_VFS_MODULE_SHELL_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/vfs_module.h>
#include <zrtos/str.h>

#ifndef ZRTOS_VFS_MODULE_SHELL__CFG_LINE_BUFFER_LENGTH
#define ZRTOS_VFS_MODULE_SHELL__CFG_LINE_BUFFER_LENGTH 80
#endif
#ifndef ZRTOS_VFS_MODULE_SHELL__CFG_MAX_ARG_COUNT
#define ZRTOS_VFS_MODULE_SHELL__CFG_MAX_ARG_COUNT      8
#endif

typedef enum{
	 ZRTOS_VFS_MODULE_SHELL_FD__MIN    = 0
	,ZRTOS_VFS_MODULE_SHELL_FD__STDIN  = 0
	,ZRTOS_VFS_MODULE_SHELL_FD__STDOUT = 1
	,ZRTOS_VFS_MODULE_SHELL_FD__STDERR = 2
	,ZRTOS_VFS_MODULE_SHELL_FD__MAX    = 2
}zrtos_vfs_module_shell_fd_t;

struct _zrtos_vfs_module_shell_t;

typedef struct{
	char *name;
	zrtos_error_t (*callback)(struct _zrtos_vfs_module_shell_t *thiz,size_t argc,char **argv);
}zrtos_vfs_module_shell_fn_t;

typedef struct{
	zrtos_vfs_fd_t      cwd;
	zrtos_vfs_fd_t      fd[ZRTOS_VFS_MODULE_SHELL_FD__MAX + 1];
}zrtos_vfs_module_shell_fd_array_t;

typedef struct _zrtos_vfs_module_shell_t{
	zrtos_vfs_module_shell_fd_array_t files;
	zrtos_vfs_module_shell_fn_t       **fn;
	void                   *data;
}zrtos_vfs_module_shell_t;

bool zrtos_vfs_module_shell__init(
	 zrtos_vfs_module_shell_t          *thiz
	,zrtos_vfs_module_shell_fd_array_t files
	,zrtos_vfs_module_shell_fn_t       **fn
	,void                   *data
){
	thiz->files = files;
	thiz->fn = fn;
	thiz->data = data;

	return true;
}

zrtos_error_t zrtos_vfs_module_shell__parse_line(
	 zrtos_vfs_module_shell_t *thiz
	,size_t *argc
	,char **argv
	,char *line
){
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;
	size_t pos = 0;
	char *arg;
	size_t offset;

	line += zrtos_str__spn(line," \t\r\n");
	offset = zrtos_str__cspn(line,"\r\n");
	if(offset){
		line[offset] = 0;
		while((arg = zrtos_str__tok_r(line," \t", &line))){
			if(pos < ZRTOS_VFS_MODULE_SHELL__CFG_MAX_ARG_COUNT){
				argv[pos++] = arg;
				continue;
			}else{
				ret = ZRTOS_ERROR__2BIG;
				break;
			}
		}
		*argc = pos;
	}else{
		*argc = 0;
	}

	return ret;
}

zrtos_error_t zrtos_vfs_module_shell__execute(
	 zrtos_vfs_module_shell_t *thiz
	,size_t argc
	,char **argv
){
	zrtos_error_t ret = ZRTOS_ERROR__NOSYS;
	zrtos_vfs_module_shell_fn_t **arr = thiz->fn;

	for(zrtos_vfs_module_shell_fn_t *fn;(fn = *arr++);){
		if(zrtos_str__cmp(argv[0],fn->name) == 0){
			ret = fn->callback(thiz,argc,argv);
			break;
		}
	}

	return ret;
}

zrtos_error_t zrtos_vfs_module_shell__run(
	 zrtos_vfs_module_shell_t *thiz
	,char      *line
){
	size_t argc;
	char *argv[ZRTOS_VFS_MODULE_SHELL__CFG_MAX_ARG_COUNT];
	zrtos_error_t ret = zrtos_vfs_module_shell__parse_line(
		 thiz
		,&argc
		,argv
		,line
	);
	if(zrtos_error__is_success(ret)
	&& argc > 0){
		ret = zrtos_vfs_module_shell__execute(thiz,argc,argv);
	}

	return ret;
}

zrtos_error_t zrtos_vfs_module_shell__on_read(
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

zrtos_error_t zrtos_vfs_module_shell__on_write(
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

ZRTOS_VFS_PLUGIN__INIT(shell,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__4_ON_READ(zrtos_vfs_module_shell__on_read)
	ZRTOS_VFS_PLUGIN__5_ON_WRITE(zrtos_vfs_module_shell__on_write)
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL_DEFAULT()
);

#ifdef __cplusplus
}
#endif
#endif