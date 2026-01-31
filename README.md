# tcp-chat

goal: a simple tcp cli chat program to learn some C. 

fyi: i am a beginner in this stuff so dont expect smth good!!!

## Features

### Implemented
- [x] Basic TCP connection
- [x] Single client messaging

### In Progress
- [ ] Multi-client support

### Planned
- [ ] Nicknames
- [ ] Private messages
- [ ] User authentication
- [ ] Database integration


## for my self

## phase 1: basics (must work)

* [x] server starts and listens on port
* [x] a client can connect
* [x] client can send a message
* [x] server receives and displays the message
* [x] server can send a response
* [x] cleanly close connection
* [x] continues chatting
* [ ] do the cleanup and make it like a real cli message thingy

---

## phase 2: multi-client (real chat)

* [ ] multiple clients at the same time (threads or `select()`)
* [ ] message from client a is sent to all other clients
* [ ] server shows: "client connected" / "client disconnected"
* [ ] client can enter `/quit` to exit

---

## phase 3: nicknames

* [ ] client chooses a nickname when connecting
* [ ] messages show nickname: `[max]: hello!`
* [ ] server checks: nickname already taken?
* [ ] `/nick newname` to change
* [ ] `/list` shows all connected users

---

## phase 4: features

* [ ] private messages: `/msg max secret message`
* [ ] chat rooms/channels: `/join #gaming`
* [ ] commands: `/help`, `/users`, `/time`
* [ ] chat history (last x messages for new clients)
* [ ] typing indicator (optional, complex)

---

## phase 5: accounts & database

* [ ] integrate sqlite or postgresql
* [ ] registration: `/register username password`
* [ ] login: `/login username password`
* [ ] store passwords hashed (e.g. bcrypt)
* [ ] persistent nicknames
* [ ] store chat history in database

---

## phase 6: extras

* [ ] tls/ssl encryption (openssl)
* [ ] config file for server (port, max clients, etc.)
* [ ] admin commands: `/kick`, `/ban`
* [ ] rate limiting (spam protection)
* [ ] file logging
* [ ] client with gui (ncurses or gtk)
