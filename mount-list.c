#include <stdio.h>
#include <stdlib.h>
#include <mntent.h>

#include "mount-list.h"

int mount_list_size(MountList *mount_list) {
    int size = -1;
    for (size = 0; mount_list -> mounts[size] != NULL; size++);
    return size;
}

MountList *mount_list_new()
{
    MountList *mount_list = (MountList *)malloc(sizeof(MountList));
    int index = -1;
    for (index = 0; index < MAX_SIZE; index++) {
        mount_list -> mounts[index] = NULL;
    }
    return mount_list;
}

int mount_list_contains(MountList *mount_list, Mount *mount)
{
    int contains = 0;
    int size = mount_list_size(mount_list);
    int index = -1; 
    for (index = 0; index < size; index++) {
        Mount *current_mount = mount_list_get(mount_list, index);
        if (mount_are_equal(mount, current_mount)) {
            contains = 1;
            break;
        }
    }
    
    return contains;
    
}

void mount_list_add(MountList *mount_list, Mount *mount) {
    int index = mount_list_size(mount_list);
    mount_list -> mounts[index] = mount;
}

Mount *mount_list_get(MountList *mount_list, int index) {
    Mount *mount = mount_list -> mounts[index];
    return mount;
}

void mount_list_print(MountList *mount_list) {
    int size = mount_list_size(mount_list);
    int index = -1; 
    for (index = 0; index < size; index++) {
        Mount *mount = mount_list_get(mount_list, index);
        mount_print(mount);
    }
}

MountDiff *mount_list_diff(MountList *old_mount_list, MountList *new_mount_list) {
    if (old_mount_list == NULL || new_mount_list == NULL) return NULL;
    
    int old_size = mount_list_size(old_mount_list);
    int new_size = mount_list_size(new_mount_list);
    int index = -1;
    
    MountDiff *mount_diff = NULL;
    
    for (index = 0; index < old_size; index++) {
        Mount *old_mount = mount_list_get(old_mount_list, index);
        if (!mount_list_contains(new_mount_list, old_mount)) {
            mount_diff = mount_diff_new(old_mount, MOUNT_DIFF_REMOVED);
        }
    }
    
    for (index = 0; index < new_size; index++) {
        Mount *new_mount = mount_list_get(new_mount_list, index);
        if (!mount_list_contains(old_mount_list, new_mount)) {
            mount_diff = mount_diff_new(new_mount, MOUNT_DIFF_ADDED);
        }
    }
    
    return mount_diff;
}

MountList *mount_list_retreive(char *mounts_file_path)
{
    MountList *mount_list = mount_list_new();
    if (mounts_file_path == NULL) {
        mounts_file_path = MOUNTS;
    }
    
    FILE *mounts_file = setmntent(mounts_file_path, "r");
    struct mntent *mount_entry = NULL;
    while (1) {
        mount_entry = getmntent(mounts_file);
        if (mount_entry == NULL) {
            break;
        }
        
        Mount *mount = mount_new(mount_entry -> mnt_fsname, mount_entry -> mnt_dir);
        mount_list_add(mount_list, mount);
    }
    endmntent(mounts_file);    
    return mount_list;
}