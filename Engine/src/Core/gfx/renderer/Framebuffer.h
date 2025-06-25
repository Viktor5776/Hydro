#pragma once
#include "Texture.h"
#include <memory>
#include <vector>

namespace hydro::gfx {

	class Framebuffer {
	public:
		enum class AttachmentType {
			Texture,
			Renderbuffer
		};

		struct Attachment {
			AttachmentType type;
			std::shared_ptr<Texture> texture = nullptr;
		};
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void Resize(unsigned int width, unsigned int height) = 0;

		virtual void AddColorAttachment(AttachmentType type, Texture::Format format) = 0;
		virtual void SetDepthAttachment(AttachmentType type, Texture::Format format) = 0;

		virtual void RemoveColorAttachment(size_t index) = 0;
		virtual void RemoveDepthAttachment() = 0;

		virtual void ClearAttachment(size_t index, int value = 0) = 0;
		virtual void ClearDepthAttachment(float depth = 1.0f) = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual std::shared_ptr<Texture> GetColorAttachment(size_t index) const = 0;
		virtual std::shared_ptr<Texture> GetDepthAttachment() const = 0;

		static std::shared_ptr<Framebuffer> Create(unsigned int width, unsigned int height);
	};

}