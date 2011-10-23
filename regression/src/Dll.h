#ifndef DLL_H
#define DLL_H

#ifdef WIN32
#if defined EXPORTS
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif
#else // Linux, etc...
#define DLL
#endif

#endif //DLL_H
