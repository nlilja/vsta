/*
 * dirname.c
 *	Print directory name of path
 */
#include <stdio.h>
#include <string.h>

main(int argc, char **argv)
{
	int i;
	char *p;

	/*
	 * Usage
	 */
	if (argc != 2) {
		fprintf(stderr, "Usage is: %s <path>\n", argv[0]);
		return(1);
	}

	/*
	 * Trim path
	 */
	p = strrchr(argv[1], '/');
	if (p) {
		*p = '\0';
	}

	puts(argv[1]);
	return(0);
}
