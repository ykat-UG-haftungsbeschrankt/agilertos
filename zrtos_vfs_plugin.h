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


#include <stdarg.h>


#include "zrtos_types.h"
#include "zrtos_error.h"

struct _zrtos_vfs_file_t;
struct _zrtos_vfs_dentry_t;
struct _zrtos_vfs_inode_t;

typedef size_t zrtos_vfs_offset_t;

#ifdef ZRTOS_VFS_PLUGIN__USE_SWITCH
typedef enum{
	 ZRTOS_VFS_PLUGIN_OPERATION__OPEN
	,ZRTOS_VFS_PLUGIN_OPERATION__CLOSE
	,ZRTOS_VFS_PLUGIN_OPERATION__MOUNT
	,ZRTOS_VFS_PLUGIN_OPERATION__UMOUNT
	,ZRTOS_VFS_PLUGIN_OPERATION__READ
	,ZRTOS_VFS_PLUGIN_OPERATION__WRITE
	,ZRTOS_VFS_PLUGIN_OPERATION__CAN_READ
	,ZRTOS_VFS_PLUGIN_OPERATION__CAN_WRITE
	,ZRTOS_VFS_PLUGIN_OPERATION__SEEK
	,ZRTOS_VFS_PLUGIN_OPERATION__IOCTL
}zrtos_vfs_plugin_operation_t;
#else
# define ZRTOS_VFS_PLUGIN_OPERATION__OPEN open
# define ZRTOS_VFS_PLUGIN_OPERATION__CLOSE close
# define ZRTOS_VFS_PLUGIN_OPERATION__MOUNT mount
# define ZRTOS_VFS_PLUGIN_OPERATION__UMOUNT umount
# define ZRTOS_VFS_PLUGIN_OPERATION__READ read
# define ZRTOS_VFS_PLUGIN_OPERATION__WRITE write
# define ZRTOS_VFS_PLUGIN_OPERATION__CAN_READ can_read
# define ZRTOS_VFS_PLUGIN_OPERATION__CAN_WRITE can_write
# define ZRTOS_VFS_PLUGIN_OPERATION__SEEK seek
# define ZRTOS_VFS_PLUGIN_OPERATION__IOCTL ioctl
#endif

#define ZRTOS_VFS_PLUGIN__GET_FILE() (thiz)
#define ZRTOS_VFS_PLUGIN__GET_ARG(type) va_arg(args,type)
#define ZRTOS_VFS_PLUGIN__RETURN(val)\
do{\
	ret = val;\
	goto L_RETURN;\
}while(0);

#ifdef ZRTOS_VFS_PLUGIN__USE_SWITCH
#define ZRTOS_VFS_PLUGIN__INIT(name,...)\
zrtos_error_t zrtos_vfs_module_##name##__operation(\
	 zrtos_vfs_plugin_operation_t operation\
	,...\
){\
	zrtos_error_t ret = ENOSYS;\
	va_list args;\
	va_start(args,operation);\
	switch(operation){\
		__VA_ARGS__\
		default:
		break;
	}\
\
L_RETURN:\
	va_end(args);\
	return ret;\
}\
\
zrtos_vfs_plugin_t zrtos_vfs_module_##name = {\
	.operation = zrtos_vfs_module_##name##__operation\
};
#else
#define ZRTOS_VFS_PLUGIN__INIT(name,...)\
zrtos_vfs_plugin_t zrtos_vfs_module_##name = {\
	__VA_ARGS__\
};
#endif

#define ZRTOS_VFS_PLUGIN(name) (&zrtos_vfs_module_##name)

#ifndef ZRTOS_VFS_PLUGIN__USE_SWITCH
#define ZRTOS_VFS_PLUGIN__INVOKE(thiz,operation,...) (thiz->operation(__VA_ARGS__))
#else
#define ZRTOS_VFS_PLUGIN__INVOKE(thiz,...) (thiz->operation(__VA_ARGS__))
#endif

