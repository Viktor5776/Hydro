#pragma once
#include <memory>

namespace hydro::gfx
{

	class Texture
	{
	public:
		enum class Format
		{
			None,
			RGBA8,
			RED_INTEGER,
			DEPTH24STENCIL8
		};
		enum class Type
		{
			Texture2D,
			Texture2DMultisample
		};
		enum class Filter
		{
			Nearest,
			Linear
		};
		enum class Wrap
		{
			Repeat,
			ClampToEdge,
			MirroredRepeat
		};
	public:
		virtual ~Texture() = default;

		virtual void Bind(unsigned int slot = 0) const = 0;
		virtual void Unbind() const = 0;
		virtual void Resize(unsigned int width, unsigned int height) = 0;
		virtual void SetData(const void* data, size_t size) = 0;
		virtual void SetFilter(Filter min, Filter mag) = 0;
		virtual void SetWrap(Wrap s, Wrap t) = 0;
		virtual void SetSamples(unsigned int samples) = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual Format GetFormat() const = 0;
		virtual Type GetType() const = 0;

		static std::shared_ptr<Texture> Create(unsigned int width, unsigned int height, Type type, Format format, const void* data = nullptr);
	};
}