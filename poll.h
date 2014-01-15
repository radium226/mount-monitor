#ifndef POLL_H
#define	POLL_H

#define POLL_NFSDS 1
#define POLL_TIMEOUT 1

struct Poll {
    
    char *directory_path;
    
    struct pollfd *pollfd;
    
};

typedef struct Poll Poll;

struct PollEvent {
    
    Poll *poll;
    
};

typedef struct PollEvent PollEvent;

Poll *poll_create(char *directory);

Poll *__poll_alloc();

void poll_destroy(Poll *poll);

void __poll_free(Poll *poll);

void poll_loop(Poll *poll, void (* handler)(PollEvent *event, void *user_data), void *user_data);

PollEvent *poll_event_create(Poll *poll);

void poll_event_destroy(PollEvent *event);

PollEvent *__poll_event_alloc();

void __poll_event_free(PollEvent *event);

#endif	/* POLL_H */

