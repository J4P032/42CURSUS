*This project has been created as part of the 42 curriculum by marcoga2, mvassall, jrollon-.*

# 🌐 ft_irc — IRC Server

An IRC (Internet Relay Chat) server implementation written in **C++98**, following the specifications defined in [RFC 2810](https://www.rfc-editor.org/rfc/rfc2810), [RFC 2811](https://www.rfc-editor.org/rfc/rfc2811), and [RFC 2812](https://www.rfc-editor.org/rfc/rfc2812). The server is designed to handle multiple concurrent clients using non-blocking I/O with the **epoll** event-driven mechanism on Linux.

---

## 📖 Description

**ft_irc** is a 42 school project whose goal is to build a fully functional IRC server from scratch in C++98. The server enables real-time text-based communication between multiple clients through channels and private messages, just like classic IRC networks.

The server accepts connections from any standard IRC client (such as **irssi**, **WeeChat**, **HexChat**, or **netcat**) and implements the core subset of the IRC protocol required for:

- **User authentication** via password, nickname, and username registration.
- **Channel management** including creation, joining, leaving, topic setting, and user listing.
- **Private messaging** between users and to channels.
- **Channel operator privileges** with mode management.
- **Graceful disconnection** and timeout handling.

### Key Highlights

- Single-threaded, event-driven architecture using **`epoll`** for high-performance I/O multiplexing.
- Non-blocking sockets with edge-triggered events.
- Full message parsing compliant with the IRC protocol (prefix, command, parameters).
- Per-client input/output buffering to handle partial reads and writes.
- Client inactivity timeout detection with server-initiated PING/PONG.
- Comprehensive numeric reply codes as specified in RFC 2812.

---

## ✨ Features

### Implemented IRC Commands

| Command | Description |
|---------|-------------|
| `PASS` | Authenticate with the server password |
| `NICK` | Set or change nickname |
| `USER` | Set username and real name during registration |
| `QUIT` | Disconnect from the server |
| `JOIN` | Join one or more channels (with optional key) |
| `PART` | Leave one or more channels |
| `PRIVMSG` | Send a message to a user or channel |
| `NOTICE` | Send a notice (no automatic reply) |
| `TOPIC` | View or set the channel topic |
| `NAMES` | List users in a channel |
| `WHO` | Query information about channel members |
| `MODE` | Query or change channel/user modes |
| `PING` | Client-initiated keepalive |
| `PONG` | Server response to PING |
| `CAP` | Capability negotiation (minimal support) |

### Supported Channel Modes

| Mode | Flag | Description |
|------|------|-------------|
| Invite-only | `+i` | Only invited users can join the channel |
| Topic protection | `+t` | Only channel operators can change the topic |
| Key (password) | `+k` | Requires a password to join the channel |
| User limit | `+l` | Limits the maximum number of users in the channel |
| Operator | `+o` | Grant or revoke channel operator privileges |

### Channel Features

- Channels must start with `#`, `&`, `+`, or `!` (as per RFC 2811).
- Channel names are case-insensitive (stored in lowercase internally).
- Maximum channel name length: 50 characters.
- The first user to join a channel is automatically promoted to **channel operator** (`@`).
- Operators can kick users, set modes, change topics, and manage invitations.

---

## 🏗️ Architecture

### Project Structure

```
irc-server/
├── include/                 # Header files
│   ├── IRCServ.hpp          # Main server class
│   ├── IRCClient.hpp        # Client representation
│   ├── IRCChannel.hpp       # Channel management
│   ├── IRCCommand.hpp       # IRC command/reply code enums
│   ├── IRCMessage.hpp       # IRC message parser
│   └── utils.hpp            # Utility functions
├── src/                     # Source files
│   ├── main.cpp             # Entry point
│   ├── IRCServ.cpp          # Server core (socket, epoll, event loop)
│   ├── IRCClient.cpp        # Client state management
│   ├── IRCChannel.cpp       # Channel logic
│   ├── IRCCommand.cpp       # Command string ↔ enum mapping
│   ├── IRCMessage.cpp       # Message parsing (prefix, command, params)
│   ├── answer_auth.cpp      # PASS, NICK, USER, QUIT handlers
│   ├── answer_join.cpp      # JOIN command handler
│   ├── answer_part.cpp      # PART command handler
│   ├── answer_mode.cpp      # MODE command handler
│   ├── answer_topic.cpp     # TOPIC command handler + broadcastToChannel
│   ├── answer_names.cpp     # NAMES command handler
│   ├── answer_who.cpp       # WHO command handler
│   └── utils.cpp            # Utility function implementations
├── Documentacion/           # Internal documentation & references
│   ├── answer_table.md      # Command behavior reference table
│   └── RFC 2812.html        # Redirect to RFC 2812
├── pcap-files/              # Packet capture files for debugging
├── Makefile                 # Build system
└── README.md                # This file
```

### Core Classes

| Class | Responsibility |
|-------|---------------|
| **`IRCServ`** | Main server: socket creation, epoll event loop, connection management, command dispatching, message sending/broadcasting |
| **`IRCClient`** | Represents a connected client: nickname, username, fullname, host, file descriptor, flags (PASS/NICK/USER/REGISTERED), input/output buffers, channel membership, timeout tracking |
| **`IRCChannel`** | Represents a channel: name, user map with modes (operator/regular), channel modes (invite-only, topic, key, user limit), topic, invited nicks list, creation metadata |
| **`IRCMessage`** | Parses raw IRC protocol strings into structured objects (prefix, command, parameters) following the `:[prefix] COMMAND [params] :[trailing]` format |
| **`IRCCommand`** | Enum of all RFC 2812 commands and numeric reply/error codes, with bidirectional string-to-enum conversion |

### Event Loop Flow

```
1. epoll_wait() blocks until events are ready
2. For each event:
   a. If event on listening_socket → accept_new_connection()
   b. If EPOLLIN on client fd → read_from_client() → process_client_buffer()
      → parse messages → answer_command() for each complete message
   c. If EPOLLOUT on client fd → flush output buffer to socket
3. Check for clients scheduled for removal (graceful cleanup)
4. Repeat
```

---

## 🔧 Instructions

### Prerequisites

- **Operating System**: Linux (required for `epoll`).
- **Compiler**: `c++` (g++ or clang++) with C++98 support.
- **Make**: GNU Make.

### Compilation

Clone the repository and build:

```bash
git clone https://github.com/mvg001/irc-server.git
cd irc-server
make
```

This compiles the project with the following flags:
- `-Wall -Werror -Wextra` — strict warnings
- `-std=c++98 -pedantic` — C++98 standard compliance
- `-g3 -fsanitize=address` — debug symbols and address sanitizer (development mode)

#### Makefile Targets

| Target | Description |
|--------|-------------|
| `make` or `make all` | Build the `ircserv` binary |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and the binary |
| `make re` | Full rebuild (fclean + all) |

### Execution

```bash
./ircserv <port> <password>
```

| Parameter | Description |
|-----------|-------------|
| `port` | The TCP port number the server will listen on (e.g., `6667`) |
| `password` | The connection password clients must provide via `PASS` |

**Example:**

```bash
./ircserv 6667 mypassword
```

### Connecting with an IRC Client

#### Using irssi

```bash
irssi
/connect 127.0.0.1 6667 mypassword
/nick MyNick
```

#### Using netcat (for testing)

```bash
nc 127.0.0.1 6667
PASS mypassword
NICK testuser
USER testuser 0 * :Test User
JOIN #general
PRIVMSG #general :Hello, world!
```

#### Using WeeChat

```bash
weechat
/server add local 127.0.0.1/6667 -password=mypassword
/connect local
```

---

## 💡 Usage Examples

### Creating and Joining a Channel

```
PASS mypassword
NICK alice
USER alice 0 * :Alice Wonderland
JOIN #wonderland
```

### Sending Messages

```
PRIVMSG #wonderland :Hello everyone!
PRIVMSG bob :Hey Bob, private message!
```

### Setting Channel Modes (as Operator)

```
MODE #wonderland +t          # Only operators can change topic
MODE #wonderland +i          # Invite-only channel
MODE #wonderland +k secret   # Set channel password to "secret"
MODE #wonderland +l 10       # Limit channel to 10 users
MODE #wonderland +o bob      # Give operator status to bob
MODE #wonderland -o bob      # Remove operator status from bob
```

### Changing the Topic

```
TOPIC #wonderland :Welcome to Wonderland!
TOPIC #wonderland               # Query current topic
```

---

## 🛠️ Technical Choices

| Decision | Rationale |
|----------|-----------|
| **C++98 standard** | Required by the 42 project subject to ensure compatibility and mastery of classic C++ |
| **`epoll` (Linux)** | Provides efficient, scalable I/O multiplexing for handling many simultaneous connections with `O(1)` event notification |
| **Non-blocking sockets** | Prevents any single client from stalling the entire server; combined with edge-triggered epoll for maximum performance |
| **Single-threaded** | Simplifies state management and avoids concurrency bugs; the event-driven model handles concurrency at the I/O level |
| **Per-client I/O buffers** | Handles partial TCP reads/writes gracefully — messages are accumulated in the input buffer and flushed from the output buffer as the socket becomes writable |
| **`SIGPIPE` ignored** | Prevents the server from crashing when writing to a disconnected client socket; errors are handled in the send logic instead |
| **Client timeout (120s)** | Server sends `PING` to inactive clients and disconnects them if no `PONG` is received, ensuring stale connections are cleaned up |
| **Case-insensitive channels** | Channel names are stored in lowercase internally, following IRC convention |

---

## 📚 Resources

### RFC Documents (Primary References)

- [RFC 2810 — Internet Relay Chat: Architecture](https://www.rfc-editor.org/rfc/rfc2810) — Overview of the IRC architecture.
- [RFC 2811 — Internet Relay Chat: Channel Management](https://www.rfc-editor.org/rfc/rfc2811) — Channel types, modes, and management.
- [RFC 2812 — Internet Relay Chat: Client Protocol](https://www.rfc-editor.org/rfc/rfc2812) — The main reference for client-server message format, commands, and numeric replies.
- [RFC 2813 — Internet Relay Chat: Server Protocol](https://www.rfc-editor.org/rfc/rfc2813) — Server-to-server communication (not implemented, for context only).

### Tutorials & Articles

- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/) — Essential reference for socket programming in C/C++.
- [The `epoll` man page](https://man7.org/linux/man-pages/man7/epoll.7.html) — Linux epoll API documentation.
- [Modern IRC Documentation](https://modern.ircdocs.horse/) — Community-maintained, modern take on IRC protocol documentation.
- [IRC Numerics List](https://defs.ircdocs.horse/defs/numerics.html) — Comprehensive list of IRC numeric reply codes.
- [Chirc — An IRC Server Project](http://chi.cs.uchicago.edu/chirc/index.html) — University of Chicago's IRC server project, useful as a learning reference.

### Tools Used for Development & Testing

- **Wireshark / tcpdump** — Network packet analysis (pcap files included in the repository for reference).
- **irssi / WeeChat / HexChat** — IRC clients used for integration testing.
- **netcat (`nc`)** — Raw TCP client used for manual protocol testing.
- **ngircd** — Reference IRC server used to compare expected behavior and responses.

### AI Usage Disclosure

AI tools (specifically **GitHub Copilot**) were used during the development of this project for the following tasks:

- **Code autocompletion**: Assisted with repetitive boilerplate code such as getters/setters, constructor initializer lists, and copy constructors following the Orthodox Canonical Form.
- **Documentation generation**: Helped draft this README.md file based on the existing codebase structure and content.
- **Debugging assistance**: Consulted for understanding specific IRC numeric reply codes and their expected format.
- **Reference lookups**: Used to quickly find the correct RFC sections for specific command behaviors.

All core logic — including the server architecture, epoll event loop, message parsing, command handlers, channel mode system, and client management — was **designed, implemented, and debugged by the team members**.

---

## 👥 Authors

| 42 Login | GitHub | Role |
|----------|--------|------|
| **mvassall** | [@mvg001](https://github.com/mvg001) | Developer |
| **marcoga2** | [@marcogmurciano](https://github.com/marcogmurciano) | Developer |
| **jrollon-** | [@JRM32](https://github.com/J4P032) | Developer |

---

## 📄 License

This project was developed as part of the **42 school curriculum**. It is intended for educational purposes.