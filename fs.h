#ifndef FS_H
#define FS_H

#include <stddef.h>

#define MAX_FILES 16
#define MAX_FILE_NAME 32
#define MAX_FILE_SIZE 1024
#define FS_BLOCK_SIZE 512

// Inode structure
typedef struct {
    char name[MAX_FILE_NAME];
    size_t size;
    size_t block_start;
    size_t block_count;
    int in_use;
} Inode;

// File System structure
typedef struct {
    Inode inodes[MAX_FILES];
    char data_blocks[MAX_FILES * MAX_FILE_SIZE];
} FileSystem;

// File System Functions
void fs_init(FileSystem* fs);
int fs_create(FileSystem* fs, const char* name);
int fs_delete(FileSystem* fs, const char* name);
int fs_write(FileSystem* fs, const char* name, const char* data, size_t size);
int fs_read(FileSystem* fs, const char* name, char* buffer, size_t size);
void fs_list(FileSystem* fs);

#endif // FS_H

