#include "picoc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <scripting/scripting.h>
#include "../../src/lvg_header.h"
#include "../../render/gl.h"

#define PICOC_STACK_SIZE (128*1024)              /* space for the the stack */

const char g_lvgDefs[] = "\
typedef unsigned int GLenum;\
typedef unsigned char GLboolean;\
typedef unsigned int GLbitfield;\
typedef void GLvoid;\
typedef signed char GLbyte;\
typedef short GLshort;\
typedef int GLint;\
typedef int GLclampx;\
typedef unsigned char GLubyte;\
typedef unsigned short GLushort;\
typedef unsigned int GLuint;\
typedef int GLsizei;\
typedef float GLfloat;\
typedef float GLclampf;\
typedef double GLdouble;\
typedef double GLclampd;\
typedef char GLchar;\
typedef long GLsizeiptr;\
typedef struct platform_params\
{\
    int winWidth; int winHeight;\
    int width; int height;\
    int mkeys; int last_mkeys;\
    double mx; double my;\
    double time;\
} platform_params;\
typedef struct LVGShapeCollection LVGShapeCollection;\
typedef struct LVGMovieClip LVGMovieClip;\
typedef struct LVGSound\
{\
    short *samples;\
    int num_samples; int orig_rate; int rate; int channels;\
} LVGSound;\
";

#define Int(n) Param[n]->Val->Integer
#define Ptr(n) Param[n]->Val->Pointer
#define Float(n) Param[n]->Val->FP

static void lib_glCreateProgram(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (0 != NumArgs)
        return;
    ReturnValue->Val->Integer = glCreateProgram();
}

static void lib_glCreateShader(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    ReturnValue->Val->Integer = glCreateShader(Int(0));
}

static void lib_glShaderSource(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (4 != NumArgs)
        return;
    glShaderSource(Int(0), Int(1), Ptr(2), Ptr(3));
}

static void lib_glCompileShader(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    glCompileShader(Int(0));
}

static void lib_glGetShaderiv(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (3 != NumArgs)
        return;
    glGetShaderiv(Int(0), Int(1), Ptr(2));
}

static void lib_glGetShaderInfoLog(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (4 != NumArgs)
        return;
    glGetShaderInfoLog(Int(0), Int(1), Ptr(2), Ptr(3));
}

static void lib_glAttachShader(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (2 != NumArgs)
        return;
    glAttachShader(Int(0), Int(1));
}

static void lib_glLinkProgram(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    glLinkProgram(Int(0));
}

static void lib_glGetProgramiv(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (3 != NumArgs)
        return;
    glGetProgramiv(Int(0), Int(1), Ptr(2));
}

static void lib_glGetUniformLocation(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (2 != NumArgs)
        return;
    ReturnValue->Val->Integer = glGetUniformLocation(Int(0), Ptr(1));
}

static void lib_glGetAttribLocation(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (2 != NumArgs)
        return;
    ReturnValue->Val->Integer = glGetAttribLocation(Int(0), Ptr(1));
}

static void lib_glGenBuffers(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (2 != NumArgs)
        return;
    glGenBuffers(Int(0), Ptr(1));
}

static void lib_glBindBuffer(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (2 != NumArgs)
        return;
    glBindBuffer(Int(0), Int(1));
}

static void lib_glEnableVertexAttribArray(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    glEnableVertexAttribArray(Int(0));
}

static void lib_glVertexAttribPointer(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (6 != NumArgs)
        return;
    glVertexAttribPointer(Int(0), Int(1), Int(2), Int(3), Int(4), Ptr(5));
}

static void lib_glBindTexture(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (2 != NumArgs)
        return;
    glBindTexture(Int(0), Int(1));
}

static void lib_glGenTextures(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (2 != NumArgs)
        return;
    glGenTextures(Int(0), Ptr(1));
}

static void lib_glTexParameteri(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (3 != NumArgs)
        return;
    glTexParameteri(Int(0), Int(1), Int(2));
}

static void lib_glTexImage2D(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (9 != NumArgs)
        return;
    glTexImage2D(Int(0), Int(1), Int(2), Int(3), Int(4), Int(5), Int(6), Int(7), Ptr(8));
}

