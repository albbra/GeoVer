#pragma once
#ifndef COGRA_UI_CUBICBEZIERPATCHLOADER_H
#define COGRA_UI_CUBICBEZIERPATCHLOADER_H
#include <vector>
#include <cogra/types.h>
namespace cogra
{
namespace io
{
namespace CubicBezierPatchLoader
{

std::vector<f32vec4> fromRib4(const char* fileName);

std::vector<f32vec4> fromText(const char* fileName);

};
}
}
#endif