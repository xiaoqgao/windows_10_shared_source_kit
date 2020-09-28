#include "dxfmt.h"

D3DFORMAT_RECORD DXGraphicsFormats[] =
{
	{D3DFMT_UNKNOWN, "D3DFMT_UNKNOWN"},
	{D3DFMT_R8G8B8, "D3DFMT_R8G8B8"},
	{D3DFMT_A8R8G8B8, "D3DFMT_A8R8G8B8"},
	{D3DFMT_X8R8G8B8, "D3DFMT_X8R8G8B8"},
	{D3DFMT_R5G6B5, "D3DFMT_R5G6B5"},
	{D3DFMT_X1R5G5B5, "D3DFMT_X1R5G5B5"},
	{D3DFMT_A1R5G5B5, "D3DFMT_A1R5G5B5"},
	{D3DFMT_A4R4G4B4, "D3DFMT_A4R4G4B4"},
	{D3DFMT_R3G3B2, "D3DFMT_R3G3B2"},
	{D3DFMT_A8, "D3DFMT_A8"},
	{D3DFMT_A8R3G3B2, "D3DFMT_A8R3G3B2"},
	{D3DFMT_X4R4G4B4, "D3DFMT_X4R4G4B4"},
	{D3DFMT_A8P8, "D3DFMT_A8P8"},
	{D3DFMT_P8, "D3DFMT_P8"},
	{D3DFMT_L8, "D3DFMT_L8"},
	{D3DFMT_A8L8, "D3DFMT_A8L8"},
	{D3DFMT_A4L4, "D3DFMT_A4L4"},
	{D3DFMT_V8U8, "D3DFMT_V8U8"},
	{D3DFMT_L6V5U5, "D3DFMT_L6V5U5"},
	{D3DFMT_X8L8V8U8, "D3DFMT_X8L8V8U8"},
	{D3DFMT_UYVY, "D3DFMT_UYVY"},
	{D3DFMT_YUY2, "D3DFMT_YUY2"},
	{D3DFMT_DXT1, "D3DFMT_DXT1"},
	{D3DFMT_DXT2, "D3DFMT_DXT2"},
	{D3DFMT_DXT3, "D3DFMT_DXT3"},
	{D3DFMT_DXT4, "D3DFMT_DXT4"},
	{D3DFMT_DXT5, "D3DFMT_DXT5"},
	{D3DFMT_D16, "D3DFMT_D16"},
	{D3DFMT_VERTEXDATA, "D3DFMT_VERTEXDATA"},
	{D3DFMT_INDEX16, "D3DFMT_INDEX16"},
	{D3DFMT_INDEX32, "D3DFMT_INDEX32"}
};

const char *D3DFormatName(D3DFORMAT d3dfmt)
{
	for
	(
		UINT uiFormatRecordIndex = 0;
		uiFormatRecordIndex < (sizeof(DXGraphicsFormats) / sizeof(DXGraphicsFormats[0]));
		++uiFormatRecordIndex
	)
	{
		if (DXGraphicsFormats[uiFormatRecordIndex].d3dformat == d3dfmt)
			return (DXGraphicsFormats[uiFormatRecordIndex].szName);
	}

	return "(Unrecognized Format)";
}