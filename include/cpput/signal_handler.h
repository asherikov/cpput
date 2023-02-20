/**
    @file
    @author  Alexander Sherikov

    @copyright 2022 Alexander Sherikov, Licensed under the Apache License, Version 2.0.
    (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#pragma once

#include "signal.h"

namespace
{
    volatile std::sig_atomic_t g_signal_flag;
    void handleSignal(int signum)
    {
        g_signal_flag = signum;
    }
}  // namespace
