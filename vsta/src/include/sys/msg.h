#ifndef _MSG_H
#define _MSG_H
/*
 * msg.h
 *	Data structures for exchanging messages
 */
#include <sys/types.h>
#include <sys/seg.h>
#include <sys/param.h>

/*
 * Format of message descriptor
 */
typedef
struct msg {
	long m_sender;		/* Index # of sender */
	int m_op;		/* Operation requested */
	long m_arg,		/*  ...a single argument */
		m_arg1;		/*  ...I know, I know! */
	seg_t m_seg[MSGSEGS];	/* Segments received */
	int m_nseg;		/*  ...number of entries valid */
} msg_t;

#ifndef KERNEL
/*
 * Many of the simpler, non-critical code paths prefer to ignore the
 * scatter/gather possibilities of m_seg[].  For them many servers
 * will gather the data into a single linear buffer.  This is then
 * hung off of the first slot in m_seg[].
 */
#define m_buf m_seg[0].s_buf
#define m_buflen m_seg[0].s_buflen
#endif

#ifdef KERNEL
/*
 * Version of msg when inside the kernel.
 */
#include <sys/mutex.h>

/*
 * The sysmsg_seg and sysmsg_err structures are only used to let
 * the compiler generate efficient assignment code
 */
struct sysmsg_seg {
	struct seg *sm_seg[MSGSEGS];
};

struct sysmsg_err {
	char sm_err[ERRLEN];
};

struct sysmsg {
	msg_t sm_msg;
#define sm_op sm_msg.m_op
#define sm_arg sm_msg.m_arg
#define sm_arg1 sm_msg.m_arg1
	struct portref *sm_sender;	/* Client associated with msg */
	int sm_nseg;			/* Segments: count & base/len */
	struct sysmsg_seg sm_segs;
#define sm_seg sm_segs.sm_seg
	struct sysmsg *sm_next;		/* For building a queue of msgs */
	struct sysmsg_err sm_errs;	/* Error returned for op */
#define sm_err sm_errs.sm_err
};

/*
 * This is in seg.c, but its arguments are defined here
 */
extern int copyoutsegs(struct sysmsg *);

#endif /* KERNEL */

port_t msg_port(port_name, port_name *); /* Create new port */
port_t msg_connect(port_name, int);	/* Connect to port */
int msg_accept(long);			/* Accept M_CONNECT */
int msg_send(port_t, msg_t *);		/* Send message to port */
int msg_receive(port_t, msg_t *);	/* Receive message on port */
int msg_reply(long, msg_t *);		/* Reply to message received */
int msg_disconnect(port_t);		/* All done with port */
#ifdef KERNEL
int msg_err(long, char *, int);		/* Request had error */
#else
int msg_err(long, char *);		/* Stub does the strlen() */
#endif
int msg_portname(port_t);		/* Get port_name for port */

/*
 * Extended descriptions for routines
 */

/*
 * M_RESVD and below have special kernel meanings.
 *
 * msg_send() returns 0 for success, -1 for error, or a number greater
 *  than 0 for the case of M_DUP (see below).
 * msg_receive() returns the total number of bytes received.  If m_buf
 *  is non-zero in length, that many bytes will be copied into your
 *  address space.  The remainder are available as segments in m_seg[].
 * In general, routines not otherwise specified return 0 on success,
 *  -1 on error.
 *
 * M_DUP will
 *  arrange for the filesystem to be able to associate a new
 *  file descriptor with an open.  The server receives the old m_sender;
 *  a non-error reply on the original port causes the new port
 *  indicated in m_arg to become an active connection to the server.
 *  A error reply means that m_arg's port will not become valid.
 *
 * The first buffer of data can be pointed to by m_buf, whose length
 *  is put in m_buflen.  For scatter/gather, segments must be created
 *  using the segment manipulation routines.  Since a segment can be
 *  created once and used many times, the overhead of getting the segment
 *  handle should amortize well.
 *
 * M_DISCONNECT sends a message to the server, and waits for the
 *  server to reply.
 *
 * M_ABORT is generated by the kernel on interrupted operations.
 *  Further operations on the port will sleep until the server
 *  turns around the abort.  As operations are blocking, and a port
 *  can not be used while busy, there's no way to send this yourself.
 *
 * M_READ reflects my (perhaps questionable) desire to use a single
 *  type of message structure.  If the client provides an m_buf,
 *  does the server receive it?  M_READ is a modifier bit which,
 *  if set, indicates NO.  It means instead that the server's response
 *  should be placed in the supplied buffer.
 *
 *  On further reflection, the real conceptual issue is that a msg_send()
 *  is a client request; the client may either be sending data or receiving
 *  data.  In this sense, msg_send() should be client_request().  The
 *  M_READ states which direction data to the named buffer flows.
 */
#define M_CONNECT 1		/* Someone has connected */
#define M_DISCONNECT 2		/* Someone has disconnected */
#define M_DUP 3			/* Dup of file for fork() */
#define M_ABORT 4		/* Aborted operation (signals, etc.) */
#define M_ISR 5			/* Interrupt happened (IRQ in m_arg) */
#define M_TIME 6		/* Low-level time mark for timer task */
#define M_RESVD 99		/* This and below reserved */

#define M_READ 0x80000000	/* Buffer is destination, not source */

#endif /* _MSG_H */
