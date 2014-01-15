#ifndef MOUNT_DIFF_H
#define	MOUNT_DIFF_H

#include "mount.h"

#define MOUNT_DIFF_ADDED 0
#define MOUNT_DIFF_REMOVED 1

struct MountDiff {
    int type;
    Mount *mount;
};

typedef struct MountDiff MountDiff;

MountDiff *mount_diff_new(Mount *mount, int type);

#endif	/* MOUNT_DIFF_H */

