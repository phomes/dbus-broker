#pragma once

/*
 * Socket Listener
 */

#include <c-list.h>
#include <c-macro.h>
#include <c-rbtree.h>
#include <stdlib.h>
#include "util/dispatch.h"

typedef struct Bus Bus;
typedef struct DispatchContext DispatchContext;
typedef struct Listener Listener;

enum {
        _LISTENER_E_SUCCESS,

        LISTENER_E_EXISTS,
};

struct Listener {
        Bus *bus;
        int socket_fd;
        DispatchFile socket_file;
        CList peer_list;
        CRBNode bus_node;
        const char path[];
};

struct ListenerRegistry {
        CRBTree listener_tree;
};

int listener_new_with_fd(Listener **listenerp, Bus *bus, const char *path, DispatchContext *dispatcher, int socket_fd);
Listener *listener_free(Listener *free);

C_DEFINE_CLEANUP(Listener *, listener_free);
