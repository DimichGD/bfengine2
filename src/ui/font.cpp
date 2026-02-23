#include "ui/font.hpp"
#include "core/log.hpp"
#include "io/file.hpp"
#include <type_traits>

BF_BEGIN_NAMESPACE

Font::Font()
{
	struct __attribute__((packed)) Info
	{
		int16_t  font_size;
		uint8_t  bit_field;
		uint8_t  char_set;
		uint16_t stretch_h;
		uint8_t  aa;
		uint8_t  padding_up;
		uint8_t  padding_right;
		uint8_t  padding_down;
		uint8_t  padding_left;
		uint8_t  spacing_horiz;
		uint8_t  spacing_vert;
		uint8_t  outline;
	};

	struct __attribute__((packed)) Common
	{
		uint16_t line_height;
		uint16_t base;
		uint16_t scale_w;
		uint16_t scale_h;
		uint16_t pages;
		uint8_t  bit_field;
		uint8_t  alpha_channel;
		uint8_t  red_channel;
		uint8_t  green_channel;
		uint8_t  blue_channel;
	};

	struct __attribute__((packed)) Char
	{
		uint32_t id;
		uint16_t x;
		uint16_t y;
		uint16_t width;
		uint16_t height;
		int16_t  xoffset;
		int16_t  yoffset;
		int16_t  xadvance;
		uint8_t  page;
		uint8_t  channel;
	};

	struct __attribute__((packed)) Pair
	{
		uint32_t first;
		uint32_t second;
		int16_t  amount;
	};


	File font_file("C:/Users/Dimich/Projects/bfengine2/data/fonts/Arial.fnt");
	if (!font_file.Open())
	{
		Log() << "Failed to open font file";
		return;
	}

	//uint32_t magic = 'B' | ('M' << 8) | ('F' << 16) | (3 << 24); // 54938946
	uint32_t magic;
	font_file.Read(&magic); // 54938946

	uint8_t block_id;
	uint32_t block_size;
	font_file.Read(&block_id);
	font_file.Read(&block_size);
	//Log() << int(block_id) << block_size;

	Info info;
	font_file.Read(&info, sizeof(Info));
	font_file.Skip(block_size - sizeof(Info));

	font_file.Read(&block_id);
	font_file.Read(&block_size);
	//Log() << int(block_id) << block_size;

	Common common;
	font_file.Read(&common, sizeof(Common));

	font_file.Read(&block_id);
	font_file.Read(&block_size);
	font_file.Skip(block_size);

	font_file.Read(&block_id);
	font_file.Read(&block_size);
	std::vector<Char> chars(block_size / 20);
	font_file.Read(chars.data(), block_size);

	if (font_file.Size() > font_file.Pos() + 1) // is it correct?
	{
		font_file.Read(&block_id);
		font_file.Read(&block_size);
		//Log() << int(block_id) << block_size;
	}

	for (auto &c: chars)
	{
		CharData data
		{
			.x = c.x,
			.y = c.y,
			.width = c.width,
			.height = c.height,
			.xoffset = c.xoffset,
			.yoffset = c.yoffset,
			.xadvance = c.xadvance,
		};

		char_data[c.id] = data;
	}

	//Log() << std::has_unique_object_representations_v<Info>;

	/*if (FT_Init_FreeType(&library))
	{
		Log() << "FT_Init_FreeType failed";
		return;
	}

	if (FT_New_Face(library, "C:/Users/Dimich/Projects/bfengine2/data/fonts/Ubuntu-Regular.ttf", 0, &face))
	{
		Log() << "FT_New_Face failed";
		return;
	}

	if (FT_Set_Char_Size(face, 0, 20 * 64, 300, 300))
	{
		Log() << "FT_Set_Char_Size failed";
		return;
	}*/
}

Font::~Font()
{
	//FT_Done_Face(face);
	//FT_Done_FreeType(library);
}

CharData Font::GetChar(uint32_t id)
{
	auto it = char_data.find(id);
	if (it != char_data.end())
	{
		return it->second;
	}

	Log() << "Char" << id << "not found";
	return {};
}

uint32_t Font::MakeString(utf8_view string_view, std::span<float> vertex_buffer)
{
	// TODO: check if scale is 0

	uint32_t text_verts_count = 0;
	float advance = 0.0f;
	//float scale = 1.0f / 512.0f;
	auto v = vertex_buffer.begin();

	for (auto it: string_view)
	{
		CharData char_data = GetChar(it);

		*v++ = float(char_data.xoffset) + advance;
		*v++ = float(char_data.yoffset);
		*v++ = 0.0f;
		*v++ = char_data.x * scale;
		*v++ = char_data.y * scale;

		*v++ = float(char_data.xoffset) + advance;
		*v++ = float(char_data.height) + float(char_data.yoffset);
		*v++ = 0.0f;
		*v++ = char_data.x * scale;
		*v++ = (char_data.y + char_data.height) * scale;

		*v++ = float(char_data.xoffset) + float(char_data.width) + advance;
		*v++ = float(char_data.yoffset);
		*v++ = 0.0f;
		*v++ = (char_data.x + char_data.width) * scale;
		*v++ = char_data.y * scale;

		*v++ = float(char_data.xoffset) + float(char_data.width) + advance;
		*v++ = float(char_data.yoffset);
		*v++ = 0.0f;
		*v++ = (char_data.x + char_data.width) * scale;
		*v++ = char_data.y * scale;

		*v++ = float(char_data.xoffset) + advance;
		*v++ = float(char_data.height) + float(char_data.yoffset);
		*v++ = 0.0f;
		*v++ = char_data.x * scale;
		*v++ = (char_data.y + char_data.height) * scale;

		*v++ = float(char_data.xoffset) + float(char_data.width) + advance;
		*v++ = float(char_data.height) + float(char_data.yoffset);
		*v++ = 0.0f;
		*v++ = (char_data.x + char_data.width) * scale;
		*v++ = (char_data.y + char_data.height) * scale;

		advance += float(char_data.xadvance);
		text_verts_count += 6; // TODO: check for overflow
	}

	return text_verts_count;
}

void Font::SetTextureScale(float scale)
{
	this->scale = scale;
}

std::string_view Font::TextureName() const
{
	//return "C:/Users/Dimich/Projects/bfengine2/data/fonts/Arial.png";
	return "Arial.png";
}

BF_END_NAMESPACE
