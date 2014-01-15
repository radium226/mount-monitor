#include <stdio.h>
#include <stdlib.h>

#include "mount-poll.h"

MountPoll *mount_poll_create()
{
    MountPoll *mount_poll = __mount_poll_alloc();
    mount_poll -> poll = poll_create(MOUNTS);
    return mount_poll;
}

void mount_poll_destroy(MountPoll *mount_poll)
{
    poll_destroy(mount_poll -> poll);
    __mount_poll_free(mount_poll);
}

MountPoll *__mount_poll_alloc()
{
    MountPoll *mount_poll = (MountPoll *)malloc(sizeof(MountPoll));
    return mount_poll;
}

void __mount_poll_free(MountPoll *mount_poll)
{
    free(mount_poll);
}

void mount_poll_loop(MountPoll *mount_poll, void (* mount_diff_handler)(MountDiff *))
{
    Poll *poll = mount_poll -> poll;
    MountList *mount_list = mount_list_retreive(MOUNTS);
    MountPollHandlerUserData *user_data = mount_poll_handler_user_data_create(mount_list, MOUNTS, mount_diff_handler);
    poll_loop(poll, mount_poll_handle_poll_event, user_data);
    
}

MountPollHandlerUserData *__mount_poll_handler_user_data_alloc()
{
    MountPollHandlerUserData *user_data = (MountPollHandlerUserData *)malloc(sizeof(MountPollHandlerUserData));
    return user_data;
}

void __mount_poll_handler_user_data_free(MountPollHandlerUserData* user_data)
{
    free(user_data);
}

MountPollHandlerUserData *mount_poll_handler_user_data_create(MountList *last_mount_list, char *mounts_file_path, void (* handler)(MountDiff *))
{
    MountPollHandlerUserData *user_data = __mount_poll_handler_user_data_alloc();
    
    user_data -> mounts_file_path = mounts_file_path;
    user_data -> last_mount_list = last_mount_list;
    user_data -> handler = handler;
    
    return user_data;
}

void mount_poll_handler_user_data_destroy(MountPollHandlerUserData* user_data)
{
    __mount_poll_handler_user_data_free(user_data);
}

void mount_poll_handle_poll_event(PollEvent *poll_event, void *user_data)
{
    MountPollHandlerUserData *mount_poll_handler_user_data = (MountPollHandlerUserData *) user_data;
    
    MountList *current_mount_list = mount_list_retreive(MOUNTS);
    MountDiff *mount_diff = mount_list_diff(mount_poll_handler_user_data -> last_mount_list, current_mount_list);
    mount_poll_handler_user_data -> last_mount_list = current_mount_list;
    mount_poll_handler_user_data -> handler(mount_diff);
    
    /*stat *file_stat = (stat *) malloc(sizeof(stat));
    stat(mount_diff -> mount -> directory_path, file_stat);
    
    __uidfile_stat -> st_uid
    
    char line[MAXLINE];
    
    FILE *file = popen("../Echo.sh", "r");
    while (fgets(line, MAXLINE, file) != NULL) {
        if (fputs(line, stdout) == EOF)
            printf("!!!\n");
    }
    pclose(file); */
}