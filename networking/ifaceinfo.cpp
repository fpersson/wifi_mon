/*
    Copyright (C) 2020, Fredrik Persson <fpersson.se@gmail.com>

    Permission to use, copy, modify, and/or distribute this software
    for any purpose with or without fee is hereby granted.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
    AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
    INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
    OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
    OF THIS SOFTWARE.
*/
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>

#include "ifaceinfo.h"

networking::IfaceDataResult networking::IfaceInfo::getActiveIFace() {
    bool success = false;
    IfaceData result{};
    struct ifaddrs *ifAddr = nullptr;
    struct ifaddrs *ifa = nullptr;
    void *tmpAddr = nullptr;

    getifaddrs(&ifAddr);
    for(ifa = ifAddr; ifa != nullptr; ifa = ifa->ifa_next){
        if(!ifa->ifa_addr){
            continue;
        }
        if(ifa->ifa_addr->sa_family == AF_INET){
            tmpAddr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char buffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddr, buffer, INET_ADDRSTRLEN);
            if(std::string(buffer) != "127.0.0.1") {
                result.ifaceName = ifa->ifa_name;
                result.ipAddr = buffer;
                auto mac = getMac(result.ifaceName);
                if(mac.first){
                    result.macAddr = mac.second;
                }else{
                    result.macAddr = "unknown";
                }
                success = true;
            }
        } else if(ifa->ifa_addr->sa_family == AF_INET6) {
            tmpAddr = &((struct sockaddr_in6 *) ifa->ifa_addr)->sin6_addr;
            char buffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddr, buffer, INET6_ADDRSTRLEN);
            /*
            result.ifaceName = ifa->ifa_name;
            result.ipAddr = buffer;
            result.macAddr = "unknown";
            success = true;
            */
        }
    }
    if(ifAddr!= nullptr){
        freeifaddrs(ifAddr);
    }

    return std::make_pair(success, result);
}

std::pair<bool, std::string> networking::IfaceInfo::getMac(const std::string &iface) {
    bool success = false;
    std::string result;
    std::string path = "/sys/class/net/";
    path.append(iface).append("/address");

    std::ifstream stream(path);

    if(stream.is_open()){
        std::getline(stream, result);
        success = true;
    }else{
        success = false;
    }

    return std::pair<bool, std::string>(success, result);
}
