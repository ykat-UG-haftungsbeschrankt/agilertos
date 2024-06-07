/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_PLUGIN_H
#define ZRTOS_VFS_PLUGIN_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_types.h"
#include "zrtos_error.h"

struct _zrtos_vfs_file_t;
struct _zrtos_vfs_dentry_t;
struct _zrtos_vfs_inode_t;

typedef enum{
	 ZRTOS_VFS_PLUGIN_OPERATION__INIT
	,ZRTOS_VFS_PLUGIN_OPERATION__DEINIT
	 ZRTOS_VFS_PLUGIN_OPERATION__MOUNT
	,ZRTOS_VFS_PLUGIN_OPERATION__UMOUNT
	,ZRTOS_VFS_PLUGIN_OPERATION__READ
	,ZRTOS_VFS_PLUGIN_OPERATION__WRITE
	,ZRTOS_VFS_PLUGIN_OPERATION__CAN_READ
	,ZRTOS_VFS_PLUGIN_OPERATION__CAN_WRITE
	,ZRTOS_VFS_PLUGIN_OPERATION__SEEK
	,ZRTOS_VFS_PLUGIN_OPERATION__IOCTL
}zrtos_vfs_plugin_operation_t;

#define ZRTOS_VFS_PLUGIN__GET_FILE() (thiz)
#define ZRTOS_VFS_PLUGIN__GET_ARG(type) va_arg(args,type)
#define ZRTOS_VFS_PLUGIN__RETURN(val)\
do{\
	ret = val;\
	goto L_RETURN;\
}while(0);

#define ZRTOS_VFS_PLUGIN__INIT(name,case_block)\
zrtos_error_t zrtos_vfs_module_##name##__operation(\
	 zrtos_vfs_plugin_operation_t operation\
	,...\
){\
	zrtos_error_t ret = ENOSYS;\
	va_list args;\
	va_start(args,operation);\
	switch(operation)\
		case_block\

L_RETURN:\
	va_end(vl);\
	return ret;\
}\
\
zrtos_vfs_plugin_t zrtos_vfs_module_##name = {\
	,.operation = zrtos_vfs_module_##name##__operation\
};

