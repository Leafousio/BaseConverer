
#include "utils.cpp"
#include <cmath>

static void Color(u32 r, u32 g, u32 b) {
	unsigned int* pixel = (u32*)render_state.memory;
	unsigned int hexCode = (r << 16) | (g << 8) | b;

	for (int y = 0; y < render_state.height; ++y) {
		for (int x = 0; x < render_state.width; ++x) {
			*pixel++ = hexCode;
		}
	}
}

static void DrawRectInPixels(int x0, int y0, int x1, int y1, u32 r, u32 g, u32 b)
{
	x0 = Clamp(x0, 0, render_state.width);
	x1 = Clamp(x1, 0, render_state.width);

	y0 = Clamp(y0, 0, render_state.height);
	y1 = Clamp(y1, 0, render_state.height);


	u32 hexCode = (r << 16) | (g << 8) | b;

	for (int y = y0; y < y1; ++y) {

		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;

		for (int x = x0; x < x1; ++x) {
			*pixel++ = hexCode;

		}
	}
}


static void DrawRect(float x0, float y0, float half_size_x, float half_size_y, u32 r, u32 g, u32 b)
{
	int x = x0 - half_size_x;
	int x1 = x0 + half_size_x;
	int y = y0 - half_size_y;
	int y1 = y0 + half_size_y;

	DrawRectInPixels(x, y, x1, y1, r, g, b);
}


static void Gradient(u32 r, u32 g, u32 b, u32 r1, u32 g1, u32 b1) {

	u32* pixel = (u32*)render_state.memory;



	int toR, toG, toB;

	for (int y = 0; y < render_state.height; ++y) {
		for (int x = 0; x < render_state.width; ++x) {

			toR = r + (int)((r1 - r) * ((float)y / (float)render_state.height));
			toG = g + (int)((g1 - g) * ((float)y / (float)render_state.height));
			toB = b + (int)((b1 - b) * ((float)y / (float)render_state.height));

			*pixel++ = (toR << 16) | (toG << 8) | toB;

		}
	}
}

const u8 LETTERHEIGHT = 5;
const u8 LETTERWIDTH = 4;

const char* letters[][5] = {
	" 00",
	"0  0",
	"0000",
	"0  0",
	"0  0",


	"000",
	"0  0",
	"000",
	"0  0",
	"000",

	" 000",
	"0",
	"0",
	"0",
	" 000",

	"000",
	"0  0",
	"0  0",
	"0  0",
	"000",

	"0000",
	"0",
	"000",
	"0",
	"0000",

	"0000",
	"0",
	"000",
	"0",
	"0",

	" 000",
	"0   ",
	"0 00",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",

	"000",
	" 0 ",
	" 0 ",
	" 0 ",
	"000",

	" 000",
	"   0",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0 0",
	"00",
	"0 0",
	"0  0",

	"0",
	"0",
	"0",
	"0",
	"0000",

	"00 00",
	"0 0 0",
	"0 0 0",
	"0   0",
	"0   0",

	"00  0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0  00",

	"0000",
	"0  0",
	"0  0",
	"0  0",
	"0000",

	" 000",
	"0  0",
	"000",
	"0",
	"0",


	"0000",
	"0  0",
	"0  0",
	"0  0",
	"0000",

	"000",
	"0  0",
	"000",
	"0  0",
	"0  0",

	" 000",
	"0 ",
	" 00",
	"   0",
	"000 ",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",

	"0  0",
	"0  0",
	"0  0",
	"0  0",
	" 00",

	"0   0",
	"0   0",
	"0   0",
	" 0 0",
	"  0",

	"0   0 ",
	"0   0",
	"0 0 0",
	"0 0 0",
	" 0 0 ",

	"0   0",
	" 0 0",
	"  0",
	" 0 0",
	"0   0",

	"0   0",
	" 0 0",
	"  0",
	"  0",
	"  0",

	"0000",
	"   0",
	" 0",
	"0",
	"0000",


	"",
	"",
	"",
	"",
	"0",

	"   0",
	"  0",
	" 0",
	"0",
	"0",

	"0",
	"",
	"",
	"",
	"0",

	"0000",
	"0  0",
	"0  0",
	"0  0",
	"0000",

	" 00",
	"0 0",
	"  0",
	"  0",
	"  0",

	" 00",
	"0  0",
	"  0",
	" 0 ",
	"0000",

	"000",
	"   0",
	" 00",
	"   0",
	"000 ",

	"0  0",
	"0  0",
	"0000",
	"   0",
	"   0",

	"0000",
	"0   ",
	"0000",
	"   0",
	"0000",

	"0000",
	"0   ",
	"0000",
	"0  0",
	"0000",

	"0000",
	"   0",
	"  0",
	"  0",
	"  0",

	"0000",
	"0  0",
	"0000",
	"0  0",
	"0000",

	"0000",
	"0  0",
	"0000",
	"   0",
	"0000",
};

void DrawPixelText(const char* text, float x, float y, float size, u32 r, u32 g, u32 b, float treshold = 0.6f) {
	float half_size = size * .5f;
	float original_y = y;

	while (*text) {
		if (*text != 32) {
			const char** letter;
			if (*text == 47) letter = letters[27];
			else if (*text == 46) letter = letters[26];
			else if (*text == ':') letter = letters[28];
			else if (*text >= 48 && *text <= 57) letter = letters[*text - 48 + 29];
			else letter = letters[*text - (int)'A']; //convert ascii table index to list index
			float original_x = x;

			for (int i = 0; i < 5; i++) {
				const char* row = letter[i];


				while (*row) {
					if (*row == '0') {
						DrawRect(x, y, half_size, half_size, r, g, b);
					}
					x += size;
					row++;

				}
				y -= size;
				x = original_x;
			}
		}
		text++;

		x += size * treshold;
		y = original_y;
	}
};