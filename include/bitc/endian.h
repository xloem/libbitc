#ifndef __LIBBITC_ENDIAN_H__
#define __LIBBITC_ENDIAN_H__
/* Copyright 2015 BitPay, Inc.
 * Distributed under the MIT/X11 software license, see the accompanying
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

/** compatibility header for endian.h
 * This is a simple compatibility shim to convert
 * BSD/Linux endian macros to the Mac OS X equivalents.
 * It is public domain.
 * */

#if defined(__APPLE__)

#include <libkern/OSByteOrder.h>

#define htobe16(x) OSSwapHostToBigInt16(x)
#define htole16(x) OSSwapHostToLittleInt16(x)
#define be16toh(x) OSSwapBigToHostInt16(x)
#define le16toh(x) OSSwapLittleToHostInt16(x)

#define htobe32(x) OSSwapHostToBigInt32(x)
#define htole32(x) OSSwapHostToLittleInt32(x)
#define be32toh(x) OSSwapBigToHostInt32(x)
#define le32toh(x) OSSwapLittleToHostInt32(x)

#define htobe64(x) OSSwapHostToBigInt64(x)
#define htole64(x) OSSwapHostToLittleInt64(x)
#define be64toh(x) OSSwapBigToHostInt64(x)
#define le64toh(x) OSSwapLittleToHostInt64(x)

#define bswap_32(x) OSSwapInt32(x)

#elif defined(__DragonFly__) || defined(__FreeBSD__) || defined(__NetBSD__)

#include <sys/endian.h>

#define bswap_32(x) bswap32(x)

#elif defined(__OpenBSD__)

#include <endian.h>

#define bswap_32(x) swap32(x)

#else // assume glibc

#include <endian.h>
#include <byteswap.h>

#endif

#endif /* __LIBBITC_ENDIAN_H__ */
