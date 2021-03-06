#ifndef _IPLUGAPI_
#define _IPLUGAPI_

#include "IPlugOSDetect.h" // Don't Know why this has to be here too
#include "IPlugBase.h"

#ifdef OS_WIN
  #include "../rtaudiomidi/RtMidi.h"

  struct IPlugInstanceInfo
  {
    RtMidiOut* mRTMidiOut;
    unsigned short* mMidiOutChan; // 0 = any, 1 = midi chan 1
  };

#elif defined OS_OSX
  #include "RtMidi.h"

  struct IPlugInstanceInfo
  {
    WDL_String mOSXBundleID;
    RtMidiOut* mRTMidiOut;
    unsigned short* mMidiOutChan; // 0 = any, 1 = midi chan 1
  };

#elif defined OS_IOS
#include "IOSLink.h"
  struct IPlugInstanceInfo
  {
    WDL_String mIOSBundleID;
    IOSLink* mIOSLink;
    unsigned short* mMidiOutChan; // 0 = any, 1 = midi chan 1
  };

#endif 

class IPlugStandalone : public IPlugBase
{
public:

	IPlugStandalone(IPlugInstanceInfo instanceInfo, 
                  int nParams, 
                  const char* channelIOStr, 
                  int nPresets,
                  const char* effectName, 
                  const char* productName, 
                  const char* mfrName,
                  int vendorVersion, 
                  int uniqueID, 
                  int mfrID, 
                  int latency = 0, 
                  bool plugDoesMidi = false, 
                  bool plugDoesChunks = false, 
                  bool plugIsInst = false,
                  int plugScChans = 0);

  void BeginInformHostOfParamChange(int idx);
	void InformHostOfParamChange(int idx, double normalizedValue);
  void EndInformHostOfParamChange(int idx);

	void InformHostOfProgramChange();
	
	int GetSamplePos();   // Samples since start of project.
	double GetTempo();
	void GetTimeSig(int* pNum, int* pDenom);
	void GetTime(ITimeInfo* pTimeInfo);

  void ResizeGraphics(int w, int h);
  void SetSampleRate(double sampleRate);
  void SetBlockSize(int blockSize); 
 
#ifdef OS_IOS
  void LockMutexAndProcessSingleReplacing(float** inputs, float** outputs, int nFrames);
#else
  void LockMutexAndProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);
#endif

protected:
  void HostSpecificInit();
	bool SendMidiMsg(IMidiMsg* pMsg);
  bool SendMidiMsgs(WDL_TypedBuf<IMidiMsg>* pMsgs);

private:

  bool mDoesMidi;
    
//  ByteChunk mState;     // Persistent storage if the host asks for plugin state.
//  ByteChunk mBankState; // Persistent storage if the host asks for bank state.

#ifdef OS_IOS
  IOSLink* mIOSLink;
#else // OSX or WIN
  RtMidiOut* mMidiOut;
  unsigned short* mMidiOutChan;
#endif
  
public:

};

IPlugStandalone* MakePlug(void* pMidiOutput, unsigned short* pMidiOutChan, void* pIOSLink =  NULL);

#endif