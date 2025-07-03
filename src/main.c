/**
 * @file main.c
 * @author Michal Vasko <mvasko@cesnet.cz>
 * @brief netopeer2-server - NETCONF server
 *
 * @copyright
 * Copyright (c) 2019 - 2021 Deutsche Telekom AG.
 * Copyright (c) 2017 - 2021 CESNET, z.s.p.o.
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */

#include <stdlib.h>
#include "netopeer2-server-startup.h"

int
main(int argc, char *argv[])
{
    int ret = EXIT_SUCCESS;
    np2srv_opts opts = { 0 };

    if ((ret = np2srv_parse_options(argc, argv, &opts)) != EXIT_SUCCESS) {
        return ret;
    }
    return np2srv_startup(&opts, true,
                          NULL, true, true);
}
