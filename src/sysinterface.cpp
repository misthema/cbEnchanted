#include "precomp.h"
#include "cbenchanted.h"
#include "gfxinterface.h"
#include "sysinterface.h"
#include <time.h>
#include <iostream>
#ifdef WIN32
	#include <Windows.h>
#else
	#include <unistd.h>
#endif

SysInterface::SysInterface() {
	cb = static_cast <CBEnchanted *> (this);
}

void SysInterface::commandWait(void) {
#ifdef WIN32
	Sleep(cb->popValue().toInt());
#else
	uint32_t sleepTime = cb->popValue().toInt();
	usleep(sleepTime * 1000);
#endif
}

void SysInterface::commandMakeError(void) {
#ifdef WIN32
	MessageBoxA(NULL,cb->popValue().toString().c_str(),"Error",MB_OK);
#else
	assert("Linux MakeError uncomplete" != 0)
#endif
}

void SysInterface::commandSaveProgram(void) {
	
}

void SysInterface::commandLoadProgram(void) {
	
}

void SysInterface::commandGotoSavedLocation(void) {
	
}

void SysInterface::commandFrameLimit(void) {
	cb->getWindow()->SetFramerateLimit(cb->popValue().toInt());
}

void SysInterface::commandEncrypt(void) {
	
}

void SysInterface::commandDecrypt(void) {
	
}

void SysInterface::commandCallDLL(void) {
	
}

void SysInterface::commandErrors(void) {
	
}

void SysInterface::commandSetWindow(void) {
    string quit = cb->popValue().toString();
    uint32_t mode = cb->popValue().toInt();
    string caption = "CBEnchanted: " + cb->popValue().toString();
	
	if (quit != "") {
		cout << "FIXME: setWindow quitmsg" << endl;
	}
	
	cb->getWindow()->SetTitle(caption);
}

void SysInterface::commandEnd(void) {
	cb->stop();
}

void SysInterface::functionDate(void) {
	
}

void SysInterface::functionTime(void) {
	
}

void SysInterface::functionTimer(void) {
	cb->pushValue((int32_t)clock());
}

void SysInterface::functionCommandLine(void) {
#ifdef WIN32
	cb->pushValue(string(GetCommandLineA()));
#else
	assert("Linux CommandLine uncomplete" != 0)
#endif
}

void SysInterface::functionGetEXEName(void) {
	
}

void SysInterface::functionFPS(void) {
    cb->pushValue(cb->getFPS());
}

void SysInterface::functionCrc32(void) {
	
}
