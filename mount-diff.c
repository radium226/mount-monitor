#include <stdio.h>
#include <stdlib.h>

#include "mount-diff.h"
#include "mount.h"


MountDiff *mount_diff_new(Mount *mount, int type) {
    MountDiff *mount_diff = (MountDiff *)malloc(sizeof(MountDiff));
    mount_diff -> mount = mount;
    mount_diff -> type = type;
    return mount_diff;
}

