/*
 * __start()
 *	Do the VSTa-specific stuff to set up argc/argv
 */
#include <sys/types.h>
#include <std.h>
#include <fdl.h>
#include <mnttab.h>

/*
 * __start()
 *	Do some massaging of arguments during C startup
 */
void
__start(int *argcp, char ***argvp, char *a)
{
	char *p, **argv = 0;
	int x, argc = 0, len;
	char *basemem;

	/*
	 * Boot programs get this
	 */
	if (a == 0) {
noargs:
		*argcp = 0;
		*argvp = 0;
		return;
	}
	basemem = a;

	/*
	 * Get count of arguments
	 */
	argc = *(ulong *)a;
	a += sizeof(ulong);
	argv = malloc((argc+1) * sizeof(char *));
	if (argv == 0) {
		goto noargs;
	}

	/*
	 * Walk the argument area.  Copy each string, as we wish
	 * to tear down the shared memory once we're finished.
	 */
	for (x = 0; x < argc; ++x) {
		len = strlen(a)+1;
		argv[x] = malloc(len);
		if (!argv[x]) {
			goto noargs;
		}
		bcopy(a, argv[x], len);
		a += len;
	}
	argv[x] = 0;	/* Traditional */

	/*
	 * Stuff our values back to our caller
	 */
	*argcp = argc;
	*argvp = argv;

	/*
	 * Set command
	 */
	if (p = strrchr(argv[0], '/')) {
		(void)set_cmd(p+1);
	} else {
		(void)set_cmd(argv[0]);
	}

	/*
	 * Restore our fdl state
	 */
	a = __fdl_restore(a);

	/*
	 * Restore mount table
	 */
	a = __mount_restore(a);

	/*
	 * Restore current working directory
	 */
	a = __cwd_restore(a);

	/*
	 * Unmap the argument memory
	 */
	(void)munmap(basemem, a-basemem);
}
