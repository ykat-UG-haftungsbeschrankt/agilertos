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
/*
struct fuse_operations {
    int (*getattr) (const char *, struct stat *);
    int (*readlink) (const char *, char *, size_t);
    int (*getdir) (const char *, fuse_dirh_t, fuse_dirfil_t);
    int (*mknod) (const char *, mode_t, dev_t);
    int (*mkdir) (const char *, mode_t);
    int (*unlink) (const char *);
    int (*rmdir) (const char *);
    int (*symlink) (const char *, const char *);
    int (*rename) (const char *, const char *);
    int (*link) (const char *, const char *);
    int (*chmod) (const char *, mode_t);
    int (*chown) (const char *, uid_t, gid_t);
    int (*truncate) (const char *, off_t);
    int (*utime) (const char *, struct utimbuf *);
    int (*open) (const char *, struct fuse_file_info *);
    int (*read) (const char *, char *, size_t, off_t, struct fuse_file_info *);
    int (*write) (const char *, const char *, size_t, off_t,struct fuse_file_info *);
    int (*statfs) (const char *, struct statfs *);
    int (*flush) (const char *, struct fuse_file_info *);
    int (*release) (const char *, struct fuse_file_info *);
    int (*fsync) (const char *, int, struct fuse_file_info *);
    int (*setxattr) (const char *, const char *, const char *, size_t, int);
    int (*getxattr) (const char *, const char *, char *, size_t);
    int (*listxattr) (const char *, char *, size_t);
    int (*removexattr) (const char *, const char *);
};
*/
#include <stdarg.h>


#include <zrtos/types.h>
#include <zrtos/error.h>

struct _zrtos_vfs_file_t;
struct _zrtos_vfs_dentry_t;
struct _zrtos_vfs_inode_t;

typedef size_t zrtos_vfs_offset_t;

typedef enum{
	 ZRTOS_VFS_PLUGIN_TYPE__FILE
	,ZRTOS_VFS_PLUGIN_TYPE__DIRECTORY
	,ZRTOS_VFS_PLUGIN_TYPE__FILESYSTEM
}zrtos_vfs_plugin_type_t;

#ifdef ZRTOS_VFS_PLUGIN__CFG_USE_SWITCH
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

#define ZRTOS_VFS_PLUGIN__ARG(type) va_arg(args,type)
#define ZRTOS_VFS_PLUGIN__RETURN(val)\
do{\
	ret = val;\
	goto L_RETURN;\
}while(0);

#ifdef ZRTOS_VFS_PLUGIN__CFG_USE_SWITCH
#define ZRTOS_VFS_PLUGIN__INIT(name,...)\
zrtos_error_t zrtos_vfs_plugin_module_##name##__operation(\
	 zrtos_vfs_plugin_operation_t operation\
	,...\
){\
	zrtos_error_t ret;\
	va_list args;\
	va_start(args,operation);\
	switch(operation){\
		__VA_ARGS__\
		default:\
			ZRTOS_VFS_PLUGIN__RETURN(ENOSYS);\
		break;\
	}\
\
L_RETURN:\
	va_end(args);\
	return ret;\
}\
\
zrtos_vfs_plugin_t zrtos_vfs_plugin_module_##name = {\
	 .operation = zrtos_vfs_plugin_module_##name##__operation\
};
#else
zrtos_error_t zrtos_vfs_plugin__default_open(struct _zrtos_vfs_file_t *thiz){return ESUCCESS;}
zrtos_error_t zrtos_vfs_plugin__default_close(struct _zrtos_vfs_file_t *thiz){return ESUCCESS;}
zrtos_error_t zrtos_vfs_plugin__default_mount(struct _zrtos_vfs_dentry_t *thiz){return ESUCCESS;}
zrtos_error_t zrtos_vfs_plugin__default_umount(struct _zrtos_vfs_dentry_t *thiz){return ESUCCESS;}
zrtos_error_t zrtos_vfs_plugin__default_read(struct _zrtos_vfs_file_t *thiz,char *path,void *buf,size_t len,zrtos_vfs_offset_t offset,size_t *out){return ENOSYS;}
zrtos_error_t zrtos_vfs_plugin__default_write(struct _zrtos_vfs_file_t *thiz,char *path,void *buf,size_t len,zrtos_vfs_offset_t offset,size_t *out){return ENOSYS;}
zrtos_error_t zrtos_vfs_plugin__default_can_read(struct _zrtos_vfs_file_t *thiz){return ESUCCESS;}
zrtos_error_t zrtos_vfs_plugin__default_can_write(struct _zrtos_vfs_file_t *thiz){return ESUCCESS;}
zrtos_error_t zrtos_vfs_plugin__default_can_write_read_only(struct _zrtos_vfs_file_t *thiz){return EAGAIN;}
zrtos_error_t zrtos_vfs_plugin__default_seek(struct _zrtos_vfs_file_t *thiz, zrtos_vfs_offset_t offset, int whence, zrtos_vfs_offset_t *out){return ENOSYS;}
zrtos_error_t zrtos_vfs_plugin__default_ioctl(struct _zrtos_vfs_file_t *thiz,char *path, int request, va_list args){return ENOSYS;}
#define ZRTOS_VFS_PLUGIN__INIT(name,...)\
zrtos_vfs_plugin_t zrtos_vfs_plugin_module_##name = {\
	__VA_ARGS__\
};
#endif