typedef struct{
	//zrtos_error_t (*init)(zrtos_vfs_file_t *thiz,void *private_data);
#define ZRTOS_VFS_PLUGIN__ON_INIT(ret,file,data,fn_body)                  \
	case ZRTOS_VFS_PLUGIN_OPERATION__INIT:{                          \
		zrtos_error_t *ret  = ZRTOS_VFS_PLUGIN__ARG(zrtos_error_t*); \
		zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(zrtos_vfs_file_t*); \
		void          *data = ZRTOS_VFS_PLUGIN__ARG(void*);          \
		do{                                                          \
			fn_body;                                                 \
		}while(0);                                                   \
		break;                                                       \
	}

	//void    (*deinit)(zrtos_vfs_file_t *thiz);
#define ZRTOS_VFS_PLUGIN__ON_DEINIT(data,fn_body)                    \
	case ZRTOS_VFS_PLUGIN_OPERATION__DEINIT:{                        \
		void          *data = ZRTOS_VFS_PLUGIN__ARG(void*);          \
		do{                                                          \
			fn_body;                                                 \
		}while(0);                                                   \
		break;                                                       \
	}

	//zrtos_error_t (*mount)(zrtos_vfs_dentry_t *thiz,void *private_data);
#define ZRTOS_VFS_PLUGIN__ON_MOUNT(ret,dentry,data)                  \
	case ZRTOS_VFS_PLUGIN_OPERATION__INIT:{                          \
		zrtos_error_t *ret  = ZRTOS_VFS_PLUGIN__ARG(zrtos_error_t*); \
		zrtos_vfs_dentry_t *dentry = ZRTOS_VFS_PLUGIN__ARG(zrtos_vfs_dentry_t*); \
		void          *data = ZRTOS_VFS_PLUGIN__ARG(void*);          \
		do{                                                          \
			fn_body;                                                 \
		}while(0);                                                   \
		break;                                                       \
	}

	//zrtos_error_t    (*umount)(zrtos_vfs_dentry_t *thiz);
#define ZRTOS_VFS_PLUGIN__ON_UMOUNT(ret,dentry,fn_body)         \
	case ZRTOS_VFS_PLUGIN_OPERATION__UMOUNT:{                        \
		zrtos_error_t *ret  = ZRTOS_VFS_PLUGIN__ARG(zrtos_error_t*); \
		zrtos_vfs_dentry_t *dentry = ZRTOS_VFS_PLUGIN__ARG(zrtos_vfs_dentry_t*); \
		do{                                                          \
			fn_body;                                                 \
		}while(0);                                                   \
		break;                                                       \
	}

	//ssize_t (*read)(zrtos_vfs_file_t *thiz,char *path,void *buf,size_t len,off_t offset);
#define ZRTOS_VFS_PLUGIN__ON_READ(ret,file,path,buf,len,offset,fn_body)\
	case ZRTOS_VFS_PLUGIN_OPERATION__READ:{                       \
		ssize_t *ret   = ZRTOS_VFS_PLUGIN__ARG(ssize_t*);         \
		zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(zrtos_vfs_file_t*); \
		char    *path  = ZRTOS_VFS_PLUGIN__ARG(char*);            \
		void    *buf   = ZRTOS_VFS_PLUGIN__ARG(void*);            \
		size_t  len    = ZRTOS_VFS_PLUGIN__ARG(size_t);           \
		off_t   offset = ZRTOS_VFS_PLUGIN__ARG(off_t);            \
		do{                                                       \
			fn_body;                                              \
		}while(0);                                                \
		break;                                                    \
	}

	//ssize_t (*write)(zrtos_vfs_file_t *thiz,char *path,void *buf,size_t len,off_t offset);
#define ZRTOS_VFS_PLUGIN__ON_WRITE(ret,file,path,buf,len,offset,fn_body)\
	case ZRTOS_VFS_PLUGIN_OPERATION__READ:{                        \
		ssize_t *ret   = ZRTOS_VFS_PLUGIN__ARG(ssize_t*);          \
		zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(zrtos_vfs_file_t*); \
		char    *path  = ZRTOS_VFS_PLUGIN__ARG(char*);             \
		void    *buf   = ZRTOS_VFS_PLUGIN__ARG(void*);             \
		size_t  len    = ZRTOS_VFS_PLUGIN__ARG(size_t);            \
		off_t   offset = ZRTOS_VFS_PLUGIN__ARG(off_t);             \
		do{                                                        \
			fn_body;                                               \
		}while(0);                                                 \
		break;                                                     \
	}

	//size_t  (*can_read)(zrtos_vfs_file_t *thiz);
#define ZRTOS_VFS_PLUGIN__ON_CAN_READ(ret,file,path,fn_body)            \
	case ZRTOS_VFS_PLUGIN_OPERATION__CAN_READ:{                    \
		size_t  *ret   = ZRTOS_VFS_PLUGIN__ARG(size_t*);           \
		zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(zrtos_vfs_file_t*); \
		char    *path  = ZRTOS_VFS_PLUGIN__ARG(char*);             \
		do{                                                        \
			fn_body;                                               \
		}while(0);                                                 \
		break;                                                     \
	}

	//size_t  (*can_write)(zrtos_vfs_file_t *thiz);
#define ZRTOS_VFS_PLUGIN__ON_CAN_WRITE(ret,file,path,fn_body)           \
	case ZRTOS_VFS_PLUGIN_OPERATION__CAN_WRITE:{                   \
		size_t  *ret   = ZRTOS_VFS_PLUGIN__ARG(size_t*);           \
		zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(zrtos_vfs_file_t*); \
		char    *path  = ZRTOS_VFS_PLUGIN__ARG(char*);             \
		do{                                                        \
			fn_body;                                               \
		}while(0);                                                 \
		break;                                                     \
	}

	//off_t   (*seek)(int fd, off_t offset, int whence);
#define ZRTOS_VFS_PLUGIN__ON_SEEK(ret,file,path,offset,whence,fn_body)  \
	case ZRTOS_VFS_PLUGIN_OPERATION__SEEK:{                        \
		off_t   *ret   = ZRTOS_VFS_PLUGIN__ARG(off_t*);            \
		zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(zrtos_vfs_file_t*); \
		char    *path  = ZRTOS_VFS_PLUGIN__ARG(char*);             \
		off_t   offset = ZRTOS_VFS_PLUGIN__ARG(off_t);             \
		size_t  whence = ZRTOS_VFS_PLUGIN__ARG(size_t);            \
		do{                                                        \
			fn_body;                                               \
		}while(0);                                                 \
		break;                                                     \
	}

	//zrtos_error_t (*ioctl)(zrtos_file_t *thiz,char *path, int whence, va_list args);
#define ZRTOS_VFS_PLUGIN__ON_IOCTL(ret,file,path,whence,args,fn_body)      \
	case ZRTOS_VFS_PLUGIN_OPERATION__READ:{                           \
		zrtos_error_t *ret = ZRTOS_VFS_PLUGIN__ARG(zrtos_error_t*);   \
		zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(zrtos_vfs_file_t*); \
		char    *path      = ZRTOS_VFS_PLUGIN__ARG(char*);            \
		int    whence      = ZRTOS_VFS_PLUGIN__ARG(int);              \
		va_list  args      = ZRTOS_VFS_PLUGIN__ARG(va_list);          \
		do{                                                           \
			fn_body;                                                  \
		}while(0);                                                    \
		break;                                                        \
	}

	zrtos_error_t (*operation)(
		 zrtos_vfs_plugin_operation_t operation
		,...
	);
}zrtos_vfs_plugin_t;


#ifdef __cplusplus
}
#endif
#endif