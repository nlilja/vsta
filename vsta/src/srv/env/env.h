#ifndef _ENV_H
#define _ENV_H
/*
 * env.h
 *	Data structures for the environment server
 *
 * The env server provides a hierarchical shared name space.  At
 * the lowest level of the tree are process-private parts of the
 * name space.  Upper levels are shared by successively larger groups
 * of processes.  A name is looked up by starting at the lowest node
 * and searching upward until it is found.
 */
#include <sys/types.h>
#include <sys/perm.h>
#include <sys/param.h>
#include <lib/llist.h>

/*
 * An open file
 */
struct file {
	struct node *f_node;	/* Current node we address */
	struct perm		/* Our abilities */
		f_perms[PROCPERMS];
	int f_nperm;		/*  ...# active */
	off_t f_pos;		/* Position in internal node */
	int f_mode;		/* Abilities WRT current node */
};

/*
 * A string value shared by one or more nodes
 */
struct string {
	uint s_refs;		/* # nodes using */
	char *s_val;		/* String value */
};

/*
 * A node in our name tree
 */
struct node {
	struct prot n_prot;	/* Protection of this node */
	char n_name[NAMESZ];	/* Name of node */
	ushort n_internal;	/* Internal node? */
	struct string *n_val;	/*  ...if not, string value for name */
	struct llist n_elems;	/* Linked list of elements under node */
	uint n_refs;		/* # references to this node */
	struct llist *n_list;	/* Our place in our parent's list */
	struct node *n_up;	/*  ...out parent */
};

/*
 * Some function prototypes
 */
extern void deref_val(struct string *),
	ref_val(struct string *);
extern struct string *alloc_val(char *);

#endif /* _ENV_H */
