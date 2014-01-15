#include <stdio.h>
#include <stdlib.h>

#include "mount-poll.h"
#include "text.h"

#include "main.h"

void handle_mount_diff(MountDiff *mount_diff)
{
    char *label = NULL;
    label = NULL;
    
    switch(mount_diff -> type)
    {
        case MOUNT_DIFF_ADDED:
            label = "ADDED";
            break;
        case MOUNT_DIFF_REMOVED:
            label = "REMOVED";
            break;
    }
    
    char *device = mount_diff -> mount -> device;
    printf("%s has been %s\n", text_red(device), text_red(label));
    
}

int main(int argc, char **argv)
{
    
    MountPoll *mount_poll = mount_poll_create();
    mount_poll_loop(mount_poll, handle_mount_diff);
    mount_poll_destroy(mount_poll);
        
    exit(EXIT_SUCCESS);
}