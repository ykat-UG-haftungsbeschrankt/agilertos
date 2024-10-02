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
#include <zrtos/mem.h>

//https://github.com/google/esh/blob/main/shell/shell/shell.c

typedef enum{
	ZRTOS_SHELL_STATE__RUNNING
}zrtos_shell_state_t;

typedef struct _zrtos_shell_t{
	void    *data;
	size_t  offset;
	size_t  length;
	zrtos_shell_state_t state;
}zrtos_shell_t;

bool zrtos_shell__init(
	 zrtos_stack_t *thiz
	,void *data
	,size_t length
){
	thiz->data = data;
	thiz->offset = 0;
	thiz->length = length;
	return true;
}

zrtos_error_t zrtos_shell__parse_line(
	 zrtos_shell_t *thiz
	,string_t *line_buffer
	,size_t *argc
	,char **argv
	,size_t argv_max_len
){
	int argc = 0;
	int pos = 0;
	int length = strlen(line_buff);

	while (pos <= length) {
		if (line_buff[pos] != '\t' && line_buff[pos] != SPACE &&
			line_buff[pos] != END_OF_LINE)
		argv[argc++] = &line_buff[pos];

		for (; line_buff[pos] != '\t' && line_buff[pos] != SPACE &&
			line_buff[pos] != END_OF_LINE;
			pos++)
		;

		if (line_buff[pos] == '\t' || line_buff[pos] == SPACE)
		line_buff[pos] = END_OF_LINE;

		pos++;
	}

	return argc;
}

zrtos_error_t zrtos_shell__execute(
	 zrtos_shell_t *thiz
	,size_t argc
	,char **argv
){
	int match_found = FALSE;

	for (int i = 0; table[i].command_name != NULL; i++) {
	if (strcmp(argv[0], table[i].command_name) == 0) {
		__cmd_exec_status = table[i].command(argc, &argv[0]);
		match_found = TRUE;
		break;
	}
	}

	if (match_found == FALSE) {
	printf("\"%s\": command not found. Use \"help\" to list all command.\n",
			argv[0]);
	__cmd_exec_status = -1;
	}
}

zrtos_error_t zrtos_shell__run(
	 zrtos_shell_t *thiz
){
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;

	while(zrtos_error__is_success(ret)
	&& thiz->state == ZRTOS_SHELL_STATE__RUNNING){
		ret = zrtos_shell__parse_line(thiz,&argc,argv,line_buff,MAX_ARG_COUNT);
		if(zrtos_error__is_success(ret)
		&& argc > 0){
			ret = zrtos_shell__execute(thiz,argc,argv);
		}
	}

	return ret;
}

#ifdef __cplusplus
}
#endif
#endif