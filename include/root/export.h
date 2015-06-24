#pragma once

#if defined(RootLibraryExport)
#define RootLibrary __declspec(dllexport)
#else
#define RootLibrary __declspec(dllimport)
#endif