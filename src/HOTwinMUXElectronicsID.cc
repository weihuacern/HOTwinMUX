#include "HOTwinMUX/interface/HOTwinMUXElectronicsID.h"

HOTwinMUXElectronicsId::HOTwinMUXElectronicsId() 
{
  hotwinmuxElectronicsId_=0xffffffffu;
}

HOTwinMUXElectronicsId::HOTwinMUXElectronicsId(uint32_t id) 
{
  hotwinmuxElectronicsId_=id;
}

HOTwinMUXElectronicsId::HOTwinMUXElectronicsId(int bitloc, int link, int htr, int crate) 
{
  hotwinmuxElectronicsId_&=0xFFFF; // keep the readout chain info
  hotwinmuxElectronicsId_=(bitloc&0x1F) | (((link-1)&0x1)<<5) | (((htr-1)&0x1F)<<6) | ((crate&0x1F)<<11);
}

std::ostream& operator<<(std::ostream& os,const HOTwinMUXElectronicsId& id) 
{
  /*
  if (id.isUTCAid()) 
  {
    if (id.isTriggerChainId()) os << "UTCA(trigger): ";
    else os << "UTCA: ";
    return os << id.crateId() << ',' << id.slot() << ',' << id.fiberIndex() << ',' << id.fiberChanId();
  } 
  else 
  {
    if (id.isTriggerChainId()) 
    {
      return os << id.dccid() << ',' << id.spigot() << ",SLB" << id.slbSiteNumber() << ',' << id.slbChannelIndex() << " (HTR "
                << id.readoutVMECrateId() << ":" << id.htrSlot() << ((id.htrTopBottom()==1)?('t'):('b')) << ')'; 
    } 
    else 
    {
      return os << id.dccid() << ',' << id.spigot() << ',' << id.fiberIndex() << ',' << id.fiberChanId() << " (HTR "
                << id.readoutVMECrateId() << ":" << id.htrSlot() << ((id.htrTopBottom()==1)?('t'):('b')) << ')'; 
    }
  }
  */
}
