/*
 * File: init.h
 * ------------
 * This file contains code to check whether the Stanford C++ library has been
 * initialized, and if not, to initialize it.
 * This file must be included by every student-facing header in the Stanford
 * C++ library to make sure that the library is initialized before it is used.
 *
 * There used to be a group of files such as private/main.h, main.cpp, and
 * startup.cpp that contained various initialization code.  These were removed
 * and replaced with this style of initialization for the following reasons:
 *
 * - simplicity/consolidation
 * - allow student to NOT include console.h and use plain text console
 *
 * @version 2018/08/28
 * - refactor to use stanfordcpplib namespace and init.cpp
 * @version 2018/07/03
 * - add code to handle Qt GUI library initialization
 * @version 2017/04/25
 * - wrap library initializer in an #ifndef to avoid multiple declaration
 *
 * TODO: figure out how to support both 0-arg and 2-arg main()
 */

#ifndef _init_h
#define _init_h

#include <cstdlib>
#include <stdio.h>

namespace stanfordcpplib {

bool exitEnabled();
void initializeLibrary(int argc, char** argv);
void runMainInThread(int (* mainFunc)(void));
void runMainInThreadVoid(void (* mainFuncVoid)(void));
void setExitEnabled(bool enabled);
void shutdownLibrary();
void staticInitializeLibrary();

#ifndef __StanfordCppLibraryInitializer_created
#define __StanfordCppLibraryInitializer_created
class __StanfordCppLibraryInitializer {
public:
    /*
     * Code to initialize the library.
     * Implemented as a class constructor so that it will run before the
     * student's main function.
     * Here we put anything that we need to initialize during the static
     * phase before main() runs.
     * Presently there is nothing that requires such initialization,
     * so this is blank.
     */
    __StanfordCppLibraryInitializer() {
        staticInitializeLibrary();
    }
};
static __StanfordCppLibraryInitializer __stanfordcpplib_init;
#endif // __StanfordCppLibraryInitializer_created

} // namespace stanfordcpplib




// taken from: http://stackoverflow.com/questions/11761703/overloading-macro-on-number-of-arguments
// get number of arguments with __NARG__
#define __NARG__(...)  __NARG_I_(__VA_ARGS__,__RSEQ_N())
#define __NARG_I_(...) __ARG_N(__VA_ARGS__)
#define __ARG_N( \
      _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
     _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
     _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
     _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
     _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
     _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
     _61,_62,_63,N,...) N
#define __RSEQ_N() \
     63,62,61,60,                   \
     59,58,57,56,55,54,53,52,51,50, \
     49,48,47,46,45,44,43,42,41,40, \
     39,38,37,36,35,34,33,32,31,30, \
     29,28,27,26,25,24,23,22,21,20, \
     19,18,17,16,15,14,13,12,11,10, \
     9,8,7,6,5,4,3,2,1,0

// general definition for any function name
#define _VFUNC_(name, n) name##n
#define _VFUNC(name, n) _VFUNC_(name, n)
#define MAIN(func, ...) _VFUNC(func, __NARG__(__VA_ARGS__)) (__VA_ARGS__)


/*
 * This weird macro converts the student's main() function into
 * a function Main() that is preceded by an inserted actual main()
 * that grabs the program name from argv[0] and does a bit of
 * initialization needed by the Stanford C++ libraries.
 *
 * This should be mostly transparent to the student except if they
 * declare their main function improperly, in which case they may
 * see occasional odd compiler errors about a Main (capital-M) function.
 */
#ifdef SPL_AUTOGRADER_MODE
#define main studentMain
#else // not SPL_AUTOGRADER_MODE
#undef main

// __initializeStanfordCppLibraryQt is defined in qgui.cpp/h;
// it initializes the Qt GUI library subsystems and Qt graphical console as needed
#define main main(int argc, char** argv) { \
        extern int Main(); \
        stanfordcpplib::initializeLibrary(argc, argv); \
        stanfordcpplib::runMainInThread(Main); \
        stanfordcpplib::shutdownLibrary(); \
        return 0; \
    } \
    int Main

#endif  // SPL_AUTOGRADER_MODE
extern int mainWrapper(int argc, char **argv);

// bypass std::exit function
namespace std {
void __stanfordcpplib__exitLibrary(int status);
} // namespace std

#define __EXIT __std_exit_function_
#define exit __stanfordcpplib__exitLibrary

#ifdef SPL_OVERLOAD_PROBLEMATIC_POINTER_ARITHMETIC
#include "pointers.h"
#endif // SPL_OVERLOAD_PROBLEMATIC_POINTER_ARITHMETIC

#endif // _init_h
