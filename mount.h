#ifndef MOUNT_H
#define	MOUNT_H

#define MOUNTS "/proc/mounts"

struct Mount {
    char *directory_path;
    char *device;
};

typedef struct Mount Mount;

Mount *mount_new(char *, char *);

Mount *mount_copy(Mount *);

void mount_print(Mount *);

int mount_are_equal(Mount *, Mount *);

#endif	/* MOUNT_H */

