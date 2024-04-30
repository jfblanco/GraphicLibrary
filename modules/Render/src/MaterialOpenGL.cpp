#include "../include/MaterialOpenGL.h"
#include "../include/RenderableOpenGL.h"
#include <SDL2/SDL_image.h>
#include <Texture.h>

void createOpenGLTextureUniform(Uint16* _id, SDL_Surface *_texture) {
    glGenTextures(1, (GLuint*) _id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _texture->w, _texture->h, 0, GL_RGB, GL_UNSIGNED_BYTE,_texture->pixels);
    //    glEnable(GL_BLEND);
    //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void MaterialOpenGL::prepareMaterial(RenderableOpenGL *renderableOpenGl) {
    if(renderableOpenGl->renderable->material->albedo != nullptr) {
        SDL_Surface *albedoSurface = IMG_Load(renderableOpenGl->renderable->material->albedo->source.c_str());
        createOpenGLTextureUniform(&(this->albedo) ,albedoSurface);
    }
    if(renderableOpenGl->renderable->material->normal != nullptr) {
        SDL_Surface *normalSurface = IMG_Load(renderableOpenGl->renderable->material->normal->source.c_str());
        createOpenGLTextureUniform(&(this->normal) ,normalSurface);
    }
    if(renderableOpenGl->renderable->material->height != nullptr) {
        SDL_Surface *heightSurface = IMG_Load(renderableOpenGl->renderable->material->height->source.c_str());
        createOpenGLTextureUniform(&(this->height) ,heightSurface);
    }
}
void MaterialOpenGL::setTextures() {
    if(this->albedo != SDL_MAX_UINT16) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->albedo);
    }
    if(this->normal != SDL_MAX_UINT16) {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, this->normal);
    }
    if(this->height != SDL_MAX_UINT16) {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, this->height);
    }
}