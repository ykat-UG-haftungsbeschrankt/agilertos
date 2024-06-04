/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_SYS_TYPES_H
#define ZRTOS_SYS_TYPES_H
#ifdef __cplusplus
extern "C" {
#endif


typedef size_t blkcnt_t; ///<Used for file block counts
typedef size_t blksize_t; ///<Used for block sizes
typedef size_t clock_t; ///<Used for system times in clock ticks or CLOCKS_PER_SEC (see <time.h>).
typedef size_t clockid_t; ///<Used for clock ID type in the clock and timer functions.
typedef size_t dev_t; ///<Used for device IDs.
typedef size_t fsblkcnt_t; ///<Used for file system block counts
typedef size_t fsfilcnt_t; ///<Used for file system file counts
typedef size_t gid_t; ///<Used for group IDs.
typedef size_t id_t; ///<Used as a general identifier; can be used to contain at least a pid_t, uid_t or a gid_t.
typedef size_t ino_t; ///<Used for file serial numbers.
typedef size_t key_t; ///<Used for interprocess communication.
typedef size_t mode_t; ///<Used for some file attributes.
typedef size_t nlink_t; ///<Used for link counts.
typedef size_t off_t; ///<Used for file sizes.
typedef size_t pid_t; ///<Used for process IDs and process group IDs.
typedef size_t pthread_attr_t; ///<Used to identify a thread attribute object.
typedef size_t pthread_cond_t; ///<Used for condition variables.
typedef size_t pthread_condattr_t; ///<Used to identify a condition attribute object.
typedef size_t pthread_key_t; ///<Used for thread-specific data keys.
typedef size_t pthread_mutex_t; ///<Used for mutexes.
typedef size_t pthread_mutexattr_t; ///<Used to identify a mutex attribute object.
typedef size_t pthread_once_t; ///<Used for dynamic package initialisation.
typedef size_t pthread_rwlock_t; ///<Used for read-write locks.
typedef size_t pthread_rwlockattr_t; ///<Used for read-write lock attributes.
typedef size_t pthread_t; ///<Used to identify a thread.
typedef size_t size_t; ///<Used for sizes of objects.
typedef size_t ssize_t; ///<Used for a count of bytes or an error indication.
typedef size_t suseconds_t; ///<Used for time in microseconds
typedef size_t time_t; ///<Used for time in seconds.
typedef size_t timer_t; ///<Used for timer ID returned by timer_create().
typedef size_t uid_t; ///<Used for user IDs.
typedef size_t useconds_t; ///<Used for time in microseconds.


#ifdef __cplusplus
}
#endif
#endif