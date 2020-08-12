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

#ifndef WIFI_MON_STRUCTS_H
#define WIFI_MON_STRUCTS_H

#include <iostream>

namespace networking{
    /**
     * contain rx/tx data
     */
    struct RTData{
        int rx_byte;
        int rx_packets;
        int tx_byte;
        int tx_packets;
    };

    struct WifiInfo{
        char ssid[33];
        int bitrate;
        int signal;
        float freq; //in GHz
        RTData rt_data;
    };

    using SignalResult = std::pair<bool, WifiInfo>;
    using RTDataResult = std::pair<bool, RTData>;
}

#endif //WIFI_MON_STRUCTS_H