#define ZRTOS_VFS_PLUGIN(name) (&zrtos_vfs_plugin_module_##name)

#ifndef ZRTOS_VFS_PLUGIN__CFG_USE_SWITCH
#define ZRTOS_VFS_PLUGIN__INVOKE(thiz,operation,...) (thiz->operation(__VA_ARGS__))
#else
#define ZRTOS_VFS_PLUGIN__INVOKE(thiz,...) (thiz->operation(__VA_ARGS__))
#endif

typedef struct{
#ifndef ZRTOS_VFS_PLUGIN__CFG_USE_SWITCH
	zrtos_error_t (*open)(struct _zrtos_vfs_file_t *thiz);
# define ZRTOS_VFS_PLUGIN__0_ON_OPEN(callback) .open=callback
# define ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()\
	 .open = zrtos_vfs_plugin__default_open
#else
# define ZRTOS_VFS_PLUGIN__0_ON_OPEN(callback)                       \
    case ZRTOS_VFS_PLUGIN_OPERATION__OPEN:{                        \
        struct _zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(    \
            struct _zrtos_vfs_file_t*                              \
        );                                                         \
        ZRTOS_VFS_PLUGIN__RETURN(callback(file));                  \
        break;                                                     \
    }
# define ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()
#endif

#ifndef ZRTOS_VFS_PLUGIN__CFG_USE_SWITCH
	zrtos_error_t    (*close)(struct _zrtos_vfs_file_t *thiz);
# define ZRTOS_VFS_PLUGIN__1_ON_CLOSE(callback) ,.close=callback
# define ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()\
	,.close = zrtos_vfs_plugin__default_close
#else
# define ZRTOS_VFS_PLUGIN__1_ON_CLOSE(callback)                      \
    case ZRTOS_VFS_PLUGIN_OPERATION__CLOSE:{                       \
        struct _zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(    \
            struct _zrtos_vfs_file_t*                              \
        );                                                         \
        ZRTOS_VFS_PLUGIN__RETURN(callback(file));                  \
        break;                                                     \
    }
# define ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
#endif

#ifndef ZRTOS_VFS_PLUGIN__CFG_USE_SWITCH
	zrtos_error_t (*mount)(struct _zrtos_vfs_dentry_t *thiz);
# define ZRTOS_VFS_PLUGIN__2_ON_MOUNT(callback) ,.mount=callback
# define ZRTOS_VFS_PLUGIN__2_ON_MOUNT_DEFAULT()\
	,.mount = zrtos_vfs_plugin__default_mount
#else
# define ZRTOS_VFS_PLUGIN__2_ON_MOUNT(callback)                      \
    case ZRTOS_VFS_PLUGIN_OPERATION__MOUNT:{                       \
        struct _zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(    \
            struct _zrtos_vfs_file_t*                              \
        );                                                         \
        ZRTOS_VFS_PLUGIN__RETURN(callback(file));                  \
        break;                                                     \
    }
# define ZRTOS_VFS_PLUGIN__2_ON_MOUNT_DEFAULT()
#endif

#ifndef ZRTOS_VFS_PLUGIN__CFG_USE_SWITCH
	zrtos_error_t    (*umount)(struct _zrtos_vfs_dentry_t *thiz);
# define ZRTOS_VFS_PLUGIN__3_ON_UMOUNT(callback) ,.umount=callback
# define ZRTOS_VFS_PLUGIN__3_ON_UMOUNT_DEFAULT()\
	,.umount = zrtos_vfs_plugin__default_umount
#else
# define ZRTOS_VFS_PLUGIN__ON_UMOUNT(ret,dentry,callback)          \
    case ZRTOS_VFS_PLUGIN_OPERATION__UMOUNT:{                      \
        struct _zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(    \
            struct _zrtos_vfs_file_t*                              \
        );                                                         \
        ZRTOS_VFS_PLUGIN__RETURN(callback(file));                  \
        break;                                                     \
    }
# define ZRTOS_VFS_PLUGIN__3_ON_UMOUNT_DEFAULT()
#endif

#ifndef ZRTOS_VFS_PLUGIN__CFG_USE_SWITCH
	zrtos_error_t (*read)(struct _zrtos_vfs_file_t *thiz,char *path,void *buf,size_t len,zrtos_vfs_offset_t offset,size_t *out);
# define ZRTOS_VFS_PLUGIN__4_ON_READ(callback) ,.read=callback
# define ZRTOS_VFS_PLUGIN__4_ON_READ_DEFAULT()\
	,.read = zrtos_vfs_plugin__default_read
#else
# define ZRTOS_VFS_PLUGIN__4_ON_READ(callback)\
    case ZRTOS_VFS_PLUGIN_OPERATION__READ:{                       \
        struct _zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(    \
            struct _zrtos_vfs_file_t*                              \
        );                                                         \
        char    *path  = ZRTOS_VFS_PLUGIN__ARG(char*);            \
        void    *buf   = ZRTOS_VFS_PLUGIN__ARG(void*);            \
        size_t  len    = ZRTOS_VFS_PLUGIN__ARG(size_t);           \
        zrtos_vfs_offset_t   offset = ZRTOS_VFS_PLUGIN__ARG(zrtos_vfs_offset_t);            \
        size_t *out   = ZRTOS_VFS_PLUGIN__ARG(size_t*);          \
        ZRTOS_VFS_PLUGIN__RETURN(callback(file,path,buf,len,offset,out)); \
        break;                                                     \
    }
# define ZRTOS_VFS_PLUGIN__4_ON_READ_DEFAULT()
#endif

#ifndef ZRTOS_VFS_PLUGIN__CFG_USE_SWITCH
	zrtos_error_t (*write)(struct _zrtos_vfs_file_t *thiz,char *path,void *buf,size_t len,zrtos_vfs_offset_t offset,size_t *out);
# define ZRTOS_VFS_PLUGIN__5_ON_WRITE(callback) ,.write=callback
# define ZRTOS_VFS_PLUGIN__5_ON_WRITE_DEFAULT()\
	,.write = zrtos_vfs_plugin__default_write
#else
# define ZRTOS_VFS_PLUGIN__5_ON_WRITE(callback)\
    case ZRTOS_VFS_PLUGIN_OPERATION__WRITE:{                       \
        struct _zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(    \
            struct _zrtos_vfs_file_t*                              \
        );                                                         \
        char    *path  = ZRTOS_VFS_PLUGIN__ARG(char*);            \
        void    *buf   = ZRTOS_VFS_PLUGIN__ARG(void*);            \
        size_t  len    = ZRTOS_VFS_PLUGIN__ARG(size_t);           \
        zrtos_vfs_offset_t   offset = ZRTOS_VFS_PLUGIN__ARG(zrtos_vfs_offset_t);            \
        size_t *out   = ZRTOS_VFS_PLUGIN__ARG(size_t*);          \
        ZRTOS_VFS_PLUGIN__RETURN(callback(file,path,buf,len,offset,out)); \
        break;                                                     \
    }
# define ZRTOS_VFS_PLUGIN__5_ON_WRITE_DEFAULT()
#endif

#ifndef ZRTOS_VFS_PLUGIN__CFG_USE_SWITCH
	zrtos_error_t  (*can_read)(struct _zrtos_vfs_file_t *thiz);
# define ZRTOS_VFS_PLUGIN__6_ON_CAN_READ(callback) ,.can_read=callback
# define ZRTOS_VFS_PLUGIN__6_ON_CAN_READ_DEFAULT()\
	,.can_read = zrtos_vfs_plugin__default_can_read
#else
# define ZRTOS_VFS_PLUGIN__6_ON_CAN_READ(callback)                   \
    case ZRTOS_VFS_PLUGIN_OPERATION__CAN_READ:{                    \
        struct _zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(    \
            struct _zrtos_vfs_file_t*                              \
        );                                                         \
        ZRTOS_VFS_PLUGIN__RETURN(callback(file));                  \
        break;                                                     \
    }
# define ZRTOS_VFS_PLUGIN__6_ON_CAN_READ_DEFAULT()
#endif

#ifndef ZRTOS_VFS_PLUGIN__CFG_USE_SWITCH
	zrtos_error_t  (*can_write)(struct _zrtos_vfs_file_t *thiz);
# define ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE(callback) ,.can_write=callback
# define ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE_DEFAULT()\
	,.can_write = zrtos_vfs_plugin__default_can_write
#else
# define ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE(callback)                  \
    case ZRTOS_VFS_PLUGIN_OPERATION__CAN_WRITE:{                   \
        struct _zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(    \
            struct _zrtos_vfs_file_t*                              \
        );                                                         \
        ZRTOS_VFS_PLUGIN__RETURN(callback(file));                  \
        break;                                                     \
    }
# define ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE_DEFAULT()
#endif

#ifndef ZRTOS_VFS_PLUGIN__CFG_USE_SWITCH
	zrtos_error_t   (*seek)(struct _zrtos_vfs_file_t *thiz, zrtos_vfs_offset_t offset, int whence,zrtos_vfs_offset_t *out);
# define ZRTOS_VFS_PLUGIN__8_ON_SEEK(callback) ,.seek=callback
# define ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()\
	,.seek = zrtos_vfs_plugin__default_seek
#else
# define ZRTOS_VFS_PLUGIN__8_ON_SEEK(callback)  \
    case ZRTOS_VFS_PLUGIN_OPERATION__SEEK:{                      \
        struct _zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(    \
            struct _zrtos_vfs_file_t*                              \
        );                                                         \
        ZRTOS_VFS_PLUGIN__RETURN(callback(file));                  \
        break;                                                     \
    }                        \
		zrtos_vfs_offset_t   *ret   = ZRTOS_VFS_PLUGIN__ARG(zrtos_vfs_offset_t*);            \
		struct _zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(struct _zrtos_vfs_file_t*); \
		char    *path  = ZRTOS_VFS_PLUGIN__ARG(char*);             \
		zrtos_vfs_offset_t   offset = ZRTOS_VFS_PLUGIN__ARG(zrtos_vfs_offset_t);             \
		size_t  whence = ZRTOS_VFS_PLUGIN__ARG(size_t);            \
		ZRTOS_VFS_PLUGIN__RETURN(callback());                         \
		break;                                                        \
	}
