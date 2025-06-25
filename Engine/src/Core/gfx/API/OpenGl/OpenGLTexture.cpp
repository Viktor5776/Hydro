#include "OpenGLTexture.h"
#include "../../../utl/Assert.h"


namespace hydro::gfx
{

	OpenGLTexture::OpenGLTexture(unsigned int width, unsigned int height, Type type, Format format, const void* data)
		:
		type_(type),
		format_(format),
		width_(width),
		height_(height)
	{
		CreateTexture(data);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		if (texture_ != 0) {
			glDeleteTextures(1, &texture_);
		}
	}

	void OpenGLTexture::CreateTexture(const void* data)
	{
		if (texture_ != 0) {
			glDeleteTextures(1, &texture_);
			texture_ = 0;
		}

		glGenTextures(1, &texture_);
		glBindTexture(GetGLType(type_), texture_);

		if (type_ == Type::Texture2DMultisample) {
			glTexImage2DMultisample(
				GetGLType(type_),
				samples_,
				GetGLInternalFormat(format_),
				width_, height_,
				GL_FALSE
			);
		}
		else {

			glTexImage2D(
				GetGLType(type_),
				0, GetGLInternalFormat(format_),
				width_, height_, 0,
				GetGLPixelFormat(format_),
				GetGLPixelType(format_),
				data
			);

			SetFilter(min_, mag_);
			SetWrap(s_, t_);
		}

		Unbind();
	}

	void OpenGLTexture::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GetGLType(type_), texture_);
	}

	void OpenGLTexture::Unbind() const
	{
		glBindTexture(GetGLType(type_), 0);
	}

	void OpenGLTexture::Resize(unsigned int width, unsigned int height)
	{
		if (width == width_ && height == height_)
			return;

		width_ = width;
		height_ = height;

		CreateTexture(nullptr);
	}

	void OpenGLTexture::SetData(const void* data, size_t size)
	{
		hass(size == width_ * height_ * BytesPerPixel(format_)).msg(L"Data size does not match texture dimensions.");

		glBindTexture(GetGLType(type_), texture_);
		glTexSubImage2D(GetGLType(type_), 0, 0, 0, width_, height_, GetGLPixelFormat(format_), GetGLPixelType(format_), data);
		Unbind();
	}


	void OpenGLTexture::SetFilter(Filter min, Filter mag)
	{
		min_ = min;
		mag_ = mag;

		glBindTexture(GetGLType(type_), texture_);
		glTexParameteri(GetGLType(type_), GL_TEXTURE_MIN_FILTER, ConvertFilter(min));
		glTexParameteri(GetGLType(type_), GL_TEXTURE_MAG_FILTER, ConvertFilter(mag));
		Unbind();
	}

	void OpenGLTexture::SetWrap(Wrap s, Wrap t)
	{
		s_ = s;
		t_ = t;

		glBindTexture(GetGLType(type_), texture_);
		glTexParameteri(GetGLType(type_), GL_TEXTURE_WRAP_S, ConvertWrap(s));
		glTexParameteri(GetGLType(type_), GL_TEXTURE_WRAP_T, ConvertWrap(t));
		Unbind();
	}

	void OpenGLTexture::SetSamples(unsigned int samples)
	{
		hass(Type::Texture2DMultisample == type_).msg(L"Cannot set samples on non-multisampled texture");
		samples_ = samples;

		CreateTexture(nullptr);
	}

	unsigned int OpenGLTexture::GetWidth() const
	{
		return width_;
	}

	unsigned int OpenGLTexture::GetHeight() const
	{
		return height_;
	}

	Texture::Format OpenGLTexture::GetFormat() const
	{
		return format_;
	}

	Texture::Type OpenGLTexture::GetType() const
	{
		return type_;
	}

	constexpr GLenum OpenGLTexture::GetGLInternalFormat(Format format)
	{
		switch (format) {
		case hydro::gfx::Texture::Format::RGBA8: return GL_RGBA8;
		case hydro::gfx::Texture::Format::RED_INTEGER: return GL_R32I;
		case hydro::gfx::Texture::Format::DEPTH24STENCIL8: return GL_DEPTH24_STENCIL8;
		}

		hass(false).msg(L"Invalid Format Type");
		return GL_NONE;
	}

	constexpr GLenum OpenGLTexture::GetGLPixelFormat(Format format)
	{
		switch (format) {
		case hydro::gfx::Texture::Format::RGBA8: return GL_RGBA;
		case hydro::gfx::Texture::Format::RED_INTEGER: return GL_RED_INTEGER;
		case hydro::gfx::Texture::Format::DEPTH24STENCIL8: return GL_DEPTH_STENCIL;
		}

		hass(false).msg(L"Invalid Format Type");
		return GL_NONE;
	}

	constexpr GLenum OpenGLTexture::GetGLPixelType(Format format)
	{
		switch (format) {
		case hydro::gfx::Texture::Format::RGBA8: return GL_UNSIGNED_BYTE;
		case hydro::gfx::Texture::Format::RED_INTEGER: return GL_INT;
		case hydro::gfx::Texture::Format::DEPTH24STENCIL8: return GL_UNSIGNED_INT_24_8;
		}

		hass(false).msg(L"Invalid Format Type");
		return GL_NONE;
	}

	constexpr GLenum OpenGLTexture::GetGLType(Type type)
	{
		switch (type) {
		case hydro::gfx::Texture::Type::Texture2D: return GL_TEXTURE_2D;
		case hydro::gfx::Texture::Type::Texture2DMultisample: return GL_TEXTURE_2D_MULTISAMPLE;
		}
		
		hass(false).msg(L"Invalid type");
		return GL_NONE;
	}

	constexpr GLenum OpenGLTexture::ConvertFilter(Filter filter)
	{
		return filter == Texture::Filter::Nearest ? GL_NEAREST : GL_LINEAR;
	}

	constexpr GLenum OpenGLTexture::ConvertWrap(Wrap wrap)
	{
		switch (wrap) {
		case Texture::Wrap::Repeat:         return GL_REPEAT;
		case Texture::Wrap::ClampToEdge:    return GL_CLAMP_TO_EDGE;
		case Texture::Wrap::MirroredRepeat: return GL_MIRRORED_REPEAT;
		}

		hass(false).msg(L"Invalid warp setting");
		return GL_NONE;
	}

	constexpr size_t OpenGLTexture::BytesPerPixel(Format format)
	{
		switch (format) {
		case hydro::gfx::Texture::Format::RGBA8: return 4;
		case hydro::gfx::Texture::Format::RED_INTEGER: return 4;    
		case hydro::gfx::Texture::Format::DEPTH24STENCIL8: return 4; 
		}

		hass(false).msg(L"Invalid Format Type");
		return 0;
	}

}
