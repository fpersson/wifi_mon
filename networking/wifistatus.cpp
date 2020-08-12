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

#include "wifistatus.h"

#include <fstream>
#include <cstring>
#include <linux/wireless.h>
#include <sys/ioctl.h>

networking::WifiStatus::WifiStatus(const std::string &iface) {
    setIface(iface);
}

bool networking::WifiStatus::setIface(const std::string &iface) {
    mIFace = iface;
    mStatus.setIFace(mIFace);
    return true;
}

networking::SignalResult networking::WifiStatus::getStatus() {
    WifiInfo signalInfo{};
    bool success = true;
    struct iw_statistics *iwStatistics{};

    iwreq req{};
    strcpy(req.ifr_name, mIFace.c_str());

    int fd = ::socket(AF_INET, SOCK_DGRAM, 0);
    req.u.data.pointer = (struct iw_statistics *) malloc( sizeof(* iwStatistics));
    req.u.data.length = sizeof(* iwStatistics);
    req.u.data.flags = 1;

    ////////////////////////// signal ////////////////////////////
    //get signal signal in dBm
    if(ioctl(fd, SIOCGIWSTATS, &req) == -1){
        success = false;
        std::cout << "failing: on strengt" << std::endl;
    }else if( ((iw_statistics*)req.u.data.pointer)->qual.updated & IW_QUAL_DBM ) {
        signalInfo.signal = ( (iw_statistics*) req.u.data.pointer)->qual.level - 256;
    }

    ////////////////////////// ssid ////////////////////////////
    char ssid_buff[32];
    memset(ssid_buff, 0, 32);
    req.u.essid.pointer = ssid_buff;
    req.u.essid.length = 32;

    if(ioctl(fd, SIOCGIWESSID, &req) == -1){
        success = false;
        std::cout << "failing: on ssid" << std::endl;
    }else{
        memcpy( &signalInfo.ssid, req.u.essid.pointer, req.u.essid.length);
        memset( &signalInfo.ssid[req.u.essid.length], 0, 1);
    }

    ////////////////////////// bitrate ////////////////////////////
    int bitrate = 0;
    if(ioctl(fd, SIOCGIWRATE, &req) == -1){
        success = false;
        std::cout << "failing on bitrate" << std::endl;
    }else{
        memcpy(&bitrate, &req.u.bitrate, sizeof(int));
        signalInfo.bitrate=bitrate/1000000; //to megabit
    }

    ////////////////////////// freq ////////////////////////////
    int freq = -1;
    if(ioctl(fd,SIOCGIWFREQ, &req) == -1){
        success = false;
        std::cout << "failed on freq" << std::endl;
    }else{
        memcpy(&freq, &req.u.freq, sizeof(int));
        signalInfo.freq = freq/100000000.0;
    }

    ////////////////////////// rx/tx ////////////////////////////
    RTData rtData{};
    auto status = mStatus.getRTX();
    if(status.first){
        signalInfo.rt_data = status.second;
    }else{
        success = false;
        std::cout << "Could not read rtx for " << mIFace << std::endl;
    }

    return std::make_pair(success, signalInfo);
}


