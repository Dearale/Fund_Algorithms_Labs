#include <stddef.h>

#if defined(__APPLE)
    static const char *error_messages[] = {
        "Success",                                  // 0
        "Operation not permitted",                  // 1 EPERM
        "No such file or directory",                // 2 ENOENT
        "No such process",                          // 3 ESRCH
        "Interrupted system call",                  // 4 EINTR
        "Input/output error",                       // 5 EIO
        "Device not configured",                    // 6 ENXIO
        "Argument list too long",                   // 7 E2BIG
        "Exec format error",                        // 8 ENOEXEC
        "Bad file descriptor",                      // 9 EBADF
        "No child processes",                       // 10 ECHILD
        "Resource deadlock avoided",                // 11 EDEADLK
        "Cannot allocate memory",                   // 12 ENOMEM
        "Permission denied",                        // 13 EACCES
        "Bad address",                              // 14 EFAULT
        "Block device required",                    // 15 ENOTBLK
        "Device / Resource busy",                   // 16 EBUSY
        "File exists",                              // 17 EEXIST
        "Cross-device link",                        // 18 EXDEV
        "Operation not supported by device",        // 19 ENODEV
        "Not a directory",                          // 20 ENOTDIR
        "Is a directory",                           // 21 EISDIR
        "Invalid argument",                         // 22 EINVAL
        "Too many open files in system",            // 23 ENFILE
        "Too many open files",                      // 24 EMFILE
        "Inappropriate ioctl for device",           // 25 ENOTTY
        "Text file busy",                           // 26 ETXTBSY
        "File too large",                           // 27 EFBIG
        "No space left on device",                  // 28 ENOSPC
        "Illegal seek",                             // 29 ESPIPE
        "Read-only file system",                    // 30 EROFS
        "Too many links",                           // 31 EMLINK
        "Broken pipe",                              // 32 EPIPE
        "Numerical argument out of domain",         // 33 EDOM
        "Result too large",                         // 34 ERANGE
        "Resource temporarily unavailable",         // 35 EAGAIN
        "Operation would block",                    // 36 EWOULDBLOCK
        "Operation now in progress",                // 37 EINPROGRESS
        "Operation already in progress",            // 38 EALREADY
        "Socket operation on non-socket",           // 39 ENOTSOCK
        "Destination address required",             // 40 EDESTADDRREQ
        "Message too long",                         // 41 EMSGSIZE
        "Protocol wrong type for socket",           // 42 EPROTOTYPE
        "Protocol not available",                   // 43 ENOPROTOOPT
        "Protocol not supported",                   // 44 EPROTONOSUPPORT
        "Socket type not supported",                // 45 ESOCKTNOSUPPORT
        "Operation not supported",                  // 46 ENOTSUP
        "Protocol family not supported",            // 47 EPFNOSUPPORT
        "Address family not supported by protocol family", // 48 EAFNOSUPPORT
        "Address already in use",                   // 49 EADDRINUSE
        "Can't assign requested address",           // 50 EADDRNOTAVAIL
        "Network is down",                          // 51 ENETDOWN
        "Network is unreachable",                   // 52 ENETUNREACH
        "Network dropped connection on reset",      // 53 ENETRESET
        "Software caused connection abort",         // 54 ECONNABORTED
        "Connection reset by peer",                 // 55 ECONNRESET
        "No buffer space available",                // 56 ENOBUFS
        "Socket is already connected",              // 57 EISCONN
        "Socket is not connected",                  // 58 ENOTCONN
        "Can't send after socket shutdown",         // 59 ESHUTDOWN
        "Too many references: can't splice",        // 60 ETOOMANYREFS
        "Operation timed out",                      // 61 ETIMEDOUT
        "Connection refused",                       // 62 ECONNREFUSED
        "Too many levels of symbolic links",        // 63 ELOOP
        "File name too long",                       // 64 ENAMETOOLONG
        "Host is down",                             // 65 EHOSTDOWN
        "No route to host",                         // 66 EHOSTUNREACH
        "Directory not empty",                      // 67 ENOTEMPTY
        "Too many processes",                       // 68 EPROCLIM
        "Too many users",                           // 69 EUSERS
        "Disk quota exceeded",                      // 70 EDQUOT
        "Stale NFS file handle",                    // 71 ESTALE
        "Too many levels of remote in path",        // 72 EREMOTE
        "RPC struct is bad",                        // 73 EBADRPC
        "RPC version wrong",                        // 74 ERPCMISMATCH
        "RPC prog. not avail",                      // 75 EPROGUNAVAIL
        "Program version wrong",                    // 76 EPROGMISMATCH
        "Bad procedure for program",                // 77 EPROCUNAVAIL
        "No locks available",                       // 78 ENOLCK
        "Function not implemented",                 // 79 ENOSYS
        "Inappropriate file type or format",        // 80 EFTYPE
        "Authentication error",                     // 81 EAUTH
        "Need authenticator",                       // 82 ENEEDAUTH
        "Device power is off",                      // 83 EPWROFF
        "Device error",                             // 84 EDEVERR
        "Value too large to be stored in data type", // 85 EOVERFLOW
        "Bad executable (or shared library)",       // 86 EBADEXEC
        "Bad CPU type in executable",               // 87 EBADARCH
        "Shared library version mismatch",          // 88 ESHLIBVERS
        "Malformed Mach-o file",                    // 89 EBADMACHO
        "Operation canceled",                       // 90 ECANCELED
        "Identifier removed",                       // 91 EIDRM
        "No message of desired type",               // 92 ENOMSG
        "Illegal byte sequence",                    // 93 EILSEQ
        "Attribute not found",                      // 94 ENOATTR
        "Bad message",                              // 95 EBADMSG
        "EMULTIHOP (Reserved)",                     // 96 EMULTIHOP
        "No message available on STREAM",           // 97 ENODATA
        "ENOLINK (Reserved)",                       // 98 ENOLINK
        "No STREAM resources",                      // 99 ENOSR
        "Not a STREAM",                             // 100 ENOSTR
        "Protocol error",                           // 101 EPROTO
        "STREAM ioctl timeout",                     // 102 ETIME
        "Operation not supported on socket",        // 103 EOPNOTSUPP
        "No such policy registered",                // 104 ENOPOLICY
        "State not recoverable",                    // 105 ENOTRECOVERABLE
        "Previous owner died",                      // 106 EOWNERDEAD
        "Interface output queue is full",           // 107 EQFULL
    };
    #define MAX_ERRNO 107
