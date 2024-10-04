/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_SHELL_H
#define ZRTOS_SHELL_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/zrtos.h>
#include <zrtos/types.h>
#include <zrtos/str.h>

#ifndef ZRTOS_SHELL__CFG_LINE_BUFFER_LENGTH
#define ZRTOS_SHELL__CFG_LINE_BUFFER_LENGTH 80
#endif
#ifndef ZRTOS_SHELL__CFG_MAX_ARG_COUNT
#define ZRTOS_SHELL__CFG_MAX_ARG_COUNT      8
#endif

typedef enum{
	 ZRTOS_SHELL_FD__MIN    = 0
	,ZRTOS_SHELL_FD__STDIN  = 0
	,ZRTOS_SHELL_FD__STDOUT = 1
	,ZRTOS_SHELL_FD__STDERR = 2
	,ZRTOS_SHELL_FD__MAX    = 2
}zrtos_shell_fd_t;

struct _zrtos_shell_t;

typedef struct{
	char *name;
	zrtos_error_t (*callback)(struct _zrtos_shell_t *thiz,size_t argc,char **argv);
}zrtos_shell_fn_t;

typedef struct{
	zrtos_vfs_fd_t      cwd;
	zrtos_vfs_fd_t      fd[ZRTOS_SHELL_FD__MAX + 1];
}zrtos_shell_fd_array_t;

typedef struct _zrtos_shell_t{
	zrtos_shell_fd_array_t files;
	zrtos_shell_fn_t       **fn;
	void                   *data;
}zrtos_shell_t;

bool zrtos_shell__init(
	 zrtos_shell_t          *thiz
	,zrtos_shell_fd_array_t files
	,zrtos_shell_fn_t       **fn
	,void                   *data
){
	thiz->files = files;
	thiz->fn = fn;
	thiz->data = data;

	return true;
}

zrtos_error_t zrtos_shell__parse_line(
	 zrtos_shell_t *thiz
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
			if(pos < ZRTOS_SHELL__CFG_MAX_ARG_COUNT){
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

zrtos_error_t zrtos_shell__execute(
	 zrtos_shell_t *thiz
	,size_t argc
	,char **argv
){
	zrtos_error_t ret = ZRTOS_ERROR__NOSYS;
	zrtos_shell_fn_t **fn = thiz->fn;

	for(;*fn;fn++){
		if(zrtos_str__cmp(argv[0],fn->name) == 0){
			ret = fn->callback(thiz,argc,argv);
			break;
		}
	}

	return ret;
}

zrtos_error_t zrtos_shell__run(
	 zrtos_shell_t *thiz
	,char      *line
){
	size_t argc;
	char *argv[ZRTOS_SHELL__CFG_MAX_ARG_COUNT];
	zrtos_error_t ret = zrtos_shell__parse_line(
		 thiz
		,&argc
		,argv
		,line
	);
	if(zrtos_error__is_success(ret)
	&& argc > 0){
		ret = zrtos_shell__execute(thiz,argc,argv);
	}

	return ret;
}

#ifdef __cplusplus
}
#endif
#endif