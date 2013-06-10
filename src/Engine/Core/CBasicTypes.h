#ifndef _CBASIC_TYPES_H_
#define _CBASIC_TYPES_H_

#include <cstdint>
#include <climits>


typedef std::int8_t			s8;
typedef std::uint8_t		u8;

typedef std::int16_t		s16;
typedef std::uint16_t		u16;

typedef std::int32_t		s32;
typedef std::uint32_t		u32;

typedef std::int64_t		s64;
typedef std::uint64_t		u64;

static_assert(sizeof(float)*CHAR_BIT==32, "float is not 32 bit on this architecture, fix the f32 typedef.");
typedef float 				f32;

static_assert(sizeof(double)*CHAR_BIT==64, "double is not 64 bit on this architecture, fix the f64 typedef.");
typedef double				f64;






#endif /* _CBASIC_TYPES_H_ */
