#ifndef CBENCHANTED_H
#define CBENCHANTED_H

//#define M_PI  3.14159265358979323846264338327950288419716939937510
#define M_HALF_PI  (3.14159265358979323846264338327950288419716939937510/2.0)

#include "cbvariableholder.h"
#include "mathinterface.h"
#include "stringinterface.h"
#include "textinterface.h"
#include "fileinterface.h"
#include "meminterface.h"
#include "inputinterface.h"
#include "sysinterface.h"
#include "soundinterface.h"
#include "animinterface.h"
#include "imageinterface.h"
#include "gfxinterface.h"
#include "objectinterface.h"
#include "camerainterface.h"
#include "mapinterface.h"
#include "effectinterface.h"
#include "debug.h"
#include <vector>

using std::vector;

class GfxInterface;


class CBEnchanted : public CBVariableHolder, public MathInterface, public GfxInterface, public StringInterface, public TextInterface, public InputInterface, public SysInterface, public ObjectInterface, public MemInterface, public FileInterface, public MapInterface, public CameraInterface, public ImageInterface, public EffectInterface, public AnimInterface, public SoundInterface {
	public:
		CBEnchanted();
		~CBEnchanted();
	
		static CBEnchanted *instance();
        bool init(string file);
		void run();
		void stop();
		void cleanup();
		bool isSafeExit(){ return safeExit; }
	private:
		
		char *code;
		uint32_t cpos;
		vector <uint32_t> pos;
	
		bool initialized;
		bool running;
		
		bool safeExit;

		map <uint32_t, uint32_t> offsets;
		map <uint32_t, uint32_t> roffsets;
		
		void handlePushFuncptr(void);
		void handleSetInt(void);
		void handleSetFloat(void);
		void handleFunction(void);
		void handleCommand(void);
		void handlePushInt(void);
		void handlePushVariable(void);
		void handlePushSomething(void);
		void handleMathOperation(void);
		void handleJump(void);
		void handleIncVar(void);
		void handleIncGlobalVar(void);
	
		void commandFunction(void);
		void commandSetGlobalVariable(void); //80
		void commandSetArrayNumbers(void); //97
		void commandSetGlobalVariableNumbers(void); //98
		void commandSetVariableNumbers(void);
		void commandGoto(void);
		void commandGosub(void);
		void commandReturn(void);
		void commandDim(void);
		void commandReDim(void);
		void commandClearArray(void);
		void commandInsert(void);
		void commandDelete(void);
		void commandSetVariable(void);
		void commandArrayAssign(void);
		
		void functionNew(void);
		void functionFirst(void);
		void functionLast(void);
		void functionBefore(void);
		void functionAfter(void);
		void functionRead(void);
		void functionConvertToInteger(void);
		void functionConvertToType(void);
};

#endif
