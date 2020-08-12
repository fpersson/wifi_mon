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

#ifndef WIFI_MON_RTSTATUS_H
#define WIFI_MON_RTSTATUS_H

#include <iostream>
#include <map>

#include "structs.h"

namespace networking {
    const std::string SYS_NET_PATH = "/sys/class/net/";
    const std::string RX_BYTES = "/statistics/rx_bytes";
    const std::string RX_PACKETS = "/statistics/rx_packets";
    const std::string TX_BYTES = "/statistics/tx_bytes";
    const std::string TX_PACKETS = "/statistics/tx_packets";

    class RTStatus {
    public:
        explicit RTStatus() = default;
        explicit RTStatus(const std::string &iface);
        void setIFace(const::std::string &iface);

        RTDataResult getRTX();

    private:
        std::pair<bool, int> readData(const std::string &path);
        std::string mRxBytePath;
        std::string mRxPacketPath;
        std::string mTxBytePath;
        std::string mTxPacketPath;
    };
}

#endif //WIFI_MON_RTSTATUS_H