static void lib_glDetachShader(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (2 != NumArgs)
        return;
    glDetachShader(Int(0), Int(1));
}

static void lib_glDeleteShader(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    glDeleteShader(Int(0));
}

static void lib_glDeleteProgram(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    glDeleteProgram(Int(0));
}

static void lib_glDeleteTextures(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (2 != NumArgs)
        return;
    glDeleteTextures(Int(0), Ptr(1));
}

static void lib_glDeleteBuffers(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (2 != NumArgs)
        return;
    glDeleteBuffers(Int(0), Ptr(1));
}

static void lib_glEnable(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    glEnable(Int(0));
}

static void lib_glBlendEquation(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    glBlendEquation(Int(0));
}

static void lib_glBlendFunc(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (2 != NumArgs)
        return;
    glBlendFunc(Int(0), Int(1));
}

static void lib_glDisable(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    glDisable(Int(0));
}

static void lib_glActiveTexture(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    glActiveTexture(Int(0));
}

static void lib_glUseProgram(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    glUseProgram(Int(0));
}

static void lib_glUniform1i(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (2 != NumArgs)
        return;
    glUniform1i(Int(0), Int(1));
}

static void lib_glUniformMatrix4fv(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (4 != NumArgs)
        return;
    glUniformMatrix4fv(Int(0), Int(1), Int(2), Ptr(3));
}

static void lib_glBufferData(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (4 != NumArgs)
        return;
    glBufferData(Int(0), Int(1), Ptr(2), Int(3));
}

static void lib_glMapBuffer(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (2 != NumArgs)
        return;
    ReturnValue->Val->Pointer = glMapBuffer(Int(0), Int(1));
}

static void lib_glUnmapBuffer(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    ReturnValue->Val->Integer = glUnmapBuffer(Int(0));
}

static void lib_glScissor(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (4 != NumArgs)
        return;
    glScissor(Int(0), Int(1), Int(2), Int(3));
}

static void lib_glDrawElements(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (4 != NumArgs)
        return;
    glDrawElements(Int(0), Int(1), Int(2), Ptr(3));
}

static void lib_glPushAttrib(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    glPushAttrib(Int(0));
}

static void lib_glViewport(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (4 != NumArgs)
        return;
    glViewport(Int(0), Int(1), Int(2), Int(3));
}

static void lib_glMatrixMode(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    glMatrixMode(Int(0));
}

static void lib_glPushMatrix(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (0 != NumArgs)
        return;
    glPushMatrix();
}

static void lib_glLoadIdentity(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (0 != NumArgs)
        return;
    glLoadIdentity();
}

static void lib_glOrtho(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (6 != NumArgs)
        return;
    glOrtho(Float(0), Float(1), Float(2), Float(3), Float(4), Float(5));
}

static void lib_glEnableClientState(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    glEnableClientState(Int(0));
}

/* LVG API */
static void lib_lvgGetParams(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (0 != NumArgs)
        return;
    ReturnValue->Val->Pointer = lvgGetParams();
}

static void lib_lvgGetFileContents(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (2 != NumArgs)
        return;
    ReturnValue->Val->Pointer = lvgGetFileContents(Ptr(0), Ptr(1));
}

static void lib_lvgFree(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    lvgFree(Ptr(0));
}

static void lib_lvgTranslate(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (2 != NumArgs)
        return;
    lvgTranslate(Float(0), Float(1));
}

static void lib_lvgScale(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (2 != NumArgs)
        return;
    lvgScale(Float(0), Float(1));
}

/* SVG */
static void lib_lvgLoadSVG(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    ReturnValue->Val->Pointer = lvgLoadSVG(Ptr(0));
}

static void lib_lvgDrawSVG(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    lvgDrawSVG(Ptr(0));
}

static void lib_lvgGetShapeBounds(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (2 != NumArgs)
        return;
    lvgGetShapeBounds(Ptr(0), Ptr(1));
}

/* SWF */
static void lib_lvgLoadSWF(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    ReturnValue->Val->Pointer = lvgLoadSWF(Ptr(0));
}

