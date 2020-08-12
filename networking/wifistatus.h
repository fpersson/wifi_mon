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

#ifndef WIFI_MON_WIFISTATUS_H
#define WIFI_MON_WIFISTATUS_H

#include <iostream>
#include <map>
#include "rtstatus.h"
#include "structs.h"

namespace networking {
    class WifiStatus {
        public:
            explicit WifiStatus() = default;
            explicit WifiStatus(const std::string &iface);
            ~WifiStatus() = default;

            bool setIface(const std::string &iface);

            SignalResult getStatus();

        private:
            std::string mIFace;
            RTStatus mStatus;
    };
}


#endif //WIFI_MON_WIFISTATUS_H
