#pragma once
#ifndef COGRA_TYPES
#define COGRA_TYPES
#include <cogra/system.h>
#include <cstdint>
#pragma warning( push )
#pragma warning( disable: 4310)
#pragma warning( disable: 4701)
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_precision.hpp>
#pragma warning (pop)
namespace cogra
{
typedef uint8_t     uint8;
typedef uint16_t    uint16;
typedef uint32_t    uint32;
typedef uint64_t    uint64;

typedef int8_t      int8;
typedef int16_t     int16;
typedef int32_t     int32;
typedef int64_t     int64;

typedef float       float32;
typedef double      float64;

typedef glm::vec2   f32vec2;
typedef glm::vec3   f32vec3;
typedef glm::vec4   f32vec4;

typedef glm::dvec2  f64vec2;
typedef glm::dvec3  f64vec3;
typedef glm::dvec4  f64vec4;

typedef glm::u64vec1	ui64vec1;
typedef glm::u64vec2	ui64vec2;
typedef glm::u64vec3	ui64vec3;
typedef glm::u64vec4	ui64vec4;

typedef glm::i64vec1	i64vec1;
typedef glm::i64vec2	i64vec2;
typedef glm::i64vec3	i64vec3;
typedef glm::i64vec4	i64vec4;

typedef glm::uvec1	ui32vec1;
typedef glm::uvec2  ui32vec2;
typedef glm::uvec3  ui32vec3;
typedef glm::uvec4  ui32vec4;

typedef glm::ivec1  i32vec1;
typedef glm::ivec2  i32vec2;
typedef glm::ivec3  i32vec3;
typedef glm::ivec4  i32vec4;

typedef glm::u16vec1	ui16vec1;
typedef glm::u16vec2	ui16vec2;
typedef glm::u16vec3	ui16vec3;
typedef glm::u16vec4	ui16vec4;

typedef glm::i16vec1	i16vec1;
typedef glm::i16vec2	i16vec2;
typedef glm::i16vec3	i16vec3;
typedef glm::i16vec4	i16vec4;

typedef glm::u8vec1	ui8vec1;
typedef glm::u8vec2	ui8vec2;
typedef glm::u8vec3	ui8vec3;
typedef glm::u8vec4	ui8vec4;

typedef glm::i8vec1	i8vec1;
typedef glm::i8vec2	i8vec2;
typedef glm::i8vec3	i8vec3;
typedef glm::i8vec4	i8vec4;

typedef glm::bvec2  bvec2;
typedef glm::bvec3  bvec3;
typedef glm::bvec4  bvec4;

typedef glm::mat2   f32mat2;
typedef glm::mat3   f32mat3;
typedef glm::mat4   f32mat4;

typedef glm::dmat2  f64mat2;
typedef glm::dmat3  f64mat3;
typedef glm::dmat4  f64mat4;

typedef glm::quat   f32quat;

// Short Types
typedef uint8_t     ui8;
typedef uint16_t    ui16;
typedef uint32_t    ui32;
typedef uint64_t    ui64;

typedef int8_t      i8;
typedef int16_t     i16;
typedef int32_t     i32;
typedef int64_t     i64;

typedef float       f32;
typedef double      f64;

typedef glm::vec2   f32v2;
typedef glm::vec3   f32v3;
typedef glm::vec4   f32v4;

typedef glm::dvec2  f64v2;
typedef glm::dvec3  f64v3;
typedef glm::dvec4  f64v4;

typedef glm::u64vec1	ui64v1;
typedef glm::u64vec2	ui64v2;
typedef glm::u64vec3	ui64v3;
typedef glm::u64vec4	ui64v4;

typedef glm::i64vec1	i64v1;
typedef glm::i64vec2	i64v2;
typedef glm::i64vec3	i64v3;
typedef glm::i64vec4	i64v4;

typedef glm::uvec1	ui32v1;
typedef glm::uvec2  ui32v2;
typedef glm::uvec3  ui32v3;
typedef glm::uvec4  ui32v4;

typedef glm::ivec1  i32v1;
typedef glm::ivec2  i32v2;
typedef glm::ivec3  i32v3;
typedef glm::ivec4  i32v4;

typedef glm::u16vec1	ui16v1;
typedef glm::u16vec2	ui16v2;
typedef glm::u16vec3	ui16v3;
typedef glm::u16vec4	ui16v4;

typedef glm::i16vec1	i16v1;
typedef glm::i16vec2	i16v2;
typedef glm::i16vec3	i16v3;
typedef glm::i16vec4	i16v4;

typedef glm::u8vec1	ui8v1;
typedef glm::u8vec2	ui8v2;
typedef glm::u8vec3	ui8v3;
typedef glm::u8vec4	ui8v4;

typedef glm::i8vec1	i8v1;
typedef glm::i8vec2	i8v2;
typedef glm::i8vec3	i8v3;
typedef glm::i8vec4	i8v4;

typedef glm::bvec2  bv2;
typedef glm::bvec3  bv3;
typedef glm::bvec4  bv4;

typedef glm::mat2   f32m2;
typedef glm::mat3   f32m3;
typedef glm::mat4   f32m4;

typedef glm::dmat2  f64m2;
typedef glm::dmat3  f64m3;
typedef glm::dmat4  f64m4;

typedef glm::quat   f32q;


}

#ifdef COGRA_VISUAL_STUDIO
#define PACKED( STRUCT_TO_PACK ) __pragma( pack(push, 1) ) STRUCT_TO_PACK __pragma( pack(pop) )
#else
#define PACKED( STRUCT_TO_PACK ) STRUCT_TO_PACK __attribute__((__packed__))
#endif

#endif