static void lib_lvgDrawClip(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (1 != NumArgs)
        return;
    lvgDrawClip(Ptr(0));
}

/* Audio */
static void lib_lvgLoadMP3(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (4 != NumArgs)
        return;
    ReturnValue->Val->Pointer = lvgLoadMP3(Ptr(0), Ptr(1), Ptr(2), Ptr(3));
}

static void lib_lvgPlaySound(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    if (5 != NumArgs)
        return;
    lvgPlaySound(Ptr(0), Int(1), Int(2), Int(3), Int(4));
}

static const struct LibraryFunction g_lvgLib[] =
{
    /* GL2 */
    { lib_glCreateProgram, "GLuint glCreateProgram();" },
    { lib_glCreateShader, "GLuint glCreateShader(GLenum type);" },
    { lib_glShaderSource, "void glShaderSource(GLuint shader, GLsizei count, char **string, GLint *length);" },
    { lib_glCompileShader, "void glCompileShader(GLuint shader);" },
    { lib_glGetShaderiv, "void glGetShaderiv(GLuint shader, GLenum pname, GLint *params);" },
    { lib_glGetShaderInfoLog, "void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);" },
    { lib_glAttachShader, "void glAttachShader(GLuint program, GLuint shader);" },
    { lib_glLinkProgram, "void glLinkProgram(GLuint program);" },
    { lib_glGetProgramiv, "void glGetProgramiv(GLuint program, GLenum pname, GLint *params);" },
    { lib_glGetUniformLocation, "GLint glGetUniformLocation(GLuint program, GLchar *name);" },
    { lib_glGetAttribLocation, "GLint glGetAttribLocation(GLuint program, GLchar *name);" },
    { lib_glGenBuffers, "void glGenBuffers(GLsizei n, GLuint *buffers);" },
    { lib_glBindBuffer, "void glBindBuffer(GLenum target, GLuint buffer);" },
    { lib_glEnableVertexAttribArray, "void glEnableVertexAttribArray(GLuint index);" },
    { lib_glVertexAttribPointer, "void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, void *pointer);" },
    { lib_glBindTexture, "void glBindTexture(GLenum target, GLuint texture);" },
    { lib_glGenTextures, "void glGenTextures(GLsizei n, GLuint *textures);" },
    { lib_glTexParameteri, "void glTexParameteri(GLenum target, GLenum pname, GLint param);" },
    { lib_glTexImage2D, "void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, void *pixels);" },
    { lib_glDetachShader, "void glDetachShader(GLuint program, GLuint shader);" },
    { lib_glDeleteShader, "void glDeleteShader(GLuint shader);" },
    { lib_glDeleteProgram, "void glDeleteProgram(GLuint program);" },
    { lib_glDeleteTextures, "void glDeleteTextures(GLsizei n, GLuint *textures);" },
    { lib_glDeleteBuffers, "void glDeleteBuffers(GLsizei n, GLuint *buffers);" },
    { lib_glEnable, "void glEnable(GLenum cap);" },
    { lib_glBlendEquation, "void glBlendEquation(GLenum mode);" },
    { lib_glBlendFunc, "void glBlendFunc(GLenum sfactor, GLenum dfactor);" },
    { lib_glDisable, "void glDisable(GLenum cap);" },
    { lib_glActiveTexture, "void glActiveTexture(GLenum texture);" },
    { lib_glUseProgram, "void glUseProgram(GLuint program);" },
    { lib_glUniform1i, "void glUniform1i(GLint location, GLint v0);" },
    { lib_glUniformMatrix4fv, "void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat *value);" },
    { lib_glBufferData, "void glBufferData(GLenum target, GLsizeiptr size, void *data, GLenum usage);" },
    { lib_glMapBuffer, "char *glMapBuffer(GLenum target, GLenum access);" },
    { lib_glUnmapBuffer, "GLboolean glUnmapBuffer(GLenum target);" },
    { lib_glScissor, "void glScissor(GLint x, GLint y, GLsizei width, GLsizei height);" },
    { lib_glDrawElements, "void glDrawElements(GLenum mode, GLsizei count, GLenum type, void *indices);" },
    { lib_glPushAttrib, "void glPushAttrib(GLbitfield mask);" },
    { lib_glViewport, "void glViewport(GLint x, GLint y, GLsizei width, GLsizei height);" },
    { lib_glMatrixMode, "void glMatrixMode(GLenum mode);" },
    { lib_glPushMatrix, "void glPushMatrix();" },
    { lib_glLoadIdentity, "void glLoadIdentity();" },
    { lib_glOrtho, "void glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);" },
    { lib_glEnableClientState, "void glEnableClientState(GLenum array);" },
#ifdef USE_GL3
    { lib_glGenVertexArrays, "void glGenVertexArrays();" },
    { lib_glBindVertexArray, "void glBindVertexArray();" },
    { lib_glMapBufferRange, "void glMapBufferRange();" },
#endif
    /* LVG API */
    { lib_lvgGetParams, "platform_params *lvgGetParams();" },
    { lib_lvgGetFileContents, "char *lvgGetFileContents(char *fname, int *size);" },
    { lib_lvgFree, "void lvgFree(void *buf);" },
    { lib_lvgTranslate, "void lvgTranslate(float x, float y);" },
    { lib_lvgScale, "void lvgScale(float x, float y);" },
    /* SVG */
    { lib_lvgLoadSVG, "LVGShapeCollection *lvgLoadSVG(char *file);" },
    { lib_lvgDrawSVG, "void lvgDrawSVG(LVGShapeCollection *svg);" },
    { lib_lvgGetShapeBounds, "void lvgGetShapeBounds(LVGShapeCollection *col, double *bounds);" },
    /* SWF */
    { lib_lvgLoadSWF, "LVGMovieClip *lvgLoadSWF(char *file);" },
    { lib_lvgDrawClip, "void lvgDrawClip(LVGMovieClip *clip);" },
    /* Audio */
    { lib_lvgLoadMP3, "short *lvgLoadMP3(char *file, int *rate, int *channels, int *num_samples);" },
    { lib_lvgPlaySound, "void lvgPlaySound(LVGSound *sound, int flags, int start_sample, int end_sample, int loops);" },
    { NULL, NULL }
};

