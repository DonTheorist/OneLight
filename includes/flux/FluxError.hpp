#ifndef FLUX_ERROR_H
#define FLUX_ERROR_H

#include <iostream>
#include <sstream>

#define FLUX_ASSERT(X, M) assert(X && M)
#define FLUX_ASSERT_FALSE(M) FLUX_ASSERT(false, M)
#define FLUX_ASSERT_ERROR_CODE(A) assert(A == E_OK)

enum FluxError
{
    E_OK,
    E_SDL_INIT_FAILED,
    E_SDL_SETVIDEOMODE_FAILED,
    E_OPENGL_ERROR,
    E_LIGHT_NOT_FOUND,
    E_SHADER_LINK_FAIL,
    E_SHADER_LOAD_FAIL,
    E_SHADER_CREATE_FAIL,
    E_GL_CREATE_PROGRAM_FAILED,
    E_GL_UNKOWN_UNIFORM,
    E_NO_MATCHING_LIGHT_MATERIAL
};

std::string getErrorMessage(const FluxError &error);
void writeError(const FluxError &error, std::ostream &stream=std::cerr);

#endif

