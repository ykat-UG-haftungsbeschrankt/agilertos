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
	const char str_st[] = " \t";
	const char str_rn[] = "\r\n";
	const char str_stnr[] = " \t\r\n";
	size_t pos = 0;
	char *arg;
	size_t offset;

	line += zrtos_str__spn(line,str_stnr);
	offset = zrtos_str__cspn(line,str_rn);
	if(offset){
		line[offset-1] = 0;
		while((arg = zrtos_str__tok_r(line,str_st, &line))){
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

typedef struct _zrtos_vfs_module_shell_file_t{
	zrtos_vfs_module_shell_t shell;
	char                     *line;
	size_t                   line_pos;
	size_t                   line_length;
	zrtos_error_t            last_error;
	bool                     overflow_error;
}zrtos_vfs_module_shell_file_t;

zrtos_error_t zrtos_vfs_module_shell__on_read(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_vfs_module_shell_file_t *mod = ZRTOS_CAST(
		 zrtos_vfs_module_shell_file_t *
		,zrtos_vfs_file__get_data(
			thiz
		)
	);
	zrtos_error_t ret;
	zrtos_vfs_module_shell_fd_t fd = ZRTOS_VFS_MODULE_SHELL_FD__STDOUT;
	size_t l = 1;

	do{
		ret = zrtos_vfs_fd__read(
			 mod->shell.files.fd[fd]
			,path
			,buf
			,len
			,offset
			,out
		);
		fd = ZRTOS_VFS_MODULE_SHELL_FD__STDERR;
	}while(zrtos_error__is_error(ret) && l--);

	return ret;
}

zrtos_error_t zrtos_vfs_module_shell__on_write(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_error_t ret;
	zrtos_vfs_module_shell_file_t *mod = ZRTOS_CAST(
		 zrtos_vfs_module_shell_file_t *
		,zrtos_vfs_file__get_data(
			thiz
		)
	);
	size_t free_space = mod->line_length - mod->line_pos;
	char *buffer = ZRTOS_CAST(char*,buf);
	size_t written = 0;

	char *str = zrtos_str__nchr(buffer,len,'\n');
	if(str){
		size_t line_length = str - buffer;
		if(mod->overflow_error){
			mod->overflow_error = false;
			written = line_length;
			ret = ZRTOS_ERROR__ILSEQ;
		}else if(line_length < free_space){
			zrtos_mem__cpy(
				 &mod->line[mod->line_pos]
				,buffer
				,line_length
			);
			mod->last_error = ret = zrtos_vfs_module_shell__run(
				 &mod->shell
				,mod->line
			);
			mod->line_pos = 0;
		}else{
			goto L_ERROR;
		}
	}else if(len < free_space){
		zrtos_mem__cpy(
			 &mod->line[mod->line_pos]
			,buffer
			,len
		);
		mod->line_pos += len;
		written = len;
		ret = ZRTOS_ERROR__SUCCESS;
	}else{
L_ERROR:
		mod->overflow_error = true;
		mod->line_pos = 0;
		written = len;
		ret = ZRTOS_ERROR__ILSEQ;
	}

	*out  = written;
	return ret;
}

zrtos_error_t zrtos_vfs_module_shell__on_can_read(
	 zrtos_vfs_file_t *thiz
){
	zrtos_vfs_module_shell_file_t *mod = ZRTOS_CAST(
		 zrtos_vfs_module_shell_file_t *
		,zrtos_vfs_file__get_data(
			thiz
		)
	);
	zrtos_error_t ret = zrtos_vfs_fd__can_read(
		mod->shell.files.fd[ZRTOS_VFS_MODULE_SHELL_FD__STDOUT]
	);
	if(zrtos_error__is_error(ret)){
		ret = zrtos_vfs_fd__can_read(
			mod->shell.files.fd[ZRTOS_VFS_MODULE_SHELL_FD__STDERR]
		);
	}
	return ret;
}

zrtos_error_t zrtos_vfs_module_shell__on_can_write(
	 zrtos_vfs_file_t *thiz
){
	/*
	zrtos_vfs_module_shell_file_t *mod = ZRTOS_CAST(
		 zrtos_vfs_module_shell_file_t *
		,zrtos_vfs_file__get_data(
			thiz
		)
	);
	*/
	return ZRTOS_ERROR__SUCCESS;
}

ZRTOS_VFS_PLUGIN__INIT(shell,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__4_ON_READ(zrtos_vfs_module_shell__on_read)
	ZRTOS_VFS_PLUGIN__5_ON_WRITE(zrtos_vfs_module_shell__on_write)
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ(zrtos_vfs_module_shell__on_can_read)
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE(zrtos_vfs_module_shell__on_can_write)
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL_DEFAULT()
);

#ifdef __cplusplus
}
#endif
#endif