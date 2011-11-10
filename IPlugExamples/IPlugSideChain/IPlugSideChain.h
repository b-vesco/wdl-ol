#ifndef __IPLUGSIDECHAIN__
#define __IPLUGSIDECHAIN__

#include "IPlug_include_in_plug_hdr.h"
#include "IPlugSideChain_Controls.h"

class IPlugSideChain : public IPlug
{
public:
  
  IPlugSideChain(IPlugInstanceInfo instanceInfo);
  ~IPlugSideChain();
  
  void Reset();
  void OnParamChange(int paramIdx);
  
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);
  
private:
  
  double mGain;
};

#endif