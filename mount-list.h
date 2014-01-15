#ifndef MOUNT_LIST_H
#define	MOUNT_LIST_H

#include "mount.h"
#include "mount-diff.h"

#define MAX_SIZE 100

struct MountList {
    
    Mount *mounts[MAX_SIZE];
    
};

typedef struct MountList MountList;

MountList *mount_list_new();

int mount_list_size(MountList *);

void mount_list_add(MountList *, Mount *);

Mount *mount_list_get(MountList *, int);

void mount_list_print(MountList *);

int mount_list_contains(MountList *, Mount *);

MountDiff *mount_list_diff(MountList *old_mount_list, MountList *);

MountList *mount_list_retreive(char *);

#endif	/* MOUNT_LIST_H */

