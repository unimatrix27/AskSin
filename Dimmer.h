//- -----------------------------------------------------------------------------------------------------------------------
// AskSin driver implementation
// 2013-08-03 <horst@diebittners.de> Creative Commons - http://creativecommons.org/licenses/by-nc-sa/3.0/de/
//- -----------------------------------------------------------------------------------------------------------------------
//- Dimmer class -----------------------------------------------------------------------------------------------------------
//- with a lot of support from martin876 at FHEM forum
//- -----------------------------------------------------------------------------------------------------------------------
#ifndef DIMMER_H
#define DIMMER_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "AskSinMain.h"
#include "utility/Serial.h"
#include "utility/Helpers.h"
#include "utility/Fastdelegate.h"

//#define DM_DBG																		// debug message flag

class Dimmer {
  //- user code here ------------------------------------------------------------------------------------------------------
  public://----------------------------------------------------------------------------------------------------------------
	//void     config(uint8_t type, uint8_t pinOn, uint8_t pinOff, uint8_t minDelay, uint8_t randomDelay);
	void     config(void Init(), void Switch(uint8_t), uint8_t minDelay, uint8_t randomDelay);

  protected://-------------------------------------------------------------------------------------------------------------
  private://---------------------------------------------------------------------------------------------------------------
	struct s_srly {
		uint8_t  shCtRampOn          : 4;     // 0x01, s:0, e:4
		uint8_t  shCtRampOff         : 4;     // 0x01, s:4, e:8
		uint8_t  shCtDlyOn           : 4;     // 0x02, s:0, e:4
		uint8_t  shCtDlyOff          : 4;     // 0x02, s:4, e:8
		uint8_t  shCtOn              : 4;     // 0x03, s:0, e:4
		uint8_t  shCtOff             : 4;     // 0x03, s:4, e:8
		uint8_t  shCtValLo;                   // 0x04, s:0, e:0
		uint8_t  shCtValHi;                   // 0x05, s:0, e:0
		uint8_t  shOnDly;                     // 0x06, s:0, e:0
		uint8_t  shOnTime;                    // 0x07, s:0, e:0
		uint8_t  shOffDly;                    // 0x08, s:0, e:0
		uint8_t  shOffTime;                   // 0x09, s:0, e:0
		uint8_t  shActionTypeDim     : 4;     // 0x0a, s:0, e:4
		uint8_t                      : 1;     //
		uint8_t  shOffTimeMode       : 1;     // 0x0a, s:6, e:7
		uint8_t  shOnTimeMode        : 1;     // 0x0a, s:7, e:8
		uint8_t  shDimJtOn           : 4;     // 0x0b, s:0, e:4
		uint8_t  shDimJtOff          : 4;     // 0x0b, s:4, e:8
		uint8_t  shDimJtDlyOn        : 4;     // 0x0c, s:0, e:4
		uint8_t  shDimJtDlyOff       : 4;     // 0x0c, s:4, e:8
		uint8_t  shDimJtRampOn       : 4;     // 0x0d, s:0, e:4
		uint8_t  shDimJtRampOff      : 4;     // 0x0d, s:4, e:8
		uint8_t                      : 5;     //       l:0, s:5
		uint8_t  shOffDlyBlink       : 1;     // 0x0e, s:5, e:6
		uint8_t  shOnLvlPrio         : 1;     // 0x0e, s:6, e:7
		uint8_t  shOnDlyMode         : 1;     // 0x0e, s:7, e:8
		uint8_t  shOffLevel;                  // 0x0f, s:0, e:0
		uint8_t  shOnMinLevel;                // 0x10, s:0, e:0
		uint8_t  shOnLevel;                   // 0x11, s:0, e:0
		uint8_t  shRampSstep;                 // 0x12, s:0, e:0
		uint8_t  shRampOnTime;                // 0x13, s:0, e:0
		uint8_t  shRampOffTime;               // 0x14, s:0, e:0
		uint8_t  shDimMinLvl;                 // 0x15, s:0, e:0
		uint8_t  shDimMaxLvl;                 // 0x16, s:0, e:0
		uint8_t  shDimStep;                   // 0x17, s:0, e:0
		uint8_t  shOffDlyNewTime;             // 0x19, s:0, e:0
		uint8_t  shOffDlyOldTime;             // 0x1a, s:0, e:0
		uint8_t  shDimElsActionType  : 4;     // 0x26, s:0, e:4
		uint8_t                      : 2;     //
		uint8_t  shDimElsOffTimeMd   : 1;     // 0x26, s:6, e:7
		uint8_t  shDimElsOnTimeMd    : 1;     // 0x26, s:7, e:8
		uint8_t  shDimElsJtOn        : 4;     // 0x27, s:0, e:4
		uint8_t  shDimElsJtOff       : 4;     // 0x27, s:4, e:8
		uint8_t  shDimElsJtDlyOn     : 4;     // 0x28, s:0, e:4
		uint8_t  shDimElsJtDlyOff    : 4;     // 0x28, s:4, e:8
		uint8_t  shDimElsJtRampOn    : 4;     // 0x29, s:0, e:4
		uint8_t  shDimElsJtRampOff   : 4;     // 0x29, s:4, e:8
		uint8_t  lgCtRampOn          : 4;     // 0x81, s:0, e:4
		uint8_t  lgCtRampOff         : 4;     // 0x81, s:4, e:8
		uint8_t  lgCtDlyOn           : 4;     // 0x82, s:0, e:4
		uint8_t  lgCtDlyOff          : 4;     // 0x82, s:4, e:8
		uint8_t  lgCtOn              : 4;     // 0x83, s:0, e:4
		uint8_t  lgCtOff             : 4;     // 0x83, s:4, e:8
		uint8_t  lgCtValLo;                   // 0x84, s:0, e:0
		uint8_t  lgCtValHi;                   // 0x85, s:0, e:0
		uint8_t  lgOnDly;                     // 0x86, s:0, e:0
		uint8_t  lgOnTime;                    // 0x87, s:0, e:0
		uint8_t  lgOffDly;                    // 0x88, s:0, e:0
		uint8_t  lgOffTime;                   // 0x89, s:0, e:0
		uint8_t  lgActionTypeDim     : 4;     // 0x8a, s:0, e:4
		uint8_t                      : 0;     //
		uint8_t  lgMultiExec         : 1;     // 0x8a, s:5, e:6
		uint8_t  lgOffTimeMode       : 1;     // 0x8a, s:6, e:7
		uint8_t  lgOnTimeMode        : 1;     // 0x8a, s:7, e:8
		uint8_t  lgDimJtOn           : 4;     // 0x8b, s:0, e:4
		uint8_t  lgDimJtOff          : 4;     // 0x8b, s:4, e:8
		uint8_t  lgDimJtDlyOn        : 4;     // 0x8c, s:0, e:4
		uint8_t  lgDimJtDlyOff       : 4;     // 0x8c, s:4, e:8
		uint8_t  lgDimJtRampOn       : 4;     // 0x8d, s:0, e:4
		uint8_t  lgDimJtRampOff      : 4;     // 0x8d, s:4, e:8
		uint8_t                      : 5;     //       l:0, s:5
		uint8_t  lgOffDlyBlink       : 1;     // 0x8e, s:5, e:6
		uint8_t  lgOnLvlPrio         : 1;     // 0x8e, s:6, e:7
		uint8_t  lgOnDlyMode         : 1;     // 0x8e, s:7, e:8
		uint8_t  lgOffLevel;                  // 0x8f, s:0, e:0
		uint8_t  lgOnMinLevel;                // 0x90, s:0, e:0
		uint8_t  lgOnLevel;                   // 0x91, s:0, e:0
		uint8_t  lgRampSstep;                 // 0x92, s:0, e:0
		uint8_t  lgRampOnTime;                // 0x93, s:0, e:0
		uint8_t  lgRampOffTime;               // 0x94, s:0, e:0
		uint8_t  lgDimMinLvl;                 // 0x95, s:0, e:0
		uint8_t  lgDimMaxLvl;                 // 0x96, s:0, e:0
		uint8_t  lgDimStep;                   // 0x97, s:0, e:0
		uint8_t  lgOffDlyNewTime;             // 0x99, s:0, e:0
		uint8_t  lgOffDlyOldTime;             // 0x9a, s:0, e:0
		uint8_t  lgDimElsActionType  : 4;     // 0xa6, s:0, e:4
		uint8_t                      : 1;     //
		uint8_t  lgDimElsOffTimeMd   : 1;     // 0xa6, s:6, e:7
		uint8_t  lgDimElsOnTimeMd    : 1;     // 0xa6, s:7, e:8
		uint8_t  lgDimElsJtOn        : 4;     // 0xa7, s:0, e:4
		uint8_t  lgDimElsJtOff       : 4;     // 0xa7, s:4, e:8
		uint8_t  lgDimElsJtDlyOn     : 4;     // 0xa8, s:0, e:4
		uint8_t  lgDimElsJtDlyOff    : 4;     // 0xa8, s:4, e:8
		uint8_t  lgDimElsJtRampOn    : 4;     // 0xa9, s:0, e:4
		uint8_t  lgDimElsJtRampOff   : 4;     // 0xa9, s:4, e:8
	};

