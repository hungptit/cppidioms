#include <cerrno>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace {
    struct UnusedPort {
        UnusedPort() {
            for (int attempt = 0; attempt < NUMBER_OF_TRIES; ++attempt) {
                port_ = get_unused_port();
                std::cout << port_ << "\n";
            }
        }

        int get_unused_port() {
            fd_ = socket(AF_INET, SOCK_DGRAM, 0);
            if (fd_ == -1) {
                std::cerr << "socket error: " << std::strerror(errno) << "\n";
                return -1;
            }

            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port   = 0;

            *reinterpret_cast<uint32_t *>(&addr.sin_addr.s_addr) = 0;
            socklen_t addr_len                                   = sizeof(addr);
            int       r1 = bind(fd_, reinterpret_cast<struct sockaddr *>(&addr), addr_len);
            if (r1 != 0) {
                std::cerr << "bind error: " << std::strerror(errno) << "\n";
                ::close(fd_);
                return -1;
            }
            // Query the socket for its port, which will be returned by `port()`.
            int r2 = getsockname(fd_, reinterpret_cast<struct sockaddr *>(&addr), &addr_len);
            if (r2 != 0) {
                std::cerr << "getsockname error: " << strerror(errno) << "\n";
                ::close(fd_);
                return -1;
            }
            ::close(fd_);
            return addr.sin_port;
        }

        static constexpr int PORT_LOWER_BOUND = 1024;
        static constexpr int PORT_UPPER_BOUND = 65535;
        static constexpr int NUMBER_OF_TRIES  = 1000;
        int                  port_            = -1;
        int                  fd_              = -1;
    };
} // namespace

int main() { UnusedPort unused_port; }
