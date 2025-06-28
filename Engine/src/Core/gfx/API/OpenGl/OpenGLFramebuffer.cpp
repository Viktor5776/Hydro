#include "OpenGLFramebuffer.h"
#include "../../../utl/Assert.h"

namespace hydro::gfx
{

    OpenGLFramebuffer::OpenGLFramebuffer(unsigned int width, unsigned int height)
        : width_(width), height_(height)
    {
        glGenFramebuffers(1, &fbo_);
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        for (auto& attachment : colorAttachments_)
            attachment.texture.reset();

        if (depthAttachment_.texture)
            depthAttachment_.texture.reset();

        for (auto rbo : colorRenderbuffers_)
            glDeleteRenderbuffers(1, &rbo);

        if (depthRenderbuffer_)
            glDeleteRenderbuffers(1, &depthRenderbuffer_);

        if (fbo_ != 0) {
            glDeleteFramebuffers(1, &fbo_);
        }
    }

    void OpenGLFramebuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
        glViewport(0, 0, width_, height_);
    }

    void OpenGLFramebuffer::Unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::Resize(unsigned int width, unsigned int height)
    {
        if (width_ == width && height_ == height)
            return;

        width_ = width;
        height_ = height;

        // Delete previous resources
        if (fbo_ != 0)
            glDeleteFramebuffers(1, &fbo_);
        for (auto id : colorRenderbuffers_)
            glDeleteRenderbuffers(1, &id);
        colorRenderbuffers_.clear();
        if (depthRenderbuffer_) {
            glDeleteRenderbuffers(1, &depthRenderbuffer_);
            depthRenderbuffer_ = 0;
        }

        // Resize color attachments
        for (auto& att : colorAttachments_) {
            if (att.type == AttachmentType::Texture && att.texture) {
                att.texture->Resize(width_, height_);
            }
        }

        // Resize depth attachment
        if (depthAttachment_.type == AttachmentType::Texture && depthAttachment_.texture) {
            depthAttachment_.texture->Resize(width_, height_);
        }

        // Recreate FBO
        glGenFramebuffers(1, &fbo_);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo_);

        int colorIndex = 0;
        for (auto& att : colorAttachments_) {
            if (att.type == AttachmentType::Texture) {
                auto tex = std::static_pointer_cast<OpenGLTexture>(att.texture);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + colorIndex++, GL_TEXTURE_2D, tex->GetID(), 0);
            }
            else {
                unsigned int rb;
                glGenRenderbuffers(1, &rb);
                glBindRenderbuffer(GL_RENDERBUFFER, rb);
                glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width_, height_);
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + colorIndex++, GL_RENDERBUFFER, rb);
                colorRenderbuffers_.push_back(rb);
            }
        }

        if (depthAttachment_.type == AttachmentType::Texture) {
            auto tex = std::static_pointer_cast<OpenGLTexture>(depthAttachment_.texture);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, tex->GetID(), 0);
        }
        else if (depthAttachment_.type == AttachmentType::Renderbuffer) {
            glGenRenderbuffers(1, &depthRenderbuffer_);
            glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer_);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width_, height_);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer_);
        }


        Validate();
    }

    void OpenGLFramebuffer::AddColorAttachment(AttachmentType type, Texture::Format format)
    {
        Bind();

        size_t index = colorAttachments_.size();
        GLenum attachment = GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(index);

        if (type == AttachmentType::Texture) {
            auto texture = std::make_shared<OpenGLTexture>(width_, height_, Texture::Type::Texture2D, format);
            glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture->GetID(), 0);
            colorAttachments_.push_back({ type, texture });
        }
        else {
            GLuint rbo;
            glGenRenderbuffers(1, &rbo);
            glBindRenderbuffer(GL_RENDERBUFFER, rbo);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width_, height_);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, rbo);
            colorRenderbuffers_.push_back(rbo);
            colorAttachments_.push_back({ type, nullptr });
        }

        Validate();
        Unbind();
    }

    void OpenGLFramebuffer::SetDepthAttachment(AttachmentType type, Texture::Format format)
    {
        Bind();

        if (depthAttachment_.type == AttachmentType::Renderbuffer && depthRenderbuffer_) {
            glDeleteRenderbuffers(1, &depthRenderbuffer_);
            depthRenderbuffer_ = 0;
        }

        if (depthAttachment_.type == AttachmentType::Texture)
            depthAttachment_.texture.reset();

        if (type == AttachmentType::Texture) {
            auto texture = std::make_shared<OpenGLTexture>(width_, height_, Texture::Type::Texture2D, format);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture->GetID(), 0);
            depthAttachment_ = { type, texture };
        }
        else {
            glGenRenderbuffers(1, &depthRenderbuffer_);
            glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer_);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width_, height_);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer_);
            depthAttachment_ = { type, nullptr };
        }

        Validate();
        Unbind();
    }

    void OpenGLFramebuffer::RemoveColorAttachment(size_t index)
    {
        hass(index < colorAttachments_.size()).msg(L"Invalid color attachment index");

        Bind();

        GLenum attachment = GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(index);
        auto& att = colorAttachments_[index];

        if (att.type == AttachmentType::Texture) {
            glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, 0, 0);
            att.texture.reset();
        }
        else {
            GLuint rbo = colorRenderbuffers_[index];
            glDeleteRenderbuffers(1, &rbo);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, 0);
        }

        colorAttachments_.erase(colorAttachments_.begin() + index);
        if (att.type == AttachmentType::Renderbuffer)
            colorRenderbuffers_.erase(colorRenderbuffers_.begin() + index);

        Validate();
        Unbind();
    }

    void OpenGLFramebuffer::RemoveDepthAttachment()
    {
        Bind();

        if (depthAttachment_.type == AttachmentType::Texture && depthAttachment_.texture) {
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
            depthAttachment_.texture.reset();
        }
        else if (depthAttachment_.type == AttachmentType::Renderbuffer && depthRenderbuffer_) {
            glDeleteRenderbuffers(1, &depthRenderbuffer_);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, 0);
            depthRenderbuffer_ = 0;
        }

        depthAttachment_ = {};
        Validate();
        Unbind();
    }

    void OpenGLFramebuffer::ClearAttachment(size_t index, int value)
    {
        hass(index < colorAttachments_.size()).msg(L"Invalid color attachment index");

        auto& att = colorAttachments_[index];
        if (att.type != AttachmentType::Texture || !att.texture)
            return;

        auto format = att.texture->GetFormat();

        if (format == Texture::Format::RED_INTEGER) {
            glClearTexImage(static_cast<OpenGLTexture*>(att.texture.get())->GetID(), 0, GL_RED_INTEGER, GL_INT, &value);
        }
        else {
            float color[4] = { 0, 0, 0, 0 };
            glClearTexImage(static_cast<OpenGLTexture*>(att.texture.get())->GetID(), 0, GL_RGBA, GL_FLOAT, &color);
        }
    }

    void OpenGLFramebuffer::ClearDepthAttachment(float depth)
    {
        if (depthAttachment_.type == AttachmentType::Texture && depthAttachment_.texture) {
            glClearTexImage(static_cast<OpenGLTexture*>(depthAttachment_.texture.get())->GetID(), 0, GL_DEPTH_STENCIL, GL_FLOAT, &depth);
        }
    }

    std::shared_ptr<Texture> OpenGLFramebuffer::GetColorAttachment(size_t index) const
    {
        hchk(index <= colorAttachments_.size()).msg(L"Invalid index");
        if (index >= colorAttachments_.size())
            return nullptr;
        return colorAttachments_[index].texture;
    }

    std::shared_ptr<Texture> OpenGLFramebuffer::GetDepthAttachment() const
    {
        return depthAttachment_.texture;
    }

    unsigned int OpenGLFramebuffer::GetWidth() const { return width_; }
    unsigned int OpenGLFramebuffer::GetHeight() const { return height_; }

    void OpenGLFramebuffer::Validate()
    {
        // Draw buffers
        std::vector<GLenum> drawBuffers;
        for (size_t i = 0; i < colorAttachments_.size(); ++i)
            drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(i));

        glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
        glDrawBuffers(static_cast<GLsizei>(drawBuffers.size()), drawBuffers.data());

        auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        hass(status == GL_FRAMEBUFFER_COMPLETE).msg(L"Framebuffer is incomplete!");
       
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

}