	void (*tInit)(void);
	void (*tSwitch)(uint8_t);
	
	//uint8_t hwType:1;																	// 0 indicates a monostable, 1 a bistable Dimmer
	//uint8_t hwPin[2];																	// first byte for on, second for off
	uint8_t msgRecvCnt;																	// receive counter to avoid double action on one message
	
	uint8_t curStat:4, nxtStat:4;														// current state and next state
	uint8_t OnDly, OnTime, OffDly, OffTime, RampOnTime, RampOffTime;					// trigger 40/41 timer variables
	uint8_t lastTrig;																	// store for the last trigger
	uint8_t nxtValue; 																	// current Dim - Target range: 0 - 200 (mapped to 0-100 in 0.5 steps)
	float curValue;																		// current Value of Dimmer 
	bool ramping;																		// is the automatic ramping activated
	uint16_t rTime, dTime;																// trigger 11 timer variables
	uint32_t rlyTime;																	// timer for poll routine
	uint32_t dimTime;																	// how much dimsteps to target
	uint32_t nextDimTime;
	float dimSlice;																		// size of next dimstep
	uint8_t mDel, rDel;																	// store for the call back delay
	uint32_t cbsTme;																	// timer for call back poll routine

	void    trigger11(uint8_t val, uint8_t *rampTime, uint8_t *duraTime);				// FHEM event
	void    trigger41(uint8_t lngIn, uint8_t val);										// sensor event called
	void    trigger40(uint8_t lngIn, uint8_t cnt);										// remote event called
 
