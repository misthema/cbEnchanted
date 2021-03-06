#include <iostream>
#include <allegro5/allegro.h>
#include "cbenchanted.h"

#ifndef CBE_LIB
int main(int argc, char** argv) {
	CBEnchanted cb;
	#ifdef TEST
	if (argc >= 2) {
		if (cb.init(argv[1], argc, argv)) {
			cb.run();
			cb.cleanup();
		}
		al_uninstall_system();
	}
	else {
		std::cerr << "Usage: CBEnchanted file.exe" << std::endl;
		return -1;
	}
	#else
		if (cb.init(NULL, argc, argv)) {
			cb.run();
			cb.cleanup();
		}
		al_uninstall_system();
	#endif


	return 0;
}

#endif

