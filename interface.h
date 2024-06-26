/**
 * @file interface.h
 * @brief Implements network interface data structures.
 * @note Copyright (C) 2020 Richard Cochran <richardcochran@gmail.com>
 * @note SPDX-License-Identifier: GPL-2.0+
 */
#ifndef HAVE_INTERFACE_H
#define HAVE_INTERFACE_H

#include <stdbool.h>
#include <sys/queue.h>
#include "sk.h"

#define MAX_IFNAME_SIZE 108 /* = UNIX_PATH_MAX */

#if (IF_NAMESIZE > MAX_IFNAME_SIZE)
#error if_namesize larger than expected.
#endif

/** Opaque type */
struct interface;

/**
 * Creates an instance of an interface.
 * @param name  The device which indentifies this interface.
 * @param remote  For UDS interfaces, the address of the remote server, possibly NULL.
 * @return      A pointer to an interface instance on success, NULL otherwise.
 */
struct interface *interface_create(const char *name, const char *remote);

/**
 * Destroys an instance of an interface.
 * @param iface  A pointer obtained via interface_create().
 */
void interface_destroy(struct interface *iface);

/**
 * Populate the time stamping information of a given interface.
 * @param iface  The interface of interest.
 * @return       zero on success, negative on failure.
 */
int interface_get_tsinfo(struct interface *iface);

/**
 * Populate the time stamping information of a given interface.
 * @param iface  The interface of interest.
 * @return       zero on success, negative on failure.
 */
int interface_get_ifinfo(struct interface *iface);

/**
 * Obtain the time stamping label of a network interface.  This can be
 * different from the name of the interface when bonding is in effect.
 *
 * @param iface  The interface of interest.
 * @return       The time stamping device name of the network interface.
 */
const char *interface_label(struct interface *iface);

/**
 * Obtains the name of a network interface.
 * @param iface  The interface of interest.
 * @return       The device name of the network interface.
 */
const char *interface_name(struct interface *iface);

/**
 * Obtains the index of a PTP Hardware Clock device from a network interface.
 * @param iface  The interface of interest.
 * @return       The PHC index of the interface.
 */
int interface_phc_index(struct interface *iface);

/**
 * Obtains the remote address from a UDS interface.
 * @param iface  The interface of interest.
 * @return       The device name of the network interface.
 */
const char *interface_remote(struct interface *iface);

/**
 * Set the time stamping label of a given interface.
 * @param iface  The interface of interest.
 * @param name   The desired label for the interface.
 */
void interface_set_label(struct interface *iface, const char *label);

/**
 * Tests whether an interface's time stamping information is valid or not.
 * @param iface  The interface of interest.
 * @return       True if the time stamping information is valid, false otherwise.
 */
bool interface_tsinfo_valid(struct interface *iface);

/**
 * Tests whether an interface's interface information is valid or not.
 * @param iface  The interface of interest.
 * @return       True if the interface information is valid, false otherwise.
 */
bool interface_ifinfo_valid(struct interface *iface);

/**
 * Tests whether an interface supports a set of given time stamping modes.
 * @param iface  The interface of interest.
 * @param modes  Bit mask of SOF_TIMESTAMPING_ flags.
 * @return       True if the time stamping modes are supported, false otherwise.
 */
bool interface_tsmodes_supported(struct interface *iface, int modes);

/**
 * Tests whether an interface supports a HWTSTAMP_FILTER_PTP_V2_XX_EVENT.
 * @param iface  The interface of interest.
 * @return       True if the HWTSTAMP_FILTER_PTP_V2_XX_EVENT is supported, false otherwise.
 */
bool interface_check_rxfilters_event(struct interface *iface);

/**
 * Set the vclock (virtual PHC) to be used for timestamping on an interface.
 * @param iface  The interface of interest.
 * @param vclock The index of the vclock.
 */
void interface_set_vclock(struct interface *iface, int vclock);

/**
 * Get the vclock index set for the interface.
 * @param iface  The interface of interest.
 * @return       The index of the vclock, or -1 if not set.
 */
int interface_get_vclock(struct interface *iface);

/**
 * Obtains the interface bit period based on the speed.
 * @param iface  The interface of interest.
 * @return       return interface bitperiod in atto seconds.
 */
uint64_t interface_bitperiod(struct interface *iface);

#endif
