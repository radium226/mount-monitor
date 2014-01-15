#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <poll.h>
#include <mntent.h>
#include <string.h>

#include "poll.h"

Poll *__poll_alloc()
{
    Poll *poll = (Poll *) malloc(sizeof(Poll));
    poll -> directory_path = NULL;
    poll -> pollfd = NULL;
    return poll;
}

Poll *poll_create(char *directory_path)
{
    // We allocate the structure
    Poll *poll = NULL;
    int directory_fd = 0;
    struct pollfd *pollfd;
    
    poll = __poll_alloc();
    
    // We copy the directory path
    poll -> directory_path = (char *) malloc((strlen(directory_path) + 1) * sizeof(char));
    strcpy(poll -> directory_path, directory_path);
    
    directory_fd = open(directory_path, O_RDONLY, 0);
    
    pollfd = (struct pollfd *) malloc(sizeof(struct pollfd));
    pollfd -> fd = directory_fd;
    pollfd -> events = POLLERR | POLLPRI;
    pollfd -> revents = 0;
    
    poll -> pollfd = pollfd;
    
    return poll;
}

void poll_loop(Poll *_poll, void (* poll_event_handler)(PollEvent *poll_event, void *user_data), void *user_data)
{
    int poll_status = -1;
    int short poll_revent;
    PollEvent *poll_event = NULL;
    
    while(1) {
        poll_status = poll(_poll -> pollfd, POLL_NFSDS, POLL_TIMEOUT);
        if (poll_status < 0) {
            break;
        }

        poll_revent = _poll -> pollfd -> revents;
        if (poll_revent & POLLERR) {
            poll_event = poll_event_create(_poll);
            poll_event_handler(poll_event, user_data);
            poll_event_destroy(poll_event);
        }
    }

}

void __poll_free(Poll *poll) 
{
    free(poll);
}

void poll_destroy(Poll *poll)
{
    
    __poll_free(poll);
}

PollEvent *__poll_event_alloc()
{
    PollEvent *poll_event = (PollEvent *) malloc(sizeof(PollEvent));
    return poll_event;
}

void __poll_event_free(PollEvent *poll_event)
{
    free(poll_event);
}

PollEvent *poll_event_create(Poll *poll)
{
    PollEvent *poll_event = __poll_event_alloc();
    poll_event -> poll = poll;
    return poll_event;
}

void poll_event_destroy(PollEvent *poll_event)
{
    __poll_event_free(poll_event);
}