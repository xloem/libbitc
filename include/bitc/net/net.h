#ifndef __LIBBITC_NET_NET_H__
#define __LIBBITC_NET_NET_H__
/* Copyright 2012 exMULTI, Inc.
 * Distributed under the MIT/X11 software license, see the accompanying
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <bitc/buint.h>                // for bu256_t
#include <bitc/clist.h>                // for clist
#include <bitc/message.h>              // for P2P_HDR_SZ, p2p_message
#include <bitc/parr.h>                 // for parr
#include <bitc/primitives/block.h>     // for bitc_block
#include <bitc/net/peerman.h>          // for peer

#include <stdbool.h>                    // for bool
#include <stdint.h>                     // for uint32_t, uint64_t
#include <stdio.h>                      // for FILE
#include <time.h>                       // for pid_t, time_t

#define event_free(EV)				free((EV))
#define event_base_loopbreak(EB)	ev_break((struct ev_loop *)(EB), EVBREAK_ONE)
#define event_new(EB, FD, FL, CB, ARG) \
			({struct event* (EV) = (struct event*)malloc(sizeof(struct event)); \
			event_set((EV), (FD), (FL), (CB), (ARG)); \
			event_base_set((EB), (EV)); (EV);})

#ifdef __cplusplus
extern "C" {
#endif

enum {
	NC_MAX_CONN	= 8,
};

enum netcmds {
	NC_OK,
	NC_ERR,
	NC_TIMEOUT,
	NC_START,
	NC_STOP,
};

struct net_settings *net_settings;

struct net_child_info {
	int			read_fd;
	int			write_fd;

	struct peer_manager	*peers;
	struct chaindb		*db;

	parr			*conns;
	struct event_base	*eb;

	time_t			last_getblocks;
	unsigned int		net_conn_timeout;
	const struct		chain_info *chain;
	uint64_t		*instance_nonce;

	bool			running;

	bool (*inv_block_process)(bu256_t *hash);
	bool (*block_process)(struct bitc_block *block,
                          struct const_buffer *buf);
};

struct nc_conn {
	bool			dead;

	int			fd;

	struct peer		peer;
	char			addr_str[64];

	bool			ipv4;
	bool			connected;
	struct event		*ev;
	struct net_child_info	*nci;

	struct event		*write_ev;
	clist			*write_q;	/* of struct buffer */
	unsigned int		write_partial;

	struct p2p_message	msg;

	void			*msg_p;
	unsigned int		expected;
	bool			reading_hdr;
	unsigned char		hdrbuf[P2P_HDR_SZ];

	bool			seen_version;
	bool			seen_verack;
	uint32_t		protover;
};

struct net_engine {
	bool	running;
	int	rx_pipefd[2];
	int	tx_pipefd[2];
	int	par_read;
	int	par_write;
	pid_t	child;
	void (*network_child_process)(int read_fd, int write_fd);

};

struct net_engine *neteng_new_start(void (*network_child)(int read_fd, int write_fd));

extern void nc_conns_process(struct net_child_info *nci);
extern void nc_conns_gc(struct net_child_info *nci, bool free_all);
extern void nc_pipe_evt(int fd, short events, void *priv);
extern void neteng_free(struct net_engine *neteng);

#ifdef __cplusplus
}
#endif

#endif /* __LIBBITC_NET_NET_H__ */
