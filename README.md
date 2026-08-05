# Embedded TCP/IP Multi-threaded File Transfer System

This project is developed in C on Linux using POSIX sockets.

Initially I started with a simple TCP server and client connection. After that I gradually added chat functionality, file transfer, multiple file transfer and finally multi-threading using pthreads.

The purpose of this project was to learn Linux socket programming and understand how client-server communication works.

---

## Features

- TCP Server and Client
- Two-way Chat
- Single File Transfer
- Multiple File Transfer
- Multi-threaded Server (pthread)
- File Name Transfer
- File Size Transfer
- File Transfer Progress
- Automatic File Creation on Server
- Directory Reading using opendir() and readdir()
- SHA-256 Checksum Verification
- Makefile Support

---

## Technologies

- C
- Linux
- POSIX Socket
- TCP/IP
- pthread
- OpenSSL
- GCC
- Makefile

---

## Project Structure

```
Embedded-TCP-FileTransfer

include/
src/
bin/
obj/
send_files/
received_files/
logs/

Makefile
README.md
```

---

## Build

```
make
```

Clean

```
make clean
```

---

## Run

Start Server

```
./bin/server
```

Start Client

```
./bin/client
```

---

## How it Works

Client connects to the server using TCP socket.

Before sending a file, the client sends

- Filename
- File Size
- SHA-256 Checksum

Then the actual file data is transferred.

The server creates a new file, receives all data and verifies the checksum.

---

## Multiple File Transfer

The client reads all files from

```
send_files/
```

using

```
opendir()
readdir()
```

and sends every file one by one.

Received files are stored inside

```
received_files/
```

---

## Multi-threading

The server creates one thread for every connected client.

```
Client 1  ---> Thread 1

Client 2  ---> Thread 2

Client 3  ---> Thread 3
```

This allows multiple clients to transfer files at the same time.

---

## APIs Used

Networking

- socket()
- bind()
- listen()
- accept()
- connect()
- send()
- recv()

Thread

- pthread_create()
- pthread_detach()

Directory

- opendir()
- readdir()

File

- fopen()
- fread()
- fwrite()
- fclose()

---

## What I Learned

While building this project I learned

- TCP/IP Socket Programming
- Client-Server Communication
- POSIX Threads
- File Handling
- Multi-threading
- Linux APIs
- Makefile
- SHA-256 Checksum Verification

---

## Future Work

- GitHub Actions CI
- Better Logging
- SSL/TLS Support
- Resume File Transfer
- Transfer Speed Calculation

---

Developed by

Gopal
