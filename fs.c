#include "fs.h"
#include <stdio.h>
#include <string.h>

// Initialize the file system
void fs_init(FileSystem* fs) {
    for (int i = 0; i < MAX_FILES; i++) {
        fs->inodes[i].in_use = 0;
    }
    memset(fs->data_blocks, 0, sizeof(fs->data_blocks));
}

// Create a new file
int fs_create(FileSystem* fs, const char* name) {
    // Check if a file with the same name exists
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->inodes[i].in_use && strcmp(fs->inodes[i].name, name) == 0) {
            printf("Error: File already exists.\n");
            return -1;
        }
    }

    // Find a free inode
    for (int i = 0; i < MAX_FILES; i++) {
        if (!fs->inodes[i].in_use) {
            fs->inodes[i].in_use = 1;
            strncpy(fs->inodes[i].name, name, MAX_FILE_NAME);
            fs->inodes[i].size = 0;
            fs->inodes[i].block_start = i * MAX_FILE_SIZE;
            fs->inodes[i].block_count = 0;
            printf("File '%s' created successfully.\n", name);
            return 0;
        }
    }

    printf("Error: No free inode available.\n");
    return -1;
}

// Delete a file
int fs_delete(FileSystem* fs, const char* name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->inodes[i].in_use && strcmp(fs->inodes[i].name, name) == 0) {
            fs->inodes[i].in_use = 0;
            memset(&fs->data_blocks[fs->inodes[i].block_start], 0, fs->inodes[i].size);
            printf("File '%s' deleted successfully.\n", name);
            return 0;
        }
    }
    printf("Error: File not found.\n");
    return -1;
}

// Write data to a file
int fs_write(FileSystem* fs, const char* name, const char* data, size_t size) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->inodes[i].in_use && strcmp(fs->inodes[i].name, name) == 0) {
            if (size > MAX_FILE_SIZE) {
                printf("Error: Data exceeds maximum file size.\n");
                return -1;
            }
            strncpy(&fs->data_blocks[fs->inodes[i].block_start], data, size);
            fs->inodes[i].size = size;
            printf("Data written to file '%s' successfully.\n", name);
            return 0;
        }
    }
    printf("Error: File not found.\n");
    return -1;
}

// Read data from a file
int fs_read(FileSystem* fs, const char* name, char* buffer, size_t size) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->inodes[i].in_use && strcmp(fs->inodes[i].name, name) == 0) {
            if (size > fs->inodes[i].size) {
                size = fs->inodes[i].size;
            }
            strncpy(buffer, &fs->data_blocks[fs->inodes[i].block_start], size);
            printf("Data read from file '%s' successfully.\n", name);
            return size;
        }
    }
    printf("Error: File not found.\n");
    return -1;
}

// List all files in the file system
void fs_list(FileSystem* fs) {
    printf("Files in the file system:\n");
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->inodes[i].in_use) {
            printf("- %s (Size: %zu bytes)\n", fs->inodes[i].name, fs->inodes[i].size);
        }
    }
}

