#ifndef MOUNT_POLL_H
#define	MOUNT_POLL_H

#include "poll.h"
#include "mount-list.h"

struct MountPoll {
    Poll *poll;
};

typedef struct MountPoll MountPoll;

MountPoll *mount_poll_create();

void mount_poll_destroy(MountPoll *);

MountPoll *__mount_poll_alloc();

void __mount_poll_free(MountPoll *);

void mount_poll_loop(MountPoll *, void (*)(MountDiff *));

struct MountPollHandlerUserData
{
    char *mounts_file_path;
    MountList *last_mount_list;
    void (* handler)(MountDiff *);
};

typedef struct MountPollHandlerUserData MountPollHandlerUserData;

MountPollHandlerUserData *mount_poll_handler_user_data_create();

void mount_poll_handler_user_data_destroy(MountPollHandlerUserData *user_data);

MountPollHandlerUserData *__mount_poll_handler_user_data_alloc();

void __mount_poll_handler_user_data_free(MountPollHandlerUserData *user_data);

void mount_poll_handle_poll_event(PollEvent *, void *);

#endif	/* MOUNT_POLL_H */

