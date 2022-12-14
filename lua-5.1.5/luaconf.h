/*
** $Id: luaconf.h,v 1.82.1.7 2008/02/11 16:25:08 roberto Exp $
** Configuration file for Lua
** See Copyright Notice in lua.h
*/
#include <stdint.h>
#ifndef lconfig_h
#define lconfig_h

#include <limits.h>
#include <stddef.h>

#define LUA_PATH "LUA_PATH"
#define LUA_CPATH "LUA_CPATH"
#define LUA_INIT "LUA_INIT"

#define LUA_ROOT "./"
#define LUA_LDIR LUA_ROOT
#define LUA_CDIR LUA_ROOT
#define LUA_PATH_DEFAULT \
	"./?.lua;" LUA_LDIR "?.lua;" LUA_LDIR "?/init.lua;" LUA_CDIR "?.lua;" LUA_CDIR "?/init.lua"
#define LUA_CPATH_DEFAULT \
	"./?.so;" LUA_CDIR "?.so;" LUA_CDIR "loadall.so"
#endif

#define LUA_DIRSEP "/"
#define LUA_PATHSEP ";"
#define LUA_PATH_MARK "?"
#define LUA_EXECDIR "!"
#define LUA_IGMARK "-"

#define LUA_INTEGER int32_t

#define LUA_API extern

/* more often than not the libs go together with the core */
#define LUALIB_API LUA_API
#define LUAI_FUNC extern
#define LUAI_DATA extern

/*
@@ LUA_QL describes how error messages quote program elements.
** CHANGE it if you want a different appearance.
*/
#define LUA_QL(x) "'" x "'"
#define LUA_QS LUA_QL("%s")

/*
@@ LUA_IDSIZE gives the maximum size for the description of the source
@* of a function in debug information.
** CHANGE it if you want a different size.
*/
#define LUA_IDSIZE 60

/*
** {==================================================================
** Stand-alone configuration
** ===================================================================
*/

/*
@@ LUA_PROMPT is the default prompt used by stand-alone Lua.
@@ LUA_PROMPT2 is the default continuation prompt used by stand-alone Lua.
** CHANGE them if you want different prompts. (You can also change the
** prompts dynamically, assigning to globals _PROMPT/_PROMPT2.)
*/
#define LUA_PROMPT "> "
#define LUA_PROMPT2 ">> "

/*
@@ LUA_PROGNAME is the default name for the stand-alone Lua program.
** CHANGE it if your stand-alone interpreter has a different name and
** your system is not able to detect that name automatically.
*/
#define LUA_PROGNAME "lua"

/*
@@ LUA_MAXINPUT is the maximum length for an input line in the
@* stand-alone interpreter.
** CHANGE it if you need longer lines.
*/
#define LUA_MAXINPUT 512

#define LUAI_GCPAUSE 200 /* 200% (wait memory to double before next GC) */
#define LUAI_GCMUL 200	 /* GC runs 'twice the speed' of memory allocation */

/*
@@ LUA_COMPAT_GETN controls compatibility with old getn behavior.
** CHANGE it (define it) if you want exact compatibility with the
** behavior of setn/getn in Lua 5.0.
*/
#undef LUA_COMPAT_GETN

/*
@@ LUA_COMPAT_LOADLIB controls compatibility about global loadlib.
** CHANGE it to undefined as soon as you do not need a global 'loadlib'
** function (the function is still available as 'package.loadlib').
*/
#undef LUA_COMPAT_LOADLIB

/*
@@ LUA_COMPAT_VARARG controls compatibility with old vararg feature.
** CHANGE it to undefined as soon as your programs use only '...' to
** access vararg parameters (instead of the old 'arg' table).
*/
#undef LUA_COMPAT_VARARG

/*
@@ LUA_COMPAT_MOD controls compatibility with old math.mod function.
** CHANGE it to undefined as soon as your programs use 'math.fmod' or
** the new '%' operator instead of 'math.mod'.
*/
#undef LUA_COMPAT_MOD

/*
@@ LUA_COMPAT_LSTR controls compatibility with old long string nesting
@* facility.
** CHANGE it to 2 if you want the old behaviour, or undefine it to turn
** off the advisory error when nesting [[...]].
*/
#undef LUA_COMPAT_LSTR 1

/*
@@ LUA_COMPAT_GFIND controls compatibility with old 'string.gfind' name.
** CHANGE it to undefined as soon as you rename 'string.gfind' to
** 'string.gmatch'.
*/
#undef LUA_COMPAT_GFIND

/*
@@ LUA_COMPAT_OPENLIB controls compatibility with old 'luaL_openlib'
@* behavior.
** CHANGE it to undefined as soon as you replace to 'luaL_register'
** your uses of 'luaL_openlib'
*/
#undef LUA_COMPAT_OPENLIB

#define luai_apicheck(L, o) \
	{                       \
		(void)L;            \
	}

