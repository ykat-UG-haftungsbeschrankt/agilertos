/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_ERROR_H
#define ZRTOS_ERROR_H
#ifdef __cplusplus
extern "C" {
#endif


#include <limits.h>
#include <stdbool.h>

#include <zrtos/assert.h>


typedef enum{
	 ZRTOS_ERROR__MIN             = INT_MIN  ///< Minimum value of zrtos_error_t
	,ZRTOS_ERROR__SUCCESS         = 0        ///< Successful program execution status
	,ZRTOS_ERROR__ERROR           = -1       ///< Unsuccessful program execution status
	,ZRTOS_ERROR__FIRST           = -1       ///< Smallest error code
	,ZRTOS_ERROR__PERM            = -1       ///< Operation not permitted
	,ZRTOS_ERROR__NOENT           = -2       ///< No such file or directory
	,ZRTOS_ERROR__SRCH            = -3       ///< No such process
	,ZRTOS_ERROR__INTR            = -4       ///< Interrupted system call
	,ZRTOS_ERROR__IO              = -5       ///< I/O error
	,ZRTOS_ERROR__NXIO            = -6       ///< No such device or address
	,ZRTOS_ERROR__2BIG            = -7       ///< Arg list too long
	,ZRTOS_ERROR__NOEXEC          = -8       ///< Exec format error
	,ZRTOS_ERROR__BADF            = -9       ///< Bad file number
	,ZRTOS_ERROR__CHILD           = -10      ///< No child processes
	,ZRTOS_ERROR__AGAIN           = -11      ///< Try again
	,ZRTOS_ERROR__NOMEM           = -12      ///< Out of memory
	,ZRTOS_ERROR__ACCES           = -13      ///< Permission denied
	,ZRTOS_ERROR__FAULT           = -14      ///< Bad address
	,ZRTOS_ERROR__NOTBLK          = -15      ///< Block device required
	,ZRTOS_ERROR__BUSY            = -16      ///< Device or resource busy
	,ZRTOS_ERROR__EXIST           = -17      ///< File exists
	,ZRTOS_ERROR__XDEV            = -18      ///< Cross-device link
	,ZRTOS_ERROR__NODEV           = -19      ///< No such device
	,ZRTOS_ERROR__NOTDIR          = -20      ///< Not a directory
	,ZRTOS_ERROR__ISDIR           = -21      ///< Is a directory
	,ZRTOS_ERROR__INVAL           = -22      ///< Invalid argument
	,ZRTOS_ERROR__NFILE           = -23      ///< File table overflow
	,ZRTOS_ERROR__MFILE           = -24      ///< Too many open files
	,ZRTOS_ERROR__NOTTY           = -25      ///< Not a typewriter
	,ZRTOS_ERROR__TXTBSY          = -26      ///< Text file busy
	,ZRTOS_ERROR__FBIG            = -27      ///< File too large
	,ZRTOS_ERROR__NOSPC           = -28      ///< No space left on device
	,ZRTOS_ERROR__SPIPE           = -29      ///< Illegal seek
	,ZRTOS_ERROR__ROFS            = -30      ///< Read-only file system
	,ZRTOS_ERROR__MLINK           = -31      ///< Too many links
	,ZRTOS_ERROR__PIPE            = -32      ///< Broken pipe
	,ZRTOS_ERROR__DOM             = -33      ///< Math argument out of domain of func
	,ZRTOS_ERROR__RANGE           = -34      ///< Math result not representable
	,ZRTOS_ERROR__DEADLK          = -35      ///< Resource deadlock would occur
	,ZRTOS_ERROR__NAMETOOLONG     = -36      ///< File name too long
	,ZRTOS_ERROR__NOLCK           = -37      ///< No record locks available
	,ZRTOS_ERROR__NOSYS           = -38      ///< Function not implemented
	,ZRTOS_ERROR__NOTEMPTY        = -39      ///< Directory not empty
	,ZRTOS_ERROR__LOOP            = -40      ///< Too many symbolic links encountered
	,ZRTOS_ERROR__WOULDBLOCK      = -41      ///< Operation would block
	,ZRTOS_ERROR__NOMSG           = -42      ///< No message of desired type
	,ZRTOS_ERROR__IDRM            = -43      ///< Identifier removed
	,ZRTOS_ERROR__CHRNG           = -44      ///< Channel number out of range
	,ZRTOS_ERROR__L2NSYNC         = -45      ///< Level 2 not synchronized
	,ZRTOS_ERROR__L3HLT           = -46      ///< Level 3 halted
	,ZRTOS_ERROR__L3RST           = -47      ///< Level 3 reset
	,ZRTOS_ERROR__LNRNG           = -48      ///< Link number out of range
	,ZRTOS_ERROR__UNATCH          = -49      ///< Protocol driver not attached
	,ZRTOS_ERROR__NOCSI           = -50      ///< No CSI structure available
	,ZRTOS_ERROR__L2HLT           = -51      ///< Level 2 halted
	,ZRTOS_ERROR__BADE            = -52      ///< Invalid exchange
	,ZRTOS_ERROR__BADR            = -53      ///< Invalid request descriptor
	,ZRTOS_ERROR__XFULL           = -54      ///< Exchange full
	,ZRTOS_ERROR__NOANO           = -55      ///< No anode
	,ZRTOS_ERROR__BADRQC          = -56      ///< Invalid request code
	,ZRTOS_ERROR__BADSLT          = -57      ///< Invalid slot
	,ZRTOS_ERROR__DEADLOCK        = -58      ///< File locking deadlock error
	,ZRTOS_ERROR__BFONT           = -59      ///< Bad font file format
	,ZRTOS_ERROR__NOSTR           = -60      ///< Device not a stream
	,ZRTOS_ERROR__NODATA          = -61      ///< No data available
	,ZRTOS_ERROR__TIME            = -62      ///< Timer expired
	,ZRTOS_ERROR__NOSR            = -63      ///< Out of streams resources
	,ZRTOS_ERROR__NONET           = -64      ///< Machine is not on the network
	,ZRTOS_ERROR__NOPKG           = -65      ///< Package not installed
	,ZRTOS_ERROR__REMOTE          = -66      ///< Object is remote
	,ZRTOS_ERROR__NOLINK          = -67      ///< Link has been severed
	,ZRTOS_ERROR__ADV             = -68      ///< Advertise error
	,ZRTOS_ERROR__SRMNT           = -69      ///< Srmount error
	,ZRTOS_ERROR__COMM            = -70      ///< Communication error on send
	,ZRTOS_ERROR__PROTO           = -71      ///< Protocol error
	,ZRTOS_ERROR__MULTIHOP        = -72      ///< Multihop attempted
	,ZRTOS_ERROR__DOTDOT          = -73      ///< RFS specific error
	,ZRTOS_ERROR__BADMSG          = -74      ///< Not a data message
	,ZRTOS_ERROR__OVERFLOW        = -75      ///< Value too large for defined data type
	,ZRTOS_ERROR__NOTUNIQ         = -76      ///< Name not unique on network
	,ZRTOS_ERROR__BADFD           = -77      ///< File descriptor in bad state
	,ZRTOS_ERROR__REMCHG          = -78      ///< Remote address changed
	,ZRTOS_ERROR__LIBACC          = -79      ///< Can not access a needed shared library
	,ZRTOS_ERROR__LIBBAD          = -80      ///< Accessing a corrupted shared library
	,ZRTOS_ERROR__LIBSCN          = -81      ///< .lib section in a.out corrupted
	,ZRTOS_ERROR__LIBMAX          = -82      ///< Attempting to link in too many shared libraries
	,ZRTOS_ERROR__LIBEXEC         = -83      ///< Cannot exec a shared library directly
	,ZRTOS_ERROR__ILSEQ           = -84      ///< Illegal byte sequence
	,ZRTOS_ERROR__RESTART         = -85      ///< Interrupted system call should be restarted
	,ZRTOS_ERROR__STRPIPE         = -86      ///< Streams pipe error
	,ZRTOS_ERROR__USERS           = -87      ///< Too many users
	,ZRTOS_ERROR__NOTSOCK         = -88      ///< Socket operation on non-socket
	,ZRTOS_ERROR__DESTADDRREQ     = -89      ///< Destination address required
	,ZRTOS_ERROR__MSGSIZE         = -90      ///< Message too long
	,ZRTOS_ERROR__PROTOTYPE       = -91      ///< Protocol wrong type for socket
	,ZRTOS_ERROR__NOPROTOOPT      = -92      ///< Protocol not available
	,ZRTOS_ERROR__PROTONOSUPPORT  = -93      ///< Protocol not supported
	,ZRTOS_ERROR__SOCKTNOSUPPORT  = -94      ///< Socket type not supported
	,ZRTOS_ERROR__OPNOTSUPP       = -95      ///< Operation not supported on transport endpoint
	,ZRTOS_ERROR__PFNOSUPPORT     = -96      ///< Protocol family not supported
	,ZRTOS_ERROR__AFNOSUPPORT     = -97      ///< Address family not supported by protocol
	,ZRTOS_ERROR__ADDRINUSE       = -98      ///< Address already in use
	,ZRTOS_ERROR__ADDRNOTAVAIL    = -99      ///< Cannot assign requested address
	,ZRTOS_ERROR__NETDOWN         = -100     ///< Network is down
	,ZRTOS_ERROR__NETUNREACH      = -101     ///< Network is unreachable
	,ZRTOS_ERROR__NETRESET        = -102     ///< Network dropped connection because of reset
	,ZRTOS_ERROR__CONNABORTED     = -103     ///< Software caused connection abort
	,ZRTOS_ERROR__CONNRESET       = -104     ///< Connection reset by peer
	,ZRTOS_ERROR__NOBUFS          = -105     ///< No buffer space available
	,ZRTOS_ERROR__ISCONN          = -106     ///< Transport endpoint is already connected
	,ZRTOS_ERROR__NOTCONN         = -107     ///< Transport endpoint is not connected
	,ZRTOS_ERROR__SHUTDOWN        = -108     ///< Cannot send after transport endpoint shutdown
	,ZRTOS_ERROR__TOOMANYREFS     = -109     ///< Too many references: cannot splice
	,ZRTOS_ERROR__TIMEDOUT        = -110     ///< Connection timed out
	,ZRTOS_ERROR__CONNREFUSED     = -111     ///< Connection refused
	,ZRTOS_ERROR__HOSTDOWN        = -112     ///< Host is down
	,ZRTOS_ERROR__HOSTUNREACH     = -113     ///< No route to host
	,ZRTOS_ERROR__ALREADY         = -114     ///< Operation already in progress
	,ZRTOS_ERROR__INPROGRESS      = -115     ///< Operation now in progress
	,ZRTOS_ERROR__STALE           = -116     ///< Stale NFS file handle
	,ZRTOS_ERROR__UCLEAN          = -117     ///< Structure needs cleaning
	,ZRTOS_ERROR__NOTNAM          = -118     ///< Not a XENIX named type file
	,ZRTOS_ERROR__NAVAIL          = -119     ///< No XENIX semaphores available
	,ZRTOS_ERROR__ISNAM           = -120     ///< Is a named type file
	,ZRTOS_ERROR__REMOTEIO        = -121     ///< Remote I/O error
	,ZRTOS_ERROR__LAST            = -121     ///< Greatest error code
	,ZRTOS_ERROR__MAX             = INT_MAX ///< Maximum value of zrtos_error_t
}zrtos_error_t;

ZRTOS_ASSERT__STATIC(sizeof(zrtos_error_t) == sizeof(int));

bool zrtos_error__is_success(zrtos_error_t thiz){
	return thiz >= 0;
}

bool zrtos_error__is_error(zrtos_error_t thiz){
	return thiz < 0;
}


#ifdef __cplusplus
}
#endif
#endif