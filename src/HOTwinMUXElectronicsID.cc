#include "HOTwinMUX/interface/HOTwinMUXElectronicsID.h"

HOTwinMUXElectronicsId::HOTwinMUXElectronicsId() {
  hotwinmuxElectronicsId_=0xffffffffu;
}

HOTwinMUXElectronicsId::HOTwinMUXElectronicsId(uint32_t id) {
  hotwinmuxElectronicsId_=id;
}

HOTwinMUXElectronicsId::HOTwinMUXElectronicsId(int fiberChan, int fiberIndex, int spigot, int dccid) {
  hotwinmuxElectronicsId_=(fiberChan&0x3) | (((fiberIndex-1)&0x7)<<2) |
    ((spigot&0xF)<<5) | ((dccid&0x1F)<<9);
}

HOTwinMUXElectronicsId::HOTwinMUXElectronicsId(int slbChan, int slbSite, int spigot, int dccid, int crate, int slot, int tb) {
  hotwinmuxElectronicsId_=(slbChan&0x3) | (((slbSite)&0x7)<<2) |
    ((spigot&0xF)<<5) | ((dccid&0x1F)<<9);
  hotwinmuxElectronicsId_|=((tb&0x1)<<19) | ((slot&0x1f)<<14) | ((crate&0x3f)<<20);
  hotwinmuxElectronicsId_|=0x02000000;
}

HOTwinMUXElectronicsId::HOTwinMUXElectronicsId(int crate, int slot, int fiber, int fc, bool isTrigger) {
  hotwinmuxElectronicsId_=(fc&0xF) | (((fiber)&0x1F)<<4) |
    ((slot&0xF)<<9) | ((crate&0x3F)<<13);
  if (isTrigger)   hotwinmuxElectronicsId_|=0x02000000;
  hotwinmuxElectronicsId_|=0x04000000;
}

std::string HOTwinMUXElectronicsId::slbChannelCode() const {
  std::string retval;
  if (isTriggerChainId() && isVMEid()) {
    if (htrTopBottom()) { // top
      switch (slbChannelIndex()) {
      case (0): retval="A0"; break;
      case (1): retval="A1"; break;
      case (2): retval="C0"; break;
      case (3): retval="C1"; break;
      }
    } else {
      switch (slbChannelIndex()) {
      case (0): retval="B0"; break;
      case (1): retval="B1"; break;
      case (2): retval="D0"; break;
      case (3): retval="D1"; break;
      }
    }
  }
  return retval;
}

void HOTwinMUXElectronicsId::setHTR(int crate, int slot, int tb) {
  if (isUTCAid()) return; // cannot do this for uTCA
  hotwinmuxElectronicsId_&=0x3FFF; // keep the readout chain info
  hotwinmuxElectronicsId_|=((tb&0x1)<<19) | ((slot&0x1f)<<14) | ((crate&0x3f)<<20);
}

std::ostream& operator<<(std::ostream& os,const HOTwinMUXElectronicsId& id) {
  if (id.isUTCAid()) {
    if (id.isTriggerChainId()) os << "UTCA(trigger): ";
    else os << "UTCA: ";
    return os << id.crateId() << ',' << id.slot() << ',' << id.fiberIndex() << ',' << id.fiberChanId();
  } else {
    if (id.isTriggerChainId()) {
      return os << id.dccid() << ',' << id.spigot() << ",SLB" << id.slbSiteNumber() << ',' << id.slbChannelIndex() << " (HTR "
		<< id.readoutVMECrateId() << ":" << id.htrSlot() << ((id.htrTopBottom()==1)?('t'):('b')) << ')'; 
      
    } else {
      return os << id.dccid() << ',' << id.spigot() << ',' << id.fiberIndex() << ',' << id.fiberChanId() << " (HTR "
		<< id.readoutVMECrateId() << ":" << id.htrSlot() << ((id.htrTopBottom()==1)?('t'):('b')) << ')'; 
    }
  }
}
