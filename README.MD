# Heartbeat / KeepAlive Project

This project implements a **TCP-based keepalive system** in C, designed to monitor client connections in real time. The server can accept multiple clients, track them via UUID, and optionally send notifications through a Telegram bot when a client disconnects or a timeout occurs.

---

## Features

- **TCP Server & Clients**
    - Accepts multiple clients simultaneously.
    - Each client is identified by a unique UUID.
    - Handles client connections in separate threads.

- **Heartbeat / Keepalive**
    - Clients periodically send heartbeat packets to the server.
    - Server detects disconnections or timeouts.
    - Timeout handling with notifications.

- **Telegram Notifications**
    - Optionally send messages via a Telegram bot.
    - Alerts when clients disconnect unexpectedly.

- **Cross-platform (Windows/Linux)**
    - Uses pthreads on Linux.
    - Uses WinAPI threads or pthread via MinGW on Windows.
    - Handles platform-specific socket and threading differences.

---

## Requirements

- **C Compiler**
    - GCC / MinGW for Windows
    - GCC / Clang for Linux
- **CMake** for building the project
- **Windows only**
    - WinHTTP library (`-lwinhttp`) for Telegram notifications
- **Linux only**
    - pthread library (`-lpthread`) for multithreading

---

## Building the Project

### Linux

```bash
mkdir build
cd build
cmake ..
make
