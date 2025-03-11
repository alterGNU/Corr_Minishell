# include <stdio.h>
- readline:
    - `char * readline (const char *prompt);`
- printf:
    - `int printf(const char *format, ...);`
- perror

# include <stdlib.h>
- malloc:
    - `void *malloc(size_t size);`
- free:
    - `void free(void *ptr);`

# include <unistd.h>
- write:
    - `ssize_t write(int fildes, const void *buf, size_t nbyte);`
- access:
    - `int access(const char *path, int amode);`
- read:
    - `ssize_t read(int fildes, void *buf, size_t nbyte);`
- close:
    - `int close(int fildes);`
- fork:
    - `pid_t fork(void);`
- chdir:
    - `int chdir(const char *path);`
    - Change the current working directory, return 0 if ok, -1 if failed.
- the stat structure:
    ```c
	   struct stat {
	       dev_t	 st_dev;	 /* ID of device containing file */
	       ino_t	 st_ino;	 /* Inode number */
	       mode_t	 st_mode;	 /* File type and mode */
	       nlink_t	 st_nlink;	 /* Number of hard links */
	       uid_t	 st_uid;	 /* User ID of owner */
	       gid_t	 st_gid;	 /* Group ID of owner */
	       dev_t	 st_rdev;	 /* Device ID (if special file) */
	       off_t	 st_size;	 /* Total size, in bytes */
	       blksize_t st_blksize;	 /* Block size for filesystem I/O */
	       blkcnt_t	 st_blocks;	 /* Number of 512B blocks allocated */

	       /* Since Linux 2.6, the kernel supports nanosecond
		  precision for the following timestamp fields.
		  For the details before Linux 2.6, see NOTES. */

	       struct timespec st_atim;	 /* Time of last access */
	       struct timespec st_mtim;	 /* Time of last modification */
	       struct timespec st_ctim;	 /* Time of last status change */

	   #define st_atime st_atim.tv_sec	/* Backward compatibility */
	   #define st_mtime st_mtim.tv_sec
	   #define st_ctime st_ctim.tv_sec
	   };
    ```
- stat:
    - `int stat(const char *pathname, struct stat *statbuf);`
    - retrieve information about the file pointed to by **pathname** in the buffer pointed to by **statbuf**
- lstat:
    - `int lstat(const char *pathname, struct stat *statbuf);`
    - Same as stat but if **pathname** is a symbolic link, retrieve information about  the link itself, not
      the file that the link refers to.
- fstat:
    - `int fstat(int fd, struct stat *statbuf);`
    - retrieve information about the file corresponding to the filedescriptor **fd**, in the buffer pointed to by **statbuf**
- dup
- dup2
- pipe
- execve
- getcwd


# include <fcntl.h>
- open
    - `int open(const char *path, int oflag, ...);`

# include <sys/wait.h>
- wait:
    - `pid_t wait(int *stat_loc);`
- waitpid:
    - `pid_t waitpid(pid_t pid, int *stat_loc, int options);`

# include <sys/stat.h>

- add_history
- closedir
- exit
- getenv
- ioctl
- isatty
- kill
- opendir
- readdir
- rl_clear_history
- rl_on_new_line
- rl_redisplay
- rl_replace_line
- sigaction
- sigaddset
- sigemptyset
- signal
- strerror
- tcgetattr
- tcsetattr
- tgetent
- tgetflag
- tgetnum
- tgetstr
- tgoto
- tputs
- ttyname
- ttyslot
- unlink
- wait3
- wait4
