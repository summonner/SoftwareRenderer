#include "framework.h"
#include "ILesson.h"

namespace NeHe
{
	AUX_RGBImageRec* LoadBMP( LPCSTR filePath )
	{
		return auxDIBImageLoad( CA2CT( filePath ) );
	}
}