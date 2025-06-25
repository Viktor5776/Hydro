#pragma once
#include "../../renderer/Texture.h"

#include <glad\glad.h>

namespace hydro::gfx
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(unsigned int width, unsigned int height, Type type, Format format, const void* data = nullptr);
		~OpenGLTexture();

		void CreateTexture(const void* data = nullptr);

		void Bind(unsigned int slot) const override;
		void Unbind() const override;
		void Resize(unsigned int width, unsigned int height) override;
		void SetData(const void* data, size_t size) override;
		void SetFilter(Filter min, Filter mag) override;
		void SetWrap(Wrap s, Wrap t) override;
		void SetSamples(unsigned int samples) override;

		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;
		Format GetFormat() const override;
		Type GetType() const override;

		unsigned int GetID() const;
		void* GetNativeHandle() const override;

		static constexpr GLenum GetGLInternalFormat(Format format);
		static constexpr GLenum GetGLPixelFormat(Format format);
		static constexpr GLenum GetGLPixelType(Format format);
		static constexpr GLenum GetGLType(Type type);
		static constexpr GLenum ConvertFilter(Filter filter);
		static constexpr GLenum ConvertWrap(Wrap wrap);
		static constexpr size_t BytesPerPixel(Format format);
	private:
		unsigned int texture_ = 0;
		unsigned int width_, height_;
		Type type_;
		Format format_;

		Filter min_ = Filter::Nearest, mag_ = Filter::Nearest;
		Wrap s_ = Wrap::Repeat, t_ = Wrap::Repeat;

		unsigned int samples_ = 4;
	};
}