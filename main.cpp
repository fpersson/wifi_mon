/*
    Copyright (C) 2019, Fredrik Persson <fpersson.se@gmail.com>

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

#include <iostream>
#include <thread>
#include "networking/wifistatus.h"

int main(int argc, char *argv[]) {
    int last_rx = 0;
    int last_tx = 0;

    if(argc != 2){
        std::cout << "usage: " << "wifi_mon <wifi_iface>" << std::endl;
        return 0;
    }

    auto iface = argv[1];

    networking::WifiStatus ws(iface);
    auto info = ws.getStatus();
    if(info.first){
        std::cout << "\t---========== WIFI_MON ==========---" << std::endl;
        std::cout << "Iface: " << iface << "\t\tMax bitrate: " << info.second.bitrate << "Mbit/s" << "\n";
        std::cout << "SSID: " << info.second.ssid << "\t\tFreq: " <<  info.second.freq << "GHz\n" << std::endl;
    }
    while(true) {
        auto result = ws.getStatus();
        if (result.first) {
            std::cout << "Signal: " << result.second.signal << " dBm ";
            std::cout << "RX: " << result.second.rt_data.rx_byte - last_rx << "b/s ";
            last_rx = result.second.rt_data.rx_byte;
            std::cout << "TX: " << result.second.rt_data.tx_byte - last_tx << "b/s" << std::endl;
            last_tx = result.second.rt_data.tx_byte;
        } else {
            std::cout << "Could not get any status for: " << iface << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
