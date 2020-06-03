#pragma once
#include <cassert>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace cppidioms {
    class UnusedPort {
      public:
        static int port() {
            UnusedPort unused_port;
            assert(unused_port.port_ > 0);
            return unused_port.port_;
        }

      private:
        UnusedPort() {
            for (int attempt = 0; attempt < NUMBER_OF_TRIES; ++attempt) {
                port_ = get_unused_port();
                if (port_ > PORT_LOWER_BOUND && port_ < PORT_UPPER_BOUND) break;
            }
        }

        int get_unused_port() {
            fd_ = socket(AF_INET, SOCK_DGRAM, 0);
            if (fd_ == -1) {
                std::cerr << "socket error: " << std::strerror(errno) << "\n";
                return -1;
            }

            addr.sin_family = AF_INET;
            addr.sin_port   = 0;

            *static_cast<uint32_t *>(&addr.sin_addr.s_addr) = 0;
            socklen_t addr_len                              = sizeof(addr);
            int       errcode = bind(fd_, reinterpret_cast<struct sockaddr *>(&addr), addr_len);
            if (errcode != 0) {
                std::cerr << "bind error: " << std::strerror(errno) << "\n";
                ::close(fd_);
                return -1;
            }
            // Query the socket for its port
            errcode = getsockname(fd_, reinterpret_cast<struct sockaddr *>(&addr), &addr_len);
            if (errcode != 0) {
                std::cerr << "getsockname error: " << strerror(errno) << "\n";
                ::close(fd_);
                return -1;
            }
            ::close(fd_);
            return addr.sin_port;
        }

        static constexpr int PORT_LOWER_BOUND = 49151;
        static constexpr int PORT_UPPER_BOUND = 65535;

        // 1000 is a big number and the chance for us not to get a valid port number is almost 0. If the random port
        // number distribution is uniform.
        static constexpr int NUMBER_OF_TRIES = 1000;

        int                port_ = -1;
        int                fd_   = -1;
        struct sockaddr_in addr;
    };
} // namespace cppidioms
