#pragma once
#include "../../renderer/Framebuffer.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>

namespace hydro::gfx
{
	
	class OpenGLFramebuffer : public Framebuffer {
	public:
		OpenGLFramebuffer(unsigned int width, unsigned int height);
		~OpenGLFramebuffer();

		void Bind() const override;
		void Unbind() const override;
		void Resize(unsigned int width, unsigned int height) override;

		void AddColorAttachment(AttachmentType type, Texture::Format format) override;
		void SetDepthAttachment(AttachmentType type, Texture::Format format) override;
		void RemoveColorAttachment(size_t index) override;
		void RemoveDepthAttachment() override;

		void ClearAttachment(size_t index, int value = 0) override;
		void ClearDepthAttachment(float depth = 1.0f) override;

		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;

		std::shared_ptr<Texture> GetColorAttachment(size_t index) const override;
		std::shared_ptr<Texture> GetDepthAttachment() const override;

	private:
		void Validate();

		unsigned int fbo_ = 0;
		unsigned int width_, height_;

		std::vector<Attachment> colorAttachments_;
		Attachment depthAttachment_ = {};

		std::vector<unsigned int> colorRenderbuffers_;
		unsigned int depthRenderbuffer_ = 0;
	};

}