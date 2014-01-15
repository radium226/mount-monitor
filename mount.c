#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mntent.h>

#include "mount.h"
#include "text.h"

#define MAX_SIZE 100
#define MOUNTS "/proc/mounts"

Mount *mount_new(char *device, char *directory_path)
{
    Mount *mount = (Mount *)malloc(sizeof(Mount));
    mount -> device = text_copy(device);
    mount -> directory_path = text_copy(directory_path);
    return mount;
}

Mount *mount_copy(Mount *mount) {
    return mount_new(mount -> device, mount -> directory_path);
}

void mount_print(Mount *mount)
{
    printf("The device [%s] is mounted to [%s]. \n", mount -> device, mount -> directory_path);
}

int mount_are_equal(Mount *one_mount, Mount *other_mount) {
    //printf("%s --> %s [", one_mount -> directory_path, other_mount -> directory_path);
    if (strcmp(one_mount -> directory_path, other_mount -> directory_path) == 0) {
        //printf("OK\n");
        return 1;
    } else {
        //printf("KO\n");
        return 0;
    }
}

