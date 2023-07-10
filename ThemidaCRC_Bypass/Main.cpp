#include <Windows.h>
#include "Themida.hpp"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
	{
		if (!Themida::InitialiseCRCBypass()) {
			MessageBoxA(NULL, "Failed to initialise CRC Bypass", "Title", MB_ICONERROR);
		}
		break;
	}
	}
	return TRUE;
}