#elif defined(__linux__)
    static const char *error_messages[] = {
        "Success",                                  // 0
        "Operation not permitted",                  // 1 EPERM
        "No such file or directory",                // 2 ENOENT
        "No such process",                          // 3 ESRCH
        "Interrupted system call",                  // 4 EINTR
        "Input/output error",                       // 5 EIO
        "No such device or address",                // 6 ENXIO
        "Argument list too long",                   // 7 E2BIG
        "Exec format error",                        // 8 ENOEXEC
        "Bad file descriptor",                      // 9 EBADF
        "No child processes",                       // 10 ECHILD
        "Resource temporarily unavailable",         // 11 EAGAIN
        "Cannot allocate memory",                   // 12 ENOMEM
        "Permission denied",                        // 13 EACCES
        "Bad address",                              // 14 EFAULT
        "Block device required",                    // 15 ENOTBLK
        "Device or resource busy",                  // 16 EBUSY
        "File exists",                              // 17 EEXIST
        "Invalid cross-device link",                // 18 EXDEV
        "No such device",                           // 19 ENODEV
        "Not a directory",                          // 20 ENOTDIR
        "Is a directory",                           // 21 EISDIR
        "Invalid argument",                         // 22 EINVAL
        "Too many open files in system",            // 23 ENFILE
        "Too many open files",                      // 24 EMFILE
        "Inappropriate ioctl for device",           // 25 ENOTTY
        "Text file busy",                           // 26 ETXTBSY
        "File too large",                           // 27 EFBIG
        "No space left on device",                  // 28 ENOSPC
        "Illegal seek",                             // 29 ESPIPE
        "Read-only file system",                    // 30 EROFS
        "Too many links",                           // 31 EMLINK
        "Broken pipe",                              // 32 EPIPE
        "Numerical argument out of domain",         // 33 EDOM
        "Numerical result out of range",            // 34 ERANGE
        "Resource deadlock avoided",                // 35 EDEADLK
        "File name too long",                       // 36 ENAMETOOLONG
        "No locks available",                       // 37 ENOLCK
        "Function not implemented",                 // 38 ENOSYS
        "Directory not empty",                      // 39 ENOTEMPTY
        "Too many levels of symbolic links",        // 40 ELOOP
        "No message of desired type",               // 42 ENOMSG
        "Identifier removed",                       // 43 EIDRM
        "Channel number out of range",              // 44 ECHRNG
        "Level 2 not synchronized",                 // 45 EL2NSYNC
        "Level 3 halted",                           // 46 EL3HLT
        "Level 3 reset",                            // 47 EL3RST
        "Link number out of range",                 // 48 ELNRNG
        "Protocol driver not attached",             // 49 EUNATCH
        "No CSI structure available",               // 50 ENOCSI
        "Level 2 halted",                           // 51 EL2HLT
        "Invalid exchange",                         // 52 EBADE
        "Invalid request descriptor",               // 53 EBADR
        "Exchange full",                            // 54 EXFULL
        "No anode",                                 // 55 ENOANO
        "Invalid request code",                     // 56 EBADRQC
        "Invalid slot",                             // 57 EBADSLT
        "Resource deadlock would occur",            // 58 EDEADLOCK
        "Bad font file format",                     // 59 EBFONT
        "Device not a stream",                      // 60 ENOSTR
        "No data available",                        // 61 ENODATA
        "Timer expired",                            // 62 ETIME
        "Out of streams resources",                 // 63 ENOSR
        "Machine is not on the network",            // 64 ENONET
        "Package not installed",                    // 65 ENOPKG
        "Object is remote",                         // 66 EREMOTE
        "Link has been severed",                    // 67 ENOLINK
        "Advertise error",                          // 68 EADV
        "Srmount error",                            // 69 ESRMNT
        "Communication error on send",              // 70 ECOMM
        "Protocol error",                           // 71 EPROTO
        "Multihop attempted",                       // 72 EMULTIHOP
        "RFS specific error",                       // 73 EDOTDOT
        "Invalid message",                          // 74 EBADMSG
        "Value too large for defined data type",    // 75 EOVERFLOW
        "Name not unique on network",               // 76 ENOTUNIQ
        "File descriptor in bad state",             // 77 EBADFD
        "Remote address changed",                   // 78 EREMCHG
        "Can not access a needed shared library",   // 79 ELIBACC
        "Accessing a corrupted shared library",     // 80 ELIBBAD
        ".lib section in a.out corrupted",          // 81 ELIBSCN
        "Attempting to link in too many shared libraries", // 82 ELIBMAX
        "Cannot exec a shared library directly",    // 83 ELIBEXEC
        "Illegal byte sequence",                    // 84 EILSEQ
        "Interrupted system call should be restarted", // 85 ERESTART
        "Streams pipe error",                       // 86 ESTRPIPE
        "Too many users",                           // 87 EUSERS
        "Socket operation on non-socket",           // 88 ENOTSOCK
        "Destination address required",             // 89 EDESTADDRREQ
        "Message too long",                         // 90 EMSGSIZE
        "Protocol wrong type for socket",           // 91 EPROTOTYPE
        "Protocol not available",                   // 92 ENOPROTOOPT
        "Protocol not supported",                   // 93 EPROTONOSUPPORT
        "Socket type not supported",                // 94 ESOCKTNOSUPPORT
        "Operation not supported",                  // 95 EOPNOTSUPP
        "Protocol family not supported",            // 96 EPFNOSUPPORT
        "Address family not supported by protocol", // 97 EAFNOSUPPORT
        "Address already in use",                   // 98 EADDRINUSE
        "Cannot assign requested address",          // 99 EADDRNOTAVAIL
        "Network is down",                          // 100 ENETDOWN
        "Network is unreachable",                   // 101 ENETUNREACH
        "Network dropped connection on reset",      // 102 ENETRESET
        "Software caused connection abort",         // 103 ECONNABORTED
        "Connection reset by peer",                 // 104 ECONNRESET
        "No buffer space available",                // 105 ENOBUFS
        "Transport endpoint is already connected",  // 106 EISCONN
        "Transport endpoint is not connected",      // 107 ENOTCONN
        "Cannot send after transport endpoint shutdown", // 108 ESHUTDOWN
        "Too many references: cannot splice",       // 109 ETOOMANYREFS
        "Connection timed out",                     // 110 ETIMEDOUT
        "Connection refused",                       // 111 ECONNREFUSED
        "Host is down",                             // 112 EHOSTDOWN
        "No route to host",                         // 113 EHOSTUNREACH
        "Operation already in progress",            // 114 EALREADY
        "Operation now in progress",                // 115 EINPROGRESS
        "Stale file handle",                        // 116 ESTALE
        "Structure needs cleaning",                 // 117 EUCLEAN
        "Not a XENIX named type file",              // 118 ENOTNAM
        "No XENIX semaphores available",            // 119 ENAVAIL
        "Is a named type file",                     // 120 EISNAM
        "Remote I/O error",                         // 121 EREMOTEIO
        "Disk quota exceeded",                      // 122 EDQUOT
        "No medium found",                          // 123 ENOMEDIUM
        "Wrong medium type",                        // 124 EMEDIUMTYPE
        "Operation canceled",                       // 125 ECANCELED
        "Required key not available",               // 126 ENOKEY
        "Key has expired",                          // 127 EKEYEXPIRED
        "Key has been revoked",                     // 128 EKEYREVOKED
        "Key was rejected by service",              // 129 EKEYREJECTED
        "Owner died",                               // 130 EOWNERDEAD
        "State not recoverable",                    // 131 ENOTRECOVERABLE
        "Operation not possible due to RF-kill",    // 132 ERFKILL
        "Memory page has hardware error",           // 133 EHWPOISON
    };
    #define MAX_ERRNO 133
#endif