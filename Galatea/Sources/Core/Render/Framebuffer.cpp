#include "Core/Render/Framebuffer.h"
#include "Core/Render/WindowManager.h"
#include <Debug/Assert.h>
#include <Debug/Log.h>

#include <iostream>
#include "GL/glew.h"	//TODO : remove

using namespace Galatea;

Framebuffer::Framebuffer() noexcept
{
    WindowManager::GetInstance().GetWindowSize(width, height);
    CreateFBO(width, height);
}

Framebuffer::~Framebuffer() noexcept
{
    glDeleteTextures(1, &textureColorBuffer);
    glDeleteRenderbuffers(1, &depthBuffer);
    glDeleteFramebuffers(1, &FBO);
}

void Framebuffer::CreateFBO(int _width, int _height) noexcept
{
    width = _width;
    height = _height;
    // framebuffer configuration
    // -------------------------
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    // create a color attachment texture
    glGenTextures(1, &textureColorBuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
    glObjectLabel(GL_TEXTURE, textureColorBuffer, -1, "ColorTexture");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    //glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, width, height, GL_TRUE);
    //glRenderbufferStorageMultisample(GL_RENDERBUFFER, 16, GL_UNSIGNED_BYTE, width, height);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0);

    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    //glGenRenderbuffers(1, &depthBuffer);
    glGenTextures(1, &depthBuffer);
    glBindTexture(GL_TEXTURE_2D, depthBuffer);
    glObjectLabel(GL_TEXTURE, depthBuffer, -1, "DepthTexture");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer, 0); // now actually attach it

    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::UseFBO() const noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureColorBuffer);	// use the color attachment texture as the texture of the quad plane
}

void Framebuffer::Resize(int _width, int _height) noexcept
{
    glDeleteTextures(1, &textureColorBuffer);
    glDeleteRenderbuffers(1, &depthBuffer);
    glDeleteFramebuffers(1, &FBO);

    CreateFBO(_width, _height);
}
