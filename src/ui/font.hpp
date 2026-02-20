#pragma once
#include "core/defines.hpp"
#include "utils/utf8.hpp"
//#include <ft2build.h>
//#include FT_FREETYPE_H
#include <cstdint>
#include <span>
#include <string_view>
#include <map>

BF_BEGIN_NAMESPACE

struct CharData
{
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
	int16_t  xoffset;
	int16_t  yoffset;
	int16_t  xadvance;
};

class Font
{
public:
	Font();
	~Font();
	BF_NON_MOVABLE(Font)
	BF_NON_COPYABLE(Font)

	CharData GetChar(uint32_t id);
	uint32_t MakeString(utf8_view string_view, std::span<float> vertex_buffer);

	void SetTextureScale(float scale);
	std::string_view TextureName() const;

private:
	std::map<uint32_t, CharData> char_data;
	float scale = 0.0f;
	//FT_Library library;
	//FT_Face face;
};

BF_END_NAMESPACE
