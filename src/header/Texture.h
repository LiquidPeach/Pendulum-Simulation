#pragma once

#include <string>

class Texture {

private:
	unsigned int   m_RenderID;
	std::string    m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP; // Bits Per Pixel
public:
	Texture();
	Texture(const std::string& path);
	~Texture();

	void CreateTexture(const std::string& path);
	inline int GetWidth()  const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	void DeleteTexture() const;
};