%define __NR_READ 0
%define __NR_WRITE 1
%define __NR_OPEN 2
%define __NR_CLOSE 3
%define __NR_STAT 4
%define __NR_FSTAT 5
%define __NR_LSTAT 6
%define __NR_POLL 7
%define __NR_LSEEK 8
%define __NR_MMAP 9
%define __NR_MPROTECT 10
%define __NR_MUNMAP 11
%define __NR_BRK 12
%define __NR_RT_SIGACTION 13
%define __NR_RT_SIGPROCMASK 14
%define __NR_RT_SIGRETURN 15
%define __NR_IOCTL 16
%define __NR_PREAD64 17
%define __NR_PWRITE64 18
%define __NR_READV 19
%define __NR_WRITEV 20
%define __NR_ACCESS 21
%define __NR_PIPE 22
%define __NR_SELECT 23
%define __NR_SCHED_YIELD 24
%define __NR_MREMAP 25
%define __NR_MSYNC 26
%define __NR_MINCORE 27
%define __NR_MADVISE 28
%define __NR_SHMGET 29
%define __NR_SHMAT 30
%define __NR_SHMCTL 31
%define __NR_DUP 32
%define __NR_DUP2 33
%define __NR_PAUSE 34
%define __NR_NANOSLEEP 35
%define __NR_GETITIMER 36
%define __NR_ALARM 37
%define __NR_SETITIMER 38
%define __NR_GETPID 39
%define __NR_SENDFILE 40
%define __NR_SOCKET 41
%define __NR_CONNECT 42
%define __NR_ACCEPT 43
%define __NR_SENDTO 44
%define __NR_RECVFROM 45
%define __NR_SENDMSG 46
%define __NR_RECVMSG 47
%define __NR_SHUTDOWN 48
%define __NR_BIND 49
%define __NR_LISTEN 50
%define __NR_GETSOCKNAME 51
%define __NR_GETPEERNAME 52
%define __NR_SOCKETPAIR 53
%define __NR_SETSOCKOPT 54
%define __NR_GETSOCKOPT 55
%define __NR_CLONE 56
%define __NR_FORK 57
%define __NR_VFORK 58
%define __NR_EXECVE 59
%define __NR_EXIT 60
%define __NR_WAIT4 61
%define __NR_KILL 62
%define __NR_UNAME 63
%define __NR_SEMGET 64
%define __NR_SEMOP 65
%define __NR_SEMCTL 66
%define __NR_SHMDT 67
%define __NR_MSGGET 68
%define __NR_MSGSND 69
%define __NR_MSGRCV 70
%define __NR_MSGCTL 71
%define __NR_FCNTL 72
%define __NR_FLOCK 73
%define __NR_FSYNC 74
%define __NR_FDATASYNC 75
%define __NR_TRUNCATE 76
%define __NR_FTRUNCATE 77
%define __NR_GETDENTS 78
%define __NR_GETCWD 79
%define __NR_CHDIR 80
%define __NR_FCHDIR 81
%define __NR_RENAME 82
%define __NR_MKDIR 83
%define __NR_RMDIR 84
%define __NR_CREAT 85
%define __NR_LINK 86
%define __NR_UNLINK 87
%define __NR_SYMLINK 88
%define __NR_READLINK 89
%define __NR_CHMOD 90
%define __NR_FCHMOD 91
%define __NR_CHOWN 92
%define __NR_FCHOWN 93
%define __NR_LCHOWN 94
%define __NR_UMASK 95
%define __NR_GETTIMEOFDAY 96
%define __NR_GETRLIMIT 97
%define __NR_GETRUSAGE 98
%define __NR_SYSINFO 99
%define __NR_TIMES 100
%define __NR_PTRACE 101
%define __NR_GETUID 102
%define __NR_SYSLOG 103
%define __NR_GETGID 104
%define __NR_SETUID 105
%define __NR_SETGID 106
%define __NR_GETEUID 107
%define __NR_GETEGID 108
%define __NR_SETPGID 109
%define __NR_GETPPID 110
%define __NR_GETPGRP 111
%define __NR_SETSID 112
%define __NR_SETREUID 113
%define __NR_SETREGID 114
%define __NR_GETGROUPS 115
%define __NR_SETGROUPS 116
%define __NR_SETRESUID 117
%define __NR_GETRESUID 118
%define __NR_SETRESGID 119
%define __NR_GETRESGID 120
%define __NR_GETPGID 121
%define __NR_SETFSUID 122
%define __NR_SETFSGID 123
%define __NR_GETSID 124
%define __NR_CAPGET 125
%define __NR_CAPSET 126
%define __NR_RT_SIGPENDING 127
%define __NR_RT_SIGTIMEDWAIT 128
%define __NR_RT_SIGQUEUEINFO 129
%define __NR_RT_SIGSUSPEND 130
%define __NR_SIGALTSTACK 131
%define __NR_UTIME 132
%define __NR_MKNOD 133
%define __NR_USELIB 134
%define __NR_PERSONALITY 135
%define __NR_USTAT 136
%define __NR_STATFS 137
%define __NR_FSTATFS 138
%define __NR_SYSFS 139
%define __NR_GETPRIORITY 140
%define __NR_SETPRIORITY 141
%define __NR_SCHED_SETPARAM 142
%define __NR_SCHED_GETPARAM 143
%define __NR_SCHED_SETSCHEDULER 144
%define __NR_SCHED_GETSCHEDULER 145
%define __NR_SCHED_GET_PRIORITY_MAX 146
%define __NR_SCHED_GET_PRIORITY_MIN 147
%define __NR_SCHED_RR_GET_INTERVAL 148
%define __NR_MLOCK 149
%define __NR_MUNLOCK 150
%define __NR_MLOCKALL 151
%define __NR_MUNLOCKALL 152
%define __NR_VHANGUP 153
%define __NR_MODIFY_LDT 154
%define __NR_PIVOT_ROOT 155
%define __NR__SYSCTL 156
%define __NR_PRCTL 157
%define __NR_ARCH_PRCTL 158
%define __NR_ADJTIMEX 159
%define __NR_SETRLIMIT 160
%define __NR_CHROOT 161
%define __NR_SYNC 162
%define __NR_ACCT 163
%define __NR_SETTIMEOFDAY 164
%define __NR_MOUNT 165
%define __NR_UMOUNT2 166
%define __NR_SWAPON 167
%define __NR_SWAPOFF 168
%define __NR_REBOOT 169
%define __NR_SETHOSTNAME 170
%define __NR_SETDOMAINNAME 171
%define __NR_IOPL 172
%define __NR_IOPERM 173
%define __NR_CREATE_MODULE 174
%define __NR_INIT_MODULE 175
%define __NR_DELETE_MODULE 176
%define __NR_GET_KERNEL_SYMS 177
%define __NR_QUERY_MODULE 178
%define __NR_QUOTACTL 179
%define __NR_NFSSERVCTL 180
%define __NR_GETPMSG 181
%define __NR_PUTPMSG 182
%define __NR_AFS_SYSCALL 183
%define __NR_TUXCALL 184
%define __NR_SECURITY 185
%define __NR_GETTID 186
%define __NR_READAHEAD 187
%define __NR_SETXATTR 188
%define __NR_LSETXATTR 189
%define __NR_FSETXATTR 190
%define __NR_GETXATTR 191
%define __NR_LGETXATTR 192
%define __NR_FGETXATTR 193
%define __NR_LISTXATTR 194
%define __NR_LLISTXATTR 195
%define __NR_FLISTXATTR 196
%define __NR_REMOVEXATTR 197
%define __NR_LREMOVEXATTR 198
%define __NR_FREMOVEXATTR 199
%define __NR_TKILL 200
%define __NR_TIME 201
%define __NR_FUTEX 202
%define __NR_SCHED_SETAFFINITY 203
%define __NR_SCHED_GETAFFINITY 204
%define __NR_SET_THREAD_AREA 205
%define __NR_IO_SETUP 206
%define __NR_IO_DESTROY 207
%define __NR_IO_GETEVENTS 208
%define __NR_IO_SUBMIT 209
%define __NR_IO_CANCEL 210
%define __NR_GET_THREAD_AREA 211
%define __NR_LOOKUP_DCOOKIE 212
%define __NR_EPOLL_CREATE 213
%define __NR_EPOLL_CTL_OLD 214
%define __NR_EPOLL_WAIT_OLD 215
%define __NR_REMAP_FILE_PAGES 216
%define __NR_GETDENTS64 217
%define __NR_SET_TID_ADDRESS 218
%define __NR_RESTART_SYSCALL 219
%define __NR_SEMTIMEDOP 220
%define __NR_FADVISE64 221
%define __NR_TIMER_CREATE 222
%define __NR_TIMER_SETTIME 223
%define __NR_TIMER_GETTIME 224
%define __NR_TIMER_GETOVERRUN 225
%define __NR_TIMER_DELETE 226
%define __NR_CLOCK_SETTIME 227
%define __NR_CLOCK_GETTIME 228
%define __NR_CLOCK_GETRES 229
%define __NR_CLOCK_NANOSLEEP 230
%define __NR_EXIT_GROUP 231
%define __NR_EPOLL_WAIT 232
%define __NR_EPOLL_CTL 233
%define __NR_TGKILL 234
%define __NR_UTIMES 235
%define __NR_VSERVER 236
%define __NR_MBIND 237
%define __NR_SET_MEMPOLICY 238
%define __NR_GET_MEMPOLICY 239
%define __NR_MQ_OPEN 240
%define __NR_MQ_UNLINK 241
%define __NR_MQ_TIMEDSEND 242
%define __NR_MQ_TIMEDRECEIVE 243
%define __NR_MQ_NOTIFY 244
%define __NR_MQ_GETSETATTR 245
%define __NR_KEXEC_LOAD 246
%define __NR_WAITID 247
%define __NR_ADD_KEY 248
%define __NR_REQUEST_KEY 249
%define __NR_KEYCTL 250
%define __NR_IOPRIO_SET 251
%define __NR_IOPRIO_GET 252
%define __NR_INOTIFY_INIT 253
%define __NR_INOTIFY_ADD_WATCH 254
%define __NR_INOTIFY_RM_WATCH 255
%define __NR_MIGRATE_PAGES 256
%define __NR_OPENAT 257
%define __NR_MKDIRAT 258
%define __NR_MKNODAT 259
%define __NR_FCHOWNAT 260
%define __NR_FUTIMESAT 261
%define __NR_NEWFSTATAT 262
%define __NR_UNLINKAT 263
%define __NR_RENAMEAT 264
%define __NR_LINKAT 265
%define __NR_SYMLINKAT 266
%define __NR_READLINKAT 267
%define __NR_FCHMODAT 268
%define __NR_FACCESSAT 269
%define __NR_PSELECT6 270
%define __NR_PPOLL 271
%define __NR_UNSHARE 272
%define __NR_SET_ROBUST_LIST 273
%define __NR_GET_ROBUST_LIST 274
%define __NR_SPLICE 275
%define __NR_TEE 276
%define __NR_SYNC_FILE_RANGE 277
%define __NR_VMSPLICE 278
%define __NR_MOVE_PAGES 279
%define __NR_UTIMENSAT 280
%define __NR_EPOLL_PWAIT 281
%define __NR_SIGNALFD 282
%define __NR_TIMERFD_CREATE 283
%define __NR_EVENTFD 284
%define __NR_FALLOCATE 285
%define __NR_TIMERFD_SETTIME 286
%define __NR_TIMERFD_GETTIME 287
%define __NR_ACCEPT4 288
%define __NR_SIGNALFD4 289
%define __NR_EVENTFD2 290
%define __NR_EPOLL_CREATE1 291
%define __NR_DUP3 292
%define __NR_PIPE2 293
%define __NR_INOTIFY_INIT1 294
%define __NR_PREADV 295
%define __NR_PWRITEV 296
%define __NR_RT_TGSIGQUEUEINFO 297
%define __NR_PERF_EVENT_OPEN 298
%define __NR_RECVMMSG 299
%define __NR_FANOTIFY_INIT 300
%define __NR_FANOTIFY_MARK 301
%define __NR_PRLIMIT64 302
%define __NR_NAME_TO_HANDLE_AT 303
%define __NR_OPEN_BY_HANDLE_AT 304
%define __NR_CLOCK_ADJTIME 305
%define __NR_SYNCFS 306
%define __NR_SENDMMSG 307
%define __NR_SETNS 308
%define __NR_GETCPU 309
%define __NR_PROCESS_VM_READV 310
%define __NR_PROCESS_VM_WRITEV 311
%define __NR_KCMP 312
%define __NR_FINIT_MODULE 313
%define __NR_SCHED_SETATTR 314
%define __NR_SCHED_GETATTR 315
%define __NR_RENAMEAT2 316
%define __NR_SECCOMP 317
%define __NR_GETRANDOM 318
%define __NR_MEMFD_CREATE 319
%define __NR_KEXEC_FILE_LOAD 320
%define __NR_BPF 321
%define __NR_EXECVEAT 322
%define __NR_USERFAULTFD 323
%define __NR_MEMBARRIER 324
%define __NR_MLOCK2 325
%define __NR_COPY_FILE_RANGE 326
%define __NR_PREADV2 327
%define __NR_PWRITEV2 328
%define __NR_PKEY_MPROTECT 329
%define __NR_PKEY_ALLOC 330
%define __NR_PKEY_FREE 331
%define __NR_STATX 332
%define __NR_IO_PGETEVENTS 333
%define __NR_RSEQ 334
%define __NR_PIDFD_SEND_SIGNAL 424
%define __NR_IO_URING_SETUP 425
%define __NR_IO_URING_ENTER 426
%define __NR_IO_URING_REGISTER 427
%define __NR_OPEN_TREE 428
%define __NR_MOVE_MOUNT 429
%define __NR_FSOPEN 430
%define __NR_FSCONFIG 431
%define __NR_FSMOUNT 432
%define __NR_FSPICK 433
%define __NR_PIDFD_OPEN 434
%define __NR_CLONE3 435
%define __NR_CLOSE_RANGE 436
%define __NR_OPENAT2 437
%define __NR_PIDFD_GETFD 438
%define __NR_FACCESSAT2 439
%define __NR_PROCESS_MADVISE 440
%define __NR_EPOLL_PWAIT2 441
%define __NR_MOUNT_SETATTR 442
%define __NR_QUOTACTL_FD 443
%define __NR_LANDLOCK_CREATE_RULESET 444
%define __NR_LANDLOCK_ADD_RULE 445
%define __NR_LANDLOCK_RESTRICT_SELF 446
%define __NR_MEMFD_SECRET 447
%define __NR_PROCESS_MRELEASE 448
%define __NR_FUTEX_WAITV 449
%define __NR_SET_MEMPOLICY_HOME_NODE 450
%define __NR_CACHESTAT 451
%define __NR_FCHMODAT2 452
%define __NR_MAP_SHADOW_STACK 453
