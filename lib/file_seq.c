/* Copyright 2012 exMULTI, Inc.
 * Copyright (c) 2009-2012 The Bitcoin developers
 * Distributed under the MIT/X11 software license, see the accompanying
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.
 */
#include "libbitc-config.h"

#include <bitc/util.h>                  // for file_seq_open

#include <fcntl.h>                      // for open, posix_fadvise
#include <sys/types.h>
#include <sys/stat.h>

int file_seq_open(const char* filename)
{
    int fd = open(filename, O_RDONLY | O_LARGEFILE);
    if (fd < 0)
        return -1;

#if _XOPEN_SOURCE >= 600 || _POSIX_C_SOURCE >= 200112L
    if (posix_fadvise(fd, 0, 0, POSIX_FADV_SEQUENTIAL) != 0) {
        close(fd);
        return -1;
    }
#endif

    return fd;
}