typedef struct{
#ifndef ZRTOS_VFS_PLUGIN__USE_SWITCH
	zrtos_error_t (*open)(struct _zrtos_vfs_file_t *thiz);
# define ZRTOS_VFS_PLUGIN__ON_OPEN(callback) .open=callback
#else
# define ZRTOS_VFS_PLUGIN__ON_OPEN(ret,file,data,callback)                  \
	case ZRTOS_VFS_PLUGIN_OPERATION__OPEN:{                          \
		zrtos_error_t *ret  = ZRTOS_VFS_PLUGIN__ARG(zrtos_error_t*); \
		struct _zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(struct _zrtos_vfs_file_t*); \
		void          *data = ZRTOS_VFS_PLUGIN__ARG(void*);          \
		*ret = callback(file,data);                              \
		break;                                                       \
	}
#endif

#ifndef ZRTOS_VFS_PLUGIN__USE_SWITCH
	zrtos_error_t    (*close)(struct _zrtos_vfs_file_t *thiz);
# define ZRTOS_VFS_PLUGIN__ON_CLOSE(callback) .close=callback
#else
# define ZRTOS_VFS_PLUGIN__ON_CLOSE(data,callback)                    \
	case ZRTOS_VFS_PLUGIN_OPERATION__CLOSE:{                        \
		void          *data = ZRTOS_VFS_PLUGIN__ARG(void*);          \
		*ret = callback(data);                                   \
		break;                                                       \
	}
#endif

#ifndef ZRTOS_VFS_PLUGIN__USE_SWITCH
	zrtos_error_t (*mount)(struct _zrtos_vfs_dentry_t *thiz);
# define ZRTOS_VFS_PLUGIN__ON_MOUNT(callback) .mount=callback
#else
# define ZRTOS_VFS_PLUGIN__ON_MOUNT(ret,dentry,data)                  \
	case ZRTOS_VFS_PLUGIN_OPERATION__MOUNT:{                          \
		zrtos_error_t *ret  = ZRTOS_VFS_PLUGIN__ARG(zrtos_error_t*); \
		struct _zrtos_vfs_dentry_t *dentry = ZRTOS_VFS_PLUGIN__ARG(struct _zrtos_vfs_dentry_t*); \
		void          *data = ZRTOS_VFS_PLUGIN__ARG(void*);          \
		*ret = callback();                                                 \
		break;                                                       \
	}
#endif

#ifndef ZRTOS_VFS_PLUGIN__USE_SWITCH
	zrtos_error_t    (*umount)(struct _zrtos_vfs_dentry_t *thiz);
# define ZRTOS_VFS_PLUGIN__ON_UMOUNT(callback) .umount=callback
#else
# define ZRTOS_VFS_PLUGIN__ON_UMOUNT(ret,dentry,callback)         \
	case ZRTOS_VFS_PLUGIN_OPERATION__UMOUNT:{                        \
		zrtos_error_t *ret  = ZRTOS_VFS_PLUGIN__ARG(zrtos_error_t*); \
		struct _zrtos_vfs_dentry_t *dentry = ZRTOS_VFS_PLUGIN__ARG(struct _zrtos_vfs_dentry_t*); \
		*ret = callback;                                                 \
		break;                                                       \
	}
#endif

#ifndef ZRTOS_VFS_PLUGIN__USE_SWITCH
	zrtos_error_t (*read)(struct _zrtos_vfs_file_t *thiz,char *path,void *buf,size_t len,off_t offset,size_t *out);
# define ZRTOS_VFS_PLUGIN__ON_READ(callback) .read=callback
#else
# define ZRTOS_VFS_PLUGIN__ON_READ(callback)\
	case ZRTOS_VFS_PLUGIN_OPERATION__READ:{                       \
		struct _zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(struct _zrtos_vfs_file_t*); \
		char    *path  = ZRTOS_VFS_PLUGIN__ARG(char*);            \
		void    *buf   = ZRTOS_VFS_PLUGIN__ARG(void*);            \
		size_t  len    = ZRTOS_VFS_PLUGIN__ARG(size_t);           \
		off_t   offset = ZRTOS_VFS_PLUGIN__ARG(off_t);            \
		ssize_t *ret   = ZRTOS_VFS_PLUGIN__ARG(ssize_t*);         \
		*ret = callback();                                              \
		break;                                                    \
}
#endif

#ifndef ZRTOS_VFS_PLUGIN__USE_SWITCH
	zrtos_error_t (*write)(struct _zrtos_vfs_file_t *thiz,char *path,void *buf,size_t len,off_t offset,size_t *out);
# define ZRTOS_VFS_PLUGIN__ON_WRITE(callback) .write=callback
#else
# define ZRTOS_VFS_PLUGIN__ON_WRITE(ret,file,path,buf,len,offset,callback)\
	case ZRTOS_VFS_PLUGIN_OPERATION__READ:{                        \
		ssize_t *ret   = ZRTOS_VFS_PLUGIN__ARG(ssize_t*);          \
		struct _zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(struct _zrtos_vfs_file_t*); \
		char    *path  = ZRTOS_VFS_PLUGIN__ARG(char*);             \
		void    *buf   = ZRTOS_VFS_PLUGIN__ARG(void*);             \
		size_t  len    = ZRTOS_VFS_PLUGIN__ARG(size_t);            \
		off_t   offset = ZRTOS_VFS_PLUGIN__ARG(off_t);             \
		*ret = callback();                                               \
		break;                                                     \
	}
#endif

#ifndef ZRTOS_VFS_PLUGIN__USE_SWITCH
	zrtos_error_t  (*can_read)(struct _zrtos_vfs_file_t *thiz);
# define ZRTOS_VFS_PLUGIN__ON_CAN_READ(callback) .can_read=callback
#else
# define ZRTOS_VFS_PLUGIN__ON_CAN_READ(ret,file,path,callback)            \
	case ZRTOS_VFS_PLUGIN_OPERATION__CAN_READ:{                    \
		size_t  *ret   = ZRTOS_VFS_PLUGIN__ARG(size_t*);           \
		struct _zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(struct _zrtos_vfs_file_t*); \
		char    *path  = ZRTOS_VFS_PLUGIN__ARG(char*);             \
		*ret = callback();                                               \
		break;                                                     \
	}
#endif

#ifndef ZRTOS_VFS_PLUGIN__USE_SWITCH
	zrtos_error_t  (*can_write)(struct _zrtos_vfs_file_t *thiz);
# define ZRTOS_VFS_PLUGIN__ON_CAN_WRITE(callback) .can_write=callback
#else
# define ZRTOS_VFS_PLUGIN__ON_CAN_WRITE(ret,file,path,callback)           \
	case ZRTOS_VFS_PLUGIN_OPERATION__CAN_WRITE:{                   \
		size_t  *ret   = ZRTOS_VFS_PLUGIN__ARG(size_t*);           \
		struct _zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(struct _zrtos_vfs_file_t*); \
		char    *path  = ZRTOS_VFS_PLUGIN__ARG(char*);             \
		*ret = callback();                                               \
		break;                                                     \
	}
#endif

#ifndef ZRTOS_VFS_PLUGIN__USE_SWITCH
	off_t   (*seek)(int fd, off_t offset, int whence);
# define ZRTOS_VFS_PLUGIN__ON_SEEK(callback) .seek=callback
#else
# define ZRTOS_VFS_PLUGIN__ON_SEEK(ret,file,path,offset,whence,callback)  \
	case ZRTOS_VFS_PLUGIN_OPERATION__SEEK:{                        \
		off_t   *ret   = ZRTOS_VFS_PLUGIN__ARG(off_t*);            \
		struct _zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(struct _zrtos_vfs_file_t*); \
		char    *path  = ZRTOS_VFS_PLUGIN__ARG(char*);             \
		off_t   offset = ZRTOS_VFS_PLUGIN__ARG(off_t);             \
		size_t  whence = ZRTOS_VFS_PLUGIN__ARG(size_t);            \
		*ret = callback();                                               \
		break;                                                     \
	}
#endif

#ifndef ZRTOS_VFS_PLUGIN__USE_SWITCH
	zrtos_error_t (*ioctl)(struct _zrtos_vfs_file_t *thiz,char *path, int request, va_list args);
# define ZRTOS_VFS_PLUGIN__ON_IOCTL(callback) .ioctl=callback
#else
# define ZRTOS_VFS_PLUGIN__ON_IOCTL(ret,file,path,request,args,callback)      \
	case ZRTOS_VFS_PLUGIN_OPERATION__READ:{                           \
		zrtos_error_t *ret = ZRTOS_VFS_PLUGIN__ARG(zrtos_error_t*);   \
		struct _zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(struct _zrtos_vfs_file_t*); \
		char    *path      = ZRTOS_VFS_PLUGIN__ARG(char*);            \
		int    request      = ZRTOS_VFS_PLUGIN__ARG(int);              \
		va_list  args      = ZRTOS_VFS_PLUGIN__ARG(va_list);          \
		*ret = callback();                                                  \
		break;                                                        \
	}
#endif

#ifdef ZRTOS_VFS_PLUGIN__USE_SWITCH
	zrtos_error_t (*operation)(
		 zrtos_vfs_plugin_operation_t operation
		,...
	);
#endif
}zrtos_vfs_plugin_t;


#ifdef __cplusplus
}
#endif
#endif