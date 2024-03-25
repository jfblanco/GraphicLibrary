#include "../include/MaterialOpenGL.h"
#include "../include/RenderableOpenGL.h"
#include <SDL2/SDL_image.h>
#include <Texture.h>

void MaterialOpenGL::prepareMaterial(RenderableOpenGL *renderableOpenGl) {
    if(renderableOpenGl->renderable->material->albedo != nullptr) {
        SDL_Surface *loadedSurface = IMG_Load(renderableOpenGl->renderable->material->albedo->source.c_str());

        glGenTextures(1, &(this->albedo));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->albedo);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedSurface->w, loadedSurface->h, 0, GL_RGB, GL_UNSIGNED_BYTE,
                     loadedSurface->pixels);
        //    glEnable(GL_BLEND);
        //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
void MaterialOpenGL::setTextures() {
    glBindTexture(GL_TEXTURE_2D, this->albedo);
}