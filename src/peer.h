#pragma once

/*
 * Peers
 */

#include <c-macro.h>
#include <c-rbtree.h>
#include <stdlib.h>
#include <sys/types.h>
#include "dispatch.h"

typedef struct Bus Bus;
typedef struct DBusSocket DBusSocket;
typedef struct Peer Peer;
typedef struct UserEntry UserEntry;

struct Peer {
        bool null_byte_done : 1;
        DispatchFile dispatch_file;
        DBusSocket *socket;
        UserEntry *user;
        CRBTree names;
        CRBNode rb;
        uint64_t id;
};

int peer_new(Bus *bus, Peer **peerp, int fd, uid_t uid);
Peer *peer_free(Peer *peer);

int peer_start(Peer *peer);
void peer_stop(Peer *peer);

C_DEFINE_CLEANUP(Peer *, peer_free);