	void    adjRly();																	// give curValue to frontend and prepare status message
	void 	newDim();
	uint8_t getMovStat(void);															// provide movement status byte for ACK enhanced - 40 if status is not set, otherwise 00
	uint8_t getRlyStat(void);															// provide Dimmer status byte for ACK enhanced - 40 if status is not set, otherwise 00

  
  //- mandatory functions for every new module to communicate within HM protocol stack ------------------------------------ 
  public://----------------------------------------------------------------------------------------------------------------
	uint8_t modStat;																	// module status byte, needed for list3 modules to answer status requests
	uint8_t regCnl;																		// holds the channel for the module

	HM      *hm;																		// pointer to HM class instance
	s_srly  *ptrPeerList;																// pointer to list3/4 in regs struct
	//uint8_t *ptrPeerList;																// pointer to list3/4 in regs struct
	uint8_t *ptrMainList;																// pointer to list0/1 in regs struct

	void     configCngEvent(void);														// list1 on registered channel had changed
	void     pairSetEvent(uint8_t *data, uint8_t len);									// pair message to specific channel, handover information for value, ramp time and so on
	void     pairStatusReq(void);														// event on status request
	void     peerMsgEvent(uint8_t type, uint8_t *data, uint8_t len);					// peer message was received on the registered channel, handover the message bytes and length

	void     poll(void);																// poll function, driven by HM loop

	//- predefined, no reason to touch ------------------------------------------------------------------------------------
	void     regInHM(uint8_t cnl, HM *instPtr);											// register this module in HM on the specific channel
	void     hmEventCol(uint8_t by3, uint8_t by10, uint8_t by11, uint8_t *data, uint8_t len); // call back address for HM for informing on events
	void     peerAddEvent(uint8_t *data, uint8_t len);									// peer was added to the specific channel, 1st and 2nd byte shows peer channel, third and fourth byte shows peer index
};


#endif
