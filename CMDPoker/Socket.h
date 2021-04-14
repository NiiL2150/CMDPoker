#pragma once
/*
   Socket.h
   Copyright (C) 2002-2017 Rene Nyffenegger
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.
   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:
   1. The origin of this source code must not be misrepresented; you must not
      claim that you wrote the original source code. If you use this source code
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.
   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original source code.
   3. This notice may not be removed or altered from any source distribution.
   Rene Nyffenegger rene.nyffenegger@adp-gmbh.ch
*/
#include "Includes.h"

enum TypeSocket { BlockingSocket, NonBlockingSocket };

class Socket {
public:
    static int nofSockets_;
    virtual ~Socket() {
        if (!--(*refCounter_)) {
            Close();
            delete refCounter_;
        }

        --nofSockets_;
        if (!nofSockets_) End();
    }
    Socket(const Socket& o) {
        refCounter_ = o.refCounter_;
        (*refCounter_)++;
        s_ = o.s_;

        nofSockets_++;
    }
    Socket& operator=(Socket& o) {
        (*o.refCounter_)++;

        refCounter_ = o.refCounter_;
        s_ = o.s_;

        nofSockets_++;

        return *this;
    }
    string ReceiveLine() {
        string ret;
        while (1) {
            char r;

            switch (recv(s_, &r, 1, 0)) {
            case 0: // not connected anymore;
                    // ... but last line sent
                    // might not end in \n,
                    // so return ret anyway.
                return ret;
            case -1:
                return "";
                //      if (errno == EAGAIN) {
                //        return ret;
                //      } else {
                //      // not connected anymore
                //      return "";
                //      }
            }

            ret += r;
            if (r == '\n')  return ret;
        }
    }
    string ReceiveBytes() {
        string ret;
        char buf[1024];

        while (1) {
            u_long arg = 0;
            if (ioctlsocket(s_, FIONREAD, &arg) != 0)
                break;

            if (arg == 0)
                break;

            if (arg > 1024) arg = 1024;

            int rv = recv(s_, buf, arg, 0);
            if (rv <= 0) break;

            string t;

            t.assign(buf, rv);
            ret += t;
        }

        return ret;
    }
    void Close() {
        closesocket(s_);
    }
    void SendLine(string s) {
        s += '\n';
        send(s_, s.c_str(), s.length(), 0);
    }
    void SendBytes(const string& s) {
        send(s_, s.c_str(), s.length(), 0);
    }
protected:
    friend class SocketServer;
    friend class SocketSelect;
    Socket(SOCKET s) : s_(s) {
        Start();
        refCounter_ = new int(1);
    };
    Socket() : s_(0) {
        Start();
        // UDP: use SOCK_DGRAM instead of SOCK_STREAM
        s_ = socket(AF_INET, SOCK_DGRAM, 0);

        if (s_ == INVALID_SOCKET) {
            throw "INVALID_SOCKET";
        }

        refCounter_ = new int(1);
    }
    SOCKET s_;
    int* refCounter_;
private:
    static void Start() {
        if (!nofSockets_) {
            WSADATA info;
            if (WSAStartup(MAKEWORD(2, 0), &info)) {
                throw "Could not start WSA";
            }
        }
        ++nofSockets_;
    }
    static void End() {
        WSACleanup();
    }
};

class SocketClient : public Socket {
public:
    SocketClient(const string& host, int port) {
        string error;

        hostent* he;
        if ((he = gethostbyname(host.c_str())) == 0) {
            error = strerror(errno);
            throw error;
        }

        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr = *((in_addr*)he->h_addr);
        memset(&(addr.sin_zero), 0, 8);

        if (::connect(s_, (sockaddr*)&addr, sizeof(sockaddr))) {
            error = strerror(WSAGetLastError());
            throw error;
        }
    }
};

class SocketServer : public Socket {
public:
    SocketServer(int port, int connections, TypeSocket type = BlockingSocket) {
        sockaddr_in sa;

        memset(&sa, 0, sizeof(sa));

        sa.sin_family = PF_INET;
        sa.sin_port = htons(port);
        s_ = socket(AF_INET, SOCK_STREAM, 0);
        if (s_ == INVALID_SOCKET) {
            throw "INVALID_SOCKET";
        }

        if (type == NonBlockingSocket) {
            u_long arg = 1;
            ioctlsocket(s_, FIONBIO, &arg);
        }

        /* bind the socket to the internet address */
        if (bind(s_, (sockaddr*)&sa, sizeof(sockaddr_in)) == SOCKET_ERROR) {
            closesocket(s_);
            throw "INVALID_SOCKET";
        }

        listen(s_, connections);
    }
    Socket* Accept() {
        SOCKET new_sock = accept(s_, 0, 0);
        if (new_sock == INVALID_SOCKET) {
            int rc = WSAGetLastError();
            if (rc == WSAEWOULDBLOCK) {
                return 0; // non-blocking call, no request pending
            }
            else {
                throw "Invalid Socket";
            }
        }

        Socket* r = new Socket(new_sock);
        return r;
    }
};

class SocketSelect {
public:
    SocketSelect(Socket const* const s1, Socket const* const s2 = NULL, TypeSocket type = BlockingSocket) {
        FD_ZERO(&fds_);
        FD_SET(const_cast<Socket*>(s1)->s_, &fds_);
        if (s2) {
            FD_SET(const_cast<Socket*>(s2)->s_, &fds_);
        }

        TIMEVAL tval;
        tval.tv_sec = 0;
        tval.tv_usec = 1;

        TIMEVAL* ptval;
        if (type == NonBlockingSocket) {
            ptval = &tval;
        }
        else {
            ptval = 0;
        }

        if (select(0, &fds_, (fd_set*)0, (fd_set*)0, ptval) == SOCKET_ERROR)
            throw "Error in select";
    }
    bool Readable(Socket const* const s) {
        if (FD_ISSET(s->s_, &fds_)) return true;
        return false;
    }
private:
    fd_set fds_;
};