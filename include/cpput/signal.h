/**
    @file
    @author  Alexander Sherikov

    @copyright 2022 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#pragma once

#include <csignal>

namespace cpput
{
    // template <class t_SignalHandler>
    // inline bool setSignalHandler(t_SignalHandler handler, const std::vector<int> &signals)
    inline bool setSignalHandler(void (*handler)(int), const std::vector<int> &signals)
    {
        struct sigaction sigaction_handler;
        sigaction_handler.sa_handler = handler;
        sigaction_handler.sa_flags = 0;
        sigemptyset(&sigaction_handler.sa_mask);
        for (const int sig : signals)
        {
            if (0 != sigaction(sig, &sigaction_handler, nullptr))
            {
                return (false);
            }
        }
        return (true);
    }
}  // namespace cpput