typedef struct picoc_stc
{
    Picoc pc;
} picoc_stc;

static int picoc_init(void **script, const char *file_name)
{
    *script = 0;
    picoc_stc *s = malloc(sizeof(picoc_stc));
    PicocInitialise(&s->pc, PICOC_STACK_SIZE);
    PicocIncludeAllSystemHeaders(&s->pc);
    PicocParse(&s->pc, "lvg.h", g_lvgDefs, sizeof(g_lvgDefs) - 1, TRUE, TRUE, FALSE, FALSE);
    LibraryAdd(&s->pc, &s->pc.GlobalTable, "lvg library", &g_lvgLib[0]);

    if (PicocPlatformSetExitPoint(&s->pc))
    {
        PicocCleanup(&s->pc);
        return s->pc.PicocExitValue;
    }
    PicocPlatformScanFile(&s->pc, file_name);
    *script = s;
    return 0;
}

static void picoc_release(void *script)
{
    picoc_stc *s = (picoc_stc *)script;
    PicocCleanup(&s->pc);
    free(s);
}

static void picoc_run(void *script, const char *func_name)
{
    picoc_stc *s = (picoc_stc *)script;
    struct Value *FuncValue = NULL;
    if (!VariableDefined(&s->pc, TableStrRegister(&s->pc, func_name)))
        ProgramFailNoParser(&s->pc, "func is not defined");
    VariableGet(&s->pc, NULL, TableStrRegister(&s->pc, func_name), &FuncValue);
    if (FuncValue->Typ->Base != TypeFunction)
        ProgramFailNoParser(&s->pc, "func is not a function - can't call it");
    char buf[128];
    snprintf(buf, sizeof(buf), "%s();", func_name);
    buf[sizeof(buf) - 1] = 0;
    PicocParse(&s->pc, "startup", buf, strlen(buf), TRUE, TRUE, FALSE, TRUE);
}

const script_engine script_engine_picoc =
{
    picoc_init,
    picoc_release,
    picoc_run
};
