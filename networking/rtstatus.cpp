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

#include "rtstatus.h"
#include <fstream>

networking::RTStatus::RTStatus(const std::string &iface) {
    setIFace(iface);
}

void networking::RTStatus::setIFace(const std::string &iface) {
    mRxBytePath = std::string(SYS_NET_PATH).append(iface).append(RX_BYTES);
    mRxPacketPath = std::string(SYS_NET_PATH).append(iface).append(RX_PACKETS);
    mTxBytePath = std::string(SYS_NET_PATH).append(iface).append(TX_BYTES);
    mTxPacketPath = std::string(SYS_NET_PATH).append(iface).append(TX_PACKETS);
}

std::pair<bool, int> networking::RTStatus::readData(const std::string &path) {
    bool success = true;
    int result = 0;

    std::string line;
    std::ifstream stream(path);

    if(stream.is_open()){
        std::getline(stream, line);
        result = std::atoi(line.c_str());
    }else{
        success = false;
    }

    return std::pair<bool, int>(success, result);
}

networking::RTDataResult networking::RTStatus::getRTX() {
    RTData ret_data{};
    bool success = true;

    auto rx_byte_result = readData(mRxBytePath);
    if(rx_byte_result.first){
        ret_data.rx_byte = rx_byte_result.second;
    }else{
        success = false;
    }

    auto rx_packets_result = readData(mRxPacketPath);
    if(rx_packets_result.first){
        ret_data.rx_packets = rx_packets_result.second;
    }else{
        success = false;
    }

    auto tx_byte_result = readData(mTxBytePath);
    if(tx_byte_result.first){
        ret_data.tx_byte = tx_byte_result.second;
    }else{
        success = false;
    }

    auto tx_packets_result = readData(mTxPacketPath);
    if(tx_packets_result.first){
        ret_data.tx_packets = tx_packets_result.second;
    }else{
        success = false;
    }

    return std::make_pair(success, ret_data);
}