# define ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
#endif

#ifndef ZRTOS_VFS_PLUGIN__CFG_USE_SWITCH
	zrtos_error_t (*ioctl)(struct _zrtos_vfs_file_t *thiz,char *path, int request, va_list args);
# define ZRTOS_VFS_PLUGIN__9_ON_IOCTL(callback) ,.ioctl=callback
# define ZRTOS_VFS_PLUGIN__9_ON_IOCTL_DEFAULT()\
	,.ioctl = zrtos_vfs_plugin__default_ioctl
#else
# define ZRTOS_VFS_PLUGIN__9_ON_IOCTL(callback)                                  \
    case ZRTOS_VFS_PLUGIN_OPERATION__IOCTL:{                                   \
        struct _zrtos_vfs_file_t *file = ZRTOS_VFS_PLUGIN__ARG(                \
            struct _zrtos_vfs_file_t*                                          \
        );                                                                     \
        char    *path      = ZRTOS_VFS_PLUGIN__ARG(char*);                     \
        int    request      = ZRTOS_VFS_PLUGIN__ARG(int);                      \
        va_list  args      = ZRTOS_VFS_PLUGIN__ARG(va_list);                   \
        ZRTOS_VFS_PLUGIN__RETURN(callback(file,path,request,args));            \
        break;                                                                 \
    }
# define ZRTOS_VFS_PLUGIN__9_ON_IOCTL_DEFAULT()
#endif

#ifdef ZRTOS_VFS_PLUGIN__CFG_USE_SWITCH
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