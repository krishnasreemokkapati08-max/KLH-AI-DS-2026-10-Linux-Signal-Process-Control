# IPC-CHAT
## Inter-Process Chat Application Using IPC

### Project Overview
IPC-CHAT is a simple, two-way chat application developed in C using Inter-Process Communication (IPC) in Linux. It uses named pipes (FIFOs) to exchange messages between two chat participants.

### Objectives
- Demonstrate inter-process communication in Linux.
- Enable two-way message exchange between two terminal instances.
- Understand named pipes, process creation, and system calls in C.

### Technologies Used
- **Programming Language:** C
- **Operating System:** Ubuntu Linux
- **IPC Mechanism:** Named Pipes (FIFOs)
- **System Calls:** `fork()`, `open()`, `read()`, `write()`, `close()`, and `wait()`
- **Compiler:** GCC

### Project Structure
```text
IPC-CHAT/
├── chat.c
├── README.md
└── Makefile
```

### Prerequisites
- Ubuntu or another Linux distribution
- GCC compiler
- Build tools

Install the compiler if needed:

```bash
sudo apt update
sudo apt install build-essential
```

### Compilation
Compile the source code using:

```bash
gcc -Wall -Wextra -std=c11 chat.c -o chat
```

### Execution
Open two separate terminal windows and navigate to the directory containing `chat.c`.

**Terminal 1:**
```bash
./chat A
```

**Terminal 2:**
```bash
./chat B
```

The participants can exchange messages in both directions. Follow the exit command implemented in the source code to terminate the chat.

### Working Principle
1. The application creates named pipes for communication.
2. Each participant starts a process for receiving messages.
3. Messages are transferred between the participants using FIFO-based IPC.
4. The program uses Linux system calls to read and write messages.

### Testing
The prototype was tested on Ubuntu Linux with two terminal instances. Two-way message delivery was verified.

### Limitations
- The prototype is designed for two participants.
- Both participants need access to the same Linux system.
- The application is intended for educational demonstration and does not provide message encryption.

### Conclusion
IPC-CHAT demonstrates how Linux processes can communicate using named pipes. It provides a practical introduction to operating-system concepts such as process creation, file descriptors, and inter-process communication.

### Author
Developed as an Operating Systems hackathon project.
