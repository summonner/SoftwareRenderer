﻿// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <mmsystem.h>
#include <vfw.h>												// Header File For Video For Windows
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <atlbase.h>

#include <vector>
#include <unordered_map>
#include <stack>

#include <memory>
#include <algorithm>
#include <cmath>
#include <functional>
#include <iterator>
#include <string>

#include "Math/MathExt.h"
#include "Math/Vector.h"
#include "Math/Degree.h"
#include "Math/Radian.h"
#include "Util/Dictionary.hpp"

#undef max
#undef min