#pragma once
#ifndef COGRA_SYSTEM_H
#define COGRA_SYSTEM_H

#ifdef WIN32
#define COGRA_WINDOWS
#else
#define COGRA_LINUX
#endif

#ifdef _MSC_VER
#define COGRA_VISUAL_STUDIO
#endif

#endif