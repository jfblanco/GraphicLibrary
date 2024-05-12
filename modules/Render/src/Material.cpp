#include "../include/Material.h"
#include "../include/Renderable.h"
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

void Material::prepareMaterial(Renderable *renderable) {
    if(renderable->material->albedo != nullptr) {
        SDL_Surface *albedoSurface = IMG_Load(renderable->material->albedo->source.c_str());
        if(albedoSurface == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[ Material ]: We couldn't open the file %s",
                         renderable->material->albedo->source.c_str());
        } else {
            createOpenGLTextureUniform(&(this->albedoUBO) ,albedoSurface);
        }
    }
    if(renderable->material->normal != nullptr) {
        SDL_Surface *normalSurface = IMG_Load(renderable->material->normal->source.c_str());
        if(normalSurface == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[ Material ]: We couldn't open the file %s",
                         renderable->material->normal->source.c_str());
        } else {
            createOpenGLTextureUniform(&(this->normalUBO) ,normalSurface);
        }
    }
    if(renderable->material->height != nullptr) {
        SDL_Surface *heightSurface = IMG_Load(renderable->material->height->source.c_str());
        if(heightSurface == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[ Material ]: We couldn't open the file %s",
                         renderable->material->height->source.c_str());
        } else {
            createOpenGLTextureUniform(&(this->heightUBO) ,heightSurface);
        }
    }
}
void Material::setTextures() {
    if(this->albedoUBO != SDL_MAX_UINT16) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->albedoUBO);
    }
    if(this->normalUBO != SDL_MAX_UINT16) {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, this->normalUBO);
    }
    if(this->heightUBO != SDL_MAX_UINT16) {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, this->heightUBO);
    }
}