/**************************************************************************
Etherboot -  BOOTP/TFTP Bootstrap Program
Prism2 NIC driver for Etherboot
Wrapper for prism2_pci

Written by Michael Brown of Fen Systems Ltd
$Id$
***************************************************************************/

/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2, or (at
 * your option) any later version.
 */

/*
 * Oracle GPL Disclaimer: For the avoidance of doubt, except that if any license choice
 * other than GPL or LGPL is available it will apply instead, Oracle elects to use only
 * the General Public License version 2 (GPLv2) at this time for any software where
 * a choice of GPL license versions is made available with the language indicating
 * that GPLv2 or any later version may be used, or where a choice of which version
 * of the GPL is applied is otherwise unspecified.
 */

FILE_LICENCE ( GPL2_OR_LATER );

#include <ipxe/pci.h>
#include <nic.h>

#define WLAN_HOSTIF WLAN_PCI
#include "prism2.c"

static int prism2_pci_probe ( struct nic *nic, struct pci_device *pci ) {
  hfa384x_t *hw = &hw_global;

  printf ( "Prism2.5 has registers at %#lx\n", pci->membase );
  hw->membase = ioremap ( pci->membase, 0x100 );

  nic->ioaddr = pci->membase;
  nic->irqno = 0;

  return prism2_probe ( nic, hw );
}

static void prism2_pci_disable ( struct nic *nic ) {
  prism2_disable ( nic );
}

static struct pci_device_id prism2_pci_nics[] = {
PCI_ROM(0x1260, 0x3873, "prism2_pci",	"Harris Semiconductor Prism2.5 clone", 0),
PCI_ROM(0x1260, 0x3873, "hwp01170",	"ActionTec HWP01170", 0),
PCI_ROM(0x1260, 0x3873, "dwl520",	"DLink DWL-520", 0),
};

PCI_DRIVER ( prism2_pci_driver, prism2_pci_nics, PCI_NO_CLASS );

DRIVER ( "Prism2/PCI", nic_driver, pci_driver, prism2_pci_driver,
	 prism2_pci_probe, prism2_pci_disable );

/*
 * Local variables:
 *  c-basic-offset: 8
 *  c-indent-level: 8
 *  tab-width: 8
 * End:
 */