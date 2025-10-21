#pragma once
#pragma comment (lib, "gdiplus.lib")

#include <iostream>
#include <windows.h>
#include <functional>
#include <fstream>
#include <sstream>

#include <xorstr.hpp>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <string>
#include <tlhelp32.h>
#include <vector>
#include <algorithm>
#include <Psapi.h>
#include <locale>
#include <map>
#include <codecvt>

#include <thread>
#include <filesystem>
#include <sddl.h>
#include <lmcons.h>
#include <regex>
#include <WinIoCtl.h>
#include <wininet.h>
#include <Shlwapi.h>
#include <ShlObj.h>
#include <KnownFolders.h>
#include <tchar.h>
#include <mutex>
#include <AclAPI.h>

#include <random>

#include <chrono>
#include <urlmon.h>

#include <taskschd.h>
#include <comutil.h>

#include <ctime>
#include <chrono>

#include <ctime>
#include <shlobj_core.h>
#include <gdiplus.h>

#define SAFE_CALL( fn ) LI_FN( fn ).safe_cached( )
#define _( str ) xorstr( str ).crypt_get( )
