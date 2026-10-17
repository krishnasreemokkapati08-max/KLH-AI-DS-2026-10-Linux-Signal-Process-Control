# IPC-CHAT: Inter-Process Chat Application Using IPC

## 1. Abstract

IPC-CHAT is a two-way chat application developed in C using Inter-Process Communication (IPC) in Ubuntu Linux. It uses named pipes, also known as FIFOs, to exchange messages between two participants running in separate terminal instances. The project demonstrates fundamental operating-system concepts, including process creation, file operations, and communication between processes.

## 2. Problem Statement

Processes running independently need a mechanism to exchange information. This project addresses that requirement by implementing a simple chat application that allows two participants to send and receive messages using Linux IPC facilities.

## 3. Objectives

- Implement inter-process communication using named pipes.
- Enable two-way message exchange between two participants.
- Understand Linux process management and system calls.
- Demonstrate the practical application of operating-system concepts.

## 4. Technologies Used

- Programming language: C
- Operating system: Ubuntu Linux
- IPC mechanism: Named pipes (FIFOs)
- Compiler: GCC
- System calls and functions: `fork()`, `open()`, `read()`, `write()`, `close()`, and `wait()`

## 5. System Design

The application consists of two participants, A and B. Two named pipes provide separate communication paths: one for messages from A to B and another for messages from B to A.

**Communication flow:**

Participant A → FIFO A-to-B → Participant B

Participant B → FIFO B-to-A → Participant A

Each participant can send messages while a receiving process handles incoming messages.

## 6. Working Methodology

1. The program prepares the named pipes required for communication.
2. The user starts participant A or participant B in a terminal.
3. A child process is created to handle message reception.
4. The main process accepts messages from the keyboard.
5. Messages are written to the appropriate FIFO and read by the other participant.
6. The participants can exchange messages in both directions.
7. The application can be terminated using the exit command implemented in the source code.

## 7. Implementation

The application is implemented in C using Linux system calls and standard library functions. The `fork()` function creates a separate process, while `open()`, `read()`, and `write()` support FIFO-based communication. Named pipes allow data to be exchanged between the two participants.

## 8. Testing and Results

The prototype was tested on Ubuntu Linux using two terminal instances. Both participants were started separately, and message delivery in both directions was verified.

**Observed result:** Successful two-way message exchange between participants A and B.

## 9. Advantages

- Simple and lightweight implementation.
- Demonstrates a practical IPC mechanism.
- Uses standard Linux facilities and the C programming language.
- Helps explain process creation and communication.

## 10. Limitations

- Supports two participants in the current implementation.
- Requires both participants to run on the same Linux system.
- Does not include message encryption or user authentication.
- Robustness under unexpected process termination requires further testing.

## 11. Future Enhancements

- Add support for multiple participants.
- Improve graceful shutdown and error handling.
- Add timestamps and message history.
- Develop a graphical user interface.
- Introduce authentication and secure communication.

## 12. Conclusion

IPC-CHAT demonstrates two-way communication between processes using named pipes in Linux. The project provides hands-on experience with process creation, file descriptors, and IPC mechanisms and can serve as a foundation for more advanced communication applications.

## 13. References

- Linux manual pages: `man 2 fork`, `man 2 open`, `man 2 read`, `man 2 write`, and `man 7 fifo`.
- GNU Compiler Collection documentation.
- Operating Systems course materials.
