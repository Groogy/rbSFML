#pragma once

#include "Object.hpp"
#include "Class.hpp"
#include "Identifier.hpp"

namespace rb
{
    
    // Modules
    Module mKernel       = rb_mKernel;
    Module mComparable   = rb_mComparable;
    Module mEnumerable   = rb_mEnumerable;
    Module mErrno        = rb_mErrno;
    Module mFileTest     = rb_mFileTest;
    Module mGC           = rb_mGC;
    Module mMath         = rb_mMath;
    Module mProcess      = rb_mProcess;
    Module mWaitReadable = rb_mWaitReadable;
    Module mWaitWritable = rb_mWaitWritable;
    
    // Classes
    Class cBasicObject   = rb_cBasicObject;
    Class cObject        = rb_cObject;
    Class cArray         = rb_cArray;
    Class cBignum        = rb_cBignum;
    Class cBinding       = rb_cBinding;
    Class cClass         = rb_cClass;
    //Class cCont          = rb_cCont; // In github but undefined on my Ruby.
    Class cDir           = rb_cDir;
    Class cData          = rb_cData;
    Class cFalseClass    = rb_cFalseClass;
    Class cEncoding      = rb_cEncoding;
    Class cEnumerator    = rb_cEnumerator;
    Class cFile          = rb_cFile;
    Class cFixnum        = rb_cFixnum;
    Class cFloat         = rb_cFloat;
    Class cHash          = rb_cHash;
    Class cInteger       = rb_cInteger;
    Class cIO            = rb_cIO;
    Class cMatch         = rb_cMatch;
    Class cMethod        = rb_cMethod;
    Class cModule        = rb_cModule;
    Class cNameErrorMesg = rb_cNameErrorMesg;
    Class cNilClass      = rb_cNilClass;
    Class cNumeric       = rb_cNumeric;
    Class cProc          = rb_cProc;
    Class cRandom        = rb_cRandom;
    Class cRange         = rb_cRange;
    Class cRational      = rb_cRational;
    Class cComplex       = rb_cComplex;
    Class cRegexp        = rb_cRegexp;
    Class cStat          = rb_cStat;
    Class cString        = rb_cString;
    Class cStruct        = rb_cStruct;
    Class cSymbol        = rb_cSymbol;
    Class cThread        = rb_cThread;
    Class cTime          = rb_cTime;
    Class cTrueClass     = rb_cTrueClass;
    Class cUnboundMethod = rb_cUnboundMethod;
    
    // Exceptions
    Class eException        = rb_eException;
    Class eStandardError    = rb_eStandardError;
    Class eSystemExit       = rb_eSystemExit;
    Class eInterrupt        = rb_eInterrupt;
    Class eSignal           = rb_eSignal;
    Class eFatal            = rb_eFatal;
    Class eArgError         = rb_eArgError;
    Class eEOFError         = rb_eEOFError;
    Class eIndexError       = rb_eIndexError;
    Class eStopIteration    = rb_eStopIteration;
    Class eKeyError         = rb_eKeyError;
    Class eRangeError       = rb_eRangeError;
    Class eIOError          = rb_eIOError;
    Class eRuntimeError     = rb_eRuntimeError;
    Class eSecurityError    = rb_eSecurityError;
    Class eSystemCallError  = rb_eSystemCallError;
    Class eThreadError      = rb_eThreadError;
    Class eTypeError        = rb_eTypeError;
    Class eZeroDivError     = rb_eZeroDivError;
    Class eNotImpError      = rb_eNotImpError;
    Class eNoMemError       = rb_eNoMemError;
    Class eNoMethodError    = rb_eNoMethodError;
    Class eFloatDomainError = rb_eFloatDomainError;
    Class eLocalJumpError   = rb_eLocalJumpError;
    Class eSysStackError    = rb_eSysStackError;
    Class eRegexpError      = rb_eRegexpError;
    Class eEncodingError    = rb_eEncodingError;
    Class eEncCompatError   = rb_eEncCompatError;
    Class eScriptError      = rb_eScriptError;
    Class eNameError        = rb_eNameError;
    Class eSyntaxError      = rb_eSyntaxError;
    Class eLoadError        = rb_eLoadError;
    Class eMathDomainError  = rb_eMathDomainError;
    
    // Objects
    Object Nil   = Qnil;
    Object True  = Qtrue;
    Object False = Qfalse;
    Object Undef = Qundef;
    
    template<typename... Args>
    Object p(const Args&... args);
    
    template<typename... Args>
    Object print(const Args&... args);
    
    template<typename... Args>
    Object puts(const Args&... args);
    
}
