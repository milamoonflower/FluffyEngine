#pragma once
#include <string>

struct _TTF_Font;

/**
 * Simple RAII wrapper for a _TTF_Font
 */
class Font final
{
public:
	explicit Font(const std::string& fullPath, unsigned int size);
	~Font();

	inline _TTF_Font* GetFont() const { return m_font; }

	Font(const Font&) = delete;
	Font(Font&&) = delete;
	Font& operator= (const Font&) = delete;
	Font& operator= (const Font&&) = delete;
private:
	_TTF_Font* m_font;
};
