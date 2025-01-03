# FSS
"A Simple File System Simulator". This will be a basic implementation of a file system, allowing you to create, delete, read, and write files within a simulated environment in memory.

# Project Goals
- Learn about file system concepts such as inodes, blocks, and directories.
- Implement basic file operations (create, delete, write, read).
- Simulate a file system in memory for educational purposes.
# Project Plan
## Data Structures:
- Define the core structures like:

  - Superblock: Holds metadata about the file system.
  - Inode: Represents files and directories.
  - Directory Entry: Maps file names to inodes.
  - Data Blocks: Store the actual content of files.

# Features:

- Initialize the file system.
- Create and delete files.
- Write data to a file.
- Read data from a file.
- List files in a directory.

# Code Organization:

  ## main.c: Contains a test interface to demonstrate the file system.
  ## fs.c: Implementation of the file system functions.
  ## fs.h: Header file for declarations.

# Tools Needed:

GCC or any standard C compiler.
