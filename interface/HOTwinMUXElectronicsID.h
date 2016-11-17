#ifndef DATAFORMATS_HCALDETID_HOTWINMUXELECTRONICSID_H
#define DATAFORMATS_HCALDETID_HOTWINMUXELECTRONICSID_H 1

#include <string>
#include <ostream>
#include <stdint.h>

/** \brief Readout chain identification for HO TwinMUX

    [31:27] Unused (so far)
    [26] VME (0), uTCA (1)

    For VME Electronics:
    [25]    Trigger-chain id flag
    [24:20] Readout Crate Id
    [19] HTR FPGA selector [t/b]
    [18:14] HTR Slot
    [13:9]  DCC id
    [8:5]   Spigot
    [4:2]   FiberIndex or SLB site
    [1:0]   FiberChanId or SLB channel

    For HOTwinMUX Electronics:
    [15:11] Readout Crate Id, 3,6,7,12 for HO. actually only 4 bits will be enough. But we use 5 bits to consistant with all HCAL VME bits assignment
    [10:6] HTR Slot
    [5]   Link, 1 or 2
    [4:0]   Bit loc, 24 channels for YB0, 18 channels for YB+-1, 15  for YB +-2
 */
class HOTwinMUXElectronicsId
{
 public:
  /** Default constructor -- invalid value */
  HOTwinMUXElectronicsId();
  /** from raw */
  HOTwinMUXElectronicsId(uint32_t);
  /** VME Constructor from fiberchan,fiber index,spigot,dccid */
  HOTwinMUXElectronicsId(int bitloc, int link, int htr, int crate);

  uint32_t operator()() { return hotwinmuxElectronicsId_; }
  uint32_t rawId() const { return hotwinmuxElectronicsId_; }

  /** Set the VME htr-related information 1=top, 0=bottom*/
  /// get the fiber channel id (which of channels on a fiber) 
  int bitloc() const { return (hotwinmuxElectronicsId_&0x1F); }
  /// get the fiber index.  For VME 1-8 (which of eight fibers carried by a spigot), for uTCA fibers are zero-based
  int link() const { return (((hotwinmuxElectronicsId_>>5)&0x1)+1); }
  /// get the htr or uHTR slot
  int slot() const { return ((hotwinmuxElectronicsId_>>6)&0x1F); }
  /// get the readout VME crate number
  int crateId() const { return ((hotwinmuxElectronicsId_>>11)&0x1F); }
  /// get a fast, compact, unique index for linear lookups 
  int linearIndex() const { return ((hotwinmuxElectronicsId_)&0xFFFF); }

  static const int maxLinearIndex = 0xFFFF; // 
  
  /** Equality operator */
  int operator==(const HOTwinMUXElectronicsId& id) const { return id.hotwinmuxElectronicsId_==hotwinmuxElectronicsId_; }
  /** Non-Equality operator */
  int operator!=(const HOTwinMUXElectronicsId& id) const { return id.hotwinmuxElectronicsId_!=hotwinmuxElectronicsId_; }
  /// Compare the id to another id for use in a map
  int operator<(const HOTwinMUXElectronicsId& id) const { return hotwinmuxElectronicsId_<id.hotwinmuxElectronicsId_; }

 private:
  uint32_t hotwinmuxElectronicsId_;
};

std::ostream& operator<<(std::ostream&,const HOTwinMUXElectronicsId&);

#endif