/*
@@ LUAI_BITSINT defines the number of bits in an int.
** CHANGE here if Lua cannot automatically detect the number of bits of
** your machine. Probably you do not need to change this.
*/
/* avoid overflows in comparison */
#if INT_MAX - 20 < 32760
#define LUAI_BITSINT 16
#elif INT_MAX > 2147483640L
/* int has at least 32 bits */
#define LUAI_BITSINT 32
#else
#error "you must define LUA_BITSINT with number of bits in an integer"
#endif

/*
@@ LUAI_UINT32 is an unsigned integer with at least 32 bits.
@@ LUAI_INT32 is an signed integer with at least 32 bits.
@@ LUAI_UMEM is an unsigned integer big enough to count the total
@* memory used by Lua.
@@ LUAI_MEM is a signed integer big enough to count the total memory
@* used by Lua.
** CHANGE here if for some weird reason the default definitions are not
** good enough for your machine. (The definitions in the 'else'
** part always works, but may waste space on machines with 64-bit
** longs.) Probably you do not need to change this.
*/
#if LUAI_BITSINT >= 32
#define LUAI_UINT32 unsigned int
#define LUAI_INT32 int
#define LUAI_MAXINT32 INT_MAX
#define LUAI_UMEM size_t
#define LUAI_MEM ptrdiff_t
#else
/* 16-bit ints */
#define LUAI_UINT32 unsigned long
#define LUAI_INT32 long
#define LUAI_MAXINT32 LONG_MAX
#define LUAI_UMEM unsigned long
#define LUAI_MEM long
#endif

/*
@@ LUAI_MAXCALLS limits the number of nested calls.
** CHANGE it if you need really deep recursive calls. This limit is
** arbitrary; its only purpose is to stop infinite recursion before
** exhausting memory.
*/
#define LUAI_MAXCALLS 1000

/*
@@ LUAI_MAXCSTACK limits the number of Lua stack slots that a C function
@* can use.
** CHANGE it if you need lots of (Lua) stack space for your C
** functions. This limit is arbitrary; its only purpose is to stop C
** functions to consume unlimited stack space. (must be smaller than
** -LUA_REGISTRYINDEX)
*/
#define LUAI_MAXCSTACK 1000

/*
@@ LUAI_MAXCCALLS is the maximum depth for nested C calls (short) and
@* syntactical nested non-terminals in a program.
*/
#define LUAI_MAXCCALLS 50

/*
@@ LUAI_MAXVARS is the maximum number of local variables per function
@* (must be smaller than 250).
*/
#define LUAI_MAXVARS 50

/*
@@ LUAI_MAXUPVALUES is the maximum number of upvalues per function
@* (must be smaller than 250).
*/
#define LUAI_MAXUPVALUES 20

/*
@@ LUAL_BUFFERSIZE is the buffer size used by the lauxlib buffer system.
*/
#define LUAL_BUFFERSIZE BUFSIZ

/* }================================================================== */

/*
** {==================================================================
@@ LUA_NUMBER is the type of numbers in Lua.
** CHANGE the following definitions only if you want to build Lua
** with a number type different from double. You may also need to
** change lua_number2int & lua_number2integer.
** ===================================================================
*/

#undef LUA_NUMBER_DOUBLE
#define LUA_NUMBER int32_t

/*
@@ LUAI_UACNUMBER is the result of an 'usual argument conversion'
@* over a number.
*/
#define LUAI_UACNUMBER LUA_NUMBER

/*
@@ LUA_NUMBER_SCAN is the format for reading numbers.
@@ LUA_NUMBER_FMT is the format for writing numbers.
@@ lua_number2str converts a number to a string.
@@ LUAI_MAXNUMBER2STR is maximum size of previous conversion.
@@ lua_str2number converts a string to a number.
*/
#define LUA_NUMBER_SCAN "%d"
#define LUA_NUMBER_FMT "%d"
#define lua_number2str(s, n) sprintf((s), LUA_NUMBER_FMT, (n))
#define LUAI_MAXNUMBER2STR 16 /* 16 digits, sign, point, and \0 */
#define lua_str2number(s, p) strtol((s), (p), 10)

/*
@@ The luai_num* macros define the primitive operations over numbers.
*/
#if defined(LUA_CORE)
#include <math.h>
#define luai_numadd(a, b) ((a) + (b))
#define luai_numsub(a, b) ((a) - (b))
#define luai_nummul(a, b) ((a) * (b))
#define luai_numdiv(a, b) ((a) / (b))
#define luai_nummod(a, b) ((a)-floor((a) / (b)) * (b))
#define luai_numpow(a, b) (pow(a, b))
#define luai_numunm(a) (-(a))
#define luai_numeq(a, b) ((a) == (b))
#define luai_numlt(a, b) ((a) < (b))
#define luai_numle(a, b) ((a) <= (b))
#define luai_numisnan(a) (!luai_numeq((a), (a)))
#endif

