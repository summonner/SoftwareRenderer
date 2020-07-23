#pragma once

#undef WINGDIAPI
#define WINGDIAPI
#include <gl/gl.h>
#include "../gl/AUX_RGBImageRec.h"

#include "Renderer/IRenderer.h"
extern std::shared_ptr<IRenderer> _renderer;