/*
* This is a workaround for the difference in fnctl encoding. If we don't fix it,
* some libc call will behave abnormal, like cannot create a new file to write
* with fopen(fname, "w").
*
* A related issue:
* https://github.com/riscv/riscv-gnu-toolchain/issues/510
*
*/

/*************************************************************
* 1. Cancle all the possibly established definitions         *
*************************************************************/

#undef _FOPEN
#undef _FREAD
#undef _FWRITE
#undef _FAPPEND
#undef _FMARK
#undef _FDEFER
#undef _FASYNC
#undef _FSHLOCK
#undef _FEXLOCK
#undef _FCREAT
#undef _FTRUNC
#undef _FEXCL
#undef _FNBIO
#undef _FSYNC
#undef _FNONBLOCK
#undef _FNDELAY
#undef _FNOCTTY
#undef _FBINARY
#undef _FTEXT
#undef _FNOINHERIT
#undef _FDIRECT
#undef _FNOFOLLOW
#undef _FDIRECTORY
#undef _FEXECSRCH
#undef _FTMPFILE
#undef _FNOATIME
#undef _FPATH

#undef O_ACCMODE

/*
 * Flag values for open(2) and fcntl(2)
 * The kernel adds 1 to the open modes to turn it into some
 * combination of FREAD and FWRITE.
 */
#undef O_RDONLY
#undef O_WRONLY
#undef O_RDWR
#undef O_APPEND
#undef O_CREAT
#undef O_TRUNC
#undef O_EXCL
#undef O_SYNC
/*	O_NDELAY	_FNDELAY 	set in include/fcntl.h */
/*	O_NDELAY	_FNBIO 		set in include/fcntl.h */
#undef O_NONBLOCK
#undef O_NOCTTY

/* POSIX-1.2008 specific flags */
#undef O_CLOEXEC
#undef O_NOFOLLOW
#undef O_DIRECTORY
#undef O_EXEC
#undef O_SEARCH

#undef O_DIRECT

#undef O_BINARY
#undef O_TEXT
#undef O_DSYNC
#undef O_RSYNC

#undef O_TMPFILE
#undef O_NOATIME
#undef O_PATH


/*
 * Flags that work for fcntl(fd, F_SETFL, FXXXX)
 */
#undef FAPPEND
#undef FSYNC
#undef FASYNC
#undef FNBIO
#undef FNONBIO
#undef FNDELAY

/*
 * Flags that are disallowed for fcntl's (FCNTLCANT);
 * used for opens, internal state, or locking.
 */
#undef FREAD
#undef FWRITE
#undef FMARK
#undef FDEFER
#undef FSHLOCK
#undef FEXLOCK

/*
 * The rest of the flags, used only for opens
 */
#undef FOPEN
#undef FCREAT
#undef FTRUNC
#undef FEXCL
#undef FNOCTTY

#undef FNONBLOCK

/* XXX close on exec request; must match UF_EXCLOSE in user.h */
#undef FD_CLOEXEC

/* fcntl(2) requests */
#undef F_DUPFD
#undef F_GETFD
#undef F_SETFD
#undef F_GETFL
#undef F_SETFL
#undef F_GETOWN
#undef F_SETOWN
#undef F_GETLK
#undef F_SETLK
#undef F_SETLKW
#undef F_RGETLK
#undef F_RSETLK
#undef F_CNVT
#undef F_RSETLKW
#undef F_DUPFD_CLOEXEC

/* fcntl(2) flags (l_type field of flock structure) */
#undef F_RDLCK
#undef F_WRLCK
#undef F_UNLCK
#undef F_UNLKSYS

/* Special descriptor value to denote the cwd in calls to openat(2) etc. */
#undef AT_FDCWD

/* Flag values for faccessat2) et al. */
#undef AT_EACCESS
#undef AT_SYMLINK_NOFOLLOW
#undef AT_SYMLINK_FOLLOW
#undef AT_REMOVEDIR
#undef AT_EMPTY_PATH


/* lock operations for flock(2) */
#undef LOCK_SH
#undef LOCK_EX
#undef LOCK_NB
#undef LOCK_U


/*************************************************************
* 2. Re-define the essential macros with Linux encoding      *
*************************************************************/

#define O_ACCMODE 0x00000003
#define O_RDONLY 0x00000000
#define O_WRONLY 0x00000001
#define O_RDWR 0x00000002
#define O_APPEND 0x00000400
#define O_CREAT 0x00000040
#define O_TRUNC 0x00000200
#define O_EXCL 0x00000080
#define O_SYNC 0x00101000
#define O_NONBLOCK 0x00000800
#define O_NOCTTY 0x00000100
/* POSIX-1.2008 specific flags */
#if __POSIX_VISIBLE >= 200809
#define O_CLOEXEC 0x00080000
#define O_NOFOLLOW 0x00020000
#define O_DIRECTORY 0x00010000
#endif
#if __BSD_VISIBLE
#define O_DIRECT 0x00004000
#endif

#if defined (__CYGWIN__)
#define O_DSYNC 0x00001000
#define O_RSYNC 0x00101000

/* Linux-specific flags */
#if __GNU_VISIBLE
#define O_TMPFILE 0x00410000
#define O_NOATIME 0x00040000
#define O_PATH 0x00200000
#endif
#endif

#if __MISC_VISIBLE
#define FAPPEND 0x00000400
#define FASYNC 0x00002000
#define FNDELAY 0x00000800
#endif	/* __MISC_VISIBLE */

#if __BSD_VISIBLE
#define FNONBLOCK 0x00000800
#endif	/* __BSD_VISIBLE */

#define FD_CLOEXEC 0x00000001
#define F_DUPFD 0x00000000
#define F_GETFD 0x00000001
#define F_SETFD 0x00000002
#define F_GETFL 0x00000003
#define F_SETFL 0x00000004
#if __BSD_VISIBLE || __POSIX_VISIBLE >= 200112
#define F_GETOWN 0x00000009
#define F_SETOWN 0x00000008
#endif /* __BSD_VISIBLE || __POSIX_VISIBLE >= 200112 */
#define F_GETLK 0x00000005
#define F_SETLK 0x00000006
#define F_SETLKW 0x00000007
#if __POSIX_VISIBLE >= 200809
#define F_DUPFD_CLOEXEC 0x00000406
#endif
#define F_RDLCK 0x00000000
#define F_WRLCK 0x00000001
#define F_UNLCK 0x00000002

#if __BSD_VISIBLE || __POSIX_VISIBLE >= 200809
#define AT_FDCWD 0xFFFFFF9C
#define AT_EACCESS 0x00000200
#define AT_SYMLINK_NOFOLLOW 0x00000100
#define AT_SYMLINK_FOLLOW 0x00000400
#define AT_REMOVEDIR 0x00000200
#if __GNU_VISIBLE
#define AT_EMPTY_PATH 0x00001000
#endif
#endif

#if __BSD_VISIBLE
#define LOCK_SH 0x00000001
#define LOCK_EX 0x00000002
#define LOCK_NB 0x00000004
#define LOCK_UN 0x00000008
#endif
