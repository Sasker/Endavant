#ifndef DEFINES_H_
#define DEFINES_H_


#define SDL_NO_COMPAT


// ACTIVATE DLL EXPORTING
#define ENDAVANT_DLL
#define ENDAVANT_DLL_EXPORTS

//
// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define ENDAVANT_HELPER_DLL_IMPORT __declspec(dllimport)
  #define ENDAVANT_HELPER_DLL_EXPORT __declspec(dllexport)
  #define ENDAVANT_HELPER_DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define ENDAVANT_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define ENDAVANT_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define ENDAVANT_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define ENDAVANT_HELPER_DLL_IMPORT
    #define ENDAVANT_HELPER_DLL_EXPORT
    #define ENDAVANT_HELPER_DLL_LOCAL
  #endif
#endif

// Now we use the generic helper definitions above to define FOX_API and FOX_LOCAL.
// FOX_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// FOX_LOCAL is used for non-api symbols.

#ifdef ENDAVANT_DLL // defined if FOX is compiled as a DLL
#ifdef ENDAVANT_DLL_EXPORTS // defined if we are building the FOX DLL (instead of using it)
    #define ENDAVANT_API ENDAVANT_HELPER_DLL_EXPORT
  #else
    #define ENDAVANT_API ENDAVANT_HELPER_DLL_IMPORT
  #endif
  #define ENDAVANT_LOCAL ENDAVANT_HELPER_DLL_LOCAL
#else // FOX_DLL is not defined: this means FOX is a static lib.
  #define ENDAVANT_API
  #define ENDAVANT_LOCAL
#endif // FOX_DLL


#endif /* DEFINES_H_ */
