#ifndef _STD_H
#define _STD_H
/*
 * std.h
 *	Another standards-driven file, I think
 *
 * See comments for unistd.h
 */
#include <sys/types.h>

/*
 * Routine templates
 */
extern void *malloc(unsigned int), *realloc(void *, unsigned int);
extern void free(void *);
extern char *strdup(char *), *strchr(char *, char), *strrchr(char *, char),
	*index(char *, char), *rindex(char *, char), *strerror(void);
extern int fork(void), tfork(voidfun);
extern int bcopy(void *, void *, unsigned int),
	bcmp(void *, void *, unsigned int);
extern long __cwd_size(void);
extern void __cwd_save(char *);
extern char *__cwd_restore(char *);
extern char *getcwd(char *, int);
extern int dup(int), dup2(int, int);
extern int execl(char *, char *, ...), execv(char *, char **),
	execlp(char *, char *, ...), execvp(char *, char **);
extern char *getenv(char *);
extern int setenv(char *, char *);
extern pid_t getpid(void), gettid(void), getppid(void);

#endif /* _STD_H */
