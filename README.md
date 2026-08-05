# 🚀 Embedded TCP/IP Multi-threaded File Transfer System

A Linux-based TCP/IP File Transfer System developed in **C** using **POSIX Sockets** and **Pthreads**. The project supports reliable single-file and multi-file transfer, concurrent client handling, transfer progress monitoring, and SHA-256 checksum verification.

---

## 📌 Features

- ✅ TCP Client-Server Communication
- ✅ Two-way Chat Application
- ✅ Single File Transfer
- ✅ Multi-file Transfer
- ✅ Multi-threaded Server (Pthreads)
- ✅ Filename Transfer
- ✅ File Size Transfer
- ✅ Transfer Progress (%)
- ✅ Automatic File Creation
- ✅ Directory Reading (`opendir()`, `readdir()`)
- ✅ SHA-256 Checksum Verification
- ✅ Modular Project Structure
- ✅ Makefile Build System

---

## 🛠 Technologies Used

- C Programming
- Linux
- POSIX Sockets
- TCP/IP
- POSIX Threads (pthread)
- OpenSSL (SHA-256)
- Makefile
- GCC
- File I/O

---

## 📂 Project Structure

```
Embedded-TCP-FileTransfer/
│
├── include/
│   ├── common.h
│   ├── server.h
│   ├── client.h
│   ├── socket_utils.h
│   └── logger.h
│
├── src/
│   ├── server.c
│   ├── client.c
│   └── main.c
│
├── send_files/
│
├── received_files/
│
├── logs/
│
├── obj/
│
├── bin/
│
├── Makefile
│
└── README.md
```

---

# ⚙️ Build

Compile the project

```bash
make
```

Clean object files

```bash
make clean
```

---

# ▶️ Run Server

```bash
./bin/server
```

Output

```
Socket Created
Bind Successful
Listening on Port 9000

Waiting for Clients...
```

---

# ▶️ Run Client

```bash
./bin/client
```

Output

```
Connected to Server
```

---

# 📁 File Transfer Workflow

```
Client

│

├── Send Filename

│

├── Send File Size

│

├── Send SHA-256 Checksum

│

└── Send File Data

        │

        ▼

Server

│

├── Receive Filename

├── Create File

├── Receive File Size

├── Receive File Data

├── Calculate SHA-256

└── Verify File Integrity
```

---

# 📁 Multi-file Transfer

Client automatically reads all files from

```
send_files/
```

using

```c
opendir()

readdir()
```

and transfers them one by one to the server.

Received files are stored inside

```
received_files/
```

---

# 🧵 Multi-threaded Architecture

```
                Server

               socket()

                   │

                bind()

                   │

               listen()

                   │

             while(1)

                   │

               accept()

                   │

          pthread_create()

        ┌─────────┼─────────┐
        │         │         │
    Client 1   Client 2   Client 3
        │         │         │
   Receive    Receive   Receive
     Files      Files      Files
```

Each client is handled by a dedicated thread allowing multiple clients to transfer files concurrently.

---

# 🔒 File Integrity Verification

The project uses **SHA-256** checksum to verify that the received file is identical to the transmitted file.

```
Client SHA256

↓

Send Checksum

↓

Server Generates SHA256

↓

Compare

↓

SUCCESS / FAILED
```

---

# 📈 Project Development Timeline

### Version 1.0

- TCP Server
- TCP Client

### Version 2.0

- Two-way Chat Application

### Version 3.0

- Single File Transfer

### Version 4.0

- Filename Transfer
- File Size Transfer
- Progress Indicator

### Version 5.0

- Multi-file Transfer
- Directory Reading (`opendir()`, `readdir()`)

### Version 6.0

- Multi-threaded Server using POSIX Threads

### Version 7.0

- SHA-256 Checksum Verification

---

# 💻 Linux APIs Used

### Networking

- socket()
- bind()
- listen()
- accept()
- connect()
- send()
- recv()

### Threading

- pthread_create()
- pthread_detach()
- pthread_exit()

### File Handling

- fopen()
- fread()
- fwrite()
- fclose()

### Directory Handling

- opendir()
- readdir()
- closedir()

### Checksum

- SHA256_Init()
- SHA256_Update()
- SHA256_Final()

---

# 🎯 Learning Outcomes

- Linux System Programming
- TCP/IP Socket Programming
- POSIX Thread Programming
- File System Programming
- Multi-threading
- Client-Server Architecture
- Custom File Transfer Protocol
- SHA-256 File Integrity Verification
- Modular Software Design
- Makefile Build Automation

---

# 🚀 Future Improvements

- GitHub Actions CI/CD Pipeline
- Thread-safe Logging using Mutex
- File Compression
- Resume Interrupted Transfer
- SSL/TLS Secure File Transfer
- Transfer Speed Monitoring
- Configuration File Support
- Epoll-based High Performance Server

---

# 👨‍💻 Author

**Gopal**

Embedded Software Engineer

Linux | C | TCP/IP | POSIX Sockets | Embedded Linux | Multithreading

---

## ⭐ If you found this project useful, consider giving it a Star!