/*
@@ lua_number2int is a macro to convert lua_Number to int.
@@ lua_number2integer is a macro to convert lua_Number to lua_Integer.
** CHANGE them if you know a faster way to convert a lua_Number to
** int (with any rounding method and without throwing errors) in your
** system. In Pentium machines, a naive typecast from double to int
** in C is extremely slow, so any alternative is worth trying.
*/

/* On a Pentium, resort to a trick */
#if defined(LUA_NUMBER_DOUBLE) && !defined(LUA_ANSI) && !defined(__SSE2__) && \
	(defined(__i386) || defined(_M_IX86) || defined(__i386__))

/* On a Microsoft compiler, use assembler */
#if defined(_MSC_VER)

#define lua_number2int(i, d) __asm fld d __asm fistp i
#define lua_number2integer(i, n) lua_number2int(i, n)

/* the next trick should work on any Pentium, but sometimes clashes
   with a DirectX idiosyncrasy */
#else

union luai_Cast
{
	double l_d;
	long l_l;
};
#define lua_number2int(i, d)              \
	{                                     \
		volatile union luai_Cast u;       \
		u.l_d = (d) + 6755399441055744.0; \
		(i) = u.l_l;                      \
	}
#define lua_number2integer(i, n) lua_number2int(i, n)

#endif

/* this option always works, but may be slow */
#else
#define lua_number2int(i, d) ((i) = (int)(d))
#define lua_number2integer(i, d) ((i) = (lua_Integer)(d))

#endif

/* }================================================================== */

/*
@@ LUAI_USER_ALIGNMENT_T is a type that requires maximum alignment.
** CHANGE it if your system requires alignments larger than double. (For
** instance, if your system supports long doubles and they must be
** aligned in 16-byte boundaries, then you should add long double in the
** union.) Probably you do not need to change this.
*/
#define LUAI_USER_ALIGNMENT_T \
	union                     \
	{                         \
		double u;             \
		void *s;              \
		long l;               \
	}

#define LUAI_THROW(L, c) longjmp((c)->b, 1)
#define LUAI_TRY(L, c, a)    \
	if (setjmp((c)->b) == 0) \
	{                        \
		a                    \
	}
#define luai_jmpbuf jmp_buf

/*
@@ LUA_MAXCAPTURES is the maximum number of captures that a pattern
@* can do during pattern-matching.
** CHANGE it if you need more captures. This limit is arbitrary.
*/
#define LUA_MAXCAPTURES 8

/*
@@ lua_tmpnam is the function that the OS library uses to create a
@* temporary name.
@@ LUA_TMPNAMBUFSIZE is the maximum size of a name created by lua_tmpnam.
** CHANGE them if you have an alternative to tmpnam (which is considered
** insecure) or if you want the original tmpnam anyway.  By default, Lua
** uses tmpnam except when POSIX is available, where it uses mkstemp.
*/
#if defined(loslib_c) || defined(luaall_c)

#if defined(LUA_USE_MKSTEMP)
#include <unistd.h>
#define LUA_TMPNAMBUFSIZE 32
#define lua_tmpnam(b, e)              \
	{                                 \
		strcpy(b, "/tmp/lua_XXXXXX"); \
		e = mkstemp(b);               \
		if (e != -1)                  \
			close(e);                 \
		e = (e == -1);                \
	}

#else
#define LUA_TMPNAMBUFSIZE L_tmpnam
#define lua_tmpnam(b, e)         \
	{                            \
		e = (tmpnam(b) == NULL); \
	}
#endif

#endif

#define lua_popen(L, c, m) ((void)((void)c, m), \
							luaL_error(L, LUA_QL("popen") " not supported"), (FILE *)0)
#define lua_pclose(L, file) ((void)((void)L, file), 0)

#define LUAI_EXTRASPACE 0

/*
@@ luai_userstate* allow user-specific actions on threads.
** CHANGE them if you defined LUAI_EXTRASPACE and need to do something
** extra when a thread is created/deleted/resumed/yielded.
*/
#define luai_userstateopen(L) ((void)L)
#define luai_userstateclose(L) ((void)L)
#define luai_userstatethread(L, L1) ((void)L)
#define luai_userstatefree(L) ((void)L)
#define luai_userstateresume(L, n) ((void)L)
#define luai_userstateyield(L, n) ((void)L)

/*
@@ LUA_INTFRMLEN is the length modifier for integer conversions
@* in 'string.format'.
@@ LUA_INTFRM_T is the integer type correspoding to the previous length
@* modifier.
** CHANGE them if your system supports long long or does not support long.
*/

#define LUA_INTFRMLEN "d"
#define LUA_INTFRM_T long

/* =================================================================== */

/*
** Local configuration. You can use this space to add your redefinitions
** without modifying the main part of the file.
*/
