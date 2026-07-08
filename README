# xv6 Operating System

A modern reimplementation of the classic Unix v6 operating system for educational purposes. This project provides a complete, working operating system kernel with user-space programs, designed to help understand operating system concepts.

## Overview

xv6 is a teaching operating system developed at MIT, reimplementing Unix v6 (circa 1975) for modern hardware. This implementation targets RISC-V architecture and includes:

- **Kernel**: Complete operating system kernel with process management, memory management, file system, and device drivers
- **User Programs**: A collection of user-space utilities and programs
- **System Calls**: Implementation of essential Unix system calls
- **File System**: Simple but functional file system with inodes and directories

## Project Structure

```
SYS_extensions/
├── kernel/           # Operating system kernel source code
│   ├── main.c       # Kernel entry point and initialization
│   ├── proc.c       # Process management
│   ├── vm.c         # Virtual memory management
│   ├── fs.c         # File system implementation
│   ├── syscall.c    # System call handling
│   └── ...          # Other kernel components
├── user/            # User-space programs
│   ├── init.c       # Initial user process
│   ├── sh.c         # Shell implementation
│   ├── cat.c        # File concatenation utility
│   ├── ls.c         # Directory listing utility
│   ├── grep.c       # Text search utility
│   └── ...          # Other user programs
└── README.md        # This file
```

## Key Features

### Kernel Features
- **Process Management**: Support for up to 64 concurrent processes
- **Memory Management**: Virtual memory with paging
- **File System**: Inode-based file system with directories
- **Device Drivers**: Console, disk, and interrupt controller support
- **System Calls**: Complete Unix-like system call interface
- **Multi-core Support**: SMP (Symmetric Multi-Processing) support for up to 8 CPUs

### User Programs
- **Shell**: Interactive command-line interface (`sh`)
- **File Utilities**: `cat`, `ls`, `grep`, `wc`, `rm`, `mkdir`, `ln`
- **System Utilities**: `echo`, `kill`, `printf`
- **Testing Programs**: `forktest`, `stressfs`, `grind`, `usertests`
- **Memory Testing**: `shmem_test`, `log_test`

### System Parameters
- Maximum processes: 64
- Maximum CPUs: 8
- File system size: 2000 blocks
- Maximum file path length: 128 characters
- Open files per process: 16

## Building and Running

### Prerequisites
- RISC-V toolchain (GCC, binutils)
- QEMU for RISC-V emulation
- Make build system

### Build Instructions
```bash
# Build the kernel and user programs
make

# Run xv6 in QEMU
make qemu

# Run with debugging
make qemu-gdb
```

### Running User Programs
Once xv6 is running, you can use the shell to execute various commands:

```bash
# List files in current directory
ls

# Display file contents
cat filename

# Search for text in files
grep pattern filename

# Count words in a file
wc filename

# Create a directory
mkdir dirname

# Remove a file
rm filename
```

## System Architecture

### Kernel Architecture
The kernel is organized into several key subsystems:

1. **Process Management** (`proc.c`): Handles process creation, scheduling, and termination
2. **Memory Management** (`vm.c`): Manages virtual memory, page tables, and memory allocation
3. **File System** (`fs.c`): Implements the file system with inodes, directories, and file operations
4. **System Calls** (`syscall.c`): Dispatches and handles system call requests from user programs
5. **Device Drivers**: Console I/O, disk I/O, and interrupt handling

### User-Space Architecture
User programs are built with:
- **User Library** (`ulib.c`): Common utility functions
- **Memory Allocation** (`umalloc.c`): User-space memory management
- **System Call Interface**: Access to kernel services

## Development and Testing

### Testing
The project includes comprehensive testing:
- **Unit Tests**: Individual program tests
- **System Tests**: `usertests.c` for comprehensive system testing
- **Stress Tests**: `stressfs.c` and `grind.c` for performance testing

### Debugging
- Use `make qemu-gdb` for kernel debugging
- Built-in printf debugging in kernel and user programs
- Memory and process state inspection capabilities

## Educational Value

This xv6 implementation is excellent for learning:
- Operating system design principles
- Process management and scheduling
- Memory management and virtual memory
- File system design and implementation
- System call interface design
- Device driver development
- Concurrent programming and synchronization

## Contributing

This is an educational project. Feel free to:
- Experiment with kernel modifications
- Add new system calls
- Implement additional user programs
- Improve documentation
- Fix bugs or add features

## License

This project is based on the MIT xv6 teaching operating system and is intended for educational purposes.

## References

- Original xv6: https://pdos.csail.mit.edu/6.828/2020/xv6.html
- RISC-V Architecture: https://riscv.org/
- Unix v6: The original Unix operating system from Bell Labs

