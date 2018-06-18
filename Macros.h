#pragma once

//
// Section attributes
//

// Would be nice to have all the different sections documented

#define BSS_SECTION __attribute__((section (".bss")))

#define SD_CODE_SECTION __attribute__((section (".SD_Code")))

//
// Platform specific attributes
//

// Specifies that the function is an interrupt handler
#define FUNCTION_INTERRUPT(type) __attribute__((interrupt(type)))

// Indicates that the function might be far from the call site,
// and thus might need special calling instructions.
#define FUNCTION_LONGCALL __attribute__((long_call))

// Indicates that the function is likely to be close to the call site,
// and thus can be called via short offset.
#define FUNCTION_SHORTCALL __attribute__((short_call))

// Specifies that the function doesn't need a prologue and epilogue generated for it.
// Used with certain assembly-only functions.
#define FUNCTION_NAKED __attribute__((naked))

//
// Documenting attributes
//

// Marks the type/variable/function as deprecated.
#define DEPRECATED __attribute__((deprecated))

// Marks the type/variable/function as deprecated with the specified deprecation message.
#define DEPRECATED(message) __attribute__((deprecated(message)))

// Specifies that the type/variable/function should be generated, even if it is unused.
#define FORCE_GENERATION __attribute__((used))

//
// Weak attribute
//

// Specifies that the variable/function is a weak symbol that may be overridden by user code.
#define WEAK_SYMBOL __attribute__((weak))

//
// Documenting function attributes
//

// Produces an error if the function is used.
#define FUNCTION_ERROR(message) __attribute__((error(message)))

// Produces a warning if the function is used.
#define FUNCTION_WARNING(message) __attribute__((warning(message)))

// Specifies that the function may be intentionally unused,
// and thus the compiler should not warn about the function being unused.
#define FUNCTION_POSSIBLY_UNUSED __attribute__((unused))

// Specifies that the return value of the function should be used,
// and causes the compiler to issue a warning if it isn't.
#define FUNCTION_WARN_IF_RESULT_UNUSED __attribute__((warn_unused_result))

//
// Optiminsing function attributes
//

// For this function, use the specified optimisation flags and ignore the compiler settings.
#define FUNCTION_OPTIMISE(option) __attribute__((optimize(option)))

// Optimise this function with -O1 settings
#define FUNCTION_OPTIMISE_O1 FUNCTION_OPTIMISE("-O1")

// Optimise this function with -O2 settings
#define FUNCTION_OPTIMISE_O2 FUNCTION_OPTIMISE("-O2")

// Optimise this function with -O3 settings
#define FUNCTION_OPTIMISE_O3 FUNCTION_OPTIMISE("-O3")

// Ignores all optimisation settings
#define FUNCTION_OPTIMISE_NONE FUNCTION_OPTIMISE("-O0")

// Applies optimisations aimed at generating smaller code.
#define FUNCTION_OPTIMISE_SIZE FUNCTION_OPTIMISE("-Os")

// Applies optimisations aimed at generating faster code.
#define FUNCTION_OPTIMISE_FAST FUNCTION_OPTIMISE("-Ofast")

// Applies only optimisations that don't have a negative effect on debugging.
#define FUNCTION_OPTIMISE_DEBUG FUNCTION_OPTIMISE("-Og")

//
// Miscellaneous Optimising function attributes
//

// Forces the function to be inlined if possible, ignoring all optimisation settings.
#define FUNCTION_ALWAYS_INLINE __attribute__((always_inline))

// Forces the function to never be inlined, ignoring all optimisation settings.
#define FUNCTION_NO_INLINE __attribute__((noinline))

// Indicates that the function never returns.
#define FUNCTION_NO_RETURN __attribute__((noreturn))

// Every call within the function will be inlined if possible.
#define FUNCTION_FLATTEN __attribute__((flatten))

// ???
// #define FUNCTION_LEAF __attribute__((leaf))

// Specified that the function relies only on its arguments and possible reads global memory.
// E.g. a lookup table.
#define FUNCTION_PURE __attribute__((pure))

// Specifies that the function relies only on its arguments and doesn't read global memory.
// E.g. a mathematical/logical relation.
#define FUNCTION_CONST __attribute__((const))

// Specifieds that the function is a code hot spot,
// i.e. the function is frequently active.
#define FUNCTION_HOT __attribute__((hot))

// Specifieds that the function is a code cold spot,
// i.e. the function is rarely active.
#define FUNCTION_COLD __attribute__((cold))
