#include "opengl_gen.hpp"
#include <SDL2/SDL_video.h>

typedef void (APIENTRYP PFNGLDRAWBUFFERPROC)(GLenum buf);
typedef void (APIENTRYP PFNGLLINEWIDTHPROC)(GLfloat width);
typedef void (APIENTRYP PFNGLDRAWBUFFERSPROC)(GLsizei n, const GLenum * bufs);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1);
typedef GLuint (APIENTRYP PFNGLGETDEBUGMESSAGELOGPROC)(GLuint count, GLsizei bufSize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog);
typedef void (APIENTRYP PFNGLDELETEPROGRAMPROC)(GLuint program);
typedef GLboolean (APIENTRYP PFNGLISFRAMEBUFFERPROC)(GLuint framebuffer);
typedef void (APIENTRYP PFNGLCOPYNAMEDBUFFERSUBDATAPROC)(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLQUERYCOUNTERPROC)(GLuint id, GLenum target);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IPROC)(GLuint program, GLint location, GLint v0, GLint v1);
typedef void (APIENTRYP PFNGLDELETEPROGRAMPIPELINESPROC)(GLsizei n, const GLuint * pipelines);
typedef void (APIENTRYP PFNGLLINKPROGRAMPROC)(GLuint program);
typedef void (APIENTRYP PFNGLGETDOUBLEI_VPROC)(GLenum target, GLuint index, GLdouble * data);
typedef void (APIENTRYP PFNGLCOPYTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IVPROC)(GLuint program, GLint location, GLsizei count, const GLint * value);
typedef void (APIENTRYP PFNGLDELETEQUERIESPROC)(GLsizei n, const GLuint * ids);
typedef void (APIENTRYP PFNGLCOPYTEXIMAGE1DPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (APIENTRYP PFNGLGETDOUBLEVPROC)(GLenum pname, GLdouble * data);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1);
typedef GLenum (APIENTRYP PFNGLGETERRORPROC)();
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (APIENTRYP PFNGLDELETERENDERBUFFERSPROC)(GLsizei n, const GLuint * renderbuffers);
typedef void (APIENTRYP PFNGLDRAWELEMENTSPROC)(GLenum mode, GLsizei count, GLenum type, const void * indices);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint * value);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLDELETESAMPLERSPROC)(GLsizei count, const GLuint * samplers);
typedef void (APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLint basevertex);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
typedef void (APIENTRYP PFNGLNAMEDBUFFERDATAPROC)(GLuint buffer, GLsizeiptr size, const void * data, GLenum usage);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount);
typedef void (APIENTRYP PFNGLDELETESHADERPROC)(GLuint shader);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE1DPROC)(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC)(GLenum mode, GLenum type, const void * indirect);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
typedef void (APIENTRYP PFNGLDELETESYNCPROC)(GLsync sync);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IPROC)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
typedef void (APIENTRYP PFNGLNAMEDBUFFERSUBDATAPROC)(GLuint buffer, GLintptr offset, GLsizeiptr size, const void * data);
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE3DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE2DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLNAMEDBUFFERSTORAGEPROC)(GLuint buffer, GLsizeiptr size, const void * data, GLbitfield flags);
typedef void (APIENTRYP PFNGLGETMULTISAMPLEFVPROC)(GLenum pname, GLuint index, GLfloat * val);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
typedef void (APIENTRYP PFNGLGETFLOATI_VPROC)(GLenum target, GLuint index, GLfloat * data);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLuint baseinstance);
typedef GLboolean (APIENTRYP PFNGLISPROGRAMPROC)(GLuint program);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPARAMETERI64VPROC)(GLuint buffer, GLenum pname, GLint64 * params);
typedef void (APIENTRYP PFNGLDELETETEXTURESPROC)(GLsizei n, const GLuint * textures);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPARAMETERIVPROC)(GLuint buffer, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC)(GLuint framebuffer, GLsizei n, const GLenum * bufs);
typedef void (APIENTRYP PFNGLSECONDARYCOLORP3UIVPROC)(GLenum type, const GLuint * color);
typedef void (APIENTRYP PFNGLSECONDARYCOLORP3UIPROC)(GLenum type, GLuint color);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC)(GLuint framebuffer, GLenum buf);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPOINTERVPROC)(GLuint buffer, GLenum pname, void ** params);
typedef void (APIENTRYP PFNGLGETFLOATVPROC)(GLenum pname, GLfloat * data);
typedef void (APIENTRYP PFNGLDELETETRANSFORMFEEDBACKSPROC)(GLsizei n, const GLuint * ids);
typedef GLboolean (APIENTRYP PFNGLISPROGRAMPIPELINEPROC)(GLuint pipeline);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC)(GLuint framebuffer, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERSUBDATAPROC)(GLuint buffer, GLintptr offset, GLsizeiptr size, void * data);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IVPROC)(GLuint program, GLint location, GLsizei count, const GLint * value);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC)(GLuint framebuffer, GLenum src);
typedef void (APIENTRYP PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint * arrays);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC)(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef GLboolean (APIENTRYP PFNGLISQUERYPROC)(GLuint id);
typedef GLint (APIENTRYP PFNGLGETFRAGDATAINDEXPROC)(GLuint program, const GLchar * name);
typedef void (APIENTRYP PFNGLMEMORYBARRIERPROC)(GLbitfield barriers);
typedef void (APIENTRYP PFNGLCREATEBUFFERSPROC)(GLsizei n, GLuint * buffers);
typedef void (APIENTRYP PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC)(GLuint framebuffer, GLenum pname, GLint * param);
typedef void (APIENTRYP PFNGLMEMORYBARRIERBYREGIONPROC)(GLbitfield barriers);
typedef GLint (APIENTRYP PFNGLGETFRAGDATALOCATIONPROC)(GLuint program, const GLchar * name);
typedef void (APIENTRYP PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLuint framebuffer, GLenum attachment, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTUREPROC)(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLCREATEFRAMEBUFFERSPROC)(GLsizei n, GLuint * framebuffers);
typedef void (APIENTRYP PFNGLLOGICOPPROC)(GLenum opcode);
typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
typedef GLboolean (APIENTRYP PFNGLISRENDERBUFFERPROC)(GLuint renderbuffer);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint * value);
typedef void (APIENTRYP PFNGLMINSAMPLESHADINGPROC)(GLfloat value);
typedef GLuint (APIENTRYP PFNGLCREATEPROGRAMPROC)();
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices, GLint basevertex);
typedef void (APIENTRYP PFNGLDEPTHFUNCPROC)(GLenum func);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
typedef void (APIENTRYP PFNGLDEPTHMASKPROC)(GLboolean flag);
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLenum target, GLenum attachment, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC)(GLuint renderbuffer, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IPROC)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (APIENTRYP PFNGLCREATEPROGRAMPIPELINESPROC)(GLsizei n, GLuint * pipelines);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC)(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (APIENTRYP PFNGLDEPTHRANGEPROC)(GLdouble n, GLdouble f);
typedef GLboolean (APIENTRYP PFNGLISSAMPLERPROC)(GLuint sampler);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
typedef void (APIENTRYP PFNGLRESUMETRANSFORMFEEDBACKPROC)();
typedef void (APIENTRYP PFNGLGETOBJECTLABELPROC)(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label);
typedef void (APIENTRYP PFNGLCREATEQUERIESPROC)(GLenum target, GLsizei n, GLuint * ids);
typedef GLboolean (APIENTRYP PFNGLISSHADERPROC)(GLuint shader);
typedef void (APIENTRYP PFNGLGETNUNIFORMFVPROC)(GLuint program, GLint location, GLsizei bufSize, GLfloat * params);
typedef void (APIENTRYP PFNGLCREATERENDERBUFFERSPROC)(GLsizei n, GLuint * renderbuffers);
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLSHADERBINARYPROC)(GLsizei count, const GLuint * shaders, GLenum binaryFormat, const void * binary, GLsizei length);
typedef GLenum (APIENTRYP PFNGLGETGRAPHICSRESETSTATUSPROC)();
typedef void (APIENTRYP PFNGLCREATESAMPLERSPROC)(GLsizei n, GLuint * samplers);
typedef void (APIENTRYP PFNGLDEPTHRANGEARRAYVPROC)(GLuint first, GLsizei count, const GLdouble * v);
typedef GLboolean (APIENTRYP PFNGLISSYNCPROC)(GLsync sync);
typedef void (APIENTRYP PFNGLDEPTHRANGEINDEXEDPROC)(GLuint index, GLdouble n, GLdouble f);
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROC)(GLenum type);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IVPROC)(GLuint program, GLint location, GLsizei count, const GLint * value);
typedef void (APIENTRYP PFNGLGETOBJECTPTRLABELPROC)(const void * ptr, GLsizei bufSize, GLsizei * length, GLchar * label);
typedef void (APIENTRYP PFNGLSAMPLECOVERAGEPROC)(GLfloat value, GLboolean invert);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKPROC)(GLenum mode, GLuint id);
typedef GLboolean (APIENTRYP PFNGLISTEXTUREPROC)(GLuint texture);
typedef void (APIENTRYP PFNGLSHADERSTORAGEBLOCKBINDINGPROC)(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);
typedef void (APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROGRAMVPROC)(GLenum type, GLsizei count, const GLchar *const* strings);
typedef void (APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEPROC)(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLDEPTHRANGEFPROC)(GLfloat n, GLfloat f);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)(GLenum mode, GLuint id, GLsizei instancecount);
typedef void (APIENTRYP PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint * value);
typedef void (APIENTRYP PFNGLCREATETEXTURESPROC)(GLenum target, GLsizei n, GLuint * textures);
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSPROC)(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)(GLenum mode, GLuint id, GLuint stream);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBBINDINGPROC)(GLuint vaobj, GLuint attribindex, GLuint bindingindex);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount);
typedef void (APIENTRYP PFNGLCREATEVERTEXARRAYSPROC)(GLsizei n, GLuint * arrays);
typedef GLboolean (APIENTRYP PFNGLISTRANSFORMFEEDBACKPROC)(GLuint id);
typedef void (APIENTRYP PFNGLCREATETRANSFORMFEEDBACKSPROC)(GLsizei n, GLuint * ids);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBFORMATPROC)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (APIENTRYP PFNGLREADBUFFERPROC)(GLenum src);
typedef void * (APIENTRYP PFNGLMAPBUFFERRANGEPROC)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTPROC)(GLenum mode, const void * indirect, GLsizei drawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLCULLFACEPROC)(GLenum mode);
typedef void * (APIENTRYP PFNGLMAPBUFFERPROC)(GLenum target, GLenum access);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBIFORMATPROC)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLDETACHSHADERPROC)(GLuint program, GLuint shader);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBLFORMATPROC)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLSAMPLEMASKIPROC)(GLuint maskNumber, GLbitfield mask);
typedef GLboolean (APIENTRYP PFNGLISVERTEXARRAYPROC)(GLuint array);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (APIENTRYP PFNGLVERTEXARRAYBINDINGDIVISORPROC)(GLuint vaobj, GLuint bindingindex, GLuint divisor);
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC)(GLenum mode, const void * indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLDISABLEPROC)(GLenum cap);
typedef void (APIENTRYP PFNGLVERTEXARRAYELEMENTBUFFERPROC)(GLuint vaobj, GLuint buffer);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (APIENTRYP PFNGLREADPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSPROC)(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIIVPROC)(GLuint sampler, GLenum pname, const GLint * param);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (APIENTRYP PFNGLSPECIALIZESHADERPROC)(GLuint shader, const GLchar * pEntryPoint, GLuint numSpecializationConstants, const GLuint * pConstantIndex, const GLuint * pConstantValue);
typedef void (APIENTRYP PFNGLGETINTEGER64I_VPROC)(GLenum target, GLuint index, GLint64 * data);
typedef void (APIENTRYP PFNGLDEBUGMESSAGECALLBACKPROC)(GLDEBUGPROC callback, const void * userParam);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount, const GLint * basevertex);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIUIVPROC)(GLuint sampler, GLenum pname, const GLuint * param);
typedef void (APIENTRYP PFNGLGETINTEGER64VPROC)(GLenum pname, GLint64 * data);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (APIENTRYP PFNGLREADNPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void * data);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTPROC)(GLenum mode, GLenum type, const void * indirect, GLsizei drawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFPROC)(GLuint sampler, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLDEBUGMESSAGECONTROLPROC)(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint * ids, GLboolean enabled);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFVPROC)(GLuint sampler, GLenum pname, const GLfloat * param);
typedef void * (APIENTRYP PFNGLMAPNAMEDBUFFERRANGEPROC)(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (APIENTRYP PFNGLENABLEPROC)(GLenum cap);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIPROC)(GLuint sampler, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (APIENTRYP PFNGLDISABLEVERTEXARRAYATTRIBPROC)(GLuint vaobj, GLuint index);
typedef void (APIENTRYP PFNGLGETINTEGERI_VPROC)(GLenum target, GLuint index, GLint * data);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIVPROC)(GLuint sampler, GLenum pname, const GLint * param);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC)(GLenum mode, GLenum type, const void * indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (APIENTRYP PFNGLDEBUGMESSAGEINSERTPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * buf);
typedef void (APIENTRYP PFNGLGETINTEGERVPROC)(GLenum pname, GLint * data);
typedef void * (APIENTRYP PFNGLMAPNAMEDBUFFERPROC)(GLuint buffer, GLenum access);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXBUFFERPROC)(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint index);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (APIENTRYP PFNGLSTENCILFUNCPROC)(GLenum func, GLint ref, GLuint mask);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (APIENTRYP PFNGLGETINTERNALFORMATIVPROC)(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint * params);
typedef void (APIENTRYP PFNGLSCISSORPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLDISABLEIPROC)(GLenum target, GLuint index);
typedef void (APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC)(GLenum face, GLenum func, GLint ref, GLuint mask);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (APIENTRYP PFNGLENABLEVERTEXARRAYATTRIBPROC)(GLuint vaobj, GLuint index);
typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint * buffers);
typedef void (APIENTRYP PFNGLGETINTERNALFORMATI64VPROC)(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint64 * params);
typedef void (APIENTRYP PFNGLSCISSORARRAYVPROC)(GLuint first, GLsizei count, const GLint * v);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXBUFFERSPROC)(GLuint vaobj, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides);
typedef void (APIENTRYP PFNGLSTENCILMASKPROC)(GLuint mask);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (APIENTRYP PFNGLSTENCILMASKSEPARATEPROC)(GLenum face, GLuint mask);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1DPROC)(GLuint index, GLdouble x);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (APIENTRYP PFNGLSTENCILOPPROC)(GLenum fail, GLenum zfail, GLenum zpass);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1DVPROC)(GLuint index, const GLdouble * v);
typedef void (APIENTRYP PFNGLNORMALP3UIPROC)(GLenum type, GLuint coords);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (APIENTRYP PFNGLSTENCILOPSEPARATEPROC)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
typedef void (APIENTRYP PFNGLNORMALP3UIVPROC)(GLenum type, const GLuint * coords);
typedef void (APIENTRYP PFNGLSCISSORINDEXEDPROC)(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (APIENTRYP PFNGLPROVOKINGVERTEXPROC)(GLenum mode);
typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEPROC)(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
typedef void (APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC)(GLsizei n, const GLuint * framebuffers);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1FPROC)(GLuint index, GLfloat x);
typedef void (APIENTRYP PFNGLENABLEIPROC)(GLenum target, GLuint index);
typedef void (APIENTRYP PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);
typedef void (APIENTRYP PFNGLGETPROGRAMBINARYPROC)(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, void * binary);
typedef void (APIENTRYP PFNGLRELEASESHADERCOMPILERPROC)();
typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC)(GLintptr indirect);
typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
typedef void (APIENTRYP PFNGLSCISSORINDEXEDVPROC)(GLuint index, const GLint * v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1FVPROC)(GLuint index, const GLfloat * v);
typedef void (APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC)(GLenum mode, const void * indirect);
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC)(GLuint program, GLenum programInterface, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance);
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLPUSHDEBUGGROUPPROC)(GLenum source, GLuint id, GLsizei length, const GLchar * message);
typedef void (APIENTRYP PFNGLENDCONDITIONALRENDERPROC)();
typedef void (APIENTRYP PFNGLWAITSYNCPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (APIENTRYP PFNGLPOINTSIZEPROC)(GLfloat size);
typedef void (APIENTRYP PFNGLUNIFORM4UIPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (APIENTRYP PFNGLTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, const GLint * params);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1SPROC)(GLuint index, GLshort x);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERFVPROC)(GLuint texture, GLenum pname, GLfloat * params);
typedef void (APIENTRYP PFNGLCLEARDEPTHPROC)(GLdouble depth);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIVPROC)(GLuint texture, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLVERTEXATTRIBLFORMATPROC)(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLOBJECTLABELPROC)(GLenum identifier, GLuint name, GLsizei length, const GLchar * label);
typedef void (APIENTRYP PFNGLUNIFORM4IVPROC)(GLint location, GLsizei count, const GLint * value);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4UBVPROC)(GLuint index, const GLubyte * v);
typedef void (APIENTRYP PFNGLGENFRAMEBUFFERSPROC)(GLsizei n, GLuint * framebuffers);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4UIVPROC)(GLuint index, const GLuint * v);
typedef void (APIENTRYP PFNGLTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, const GLuint * params);
typedef void (APIENTRYP PFNGLGETNUNIFORMIVPROC)(GLuint program, GLint location, GLsizei bufSize, GLint * params);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1SVPROC)(GLuint index, const GLshort * v);
typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGPROC)(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
typedef void (APIENTRYP PFNGLVERTEXATTRIBLPOINTERPROC)(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (APIENTRYP PFNGLOBJECTPTRLABELPROC)(const void * ptr, GLsizei length, const GLchar * label);
typedef void (APIENTRYP PFNGLCLEARDEPTHFPROC)(GLfloat d);
typedef void (APIENTRYP PFNGLTEXPARAMETERFPROC)(GLenum target, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLUNIFORM1DPROC)(GLint location, GLdouble x);
typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEIVPROC)(GLuint pipeline, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4USVPROC)(GLuint index, const GLushort * v);
typedef void (APIENTRYP PFNGLGETTEXTURESUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void * pixels);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP2UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (APIENTRYP PFNGLUNIFORM1DVPROC)(GLint location, GLsizei count, const GLdouble * value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP1UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
typedef void (APIENTRYP PFNGLGETNUNIFORMUIVPROC)(GLuint program, GLint location, GLsizei bufSize, GLuint * params);
typedef void (APIENTRYP PFNGLTEXPARAMETERFVPROC)(GLenum target, GLenum pname, const GLfloat * params);
typedef GLuint (APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC)(GLuint program, GLenum programInterface, const GLchar * name);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP2UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
typedef void (APIENTRYP PFNGLUNIFORM1FPROC)(GLint location, GLfloat v0);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP1UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef GLint (APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC)(GLuint program, GLenum programInterface, const GLchar * name);
typedef void (APIENTRYP PFNGLTEXPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2DPROC)(GLuint index, GLdouble x, GLdouble y);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP3UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (APIENTRYP PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
typedef GLint (APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC)(GLuint program, GLenum programInterface, const GLchar * name);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKI64_VPROC)(GLuint xfb, GLenum pname, GLuint index, GLint64 * param);
typedef void (APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP3UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
typedef void (APIENTRYP PFNGLPOLYGONMODEPROC)(GLenum face, GLenum mode);
typedef void (APIENTRYP PFNGLTEXPARAMETERIVPROC)(GLenum target, GLenum pname, const GLint * params);
typedef void (APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC)(GLuint index, GLuint divisor);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP4UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC)(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKI_VPROC)(GLuint xfb, GLenum pname, GLuint index, GLint * param);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP4UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
typedef void (APIENTRYP PFNGLENDQUERYPROC)(GLenum target);
typedef void (APIENTRYP PFNGLUNIFORM1FVPROC)(GLint location, GLsizei count, const GLfloat * value);
typedef void (APIENTRYP PFNGLBEGINCONDITIONALRENDERPROC)(GLuint id, GLenum mode);
typedef void (APIENTRYP PFNGLGETPROGRAMSTAGEIVPROC)(GLuint program, GLenum shadertype, GLenum pname, GLint * values);
typedef void (APIENTRYP PFNGLVERTEXATTRIBBINDINGPROC)(GLuint attribindex, GLuint bindingindex);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKIVPROC)(GLuint xfb, GLenum pname, GLint * param);
typedef void (APIENTRYP PFNGLUNIFORM4UIVPROC)(GLint location, GLsizei count, const GLuint * value);
typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC)(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei count, GLsizei * length, GLint * params);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2DVPROC)(GLuint index, const GLdouble * v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
typedef void (APIENTRYP PFNGLPOLYGONOFFSETPROC)(GLfloat factor, GLfloat units);
typedef GLuint (APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC)(GLuint program, const GLchar * uniformBlockName);
typedef void (APIENTRYP PFNGLVERTEXATTRIBFORMATPROC)(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLCLEARNAMEDBUFFERDATAPROC)(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void * data);
typedef void (APIENTRYP PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
typedef void (APIENTRYP PFNGLGENPROGRAMPIPELINESPROC)(GLsizei n, GLuint * pipelines);
typedef void (APIENTRYP PFNGLPOLYGONOFFSETCLAMPPROC)(GLfloat factor, GLfloat units, GLfloat clamp);
typedef void (APIENTRYP PFNGLGETUNIFORMINDICESPROC)(GLuint program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices);
typedef void (APIENTRYP PFNGLCOLORMASKPROC)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLBLENDCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef GLint (APIENTRYP PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar * name);
typedef void (APIENTRYP PFNGLTEXSTORAGE1DPROC)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2FPROC)(GLuint index, GLfloat x, GLfloat y);
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERFIPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
typedef void (APIENTRYP PFNGLENDQUERYINDEXEDPROC)(GLenum target, GLuint index);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1IPROC)(GLuint index, GLint x);
typedef void (APIENTRYP PFNGLTEXSTORAGE2DPROC)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLCLEARNAMEDBUFFERSUBDATAPROC)(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data);
typedef void (APIENTRYP PFNGLBLENDEQUATIONPROC)(GLenum mode);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1IVPROC)(GLuint index, const GLint * v);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (APIENTRYP PFNGLGETUNIFORMSUBROUTINEUIVPROC)(GLenum shadertype, GLint location, GLuint * params);
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint * value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (APIENTRYP PFNGLCOLORP3UIPROC)(GLenum type, GLuint color);
typedef void (APIENTRYP PFNGLGETUNIFORMDVPROC)(GLuint program, GLint location, GLdouble * params);
typedef void (APIENTRYP PFNGLGENQUERIESPROC)(GLsizei n, GLuint * ids);
typedef void (APIENTRYP PFNGLCOLORMASKIPROC)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTI64VPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (APIENTRYP PFNGLGETUNIFORMIVPROC)(GLuint program, GLint location, GLint * params);
typedef void (APIENTRYP PFNGLCOLORP3UIVPROC)(GLenum type, const GLuint * color);
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERIVPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint * value);
typedef void (APIENTRYP PFNGLGETUNIFORMFVPROC)(GLuint program, GLint location, GLfloat * params);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2FVPROC)(GLuint index, const GLfloat * v);
typedef void (APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC)();
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERFVPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat * value);
typedef void (APIENTRYP PFNGLHINTPROC)(GLenum target, GLenum mode);
typedef void (APIENTRYP PFNGLBEGINQUERYPROC)(GLenum target, GLuint id);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1UIPROC)(GLuint index, GLuint x);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTIVPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTUI64VPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (APIENTRYP PFNGLCLEARSTENCILPROC)(GLint s);
typedef void (APIENTRYP PFNGLUNIFORM1IVPROC)(GLint location, GLsizei count, const GLint * value);
typedef void (APIENTRYP PFNGLTEXSTORAGE2DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTUIVPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (APIENTRYP PFNGLPATCHPARAMETERFVPROC)(GLenum pname, const GLfloat * values);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1UIVPROC)(GLuint index, const GLuint * v);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (APIENTRYP PFNGLGETQUERYINDEXEDIVPROC)(GLenum target, GLuint index, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLTEXSTORAGE3DPROC)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (APIENTRYP PFNGLCLEARTEXIMAGEPROC)(GLuint texture, GLint level, GLenum format, GLenum type, const void * data);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTI64VPROC)(GLuint id, GLenum pname, GLint64 * params);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTIVPROC)(GLuint id, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLCOLORP4UIPROC)(GLenum type, GLuint color);
typedef void (APIENTRYP PFNGLPATCHPARAMETERIPROC)(GLenum pname, GLint value);
typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC)(GLenum modeRGB, GLenum modeAlpha);
typedef void (APIENTRYP PFNGLUNIFORM1UIPROC)(GLint location, GLuint v0);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2IPROC)(GLuint index, GLint x, GLint y);
typedef void (APIENTRYP PFNGLGENRENDERBUFFERSPROC)(GLsizei n, GLuint * renderbuffers);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTUIVPROC)(GLuint id, GLenum pname, GLuint * params);
typedef void (APIENTRYP PFNGLCOLORP4UIVPROC)(GLenum type, const GLuint * color);
typedef void (APIENTRYP PFNGLBEGINQUERYINDEXEDPROC)(GLenum target, GLuint index, GLuint id);
typedef void (APIENTRYP PFNGLPOPDEBUGGROUPPROC)();
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2SPROC)(GLuint index, GLshort x, GLshort y);
typedef void (APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC)(GLenum primitiveMode);
typedef void (APIENTRYP PFNGLGETUNIFORMUIVPROC)(GLuint program, GLint location, GLuint * params);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTUI64VPROC)(GLuint id, GLenum pname, GLuint64 * params);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (APIENTRYP PFNGLCLEARTEXSUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * data);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2IVPROC)(GLuint index, const GLint * v);
typedef void (APIENTRYP PFNGLGENSAMPLERSPROC)(GLsizei count, GLuint * samplers);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEIPROC)(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2SVPROC)(GLuint index, const GLshort * v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2UIPROC)(GLuint index, GLuint x, GLuint y);
typedef void (APIENTRYP PFNGLVERTEXBINDINGDIVISORPROC)(GLuint bindingindex, GLuint divisor);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (APIENTRYP PFNGLTEXBUFFERPROC)(GLenum target, GLenum internalformat, GLuint buffer);
typedef void (APIENTRYP PFNGLGETQUERYIVPROC)(GLenum target, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLGENTEXTURESPROC)(GLsizei n, GLuint * textures);
typedef void (APIENTRYP PFNGLBLENDEQUATIONIPROC)(GLuint buf, GLenum mode);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels);
typedef void (APIENTRYP PFNGLBINDATTRIBLOCATIONPROC)(GLuint program, GLuint index, const GLchar * name);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2UIVPROC)(GLuint index, const GLuint * v);
typedef void (APIENTRYP PFNGLUNIFORM1UIVPROC)(GLint location, GLsizei count, const GLuint * value);
typedef void (APIENTRYP PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef GLenum (APIENTRYP PFNGLCLIENTWAITSYNCPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (APIENTRYP PFNGLUNIFORM2DVPROC)(GLint location, GLsizei count, const GLdouble * value);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLGENTRANSFORMFEEDBACKSPROC)(GLsizei n, GLuint * ids);
typedef void (APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3IPROC)(GLuint index, GLint x, GLint y, GLint z);
typedef void (APIENTRYP PFNGLCLIPCONTROLPROC)(GLenum origin, GLenum depth);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYINDEXED64IVPROC)(GLuint vaobj, GLuint index, GLenum pname, GLint64 * param);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (APIENTRYP PFNGLUNIFORM2DPROC)(GLint location, GLdouble x, GLdouble y);
typedef void (APIENTRYP PFNGLTEXBUFFERRANGEPROC)(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels);
typedef void (APIENTRYP PFNGLVERTEXP2UIVPROC)(GLenum type, const GLuint * value);
typedef void (APIENTRYP PFNGLBLENDFUNCPROC)(GLenum sfactor, GLenum dfactor);
typedef void (APIENTRYP PFNGLBINDBUFFERBASEPROC)(GLenum target, GLuint index, GLuint buffer);
typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint * arrays);
typedef void (APIENTRYP PFNGLVERTEXP2UIPROC)(GLenum type, GLuint value);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIIVPROC)(GLuint sampler, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (APIENTRYP PFNGLUNIFORM2FPROC)(GLint location, GLfloat v0, GLfloat v1);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3DVPROC)(GLuint index, const GLdouble * v);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3IVPROC)(GLuint index, const GLint * v);
typedef void (APIENTRYP PFNGLTEXTUREBARRIERPROC)();
typedef void (APIENTRYP PFNGLGETVERTEXARRAYINDEXEDIVPROC)(GLuint vaobj, GLuint index, GLenum pname, GLint * param);
typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEPROC)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3UIPROC)(GLuint index, GLuint x, GLuint y, GLuint z);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVPROC)(GLuint sampler, GLenum pname, GLuint * params);
typedef void (APIENTRYP PFNGLVERTEXP3UIPROC)(GLenum type, GLuint value);
typedef void (APIENTRYP PFNGLUNIFORMSUBROUTINESUIVPROC)(GLenum shadertype, GLsizei count, const GLuint * indices);
typedef void (APIENTRYP PFNGLUNIFORM2FVPROC)(GLint location, GLsizei count, const GLfloat * value);
typedef void (APIENTRYP PFNGLVERTEXP3UIVPROC)(GLenum type, const GLuint * value);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRYP PFNGLBINDBUFFERRANGEPROC)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3UIVPROC)(GLuint index, const GLuint * v);
typedef void (APIENTRYP PFNGLGENERATEMIPMAPPROC)(GLenum target);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC)(GLuint sampler, GLenum pname, GLfloat * params);
typedef void (APIENTRYP PFNGLPRIMITIVERESTARTINDEXPROC)(GLuint index);
typedef void (APIENTRYP PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name);
typedef void (APIENTRYP PFNGLUNIFORM2IPROC)(GLint location, GLint v0, GLint v1);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC)(GLuint sampler, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLVERTEXP4UIPROC)(GLenum type, GLuint value);
typedef void (APIENTRYP PFNGLTEXTUREBUFFERPROC)(GLuint texture, GLenum internalformat, GLuint buffer);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYIVPROC)(GLuint vaobj, GLenum pname, GLint * param);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC)(GLuint index, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4BVPROC)(GLuint index, const GLbyte * v);
typedef void (APIENTRYP PFNGLBINDFRAGDATALOCATIONPROC)(GLuint program, GLuint color, const GLchar * name);
typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEIPROC)(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
typedef void (APIENTRYP PFNGLVERTEXP4UIVPROC)(GLenum type, const GLuint * value);
typedef GLboolean (APIENTRYP PFNGLUNMAPBUFFERPROC)(GLenum target);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3FVPROC)(GLuint index, const GLfloat * v);
typedef void (APIENTRYP PFNGLBINDBUFFERSRANGEPROC)(GLenum target, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizeiptr * sizes);
typedef void (APIENTRYP PFNGLTEXTUREBUFFERRANGEPROC)(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IPROC)(GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (APIENTRYP PFNGLTEXCOORDP1UIPROC)(GLenum type, GLuint coords);
typedef void (APIENTRYP PFNGLBINDBUFFERSBASEPROC)(GLenum target, GLuint first, GLsizei count, const GLuint * buffers);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC)(GLuint index, GLenum pname, GLuint * params);
typedef void (APIENTRYP PFNGLPROGRAMBINARYPROC)(GLuint program, GLenum binaryFormat, const void * binary, GLsizei length);
typedef void (APIENTRYP PFNGLGETSHADERSOURCEPROC)(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source);
typedef void (APIENTRYP PFNGLTEXCOORDP1UIVPROC)(GLenum type, const GLuint * coords);
typedef void (APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC)(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision);
typedef void (APIENTRYP PFNGLCOMPILESHADERPROC)(GLuint shader);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBLDVPROC)(GLuint index, GLenum pname, GLdouble * params);
typedef void (APIENTRYP PFNGLGENERATETEXTUREMIPMAPPROC)(GLuint texture);
typedef void (APIENTRYP PFNGLBINDFRAMEBUFFERPROC)(GLenum target, GLuint framebuffer);
typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
typedef void (APIENTRYP PFNGLTEXCOORDP2UIPROC)(GLenum type, GLuint coords);
typedef void (APIENTRYP PFNGLBLENDFUNCIPROC)(GLuint buf, GLenum src, GLenum dst);
typedef void (APIENTRYP PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLUNIFORM2IVPROC)(GLint location, GLsizei count, const GLint * value);
typedef GLboolean (APIENTRYP PFNGLUNMAPNAMEDBUFFERPROC)(GLuint buffer);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3SPROC)(GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4SVPROC)(GLuint index, const GLshort * v);
typedef void (APIENTRYP PFNGLPAUSETRANSFORMFEEDBACKPROC)();
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IVPROC)(GLuint index, const GLint * v);
typedef void (APIENTRYP PFNGLTEXCOORDP2UIVPROC)(GLenum type, const GLuint * coords);
typedef void (APIENTRYP PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC)(GLuint program, GLuint bufferIndex, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLGETACTIVEATTRIBPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC)(GLuint index, GLenum pname, void ** pointer);
typedef void (APIENTRYP PFNGLUNIFORM2UIPROC)(GLint location, GLuint v0, GLuint v1);
typedef void (APIENTRYP PFNGLTEXCOORDP3UIPROC)(GLenum type, GLuint coords);
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINENAMEPROC)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UBVPROC)(GLuint index, const GLubyte * v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3SVPROC)(GLuint index, const GLshort * v);
typedef void (APIENTRYP PFNGLBINDIMAGETEXTUREPROC)(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBDVPROC)(GLuint index, GLenum pname, GLdouble * params);
typedef void (APIENTRYP PFNGLBLITFRAMEBUFFERPROC)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName);
typedef void (APIENTRYP PFNGLTEXCOORDP3UIVPROC)(GLenum type, const GLuint * coords);
typedef void (APIENTRYP PFNGLBINDIMAGETEXTURESPROC)(GLuint first, GLsizei count, const GLuint * textures);
typedef const GLubyte * (APIENTRYP PFNGLGETSTRINGPROC)(GLenum name);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMNAMEPROC)(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIPROC)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE1DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data);
typedef void (APIENTRYP PFNGLTEXCOORDP4UIPROC)(GLenum type, GLuint coords);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBFVPROC)(GLuint index, GLenum pname, GLfloat * params);
typedef const GLubyte * (APIENTRYP PFNGLGETSTRINGIPROC)(GLenum name, GLuint index);
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NBVPROC)(GLuint index, const GLbyte * v);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data);
typedef void (APIENTRYP PFNGLTEXCOORDP4UIVPROC)(GLenum type, const GLuint * coords);
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values);
typedef void (APIENTRYP PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void * data, GLenum usage);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
typedef void (APIENTRYP PFNGLUSEPROGRAMPROC)(GLuint program);
typedef void (APIENTRYP PFNGLBLITNAMEDFRAMEBUFFERPROC)(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef GLuint (APIENTRYP PFNGLGETSUBROUTINEINDEXPROC)(GLuint program, GLenum shadertype, const GLchar * name);
typedef void (APIENTRYP PFNGLPIXELSTOREFPROC)(GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIVPROC)(GLuint index, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLUNIFORM3DVPROC)(GLint location, GLsizei count, const GLdouble * value);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NIVPROC)(GLuint index, const GLint * v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4USVPROC)(GLuint index, const GLushort * v);
typedef void (APIENTRYP PFNGLUNIFORM2UIVPROC)(GLint location, GLsizei count, const GLuint * value);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC)(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC)(GLuint index, const GLuint * v);
typedef GLint (APIENTRYP PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)(GLuint program, GLenum shadertype, const GLchar * name);
typedef void (APIENTRYP PFNGLPIXELSTOREIPROC)(GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLUSEPROGRAMSTAGESPROC)(GLuint pipeline, GLbitfield stages, GLuint program);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERFVPROC)(GLuint texture, GLenum pname, const GLfloat * param);
typedef void (APIENTRYP PFNGLGETSYNCIVPROC)(GLsync sync, GLenum pname, GLsizei count, GLsizei * length, GLint * values);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIIVPROC)(GLuint texture, GLenum pname, const GLint * params);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC)(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLFRAMEBUFFERPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NSVPROC)(GLuint index, const GLshort * v);
typedef void (APIENTRYP PFNGLUNIFORM3DPROC)(GLint location, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLVERTEXATTRIBIFORMATPROC)(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIUIVPROC)(GLuint texture, GLenum pname, const GLuint * params);
typedef void (APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLGETATTACHEDSHADERSPROC)(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders);
typedef void (APIENTRYP PFNGLBINDPROGRAMPIPELINEPROC)(GLuint pipeline);
typedef void (APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC)(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERFPROC)(GLuint texture, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLUNIFORM3FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBPROC)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data);
typedef GLint (APIENTRYP PFNGLGETATTRIBLOCATIONPROC)(GLuint program, const GLchar * name);
typedef void (APIENTRYP PFNGLUNIFORM3FVPROC)(GLint location, GLsizei count, const GLfloat * value);
typedef void (APIENTRYP PFNGLBINDRENDERBUFFERPROC)(GLenum target, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLBUFFERSTORAGEPROC)(GLenum target, GLsizeiptr size, const void * data, GLbitfield flags);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIPROC)(GLuint texture, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1DPROC)(GLuint index, GLdouble x);
typedef void (APIENTRYP PFNGLGETBOOLEANI_VPROC)(GLenum target, GLuint index, GLboolean * data);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1DVPROC)(GLuint index, const GLdouble * v);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIVPROC)(GLuint texture, GLenum pname, const GLint * param);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUIVPROC)(GLuint index, const GLuint * v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBVPROC)(GLuint index, const GLubyte * v);
typedef void (APIENTRYP PFNGLBINDSAMPLERPROC)(GLuint unit, GLuint sampler);
typedef void (APIENTRYP PFNGLGETBOOLEANVPROC)(GLenum pname, GLboolean * data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data);
typedef void (APIENTRYP PFNGLUNIFORM3IPROC)(GLint location, GLint v0, GLint v1, GLint v2);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE1DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTUREPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLBINDSAMPLERSPROC)(GLuint first, GLsizei count, const GLuint * samplers);
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERI64VPROC)(GLenum target, GLenum pname, GLint64 * params);
typedef void (APIENTRYP PFNGLGETNCOLORTABLEPROC)(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void * table);
typedef void (APIENTRYP PFNGLBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, const void * data);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUSVPROC)(GLuint index, const GLushort * v);
typedef GLsync (APIENTRYP PFNGLFENCESYNCPROC)(GLenum condition, GLbitfield flags);
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE1DPROC)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC)(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4BVPROC)(GLuint index, const GLbyte * v);
typedef void (APIENTRYP PFNGLBINDTEXTUREPROC)(GLenum target, GLuint texture);
typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPROC)(GLuint program);
typedef void (APIENTRYP PFNGLGETBUFFERPOINTERVPROC)(GLenum target, GLenum pname, void ** params);
typedef void (APIENTRYP PFNGLGETNCONVOLUTIONFILTERPROC)(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void * image);
typedef void (APIENTRYP PFNGLGETNCOMPRESSEDTEXIMAGEPROC)(GLenum target, GLint lod, GLsizei bufSize, void * pixels);
typedef void (APIENTRYP PFNGLACTIVESHADERPROGRAMPROC)(GLuint pipeline, GLuint program);
typedef void (APIENTRYP PFNGLFINISHPROC)();
typedef void (APIENTRYP PFNGLGETBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, void * data);
typedef void (APIENTRYP PFNGLINVALIDATEBUFFERSUBDATAPROC)(GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE2DPROC)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRYP PFNGLPROGRAMPARAMETERIPROC)(GLuint program, GLenum pname, GLint value);
typedef void (APIENTRYP PFNGLBINDTEXTUREUNITPROC)(GLuint unit, GLuint texture);
typedef void (APIENTRYP PFNGLUNIFORM3IVPROC)(GLint location, GLsizei count, const GLint * value);
typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEPROC)(GLuint pipeline);
typedef void (APIENTRYP PFNGLINVALIDATEBUFFERDATAPROC)(GLuint buffer);
typedef GLenum (APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC)(GLenum target);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE3DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC)(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL2DPROC)(GLuint index, GLdouble x, GLdouble y);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data);
typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC)(GLenum texture);
typedef void (APIENTRYP PFNGLGETNHISTOGRAMPROC)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void * values);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP1UIVPROC)(GLenum texture, GLenum type, const GLuint * coords);
typedef void (APIENTRYP PFNGLBINDTEXTURESPROC)(GLuint first, GLsizei count, const GLuint * textures);
typedef void (APIENTRYP PFNGLGETTEXIMAGEPROC)(GLenum target, GLint level, GLenum format, GLenum type, void * pixels);
typedef void (APIENTRYP PFNGLUNIFORM3UIPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE3DPROC)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP2UIVPROC)(GLenum texture, GLenum type, const GLuint * coords);
typedef void (APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC)(GLenum target, GLsizei numAttachments, const GLenum * attachments);
typedef void (APIENTRYP PFNGLBINDTRANSFORMFEEDBACKPROC)(GLenum target, GLuint id);
typedef void (APIENTRYP PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC)(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments);
typedef void (APIENTRYP PFNGLGETNMAPDVPROC)(GLenum target, GLenum query, GLsizei bufSize, GLdouble * v);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP1UIPROC)(GLenum texture, GLenum type, GLuint coords);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL2DVPROC)(GLuint index, const GLdouble * v);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC)(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLGETNMAPFVPROC)(GLenum target, GLenum query, GLsizei bufSize, GLfloat * v);
typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC)(GLenum target, GLint level, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP2UIPROC)(GLenum texture, GLenum type, GLuint coords);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DPROC)(GLuint program, GLint location, GLdouble v0);
typedef void (APIENTRYP PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC)(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height);
typedef GLboolean (APIENTRYP PFNGLISBUFFERPROC)(GLuint buffer);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4DVPROC)(GLuint index, const GLdouble * v);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, GLint * params);
typedef GLenum (APIENTRYP PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC)(GLuint framebuffer, GLenum target);
typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC)(GLuint array);
typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC)(GLenum target, GLint level, GLenum pname, GLfloat * params);
typedef void (APIENTRYP PFNGLINVALIDATETEXSUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
typedef void (APIENTRYP PFNGLGETNMAPIVPROC)(GLenum target, GLenum query, GLsizei bufSize, GLint * v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP3UIPROC)(GLenum texture, GLenum type, GLuint coords);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
typedef void (APIENTRYP PFNGLINVALIDATESUBFRAMEBUFFERPROC)(GLenum target, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIVPROC)(GLenum target, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (APIENTRYP PFNGLPOINTPARAMETERFPROC)(GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP3UIVPROC)(GLenum texture, GLenum type, const GLuint * coords);
typedef void (APIENTRYP PFNGLCLAMPCOLORPROC)(GLenum target, GLenum clamp);
typedef void (APIENTRYP PFNGLINVALIDATETEXIMAGEPROC)(GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP4UIPROC)(GLenum texture, GLenum type, GLuint coords);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FPROC)(GLuint program, GLint location, GLfloat v0);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, GLuint * params);
typedef void (APIENTRYP PFNGLGETNMINMAXPROC)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void * values);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP4UIVPROC)(GLenum texture, GLenum type, const GLuint * coords);
typedef void (APIENTRYP PFNGLFLUSHPROC)();
typedef void (APIENTRYP PFNGLUNIFORM3UIVPROC)(GLint location, GLsizei count, const GLuint * value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE1DPROC)(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels);
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE3DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels);
typedef void (APIENTRYP PFNGLFRONTFACEPROC)(GLenum mode);
typedef void (APIENTRYP PFNGLCLEARPROC)(GLbitfield mask);
typedef void (APIENTRYP PFNGLPOINTPARAMETERFVPROC)(GLenum pname, const GLfloat * params);
typedef void (APIENTRYP PFNGLVIEWPORTARRAYVPROC)(GLuint first, GLsizei count, const GLfloat * v);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERFVPROC)(GLenum target, GLenum pname, GLfloat * params);
typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERPROC)(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC)(GLuint xfb, GLuint index, GLuint buffer);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IPROC)(GLuint program, GLint location, GLint v0);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL3DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEPROC)(GLenum target, GLintptr offset, GLsizeiptr length);
typedef void (APIENTRYP PFNGLUNIFORM4DPROC)(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRYP PFNGLGETNPIXELMAPUIVPROC)(GLenum map, GLsizei bufSize, GLuint * values);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4FVPROC)(GLuint index, const GLfloat * v);
typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERSPROC)(GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides);
typedef void (APIENTRYP PFNGLVIEWPORTPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC)(GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE2DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
typedef void (APIENTRYP PFNGLGETNPIXELMAPFVPROC)(GLenum map, GLsizei bufSize, GLfloat * values);
typedef void (APIENTRYP PFNGLUNIFORM4FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (APIENTRYP PFNGLTEXIMAGE1DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL3DVPROC)(GLuint index, const GLdouble * v);
typedef void (APIENTRYP PFNGLCLEARBUFFERDATAPROC)(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void * data);
typedef void (APIENTRYP PFNGLTEXTUREVIEWPROC)(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
typedef void (APIENTRYP PFNGLCOPYBUFFERSUBDATAPROC)(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLGETNPIXELMAPUSVPROC)(GLenum map, GLsizei bufSize, GLushort * values);
typedef void (APIENTRYP PFNGLPOINTPARAMETERIPROC)(GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4IVPROC)(GLuint index, const GLint * v);
typedef void (APIENTRYP PFNGLUNIFORM4DVPROC)(GLint location, GLsizei count, const GLdouble * value);
typedef void (APIENTRYP PFNGLGETNPOLYGONSTIPPLEPROC)(GLsizei bufSize, GLubyte * pattern);
typedef GLboolean (APIENTRYP PFNGLISENABLEDPROC)(GLenum cap);
typedef void (APIENTRYP PFNGLUNIFORM4IPROC)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (APIENTRYP PFNGLTEXIMAGE2DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IVPROC)(GLuint program, GLint location, GLsizei count, const GLint * value);
typedef void (APIENTRYP PFNGLVIEWPORTINDEXEDFPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
typedef void (APIENTRYP PFNGLCLEARBUFFERIVPROC)(GLenum buffer, GLint drawbuffer, const GLint * value);
typedef void (APIENTRYP PFNGLTEXIMAGE2DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (APIENTRYP PFNGLGETTEXTUREIMAGEPROC)(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels);
typedef void (APIENTRYP PFNGLTEXIMAGE3DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (APIENTRYP PFNGLGETNTEXIMAGEPROC)(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels);
typedef void (APIENTRYP PFNGLPOINTPARAMETERIVPROC)(GLenum pname, const GLint * params);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4SPROC)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (APIENTRYP PFNGLCLEARBUFFERSUBDATAPROC)(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data);
typedef void (APIENTRYP PFNGLCLEARBUFFERFVPROC)(GLenum buffer, GLint drawbuffer, const GLfloat * value);
typedef void (APIENTRYP PFNGLGETTEXTURELEVELPARAMETERIVPROC)(GLuint texture, GLint level, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLGETNSEPARABLEFILTERPROC)(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void * row, GLsizei columnBufSize, void * column, void * span);
typedef void (APIENTRYP PFNGLUNIFORM4FVPROC)(GLint location, GLsizei count, const GLfloat * value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIPROC)(GLuint program, GLint location, GLuint v0);
typedef void (APIENTRYP PFNGLCLEARBUFFERFIPROC)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
typedef GLboolean (APIENTRYP PFNGLISENABLEDIPROC)(GLenum target, GLuint index);
typedef void (APIENTRYP PFNGLCOPYIMAGESUBDATAPROC)(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC)(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL4DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC)(GLuint texture, GLint level, GLsizei bufSize, void * pixels);
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXIMAGEPROC)(GLenum target, GLint level, void * img);
typedef void (APIENTRYP PFNGLGENBUFFERSPROC)(GLsizei n, GLuint * buffers);
typedef void (APIENTRYP PFNGLCLEARBUFFERUIVPROC)(GLenum buffer, GLint drawbuffer, const GLuint * value);
typedef void (APIENTRYP PFNGLTEXIMAGE3DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLVIEWPORTINDEXEDFVPROC)(GLuint index, const GLfloat * v);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIIVPROC)(GLuint texture, GLenum pname, GLint * params);
typedef void (APIENTRYP PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC)(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode);
typedef void (APIENTRYP PFNGLGETTEXTURELEVELPARAMETERFVPROC)(GLuint texture, GLint level, GLenum pname, GLfloat * params);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint * value);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIUIVPROC)(GLuint texture, GLenum pname, GLuint * params);
typedef void (APIENTRYP PFNGLGETNUNIFORMDVPROC)(GLuint program, GLint location, GLsizei bufSize, GLdouble * params);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4SVPROC)(GLuint index, const GLshort * v);
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void * pixels);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL4DVPROC)(GLuint index, const GLdouble * v);

PFNGLDRAWBUFFERPROC pfn_glDrawBuffer;
PFNGLLINEWIDTHPROC pfn_glLineWidth;
PFNGLDRAWBUFFERSPROC pfn_glDrawBuffers;
PFNGLPROGRAMUNIFORM2DVPROC pfn_glProgramUniform2dv;
PFNGLPROGRAMUNIFORM2FPROC pfn_glProgramUniform2f;
PFNGLGETDEBUGMESSAGELOGPROC pfn_glGetDebugMessageLog;
PFNGLDELETEPROGRAMPROC pfn_glDeleteProgram;
PFNGLISFRAMEBUFFERPROC pfn_glIsFramebuffer;
PFNGLCOPYNAMEDBUFFERSUBDATAPROC pfn_glCopyNamedBufferSubData;
PFNGLQUERYCOUNTERPROC pfn_glQueryCounter;
PFNGLPROGRAMUNIFORM2FVPROC pfn_glProgramUniform2fv;
PFNGLPROGRAMUNIFORM2IPROC pfn_glProgramUniform2i;
PFNGLDELETEPROGRAMPIPELINESPROC pfn_glDeleteProgramPipelines;
PFNGLLINKPROGRAMPROC pfn_glLinkProgram;
PFNGLGETDOUBLEI_VPROC pfn_glGetDoublei_v;
PFNGLCOPYTEXIMAGE2DPROC pfn_glCopyTexImage2D;
PFNGLPROGRAMUNIFORM2IVPROC pfn_glProgramUniform2iv;
PFNGLDELETEQUERIESPROC pfn_glDeleteQueries;
PFNGLCOPYTEXIMAGE1DPROC pfn_glCopyTexImage1D;
PFNGLGETDOUBLEVPROC pfn_glGetDoublev;
PFNGLPROGRAMUNIFORM2UIPROC pfn_glProgramUniform2ui;
PFNGLGETERRORPROC pfn_glGetError;
PFNGLCOPYTEXSUBIMAGE1DPROC pfn_glCopyTexSubImage1D;
PFNGLDELETERENDERBUFFERSPROC pfn_glDeleteRenderbuffers;
PFNGLDRAWELEMENTSPROC pfn_glDrawElements;
PFNGLPROGRAMUNIFORM2UIVPROC pfn_glProgramUniform2uiv;
PFNGLCOPYTEXSUBIMAGE2DPROC pfn_glCopyTexSubImage2D;
PFNGLDELETESAMPLERSPROC pfn_glDeleteSamplers;
PFNGLDRAWELEMENTSBASEVERTEXPROC pfn_glDrawElementsBaseVertex;
PFNGLCOPYTEXSUBIMAGE3DPROC pfn_glCopyTexSubImage3D;
PFNGLPROGRAMUNIFORM3DPROC pfn_glProgramUniform3d;
PFNGLNAMEDBUFFERDATAPROC pfn_glNamedBufferData;
PFNGLDRAWELEMENTSINSTANCEDPROC pfn_glDrawElementsInstanced;
PFNGLDELETESHADERPROC pfn_glDeleteShader;
PFNGLPROGRAMUNIFORM3FPROC pfn_glProgramUniform3f;
PFNGLCOPYTEXTURESUBIMAGE1DPROC pfn_glCopyTextureSubImage1D;
PFNGLDRAWELEMENTSINDIRECTPROC pfn_glDrawElementsIndirect;
PFNGLPROGRAMUNIFORM3DVPROC pfn_glProgramUniform3dv;
PFNGLDELETESYNCPROC pfn_glDeleteSync;
PFNGLPROGRAMUNIFORM3IPROC pfn_glProgramUniform3i;
PFNGLNAMEDBUFFERSUBDATAPROC pfn_glNamedBufferSubData;
PFNGLCOPYTEXTURESUBIMAGE3DPROC pfn_glCopyTextureSubImage3D;
PFNGLCOPYTEXTURESUBIMAGE2DPROC pfn_glCopyTextureSubImage2D;
PFNGLNAMEDBUFFERSTORAGEPROC pfn_glNamedBufferStorage;
PFNGLGETMULTISAMPLEFVPROC pfn_glGetMultisamplefv;
PFNGLPROGRAMUNIFORM3FVPROC pfn_glProgramUniform3fv;
PFNGLGETFLOATI_VPROC pfn_glGetFloati_v;
PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC pfn_glDrawElementsInstancedBaseInstance;
PFNGLISPROGRAMPROC pfn_glIsProgram;
PFNGLGETNAMEDBUFFERPARAMETERI64VPROC pfn_glGetNamedBufferParameteri64v;
PFNGLDELETETEXTURESPROC pfn_glDeleteTextures;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC pfn_glDrawElementsInstancedBaseVertex;
PFNGLGETNAMEDBUFFERPARAMETERIVPROC pfn_glGetNamedBufferParameteriv;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC pfn_glDrawElementsInstancedBaseVertexBaseInstance;
PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC pfn_glNamedFramebufferDrawBuffers;
PFNGLSECONDARYCOLORP3UIVPROC pfn_glSecondaryColorP3uiv;
PFNGLSECONDARYCOLORP3UIPROC pfn_glSecondaryColorP3ui;
PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC pfn_glNamedFramebufferDrawBuffer;
PFNGLGETNAMEDBUFFERPOINTERVPROC pfn_glGetNamedBufferPointerv;
PFNGLGETFLOATVPROC pfn_glGetFloatv;
PFNGLDELETETRANSFORMFEEDBACKSPROC pfn_glDeleteTransformFeedbacks;
PFNGLISPROGRAMPIPELINEPROC pfn_glIsProgramPipeline;
PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC pfn_glNamedFramebufferParameteri;
PFNGLGETNAMEDBUFFERSUBDATAPROC pfn_glGetNamedBufferSubData;
PFNGLPROGRAMUNIFORM3UIPROC pfn_glProgramUniform3ui;
PFNGLPROGRAMUNIFORM3IVPROC pfn_glProgramUniform3iv;
PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC pfn_glNamedFramebufferReadBuffer;
PFNGLDELETEVERTEXARRAYSPROC pfn_glDeleteVertexArrays;
PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC pfn_glNamedFramebufferRenderbuffer;
PFNGLISQUERYPROC pfn_glIsQuery;
PFNGLGETFRAGDATAINDEXPROC pfn_glGetFragDataIndex;
PFNGLMEMORYBARRIERPROC pfn_glMemoryBarrier;
PFNGLCREATEBUFFERSPROC pfn_glCreateBuffers;
PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC pfn_glGetNamedFramebufferParameteriv;
PFNGLMEMORYBARRIERBYREGIONPROC pfn_glMemoryBarrierByRegion;
PFNGLGETFRAGDATALOCATIONPROC pfn_glGetFragDataLocation;
PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC pfn_glGetNamedFramebufferAttachmentParameteriv;
PFNGLNAMEDFRAMEBUFFERTEXTUREPROC pfn_glNamedFramebufferTexture;
PFNGLCREATEFRAMEBUFFERSPROC pfn_glCreateFramebuffers;
PFNGLLOGICOPPROC pfn_glLogicOp;
PFNGLDRAWRANGEELEMENTSPROC pfn_glDrawRangeElements;
PFNGLPROGRAMUNIFORM4DPROC pfn_glProgramUniform4d;
PFNGLISRENDERBUFFERPROC pfn_glIsRenderbuffer;
PFNGLPROGRAMUNIFORM3UIVPROC pfn_glProgramUniform3uiv;
PFNGLMINSAMPLESHADINGPROC pfn_glMinSampleShading;
PFNGLCREATEPROGRAMPROC pfn_glCreateProgram;
PFNGLPROGRAMUNIFORM4FPROC pfn_glProgramUniform4f;
PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC pfn_glDrawRangeElementsBaseVertex;
PFNGLDEPTHFUNCPROC pfn_glDepthFunc;
PFNGLPROGRAMUNIFORM4DVPROC pfn_glProgramUniform4dv;
PFNGLDEPTHMASKPROC pfn_glDepthMask;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC pfn_glGetFramebufferAttachmentParameteriv;
PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC pfn_glGetNamedRenderbufferParameteriv;
PFNGLPROGRAMUNIFORM4IPROC pfn_glProgramUniform4i;
PFNGLCREATEPROGRAMPIPELINESPROC pfn_glCreateProgramPipelines;
PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC pfn_glNamedFramebufferTextureLayer;
PFNGLDEPTHRANGEPROC pfn_glDepthRange;
PFNGLISSAMPLERPROC pfn_glIsSampler;
PFNGLPROGRAMUNIFORM4FVPROC pfn_glProgramUniform4fv;
PFNGLRESUMETRANSFORMFEEDBACKPROC pfn_glResumeTransformFeedback;
PFNGLGETOBJECTLABELPROC pfn_glGetObjectLabel;
PFNGLCREATEQUERIESPROC pfn_glCreateQueries;
PFNGLISSHADERPROC pfn_glIsShader;
PFNGLGETNUNIFORMFVPROC pfn_glGetnUniformfv;
PFNGLCREATERENDERBUFFERSPROC pfn_glCreateRenderbuffers;
PFNGLGETFRAMEBUFFERPARAMETERIVPROC pfn_glGetFramebufferParameteriv;
PFNGLSHADERBINARYPROC pfn_glShaderBinary;
PFNGLGETGRAPHICSRESETSTATUSPROC pfn_glGetGraphicsResetStatus;
PFNGLCREATESAMPLERSPROC pfn_glCreateSamplers;
PFNGLDEPTHRANGEARRAYVPROC pfn_glDepthRangeArrayv;
PFNGLISSYNCPROC pfn_glIsSync;
PFNGLDEPTHRANGEINDEXEDPROC pfn_glDepthRangeIndexed;
PFNGLCREATESHADERPROC pfn_glCreateShader;
PFNGLPROGRAMUNIFORM4UIPROC pfn_glProgramUniform4ui;
PFNGLPROGRAMUNIFORM4IVPROC pfn_glProgramUniform4iv;
PFNGLGETOBJECTPTRLABELPROC pfn_glGetObjectPtrLabel;
PFNGLSAMPLECOVERAGEPROC pfn_glSampleCoverage;
PFNGLDRAWTRANSFORMFEEDBACKPROC pfn_glDrawTransformFeedback;
PFNGLISTEXTUREPROC pfn_glIsTexture;
PFNGLSHADERSTORAGEBLOCKBINDINGPROC pfn_glShaderStorageBlockBinding;
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC pfn_glNamedRenderbufferStorageMultisample;
PFNGLCREATESHADERPROGRAMVPROC pfn_glCreateShaderProgramv;
PFNGLNAMEDRENDERBUFFERSTORAGEPROC pfn_glNamedRenderbufferStorage;
PFNGLDEPTHRANGEFPROC pfn_glDepthRangef;
PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC pfn_glDrawTransformFeedbackInstanced;
PFNGLSHADERSOURCEPROC pfn_glShaderSource;
PFNGLPROGRAMUNIFORM4UIVPROC pfn_glProgramUniform4uiv;
PFNGLCREATETEXTURESPROC pfn_glCreateTextures;
PFNGLMULTIDRAWARRAYSPROC pfn_glMultiDrawArrays;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC pfn_glDrawTransformFeedbackStream;
PFNGLVERTEXARRAYATTRIBBINDINGPROC pfn_glVertexArrayAttribBinding;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC pfn_glDrawTransformFeedbackStreamInstanced;
PFNGLCREATEVERTEXARRAYSPROC pfn_glCreateVertexArrays;
PFNGLISTRANSFORMFEEDBACKPROC pfn_glIsTransformFeedback;
PFNGLCREATETRANSFORMFEEDBACKSPROC pfn_glCreateTransformFeedbacks;
PFNGLVERTEXARRAYATTRIBFORMATPROC pfn_glVertexArrayAttribFormat;
PFNGLPROGRAMUNIFORMMATRIX2DVPROC pfn_glProgramUniformMatrix2dv;
PFNGLREADBUFFERPROC pfn_glReadBuffer;
PFNGLMAPBUFFERRANGEPROC pfn_glMapBufferRange;
PFNGLMULTIDRAWARRAYSINDIRECTPROC pfn_glMultiDrawArraysIndirect;
PFNGLCULLFACEPROC pfn_glCullFace;
PFNGLMAPBUFFERPROC pfn_glMapBuffer;
PFNGLVERTEXARRAYATTRIBIFORMATPROC pfn_glVertexArrayAttribIFormat;
PFNGLDETACHSHADERPROC pfn_glDetachShader;
PFNGLVERTEXARRAYATTRIBLFORMATPROC pfn_glVertexArrayAttribLFormat;
PFNGLSAMPLEMASKIPROC pfn_glSampleMaski;
PFNGLISVERTEXARRAYPROC pfn_glIsVertexArray;
PFNGLPROGRAMUNIFORMMATRIX2FVPROC pfn_glProgramUniformMatrix2fv;
PFNGLVERTEXARRAYBINDINGDIVISORPROC pfn_glVertexArrayBindingDivisor;
PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC pfn_glMultiDrawArraysIndirectCount;
PFNGLDISABLEPROC pfn_glDisable;
PFNGLVERTEXARRAYELEMENTBUFFERPROC pfn_glVertexArrayElementBuffer;
PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC pfn_glProgramUniformMatrix2x3dv;
PFNGLREADPIXELSPROC pfn_glReadPixels;
PFNGLMULTIDRAWELEMENTSPROC pfn_glMultiDrawElements;
PFNGLSAMPLERPARAMETERIIVPROC pfn_glSamplerParameterIiv;
PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC pfn_glProgramUniformMatrix2x3fv;
PFNGLSPECIALIZESHADERPROC pfn_glSpecializeShader;
PFNGLGETINTEGER64I_VPROC pfn_glGetInteger64i_v;
PFNGLDEBUGMESSAGECALLBACKPROC pfn_glDebugMessageCallback;
PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC pfn_glMultiDrawElementsBaseVertex;
PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC pfn_glProgramUniformMatrix2x4dv;
PFNGLSAMPLERPARAMETERIUIVPROC pfn_glSamplerParameterIuiv;
PFNGLGETINTEGER64VPROC pfn_glGetInteger64v;
PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC pfn_glProgramUniformMatrix2x4fv;
PFNGLREADNPIXELSPROC pfn_glReadnPixels;
PFNGLMULTIDRAWELEMENTSINDIRECTPROC pfn_glMultiDrawElementsIndirect;
PFNGLSAMPLERPARAMETERFPROC pfn_glSamplerParameterf;
PFNGLDEBUGMESSAGECONTROLPROC pfn_glDebugMessageControl;
PFNGLPROGRAMUNIFORMMATRIX3DVPROC pfn_glProgramUniformMatrix3dv;
PFNGLSAMPLERPARAMETERFVPROC pfn_glSamplerParameterfv;
PFNGLMAPNAMEDBUFFERRANGEPROC pfn_glMapNamedBufferRange;
PFNGLENABLEPROC pfn_glEnable;
PFNGLSAMPLERPARAMETERIPROC pfn_glSamplerParameteri;
PFNGLPROGRAMUNIFORMMATRIX3FVPROC pfn_glProgramUniformMatrix3fv;
PFNGLDISABLEVERTEXARRAYATTRIBPROC pfn_glDisableVertexArrayAttrib;
PFNGLGETINTEGERI_VPROC pfn_glGetIntegeri_v;
PFNGLSAMPLERPARAMETERIVPROC pfn_glSamplerParameteriv;
PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC pfn_glMultiDrawElementsIndirectCount;
PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC pfn_glProgramUniformMatrix3x2dv;
PFNGLDEBUGMESSAGEINSERTPROC pfn_glDebugMessageInsert;
PFNGLGETINTEGERVPROC pfn_glGetIntegerv;
PFNGLMAPNAMEDBUFFERPROC pfn_glMapNamedBuffer;
PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC pfn_glProgramUniformMatrix3x2fv;
PFNGLVERTEXARRAYVERTEXBUFFERPROC pfn_glVertexArrayVertexBuffer;
PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC pfn_glProgramUniformMatrix3x4dv;
PFNGLDISABLEVERTEXATTRIBARRAYPROC pfn_glDisableVertexAttribArray;
PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC pfn_glProgramUniformMatrix3x4fv;
PFNGLSTENCILFUNCPROC pfn_glStencilFunc;
PFNGLPROGRAMUNIFORMMATRIX4DVPROC pfn_glProgramUniformMatrix4dv;
PFNGLGETINTERNALFORMATIVPROC pfn_glGetInternalformativ;
PFNGLSCISSORPROC pfn_glScissor;
PFNGLDISABLEIPROC pfn_glDisablei;
PFNGLSTENCILFUNCSEPARATEPROC pfn_glStencilFuncSeparate;
PFNGLPROGRAMUNIFORMMATRIX4FVPROC pfn_glProgramUniformMatrix4fv;
PFNGLENABLEVERTEXARRAYATTRIBPROC pfn_glEnableVertexArrayAttrib;
PFNGLDELETEBUFFERSPROC pfn_glDeleteBuffers;
PFNGLGETINTERNALFORMATI64VPROC pfn_glGetInternalformati64v;
PFNGLSCISSORARRAYVPROC pfn_glScissorArrayv;
PFNGLVERTEXARRAYVERTEXBUFFERSPROC pfn_glVertexArrayVertexBuffers;
PFNGLSTENCILMASKPROC pfn_glStencilMask;
PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC pfn_glProgramUniformMatrix4x2dv;
PFNGLSTENCILMASKSEPARATEPROC pfn_glStencilMaskSeparate;
PFNGLVERTEXATTRIB1DPROC pfn_glVertexAttrib1d;
PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC pfn_glProgramUniformMatrix4x2fv;
PFNGLSTENCILOPPROC pfn_glStencilOp;
PFNGLVERTEXATTRIB1DVPROC pfn_glVertexAttrib1dv;
PFNGLNORMALP3UIPROC pfn_glNormalP3ui;
PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC pfn_glProgramUniformMatrix4x3dv;
PFNGLSTENCILOPSEPARATEPROC pfn_glStencilOpSeparate;
PFNGLENABLEVERTEXATTRIBARRAYPROC pfn_glEnableVertexAttribArray;
PFNGLNORMALP3UIVPROC pfn_glNormalP3uiv;
PFNGLSCISSORINDEXEDPROC pfn_glScissorIndexed;
PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC pfn_glProgramUniformMatrix4x3fv;
PFNGLPROVOKINGVERTEXPROC pfn_glProvokingVertex;
PFNGLDISPATCHCOMPUTEPROC pfn_glDispatchCompute;
PFNGLDELETEFRAMEBUFFERSPROC pfn_glDeleteFramebuffers;
PFNGLVERTEXATTRIB1FPROC pfn_glVertexAttrib1f;
PFNGLENABLEIPROC pfn_glEnablei;
PFNGLDRAWARRAYSPROC pfn_glDrawArrays;
PFNGLGETPROGRAMBINARYPROC pfn_glGetProgramBinary;
PFNGLRELEASESHADERCOMPILERPROC pfn_glReleaseShaderCompiler;
PFNGLDISPATCHCOMPUTEINDIRECTPROC pfn_glDispatchComputeIndirect;
PFNGLGETPROGRAMINFOLOGPROC pfn_glGetProgramInfoLog;
PFNGLDRAWARRAYSINSTANCEDPROC pfn_glDrawArraysInstanced;
PFNGLSCISSORINDEXEDVPROC pfn_glScissorIndexedv;
PFNGLVERTEXATTRIB1FVPROC pfn_glVertexAttrib1fv;
PFNGLDRAWARRAYSINDIRECTPROC pfn_glDrawArraysIndirect;
PFNGLRENDERBUFFERSTORAGEPROC pfn_glRenderbufferStorage;
PFNGLGETPROGRAMINTERFACEIVPROC pfn_glGetProgramInterfaceiv;
PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC pfn_glDrawArraysInstancedBaseInstance;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC pfn_glRenderbufferStorageMultisample;
PFNGLPUSHDEBUGGROUPPROC pfn_glPushDebugGroup;
PFNGLENDCONDITIONALRENDERPROC pfn_glEndConditionalRender;
PFNGLWAITSYNCPROC pfn_glWaitSync;
PFNGLPOINTSIZEPROC pfn_glPointSize;
PFNGLUNIFORM4UIPROC pfn_glUniform4ui;
PFNGLTEXPARAMETERIIVPROC pfn_glTexParameterIiv;
PFNGLVERTEXATTRIB1SPROC pfn_glVertexAttrib1s;
PFNGLGETTEXTUREPARAMETERFVPROC pfn_glGetTextureParameterfv;
PFNGLCLEARDEPTHPROC pfn_glClearDepth;
PFNGLGETTEXTUREPARAMETERIVPROC pfn_glGetTextureParameteriv;
PFNGLVERTEXATTRIBLFORMATPROC pfn_glVertexAttribLFormat;
PFNGLOBJECTLABELPROC pfn_glObjectLabel;
PFNGLUNIFORM4IVPROC pfn_glUniform4iv;
PFNGLVERTEXATTRIB4UBVPROC pfn_glVertexAttrib4ubv;
PFNGLGENFRAMEBUFFERSPROC pfn_glGenFramebuffers;
PFNGLVERTEXATTRIB4UIVPROC pfn_glVertexAttrib4uiv;
PFNGLTEXPARAMETERIUIVPROC pfn_glTexParameterIuiv;
PFNGLGETNUNIFORMIVPROC pfn_glGetnUniformiv;
PFNGLVERTEXATTRIB1SVPROC pfn_glVertexAttrib1sv;
PFNGLGETPROGRAMPIPELINEINFOLOGPROC pfn_glGetProgramPipelineInfoLog;
PFNGLVERTEXATTRIBLPOINTERPROC pfn_glVertexAttribLPointer;
PFNGLOBJECTPTRLABELPROC pfn_glObjectPtrLabel;
PFNGLCLEARDEPTHFPROC pfn_glClearDepthf;
PFNGLTEXPARAMETERFPROC pfn_glTexParameterf;
PFNGLUNIFORM1DPROC pfn_glUniform1d;
PFNGLGETPROGRAMPIPELINEIVPROC pfn_glGetProgramPipelineiv;
PFNGLVERTEXATTRIB4USVPROC pfn_glVertexAttrib4usv;
PFNGLGETTEXTURESUBIMAGEPROC pfn_glGetTextureSubImage;
PFNGLVERTEXATTRIBP2UIPROC pfn_glVertexAttribP2ui;
PFNGLUNIFORM1DVPROC pfn_glUniform1dv;
PFNGLVERTEXATTRIBP1UIVPROC pfn_glVertexAttribP1uiv;
PFNGLGETNUNIFORMUIVPROC pfn_glGetnUniformuiv;
PFNGLTEXPARAMETERFVPROC pfn_glTexParameterfv;
PFNGLGETPROGRAMRESOURCEINDEXPROC pfn_glGetProgramResourceIndex;
PFNGLVERTEXATTRIBP2UIVPROC pfn_glVertexAttribP2uiv;
PFNGLUNIFORM1FPROC pfn_glUniform1f;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC pfn_glGetTransformFeedbackVarying;
PFNGLVERTEXATTRIBP1UIPROC pfn_glVertexAttribP1ui;
PFNGLGETPROGRAMRESOURCELOCATIONPROC pfn_glGetProgramResourceLocation;
PFNGLTEXPARAMETERIPROC pfn_glTexParameteri;
PFNGLVERTEXATTRIB2DPROC pfn_glVertexAttrib2d;
PFNGLVERTEXATTRIBP3UIPROC pfn_glVertexAttribP3ui;
PFNGLATTACHSHADERPROC pfn_glAttachShader;
PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC pfn_glGetProgramResourceLocationIndex;
PFNGLGETTRANSFORMFEEDBACKI64_VPROC pfn_glGetTransformFeedbacki64_v;
PFNGLUNIFORMBLOCKBINDINGPROC pfn_glUniformBlockBinding;
PFNGLVERTEXATTRIBP3UIVPROC pfn_glVertexAttribP3uiv;
PFNGLPOLYGONMODEPROC pfn_glPolygonMode;
PFNGLTEXPARAMETERIVPROC pfn_glTexParameteriv;
PFNGLVERTEXATTRIBDIVISORPROC pfn_glVertexAttribDivisor;
PFNGLVERTEXATTRIBP4UIPROC pfn_glVertexAttribP4ui;
PFNGLGETPROGRAMRESOURCENAMEPROC pfn_glGetProgramResourceName;
PFNGLGETTRANSFORMFEEDBACKI_VPROC pfn_glGetTransformFeedbacki_v;
PFNGLVERTEXATTRIBP4UIVPROC pfn_glVertexAttribP4uiv;
PFNGLENDQUERYPROC pfn_glEndQuery;
PFNGLUNIFORM1FVPROC pfn_glUniform1fv;
PFNGLBEGINCONDITIONALRENDERPROC pfn_glBeginConditionalRender;
PFNGLGETPROGRAMSTAGEIVPROC pfn_glGetProgramStageiv;
PFNGLVERTEXATTRIBBINDINGPROC pfn_glVertexAttribBinding;
PFNGLGETTRANSFORMFEEDBACKIVPROC pfn_glGetTransformFeedbackiv;
PFNGLUNIFORM4UIVPROC pfn_glUniform4uiv;
PFNGLGETPROGRAMRESOURCEIVPROC pfn_glGetProgramResourceiv;
PFNGLVERTEXATTRIB2DVPROC pfn_glVertexAttrib2dv;
PFNGLVERTEXATTRIBPOINTERPROC pfn_glVertexAttribPointer;
PFNGLPOLYGONOFFSETPROC pfn_glPolygonOffset;
PFNGLGETUNIFORMBLOCKINDEXPROC pfn_glGetUniformBlockIndex;
PFNGLVERTEXATTRIBFORMATPROC pfn_glVertexAttribFormat;
PFNGLCLEARNAMEDBUFFERDATAPROC pfn_glClearNamedBufferData;
PFNGLUNIFORM1IPROC pfn_glUniform1i;
PFNGLGENPROGRAMPIPELINESPROC pfn_glGenProgramPipelines;
PFNGLPOLYGONOFFSETCLAMPPROC pfn_glPolygonOffsetClamp;
PFNGLGETUNIFORMINDICESPROC pfn_glGetUniformIndices;
PFNGLCOLORMASKPROC pfn_glColorMask;
PFNGLGETPROGRAMIVPROC pfn_glGetProgramiv;
PFNGLBLENDCOLORPROC pfn_glBlendColor;
PFNGLGETUNIFORMLOCATIONPROC pfn_glGetUniformLocation;
PFNGLTEXSTORAGE1DPROC pfn_glTexStorage1D;
PFNGLVERTEXATTRIB2FPROC pfn_glVertexAttrib2f;
PFNGLCLEARNAMEDFRAMEBUFFERFIPROC pfn_glClearNamedFramebufferfi;
PFNGLENDQUERYINDEXEDPROC pfn_glEndQueryIndexed;
PFNGLVERTEXATTRIBI1IPROC pfn_glVertexAttribI1i;
PFNGLTEXSTORAGE2DPROC pfn_glTexStorage2D;
PFNGLCLEARNAMEDBUFFERSUBDATAPROC pfn_glClearNamedBufferSubData;
PFNGLBLENDEQUATIONPROC pfn_glBlendEquation;
PFNGLVERTEXATTRIBI1IVPROC pfn_glVertexAttribI1iv;
PFNGLUNIFORMMATRIX2DVPROC pfn_glUniformMatrix2dv;
PFNGLGETUNIFORMSUBROUTINEUIVPROC pfn_glGetUniformSubroutineuiv;
PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC pfn_glClearNamedFramebufferuiv;
PFNGLUNIFORMMATRIX2FVPROC pfn_glUniformMatrix2fv;
PFNGLCOLORP3UIPROC pfn_glColorP3ui;
PFNGLGETUNIFORMDVPROC pfn_glGetUniformdv;
PFNGLGENQUERIESPROC pfn_glGenQueries;
PFNGLCOLORMASKIPROC pfn_glColorMaski;
PFNGLGETQUERYBUFFEROBJECTI64VPROC pfn_glGetQueryBufferObjecti64v;
PFNGLGETUNIFORMIVPROC pfn_glGetUniformiv;
PFNGLCOLORP3UIVPROC pfn_glColorP3uiv;
PFNGLCLEARNAMEDFRAMEBUFFERIVPROC pfn_glClearNamedFramebufferiv;
PFNGLGETUNIFORMFVPROC pfn_glGetUniformfv;
PFNGLVERTEXATTRIB2FVPROC pfn_glVertexAttrib2fv;
PFNGLENDTRANSFORMFEEDBACKPROC pfn_glEndTransformFeedback;
PFNGLCLEARNAMEDFRAMEBUFFERFVPROC pfn_glClearNamedFramebufferfv;
PFNGLHINTPROC pfn_glHint;
PFNGLBEGINQUERYPROC pfn_glBeginQuery;
PFNGLVERTEXATTRIBI1UIPROC pfn_glVertexAttribI1ui;
PFNGLUNIFORMMATRIX2X3DVPROC pfn_glUniformMatrix2x3dv;
PFNGLGETQUERYBUFFEROBJECTIVPROC pfn_glGetQueryBufferObjectiv;
PFNGLUNIFORMMATRIX2X3FVPROC pfn_glUniformMatrix2x3fv;
PFNGLGETQUERYBUFFEROBJECTUI64VPROC pfn_glGetQueryBufferObjectui64v;
PFNGLCLEARSTENCILPROC pfn_glClearStencil;
PFNGLUNIFORM1IVPROC pfn_glUniform1iv;
PFNGLTEXSTORAGE2DMULTISAMPLEPROC pfn_glTexStorage2DMultisample;
PFNGLGETQUERYBUFFEROBJECTUIVPROC pfn_glGetQueryBufferObjectuiv;
PFNGLPATCHPARAMETERFVPROC pfn_glPatchParameterfv;
PFNGLVERTEXATTRIBI1UIVPROC pfn_glVertexAttribI1uiv;
PFNGLUNIFORMMATRIX2X4DVPROC pfn_glUniformMatrix2x4dv;
PFNGLGETQUERYINDEXEDIVPROC pfn_glGetQueryIndexediv;
PFNGLTEXSTORAGE3DPROC pfn_glTexStorage3D;
PFNGLCLEARTEXIMAGEPROC pfn_glClearTexImage;
PFNGLUNIFORMMATRIX2X4FVPROC pfn_glUniformMatrix2x4fv;
PFNGLGETQUERYOBJECTI64VPROC pfn_glGetQueryObjecti64v;
PFNGLGETQUERYOBJECTIVPROC pfn_glGetQueryObjectiv;
PFNGLCOLORP4UIPROC pfn_glColorP4ui;
PFNGLPATCHPARAMETERIPROC pfn_glPatchParameteri;
PFNGLBLENDEQUATIONSEPARATEPROC pfn_glBlendEquationSeparate;
PFNGLUNIFORM1UIPROC pfn_glUniform1ui;
PFNGLVERTEXATTRIBI2IPROC pfn_glVertexAttribI2i;
PFNGLGENRENDERBUFFERSPROC pfn_glGenRenderbuffers;
PFNGLUNIFORMMATRIX3DVPROC pfn_glUniformMatrix3dv;
PFNGLTEXSTORAGE3DMULTISAMPLEPROC pfn_glTexStorage3DMultisample;
PFNGLGETQUERYOBJECTUIVPROC pfn_glGetQueryObjectuiv;
PFNGLCOLORP4UIVPROC pfn_glColorP4uiv;
PFNGLBEGINQUERYINDEXEDPROC pfn_glBeginQueryIndexed;
PFNGLPOPDEBUGGROUPPROC pfn_glPopDebugGroup;
PFNGLUNIFORMMATRIX3FVPROC pfn_glUniformMatrix3fv;
PFNGLVERTEXATTRIB2SPROC pfn_glVertexAttrib2s;
PFNGLBEGINTRANSFORMFEEDBACKPROC pfn_glBeginTransformFeedback;
PFNGLGETUNIFORMUIVPROC pfn_glGetUniformuiv;
PFNGLGETQUERYOBJECTUI64VPROC pfn_glGetQueryObjectui64v;
PFNGLUNIFORMMATRIX3X2DVPROC pfn_glUniformMatrix3x2dv;
PFNGLCLEARTEXSUBIMAGEPROC pfn_glClearTexSubImage;
PFNGLVERTEXATTRIBI2IVPROC pfn_glVertexAttribI2iv;
PFNGLGENSAMPLERSPROC pfn_glGenSamplers;
PFNGLUNIFORMMATRIX3X2FVPROC pfn_glUniformMatrix3x2fv;
PFNGLBLENDEQUATIONSEPARATEIPROC pfn_glBlendEquationSeparatei;
PFNGLUNIFORMMATRIX3X4DVPROC pfn_glUniformMatrix3x4dv;
PFNGLVERTEXATTRIB2SVPROC pfn_glVertexAttrib2sv;
PFNGLVERTEXATTRIBI2UIPROC pfn_glVertexAttribI2ui;
PFNGLVERTEXBINDINGDIVISORPROC pfn_glVertexBindingDivisor;
PFNGLUNIFORMMATRIX3X4FVPROC pfn_glUniformMatrix3x4fv;
PFNGLTEXBUFFERPROC pfn_glTexBuffer;
PFNGLGETQUERYIVPROC pfn_glGetQueryiv;
PFNGLGENTEXTURESPROC pfn_glGenTextures;
PFNGLBLENDEQUATIONIPROC pfn_glBlendEquationi;
PFNGLTEXSUBIMAGE1DPROC pfn_glTexSubImage1D;
PFNGLBINDATTRIBLOCATIONPROC pfn_glBindAttribLocation;
PFNGLUNIFORMMATRIX4DVPROC pfn_glUniformMatrix4dv;
PFNGLVERTEXATTRIBI2UIVPROC pfn_glVertexAttribI2uiv;
PFNGLUNIFORM1UIVPROC pfn_glUniform1uiv;
PFNGLBINDBUFFERPROC pfn_glBindBuffer;
PFNGLUNIFORMMATRIX4FVPROC pfn_glUniformMatrix4fv;
PFNGLCLIENTWAITSYNCPROC pfn_glClientWaitSync;
PFNGLUNIFORM2DVPROC pfn_glUniform2dv;
PFNGLVERTEXATTRIB3DPROC pfn_glVertexAttrib3d;
PFNGLGENTRANSFORMFEEDBACKSPROC pfn_glGenTransformFeedbacks;
PFNGLGETRENDERBUFFERPARAMETERIVPROC pfn_glGetRenderbufferParameteriv;
PFNGLUNIFORMMATRIX4X2DVPROC pfn_glUniformMatrix4x2dv;
PFNGLVERTEXATTRIBI3IPROC pfn_glVertexAttribI3i;
PFNGLCLIPCONTROLPROC pfn_glClipControl;
PFNGLGETVERTEXARRAYINDEXED64IVPROC pfn_glGetVertexArrayIndexed64iv;
PFNGLTEXSUBIMAGE2DPROC pfn_glTexSubImage2D;
PFNGLUNIFORMMATRIX4X2FVPROC pfn_glUniformMatrix4x2fv;
PFNGLUNIFORM2DPROC pfn_glUniform2d;
PFNGLTEXBUFFERRANGEPROC pfn_glTexBufferRange;
PFNGLTEXSUBIMAGE3DPROC pfn_glTexSubImage3D;
PFNGLVERTEXP2UIVPROC pfn_glVertexP2uiv;
PFNGLBLENDFUNCPROC pfn_glBlendFunc;
PFNGLBINDBUFFERBASEPROC pfn_glBindBufferBase;
PFNGLGENVERTEXARRAYSPROC pfn_glGenVertexArrays;
PFNGLVERTEXP2UIPROC pfn_glVertexP2ui;
PFNGLGETSAMPLERPARAMETERIIVPROC pfn_glGetSamplerParameterIiv;
PFNGLUNIFORMMATRIX4X3DVPROC pfn_glUniformMatrix4x3dv;
PFNGLUNIFORM2FPROC pfn_glUniform2f;
PFNGLVERTEXATTRIB3DVPROC pfn_glVertexAttrib3dv;
PFNGLUNIFORMMATRIX4X3FVPROC pfn_glUniformMatrix4x3fv;
PFNGLVERTEXATTRIBI3IVPROC pfn_glVertexAttribI3iv;
PFNGLTEXTUREBARRIERPROC pfn_glTextureBarrier;
PFNGLGETVERTEXARRAYINDEXEDIVPROC pfn_glGetVertexArrayIndexediv;
PFNGLBLENDFUNCSEPARATEPROC pfn_glBlendFuncSeparate;
PFNGLVERTEXATTRIBI3UIPROC pfn_glVertexAttribI3ui;
PFNGLGETSAMPLERPARAMETERIUIVPROC pfn_glGetSamplerParameterIuiv;
PFNGLVERTEXP3UIPROC pfn_glVertexP3ui;
PFNGLUNIFORMSUBROUTINESUIVPROC pfn_glUniformSubroutinesuiv;
PFNGLUNIFORM2FVPROC pfn_glUniform2fv;
PFNGLVERTEXP3UIVPROC pfn_glVertexP3uiv;
PFNGLVERTEXATTRIB3FPROC pfn_glVertexAttrib3f;
PFNGLBINDBUFFERRANGEPROC pfn_glBindBufferRange;
PFNGLVERTEXATTRIBI3UIVPROC pfn_glVertexAttribI3uiv;
PFNGLGENERATEMIPMAPPROC pfn_glGenerateMipmap;
PFNGLGETSAMPLERPARAMETERFVPROC pfn_glGetSamplerParameterfv;
PFNGLPRIMITIVERESTARTINDEXPROC pfn_glPrimitiveRestartIndex;
PFNGLBINDFRAGDATALOCATIONINDEXEDPROC pfn_glBindFragDataLocationIndexed;
PFNGLUNIFORM2IPROC pfn_glUniform2i;
PFNGLGETSAMPLERPARAMETERIVPROC pfn_glGetSamplerParameteriv;
PFNGLVERTEXP4UIPROC pfn_glVertexP4ui;
PFNGLTEXTUREBUFFERPROC pfn_glTextureBuffer;
PFNGLGETVERTEXARRAYIVPROC pfn_glGetVertexArrayiv;
PFNGLGETVERTEXATTRIBIIVPROC pfn_glGetVertexAttribIiv;
PFNGLVERTEXATTRIBI4BVPROC pfn_glVertexAttribI4bv;
PFNGLBINDFRAGDATALOCATIONPROC pfn_glBindFragDataLocation;
PFNGLBLENDFUNCSEPARATEIPROC pfn_glBlendFuncSeparatei;
PFNGLVERTEXP4UIVPROC pfn_glVertexP4uiv;
PFNGLUNMAPBUFFERPROC pfn_glUnmapBuffer;
PFNGLVERTEXATTRIB3FVPROC pfn_glVertexAttrib3fv;
PFNGLBINDBUFFERSRANGEPROC pfn_glBindBuffersRange;
PFNGLTEXTUREBUFFERRANGEPROC pfn_glTextureBufferRange;
PFNGLVERTEXATTRIBI4IPROC pfn_glVertexAttribI4i;
PFNGLTEXCOORDP1UIPROC pfn_glTexCoordP1ui;
PFNGLBINDBUFFERSBASEPROC pfn_glBindBuffersBase;
PFNGLGETVERTEXATTRIBIUIVPROC pfn_glGetVertexAttribIuiv;
PFNGLPROGRAMBINARYPROC pfn_glProgramBinary;
PFNGLGETSHADERSOURCEPROC pfn_glGetShaderSource;
PFNGLTEXCOORDP1UIVPROC pfn_glTexCoordP1uiv;
PFNGLGETSHADERPRECISIONFORMATPROC pfn_glGetShaderPrecisionFormat;
PFNGLCOMPILESHADERPROC pfn_glCompileShader;
PFNGLGETVERTEXATTRIBLDVPROC pfn_glGetVertexAttribLdv;
PFNGLGENERATETEXTUREMIPMAPPROC pfn_glGenerateTextureMipmap;
PFNGLBINDFRAMEBUFFERPROC pfn_glBindFramebuffer;
PFNGLGETSHADERINFOLOGPROC pfn_glGetShaderInfoLog;
PFNGLTEXCOORDP2UIPROC pfn_glTexCoordP2ui;
PFNGLBLENDFUNCIPROC pfn_glBlendFunci;
PFNGLGETSHADERIVPROC pfn_glGetShaderiv;
PFNGLUNIFORM2IVPROC pfn_glUniform2iv;
PFNGLUNMAPNAMEDBUFFERPROC pfn_glUnmapNamedBuffer;
PFNGLVERTEXATTRIB3SPROC pfn_glVertexAttrib3s;
PFNGLVERTEXATTRIBI4SVPROC pfn_glVertexAttribI4sv;
PFNGLPAUSETRANSFORMFEEDBACKPROC pfn_glPauseTransformFeedback;
PFNGLVERTEXATTRIBI4IVPROC pfn_glVertexAttribI4iv;
PFNGLTEXCOORDP2UIVPROC pfn_glTexCoordP2uiv;
PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC pfn_glGetActiveAtomicCounterBufferiv;
PFNGLGETACTIVEATTRIBPROC pfn_glGetActiveAttrib;
PFNGLGETVERTEXATTRIBPOINTERVPROC pfn_glGetVertexAttribPointerv;
PFNGLUNIFORM2UIPROC pfn_glUniform2ui;
PFNGLTEXCOORDP3UIPROC pfn_glTexCoordP3ui;
PFNGLGETACTIVESUBROUTINENAMEPROC pfn_glGetActiveSubroutineName;
PFNGLVERTEXATTRIBI4UBVPROC pfn_glVertexAttribI4ubv;
PFNGLVERTEXATTRIB3SVPROC pfn_glVertexAttrib3sv;
PFNGLBINDIMAGETEXTUREPROC pfn_glBindImageTexture;
PFNGLGETVERTEXATTRIBDVPROC pfn_glGetVertexAttribdv;
PFNGLBLITFRAMEBUFFERPROC pfn_glBlitFramebuffer;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC pfn_glGetActiveUniformBlockName;
PFNGLTEXCOORDP3UIVPROC pfn_glTexCoordP3uiv;
PFNGLBINDIMAGETEXTURESPROC pfn_glBindImageTextures;
PFNGLGETSTRINGPROC pfn_glGetString;
PFNGLGETACTIVEUNIFORMNAMEPROC pfn_glGetActiveUniformName;
PFNGLVERTEXATTRIBI4UIPROC pfn_glVertexAttribI4ui;
PFNGLCOMPRESSEDTEXIMAGE1DPROC pfn_glCompressedTexImage1D;
PFNGLTEXCOORDP4UIPROC pfn_glTexCoordP4ui;
PFNGLGETVERTEXATTRIBFVPROC pfn_glGetVertexAttribfv;
PFNGLGETSTRINGIPROC pfn_glGetStringi;
PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC pfn_glGetActiveSubroutineUniformName;
PFNGLVERTEXATTRIB4NBVPROC pfn_glVertexAttrib4Nbv;
PFNGLCOMPRESSEDTEXIMAGE2DPROC pfn_glCompressedTexImage2D;
PFNGLTEXCOORDP4UIVPROC pfn_glTexCoordP4uiv;
PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC pfn_glGetActiveSubroutineUniformiv;
PFNGLBUFFERDATAPROC pfn_glBufferData;
PFNGLGETACTIVEUNIFORMPROC pfn_glGetActiveUniform;
PFNGLUSEPROGRAMPROC pfn_glUseProgram;
PFNGLBLITNAMEDFRAMEBUFFERPROC pfn_glBlitNamedFramebuffer;
PFNGLGETSUBROUTINEINDEXPROC pfn_glGetSubroutineIndex;
PFNGLPIXELSTOREFPROC pfn_glPixelStoref;
PFNGLGETVERTEXATTRIBIVPROC pfn_glGetVertexAttribiv;
PFNGLUNIFORM3DVPROC pfn_glUniform3dv;
PFNGLVERTEXATTRIB4NIVPROC pfn_glVertexAttrib4Niv;
PFNGLVERTEXATTRIBI4USVPROC pfn_glVertexAttribI4usv;
PFNGLUNIFORM2UIVPROC pfn_glUniform2uiv;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC pfn_glGetActiveUniformBlockiv;
PFNGLVERTEXATTRIBI4UIVPROC pfn_glVertexAttribI4uiv;
PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC pfn_glGetSubroutineUniformLocation;
PFNGLPIXELSTOREIPROC pfn_glPixelStorei;
PFNGLUSEPROGRAMSTAGESPROC pfn_glUseProgramStages;
PFNGLTEXTUREPARAMETERFVPROC pfn_glTextureParameterfv;
PFNGLGETSYNCIVPROC pfn_glGetSynciv;
PFNGLTEXTUREPARAMETERIIVPROC pfn_glTextureParameterIiv;
PFNGLGETACTIVEUNIFORMSIVPROC pfn_glGetActiveUniformsiv;
PFNGLFRAMEBUFFERPARAMETERIPROC pfn_glFramebufferParameteri;
PFNGLVERTEXATTRIB4NSVPROC pfn_glVertexAttrib4Nsv;
PFNGLUNIFORM3DPROC pfn_glUniform3d;
PFNGLVERTEXATTRIBIFORMATPROC pfn_glVertexAttribIFormat;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC pfn_glCompressedTexSubImage1D;
PFNGLTEXTUREPARAMETERIUIVPROC pfn_glTextureParameterIuiv;
PFNGLFRAMEBUFFERRENDERBUFFERPROC pfn_glFramebufferRenderbuffer;
PFNGLGETATTACHEDSHADERSPROC pfn_glGetAttachedShaders;
PFNGLBINDPROGRAMPIPELINEPROC pfn_glBindProgramPipeline;
PFNGLVERTEXATTRIBIPOINTERPROC pfn_glVertexAttribIPointer;
PFNGLTEXTUREPARAMETERFPROC pfn_glTextureParameterf;
PFNGLUNIFORM3FPROC pfn_glUniform3f;
PFNGLVERTEXATTRIB4NUBPROC pfn_glVertexAttrib4Nub;
PFNGLCOMPRESSEDTEXIMAGE3DPROC pfn_glCompressedTexImage3D;
PFNGLGETATTRIBLOCATIONPROC pfn_glGetAttribLocation;
PFNGLUNIFORM3FVPROC pfn_glUniform3fv;
PFNGLBINDRENDERBUFFERPROC pfn_glBindRenderbuffer;
PFNGLBUFFERSTORAGEPROC pfn_glBufferStorage;
PFNGLTEXTUREPARAMETERIPROC pfn_glTextureParameteri;
PFNGLVERTEXATTRIBL1DPROC pfn_glVertexAttribL1d;
PFNGLGETBOOLEANI_VPROC pfn_glGetBooleani_v;
PFNGLVERTEXATTRIBL1DVPROC pfn_glVertexAttribL1dv;
PFNGLTEXTUREPARAMETERIVPROC pfn_glTextureParameteriv;
PFNGLVERTEXATTRIB4NUIVPROC pfn_glVertexAttrib4Nuiv;
PFNGLVERTEXATTRIB4NUBVPROC pfn_glVertexAttrib4Nubv;
PFNGLBINDSAMPLERPROC pfn_glBindSampler;
PFNGLGETBOOLEANVPROC pfn_glGetBooleanv;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC pfn_glCompressedTexSubImage3D;
PFNGLUNIFORM3IPROC pfn_glUniform3i;
PFNGLFRAMEBUFFERTEXTURE1DPROC pfn_glFramebufferTexture1D;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC pfn_glCompressedTexSubImage2D;
PFNGLFRAMEBUFFERTEXTUREPROC pfn_glFramebufferTexture;
PFNGLBINDSAMPLERSPROC pfn_glBindSamplers;
PFNGLGETBUFFERPARAMETERI64VPROC pfn_glGetBufferParameteri64v;
PFNGLGETNCOLORTABLEPROC pfn_glGetnColorTable;
PFNGLBUFFERSUBDATAPROC pfn_glBufferSubData;
PFNGLVERTEXATTRIB4NUSVPROC pfn_glVertexAttrib4Nusv;
PFNGLFENCESYNCPROC pfn_glFenceSync;
PFNGLGETBUFFERPARAMETERIVPROC pfn_glGetBufferParameteriv;
PFNGLTEXTURESTORAGE1DPROC pfn_glTextureStorage1D;
PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC pfn_glCompressedTextureSubImage1D;
PFNGLFRAMEBUFFERTEXTURE2DPROC pfn_glFramebufferTexture2D;
PFNGLVERTEXATTRIB4BVPROC pfn_glVertexAttrib4bv;
PFNGLBINDTEXTUREPROC pfn_glBindTexture;
PFNGLVALIDATEPROGRAMPROC pfn_glValidateProgram;
PFNGLGETBUFFERPOINTERVPROC pfn_glGetBufferPointerv;
PFNGLGETNCONVOLUTIONFILTERPROC pfn_glGetnConvolutionFilter;
PFNGLGETNCOMPRESSEDTEXIMAGEPROC pfn_glGetnCompressedTexImage;
PFNGLACTIVESHADERPROGRAMPROC pfn_glActiveShaderProgram;
PFNGLFINISHPROC pfn_glFinish;
PFNGLGETBUFFERSUBDATAPROC pfn_glGetBufferSubData;
PFNGLINVALIDATEBUFFERSUBDATAPROC pfn_glInvalidateBufferSubData;
PFNGLTEXTURESTORAGE2DPROC pfn_glTextureStorage2D;
PFNGLVERTEXATTRIB4DPROC pfn_glVertexAttrib4d;
PFNGLPROGRAMPARAMETERIPROC pfn_glProgramParameteri;
PFNGLBINDTEXTUREUNITPROC pfn_glBindTextureUnit;
PFNGLUNIFORM3IVPROC pfn_glUniform3iv;
PFNGLVALIDATEPROGRAMPIPELINEPROC pfn_glValidateProgramPipeline;
PFNGLINVALIDATEBUFFERDATAPROC pfn_glInvalidateBufferData;
PFNGLCHECKFRAMEBUFFERSTATUSPROC pfn_glCheckFramebufferStatus;
PFNGLFRAMEBUFFERTEXTURE3DPROC pfn_glFramebufferTexture3D;
PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC pfn_glTextureStorage2DMultisample;
PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC pfn_glCompressedTextureSubImage3D;
PFNGLVERTEXATTRIBL2DPROC pfn_glVertexAttribL2d;
PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC pfn_glCompressedTextureSubImage2D;
PFNGLACTIVETEXTUREPROC pfn_glActiveTexture;
PFNGLGETNHISTOGRAMPROC pfn_glGetnHistogram;
PFNGLMULTITEXCOORDP1UIVPROC pfn_glMultiTexCoordP1uiv;
PFNGLBINDTEXTURESPROC pfn_glBindTextures;
PFNGLGETTEXIMAGEPROC pfn_glGetTexImage;
PFNGLUNIFORM3UIPROC pfn_glUniform3ui;
PFNGLTEXTURESTORAGE3DPROC pfn_glTextureStorage3D;
PFNGLMULTITEXCOORDP2UIVPROC pfn_glMultiTexCoordP2uiv;
PFNGLINVALIDATEFRAMEBUFFERPROC pfn_glInvalidateFramebuffer;
PFNGLBINDTRANSFORMFEEDBACKPROC pfn_glBindTransformFeedback;
PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC pfn_glInvalidateNamedFramebufferData;
PFNGLGETNMAPDVPROC pfn_glGetnMapdv;
PFNGLMULTITEXCOORDP1UIPROC pfn_glMultiTexCoordP1ui;
PFNGLVERTEXATTRIBL2DVPROC pfn_glVertexAttribL2dv;
PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC pfn_glTextureStorage3DMultisample;
PFNGLGETNMAPFVPROC pfn_glGetnMapfv;
PFNGLGETTEXLEVELPARAMETERIVPROC pfn_glGetTexLevelParameteriv;
PFNGLMULTITEXCOORDP2UIPROC pfn_glMultiTexCoordP2ui;
PFNGLPROGRAMUNIFORM1DPROC pfn_glProgramUniform1d;
PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC pfn_glInvalidateNamedFramebufferSubData;
PFNGLISBUFFERPROC pfn_glIsBuffer;
PFNGLVERTEXATTRIB4DVPROC pfn_glVertexAttrib4dv;
PFNGLGETTEXPARAMETERIIVPROC pfn_glGetTexParameterIiv;
PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC pfn_glCheckNamedFramebufferStatus;
PFNGLBINDVERTEXARRAYPROC pfn_glBindVertexArray;
PFNGLGETTEXLEVELPARAMETERFVPROC pfn_glGetTexLevelParameterfv;
PFNGLINVALIDATETEXSUBIMAGEPROC pfn_glInvalidateTexSubImage;
PFNGLGETNMAPIVPROC pfn_glGetnMapiv;
PFNGLVERTEXATTRIB4FPROC pfn_glVertexAttrib4f;
PFNGLMULTITEXCOORDP3UIPROC pfn_glMultiTexCoordP3ui;
PFNGLPROGRAMUNIFORM1DVPROC pfn_glProgramUniform1dv;
PFNGLINVALIDATESUBFRAMEBUFFERPROC pfn_glInvalidateSubFramebuffer;
PFNGLGETTEXPARAMETERIVPROC pfn_glGetTexParameteriv;
PFNGLFRAMEBUFFERTEXTURELAYERPROC pfn_glFramebufferTextureLayer;
PFNGLPOINTPARAMETERFPROC pfn_glPointParameterf;
PFNGLMULTITEXCOORDP3UIVPROC pfn_glMultiTexCoordP3uiv;
PFNGLCLAMPCOLORPROC pfn_glClampColor;
PFNGLINVALIDATETEXIMAGEPROC pfn_glInvalidateTexImage;
PFNGLMULTITEXCOORDP4UIPROC pfn_glMultiTexCoordP4ui;
PFNGLPROGRAMUNIFORM1FPROC pfn_glProgramUniform1f;
PFNGLGETTEXPARAMETERIUIVPROC pfn_glGetTexParameterIuiv;
PFNGLGETNMINMAXPROC pfn_glGetnMinmax;
PFNGLMULTITEXCOORDP4UIVPROC pfn_glMultiTexCoordP4uiv;
PFNGLFLUSHPROC pfn_glFlush;
PFNGLUNIFORM3UIVPROC pfn_glUniform3uiv;
PFNGLPROGRAMUNIFORM1FVPROC pfn_glProgramUniform1fv;
PFNGLTEXTURESUBIMAGE1DPROC pfn_glTextureSubImage1D;
PFNGLTEXTURESUBIMAGE3DPROC pfn_glTextureSubImage3D;
PFNGLFRONTFACEPROC pfn_glFrontFace;
PFNGLCLEARPROC pfn_glClear;
PFNGLPOINTPARAMETERFVPROC pfn_glPointParameterfv;
PFNGLVIEWPORTARRAYVPROC pfn_glViewportArrayv;
PFNGLGETTEXPARAMETERFVPROC pfn_glGetTexParameterfv;
PFNGLBINDVERTEXBUFFERPROC pfn_glBindVertexBuffer;
PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC pfn_glTransformFeedbackBufferBase;
PFNGLPROGRAMUNIFORM1IPROC pfn_glProgramUniform1i;
PFNGLVERTEXATTRIBL3DPROC pfn_glVertexAttribL3d;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC pfn_glFlushMappedBufferRange;
PFNGLUNIFORM4DPROC pfn_glUniform4d;
PFNGLGETNPIXELMAPUIVPROC pfn_glGetnPixelMapuiv;
PFNGLVERTEXATTRIB4FVPROC pfn_glVertexAttrib4fv;
PFNGLBINDVERTEXBUFFERSPROC pfn_glBindVertexBuffers;
PFNGLVIEWPORTPROC pfn_glViewport;
PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC pfn_glFlushMappedNamedBufferRange;
PFNGLTEXTURESUBIMAGE2DPROC pfn_glTextureSubImage2D;
PFNGLGETNPIXELMAPFVPROC pfn_glGetnPixelMapfv;
PFNGLUNIFORM4FPROC pfn_glUniform4f;
PFNGLTEXIMAGE1DPROC pfn_glTexImage1D;
PFNGLVERTEXATTRIBL3DVPROC pfn_glVertexAttribL3dv;
PFNGLCLEARBUFFERDATAPROC pfn_glClearBufferData;
PFNGLTEXTUREVIEWPROC pfn_glTextureView;
PFNGLCOPYBUFFERSUBDATAPROC pfn_glCopyBufferSubData;
PFNGLGETNPIXELMAPUSVPROC pfn_glGetnPixelMapusv;
PFNGLPOINTPARAMETERIPROC pfn_glPointParameteri;
PFNGLVERTEXATTRIB4IVPROC pfn_glVertexAttrib4iv;
PFNGLUNIFORM4DVPROC pfn_glUniform4dv;
PFNGLGETNPOLYGONSTIPPLEPROC pfn_glGetnPolygonStipple;
PFNGLISENABLEDPROC pfn_glIsEnabled;
PFNGLUNIFORM4IPROC pfn_glUniform4i;
PFNGLTEXIMAGE2DMULTISAMPLEPROC pfn_glTexImage2DMultisample;
PFNGLPROGRAMUNIFORM1IVPROC pfn_glProgramUniform1iv;
PFNGLVIEWPORTINDEXEDFPROC pfn_glViewportIndexedf;
PFNGLCLEARBUFFERIVPROC pfn_glClearBufferiv;
PFNGLTEXIMAGE2DPROC pfn_glTexImage2D;
PFNGLGETTEXTUREIMAGEPROC pfn_glGetTextureImage;
PFNGLTEXIMAGE3DPROC pfn_glTexImage3D;
PFNGLGETNTEXIMAGEPROC pfn_glGetnTexImage;
PFNGLPOINTPARAMETERIVPROC pfn_glPointParameteriv;
PFNGLVERTEXATTRIB4SPROC pfn_glVertexAttrib4s;
PFNGLCLEARBUFFERSUBDATAPROC pfn_glClearBufferSubData;
PFNGLCLEARBUFFERFVPROC pfn_glClearBufferfv;
PFNGLGETTEXTURELEVELPARAMETERIVPROC pfn_glGetTextureLevelParameteriv;
PFNGLGETNSEPARABLEFILTERPROC pfn_glGetnSeparableFilter;
PFNGLUNIFORM4FVPROC pfn_glUniform4fv;
PFNGLPROGRAMUNIFORM1UIPROC pfn_glProgramUniform1ui;
PFNGLCLEARBUFFERFIPROC pfn_glClearBufferfi;
PFNGLISENABLEDIPROC pfn_glIsEnabledi;
PFNGLCOPYIMAGESUBDATAPROC pfn_glCopyImageSubData;
PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC pfn_glTransformFeedbackBufferRange;
PFNGLVERTEXATTRIBL4DPROC pfn_glVertexAttribL4d;
PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC pfn_glGetCompressedTextureImage;
PFNGLGETCOMPRESSEDTEXIMAGEPROC pfn_glGetCompressedTexImage;
PFNGLGENBUFFERSPROC pfn_glGenBuffers;
PFNGLCLEARBUFFERUIVPROC pfn_glClearBufferuiv;
PFNGLTEXIMAGE3DMULTISAMPLEPROC pfn_glTexImage3DMultisample;
PFNGLVIEWPORTINDEXEDFVPROC pfn_glViewportIndexedfv;
PFNGLGETTEXTUREPARAMETERIIVPROC pfn_glGetTextureParameterIiv;
PFNGLCLEARCOLORPROC pfn_glClearColor;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC pfn_glTransformFeedbackVaryings;
PFNGLGETTEXTURELEVELPARAMETERFVPROC pfn_glGetTextureLevelParameterfv;
PFNGLPROGRAMUNIFORM1UIVPROC pfn_glProgramUniform1uiv;
PFNGLGETTEXTUREPARAMETERIUIVPROC pfn_glGetTextureParameterIuiv;
PFNGLGETNUNIFORMDVPROC pfn_glGetnUniformdv;
PFNGLVERTEXATTRIB4SVPROC pfn_glVertexAttrib4sv;
PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC pfn_glGetCompressedTextureSubImage;
PFNGLPROGRAMUNIFORM2DPROC pfn_glProgramUniform2d;
PFNGLVERTEXATTRIBL4DVPROC pfn_glVertexAttribL4dv;

void glDrawBuffer(GLenum buf) { pfn_glDrawBuffer(buf); } 
void glLineWidth(GLfloat width) { pfn_glLineWidth(width); } 
void glDrawBuffers(GLsizei n, const GLenum * bufs) { pfn_glDrawBuffers(n, bufs); } 
void glProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble * value) { pfn_glProgramUniform2dv(program, location, count, value); } 
void glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1) { pfn_glProgramUniform2f(program, location, v0, v1); } 
GLuint glGetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog) { return pfn_glGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog); } 
void glDeleteProgram(GLuint program) { pfn_glDeleteProgram(program); } 
GLboolean glIsFramebuffer(GLuint framebuffer) { return pfn_glIsFramebuffer(framebuffer); } 
void glCopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) { pfn_glCopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size); } 
void glQueryCounter(GLuint id, GLenum target) { pfn_glQueryCounter(id, target); } 
void glProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat * value) { pfn_glProgramUniform2fv(program, location, count, value); } 
void glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1) { pfn_glProgramUniform2i(program, location, v0, v1); } 
void glDeleteProgramPipelines(GLsizei n, const GLuint * pipelines) { pfn_glDeleteProgramPipelines(n, pipelines); } 
void glLinkProgram(GLuint program) { pfn_glLinkProgram(program); } 
void glGetDoublei_v(GLenum target, GLuint index, GLdouble * data) { pfn_glGetDoublei_v(target, index, data); } 
void glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) { pfn_glCopyTexImage2D(target, level, internalformat, x, y, width, height, border); } 
void glProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint * value) { pfn_glProgramUniform2iv(program, location, count, value); } 
void glDeleteQueries(GLsizei n, const GLuint * ids) { pfn_glDeleteQueries(n, ids); } 
void glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) { pfn_glCopyTexImage1D(target, level, internalformat, x, y, width, border); } 
void glGetDoublev(GLenum pname, GLdouble * data) { pfn_glGetDoublev(pname, data); } 
void glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1) { pfn_glProgramUniform2ui(program, location, v0, v1); } 
GLenum glGetError() { return pfn_glGetError(); } 
void glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) { pfn_glCopyTexSubImage1D(target, level, xoffset, x, y, width); } 
void glDeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers) { pfn_glDeleteRenderbuffers(n, renderbuffers); } 
void glDrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices) { pfn_glDrawElements(mode, count, type, indices); } 
void glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint * value) { pfn_glProgramUniform2uiv(program, location, count, value); } 
void glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) { pfn_glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height); } 
void glDeleteSamplers(GLsizei count, const GLuint * samplers) { pfn_glDeleteSamplers(count, samplers); } 
void glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLint basevertex) { pfn_glDrawElementsBaseVertex(mode, count, type, indices, basevertex); } 
void glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) { pfn_glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height); } 
void glProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2) { pfn_glProgramUniform3d(program, location, v0, v1, v2); } 
void glNamedBufferData(GLuint buffer, GLsizeiptr size, const void * data, GLenum usage) { pfn_glNamedBufferData(buffer, size, data, usage); } 
void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount) { pfn_glDrawElementsInstanced(mode, count, type, indices, instancecount); } 
void glDeleteShader(GLuint shader) { pfn_glDeleteShader(shader); } 
void glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) { pfn_glProgramUniform3f(program, location, v0, v1, v2); } 
void glCopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) { pfn_glCopyTextureSubImage1D(texture, level, xoffset, x, y, width); } 
void glDrawElementsIndirect(GLenum mode, GLenum type, const void * indirect) { pfn_glDrawElementsIndirect(mode, type, indirect); } 
void glProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble * value) { pfn_glProgramUniform3dv(program, location, count, value); } 
void glDeleteSync(GLsync sync) { pfn_glDeleteSync(sync); } 
void glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2) { pfn_glProgramUniform3i(program, location, v0, v1, v2); } 
void glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void * data) { pfn_glNamedBufferSubData(buffer, offset, size, data); } 
void glCopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) { pfn_glCopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height); } 
void glCopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) { pfn_glCopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height); } 
void glNamedBufferStorage(GLuint buffer, GLsizeiptr size, const void * data, GLbitfield flags) { pfn_glNamedBufferStorage(buffer, size, data, flags); } 
void glGetMultisamplefv(GLenum pname, GLuint index, GLfloat * val) { pfn_glGetMultisamplefv(pname, index, val); } 
void glProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat * value) { pfn_glProgramUniform3fv(program, location, count, value); } 
void glGetFloati_v(GLenum target, GLuint index, GLfloat * data) { pfn_glGetFloati_v(target, index, data); } 
void glDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLuint baseinstance) { pfn_glDrawElementsInstancedBaseInstance(mode, count, type, indices, instancecount, baseinstance); } 
GLboolean glIsProgram(GLuint program) { return pfn_glIsProgram(program); } 
void glGetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64 * params) { pfn_glGetNamedBufferParameteri64v(buffer, pname, params); } 
void glDeleteTextures(GLsizei n, const GLuint * textures) { pfn_glDeleteTextures(n, textures); } 
void glDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex) { pfn_glDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex); } 
void glGetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint * params) { pfn_glGetNamedBufferParameteriv(buffer, pname, params); } 
void glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance) { pfn_glDrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instancecount, basevertex, baseinstance); } 
void glNamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum * bufs) { pfn_glNamedFramebufferDrawBuffers(framebuffer, n, bufs); } 
void glSecondaryColorP3uiv(GLenum type, const GLuint * color) { pfn_glSecondaryColorP3uiv(type, color); } 
void glSecondaryColorP3ui(GLenum type, GLuint color) { pfn_glSecondaryColorP3ui(type, color); } 
void glNamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf) { pfn_glNamedFramebufferDrawBuffer(framebuffer, buf); } 
void glGetNamedBufferPointerv(GLuint buffer, GLenum pname, void ** params) { pfn_glGetNamedBufferPointerv(buffer, pname, params); } 
void glGetFloatv(GLenum pname, GLfloat * data) { pfn_glGetFloatv(pname, data); } 
void glDeleteTransformFeedbacks(GLsizei n, const GLuint * ids) { pfn_glDeleteTransformFeedbacks(n, ids); } 
GLboolean glIsProgramPipeline(GLuint pipeline) { return pfn_glIsProgramPipeline(pipeline); } 
void glNamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param) { pfn_glNamedFramebufferParameteri(framebuffer, pname, param); } 
void glGetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, void * data) { pfn_glGetNamedBufferSubData(buffer, offset, size, data); } 
void glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2) { pfn_glProgramUniform3ui(program, location, v0, v1, v2); } 
void glProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint * value) { pfn_glProgramUniform3iv(program, location, count, value); } 
void glNamedFramebufferReadBuffer(GLuint framebuffer, GLenum src) { pfn_glNamedFramebufferReadBuffer(framebuffer, src); } 
void glDeleteVertexArrays(GLsizei n, const GLuint * arrays) { pfn_glDeleteVertexArrays(n, arrays); } 
void glNamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) { pfn_glNamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer); } 
GLboolean glIsQuery(GLuint id) { return pfn_glIsQuery(id); } 
GLint glGetFragDataIndex(GLuint program, const GLchar * name) { return pfn_glGetFragDataIndex(program, name); } 
void glMemoryBarrier(GLbitfield barriers) { pfn_glMemoryBarrier(barriers); } 
void glCreateBuffers(GLsizei n, GLuint * buffers) { pfn_glCreateBuffers(n, buffers); } 
void glGetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint * param) { pfn_glGetNamedFramebufferParameteriv(framebuffer, pname, param); } 
void glMemoryBarrierByRegion(GLbitfield barriers) { pfn_glMemoryBarrierByRegion(barriers); } 
GLint glGetFragDataLocation(GLuint program, const GLchar * name) { return pfn_glGetFragDataLocation(program, name); } 
void glGetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint * params) { pfn_glGetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params); } 
void glNamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level) { pfn_glNamedFramebufferTexture(framebuffer, attachment, texture, level); } 
void glCreateFramebuffers(GLsizei n, GLuint * framebuffers) { pfn_glCreateFramebuffers(n, framebuffers); } 
void glLogicOp(GLenum opcode) { pfn_glLogicOp(opcode); } 
void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices) { pfn_glDrawRangeElements(mode, start, end, count, type, indices); } 
void glProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3) { pfn_glProgramUniform4d(program, location, v0, v1, v2, v3); } 
GLboolean glIsRenderbuffer(GLuint renderbuffer) { return pfn_glIsRenderbuffer(renderbuffer); } 
void glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint * value) { pfn_glProgramUniform3uiv(program, location, count, value); } 
void glMinSampleShading(GLfloat value) { pfn_glMinSampleShading(value); } 
GLuint glCreateProgram() { return pfn_glCreateProgram(); } 
void glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) { pfn_glProgramUniform4f(program, location, v0, v1, v2, v3); } 
void glDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices, GLint basevertex) { pfn_glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex); } 
void glDepthFunc(GLenum func) { pfn_glDepthFunc(func); } 
void glProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble * value) { pfn_glProgramUniform4dv(program, location, count, value); } 
void glDepthMask(GLboolean flag) { pfn_glDepthMask(flag); } 
void glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params) { pfn_glGetFramebufferAttachmentParameteriv(target, attachment, pname, params); } 
void glGetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint * params) { pfn_glGetNamedRenderbufferParameteriv(renderbuffer, pname, params); } 
void glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3) { pfn_glProgramUniform4i(program, location, v0, v1, v2, v3); } 
void glCreateProgramPipelines(GLsizei n, GLuint * pipelines) { pfn_glCreateProgramPipelines(n, pipelines); } 
void glNamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer) { pfn_glNamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer); } 
void glDepthRange(GLdouble n, GLdouble f) { pfn_glDepthRange(n, f); } 
GLboolean glIsSampler(GLuint sampler) { return pfn_glIsSampler(sampler); } 
void glProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat * value) { pfn_glProgramUniform4fv(program, location, count, value); } 
void glResumeTransformFeedback() { pfn_glResumeTransformFeedback(); } 
void glGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label) { pfn_glGetObjectLabel(identifier, name, bufSize, length, label); } 
void glCreateQueries(GLenum target, GLsizei n, GLuint * ids) { pfn_glCreateQueries(target, n, ids); } 
GLboolean glIsShader(GLuint shader) { return pfn_glIsShader(shader); } 
void glGetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat * params) { pfn_glGetnUniformfv(program, location, bufSize, params); } 
void glCreateRenderbuffers(GLsizei n, GLuint * renderbuffers) { pfn_glCreateRenderbuffers(n, renderbuffers); } 
void glGetFramebufferParameteriv(GLenum target, GLenum pname, GLint * params) { pfn_glGetFramebufferParameteriv(target, pname, params); } 
void glShaderBinary(GLsizei count, const GLuint * shaders, GLenum binaryFormat, const void * binary, GLsizei length) { pfn_glShaderBinary(count, shaders, binaryFormat, binary, length); } 
GLenum glGetGraphicsResetStatus() { return pfn_glGetGraphicsResetStatus(); } 
void glCreateSamplers(GLsizei n, GLuint * samplers) { pfn_glCreateSamplers(n, samplers); } 
void glDepthRangeArrayv(GLuint first, GLsizei count, const GLdouble * v) { pfn_glDepthRangeArrayv(first, count, v); } 
GLboolean glIsSync(GLsync sync) { return pfn_glIsSync(sync); } 
void glDepthRangeIndexed(GLuint index, GLdouble n, GLdouble f) { pfn_glDepthRangeIndexed(index, n, f); } 
GLuint glCreateShader(GLenum type) { return pfn_glCreateShader(type); } 
void glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) { pfn_glProgramUniform4ui(program, location, v0, v1, v2, v3); } 
void glProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint * value) { pfn_glProgramUniform4iv(program, location, count, value); } 
void glGetObjectPtrLabel(const void * ptr, GLsizei bufSize, GLsizei * length, GLchar * label) { pfn_glGetObjectPtrLabel(ptr, bufSize, length, label); } 
void glSampleCoverage(GLfloat value, GLboolean invert) { pfn_glSampleCoverage(value, invert); } 
void glDrawTransformFeedback(GLenum mode, GLuint id) { pfn_glDrawTransformFeedback(mode, id); } 
GLboolean glIsTexture(GLuint texture) { return pfn_glIsTexture(texture); } 
void glShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding) { pfn_glShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding); } 
void glNamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) { pfn_glNamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height); } 
GLuint glCreateShaderProgramv(GLenum type, GLsizei count, const GLchar *const* strings) { return pfn_glCreateShaderProgramv(type, count, strings); } 
void glNamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height) { pfn_glNamedRenderbufferStorage(renderbuffer, internalformat, width, height); } 
void glDepthRangef(GLfloat n, GLfloat f) { pfn_glDepthRangef(n, f); } 
void glDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount) { pfn_glDrawTransformFeedbackInstanced(mode, id, instancecount); } 
void glShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length) { pfn_glShaderSource(shader, count, string, length); } 
void glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint * value) { pfn_glProgramUniform4uiv(program, location, count, value); } 
void glCreateTextures(GLenum target, GLsizei n, GLuint * textures) { pfn_glCreateTextures(target, n, textures); } 
void glMultiDrawArrays(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount) { pfn_glMultiDrawArrays(mode, first, count, drawcount); } 
void glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream) { pfn_glDrawTransformFeedbackStream(mode, id, stream); } 
void glVertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex) { pfn_glVertexArrayAttribBinding(vaobj, attribindex, bindingindex); } 
void glDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount) { pfn_glDrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount); } 
void glCreateVertexArrays(GLsizei n, GLuint * arrays) { pfn_glCreateVertexArrays(n, arrays); } 
GLboolean glIsTransformFeedback(GLuint id) { return pfn_glIsTransformFeedback(id); } 
void glCreateTransformFeedbacks(GLsizei n, GLuint * ids) { pfn_glCreateTransformFeedbacks(n, ids); } 
void glVertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) { pfn_glVertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset); } 
void glProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) { pfn_glProgramUniformMatrix2dv(program, location, count, transpose, value); } 
void glReadBuffer(GLenum src) { pfn_glReadBuffer(src); } 
void * glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) { return pfn_glMapBufferRange(target, offset, length, access); } 
void glMultiDrawArraysIndirect(GLenum mode, const void * indirect, GLsizei drawcount, GLsizei stride) { pfn_glMultiDrawArraysIndirect(mode, indirect, drawcount, stride); } 
void glCullFace(GLenum mode) { pfn_glCullFace(mode); } 
void * glMapBuffer(GLenum target, GLenum access) { return pfn_glMapBuffer(target, access); } 
void glVertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) { pfn_glVertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset); } 
void glDetachShader(GLuint program, GLuint shader) { pfn_glDetachShader(program, shader); } 
void glVertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) { pfn_glVertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset); } 
void glSampleMaski(GLuint maskNumber, GLbitfield mask) { pfn_glSampleMaski(maskNumber, mask); } 
GLboolean glIsVertexArray(GLuint array) { return pfn_glIsVertexArray(array); } 
void glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { pfn_glProgramUniformMatrix2fv(program, location, count, transpose, value); } 
void glVertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor) { pfn_glVertexArrayBindingDivisor(vaobj, bindingindex, divisor); } 
void glMultiDrawArraysIndirectCount(GLenum mode, const void * indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride) { pfn_glMultiDrawArraysIndirectCount(mode, indirect, drawcount, maxdrawcount, stride); } 
void glDisable(GLenum cap) { pfn_glDisable(cap); } 
void glVertexArrayElementBuffer(GLuint vaobj, GLuint buffer) { pfn_glVertexArrayElementBuffer(vaobj, buffer); } 
void glProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) { pfn_glProgramUniformMatrix2x3dv(program, location, count, transpose, value); } 
void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels) { pfn_glReadPixels(x, y, width, height, format, type, pixels); } 
void glMultiDrawElements(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount) { pfn_glMultiDrawElements(mode, count, type, indices, drawcount); } 
void glSamplerParameterIiv(GLuint sampler, GLenum pname, const GLint * param) { pfn_glSamplerParameterIiv(sampler, pname, param); } 
void glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { pfn_glProgramUniformMatrix2x3fv(program, location, count, transpose, value); } 
void glSpecializeShader(GLuint shader, const GLchar * pEntryPoint, GLuint numSpecializationConstants, const GLuint * pConstantIndex, const GLuint * pConstantValue) { pfn_glSpecializeShader(shader, pEntryPoint, numSpecializationConstants, pConstantIndex, pConstantValue); } 
void glGetInteger64i_v(GLenum target, GLuint index, GLint64 * data) { pfn_glGetInteger64i_v(target, index, data); } 
void glDebugMessageCallback(GLDEBUGPROC callback, const void * userParam) { pfn_glDebugMessageCallback(callback, userParam); } 
void glMultiDrawElementsBaseVertex(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount, const GLint * basevertex) { pfn_glMultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex); } 
void glProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) { pfn_glProgramUniformMatrix2x4dv(program, location, count, transpose, value); } 
void glSamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint * param) { pfn_glSamplerParameterIuiv(sampler, pname, param); } 
void glGetInteger64v(GLenum pname, GLint64 * data) { pfn_glGetInteger64v(pname, data); } 
void glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { pfn_glProgramUniformMatrix2x4fv(program, location, count, transpose, value); } 
void glReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void * data) { pfn_glReadnPixels(x, y, width, height, format, type, bufSize, data); } 
void glMultiDrawElementsIndirect(GLenum mode, GLenum type, const void * indirect, GLsizei drawcount, GLsizei stride) { pfn_glMultiDrawElementsIndirect(mode, type, indirect, drawcount, stride); } 
void glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param) { pfn_glSamplerParameterf(sampler, pname, param); } 
void glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint * ids, GLboolean enabled) { pfn_glDebugMessageControl(source, type, severity, count, ids, enabled); } 
void glProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) { pfn_glProgramUniformMatrix3dv(program, location, count, transpose, value); } 
void glSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat * param) { pfn_glSamplerParameterfv(sampler, pname, param); } 
void * glMapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access) { return pfn_glMapNamedBufferRange(buffer, offset, length, access); } 
void glEnable(GLenum cap) { pfn_glEnable(cap); } 
void glSamplerParameteri(GLuint sampler, GLenum pname, GLint param) { pfn_glSamplerParameteri(sampler, pname, param); } 
void glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { pfn_glProgramUniformMatrix3fv(program, location, count, transpose, value); } 
void glDisableVertexArrayAttrib(GLuint vaobj, GLuint index) { pfn_glDisableVertexArrayAttrib(vaobj, index); } 
void glGetIntegeri_v(GLenum target, GLuint index, GLint * data) { pfn_glGetIntegeri_v(target, index, data); } 
void glSamplerParameteriv(GLuint sampler, GLenum pname, const GLint * param) { pfn_glSamplerParameteriv(sampler, pname, param); } 
void glMultiDrawElementsIndirectCount(GLenum mode, GLenum type, const void * indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride) { pfn_glMultiDrawElementsIndirectCount(mode, type, indirect, drawcount, maxdrawcount, stride); } 
void glProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) { pfn_glProgramUniformMatrix3x2dv(program, location, count, transpose, value); } 
void glDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * buf) { pfn_glDebugMessageInsert(source, type, id, severity, length, buf); } 
void glGetIntegerv(GLenum pname, GLint * data) { pfn_glGetIntegerv(pname, data); } 
void * glMapNamedBuffer(GLuint buffer, GLenum access) { return pfn_glMapNamedBuffer(buffer, access); } 
void glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { pfn_glProgramUniformMatrix3x2fv(program, location, count, transpose, value); } 
void glVertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) { pfn_glVertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride); } 
void glProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) { pfn_glProgramUniformMatrix3x4dv(program, location, count, transpose, value); } 
void glDisableVertexAttribArray(GLuint index) { pfn_glDisableVertexAttribArray(index); } 
void glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { pfn_glProgramUniformMatrix3x4fv(program, location, count, transpose, value); } 
void glStencilFunc(GLenum func, GLint ref, GLuint mask) { pfn_glStencilFunc(func, ref, mask); } 
void glProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) { pfn_glProgramUniformMatrix4dv(program, location, count, transpose, value); } 
void glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint * params) { pfn_glGetInternalformativ(target, internalformat, pname, count, params); } 
void glScissor(GLint x, GLint y, GLsizei width, GLsizei height) { pfn_glScissor(x, y, width, height); } 
void glDisablei(GLenum target, GLuint index) { pfn_glDisablei(target, index); } 
void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) { pfn_glStencilFuncSeparate(face, func, ref, mask); } 
void glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { pfn_glProgramUniformMatrix4fv(program, location, count, transpose, value); } 
void glEnableVertexArrayAttrib(GLuint vaobj, GLuint index) { pfn_glEnableVertexArrayAttrib(vaobj, index); } 
void glDeleteBuffers(GLsizei n, const GLuint * buffers) { pfn_glDeleteBuffers(n, buffers); } 
void glGetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint64 * params) { pfn_glGetInternalformati64v(target, internalformat, pname, count, params); } 
void glScissorArrayv(GLuint first, GLsizei count, const GLint * v) { pfn_glScissorArrayv(first, count, v); } 
void glVertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides) { pfn_glVertexArrayVertexBuffers(vaobj, first, count, buffers, offsets, strides); } 
void glStencilMask(GLuint mask) { pfn_glStencilMask(mask); } 
void glProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) { pfn_glProgramUniformMatrix4x2dv(program, location, count, transpose, value); } 
void glStencilMaskSeparate(GLenum face, GLuint mask) { pfn_glStencilMaskSeparate(face, mask); } 
void glVertexAttrib1d(GLuint index, GLdouble x) { pfn_glVertexAttrib1d(index, x); } 
void glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { pfn_glProgramUniformMatrix4x2fv(program, location, count, transpose, value); } 
void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) { pfn_glStencilOp(fail, zfail, zpass); } 
void glVertexAttrib1dv(GLuint index, const GLdouble * v) { pfn_glVertexAttrib1dv(index, v); } 
void glNormalP3ui(GLenum type, GLuint coords) { pfn_glNormalP3ui(type, coords); } 
void glProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) { pfn_glProgramUniformMatrix4x3dv(program, location, count, transpose, value); } 
void glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) { pfn_glStencilOpSeparate(face, sfail, dpfail, dppass); } 
void glEnableVertexAttribArray(GLuint index) { pfn_glEnableVertexAttribArray(index); } 
void glNormalP3uiv(GLenum type, const GLuint * coords) { pfn_glNormalP3uiv(type, coords); } 
void glScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height) { pfn_glScissorIndexed(index, left, bottom, width, height); } 
void glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { pfn_glProgramUniformMatrix4x3fv(program, location, count, transpose, value); } 
void glProvokingVertex(GLenum mode) { pfn_glProvokingVertex(mode); } 
void glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z) { pfn_glDispatchCompute(num_groups_x, num_groups_y, num_groups_z); } 
void glDeleteFramebuffers(GLsizei n, const GLuint * framebuffers) { pfn_glDeleteFramebuffers(n, framebuffers); } 
void glVertexAttrib1f(GLuint index, GLfloat x) { pfn_glVertexAttrib1f(index, x); } 
void glEnablei(GLenum target, GLuint index) { pfn_glEnablei(target, index); } 
void glDrawArrays(GLenum mode, GLint first, GLsizei count) { pfn_glDrawArrays(mode, first, count); } 
void glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, void * binary) { pfn_glGetProgramBinary(program, bufSize, length, binaryFormat, binary); } 
void glReleaseShaderCompiler() { pfn_glReleaseShaderCompiler(); } 
void glDispatchComputeIndirect(GLintptr indirect) { pfn_glDispatchComputeIndirect(indirect); } 
void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog) { pfn_glGetProgramInfoLog(program, bufSize, length, infoLog); } 
void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount) { pfn_glDrawArraysInstanced(mode, first, count, instancecount); } 
void glScissorIndexedv(GLuint index, const GLint * v) { pfn_glScissorIndexedv(index, v); } 
void glVertexAttrib1fv(GLuint index, const GLfloat * v) { pfn_glVertexAttrib1fv(index, v); } 
void glDrawArraysIndirect(GLenum mode, const void * indirect) { pfn_glDrawArraysIndirect(mode, indirect); } 
void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) { pfn_glRenderbufferStorage(target, internalformat, width, height); } 
void glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint * params) { pfn_glGetProgramInterfaceiv(program, programInterface, pname, params); } 
void glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance) { pfn_glDrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance); } 
void glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) { pfn_glRenderbufferStorageMultisample(target, samples, internalformat, width, height); } 
void glPushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar * message) { pfn_glPushDebugGroup(source, id, length, message); } 
void glEndConditionalRender() { pfn_glEndConditionalRender(); } 
void glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) { pfn_glWaitSync(sync, flags, timeout); } 
void glPointSize(GLfloat size) { pfn_glPointSize(size); } 
void glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) { pfn_glUniform4ui(location, v0, v1, v2, v3); } 
void glTexParameterIiv(GLenum target, GLenum pname, const GLint * params) { pfn_glTexParameterIiv(target, pname, params); } 
void glVertexAttrib1s(GLuint index, GLshort x) { pfn_glVertexAttrib1s(index, x); } 
void glGetTextureParameterfv(GLuint texture, GLenum pname, GLfloat * params) { pfn_glGetTextureParameterfv(texture, pname, params); } 
void glClearDepth(GLdouble depth) { pfn_glClearDepth(depth); } 
void glGetTextureParameteriv(GLuint texture, GLenum pname, GLint * params) { pfn_glGetTextureParameteriv(texture, pname, params); } 
void glVertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) { pfn_glVertexAttribLFormat(attribindex, size, type, relativeoffset); } 
void glObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar * label) { pfn_glObjectLabel(identifier, name, length, label); } 
void glUniform4iv(GLint location, GLsizei count, const GLint * value) { pfn_glUniform4iv(location, count, value); } 
void glVertexAttrib4ubv(GLuint index, const GLubyte * v) { pfn_glVertexAttrib4ubv(index, v); } 
void glGenFramebuffers(GLsizei n, GLuint * framebuffers) { pfn_glGenFramebuffers(n, framebuffers); } 
void glVertexAttrib4uiv(GLuint index, const GLuint * v) { pfn_glVertexAttrib4uiv(index, v); } 
void glTexParameterIuiv(GLenum target, GLenum pname, const GLuint * params) { pfn_glTexParameterIuiv(target, pname, params); } 
void glGetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint * params) { pfn_glGetnUniformiv(program, location, bufSize, params); } 
void glVertexAttrib1sv(GLuint index, const GLshort * v) { pfn_glVertexAttrib1sv(index, v); } 
void glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog) { pfn_glGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog); } 
void glVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer) { pfn_glVertexAttribLPointer(index, size, type, stride, pointer); } 
void glObjectPtrLabel(const void * ptr, GLsizei length, const GLchar * label) { pfn_glObjectPtrLabel(ptr, length, label); } 
void glClearDepthf(GLfloat d) { pfn_glClearDepthf(d); } 
void glTexParameterf(GLenum target, GLenum pname, GLfloat param) { pfn_glTexParameterf(target, pname, param); } 
void glUniform1d(GLint location, GLdouble x) { pfn_glUniform1d(location, x); } 
void glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint * params) { pfn_glGetProgramPipelineiv(pipeline, pname, params); } 
void glVertexAttrib4usv(GLuint index, const GLushort * v) { pfn_glVertexAttrib4usv(index, v); } 
void glGetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void * pixels) { pfn_glGetTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels); } 
void glVertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) { pfn_glVertexAttribP2ui(index, type, normalized, value); } 
void glUniform1dv(GLint location, GLsizei count, const GLdouble * value) { pfn_glUniform1dv(location, count, value); } 
void glVertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value) { pfn_glVertexAttribP1uiv(index, type, normalized, value); } 
void glGetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint * params) { pfn_glGetnUniformuiv(program, location, bufSize, params); } 
void glTexParameterfv(GLenum target, GLenum pname, const GLfloat * params) { pfn_glTexParameterfv(target, pname, params); } 
GLuint glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar * name) { return pfn_glGetProgramResourceIndex(program, programInterface, name); } 
void glVertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value) { pfn_glVertexAttribP2uiv(index, type, normalized, value); } 
void glUniform1f(GLint location, GLfloat v0) { pfn_glUniform1f(location, v0); } 
void glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name) { pfn_glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name); } 
void glVertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) { pfn_glVertexAttribP1ui(index, type, normalized, value); } 
GLint glGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar * name) { return pfn_glGetProgramResourceLocation(program, programInterface, name); } 
void glTexParameteri(GLenum target, GLenum pname, GLint param) { pfn_glTexParameteri(target, pname, param); } 
void glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y) { pfn_glVertexAttrib2d(index, x, y); } 
void glVertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) { pfn_glVertexAttribP3ui(index, type, normalized, value); } 
void glAttachShader(GLuint program, GLuint shader) { pfn_glAttachShader(program, shader); } 
GLint glGetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar * name) { return pfn_glGetProgramResourceLocationIndex(program, programInterface, name); } 
void glGetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64 * param) { pfn_glGetTransformFeedbacki64_v(xfb, pname, index, param); } 
void glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding) { pfn_glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding); } 
void glVertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value) { pfn_glVertexAttribP3uiv(index, type, normalized, value); } 
void glPolygonMode(GLenum face, GLenum mode) { pfn_glPolygonMode(face, mode); } 
void glTexParameteriv(GLenum target, GLenum pname, const GLint * params) { pfn_glTexParameteriv(target, pname, params); } 
void glVertexAttribDivisor(GLuint index, GLuint divisor) { pfn_glVertexAttribDivisor(index, divisor); } 
void glVertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) { pfn_glVertexAttribP4ui(index, type, normalized, value); } 
void glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name) { pfn_glGetProgramResourceName(program, programInterface, index, bufSize, length, name); } 
void glGetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint * param) { pfn_glGetTransformFeedbacki_v(xfb, pname, index, param); } 
void glVertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value) { pfn_glVertexAttribP4uiv(index, type, normalized, value); } 
void glEndQuery(GLenum target) { pfn_glEndQuery(target); } 
void glUniform1fv(GLint location, GLsizei count, const GLfloat * value) { pfn_glUniform1fv(location, count, value); } 
void glBeginConditionalRender(GLuint id, GLenum mode) { pfn_glBeginConditionalRender(id, mode); } 
void glGetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint * values) { pfn_glGetProgramStageiv(program, shadertype, pname, values); } 
void glVertexAttribBinding(GLuint attribindex, GLuint bindingindex) { pfn_glVertexAttribBinding(attribindex, bindingindex); } 
void glGetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint * param) { pfn_glGetTransformFeedbackiv(xfb, pname, param); } 
void glUniform4uiv(GLint location, GLsizei count, const GLuint * value) { pfn_glUniform4uiv(location, count, value); } 
void glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei count, GLsizei * length, GLint * params) { pfn_glGetProgramResourceiv(program, programInterface, index, propCount, props, count, length, params); } 
void glVertexAttrib2dv(GLuint index, const GLdouble * v) { pfn_glVertexAttrib2dv(index, v); } 
void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer) { pfn_glVertexAttribPointer(index, size, type, normalized, stride, pointer); } 
void glPolygonOffset(GLfloat factor, GLfloat units) { pfn_glPolygonOffset(factor, units); } 
GLuint glGetUniformBlockIndex(GLuint program, const GLchar * uniformBlockName) { return pfn_glGetUniformBlockIndex(program, uniformBlockName); } 
void glVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) { pfn_glVertexAttribFormat(attribindex, size, type, normalized, relativeoffset); } 
void glClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void * data) { pfn_glClearNamedBufferData(buffer, internalformat, format, type, data); } 
void glUniform1i(GLint location, GLint v0) { pfn_glUniform1i(location, v0); } 
void glGenProgramPipelines(GLsizei n, GLuint * pipelines) { pfn_glGenProgramPipelines(n, pipelines); } 
void glPolygonOffsetClamp(GLfloat factor, GLfloat units, GLfloat clamp) { pfn_glPolygonOffsetClamp(factor, units, clamp); } 
void glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices) { pfn_glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices); } 
void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) { pfn_glColorMask(red, green, blue, alpha); } 
void glGetProgramiv(GLuint program, GLenum pname, GLint * params) { pfn_glGetProgramiv(program, pname, params); } 
void glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) { pfn_glBlendColor(red, green, blue, alpha); } 
GLint glGetUniformLocation(GLuint program, const GLchar * name) { return pfn_glGetUniformLocation(program, name); } 
void glTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width) { pfn_glTexStorage1D(target, levels, internalformat, width); } 
void glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y) { pfn_glVertexAttrib2f(index, x, y); } 
void glClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) { pfn_glClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil); } 
void glEndQueryIndexed(GLenum target, GLuint index) { pfn_glEndQueryIndexed(target, index); } 
void glVertexAttribI1i(GLuint index, GLint x) { pfn_glVertexAttribI1i(index, x); } 
void glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) { pfn_glTexStorage2D(target, levels, internalformat, width, height); } 
void glClearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data) { pfn_glClearNamedBufferSubData(buffer, internalformat, offset, size, format, type, data); } 
void glBlendEquation(GLenum mode) { pfn_glBlendEquation(mode); } 
void glVertexAttribI1iv(GLuint index, const GLint * v) { pfn_glVertexAttribI1iv(index, v); } 
void glUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) { pfn_glUniformMatrix2dv(location, count, transpose, value); } 
void glGetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint * params) { pfn_glGetUniformSubroutineuiv(shadertype, location, params); } 
void glClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint * value) { pfn_glClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value); } 
void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { pfn_glUniformMatrix2fv(location, count, transpose, value); } 
void glColorP3ui(GLenum type, GLuint color) { pfn_glColorP3ui(type, color); } 
void glGetUniformdv(GLuint program, GLint location, GLdouble * params) { pfn_glGetUniformdv(program, location, params); } 
void glGenQueries(GLsizei n, GLuint * ids) { pfn_glGenQueries(n, ids); } 
void glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a) { pfn_glColorMaski(index, r, g, b, a); } 
void glGetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) { pfn_glGetQueryBufferObjecti64v(id, buffer, pname, offset); } 
void glGetUniformiv(GLuint program, GLint location, GLint * params) { pfn_glGetUniformiv(program, location, params); } 
void glColorP3uiv(GLenum type, const GLuint * color) { pfn_glColorP3uiv(type, color); } 
void glClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint * value) { pfn_glClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value); } 
void glGetUniformfv(GLuint program, GLint location, GLfloat * params) { pfn_glGetUniformfv(program, location, params); } 
void glVertexAttrib2fv(GLuint index, const GLfloat * v) { pfn_glVertexAttrib2fv(index, v); } 
void glEndTransformFeedback() { pfn_glEndTransformFeedback(); } 
void glClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat * value) { pfn_glClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value); } 
void glHint(GLenum target, GLenum mode) { pfn_glHint(target, mode); } 
void glBeginQuery(GLenum target, GLuint id) { pfn_glBeginQuery(target, id); } 
void glVertexAttribI1ui(GLuint index, GLuint x) { pfn_glVertexAttribI1ui(index, x); } 
void glUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) { pfn_glUniformMatrix2x3dv(location, count, transpose, value); } 
void glGetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) { pfn_glGetQueryBufferObjectiv(id, buffer, pname, offset); } 
void glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { pfn_glUniformMatrix2x3fv(location, count, transpose, value); } 
void glGetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) { pfn_glGetQueryBufferObjectui64v(id, buffer, pname, offset); } 
void glClearStencil(GLint s) { pfn_glClearStencil(s); } 
void glUniform1iv(GLint location, GLsizei count, const GLint * value) { pfn_glUniform1iv(location, count, value); } 
void glTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) { pfn_glTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations); } 
void glGetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) { pfn_glGetQueryBufferObjectuiv(id, buffer, pname, offset); } 
void glPatchParameterfv(GLenum pname, const GLfloat * values) { pfn_glPatchParameterfv(pname, values); } 
void glVertexAttribI1uiv(GLuint index, const GLuint * v) { pfn_glVertexAttribI1uiv(index, v); } 
void glUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) { pfn_glUniformMatrix2x4dv(location, count, transpose, value); } 
void glGetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint * params) { pfn_glGetQueryIndexediv(target, index, pname, params); } 
void glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) { pfn_glTexStorage3D(target, levels, internalformat, width, height, depth); } 
void glClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void * data) { pfn_glClearTexImage(texture, level, format, type, data); } 
void glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { pfn_glUniformMatrix2x4fv(location, count, transpose, value); } 
void glGetQueryObjecti64v(GLuint id, GLenum pname, GLint64 * params) { pfn_glGetQueryObjecti64v(id, pname, params); } 
void glGetQueryObjectiv(GLuint id, GLenum pname, GLint * params) { pfn_glGetQueryObjectiv(id, pname, params); } 
void glColorP4ui(GLenum type, GLuint color) { pfn_glColorP4ui(type, color); } 
void glPatchParameteri(GLenum pname, GLint value) { pfn_glPatchParameteri(pname, value); } 
void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) { pfn_glBlendEquationSeparate(modeRGB, modeAlpha); } 
void glUniform1ui(GLint location, GLuint v0) { pfn_glUniform1ui(location, v0); } 
void glVertexAttribI2i(GLuint index, GLint x, GLint y) { pfn_glVertexAttribI2i(index, x, y); } 
void glGenRenderbuffers(GLsizei n, GLuint * renderbuffers) { pfn_glGenRenderbuffers(n, renderbuffers); } 
void glUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) { pfn_glUniformMatrix3dv(location, count, transpose, value); } 
void glTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) { pfn_glTexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations); } 
void glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params) { pfn_glGetQueryObjectuiv(id, pname, params); } 
void glColorP4uiv(GLenum type, const GLuint * color) { pfn_glColorP4uiv(type, color); } 
void glBeginQueryIndexed(GLenum target, GLuint index, GLuint id) { pfn_glBeginQueryIndexed(target, index, id); } 
void glPopDebugGroup() { pfn_glPopDebugGroup(); } 
void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { pfn_glUniformMatrix3fv(location, count, transpose, value); } 
void glVertexAttrib2s(GLuint index, GLshort x, GLshort y) { pfn_glVertexAttrib2s(index, x, y); } 
void glBeginTransformFeedback(GLenum primitiveMode) { pfn_glBeginTransformFeedback(primitiveMode); } 
void glGetUniformuiv(GLuint program, GLint location, GLuint * params) { pfn_glGetUniformuiv(program, location, params); } 
void glGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 * params) { pfn_glGetQueryObjectui64v(id, pname, params); } 
void glUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) { pfn_glUniformMatrix3x2dv(location, count, transpose, value); } 
void glClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * data) { pfn_glClearTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data); } 
void glVertexAttribI2iv(GLuint index, const GLint * v) { pfn_glVertexAttribI2iv(index, v); } 
void glGenSamplers(GLsizei count, GLuint * samplers) { pfn_glGenSamplers(count, samplers); } 
void glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { pfn_glUniformMatrix3x2fv(location, count, transpose, value); } 
void glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha) { pfn_glBlendEquationSeparatei(buf, modeRGB, modeAlpha); } 
void glUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) { pfn_glUniformMatrix3x4dv(location, count, transpose, value); } 
void glVertexAttrib2sv(GLuint index, const GLshort * v) { pfn_glVertexAttrib2sv(index, v); } 
void glVertexAttribI2ui(GLuint index, GLuint x, GLuint y) { pfn_glVertexAttribI2ui(index, x, y); } 
void glVertexBindingDivisor(GLuint bindingindex, GLuint divisor) { pfn_glVertexBindingDivisor(bindingindex, divisor); } 
void glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { pfn_glUniformMatrix3x4fv(location, count, transpose, value); } 
void glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer) { pfn_glTexBuffer(target, internalformat, buffer); } 
void glGetQueryiv(GLenum target, GLenum pname, GLint * params) { pfn_glGetQueryiv(target, pname, params); } 
void glGenTextures(GLsizei n, GLuint * textures) { pfn_glGenTextures(n, textures); } 
void glBlendEquationi(GLuint buf, GLenum mode) { pfn_glBlendEquationi(buf, mode); } 
void glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels) { pfn_glTexSubImage1D(target, level, xoffset, width, format, type, pixels); } 
void glBindAttribLocation(GLuint program, GLuint index, const GLchar * name) { pfn_glBindAttribLocation(program, index, name); } 
void glUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) { pfn_glUniformMatrix4dv(location, count, transpose, value); } 
void glVertexAttribI2uiv(GLuint index, const GLuint * v) { pfn_glVertexAttribI2uiv(index, v); } 
void glUniform1uiv(GLint location, GLsizei count, const GLuint * value) { pfn_glUniform1uiv(location, count, value); } 
void glBindBuffer(GLenum target, GLuint buffer) { pfn_glBindBuffer(target, buffer); } 
void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { pfn_glUniformMatrix4fv(location, count, transpose, value); } 
GLenum glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) { return pfn_glClientWaitSync(sync, flags, timeout); } 
void glUniform2dv(GLint location, GLsizei count, const GLdouble * value) { pfn_glUniform2dv(location, count, value); } 
void glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z) { pfn_glVertexAttrib3d(index, x, y, z); } 
void glGenTransformFeedbacks(GLsizei n, GLuint * ids) { pfn_glGenTransformFeedbacks(n, ids); } 
void glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params) { pfn_glGetRenderbufferParameteriv(target, pname, params); } 
void glUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) { pfn_glUniformMatrix4x2dv(location, count, transpose, value); } 
void glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z) { pfn_glVertexAttribI3i(index, x, y, z); } 
void glClipControl(GLenum origin, GLenum depth) { pfn_glClipControl(origin, depth); } 
void glGetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64 * param) { pfn_glGetVertexArrayIndexed64iv(vaobj, index, pname, param); } 
void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels) { pfn_glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels); } 
void glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { pfn_glUniformMatrix4x2fv(location, count, transpose, value); } 
void glUniform2d(GLint location, GLdouble x, GLdouble y) { pfn_glUniform2d(location, x, y); } 
void glTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) { pfn_glTexBufferRange(target, internalformat, buffer, offset, size); } 
void glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels) { pfn_glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels); } 
void glVertexP2uiv(GLenum type, const GLuint * value) { pfn_glVertexP2uiv(type, value); } 
void glBlendFunc(GLenum sfactor, GLenum dfactor) { pfn_glBlendFunc(sfactor, dfactor); } 
void glBindBufferBase(GLenum target, GLuint index, GLuint buffer) { pfn_glBindBufferBase(target, index, buffer); } 
void glGenVertexArrays(GLsizei n, GLuint * arrays) { pfn_glGenVertexArrays(n, arrays); } 
void glVertexP2ui(GLenum type, GLuint value) { pfn_glVertexP2ui(type, value); } 
void glGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint * params) { pfn_glGetSamplerParameterIiv(sampler, pname, params); } 
void glUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) { pfn_glUniformMatrix4x3dv(location, count, transpose, value); } 
void glUniform2f(GLint location, GLfloat v0, GLfloat v1) { pfn_glUniform2f(location, v0, v1); } 
void glVertexAttrib3dv(GLuint index, const GLdouble * v) { pfn_glVertexAttrib3dv(index, v); } 
void glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { pfn_glUniformMatrix4x3fv(location, count, transpose, value); } 
void glVertexAttribI3iv(GLuint index, const GLint * v) { pfn_glVertexAttribI3iv(index, v); } 
void glTextureBarrier() { pfn_glTextureBarrier(); } 
void glGetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint * param) { pfn_glGetVertexArrayIndexediv(vaobj, index, pname, param); } 
void glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) { pfn_glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha); } 
void glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z) { pfn_glVertexAttribI3ui(index, x, y, z); } 
void glGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint * params) { pfn_glGetSamplerParameterIuiv(sampler, pname, params); } 
void glVertexP3ui(GLenum type, GLuint value) { pfn_glVertexP3ui(type, value); } 
void glUniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint * indices) { pfn_glUniformSubroutinesuiv(shadertype, count, indices); } 
void glUniform2fv(GLint location, GLsizei count, const GLfloat * value) { pfn_glUniform2fv(location, count, value); } 
void glVertexP3uiv(GLenum type, const GLuint * value) { pfn_glVertexP3uiv(type, value); } 
void glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z) { pfn_glVertexAttrib3f(index, x, y, z); } 
void glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) { pfn_glBindBufferRange(target, index, buffer, offset, size); } 
void glVertexAttribI3uiv(GLuint index, const GLuint * v) { pfn_glVertexAttribI3uiv(index, v); } 
void glGenerateMipmap(GLenum target) { pfn_glGenerateMipmap(target); } 
void glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat * params) { pfn_glGetSamplerParameterfv(sampler, pname, params); } 
void glPrimitiveRestartIndex(GLuint index) { pfn_glPrimitiveRestartIndex(index); } 
void glBindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name) { pfn_glBindFragDataLocationIndexed(program, colorNumber, index, name); } 
void glUniform2i(GLint location, GLint v0, GLint v1) { pfn_glUniform2i(location, v0, v1); } 
void glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint * params) { pfn_glGetSamplerParameteriv(sampler, pname, params); } 
void glVertexP4ui(GLenum type, GLuint value) { pfn_glVertexP4ui(type, value); } 
void glTextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer) { pfn_glTextureBuffer(texture, internalformat, buffer); } 
void glGetVertexArrayiv(GLuint vaobj, GLenum pname, GLint * param) { pfn_glGetVertexArrayiv(vaobj, pname, param); } 
void glGetVertexAttribIiv(GLuint index, GLenum pname, GLint * params) { pfn_glGetVertexAttribIiv(index, pname, params); } 
void glVertexAttribI4bv(GLuint index, const GLbyte * v) { pfn_glVertexAttribI4bv(index, v); } 
void glBindFragDataLocation(GLuint program, GLuint color, const GLchar * name) { pfn_glBindFragDataLocation(program, color, name); } 
void glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) { pfn_glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha); } 
void glVertexP4uiv(GLenum type, const GLuint * value) { pfn_glVertexP4uiv(type, value); } 
GLboolean glUnmapBuffer(GLenum target) { return pfn_glUnmapBuffer(target); } 
void glVertexAttrib3fv(GLuint index, const GLfloat * v) { pfn_glVertexAttrib3fv(index, v); } 
void glBindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizeiptr * sizes) { pfn_glBindBuffersRange(target, first, count, buffers, offsets, sizes); } 
void glTextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) { pfn_glTextureBufferRange(texture, internalformat, buffer, offset, size); } 
void glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w) { pfn_glVertexAttribI4i(index, x, y, z, w); } 
void glTexCoordP1ui(GLenum type, GLuint coords) { pfn_glTexCoordP1ui(type, coords); } 
void glBindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint * buffers) { pfn_glBindBuffersBase(target, first, count, buffers); } 
void glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params) { pfn_glGetVertexAttribIuiv(index, pname, params); } 
void glProgramBinary(GLuint program, GLenum binaryFormat, const void * binary, GLsizei length) { pfn_glProgramBinary(program, binaryFormat, binary, length); } 
void glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source) { pfn_glGetShaderSource(shader, bufSize, length, source); } 
void glTexCoordP1uiv(GLenum type, const GLuint * coords) { pfn_glTexCoordP1uiv(type, coords); } 
void glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision) { pfn_glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision); } 
void glCompileShader(GLuint shader) { pfn_glCompileShader(shader); } 
void glGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble * params) { pfn_glGetVertexAttribLdv(index, pname, params); } 
void glGenerateTextureMipmap(GLuint texture) { pfn_glGenerateTextureMipmap(texture); } 
void glBindFramebuffer(GLenum target, GLuint framebuffer) { pfn_glBindFramebuffer(target, framebuffer); } 
void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog) { pfn_glGetShaderInfoLog(shader, bufSize, length, infoLog); } 
void glTexCoordP2ui(GLenum type, GLuint coords) { pfn_glTexCoordP2ui(type, coords); } 
void glBlendFunci(GLuint buf, GLenum src, GLenum dst) { pfn_glBlendFunci(buf, src, dst); } 
void glGetShaderiv(GLuint shader, GLenum pname, GLint * params) { pfn_glGetShaderiv(shader, pname, params); } 
void glUniform2iv(GLint location, GLsizei count, const GLint * value) { pfn_glUniform2iv(location, count, value); } 
GLboolean glUnmapNamedBuffer(GLuint buffer) { return pfn_glUnmapNamedBuffer(buffer); } 
void glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z) { pfn_glVertexAttrib3s(index, x, y, z); } 
void glVertexAttribI4sv(GLuint index, const GLshort * v) { pfn_glVertexAttribI4sv(index, v); } 
void glPauseTransformFeedback() { pfn_glPauseTransformFeedback(); } 
void glVertexAttribI4iv(GLuint index, const GLint * v) { pfn_glVertexAttribI4iv(index, v); } 
void glTexCoordP2uiv(GLenum type, const GLuint * coords) { pfn_glTexCoordP2uiv(type, coords); } 
void glGetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint * params) { pfn_glGetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params); } 
void glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name) { pfn_glGetActiveAttrib(program, index, bufSize, length, size, type, name); } 
void glGetVertexAttribPointerv(GLuint index, GLenum pname, void ** pointer) { pfn_glGetVertexAttribPointerv(index, pname, pointer); } 
void glUniform2ui(GLint location, GLuint v0, GLuint v1) { pfn_glUniform2ui(location, v0, v1); } 
void glTexCoordP3ui(GLenum type, GLuint coords) { pfn_glTexCoordP3ui(type, coords); } 
void glGetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name) { pfn_glGetActiveSubroutineName(program, shadertype, index, bufSize, length, name); } 
void glVertexAttribI4ubv(GLuint index, const GLubyte * v) { pfn_glVertexAttribI4ubv(index, v); } 
void glVertexAttrib3sv(GLuint index, const GLshort * v) { pfn_glVertexAttrib3sv(index, v); } 
void glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format) { pfn_glBindImageTexture(unit, texture, level, layered, layer, access, format); } 
void glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params) { pfn_glGetVertexAttribdv(index, pname, params); } 
void glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) { pfn_glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter); } 
void glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName) { pfn_glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName); } 
void glTexCoordP3uiv(GLenum type, const GLuint * coords) { pfn_glTexCoordP3uiv(type, coords); } 
void glBindImageTextures(GLuint first, GLsizei count, const GLuint * textures) { pfn_glBindImageTextures(first, count, textures); } 
const GLubyte * glGetString(GLenum name) { return pfn_glGetString(name); } 
void glGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName) { pfn_glGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName); } 
void glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) { pfn_glVertexAttribI4ui(index, x, y, z, w); } 
void glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data) { pfn_glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data); } 
void glTexCoordP4ui(GLenum type, GLuint coords) { pfn_glTexCoordP4ui(type, coords); } 
void glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params) { pfn_glGetVertexAttribfv(index, pname, params); } 
const GLubyte * glGetStringi(GLenum name, GLuint index) { return pfn_glGetStringi(name, index); } 
void glGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name) { pfn_glGetActiveSubroutineUniformName(program, shadertype, index, bufSize, length, name); } 
void glVertexAttrib4Nbv(GLuint index, const GLbyte * v) { pfn_glVertexAttrib4Nbv(index, v); } 
void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data) { pfn_glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data); } 
void glTexCoordP4uiv(GLenum type, const GLuint * coords) { pfn_glTexCoordP4uiv(type, coords); } 
void glGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values) { pfn_glGetActiveSubroutineUniformiv(program, shadertype, index, pname, values); } 
void glBufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage) { pfn_glBufferData(target, size, data, usage); } 
void glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name) { pfn_glGetActiveUniform(program, index, bufSize, length, size, type, name); } 
void glUseProgram(GLuint program) { pfn_glUseProgram(program); } 
void glBlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) { pfn_glBlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter); } 
GLuint glGetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar * name) { return pfn_glGetSubroutineIndex(program, shadertype, name); } 
void glPixelStoref(GLenum pname, GLfloat param) { pfn_glPixelStoref(pname, param); } 
void glGetVertexAttribiv(GLuint index, GLenum pname, GLint * params) { pfn_glGetVertexAttribiv(index, pname, params); } 
void glUniform3dv(GLint location, GLsizei count, const GLdouble * value) { pfn_glUniform3dv(location, count, value); } 
void glVertexAttrib4Niv(GLuint index, const GLint * v) { pfn_glVertexAttrib4Niv(index, v); } 
void glVertexAttribI4usv(GLuint index, const GLushort * v) { pfn_glVertexAttribI4usv(index, v); } 
void glUniform2uiv(GLint location, GLsizei count, const GLuint * value) { pfn_glUniform2uiv(location, count, value); } 
void glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params) { pfn_glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params); } 
void glVertexAttribI4uiv(GLuint index, const GLuint * v) { pfn_glVertexAttribI4uiv(index, v); } 
GLint glGetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar * name) { return pfn_glGetSubroutineUniformLocation(program, shadertype, name); } 
void glPixelStorei(GLenum pname, GLint param) { pfn_glPixelStorei(pname, param); } 
void glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program) { pfn_glUseProgramStages(pipeline, stages, program); } 
void glTextureParameterfv(GLuint texture, GLenum pname, const GLfloat * param) { pfn_glTextureParameterfv(texture, pname, param); } 
void glGetSynciv(GLsync sync, GLenum pname, GLsizei count, GLsizei * length, GLint * values) { pfn_glGetSynciv(sync, pname, count, length, values); } 
void glTextureParameterIiv(GLuint texture, GLenum pname, const GLint * params) { pfn_glTextureParameterIiv(texture, pname, params); } 
void glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params) { pfn_glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params); } 
void glFramebufferParameteri(GLenum target, GLenum pname, GLint param) { pfn_glFramebufferParameteri(target, pname, param); } 
void glVertexAttrib4Nsv(GLuint index, const GLshort * v) { pfn_glVertexAttrib4Nsv(index, v); } 
void glUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z) { pfn_glUniform3d(location, x, y, z); } 
void glVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) { pfn_glVertexAttribIFormat(attribindex, size, type, relativeoffset); } 
void glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data) { pfn_glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data); } 
void glTextureParameterIuiv(GLuint texture, GLenum pname, const GLuint * params) { pfn_glTextureParameterIuiv(texture, pname, params); } 
void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) { pfn_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer); } 
void glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders) { pfn_glGetAttachedShaders(program, maxCount, count, shaders); } 
void glBindProgramPipeline(GLuint pipeline) { pfn_glBindProgramPipeline(pipeline); } 
void glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer) { pfn_glVertexAttribIPointer(index, size, type, stride, pointer); } 
void glTextureParameterf(GLuint texture, GLenum pname, GLfloat param) { pfn_glTextureParameterf(texture, pname, param); } 
void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) { pfn_glUniform3f(location, v0, v1, v2); } 
void glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) { pfn_glVertexAttrib4Nub(index, x, y, z, w); } 
void glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data) { pfn_glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data); } 
GLint glGetAttribLocation(GLuint program, const GLchar * name) { return pfn_glGetAttribLocation(program, name); } 
void glUniform3fv(GLint location, GLsizei count, const GLfloat * value) { pfn_glUniform3fv(location, count, value); } 
void glBindRenderbuffer(GLenum target, GLuint renderbuffer) { pfn_glBindRenderbuffer(target, renderbuffer); } 
void glBufferStorage(GLenum target, GLsizeiptr size, const void * data, GLbitfield flags) { pfn_glBufferStorage(target, size, data, flags); } 
void glTextureParameteri(GLuint texture, GLenum pname, GLint param) { pfn_glTextureParameteri(texture, pname, param); } 
void glVertexAttribL1d(GLuint index, GLdouble x) { pfn_glVertexAttribL1d(index, x); } 
void glGetBooleani_v(GLenum target, GLuint index, GLboolean * data) { pfn_glGetBooleani_v(target, index, data); } 
void glVertexAttribL1dv(GLuint index, const GLdouble * v) { pfn_glVertexAttribL1dv(index, v); } 
void glTextureParameteriv(GLuint texture, GLenum pname, const GLint * param) { pfn_glTextureParameteriv(texture, pname, param); } 
void glVertexAttrib4Nuiv(GLuint index, const GLuint * v) { pfn_glVertexAttrib4Nuiv(index, v); } 
void glVertexAttrib4Nubv(GLuint index, const GLubyte * v) { pfn_glVertexAttrib4Nubv(index, v); } 
void glBindSampler(GLuint unit, GLuint sampler) { pfn_glBindSampler(unit, sampler); } 
void glGetBooleanv(GLenum pname, GLboolean * data) { pfn_glGetBooleanv(pname, data); } 
void glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data) { pfn_glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data); } 
void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2) { pfn_glUniform3i(location, v0, v1, v2); } 
void glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) { pfn_glFramebufferTexture1D(target, attachment, textarget, texture, level); } 
void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data) { pfn_glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data); } 
void glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level) { pfn_glFramebufferTexture(target, attachment, texture, level); } 
void glBindSamplers(GLuint first, GLsizei count, const GLuint * samplers) { pfn_glBindSamplers(first, count, samplers); } 
void glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64 * params) { pfn_glGetBufferParameteri64v(target, pname, params); } 
void glGetnColorTable(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void * table) { pfn_glGetnColorTable(target, format, type, bufSize, table); } 
void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data) { pfn_glBufferSubData(target, offset, size, data); } 
void glVertexAttrib4Nusv(GLuint index, const GLushort * v) { pfn_glVertexAttrib4Nusv(index, v); } 
GLsync glFenceSync(GLenum condition, GLbitfield flags) { return pfn_glFenceSync(condition, flags); } 
void glGetBufferParameteriv(GLenum target, GLenum pname, GLint * params) { pfn_glGetBufferParameteriv(target, pname, params); } 
void glTextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width) { pfn_glTextureStorage1D(texture, levels, internalformat, width); } 
void glCompressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data) { pfn_glCompressedTextureSubImage1D(texture, level, xoffset, width, format, imageSize, data); } 
void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) { pfn_glFramebufferTexture2D(target, attachment, textarget, texture, level); } 
void glVertexAttrib4bv(GLuint index, const GLbyte * v) { pfn_glVertexAttrib4bv(index, v); } 
void glBindTexture(GLenum target, GLuint texture) { pfn_glBindTexture(target, texture); } 
void glValidateProgram(GLuint program) { pfn_glValidateProgram(program); } 
void glGetBufferPointerv(GLenum target, GLenum pname, void ** params) { pfn_glGetBufferPointerv(target, pname, params); } 
void glGetnConvolutionFilter(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void * image) { pfn_glGetnConvolutionFilter(target, format, type, bufSize, image); } 
void glGetnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, void * pixels) { pfn_glGetnCompressedTexImage(target, lod, bufSize, pixels); } 
void glActiveShaderProgram(GLuint pipeline, GLuint program) { pfn_glActiveShaderProgram(pipeline, program); } 
void glFinish() { pfn_glFinish(); } 
void glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void * data) { pfn_glGetBufferSubData(target, offset, size, data); } 
void glInvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length) { pfn_glInvalidateBufferSubData(buffer, offset, length); } 
void glTextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) { pfn_glTextureStorage2D(texture, levels, internalformat, width, height); } 
void glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { pfn_glVertexAttrib4d(index, x, y, z, w); } 
void glProgramParameteri(GLuint program, GLenum pname, GLint value) { pfn_glProgramParameteri(program, pname, value); } 
void glBindTextureUnit(GLuint unit, GLuint texture) { pfn_glBindTextureUnit(unit, texture); } 
void glUniform3iv(GLint location, GLsizei count, const GLint * value) { pfn_glUniform3iv(location, count, value); } 
void glValidateProgramPipeline(GLuint pipeline) { pfn_glValidateProgramPipeline(pipeline); } 
void glInvalidateBufferData(GLuint buffer) { pfn_glInvalidateBufferData(buffer); } 
GLenum glCheckFramebufferStatus(GLenum target) { return pfn_glCheckFramebufferStatus(target); } 
void glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) { pfn_glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset); } 
void glTextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) { pfn_glTextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations); } 
void glCompressedTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data) { pfn_glCompressedTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data); } 
void glVertexAttribL2d(GLuint index, GLdouble x, GLdouble y) { pfn_glVertexAttribL2d(index, x, y); } 
void glCompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data) { pfn_glCompressedTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, imageSize, data); } 
void glActiveTexture(GLenum texture) { pfn_glActiveTexture(texture); } 
void glGetnHistogram(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void * values) { pfn_glGetnHistogram(target, reset, format, type, bufSize, values); } 
void glMultiTexCoordP1uiv(GLenum texture, GLenum type, const GLuint * coords) { pfn_glMultiTexCoordP1uiv(texture, type, coords); } 
void glBindTextures(GLuint first, GLsizei count, const GLuint * textures) { pfn_glBindTextures(first, count, textures); } 
void glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void * pixels) { pfn_glGetTexImage(target, level, format, type, pixels); } 
void glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2) { pfn_glUniform3ui(location, v0, v1, v2); } 
void glTextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) { pfn_glTextureStorage3D(texture, levels, internalformat, width, height, depth); } 
void glMultiTexCoordP2uiv(GLenum texture, GLenum type, const GLuint * coords) { pfn_glMultiTexCoordP2uiv(texture, type, coords); } 
void glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments) { pfn_glInvalidateFramebuffer(target, numAttachments, attachments); } 
void glBindTransformFeedback(GLenum target, GLuint id) { pfn_glBindTransformFeedback(target, id); } 
void glInvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments) { pfn_glInvalidateNamedFramebufferData(framebuffer, numAttachments, attachments); } 
void glGetnMapdv(GLenum target, GLenum query, GLsizei bufSize, GLdouble * v) { pfn_glGetnMapdv(target, query, bufSize, v); } 
void glMultiTexCoordP1ui(GLenum texture, GLenum type, GLuint coords) { pfn_glMultiTexCoordP1ui(texture, type, coords); } 
void glVertexAttribL2dv(GLuint index, const GLdouble * v) { pfn_glVertexAttribL2dv(index, v); } 
void glTextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) { pfn_glTextureStorage3DMultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations); } 
void glGetnMapfv(GLenum target, GLenum query, GLsizei bufSize, GLfloat * v) { pfn_glGetnMapfv(target, query, bufSize, v); } 
void glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params) { pfn_glGetTexLevelParameteriv(target, level, pname, params); } 
void glMultiTexCoordP2ui(GLenum texture, GLenum type, GLuint coords) { pfn_glMultiTexCoordP2ui(texture, type, coords); } 
void glProgramUniform1d(GLuint program, GLint location, GLdouble v0) { pfn_glProgramUniform1d(program, location, v0); } 
void glInvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height) { pfn_glInvalidateNamedFramebufferSubData(framebuffer, numAttachments, attachments, x, y, width, height); } 
GLboolean glIsBuffer(GLuint buffer) { return pfn_glIsBuffer(buffer); } 
void glVertexAttrib4dv(GLuint index, const GLdouble * v) { pfn_glVertexAttrib4dv(index, v); } 
void glGetTexParameterIiv(GLenum target, GLenum pname, GLint * params) { pfn_glGetTexParameterIiv(target, pname, params); } 
GLenum glCheckNamedFramebufferStatus(GLuint framebuffer, GLenum target) { return pfn_glCheckNamedFramebufferStatus(framebuffer, target); } 
void glBindVertexArray(GLuint array) { pfn_glBindVertexArray(array); } 
void glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params) { pfn_glGetTexLevelParameterfv(target, level, pname, params); } 
void glInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth) { pfn_glInvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth); } 
void glGetnMapiv(GLenum target, GLenum query, GLsizei bufSize, GLint * v) { pfn_glGetnMapiv(target, query, bufSize, v); } 
void glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { pfn_glVertexAttrib4f(index, x, y, z, w); } 
void glMultiTexCoordP3ui(GLenum texture, GLenum type, GLuint coords) { pfn_glMultiTexCoordP3ui(texture, type, coords); } 
void glProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble * value) { pfn_glProgramUniform1dv(program, location, count, value); } 
void glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height) { pfn_glInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height); } 
void glGetTexParameteriv(GLenum target, GLenum pname, GLint * params) { pfn_glGetTexParameteriv(target, pname, params); } 
void glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) { pfn_glFramebufferTextureLayer(target, attachment, texture, level, layer); } 
void glPointParameterf(GLenum pname, GLfloat param) { pfn_glPointParameterf(pname, param); } 
void glMultiTexCoordP3uiv(GLenum texture, GLenum type, const GLuint * coords) { pfn_glMultiTexCoordP3uiv(texture, type, coords); } 
void glClampColor(GLenum target, GLenum clamp) { pfn_glClampColor(target, clamp); } 
void glInvalidateTexImage(GLuint texture, GLint level) { pfn_glInvalidateTexImage(texture, level); } 
void glMultiTexCoordP4ui(GLenum texture, GLenum type, GLuint coords) { pfn_glMultiTexCoordP4ui(texture, type, coords); } 
void glProgramUniform1f(GLuint program, GLint location, GLfloat v0) { pfn_glProgramUniform1f(program, location, v0); } 
void glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params) { pfn_glGetTexParameterIuiv(target, pname, params); } 
void glGetnMinmax(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void * values) { pfn_glGetnMinmax(target, reset, format, type, bufSize, values); } 
void glMultiTexCoordP4uiv(GLenum texture, GLenum type, const GLuint * coords) { pfn_glMultiTexCoordP4uiv(texture, type, coords); } 
void glFlush() { pfn_glFlush(); } 
void glUniform3uiv(GLint location, GLsizei count, const GLuint * value) { pfn_glUniform3uiv(location, count, value); } 
void glProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat * value) { pfn_glProgramUniform1fv(program, location, count, value); } 
void glTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels) { pfn_glTextureSubImage1D(texture, level, xoffset, width, format, type, pixels); } 
void glTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels) { pfn_glTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels); } 
void glFrontFace(GLenum mode) { pfn_glFrontFace(mode); } 
void glClear(GLbitfield mask) { pfn_glClear(mask); } 
void glPointParameterfv(GLenum pname, const GLfloat * params) { pfn_glPointParameterfv(pname, params); } 
void glViewportArrayv(GLuint first, GLsizei count, const GLfloat * v) { pfn_glViewportArrayv(first, count, v); } 
void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat * params) { pfn_glGetTexParameterfv(target, pname, params); } 
void glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) { pfn_glBindVertexBuffer(bindingindex, buffer, offset, stride); } 
void glTransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer) { pfn_glTransformFeedbackBufferBase(xfb, index, buffer); } 
void glProgramUniform1i(GLuint program, GLint location, GLint v0) { pfn_glProgramUniform1i(program, location, v0); } 
void glVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z) { pfn_glVertexAttribL3d(index, x, y, z); } 
void glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length) { pfn_glFlushMappedBufferRange(target, offset, length); } 
void glUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { pfn_glUniform4d(location, x, y, z, w); } 
void glGetnPixelMapuiv(GLenum map, GLsizei bufSize, GLuint * values) { pfn_glGetnPixelMapuiv(map, bufSize, values); } 
void glVertexAttrib4fv(GLuint index, const GLfloat * v) { pfn_glVertexAttrib4fv(index, v); } 
void glBindVertexBuffers(GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides) { pfn_glBindVertexBuffers(first, count, buffers, offsets, strides); } 
void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) { pfn_glViewport(x, y, width, height); } 
void glFlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length) { pfn_glFlushMappedNamedBufferRange(buffer, offset, length); } 
void glTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels) { pfn_glTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels); } 
void glGetnPixelMapfv(GLenum map, GLsizei bufSize, GLfloat * values) { pfn_glGetnPixelMapfv(map, bufSize, values); } 
void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) { pfn_glUniform4f(location, v0, v1, v2, v3); } 
void glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels) { pfn_glTexImage1D(target, level, internalformat, width, border, format, type, pixels); } 
void glVertexAttribL3dv(GLuint index, const GLdouble * v) { pfn_glVertexAttribL3dv(index, v); } 
void glClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void * data) { pfn_glClearBufferData(target, internalformat, format, type, data); } 
void glTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers) { pfn_glTextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers); } 
void glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) { pfn_glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size); } 
void glGetnPixelMapusv(GLenum map, GLsizei bufSize, GLushort * values) { pfn_glGetnPixelMapusv(map, bufSize, values); } 
void glPointParameteri(GLenum pname, GLint param) { pfn_glPointParameteri(pname, param); } 
void glVertexAttrib4iv(GLuint index, const GLint * v) { pfn_glVertexAttrib4iv(index, v); } 
void glUniform4dv(GLint location, GLsizei count, const GLdouble * value) { pfn_glUniform4dv(location, count, value); } 
void glGetnPolygonStipple(GLsizei bufSize, GLubyte * pattern) { pfn_glGetnPolygonStipple(bufSize, pattern); } 
GLboolean glIsEnabled(GLenum cap) { return pfn_glIsEnabled(cap); } 
void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) { pfn_glUniform4i(location, v0, v1, v2, v3); } 
void glTexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) { pfn_glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations); } 
void glProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint * value) { pfn_glProgramUniform1iv(program, location, count, value); } 
void glViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h) { pfn_glViewportIndexedf(index, x, y, w, h); } 
void glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint * value) { pfn_glClearBufferiv(buffer, drawbuffer, value); } 
void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels) { pfn_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels); } 
void glGetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels) { pfn_glGetTextureImage(texture, level, format, type, bufSize, pixels); } 
void glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels) { pfn_glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels); } 
void glGetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels) { pfn_glGetnTexImage(target, level, format, type, bufSize, pixels); } 
void glPointParameteriv(GLenum pname, const GLint * params) { pfn_glPointParameteriv(pname, params); } 
void glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) { pfn_glVertexAttrib4s(index, x, y, z, w); } 
void glClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data) { pfn_glClearBufferSubData(target, internalformat, offset, size, format, type, data); } 
void glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat * value) { pfn_glClearBufferfv(buffer, drawbuffer, value); } 
void glGetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint * params) { pfn_glGetTextureLevelParameteriv(texture, level, pname, params); } 
void glGetnSeparableFilter(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void * row, GLsizei columnBufSize, void * column, void * span) { pfn_glGetnSeparableFilter(target, format, type, rowBufSize, row, columnBufSize, column, span); } 
void glUniform4fv(GLint location, GLsizei count, const GLfloat * value) { pfn_glUniform4fv(location, count, value); } 
void glProgramUniform1ui(GLuint program, GLint location, GLuint v0) { pfn_glProgramUniform1ui(program, location, v0); } 
void glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) { pfn_glClearBufferfi(buffer, drawbuffer, depth, stencil); } 
GLboolean glIsEnabledi(GLenum target, GLuint index) { return pfn_glIsEnabledi(target, index); } 
void glCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth) { pfn_glCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth); } 
void glTransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) { pfn_glTransformFeedbackBufferRange(xfb, index, buffer, offset, size); } 
void glVertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { pfn_glVertexAttribL4d(index, x, y, z, w); } 
void glGetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void * pixels) { pfn_glGetCompressedTextureImage(texture, level, bufSize, pixels); } 
void glGetCompressedTexImage(GLenum target, GLint level, void * img) { pfn_glGetCompressedTexImage(target, level, img); } 
void glGenBuffers(GLsizei n, GLuint * buffers) { pfn_glGenBuffers(n, buffers); } 
void glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint * value) { pfn_glClearBufferuiv(buffer, drawbuffer, value); } 
void glTexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) { pfn_glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations); } 
void glViewportIndexedfv(GLuint index, const GLfloat * v) { pfn_glViewportIndexedfv(index, v); } 
void glGetTextureParameterIiv(GLuint texture, GLenum pname, GLint * params) { pfn_glGetTextureParameterIiv(texture, pname, params); } 
void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) { pfn_glClearColor(red, green, blue, alpha); } 
void glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode) { pfn_glTransformFeedbackVaryings(program, count, varyings, bufferMode); } 
void glGetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat * params) { pfn_glGetTextureLevelParameterfv(texture, level, pname, params); } 
void glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint * value) { pfn_glProgramUniform1uiv(program, location, count, value); } 
void glGetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint * params) { pfn_glGetTextureParameterIuiv(texture, pname, params); } 
void glGetnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble * params) { pfn_glGetnUniformdv(program, location, bufSize, params); } 
void glVertexAttrib4sv(GLuint index, const GLshort * v) { pfn_glVertexAttrib4sv(index, v); } 
void glGetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void * pixels) { pfn_glGetCompressedTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels); } 
void glProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1) { pfn_glProgramUniform2d(program, location, v0, v1); } 
void glVertexAttribL4dv(GLuint index, const GLdouble * v) { pfn_glVertexAttribL4dv(index, v); } 

void gl_load_functions()
{
	pfn_glDrawBuffer = reinterpret_cast<PFNGLDRAWBUFFERPROC>(SDL_GL_GetProcAddress("glDrawBuffer"));
	pfn_glLineWidth = reinterpret_cast<PFNGLLINEWIDTHPROC>(SDL_GL_GetProcAddress("glLineWidth"));
	pfn_glDrawBuffers = reinterpret_cast<PFNGLDRAWBUFFERSPROC>(SDL_GL_GetProcAddress("glDrawBuffers"));
	pfn_glProgramUniform2dv = reinterpret_cast<PFNGLPROGRAMUNIFORM2DVPROC>(SDL_GL_GetProcAddress("glProgramUniform2dv"));
	pfn_glProgramUniform2f = reinterpret_cast<PFNGLPROGRAMUNIFORM2FPROC>(SDL_GL_GetProcAddress("glProgramUniform2f"));
	pfn_glGetDebugMessageLog = reinterpret_cast<PFNGLGETDEBUGMESSAGELOGPROC>(SDL_GL_GetProcAddress("glGetDebugMessageLog"));
	pfn_glDeleteProgram = reinterpret_cast<PFNGLDELETEPROGRAMPROC>(SDL_GL_GetProcAddress("glDeleteProgram"));
	pfn_glIsFramebuffer = reinterpret_cast<PFNGLISFRAMEBUFFERPROC>(SDL_GL_GetProcAddress("glIsFramebuffer"));
	pfn_glCopyNamedBufferSubData = reinterpret_cast<PFNGLCOPYNAMEDBUFFERSUBDATAPROC>(SDL_GL_GetProcAddress("glCopyNamedBufferSubData"));
	pfn_glQueryCounter = reinterpret_cast<PFNGLQUERYCOUNTERPROC>(SDL_GL_GetProcAddress("glQueryCounter"));
	pfn_glProgramUniform2fv = reinterpret_cast<PFNGLPROGRAMUNIFORM2FVPROC>(SDL_GL_GetProcAddress("glProgramUniform2fv"));
	pfn_glProgramUniform2i = reinterpret_cast<PFNGLPROGRAMUNIFORM2IPROC>(SDL_GL_GetProcAddress("glProgramUniform2i"));
	pfn_glDeleteProgramPipelines = reinterpret_cast<PFNGLDELETEPROGRAMPIPELINESPROC>(SDL_GL_GetProcAddress("glDeleteProgramPipelines"));
	pfn_glLinkProgram = reinterpret_cast<PFNGLLINKPROGRAMPROC>(SDL_GL_GetProcAddress("glLinkProgram"));
	pfn_glGetDoublei_v = reinterpret_cast<PFNGLGETDOUBLEI_VPROC>(SDL_GL_GetProcAddress("glGetDoublei_v"));
	pfn_glCopyTexImage2D = reinterpret_cast<PFNGLCOPYTEXIMAGE2DPROC>(SDL_GL_GetProcAddress("glCopyTexImage2D"));
	pfn_glProgramUniform2iv = reinterpret_cast<PFNGLPROGRAMUNIFORM2IVPROC>(SDL_GL_GetProcAddress("glProgramUniform2iv"));
	pfn_glDeleteQueries = reinterpret_cast<PFNGLDELETEQUERIESPROC>(SDL_GL_GetProcAddress("glDeleteQueries"));
	pfn_glCopyTexImage1D = reinterpret_cast<PFNGLCOPYTEXIMAGE1DPROC>(SDL_GL_GetProcAddress("glCopyTexImage1D"));
	pfn_glGetDoublev = reinterpret_cast<PFNGLGETDOUBLEVPROC>(SDL_GL_GetProcAddress("glGetDoublev"));
	pfn_glProgramUniform2ui = reinterpret_cast<PFNGLPROGRAMUNIFORM2UIPROC>(SDL_GL_GetProcAddress("glProgramUniform2ui"));
	pfn_glGetError = reinterpret_cast<PFNGLGETERRORPROC>(SDL_GL_GetProcAddress("glGetError"));
	pfn_glCopyTexSubImage1D = reinterpret_cast<PFNGLCOPYTEXSUBIMAGE1DPROC>(SDL_GL_GetProcAddress("glCopyTexSubImage1D"));
	pfn_glDeleteRenderbuffers = reinterpret_cast<PFNGLDELETERENDERBUFFERSPROC>(SDL_GL_GetProcAddress("glDeleteRenderbuffers"));
	pfn_glDrawElements = reinterpret_cast<PFNGLDRAWELEMENTSPROC>(SDL_GL_GetProcAddress("glDrawElements"));
	pfn_glProgramUniform2uiv = reinterpret_cast<PFNGLPROGRAMUNIFORM2UIVPROC>(SDL_GL_GetProcAddress("glProgramUniform2uiv"));
	pfn_glCopyTexSubImage2D = reinterpret_cast<PFNGLCOPYTEXSUBIMAGE2DPROC>(SDL_GL_GetProcAddress("glCopyTexSubImage2D"));
	pfn_glDeleteSamplers = reinterpret_cast<PFNGLDELETESAMPLERSPROC>(SDL_GL_GetProcAddress("glDeleteSamplers"));
	pfn_glDrawElementsBaseVertex = reinterpret_cast<PFNGLDRAWELEMENTSBASEVERTEXPROC>(SDL_GL_GetProcAddress("glDrawElementsBaseVertex"));
	pfn_glCopyTexSubImage3D = reinterpret_cast<PFNGLCOPYTEXSUBIMAGE3DPROC>(SDL_GL_GetProcAddress("glCopyTexSubImage3D"));
	pfn_glProgramUniform3d = reinterpret_cast<PFNGLPROGRAMUNIFORM3DPROC>(SDL_GL_GetProcAddress("glProgramUniform3d"));
	pfn_glNamedBufferData = reinterpret_cast<PFNGLNAMEDBUFFERDATAPROC>(SDL_GL_GetProcAddress("glNamedBufferData"));
	pfn_glDrawElementsInstanced = reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDPROC>(SDL_GL_GetProcAddress("glDrawElementsInstanced"));
	pfn_glDeleteShader = reinterpret_cast<PFNGLDELETESHADERPROC>(SDL_GL_GetProcAddress("glDeleteShader"));
	pfn_glProgramUniform3f = reinterpret_cast<PFNGLPROGRAMUNIFORM3FPROC>(SDL_GL_GetProcAddress("glProgramUniform3f"));
	pfn_glCopyTextureSubImage1D = reinterpret_cast<PFNGLCOPYTEXTURESUBIMAGE1DPROC>(SDL_GL_GetProcAddress("glCopyTextureSubImage1D"));
	pfn_glDrawElementsIndirect = reinterpret_cast<PFNGLDRAWELEMENTSINDIRECTPROC>(SDL_GL_GetProcAddress("glDrawElementsIndirect"));
	pfn_glProgramUniform3dv = reinterpret_cast<PFNGLPROGRAMUNIFORM3DVPROC>(SDL_GL_GetProcAddress("glProgramUniform3dv"));
	pfn_glDeleteSync = reinterpret_cast<PFNGLDELETESYNCPROC>(SDL_GL_GetProcAddress("glDeleteSync"));
	pfn_glProgramUniform3i = reinterpret_cast<PFNGLPROGRAMUNIFORM3IPROC>(SDL_GL_GetProcAddress("glProgramUniform3i"));
	pfn_glNamedBufferSubData = reinterpret_cast<PFNGLNAMEDBUFFERSUBDATAPROC>(SDL_GL_GetProcAddress("glNamedBufferSubData"));
	pfn_glCopyTextureSubImage3D = reinterpret_cast<PFNGLCOPYTEXTURESUBIMAGE3DPROC>(SDL_GL_GetProcAddress("glCopyTextureSubImage3D"));
	pfn_glCopyTextureSubImage2D = reinterpret_cast<PFNGLCOPYTEXTURESUBIMAGE2DPROC>(SDL_GL_GetProcAddress("glCopyTextureSubImage2D"));
	pfn_glNamedBufferStorage = reinterpret_cast<PFNGLNAMEDBUFFERSTORAGEPROC>(SDL_GL_GetProcAddress("glNamedBufferStorage"));
	pfn_glGetMultisamplefv = reinterpret_cast<PFNGLGETMULTISAMPLEFVPROC>(SDL_GL_GetProcAddress("glGetMultisamplefv"));
	pfn_glProgramUniform3fv = reinterpret_cast<PFNGLPROGRAMUNIFORM3FVPROC>(SDL_GL_GetProcAddress("glProgramUniform3fv"));
	pfn_glGetFloati_v = reinterpret_cast<PFNGLGETFLOATI_VPROC>(SDL_GL_GetProcAddress("glGetFloati_v"));
	pfn_glDrawElementsInstancedBaseInstance = reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC>(SDL_GL_GetProcAddress("glDrawElementsInstancedBaseInstance"));
	pfn_glIsProgram = reinterpret_cast<PFNGLISPROGRAMPROC>(SDL_GL_GetProcAddress("glIsProgram"));
	pfn_glGetNamedBufferParameteri64v = reinterpret_cast<PFNGLGETNAMEDBUFFERPARAMETERI64VPROC>(SDL_GL_GetProcAddress("glGetNamedBufferParameteri64v"));
	pfn_glDeleteTextures = reinterpret_cast<PFNGLDELETETEXTURESPROC>(SDL_GL_GetProcAddress("glDeleteTextures"));
	pfn_glDrawElementsInstancedBaseVertex = reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC>(SDL_GL_GetProcAddress("glDrawElementsInstancedBaseVertex"));
	pfn_glGetNamedBufferParameteriv = reinterpret_cast<PFNGLGETNAMEDBUFFERPARAMETERIVPROC>(SDL_GL_GetProcAddress("glGetNamedBufferParameteriv"));
	pfn_glDrawElementsInstancedBaseVertexBaseInstance = reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC>(SDL_GL_GetProcAddress("glDrawElementsInstancedBaseVertexBaseInstance"));
	pfn_glNamedFramebufferDrawBuffers = reinterpret_cast<PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC>(SDL_GL_GetProcAddress("glNamedFramebufferDrawBuffers"));
	pfn_glSecondaryColorP3uiv = reinterpret_cast<PFNGLSECONDARYCOLORP3UIVPROC>(SDL_GL_GetProcAddress("glSecondaryColorP3uiv"));
	pfn_glSecondaryColorP3ui = reinterpret_cast<PFNGLSECONDARYCOLORP3UIPROC>(SDL_GL_GetProcAddress("glSecondaryColorP3ui"));
	pfn_glNamedFramebufferDrawBuffer = reinterpret_cast<PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC>(SDL_GL_GetProcAddress("glNamedFramebufferDrawBuffer"));
	pfn_glGetNamedBufferPointerv = reinterpret_cast<PFNGLGETNAMEDBUFFERPOINTERVPROC>(SDL_GL_GetProcAddress("glGetNamedBufferPointerv"));
	pfn_glGetFloatv = reinterpret_cast<PFNGLGETFLOATVPROC>(SDL_GL_GetProcAddress("glGetFloatv"));
	pfn_glDeleteTransformFeedbacks = reinterpret_cast<PFNGLDELETETRANSFORMFEEDBACKSPROC>(SDL_GL_GetProcAddress("glDeleteTransformFeedbacks"));
	pfn_glIsProgramPipeline = reinterpret_cast<PFNGLISPROGRAMPIPELINEPROC>(SDL_GL_GetProcAddress("glIsProgramPipeline"));
	pfn_glNamedFramebufferParameteri = reinterpret_cast<PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC>(SDL_GL_GetProcAddress("glNamedFramebufferParameteri"));
	pfn_glGetNamedBufferSubData = reinterpret_cast<PFNGLGETNAMEDBUFFERSUBDATAPROC>(SDL_GL_GetProcAddress("glGetNamedBufferSubData"));
	pfn_glProgramUniform3ui = reinterpret_cast<PFNGLPROGRAMUNIFORM3UIPROC>(SDL_GL_GetProcAddress("glProgramUniform3ui"));
	pfn_glProgramUniform3iv = reinterpret_cast<PFNGLPROGRAMUNIFORM3IVPROC>(SDL_GL_GetProcAddress("glProgramUniform3iv"));
	pfn_glNamedFramebufferReadBuffer = reinterpret_cast<PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC>(SDL_GL_GetProcAddress("glNamedFramebufferReadBuffer"));
	pfn_glDeleteVertexArrays = reinterpret_cast<PFNGLDELETEVERTEXARRAYSPROC>(SDL_GL_GetProcAddress("glDeleteVertexArrays"));
	pfn_glNamedFramebufferRenderbuffer = reinterpret_cast<PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC>(SDL_GL_GetProcAddress("glNamedFramebufferRenderbuffer"));
	pfn_glIsQuery = reinterpret_cast<PFNGLISQUERYPROC>(SDL_GL_GetProcAddress("glIsQuery"));
	pfn_glGetFragDataIndex = reinterpret_cast<PFNGLGETFRAGDATAINDEXPROC>(SDL_GL_GetProcAddress("glGetFragDataIndex"));
	pfn_glMemoryBarrier = reinterpret_cast<PFNGLMEMORYBARRIERPROC>(SDL_GL_GetProcAddress("glMemoryBarrier"));
	pfn_glCreateBuffers = reinterpret_cast<PFNGLCREATEBUFFERSPROC>(SDL_GL_GetProcAddress("glCreateBuffers"));
	pfn_glGetNamedFramebufferParameteriv = reinterpret_cast<PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC>(SDL_GL_GetProcAddress("glGetNamedFramebufferParameteriv"));
	pfn_glMemoryBarrierByRegion = reinterpret_cast<PFNGLMEMORYBARRIERBYREGIONPROC>(SDL_GL_GetProcAddress("glMemoryBarrierByRegion"));
	pfn_glGetFragDataLocation = reinterpret_cast<PFNGLGETFRAGDATALOCATIONPROC>(SDL_GL_GetProcAddress("glGetFragDataLocation"));
	pfn_glGetNamedFramebufferAttachmentParameteriv = reinterpret_cast<PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC>(SDL_GL_GetProcAddress("glGetNamedFramebufferAttachmentParameteriv"));
	pfn_glNamedFramebufferTexture = reinterpret_cast<PFNGLNAMEDFRAMEBUFFERTEXTUREPROC>(SDL_GL_GetProcAddress("glNamedFramebufferTexture"));
	pfn_glCreateFramebuffers = reinterpret_cast<PFNGLCREATEFRAMEBUFFERSPROC>(SDL_GL_GetProcAddress("glCreateFramebuffers"));
	pfn_glLogicOp = reinterpret_cast<PFNGLLOGICOPPROC>(SDL_GL_GetProcAddress("glLogicOp"));
	pfn_glDrawRangeElements = reinterpret_cast<PFNGLDRAWRANGEELEMENTSPROC>(SDL_GL_GetProcAddress("glDrawRangeElements"));
	pfn_glProgramUniform4d = reinterpret_cast<PFNGLPROGRAMUNIFORM4DPROC>(SDL_GL_GetProcAddress("glProgramUniform4d"));
	pfn_glIsRenderbuffer = reinterpret_cast<PFNGLISRENDERBUFFERPROC>(SDL_GL_GetProcAddress("glIsRenderbuffer"));
	pfn_glProgramUniform3uiv = reinterpret_cast<PFNGLPROGRAMUNIFORM3UIVPROC>(SDL_GL_GetProcAddress("glProgramUniform3uiv"));
	pfn_glMinSampleShading = reinterpret_cast<PFNGLMINSAMPLESHADINGPROC>(SDL_GL_GetProcAddress("glMinSampleShading"));
	pfn_glCreateProgram = reinterpret_cast<PFNGLCREATEPROGRAMPROC>(SDL_GL_GetProcAddress("glCreateProgram"));
	pfn_glProgramUniform4f = reinterpret_cast<PFNGLPROGRAMUNIFORM4FPROC>(SDL_GL_GetProcAddress("glProgramUniform4f"));
	pfn_glDrawRangeElementsBaseVertex = reinterpret_cast<PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC>(SDL_GL_GetProcAddress("glDrawRangeElementsBaseVertex"));
	pfn_glDepthFunc = reinterpret_cast<PFNGLDEPTHFUNCPROC>(SDL_GL_GetProcAddress("glDepthFunc"));
	pfn_glProgramUniform4dv = reinterpret_cast<PFNGLPROGRAMUNIFORM4DVPROC>(SDL_GL_GetProcAddress("glProgramUniform4dv"));
	pfn_glDepthMask = reinterpret_cast<PFNGLDEPTHMASKPROC>(SDL_GL_GetProcAddress("glDepthMask"));
	pfn_glGetFramebufferAttachmentParameteriv = reinterpret_cast<PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC>(SDL_GL_GetProcAddress("glGetFramebufferAttachmentParameteriv"));
	pfn_glGetNamedRenderbufferParameteriv = reinterpret_cast<PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC>(SDL_GL_GetProcAddress("glGetNamedRenderbufferParameteriv"));
	pfn_glProgramUniform4i = reinterpret_cast<PFNGLPROGRAMUNIFORM4IPROC>(SDL_GL_GetProcAddress("glProgramUniform4i"));
	pfn_glCreateProgramPipelines = reinterpret_cast<PFNGLCREATEPROGRAMPIPELINESPROC>(SDL_GL_GetProcAddress("glCreateProgramPipelines"));
	pfn_glNamedFramebufferTextureLayer = reinterpret_cast<PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC>(SDL_GL_GetProcAddress("glNamedFramebufferTextureLayer"));
	pfn_glDepthRange = reinterpret_cast<PFNGLDEPTHRANGEPROC>(SDL_GL_GetProcAddress("glDepthRange"));
	pfn_glIsSampler = reinterpret_cast<PFNGLISSAMPLERPROC>(SDL_GL_GetProcAddress("glIsSampler"));
	pfn_glProgramUniform4fv = reinterpret_cast<PFNGLPROGRAMUNIFORM4FVPROC>(SDL_GL_GetProcAddress("glProgramUniform4fv"));
	pfn_glResumeTransformFeedback = reinterpret_cast<PFNGLRESUMETRANSFORMFEEDBACKPROC>(SDL_GL_GetProcAddress("glResumeTransformFeedback"));
	pfn_glGetObjectLabel = reinterpret_cast<PFNGLGETOBJECTLABELPROC>(SDL_GL_GetProcAddress("glGetObjectLabel"));
	pfn_glCreateQueries = reinterpret_cast<PFNGLCREATEQUERIESPROC>(SDL_GL_GetProcAddress("glCreateQueries"));
	pfn_glIsShader = reinterpret_cast<PFNGLISSHADERPROC>(SDL_GL_GetProcAddress("glIsShader"));
	pfn_glGetnUniformfv = reinterpret_cast<PFNGLGETNUNIFORMFVPROC>(SDL_GL_GetProcAddress("glGetnUniformfv"));
	pfn_glCreateRenderbuffers = reinterpret_cast<PFNGLCREATERENDERBUFFERSPROC>(SDL_GL_GetProcAddress("glCreateRenderbuffers"));
	pfn_glGetFramebufferParameteriv = reinterpret_cast<PFNGLGETFRAMEBUFFERPARAMETERIVPROC>(SDL_GL_GetProcAddress("glGetFramebufferParameteriv"));
	pfn_glShaderBinary = reinterpret_cast<PFNGLSHADERBINARYPROC>(SDL_GL_GetProcAddress("glShaderBinary"));
	pfn_glGetGraphicsResetStatus = reinterpret_cast<PFNGLGETGRAPHICSRESETSTATUSPROC>(SDL_GL_GetProcAddress("glGetGraphicsResetStatus"));
	pfn_glCreateSamplers = reinterpret_cast<PFNGLCREATESAMPLERSPROC>(SDL_GL_GetProcAddress("glCreateSamplers"));
	pfn_glDepthRangeArrayv = reinterpret_cast<PFNGLDEPTHRANGEARRAYVPROC>(SDL_GL_GetProcAddress("glDepthRangeArrayv"));
	pfn_glIsSync = reinterpret_cast<PFNGLISSYNCPROC>(SDL_GL_GetProcAddress("glIsSync"));
	pfn_glDepthRangeIndexed = reinterpret_cast<PFNGLDEPTHRANGEINDEXEDPROC>(SDL_GL_GetProcAddress("glDepthRangeIndexed"));
	pfn_glCreateShader = reinterpret_cast<PFNGLCREATESHADERPROC>(SDL_GL_GetProcAddress("glCreateShader"));
	pfn_glProgramUniform4ui = reinterpret_cast<PFNGLPROGRAMUNIFORM4UIPROC>(SDL_GL_GetProcAddress("glProgramUniform4ui"));
	pfn_glProgramUniform4iv = reinterpret_cast<PFNGLPROGRAMUNIFORM4IVPROC>(SDL_GL_GetProcAddress("glProgramUniform4iv"));
	pfn_glGetObjectPtrLabel = reinterpret_cast<PFNGLGETOBJECTPTRLABELPROC>(SDL_GL_GetProcAddress("glGetObjectPtrLabel"));
	pfn_glSampleCoverage = reinterpret_cast<PFNGLSAMPLECOVERAGEPROC>(SDL_GL_GetProcAddress("glSampleCoverage"));
	pfn_glDrawTransformFeedback = reinterpret_cast<PFNGLDRAWTRANSFORMFEEDBACKPROC>(SDL_GL_GetProcAddress("glDrawTransformFeedback"));
	pfn_glIsTexture = reinterpret_cast<PFNGLISTEXTUREPROC>(SDL_GL_GetProcAddress("glIsTexture"));
	pfn_glShaderStorageBlockBinding = reinterpret_cast<PFNGLSHADERSTORAGEBLOCKBINDINGPROC>(SDL_GL_GetProcAddress("glShaderStorageBlockBinding"));
	pfn_glNamedRenderbufferStorageMultisample = reinterpret_cast<PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC>(SDL_GL_GetProcAddress("glNamedRenderbufferStorageMultisample"));
	pfn_glCreateShaderProgramv = reinterpret_cast<PFNGLCREATESHADERPROGRAMVPROC>(SDL_GL_GetProcAddress("glCreateShaderProgramv"));
	pfn_glNamedRenderbufferStorage = reinterpret_cast<PFNGLNAMEDRENDERBUFFERSTORAGEPROC>(SDL_GL_GetProcAddress("glNamedRenderbufferStorage"));
	pfn_glDepthRangef = reinterpret_cast<PFNGLDEPTHRANGEFPROC>(SDL_GL_GetProcAddress("glDepthRangef"));
	pfn_glDrawTransformFeedbackInstanced = reinterpret_cast<PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC>(SDL_GL_GetProcAddress("glDrawTransformFeedbackInstanced"));
	pfn_glShaderSource = reinterpret_cast<PFNGLSHADERSOURCEPROC>(SDL_GL_GetProcAddress("glShaderSource"));
	pfn_glProgramUniform4uiv = reinterpret_cast<PFNGLPROGRAMUNIFORM4UIVPROC>(SDL_GL_GetProcAddress("glProgramUniform4uiv"));
	pfn_glCreateTextures = reinterpret_cast<PFNGLCREATETEXTURESPROC>(SDL_GL_GetProcAddress("glCreateTextures"));
	pfn_glMultiDrawArrays = reinterpret_cast<PFNGLMULTIDRAWARRAYSPROC>(SDL_GL_GetProcAddress("glMultiDrawArrays"));
	pfn_glDrawTransformFeedbackStream = reinterpret_cast<PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC>(SDL_GL_GetProcAddress("glDrawTransformFeedbackStream"));
	pfn_glVertexArrayAttribBinding = reinterpret_cast<PFNGLVERTEXARRAYATTRIBBINDINGPROC>(SDL_GL_GetProcAddress("glVertexArrayAttribBinding"));
	pfn_glDrawTransformFeedbackStreamInstanced = reinterpret_cast<PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC>(SDL_GL_GetProcAddress("glDrawTransformFeedbackStreamInstanced"));
	pfn_glCreateVertexArrays = reinterpret_cast<PFNGLCREATEVERTEXARRAYSPROC>(SDL_GL_GetProcAddress("glCreateVertexArrays"));
	pfn_glIsTransformFeedback = reinterpret_cast<PFNGLISTRANSFORMFEEDBACKPROC>(SDL_GL_GetProcAddress("glIsTransformFeedback"));
	pfn_glCreateTransformFeedbacks = reinterpret_cast<PFNGLCREATETRANSFORMFEEDBACKSPROC>(SDL_GL_GetProcAddress("glCreateTransformFeedbacks"));
	pfn_glVertexArrayAttribFormat = reinterpret_cast<PFNGLVERTEXARRAYATTRIBFORMATPROC>(SDL_GL_GetProcAddress("glVertexArrayAttribFormat"));
	pfn_glProgramUniformMatrix2dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2DVPROC>(SDL_GL_GetProcAddress("glProgramUniformMatrix2dv"));
	pfn_glReadBuffer = reinterpret_cast<PFNGLREADBUFFERPROC>(SDL_GL_GetProcAddress("glReadBuffer"));
	pfn_glMapBufferRange = reinterpret_cast<PFNGLMAPBUFFERRANGEPROC>(SDL_GL_GetProcAddress("glMapBufferRange"));
	pfn_glMultiDrawArraysIndirect = reinterpret_cast<PFNGLMULTIDRAWARRAYSINDIRECTPROC>(SDL_GL_GetProcAddress("glMultiDrawArraysIndirect"));
	pfn_glCullFace = reinterpret_cast<PFNGLCULLFACEPROC>(SDL_GL_GetProcAddress("glCullFace"));
	pfn_glMapBuffer = reinterpret_cast<PFNGLMAPBUFFERPROC>(SDL_GL_GetProcAddress("glMapBuffer"));
	pfn_glVertexArrayAttribIFormat = reinterpret_cast<PFNGLVERTEXARRAYATTRIBIFORMATPROC>(SDL_GL_GetProcAddress("glVertexArrayAttribIFormat"));
	pfn_glDetachShader = reinterpret_cast<PFNGLDETACHSHADERPROC>(SDL_GL_GetProcAddress("glDetachShader"));
	pfn_glVertexArrayAttribLFormat = reinterpret_cast<PFNGLVERTEXARRAYATTRIBLFORMATPROC>(SDL_GL_GetProcAddress("glVertexArrayAttribLFormat"));
	pfn_glSampleMaski = reinterpret_cast<PFNGLSAMPLEMASKIPROC>(SDL_GL_GetProcAddress("glSampleMaski"));
	pfn_glIsVertexArray = reinterpret_cast<PFNGLISVERTEXARRAYPROC>(SDL_GL_GetProcAddress("glIsVertexArray"));
	pfn_glProgramUniformMatrix2fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2FVPROC>(SDL_GL_GetProcAddress("glProgramUniformMatrix2fv"));
	pfn_glVertexArrayBindingDivisor = reinterpret_cast<PFNGLVERTEXARRAYBINDINGDIVISORPROC>(SDL_GL_GetProcAddress("glVertexArrayBindingDivisor"));
	pfn_glMultiDrawArraysIndirectCount = reinterpret_cast<PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC>(SDL_GL_GetProcAddress("glMultiDrawArraysIndirectCount"));
	pfn_glDisable = reinterpret_cast<PFNGLDISABLEPROC>(SDL_GL_GetProcAddress("glDisable"));
	pfn_glVertexArrayElementBuffer = reinterpret_cast<PFNGLVERTEXARRAYELEMENTBUFFERPROC>(SDL_GL_GetProcAddress("glVertexArrayElementBuffer"));
	pfn_glProgramUniformMatrix2x3dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC>(SDL_GL_GetProcAddress("glProgramUniformMatrix2x3dv"));
	pfn_glReadPixels = reinterpret_cast<PFNGLREADPIXELSPROC>(SDL_GL_GetProcAddress("glReadPixels"));
	pfn_glMultiDrawElements = reinterpret_cast<PFNGLMULTIDRAWELEMENTSPROC>(SDL_GL_GetProcAddress("glMultiDrawElements"));
	pfn_glSamplerParameterIiv = reinterpret_cast<PFNGLSAMPLERPARAMETERIIVPROC>(SDL_GL_GetProcAddress("glSamplerParameterIiv"));
	pfn_glProgramUniformMatrix2x3fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC>(SDL_GL_GetProcAddress("glProgramUniformMatrix2x3fv"));
	pfn_glSpecializeShader = reinterpret_cast<PFNGLSPECIALIZESHADERPROC>(SDL_GL_GetProcAddress("glSpecializeShader"));
	pfn_glGetInteger64i_v = reinterpret_cast<PFNGLGETINTEGER64I_VPROC>(SDL_GL_GetProcAddress("glGetInteger64i_v"));
	pfn_glDebugMessageCallback = reinterpret_cast<PFNGLDEBUGMESSAGECALLBACKPROC>(SDL_GL_GetProcAddress("glDebugMessageCallback"));
	pfn_glMultiDrawElementsBaseVertex = reinterpret_cast<PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC>(SDL_GL_GetProcAddress("glMultiDrawElementsBaseVertex"));
	pfn_glProgramUniformMatrix2x4dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC>(SDL_GL_GetProcAddress("glProgramUniformMatrix2x4dv"));
	pfn_glSamplerParameterIuiv = reinterpret_cast<PFNGLSAMPLERPARAMETERIUIVPROC>(SDL_GL_GetProcAddress("glSamplerParameterIuiv"));
	pfn_glGetInteger64v = reinterpret_cast<PFNGLGETINTEGER64VPROC>(SDL_GL_GetProcAddress("glGetInteger64v"));
	pfn_glProgramUniformMatrix2x4fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC>(SDL_GL_GetProcAddress("glProgramUniformMatrix2x4fv"));
	pfn_glReadnPixels = reinterpret_cast<PFNGLREADNPIXELSPROC>(SDL_GL_GetProcAddress("glReadnPixels"));
	pfn_glMultiDrawElementsIndirect = reinterpret_cast<PFNGLMULTIDRAWELEMENTSINDIRECTPROC>(SDL_GL_GetProcAddress("glMultiDrawElementsIndirect"));
	pfn_glSamplerParameterf = reinterpret_cast<PFNGLSAMPLERPARAMETERFPROC>(SDL_GL_GetProcAddress("glSamplerParameterf"));
	pfn_glDebugMessageControl = reinterpret_cast<PFNGLDEBUGMESSAGECONTROLPROC>(SDL_GL_GetProcAddress("glDebugMessageControl"));
	pfn_glProgramUniformMatrix3dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3DVPROC>(SDL_GL_GetProcAddress("glProgramUniformMatrix3dv"));
	pfn_glSamplerParameterfv = reinterpret_cast<PFNGLSAMPLERPARAMETERFVPROC>(SDL_GL_GetProcAddress("glSamplerParameterfv"));
	pfn_glMapNamedBufferRange = reinterpret_cast<PFNGLMAPNAMEDBUFFERRANGEPROC>(SDL_GL_GetProcAddress("glMapNamedBufferRange"));
	pfn_glEnable = reinterpret_cast<PFNGLENABLEPROC>(SDL_GL_GetProcAddress("glEnable"));
	pfn_glSamplerParameteri = reinterpret_cast<PFNGLSAMPLERPARAMETERIPROC>(SDL_GL_GetProcAddress("glSamplerParameteri"));
	pfn_glProgramUniformMatrix3fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3FVPROC>(SDL_GL_GetProcAddress("glProgramUniformMatrix3fv"));
	pfn_glDisableVertexArrayAttrib = reinterpret_cast<PFNGLDISABLEVERTEXARRAYATTRIBPROC>(SDL_GL_GetProcAddress("glDisableVertexArrayAttrib"));
	pfn_glGetIntegeri_v = reinterpret_cast<PFNGLGETINTEGERI_VPROC>(SDL_GL_GetProcAddress("glGetIntegeri_v"));
	pfn_glSamplerParameteriv = reinterpret_cast<PFNGLSAMPLERPARAMETERIVPROC>(SDL_GL_GetProcAddress("glSamplerParameteriv"));
	pfn_glMultiDrawElementsIndirectCount = reinterpret_cast<PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC>(SDL_GL_GetProcAddress("glMultiDrawElementsIndirectCount"));
	pfn_glProgramUniformMatrix3x2dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC>(SDL_GL_GetProcAddress("glProgramUniformMatrix3x2dv"));
	pfn_glDebugMessageInsert = reinterpret_cast<PFNGLDEBUGMESSAGEINSERTPROC>(SDL_GL_GetProcAddress("glDebugMessageInsert"));
	pfn_glGetIntegerv = reinterpret_cast<PFNGLGETINTEGERVPROC>(SDL_GL_GetProcAddress("glGetIntegerv"));
	pfn_glMapNamedBuffer = reinterpret_cast<PFNGLMAPNAMEDBUFFERPROC>(SDL_GL_GetProcAddress("glMapNamedBuffer"));
	pfn_glProgramUniformMatrix3x2fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC>(SDL_GL_GetProcAddress("glProgramUniformMatrix3x2fv"));
	pfn_glVertexArrayVertexBuffer = reinterpret_cast<PFNGLVERTEXARRAYVERTEXBUFFERPROC>(SDL_GL_GetProcAddress("glVertexArrayVertexBuffer"));
	pfn_glProgramUniformMatrix3x4dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC>(SDL_GL_GetProcAddress("glProgramUniformMatrix3x4dv"));
	pfn_glDisableVertexAttribArray = reinterpret_cast<PFNGLDISABLEVERTEXATTRIBARRAYPROC>(SDL_GL_GetProcAddress("glDisableVertexAttribArray"));
	pfn_glProgramUniformMatrix3x4fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC>(SDL_GL_GetProcAddress("glProgramUniformMatrix3x4fv"));
	pfn_glStencilFunc = reinterpret_cast<PFNGLSTENCILFUNCPROC>(SDL_GL_GetProcAddress("glStencilFunc"));
	pfn_glProgramUniformMatrix4dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4DVPROC>(SDL_GL_GetProcAddress("glProgramUniformMatrix4dv"));
	pfn_glGetInternalformativ = reinterpret_cast<PFNGLGETINTERNALFORMATIVPROC>(SDL_GL_GetProcAddress("glGetInternalformativ"));
	pfn_glScissor = reinterpret_cast<PFNGLSCISSORPROC>(SDL_GL_GetProcAddress("glScissor"));
	pfn_glDisablei = reinterpret_cast<PFNGLDISABLEIPROC>(SDL_GL_GetProcAddress("glDisablei"));
	pfn_glStencilFuncSeparate = reinterpret_cast<PFNGLSTENCILFUNCSEPARATEPROC>(SDL_GL_GetProcAddress("glStencilFuncSeparate"));
	pfn_glProgramUniformMatrix4fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4FVPROC>(SDL_GL_GetProcAddress("glProgramUniformMatrix4fv"));
	pfn_glEnableVertexArrayAttrib = reinterpret_cast<PFNGLENABLEVERTEXARRAYATTRIBPROC>(SDL_GL_GetProcAddress("glEnableVertexArrayAttrib"));
	pfn_glDeleteBuffers = reinterpret_cast<PFNGLDELETEBUFFERSPROC>(SDL_GL_GetProcAddress("glDeleteBuffers"));
	pfn_glGetInternalformati64v = reinterpret_cast<PFNGLGETINTERNALFORMATI64VPROC>(SDL_GL_GetProcAddress("glGetInternalformati64v"));
	pfn_glScissorArrayv = reinterpret_cast<PFNGLSCISSORARRAYVPROC>(SDL_GL_GetProcAddress("glScissorArrayv"));
	pfn_glVertexArrayVertexBuffers = reinterpret_cast<PFNGLVERTEXARRAYVERTEXBUFFERSPROC>(SDL_GL_GetProcAddress("glVertexArrayVertexBuffers"));
	pfn_glStencilMask = reinterpret_cast<PFNGLSTENCILMASKPROC>(SDL_GL_GetProcAddress("glStencilMask"));
	pfn_glProgramUniformMatrix4x2dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC>(SDL_GL_GetProcAddress("glProgramUniformMatrix4x2dv"));
	pfn_glStencilMaskSeparate = reinterpret_cast<PFNGLSTENCILMASKSEPARATEPROC>(SDL_GL_GetProcAddress("glStencilMaskSeparate"));
	pfn_glVertexAttrib1d = reinterpret_cast<PFNGLVERTEXATTRIB1DPROC>(SDL_GL_GetProcAddress("glVertexAttrib1d"));
	pfn_glProgramUniformMatrix4x2fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC>(SDL_GL_GetProcAddress("glProgramUniformMatrix4x2fv"));
	pfn_glStencilOp = reinterpret_cast<PFNGLSTENCILOPPROC>(SDL_GL_GetProcAddress("glStencilOp"));
	pfn_glVertexAttrib1dv = reinterpret_cast<PFNGLVERTEXATTRIB1DVPROC>(SDL_GL_GetProcAddress("glVertexAttrib1dv"));
	pfn_glNormalP3ui = reinterpret_cast<PFNGLNORMALP3UIPROC>(SDL_GL_GetProcAddress("glNormalP3ui"));
	pfn_glProgramUniformMatrix4x3dv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC>(SDL_GL_GetProcAddress("glProgramUniformMatrix4x3dv"));
	pfn_glStencilOpSeparate = reinterpret_cast<PFNGLSTENCILOPSEPARATEPROC>(SDL_GL_GetProcAddress("glStencilOpSeparate"));
	pfn_glEnableVertexAttribArray = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>(SDL_GL_GetProcAddress("glEnableVertexAttribArray"));
	pfn_glNormalP3uiv = reinterpret_cast<PFNGLNORMALP3UIVPROC>(SDL_GL_GetProcAddress("glNormalP3uiv"));
	pfn_glScissorIndexed = reinterpret_cast<PFNGLSCISSORINDEXEDPROC>(SDL_GL_GetProcAddress("glScissorIndexed"));
	pfn_glProgramUniformMatrix4x3fv = reinterpret_cast<PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC>(SDL_GL_GetProcAddress("glProgramUniformMatrix4x3fv"));
	pfn_glProvokingVertex = reinterpret_cast<PFNGLPROVOKINGVERTEXPROC>(SDL_GL_GetProcAddress("glProvokingVertex"));
	pfn_glDispatchCompute = reinterpret_cast<PFNGLDISPATCHCOMPUTEPROC>(SDL_GL_GetProcAddress("glDispatchCompute"));
	pfn_glDeleteFramebuffers = reinterpret_cast<PFNGLDELETEFRAMEBUFFERSPROC>(SDL_GL_GetProcAddress("glDeleteFramebuffers"));
	pfn_glVertexAttrib1f = reinterpret_cast<PFNGLVERTEXATTRIB1FPROC>(SDL_GL_GetProcAddress("glVertexAttrib1f"));
	pfn_glEnablei = reinterpret_cast<PFNGLENABLEIPROC>(SDL_GL_GetProcAddress("glEnablei"));
	pfn_glDrawArrays = reinterpret_cast<PFNGLDRAWARRAYSPROC>(SDL_GL_GetProcAddress("glDrawArrays"));
	pfn_glGetProgramBinary = reinterpret_cast<PFNGLGETPROGRAMBINARYPROC>(SDL_GL_GetProcAddress("glGetProgramBinary"));
	pfn_glReleaseShaderCompiler = reinterpret_cast<PFNGLRELEASESHADERCOMPILERPROC>(SDL_GL_GetProcAddress("glReleaseShaderCompiler"));
	pfn_glDispatchComputeIndirect = reinterpret_cast<PFNGLDISPATCHCOMPUTEINDIRECTPROC>(SDL_GL_GetProcAddress("glDispatchComputeIndirect"));
	pfn_glGetProgramInfoLog = reinterpret_cast<PFNGLGETPROGRAMINFOLOGPROC>(SDL_GL_GetProcAddress("glGetProgramInfoLog"));
	pfn_glDrawArraysInstanced = reinterpret_cast<PFNGLDRAWARRAYSINSTANCEDPROC>(SDL_GL_GetProcAddress("glDrawArraysInstanced"));
	pfn_glScissorIndexedv = reinterpret_cast<PFNGLSCISSORINDEXEDVPROC>(SDL_GL_GetProcAddress("glScissorIndexedv"));
	pfn_glVertexAttrib1fv = reinterpret_cast<PFNGLVERTEXATTRIB1FVPROC>(SDL_GL_GetProcAddress("glVertexAttrib1fv"));
	pfn_glDrawArraysIndirect = reinterpret_cast<PFNGLDRAWARRAYSINDIRECTPROC>(SDL_GL_GetProcAddress("glDrawArraysIndirect"));
	pfn_glRenderbufferStorage = reinterpret_cast<PFNGLRENDERBUFFERSTORAGEPROC>(SDL_GL_GetProcAddress("glRenderbufferStorage"));
	pfn_glGetProgramInterfaceiv = reinterpret_cast<PFNGLGETPROGRAMINTERFACEIVPROC>(SDL_GL_GetProcAddress("glGetProgramInterfaceiv"));
	pfn_glDrawArraysInstancedBaseInstance = reinterpret_cast<PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC>(SDL_GL_GetProcAddress("glDrawArraysInstancedBaseInstance"));
	pfn_glRenderbufferStorageMultisample = reinterpret_cast<PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC>(SDL_GL_GetProcAddress("glRenderbufferStorageMultisample"));
	pfn_glPushDebugGroup = reinterpret_cast<PFNGLPUSHDEBUGGROUPPROC>(SDL_GL_GetProcAddress("glPushDebugGroup"));
	pfn_glEndConditionalRender = reinterpret_cast<PFNGLENDCONDITIONALRENDERPROC>(SDL_GL_GetProcAddress("glEndConditionalRender"));
	pfn_glWaitSync = reinterpret_cast<PFNGLWAITSYNCPROC>(SDL_GL_GetProcAddress("glWaitSync"));
	pfn_glPointSize = reinterpret_cast<PFNGLPOINTSIZEPROC>(SDL_GL_GetProcAddress("glPointSize"));
	pfn_glUniform4ui = reinterpret_cast<PFNGLUNIFORM4UIPROC>(SDL_GL_GetProcAddress("glUniform4ui"));
	pfn_glTexParameterIiv = reinterpret_cast<PFNGLTEXPARAMETERIIVPROC>(SDL_GL_GetProcAddress("glTexParameterIiv"));
	pfn_glVertexAttrib1s = reinterpret_cast<PFNGLVERTEXATTRIB1SPROC>(SDL_GL_GetProcAddress("glVertexAttrib1s"));
	pfn_glGetTextureParameterfv = reinterpret_cast<PFNGLGETTEXTUREPARAMETERFVPROC>(SDL_GL_GetProcAddress("glGetTextureParameterfv"));
	pfn_glClearDepth = reinterpret_cast<PFNGLCLEARDEPTHPROC>(SDL_GL_GetProcAddress("glClearDepth"));
	pfn_glGetTextureParameteriv = reinterpret_cast<PFNGLGETTEXTUREPARAMETERIVPROC>(SDL_GL_GetProcAddress("glGetTextureParameteriv"));
	pfn_glVertexAttribLFormat = reinterpret_cast<PFNGLVERTEXATTRIBLFORMATPROC>(SDL_GL_GetProcAddress("glVertexAttribLFormat"));
	pfn_glObjectLabel = reinterpret_cast<PFNGLOBJECTLABELPROC>(SDL_GL_GetProcAddress("glObjectLabel"));
	pfn_glUniform4iv = reinterpret_cast<PFNGLUNIFORM4IVPROC>(SDL_GL_GetProcAddress("glUniform4iv"));
	pfn_glVertexAttrib4ubv = reinterpret_cast<PFNGLVERTEXATTRIB4UBVPROC>(SDL_GL_GetProcAddress("glVertexAttrib4ubv"));
	pfn_glGenFramebuffers = reinterpret_cast<PFNGLGENFRAMEBUFFERSPROC>(SDL_GL_GetProcAddress("glGenFramebuffers"));
	pfn_glVertexAttrib4uiv = reinterpret_cast<PFNGLVERTEXATTRIB4UIVPROC>(SDL_GL_GetProcAddress("glVertexAttrib4uiv"));
	pfn_glTexParameterIuiv = reinterpret_cast<PFNGLTEXPARAMETERIUIVPROC>(SDL_GL_GetProcAddress("glTexParameterIuiv"));
	pfn_glGetnUniformiv = reinterpret_cast<PFNGLGETNUNIFORMIVPROC>(SDL_GL_GetProcAddress("glGetnUniformiv"));
	pfn_glVertexAttrib1sv = reinterpret_cast<PFNGLVERTEXATTRIB1SVPROC>(SDL_GL_GetProcAddress("glVertexAttrib1sv"));
	pfn_glGetProgramPipelineInfoLog = reinterpret_cast<PFNGLGETPROGRAMPIPELINEINFOLOGPROC>(SDL_GL_GetProcAddress("glGetProgramPipelineInfoLog"));
	pfn_glVertexAttribLPointer = reinterpret_cast<PFNGLVERTEXATTRIBLPOINTERPROC>(SDL_GL_GetProcAddress("glVertexAttribLPointer"));
	pfn_glObjectPtrLabel = reinterpret_cast<PFNGLOBJECTPTRLABELPROC>(SDL_GL_GetProcAddress("glObjectPtrLabel"));
	pfn_glClearDepthf = reinterpret_cast<PFNGLCLEARDEPTHFPROC>(SDL_GL_GetProcAddress("glClearDepthf"));
	pfn_glTexParameterf = reinterpret_cast<PFNGLTEXPARAMETERFPROC>(SDL_GL_GetProcAddress("glTexParameterf"));
	pfn_glUniform1d = reinterpret_cast<PFNGLUNIFORM1DPROC>(SDL_GL_GetProcAddress("glUniform1d"));
	pfn_glGetProgramPipelineiv = reinterpret_cast<PFNGLGETPROGRAMPIPELINEIVPROC>(SDL_GL_GetProcAddress("glGetProgramPipelineiv"));
	pfn_glVertexAttrib4usv = reinterpret_cast<PFNGLVERTEXATTRIB4USVPROC>(SDL_GL_GetProcAddress("glVertexAttrib4usv"));
	pfn_glGetTextureSubImage = reinterpret_cast<PFNGLGETTEXTURESUBIMAGEPROC>(SDL_GL_GetProcAddress("glGetTextureSubImage"));
	pfn_glVertexAttribP2ui = reinterpret_cast<PFNGLVERTEXATTRIBP2UIPROC>(SDL_GL_GetProcAddress("glVertexAttribP2ui"));
	pfn_glUniform1dv = reinterpret_cast<PFNGLUNIFORM1DVPROC>(SDL_GL_GetProcAddress("glUniform1dv"));
	pfn_glVertexAttribP1uiv = reinterpret_cast<PFNGLVERTEXATTRIBP1UIVPROC>(SDL_GL_GetProcAddress("glVertexAttribP1uiv"));
	pfn_glGetnUniformuiv = reinterpret_cast<PFNGLGETNUNIFORMUIVPROC>(SDL_GL_GetProcAddress("glGetnUniformuiv"));
	pfn_glTexParameterfv = reinterpret_cast<PFNGLTEXPARAMETERFVPROC>(SDL_GL_GetProcAddress("glTexParameterfv"));
	pfn_glGetProgramResourceIndex = reinterpret_cast<PFNGLGETPROGRAMRESOURCEINDEXPROC>(SDL_GL_GetProcAddress("glGetProgramResourceIndex"));
	pfn_glVertexAttribP2uiv = reinterpret_cast<PFNGLVERTEXATTRIBP2UIVPROC>(SDL_GL_GetProcAddress("glVertexAttribP2uiv"));
	pfn_glUniform1f = reinterpret_cast<PFNGLUNIFORM1FPROC>(SDL_GL_GetProcAddress("glUniform1f"));
	pfn_glGetTransformFeedbackVarying = reinterpret_cast<PFNGLGETTRANSFORMFEEDBACKVARYINGPROC>(SDL_GL_GetProcAddress("glGetTransformFeedbackVarying"));
	pfn_glVertexAttribP1ui = reinterpret_cast<PFNGLVERTEXATTRIBP1UIPROC>(SDL_GL_GetProcAddress("glVertexAttribP1ui"));
	pfn_glGetProgramResourceLocation = reinterpret_cast<PFNGLGETPROGRAMRESOURCELOCATIONPROC>(SDL_GL_GetProcAddress("glGetProgramResourceLocation"));
	pfn_glTexParameteri = reinterpret_cast<PFNGLTEXPARAMETERIPROC>(SDL_GL_GetProcAddress("glTexParameteri"));
	pfn_glVertexAttrib2d = reinterpret_cast<PFNGLVERTEXATTRIB2DPROC>(SDL_GL_GetProcAddress("glVertexAttrib2d"));
	pfn_glVertexAttribP3ui = reinterpret_cast<PFNGLVERTEXATTRIBP3UIPROC>(SDL_GL_GetProcAddress("glVertexAttribP3ui"));
	pfn_glAttachShader = reinterpret_cast<PFNGLATTACHSHADERPROC>(SDL_GL_GetProcAddress("glAttachShader"));
	pfn_glGetProgramResourceLocationIndex = reinterpret_cast<PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC>(SDL_GL_GetProcAddress("glGetProgramResourceLocationIndex"));
	pfn_glGetTransformFeedbacki64_v = reinterpret_cast<PFNGLGETTRANSFORMFEEDBACKI64_VPROC>(SDL_GL_GetProcAddress("glGetTransformFeedbacki64_v"));
	pfn_glUniformBlockBinding = reinterpret_cast<PFNGLUNIFORMBLOCKBINDINGPROC>(SDL_GL_GetProcAddress("glUniformBlockBinding"));
	pfn_glVertexAttribP3uiv = reinterpret_cast<PFNGLVERTEXATTRIBP3UIVPROC>(SDL_GL_GetProcAddress("glVertexAttribP3uiv"));
	pfn_glPolygonMode = reinterpret_cast<PFNGLPOLYGONMODEPROC>(SDL_GL_GetProcAddress("glPolygonMode"));
	pfn_glTexParameteriv = reinterpret_cast<PFNGLTEXPARAMETERIVPROC>(SDL_GL_GetProcAddress("glTexParameteriv"));
	pfn_glVertexAttribDivisor = reinterpret_cast<PFNGLVERTEXATTRIBDIVISORPROC>(SDL_GL_GetProcAddress("glVertexAttribDivisor"));
	pfn_glVertexAttribP4ui = reinterpret_cast<PFNGLVERTEXATTRIBP4UIPROC>(SDL_GL_GetProcAddress("glVertexAttribP4ui"));
	pfn_glGetProgramResourceName = reinterpret_cast<PFNGLGETPROGRAMRESOURCENAMEPROC>(SDL_GL_GetProcAddress("glGetProgramResourceName"));
	pfn_glGetTransformFeedbacki_v = reinterpret_cast<PFNGLGETTRANSFORMFEEDBACKI_VPROC>(SDL_GL_GetProcAddress("glGetTransformFeedbacki_v"));
	pfn_glVertexAttribP4uiv = reinterpret_cast<PFNGLVERTEXATTRIBP4UIVPROC>(SDL_GL_GetProcAddress("glVertexAttribP4uiv"));
	pfn_glEndQuery = reinterpret_cast<PFNGLENDQUERYPROC>(SDL_GL_GetProcAddress("glEndQuery"));
	pfn_glUniform1fv = reinterpret_cast<PFNGLUNIFORM1FVPROC>(SDL_GL_GetProcAddress("glUniform1fv"));
	pfn_glBeginConditionalRender = reinterpret_cast<PFNGLBEGINCONDITIONALRENDERPROC>(SDL_GL_GetProcAddress("glBeginConditionalRender"));
	pfn_glGetProgramStageiv = reinterpret_cast<PFNGLGETPROGRAMSTAGEIVPROC>(SDL_GL_GetProcAddress("glGetProgramStageiv"));
	pfn_glVertexAttribBinding = reinterpret_cast<PFNGLVERTEXATTRIBBINDINGPROC>(SDL_GL_GetProcAddress("glVertexAttribBinding"));
	pfn_glGetTransformFeedbackiv = reinterpret_cast<PFNGLGETTRANSFORMFEEDBACKIVPROC>(SDL_GL_GetProcAddress("glGetTransformFeedbackiv"));
	pfn_glUniform4uiv = reinterpret_cast<PFNGLUNIFORM4UIVPROC>(SDL_GL_GetProcAddress("glUniform4uiv"));
	pfn_glGetProgramResourceiv = reinterpret_cast<PFNGLGETPROGRAMRESOURCEIVPROC>(SDL_GL_GetProcAddress("glGetProgramResourceiv"));
	pfn_glVertexAttrib2dv = reinterpret_cast<PFNGLVERTEXATTRIB2DVPROC>(SDL_GL_GetProcAddress("glVertexAttrib2dv"));
	pfn_glVertexAttribPointer = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERPROC>(SDL_GL_GetProcAddress("glVertexAttribPointer"));
	pfn_glPolygonOffset = reinterpret_cast<PFNGLPOLYGONOFFSETPROC>(SDL_GL_GetProcAddress("glPolygonOffset"));
	pfn_glGetUniformBlockIndex = reinterpret_cast<PFNGLGETUNIFORMBLOCKINDEXPROC>(SDL_GL_GetProcAddress("glGetUniformBlockIndex"));
	pfn_glVertexAttribFormat = reinterpret_cast<PFNGLVERTEXATTRIBFORMATPROC>(SDL_GL_GetProcAddress("glVertexAttribFormat"));
	pfn_glClearNamedBufferData = reinterpret_cast<PFNGLCLEARNAMEDBUFFERDATAPROC>(SDL_GL_GetProcAddress("glClearNamedBufferData"));
	pfn_glUniform1i = reinterpret_cast<PFNGLUNIFORM1IPROC>(SDL_GL_GetProcAddress("glUniform1i"));
	pfn_glGenProgramPipelines = reinterpret_cast<PFNGLGENPROGRAMPIPELINESPROC>(SDL_GL_GetProcAddress("glGenProgramPipelines"));
	pfn_glPolygonOffsetClamp = reinterpret_cast<PFNGLPOLYGONOFFSETCLAMPPROC>(SDL_GL_GetProcAddress("glPolygonOffsetClamp"));
	pfn_glGetUniformIndices = reinterpret_cast<PFNGLGETUNIFORMINDICESPROC>(SDL_GL_GetProcAddress("glGetUniformIndices"));
	pfn_glColorMask = reinterpret_cast<PFNGLCOLORMASKPROC>(SDL_GL_GetProcAddress("glColorMask"));
	pfn_glGetProgramiv = reinterpret_cast<PFNGLGETPROGRAMIVPROC>(SDL_GL_GetProcAddress("glGetProgramiv"));
	pfn_glBlendColor = reinterpret_cast<PFNGLBLENDCOLORPROC>(SDL_GL_GetProcAddress("glBlendColor"));
	pfn_glGetUniformLocation = reinterpret_cast<PFNGLGETUNIFORMLOCATIONPROC>(SDL_GL_GetProcAddress("glGetUniformLocation"));
	pfn_glTexStorage1D = reinterpret_cast<PFNGLTEXSTORAGE1DPROC>(SDL_GL_GetProcAddress("glTexStorage1D"));
	pfn_glVertexAttrib2f = reinterpret_cast<PFNGLVERTEXATTRIB2FPROC>(SDL_GL_GetProcAddress("glVertexAttrib2f"));
	pfn_glClearNamedFramebufferfi = reinterpret_cast<PFNGLCLEARNAMEDFRAMEBUFFERFIPROC>(SDL_GL_GetProcAddress("glClearNamedFramebufferfi"));
	pfn_glEndQueryIndexed = reinterpret_cast<PFNGLENDQUERYINDEXEDPROC>(SDL_GL_GetProcAddress("glEndQueryIndexed"));
	pfn_glVertexAttribI1i = reinterpret_cast<PFNGLVERTEXATTRIBI1IPROC>(SDL_GL_GetProcAddress("glVertexAttribI1i"));
	pfn_glTexStorage2D = reinterpret_cast<PFNGLTEXSTORAGE2DPROC>(SDL_GL_GetProcAddress("glTexStorage2D"));
	pfn_glClearNamedBufferSubData = reinterpret_cast<PFNGLCLEARNAMEDBUFFERSUBDATAPROC>(SDL_GL_GetProcAddress("glClearNamedBufferSubData"));
	pfn_glBlendEquation = reinterpret_cast<PFNGLBLENDEQUATIONPROC>(SDL_GL_GetProcAddress("glBlendEquation"));
	pfn_glVertexAttribI1iv = reinterpret_cast<PFNGLVERTEXATTRIBI1IVPROC>(SDL_GL_GetProcAddress("glVertexAttribI1iv"));
	pfn_glUniformMatrix2dv = reinterpret_cast<PFNGLUNIFORMMATRIX2DVPROC>(SDL_GL_GetProcAddress("glUniformMatrix2dv"));
	pfn_glGetUniformSubroutineuiv = reinterpret_cast<PFNGLGETUNIFORMSUBROUTINEUIVPROC>(SDL_GL_GetProcAddress("glGetUniformSubroutineuiv"));
	pfn_glClearNamedFramebufferuiv = reinterpret_cast<PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC>(SDL_GL_GetProcAddress("glClearNamedFramebufferuiv"));
	pfn_glUniformMatrix2fv = reinterpret_cast<PFNGLUNIFORMMATRIX2FVPROC>(SDL_GL_GetProcAddress("glUniformMatrix2fv"));
	pfn_glColorP3ui = reinterpret_cast<PFNGLCOLORP3UIPROC>(SDL_GL_GetProcAddress("glColorP3ui"));
	pfn_glGetUniformdv = reinterpret_cast<PFNGLGETUNIFORMDVPROC>(SDL_GL_GetProcAddress("glGetUniformdv"));
	pfn_glGenQueries = reinterpret_cast<PFNGLGENQUERIESPROC>(SDL_GL_GetProcAddress("glGenQueries"));
	pfn_glColorMaski = reinterpret_cast<PFNGLCOLORMASKIPROC>(SDL_GL_GetProcAddress("glColorMaski"));
	pfn_glGetQueryBufferObjecti64v = reinterpret_cast<PFNGLGETQUERYBUFFEROBJECTI64VPROC>(SDL_GL_GetProcAddress("glGetQueryBufferObjecti64v"));
	pfn_glGetUniformiv = reinterpret_cast<PFNGLGETUNIFORMIVPROC>(SDL_GL_GetProcAddress("glGetUniformiv"));
	pfn_glColorP3uiv = reinterpret_cast<PFNGLCOLORP3UIVPROC>(SDL_GL_GetProcAddress("glColorP3uiv"));
	pfn_glClearNamedFramebufferiv = reinterpret_cast<PFNGLCLEARNAMEDFRAMEBUFFERIVPROC>(SDL_GL_GetProcAddress("glClearNamedFramebufferiv"));
	pfn_glGetUniformfv = reinterpret_cast<PFNGLGETUNIFORMFVPROC>(SDL_GL_GetProcAddress("glGetUniformfv"));
	pfn_glVertexAttrib2fv = reinterpret_cast<PFNGLVERTEXATTRIB2FVPROC>(SDL_GL_GetProcAddress("glVertexAttrib2fv"));
	pfn_glEndTransformFeedback = reinterpret_cast<PFNGLENDTRANSFORMFEEDBACKPROC>(SDL_GL_GetProcAddress("glEndTransformFeedback"));
	pfn_glClearNamedFramebufferfv = reinterpret_cast<PFNGLCLEARNAMEDFRAMEBUFFERFVPROC>(SDL_GL_GetProcAddress("glClearNamedFramebufferfv"));
	pfn_glHint = reinterpret_cast<PFNGLHINTPROC>(SDL_GL_GetProcAddress("glHint"));
	pfn_glBeginQuery = reinterpret_cast<PFNGLBEGINQUERYPROC>(SDL_GL_GetProcAddress("glBeginQuery"));
	pfn_glVertexAttribI1ui = reinterpret_cast<PFNGLVERTEXATTRIBI1UIPROC>(SDL_GL_GetProcAddress("glVertexAttribI1ui"));
	pfn_glUniformMatrix2x3dv = reinterpret_cast<PFNGLUNIFORMMATRIX2X3DVPROC>(SDL_GL_GetProcAddress("glUniformMatrix2x3dv"));
	pfn_glGetQueryBufferObjectiv = reinterpret_cast<PFNGLGETQUERYBUFFEROBJECTIVPROC>(SDL_GL_GetProcAddress("glGetQueryBufferObjectiv"));
	pfn_glUniformMatrix2x3fv = reinterpret_cast<PFNGLUNIFORMMATRIX2X3FVPROC>(SDL_GL_GetProcAddress("glUniformMatrix2x3fv"));
	pfn_glGetQueryBufferObjectui64v = reinterpret_cast<PFNGLGETQUERYBUFFEROBJECTUI64VPROC>(SDL_GL_GetProcAddress("glGetQueryBufferObjectui64v"));
	pfn_glClearStencil = reinterpret_cast<PFNGLCLEARSTENCILPROC>(SDL_GL_GetProcAddress("glClearStencil"));
	pfn_glUniform1iv = reinterpret_cast<PFNGLUNIFORM1IVPROC>(SDL_GL_GetProcAddress("glUniform1iv"));
	pfn_glTexStorage2DMultisample = reinterpret_cast<PFNGLTEXSTORAGE2DMULTISAMPLEPROC>(SDL_GL_GetProcAddress("glTexStorage2DMultisample"));
	pfn_glGetQueryBufferObjectuiv = reinterpret_cast<PFNGLGETQUERYBUFFEROBJECTUIVPROC>(SDL_GL_GetProcAddress("glGetQueryBufferObjectuiv"));
	pfn_glPatchParameterfv = reinterpret_cast<PFNGLPATCHPARAMETERFVPROC>(SDL_GL_GetProcAddress("glPatchParameterfv"));
	pfn_glVertexAttribI1uiv = reinterpret_cast<PFNGLVERTEXATTRIBI1UIVPROC>(SDL_GL_GetProcAddress("glVertexAttribI1uiv"));
	pfn_glUniformMatrix2x4dv = reinterpret_cast<PFNGLUNIFORMMATRIX2X4DVPROC>(SDL_GL_GetProcAddress("glUniformMatrix2x4dv"));
	pfn_glGetQueryIndexediv = reinterpret_cast<PFNGLGETQUERYINDEXEDIVPROC>(SDL_GL_GetProcAddress("glGetQueryIndexediv"));
	pfn_glTexStorage3D = reinterpret_cast<PFNGLTEXSTORAGE3DPROC>(SDL_GL_GetProcAddress("glTexStorage3D"));
	pfn_glClearTexImage = reinterpret_cast<PFNGLCLEARTEXIMAGEPROC>(SDL_GL_GetProcAddress("glClearTexImage"));
	pfn_glUniformMatrix2x4fv = reinterpret_cast<PFNGLUNIFORMMATRIX2X4FVPROC>(SDL_GL_GetProcAddress("glUniformMatrix2x4fv"));
	pfn_glGetQueryObjecti64v = reinterpret_cast<PFNGLGETQUERYOBJECTI64VPROC>(SDL_GL_GetProcAddress("glGetQueryObjecti64v"));
	pfn_glGetQueryObjectiv = reinterpret_cast<PFNGLGETQUERYOBJECTIVPROC>(SDL_GL_GetProcAddress("glGetQueryObjectiv"));
	pfn_glColorP4ui = reinterpret_cast<PFNGLCOLORP4UIPROC>(SDL_GL_GetProcAddress("glColorP4ui"));
	pfn_glPatchParameteri = reinterpret_cast<PFNGLPATCHPARAMETERIPROC>(SDL_GL_GetProcAddress("glPatchParameteri"));
	pfn_glBlendEquationSeparate = reinterpret_cast<PFNGLBLENDEQUATIONSEPARATEPROC>(SDL_GL_GetProcAddress("glBlendEquationSeparate"));
	pfn_glUniform1ui = reinterpret_cast<PFNGLUNIFORM1UIPROC>(SDL_GL_GetProcAddress("glUniform1ui"));
	pfn_glVertexAttribI2i = reinterpret_cast<PFNGLVERTEXATTRIBI2IPROC>(SDL_GL_GetProcAddress("glVertexAttribI2i"));
	pfn_glGenRenderbuffers = reinterpret_cast<PFNGLGENRENDERBUFFERSPROC>(SDL_GL_GetProcAddress("glGenRenderbuffers"));
	pfn_glUniformMatrix3dv = reinterpret_cast<PFNGLUNIFORMMATRIX3DVPROC>(SDL_GL_GetProcAddress("glUniformMatrix3dv"));
	pfn_glTexStorage3DMultisample = reinterpret_cast<PFNGLTEXSTORAGE3DMULTISAMPLEPROC>(SDL_GL_GetProcAddress("glTexStorage3DMultisample"));
	pfn_glGetQueryObjectuiv = reinterpret_cast<PFNGLGETQUERYOBJECTUIVPROC>(SDL_GL_GetProcAddress("glGetQueryObjectuiv"));
	pfn_glColorP4uiv = reinterpret_cast<PFNGLCOLORP4UIVPROC>(SDL_GL_GetProcAddress("glColorP4uiv"));
	pfn_glBeginQueryIndexed = reinterpret_cast<PFNGLBEGINQUERYINDEXEDPROC>(SDL_GL_GetProcAddress("glBeginQueryIndexed"));
	pfn_glPopDebugGroup = reinterpret_cast<PFNGLPOPDEBUGGROUPPROC>(SDL_GL_GetProcAddress("glPopDebugGroup"));
	pfn_glUniformMatrix3fv = reinterpret_cast<PFNGLUNIFORMMATRIX3FVPROC>(SDL_GL_GetProcAddress("glUniformMatrix3fv"));
	pfn_glVertexAttrib2s = reinterpret_cast<PFNGLVERTEXATTRIB2SPROC>(SDL_GL_GetProcAddress("glVertexAttrib2s"));
	pfn_glBeginTransformFeedback = reinterpret_cast<PFNGLBEGINTRANSFORMFEEDBACKPROC>(SDL_GL_GetProcAddress("glBeginTransformFeedback"));
	pfn_glGetUniformuiv = reinterpret_cast<PFNGLGETUNIFORMUIVPROC>(SDL_GL_GetProcAddress("glGetUniformuiv"));
	pfn_glGetQueryObjectui64v = reinterpret_cast<PFNGLGETQUERYOBJECTUI64VPROC>(SDL_GL_GetProcAddress("glGetQueryObjectui64v"));
	pfn_glUniformMatrix3x2dv = reinterpret_cast<PFNGLUNIFORMMATRIX3X2DVPROC>(SDL_GL_GetProcAddress("glUniformMatrix3x2dv"));
	pfn_glClearTexSubImage = reinterpret_cast<PFNGLCLEARTEXSUBIMAGEPROC>(SDL_GL_GetProcAddress("glClearTexSubImage"));
	pfn_glVertexAttribI2iv = reinterpret_cast<PFNGLVERTEXATTRIBI2IVPROC>(SDL_GL_GetProcAddress("glVertexAttribI2iv"));
	pfn_glGenSamplers = reinterpret_cast<PFNGLGENSAMPLERSPROC>(SDL_GL_GetProcAddress("glGenSamplers"));
	pfn_glUniformMatrix3x2fv = reinterpret_cast<PFNGLUNIFORMMATRIX3X2FVPROC>(SDL_GL_GetProcAddress("glUniformMatrix3x2fv"));
	pfn_glBlendEquationSeparatei = reinterpret_cast<PFNGLBLENDEQUATIONSEPARATEIPROC>(SDL_GL_GetProcAddress("glBlendEquationSeparatei"));
	pfn_glUniformMatrix3x4dv = reinterpret_cast<PFNGLUNIFORMMATRIX3X4DVPROC>(SDL_GL_GetProcAddress("glUniformMatrix3x4dv"));
	pfn_glVertexAttrib2sv = reinterpret_cast<PFNGLVERTEXATTRIB2SVPROC>(SDL_GL_GetProcAddress("glVertexAttrib2sv"));
	pfn_glVertexAttribI2ui = reinterpret_cast<PFNGLVERTEXATTRIBI2UIPROC>(SDL_GL_GetProcAddress("glVertexAttribI2ui"));
	pfn_glVertexBindingDivisor = reinterpret_cast<PFNGLVERTEXBINDINGDIVISORPROC>(SDL_GL_GetProcAddress("glVertexBindingDivisor"));
	pfn_glUniformMatrix3x4fv = reinterpret_cast<PFNGLUNIFORMMATRIX3X4FVPROC>(SDL_GL_GetProcAddress("glUniformMatrix3x4fv"));
	pfn_glTexBuffer = reinterpret_cast<PFNGLTEXBUFFERPROC>(SDL_GL_GetProcAddress("glTexBuffer"));
	pfn_glGetQueryiv = reinterpret_cast<PFNGLGETQUERYIVPROC>(SDL_GL_GetProcAddress("glGetQueryiv"));
	pfn_glGenTextures = reinterpret_cast<PFNGLGENTEXTURESPROC>(SDL_GL_GetProcAddress("glGenTextures"));
	pfn_glBlendEquationi = reinterpret_cast<PFNGLBLENDEQUATIONIPROC>(SDL_GL_GetProcAddress("glBlendEquationi"));
	pfn_glTexSubImage1D = reinterpret_cast<PFNGLTEXSUBIMAGE1DPROC>(SDL_GL_GetProcAddress("glTexSubImage1D"));
	pfn_glBindAttribLocation = reinterpret_cast<PFNGLBINDATTRIBLOCATIONPROC>(SDL_GL_GetProcAddress("glBindAttribLocation"));
	pfn_glUniformMatrix4dv = reinterpret_cast<PFNGLUNIFORMMATRIX4DVPROC>(SDL_GL_GetProcAddress("glUniformMatrix4dv"));
	pfn_glVertexAttribI2uiv = reinterpret_cast<PFNGLVERTEXATTRIBI2UIVPROC>(SDL_GL_GetProcAddress("glVertexAttribI2uiv"));
	pfn_glUniform1uiv = reinterpret_cast<PFNGLUNIFORM1UIVPROC>(SDL_GL_GetProcAddress("glUniform1uiv"));
	pfn_glBindBuffer = reinterpret_cast<PFNGLBINDBUFFERPROC>(SDL_GL_GetProcAddress("glBindBuffer"));
	pfn_glUniformMatrix4fv = reinterpret_cast<PFNGLUNIFORMMATRIX4FVPROC>(SDL_GL_GetProcAddress("glUniformMatrix4fv"));
	pfn_glClientWaitSync = reinterpret_cast<PFNGLCLIENTWAITSYNCPROC>(SDL_GL_GetProcAddress("glClientWaitSync"));
	pfn_glUniform2dv = reinterpret_cast<PFNGLUNIFORM2DVPROC>(SDL_GL_GetProcAddress("glUniform2dv"));
	pfn_glVertexAttrib3d = reinterpret_cast<PFNGLVERTEXATTRIB3DPROC>(SDL_GL_GetProcAddress("glVertexAttrib3d"));
	pfn_glGenTransformFeedbacks = reinterpret_cast<PFNGLGENTRANSFORMFEEDBACKSPROC>(SDL_GL_GetProcAddress("glGenTransformFeedbacks"));
	pfn_glGetRenderbufferParameteriv = reinterpret_cast<PFNGLGETRENDERBUFFERPARAMETERIVPROC>(SDL_GL_GetProcAddress("glGetRenderbufferParameteriv"));
	pfn_glUniformMatrix4x2dv = reinterpret_cast<PFNGLUNIFORMMATRIX4X2DVPROC>(SDL_GL_GetProcAddress("glUniformMatrix4x2dv"));
	pfn_glVertexAttribI3i = reinterpret_cast<PFNGLVERTEXATTRIBI3IPROC>(SDL_GL_GetProcAddress("glVertexAttribI3i"));
	pfn_glClipControl = reinterpret_cast<PFNGLCLIPCONTROLPROC>(SDL_GL_GetProcAddress("glClipControl"));
	pfn_glGetVertexArrayIndexed64iv = reinterpret_cast<PFNGLGETVERTEXARRAYINDEXED64IVPROC>(SDL_GL_GetProcAddress("glGetVertexArrayIndexed64iv"));
	pfn_glTexSubImage2D = reinterpret_cast<PFNGLTEXSUBIMAGE2DPROC>(SDL_GL_GetProcAddress("glTexSubImage2D"));
	pfn_glUniformMatrix4x2fv = reinterpret_cast<PFNGLUNIFORMMATRIX4X2FVPROC>(SDL_GL_GetProcAddress("glUniformMatrix4x2fv"));
	pfn_glUniform2d = reinterpret_cast<PFNGLUNIFORM2DPROC>(SDL_GL_GetProcAddress("glUniform2d"));
	pfn_glTexBufferRange = reinterpret_cast<PFNGLTEXBUFFERRANGEPROC>(SDL_GL_GetProcAddress("glTexBufferRange"));
	pfn_glTexSubImage3D = reinterpret_cast<PFNGLTEXSUBIMAGE3DPROC>(SDL_GL_GetProcAddress("glTexSubImage3D"));
	pfn_glVertexP2uiv = reinterpret_cast<PFNGLVERTEXP2UIVPROC>(SDL_GL_GetProcAddress("glVertexP2uiv"));
	pfn_glBlendFunc = reinterpret_cast<PFNGLBLENDFUNCPROC>(SDL_GL_GetProcAddress("glBlendFunc"));
	pfn_glBindBufferBase = reinterpret_cast<PFNGLBINDBUFFERBASEPROC>(SDL_GL_GetProcAddress("glBindBufferBase"));
	pfn_glGenVertexArrays = reinterpret_cast<PFNGLGENVERTEXARRAYSPROC>(SDL_GL_GetProcAddress("glGenVertexArrays"));
	pfn_glVertexP2ui = reinterpret_cast<PFNGLVERTEXP2UIPROC>(SDL_GL_GetProcAddress("glVertexP2ui"));
	pfn_glGetSamplerParameterIiv = reinterpret_cast<PFNGLGETSAMPLERPARAMETERIIVPROC>(SDL_GL_GetProcAddress("glGetSamplerParameterIiv"));
	pfn_glUniformMatrix4x3dv = reinterpret_cast<PFNGLUNIFORMMATRIX4X3DVPROC>(SDL_GL_GetProcAddress("glUniformMatrix4x3dv"));
	pfn_glUniform2f = reinterpret_cast<PFNGLUNIFORM2FPROC>(SDL_GL_GetProcAddress("glUniform2f"));
	pfn_glVertexAttrib3dv = reinterpret_cast<PFNGLVERTEXATTRIB3DVPROC>(SDL_GL_GetProcAddress("glVertexAttrib3dv"));
	pfn_glUniformMatrix4x3fv = reinterpret_cast<PFNGLUNIFORMMATRIX4X3FVPROC>(SDL_GL_GetProcAddress("glUniformMatrix4x3fv"));
	pfn_glVertexAttribI3iv = reinterpret_cast<PFNGLVERTEXATTRIBI3IVPROC>(SDL_GL_GetProcAddress("glVertexAttribI3iv"));
	pfn_glTextureBarrier = reinterpret_cast<PFNGLTEXTUREBARRIERPROC>(SDL_GL_GetProcAddress("glTextureBarrier"));
	pfn_glGetVertexArrayIndexediv = reinterpret_cast<PFNGLGETVERTEXARRAYINDEXEDIVPROC>(SDL_GL_GetProcAddress("glGetVertexArrayIndexediv"));
	pfn_glBlendFuncSeparate = reinterpret_cast<PFNGLBLENDFUNCSEPARATEPROC>(SDL_GL_GetProcAddress("glBlendFuncSeparate"));
	pfn_glVertexAttribI3ui = reinterpret_cast<PFNGLVERTEXATTRIBI3UIPROC>(SDL_GL_GetProcAddress("glVertexAttribI3ui"));
	pfn_glGetSamplerParameterIuiv = reinterpret_cast<PFNGLGETSAMPLERPARAMETERIUIVPROC>(SDL_GL_GetProcAddress("glGetSamplerParameterIuiv"));
	pfn_glVertexP3ui = reinterpret_cast<PFNGLVERTEXP3UIPROC>(SDL_GL_GetProcAddress("glVertexP3ui"));
	pfn_glUniformSubroutinesuiv = reinterpret_cast<PFNGLUNIFORMSUBROUTINESUIVPROC>(SDL_GL_GetProcAddress("glUniformSubroutinesuiv"));
	pfn_glUniform2fv = reinterpret_cast<PFNGLUNIFORM2FVPROC>(SDL_GL_GetProcAddress("glUniform2fv"));
	pfn_glVertexP3uiv = reinterpret_cast<PFNGLVERTEXP3UIVPROC>(SDL_GL_GetProcAddress("glVertexP3uiv"));
	pfn_glVertexAttrib3f = reinterpret_cast<PFNGLVERTEXATTRIB3FPROC>(SDL_GL_GetProcAddress("glVertexAttrib3f"));
	pfn_glBindBufferRange = reinterpret_cast<PFNGLBINDBUFFERRANGEPROC>(SDL_GL_GetProcAddress("glBindBufferRange"));
	pfn_glVertexAttribI3uiv = reinterpret_cast<PFNGLVERTEXATTRIBI3UIVPROC>(SDL_GL_GetProcAddress("glVertexAttribI3uiv"));
	pfn_glGenerateMipmap = reinterpret_cast<PFNGLGENERATEMIPMAPPROC>(SDL_GL_GetProcAddress("glGenerateMipmap"));
	pfn_glGetSamplerParameterfv = reinterpret_cast<PFNGLGETSAMPLERPARAMETERFVPROC>(SDL_GL_GetProcAddress("glGetSamplerParameterfv"));
	pfn_glPrimitiveRestartIndex = reinterpret_cast<PFNGLPRIMITIVERESTARTINDEXPROC>(SDL_GL_GetProcAddress("glPrimitiveRestartIndex"));
	pfn_glBindFragDataLocationIndexed = reinterpret_cast<PFNGLBINDFRAGDATALOCATIONINDEXEDPROC>(SDL_GL_GetProcAddress("glBindFragDataLocationIndexed"));
	pfn_glUniform2i = reinterpret_cast<PFNGLUNIFORM2IPROC>(SDL_GL_GetProcAddress("glUniform2i"));
	pfn_glGetSamplerParameteriv = reinterpret_cast<PFNGLGETSAMPLERPARAMETERIVPROC>(SDL_GL_GetProcAddress("glGetSamplerParameteriv"));
	pfn_glVertexP4ui = reinterpret_cast<PFNGLVERTEXP4UIPROC>(SDL_GL_GetProcAddress("glVertexP4ui"));
	pfn_glTextureBuffer = reinterpret_cast<PFNGLTEXTUREBUFFERPROC>(SDL_GL_GetProcAddress("glTextureBuffer"));
	pfn_glGetVertexArrayiv = reinterpret_cast<PFNGLGETVERTEXARRAYIVPROC>(SDL_GL_GetProcAddress("glGetVertexArrayiv"));
	pfn_glGetVertexAttribIiv = reinterpret_cast<PFNGLGETVERTEXATTRIBIIVPROC>(SDL_GL_GetProcAddress("glGetVertexAttribIiv"));
	pfn_glVertexAttribI4bv = reinterpret_cast<PFNGLVERTEXATTRIBI4BVPROC>(SDL_GL_GetProcAddress("glVertexAttribI4bv"));
	pfn_glBindFragDataLocation = reinterpret_cast<PFNGLBINDFRAGDATALOCATIONPROC>(SDL_GL_GetProcAddress("glBindFragDataLocation"));
	pfn_glBlendFuncSeparatei = reinterpret_cast<PFNGLBLENDFUNCSEPARATEIPROC>(SDL_GL_GetProcAddress("glBlendFuncSeparatei"));
	pfn_glVertexP4uiv = reinterpret_cast<PFNGLVERTEXP4UIVPROC>(SDL_GL_GetProcAddress("glVertexP4uiv"));
	pfn_glUnmapBuffer = reinterpret_cast<PFNGLUNMAPBUFFERPROC>(SDL_GL_GetProcAddress("glUnmapBuffer"));
	pfn_glVertexAttrib3fv = reinterpret_cast<PFNGLVERTEXATTRIB3FVPROC>(SDL_GL_GetProcAddress("glVertexAttrib3fv"));
	pfn_glBindBuffersRange = reinterpret_cast<PFNGLBINDBUFFERSRANGEPROC>(SDL_GL_GetProcAddress("glBindBuffersRange"));
	pfn_glTextureBufferRange = reinterpret_cast<PFNGLTEXTUREBUFFERRANGEPROC>(SDL_GL_GetProcAddress("glTextureBufferRange"));
	pfn_glVertexAttribI4i = reinterpret_cast<PFNGLVERTEXATTRIBI4IPROC>(SDL_GL_GetProcAddress("glVertexAttribI4i"));
	pfn_glTexCoordP1ui = reinterpret_cast<PFNGLTEXCOORDP1UIPROC>(SDL_GL_GetProcAddress("glTexCoordP1ui"));
	pfn_glBindBuffersBase = reinterpret_cast<PFNGLBINDBUFFERSBASEPROC>(SDL_GL_GetProcAddress("glBindBuffersBase"));
	pfn_glGetVertexAttribIuiv = reinterpret_cast<PFNGLGETVERTEXATTRIBIUIVPROC>(SDL_GL_GetProcAddress("glGetVertexAttribIuiv"));
	pfn_glProgramBinary = reinterpret_cast<PFNGLPROGRAMBINARYPROC>(SDL_GL_GetProcAddress("glProgramBinary"));
	pfn_glGetShaderSource = reinterpret_cast<PFNGLGETSHADERSOURCEPROC>(SDL_GL_GetProcAddress("glGetShaderSource"));
	pfn_glTexCoordP1uiv = reinterpret_cast<PFNGLTEXCOORDP1UIVPROC>(SDL_GL_GetProcAddress("glTexCoordP1uiv"));
	pfn_glGetShaderPrecisionFormat = reinterpret_cast<PFNGLGETSHADERPRECISIONFORMATPROC>(SDL_GL_GetProcAddress("glGetShaderPrecisionFormat"));
	pfn_glCompileShader = reinterpret_cast<PFNGLCOMPILESHADERPROC>(SDL_GL_GetProcAddress("glCompileShader"));
	pfn_glGetVertexAttribLdv = reinterpret_cast<PFNGLGETVERTEXATTRIBLDVPROC>(SDL_GL_GetProcAddress("glGetVertexAttribLdv"));
	pfn_glGenerateTextureMipmap = reinterpret_cast<PFNGLGENERATETEXTUREMIPMAPPROC>(SDL_GL_GetProcAddress("glGenerateTextureMipmap"));
	pfn_glBindFramebuffer = reinterpret_cast<PFNGLBINDFRAMEBUFFERPROC>(SDL_GL_GetProcAddress("glBindFramebuffer"));
	pfn_glGetShaderInfoLog = reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>(SDL_GL_GetProcAddress("glGetShaderInfoLog"));
	pfn_glTexCoordP2ui = reinterpret_cast<PFNGLTEXCOORDP2UIPROC>(SDL_GL_GetProcAddress("glTexCoordP2ui"));
	pfn_glBlendFunci = reinterpret_cast<PFNGLBLENDFUNCIPROC>(SDL_GL_GetProcAddress("glBlendFunci"));
	pfn_glGetShaderiv = reinterpret_cast<PFNGLGETSHADERIVPROC>(SDL_GL_GetProcAddress("glGetShaderiv"));
	pfn_glUniform2iv = reinterpret_cast<PFNGLUNIFORM2IVPROC>(SDL_GL_GetProcAddress("glUniform2iv"));
	pfn_glUnmapNamedBuffer = reinterpret_cast<PFNGLUNMAPNAMEDBUFFERPROC>(SDL_GL_GetProcAddress("glUnmapNamedBuffer"));
	pfn_glVertexAttrib3s = reinterpret_cast<PFNGLVERTEXATTRIB3SPROC>(SDL_GL_GetProcAddress("glVertexAttrib3s"));
	pfn_glVertexAttribI4sv = reinterpret_cast<PFNGLVERTEXATTRIBI4SVPROC>(SDL_GL_GetProcAddress("glVertexAttribI4sv"));
	pfn_glPauseTransformFeedback = reinterpret_cast<PFNGLPAUSETRANSFORMFEEDBACKPROC>(SDL_GL_GetProcAddress("glPauseTransformFeedback"));
	pfn_glVertexAttribI4iv = reinterpret_cast<PFNGLVERTEXATTRIBI4IVPROC>(SDL_GL_GetProcAddress("glVertexAttribI4iv"));
	pfn_glTexCoordP2uiv = reinterpret_cast<PFNGLTEXCOORDP2UIVPROC>(SDL_GL_GetProcAddress("glTexCoordP2uiv"));
	pfn_glGetActiveAtomicCounterBufferiv = reinterpret_cast<PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC>(SDL_GL_GetProcAddress("glGetActiveAtomicCounterBufferiv"));
	pfn_glGetActiveAttrib = reinterpret_cast<PFNGLGETACTIVEATTRIBPROC>(SDL_GL_GetProcAddress("glGetActiveAttrib"));
	pfn_glGetVertexAttribPointerv = reinterpret_cast<PFNGLGETVERTEXATTRIBPOINTERVPROC>(SDL_GL_GetProcAddress("glGetVertexAttribPointerv"));
	pfn_glUniform2ui = reinterpret_cast<PFNGLUNIFORM2UIPROC>(SDL_GL_GetProcAddress("glUniform2ui"));
	pfn_glTexCoordP3ui = reinterpret_cast<PFNGLTEXCOORDP3UIPROC>(SDL_GL_GetProcAddress("glTexCoordP3ui"));
	pfn_glGetActiveSubroutineName = reinterpret_cast<PFNGLGETACTIVESUBROUTINENAMEPROC>(SDL_GL_GetProcAddress("glGetActiveSubroutineName"));
	pfn_glVertexAttribI4ubv = reinterpret_cast<PFNGLVERTEXATTRIBI4UBVPROC>(SDL_GL_GetProcAddress("glVertexAttribI4ubv"));
	pfn_glVertexAttrib3sv = reinterpret_cast<PFNGLVERTEXATTRIB3SVPROC>(SDL_GL_GetProcAddress("glVertexAttrib3sv"));
	pfn_glBindImageTexture = reinterpret_cast<PFNGLBINDIMAGETEXTUREPROC>(SDL_GL_GetProcAddress("glBindImageTexture"));
	pfn_glGetVertexAttribdv = reinterpret_cast<PFNGLGETVERTEXATTRIBDVPROC>(SDL_GL_GetProcAddress("glGetVertexAttribdv"));
	pfn_glBlitFramebuffer = reinterpret_cast<PFNGLBLITFRAMEBUFFERPROC>(SDL_GL_GetProcAddress("glBlitFramebuffer"));
	pfn_glGetActiveUniformBlockName = reinterpret_cast<PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC>(SDL_GL_GetProcAddress("glGetActiveUniformBlockName"));
	pfn_glTexCoordP3uiv = reinterpret_cast<PFNGLTEXCOORDP3UIVPROC>(SDL_GL_GetProcAddress("glTexCoordP3uiv"));
	pfn_glBindImageTextures = reinterpret_cast<PFNGLBINDIMAGETEXTURESPROC>(SDL_GL_GetProcAddress("glBindImageTextures"));
	pfn_glGetString = reinterpret_cast<PFNGLGETSTRINGPROC>(SDL_GL_GetProcAddress("glGetString"));
	pfn_glGetActiveUniformName = reinterpret_cast<PFNGLGETACTIVEUNIFORMNAMEPROC>(SDL_GL_GetProcAddress("glGetActiveUniformName"));
	pfn_glVertexAttribI4ui = reinterpret_cast<PFNGLVERTEXATTRIBI4UIPROC>(SDL_GL_GetProcAddress("glVertexAttribI4ui"));
	pfn_glCompressedTexImage1D = reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE1DPROC>(SDL_GL_GetProcAddress("glCompressedTexImage1D"));
	pfn_glTexCoordP4ui = reinterpret_cast<PFNGLTEXCOORDP4UIPROC>(SDL_GL_GetProcAddress("glTexCoordP4ui"));
	pfn_glGetVertexAttribfv = reinterpret_cast<PFNGLGETVERTEXATTRIBFVPROC>(SDL_GL_GetProcAddress("glGetVertexAttribfv"));
	pfn_glGetStringi = reinterpret_cast<PFNGLGETSTRINGIPROC>(SDL_GL_GetProcAddress("glGetStringi"));
	pfn_glGetActiveSubroutineUniformName = reinterpret_cast<PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC>(SDL_GL_GetProcAddress("glGetActiveSubroutineUniformName"));
	pfn_glVertexAttrib4Nbv = reinterpret_cast<PFNGLVERTEXATTRIB4NBVPROC>(SDL_GL_GetProcAddress("glVertexAttrib4Nbv"));
	pfn_glCompressedTexImage2D = reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE2DPROC>(SDL_GL_GetProcAddress("glCompressedTexImage2D"));
	pfn_glTexCoordP4uiv = reinterpret_cast<PFNGLTEXCOORDP4UIVPROC>(SDL_GL_GetProcAddress("glTexCoordP4uiv"));
	pfn_glGetActiveSubroutineUniformiv = reinterpret_cast<PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC>(SDL_GL_GetProcAddress("glGetActiveSubroutineUniformiv"));
	pfn_glBufferData = reinterpret_cast<PFNGLBUFFERDATAPROC>(SDL_GL_GetProcAddress("glBufferData"));
	pfn_glGetActiveUniform = reinterpret_cast<PFNGLGETACTIVEUNIFORMPROC>(SDL_GL_GetProcAddress("glGetActiveUniform"));
	pfn_glUseProgram = reinterpret_cast<PFNGLUSEPROGRAMPROC>(SDL_GL_GetProcAddress("glUseProgram"));
	pfn_glBlitNamedFramebuffer = reinterpret_cast<PFNGLBLITNAMEDFRAMEBUFFERPROC>(SDL_GL_GetProcAddress("glBlitNamedFramebuffer"));
	pfn_glGetSubroutineIndex = reinterpret_cast<PFNGLGETSUBROUTINEINDEXPROC>(SDL_GL_GetProcAddress("glGetSubroutineIndex"));
	pfn_glPixelStoref = reinterpret_cast<PFNGLPIXELSTOREFPROC>(SDL_GL_GetProcAddress("glPixelStoref"));
	pfn_glGetVertexAttribiv = reinterpret_cast<PFNGLGETVERTEXATTRIBIVPROC>(SDL_GL_GetProcAddress("glGetVertexAttribiv"));
	pfn_glUniform3dv = reinterpret_cast<PFNGLUNIFORM3DVPROC>(SDL_GL_GetProcAddress("glUniform3dv"));
	pfn_glVertexAttrib4Niv = reinterpret_cast<PFNGLVERTEXATTRIB4NIVPROC>(SDL_GL_GetProcAddress("glVertexAttrib4Niv"));
	pfn_glVertexAttribI4usv = reinterpret_cast<PFNGLVERTEXATTRIBI4USVPROC>(SDL_GL_GetProcAddress("glVertexAttribI4usv"));
	pfn_glUniform2uiv = reinterpret_cast<PFNGLUNIFORM2UIVPROC>(SDL_GL_GetProcAddress("glUniform2uiv"));
	pfn_glGetActiveUniformBlockiv = reinterpret_cast<PFNGLGETACTIVEUNIFORMBLOCKIVPROC>(SDL_GL_GetProcAddress("glGetActiveUniformBlockiv"));
	pfn_glVertexAttribI4uiv = reinterpret_cast<PFNGLVERTEXATTRIBI4UIVPROC>(SDL_GL_GetProcAddress("glVertexAttribI4uiv"));
	pfn_glGetSubroutineUniformLocation = reinterpret_cast<PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC>(SDL_GL_GetProcAddress("glGetSubroutineUniformLocation"));
	pfn_glPixelStorei = reinterpret_cast<PFNGLPIXELSTOREIPROC>(SDL_GL_GetProcAddress("glPixelStorei"));
	pfn_glUseProgramStages = reinterpret_cast<PFNGLUSEPROGRAMSTAGESPROC>(SDL_GL_GetProcAddress("glUseProgramStages"));
	pfn_glTextureParameterfv = reinterpret_cast<PFNGLTEXTUREPARAMETERFVPROC>(SDL_GL_GetProcAddress("glTextureParameterfv"));
	pfn_glGetSynciv = reinterpret_cast<PFNGLGETSYNCIVPROC>(SDL_GL_GetProcAddress("glGetSynciv"));
	pfn_glTextureParameterIiv = reinterpret_cast<PFNGLTEXTUREPARAMETERIIVPROC>(SDL_GL_GetProcAddress("glTextureParameterIiv"));
	pfn_glGetActiveUniformsiv = reinterpret_cast<PFNGLGETACTIVEUNIFORMSIVPROC>(SDL_GL_GetProcAddress("glGetActiveUniformsiv"));
	pfn_glFramebufferParameteri = reinterpret_cast<PFNGLFRAMEBUFFERPARAMETERIPROC>(SDL_GL_GetProcAddress("glFramebufferParameteri"));
	pfn_glVertexAttrib4Nsv = reinterpret_cast<PFNGLVERTEXATTRIB4NSVPROC>(SDL_GL_GetProcAddress("glVertexAttrib4Nsv"));
	pfn_glUniform3d = reinterpret_cast<PFNGLUNIFORM3DPROC>(SDL_GL_GetProcAddress("glUniform3d"));
	pfn_glVertexAttribIFormat = reinterpret_cast<PFNGLVERTEXATTRIBIFORMATPROC>(SDL_GL_GetProcAddress("glVertexAttribIFormat"));
	pfn_glCompressedTexSubImage1D = reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC>(SDL_GL_GetProcAddress("glCompressedTexSubImage1D"));
	pfn_glTextureParameterIuiv = reinterpret_cast<PFNGLTEXTUREPARAMETERIUIVPROC>(SDL_GL_GetProcAddress("glTextureParameterIuiv"));
	pfn_glFramebufferRenderbuffer = reinterpret_cast<PFNGLFRAMEBUFFERRENDERBUFFERPROC>(SDL_GL_GetProcAddress("glFramebufferRenderbuffer"));
	pfn_glGetAttachedShaders = reinterpret_cast<PFNGLGETATTACHEDSHADERSPROC>(SDL_GL_GetProcAddress("glGetAttachedShaders"));
	pfn_glBindProgramPipeline = reinterpret_cast<PFNGLBINDPROGRAMPIPELINEPROC>(SDL_GL_GetProcAddress("glBindProgramPipeline"));
	pfn_glVertexAttribIPointer = reinterpret_cast<PFNGLVERTEXATTRIBIPOINTERPROC>(SDL_GL_GetProcAddress("glVertexAttribIPointer"));
	pfn_glTextureParameterf = reinterpret_cast<PFNGLTEXTUREPARAMETERFPROC>(SDL_GL_GetProcAddress("glTextureParameterf"));
	pfn_glUniform3f = reinterpret_cast<PFNGLUNIFORM3FPROC>(SDL_GL_GetProcAddress("glUniform3f"));
	pfn_glVertexAttrib4Nub = reinterpret_cast<PFNGLVERTEXATTRIB4NUBPROC>(SDL_GL_GetProcAddress("glVertexAttrib4Nub"));
	pfn_glCompressedTexImage3D = reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE3DPROC>(SDL_GL_GetProcAddress("glCompressedTexImage3D"));
	pfn_glGetAttribLocation = reinterpret_cast<PFNGLGETATTRIBLOCATIONPROC>(SDL_GL_GetProcAddress("glGetAttribLocation"));
	pfn_glUniform3fv = reinterpret_cast<PFNGLUNIFORM3FVPROC>(SDL_GL_GetProcAddress("glUniform3fv"));
	pfn_glBindRenderbuffer = reinterpret_cast<PFNGLBINDRENDERBUFFERPROC>(SDL_GL_GetProcAddress("glBindRenderbuffer"));
	pfn_glBufferStorage = reinterpret_cast<PFNGLBUFFERSTORAGEPROC>(SDL_GL_GetProcAddress("glBufferStorage"));
	pfn_glTextureParameteri = reinterpret_cast<PFNGLTEXTUREPARAMETERIPROC>(SDL_GL_GetProcAddress("glTextureParameteri"));
	pfn_glVertexAttribL1d = reinterpret_cast<PFNGLVERTEXATTRIBL1DPROC>(SDL_GL_GetProcAddress("glVertexAttribL1d"));
	pfn_glGetBooleani_v = reinterpret_cast<PFNGLGETBOOLEANI_VPROC>(SDL_GL_GetProcAddress("glGetBooleani_v"));
	pfn_glVertexAttribL1dv = reinterpret_cast<PFNGLVERTEXATTRIBL1DVPROC>(SDL_GL_GetProcAddress("glVertexAttribL1dv"));
	pfn_glTextureParameteriv = reinterpret_cast<PFNGLTEXTUREPARAMETERIVPROC>(SDL_GL_GetProcAddress("glTextureParameteriv"));
	pfn_glVertexAttrib4Nuiv = reinterpret_cast<PFNGLVERTEXATTRIB4NUIVPROC>(SDL_GL_GetProcAddress("glVertexAttrib4Nuiv"));
	pfn_glVertexAttrib4Nubv = reinterpret_cast<PFNGLVERTEXATTRIB4NUBVPROC>(SDL_GL_GetProcAddress("glVertexAttrib4Nubv"));
	pfn_glBindSampler = reinterpret_cast<PFNGLBINDSAMPLERPROC>(SDL_GL_GetProcAddress("glBindSampler"));
	pfn_glGetBooleanv = reinterpret_cast<PFNGLGETBOOLEANVPROC>(SDL_GL_GetProcAddress("glGetBooleanv"));
	pfn_glCompressedTexSubImage3D = reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC>(SDL_GL_GetProcAddress("glCompressedTexSubImage3D"));
	pfn_glUniform3i = reinterpret_cast<PFNGLUNIFORM3IPROC>(SDL_GL_GetProcAddress("glUniform3i"));
	pfn_glFramebufferTexture1D = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE1DPROC>(SDL_GL_GetProcAddress("glFramebufferTexture1D"));
	pfn_glCompressedTexSubImage2D = reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC>(SDL_GL_GetProcAddress("glCompressedTexSubImage2D"));
	pfn_glFramebufferTexture = reinterpret_cast<PFNGLFRAMEBUFFERTEXTUREPROC>(SDL_GL_GetProcAddress("glFramebufferTexture"));
	pfn_glBindSamplers = reinterpret_cast<PFNGLBINDSAMPLERSPROC>(SDL_GL_GetProcAddress("glBindSamplers"));
	pfn_glGetBufferParameteri64v = reinterpret_cast<PFNGLGETBUFFERPARAMETERI64VPROC>(SDL_GL_GetProcAddress("glGetBufferParameteri64v"));
	pfn_glGetnColorTable = reinterpret_cast<PFNGLGETNCOLORTABLEPROC>(SDL_GL_GetProcAddress("glGetnColorTable"));
	pfn_glBufferSubData = reinterpret_cast<PFNGLBUFFERSUBDATAPROC>(SDL_GL_GetProcAddress("glBufferSubData"));
	pfn_glVertexAttrib4Nusv = reinterpret_cast<PFNGLVERTEXATTRIB4NUSVPROC>(SDL_GL_GetProcAddress("glVertexAttrib4Nusv"));
	pfn_glFenceSync = reinterpret_cast<PFNGLFENCESYNCPROC>(SDL_GL_GetProcAddress("glFenceSync"));
	pfn_glGetBufferParameteriv = reinterpret_cast<PFNGLGETBUFFERPARAMETERIVPROC>(SDL_GL_GetProcAddress("glGetBufferParameteriv"));
	pfn_glTextureStorage1D = reinterpret_cast<PFNGLTEXTURESTORAGE1DPROC>(SDL_GL_GetProcAddress("glTextureStorage1D"));
	pfn_glCompressedTextureSubImage1D = reinterpret_cast<PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC>(SDL_GL_GetProcAddress("glCompressedTextureSubImage1D"));
	pfn_glFramebufferTexture2D = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE2DPROC>(SDL_GL_GetProcAddress("glFramebufferTexture2D"));
	pfn_glVertexAttrib4bv = reinterpret_cast<PFNGLVERTEXATTRIB4BVPROC>(SDL_GL_GetProcAddress("glVertexAttrib4bv"));
	pfn_glBindTexture = reinterpret_cast<PFNGLBINDTEXTUREPROC>(SDL_GL_GetProcAddress("glBindTexture"));
	pfn_glValidateProgram = reinterpret_cast<PFNGLVALIDATEPROGRAMPROC>(SDL_GL_GetProcAddress("glValidateProgram"));
	pfn_glGetBufferPointerv = reinterpret_cast<PFNGLGETBUFFERPOINTERVPROC>(SDL_GL_GetProcAddress("glGetBufferPointerv"));
	pfn_glGetnConvolutionFilter = reinterpret_cast<PFNGLGETNCONVOLUTIONFILTERPROC>(SDL_GL_GetProcAddress("glGetnConvolutionFilter"));
	pfn_glGetnCompressedTexImage = reinterpret_cast<PFNGLGETNCOMPRESSEDTEXIMAGEPROC>(SDL_GL_GetProcAddress("glGetnCompressedTexImage"));
	pfn_glActiveShaderProgram = reinterpret_cast<PFNGLACTIVESHADERPROGRAMPROC>(SDL_GL_GetProcAddress("glActiveShaderProgram"));
	pfn_glFinish = reinterpret_cast<PFNGLFINISHPROC>(SDL_GL_GetProcAddress("glFinish"));
	pfn_glGetBufferSubData = reinterpret_cast<PFNGLGETBUFFERSUBDATAPROC>(SDL_GL_GetProcAddress("glGetBufferSubData"));
	pfn_glInvalidateBufferSubData = reinterpret_cast<PFNGLINVALIDATEBUFFERSUBDATAPROC>(SDL_GL_GetProcAddress("glInvalidateBufferSubData"));
	pfn_glTextureStorage2D = reinterpret_cast<PFNGLTEXTURESTORAGE2DPROC>(SDL_GL_GetProcAddress("glTextureStorage2D"));
	pfn_glVertexAttrib4d = reinterpret_cast<PFNGLVERTEXATTRIB4DPROC>(SDL_GL_GetProcAddress("glVertexAttrib4d"));
	pfn_glProgramParameteri = reinterpret_cast<PFNGLPROGRAMPARAMETERIPROC>(SDL_GL_GetProcAddress("glProgramParameteri"));
	pfn_glBindTextureUnit = reinterpret_cast<PFNGLBINDTEXTUREUNITPROC>(SDL_GL_GetProcAddress("glBindTextureUnit"));
	pfn_glUniform3iv = reinterpret_cast<PFNGLUNIFORM3IVPROC>(SDL_GL_GetProcAddress("glUniform3iv"));
	pfn_glValidateProgramPipeline = reinterpret_cast<PFNGLVALIDATEPROGRAMPIPELINEPROC>(SDL_GL_GetProcAddress("glValidateProgramPipeline"));
	pfn_glInvalidateBufferData = reinterpret_cast<PFNGLINVALIDATEBUFFERDATAPROC>(SDL_GL_GetProcAddress("glInvalidateBufferData"));
	pfn_glCheckFramebufferStatus = reinterpret_cast<PFNGLCHECKFRAMEBUFFERSTATUSPROC>(SDL_GL_GetProcAddress("glCheckFramebufferStatus"));
	pfn_glFramebufferTexture3D = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE3DPROC>(SDL_GL_GetProcAddress("glFramebufferTexture3D"));
	pfn_glTextureStorage2DMultisample = reinterpret_cast<PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC>(SDL_GL_GetProcAddress("glTextureStorage2DMultisample"));
	pfn_glCompressedTextureSubImage3D = reinterpret_cast<PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC>(SDL_GL_GetProcAddress("glCompressedTextureSubImage3D"));
	pfn_glVertexAttribL2d = reinterpret_cast<PFNGLVERTEXATTRIBL2DPROC>(SDL_GL_GetProcAddress("glVertexAttribL2d"));
	pfn_glCompressedTextureSubImage2D = reinterpret_cast<PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC>(SDL_GL_GetProcAddress("glCompressedTextureSubImage2D"));
	pfn_glActiveTexture = reinterpret_cast<PFNGLACTIVETEXTUREPROC>(SDL_GL_GetProcAddress("glActiveTexture"));
	pfn_glGetnHistogram = reinterpret_cast<PFNGLGETNHISTOGRAMPROC>(SDL_GL_GetProcAddress("glGetnHistogram"));
	pfn_glMultiTexCoordP1uiv = reinterpret_cast<PFNGLMULTITEXCOORDP1UIVPROC>(SDL_GL_GetProcAddress("glMultiTexCoordP1uiv"));
	pfn_glBindTextures = reinterpret_cast<PFNGLBINDTEXTURESPROC>(SDL_GL_GetProcAddress("glBindTextures"));
	pfn_glGetTexImage = reinterpret_cast<PFNGLGETTEXIMAGEPROC>(SDL_GL_GetProcAddress("glGetTexImage"));
	pfn_glUniform3ui = reinterpret_cast<PFNGLUNIFORM3UIPROC>(SDL_GL_GetProcAddress("glUniform3ui"));
	pfn_glTextureStorage3D = reinterpret_cast<PFNGLTEXTURESTORAGE3DPROC>(SDL_GL_GetProcAddress("glTextureStorage3D"));
	pfn_glMultiTexCoordP2uiv = reinterpret_cast<PFNGLMULTITEXCOORDP2UIVPROC>(SDL_GL_GetProcAddress("glMultiTexCoordP2uiv"));
	pfn_glInvalidateFramebuffer = reinterpret_cast<PFNGLINVALIDATEFRAMEBUFFERPROC>(SDL_GL_GetProcAddress("glInvalidateFramebuffer"));
	pfn_glBindTransformFeedback = reinterpret_cast<PFNGLBINDTRANSFORMFEEDBACKPROC>(SDL_GL_GetProcAddress("glBindTransformFeedback"));
	pfn_glInvalidateNamedFramebufferData = reinterpret_cast<PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC>(SDL_GL_GetProcAddress("glInvalidateNamedFramebufferData"));
	pfn_glGetnMapdv = reinterpret_cast<PFNGLGETNMAPDVPROC>(SDL_GL_GetProcAddress("glGetnMapdv"));
	pfn_glMultiTexCoordP1ui = reinterpret_cast<PFNGLMULTITEXCOORDP1UIPROC>(SDL_GL_GetProcAddress("glMultiTexCoordP1ui"));
	pfn_glVertexAttribL2dv = reinterpret_cast<PFNGLVERTEXATTRIBL2DVPROC>(SDL_GL_GetProcAddress("glVertexAttribL2dv"));
	pfn_glTextureStorage3DMultisample = reinterpret_cast<PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC>(SDL_GL_GetProcAddress("glTextureStorage3DMultisample"));
	pfn_glGetnMapfv = reinterpret_cast<PFNGLGETNMAPFVPROC>(SDL_GL_GetProcAddress("glGetnMapfv"));
	pfn_glGetTexLevelParameteriv = reinterpret_cast<PFNGLGETTEXLEVELPARAMETERIVPROC>(SDL_GL_GetProcAddress("glGetTexLevelParameteriv"));
	pfn_glMultiTexCoordP2ui = reinterpret_cast<PFNGLMULTITEXCOORDP2UIPROC>(SDL_GL_GetProcAddress("glMultiTexCoordP2ui"));
	pfn_glProgramUniform1d = reinterpret_cast<PFNGLPROGRAMUNIFORM1DPROC>(SDL_GL_GetProcAddress("glProgramUniform1d"));
	pfn_glInvalidateNamedFramebufferSubData = reinterpret_cast<PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC>(SDL_GL_GetProcAddress("glInvalidateNamedFramebufferSubData"));
	pfn_glIsBuffer = reinterpret_cast<PFNGLISBUFFERPROC>(SDL_GL_GetProcAddress("glIsBuffer"));
	pfn_glVertexAttrib4dv = reinterpret_cast<PFNGLVERTEXATTRIB4DVPROC>(SDL_GL_GetProcAddress("glVertexAttrib4dv"));
	pfn_glGetTexParameterIiv = reinterpret_cast<PFNGLGETTEXPARAMETERIIVPROC>(SDL_GL_GetProcAddress("glGetTexParameterIiv"));
	pfn_glCheckNamedFramebufferStatus = reinterpret_cast<PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC>(SDL_GL_GetProcAddress("glCheckNamedFramebufferStatus"));
	pfn_glBindVertexArray = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>(SDL_GL_GetProcAddress("glBindVertexArray"));
	pfn_glGetTexLevelParameterfv = reinterpret_cast<PFNGLGETTEXLEVELPARAMETERFVPROC>(SDL_GL_GetProcAddress("glGetTexLevelParameterfv"));
	pfn_glInvalidateTexSubImage = reinterpret_cast<PFNGLINVALIDATETEXSUBIMAGEPROC>(SDL_GL_GetProcAddress("glInvalidateTexSubImage"));
	pfn_glGetnMapiv = reinterpret_cast<PFNGLGETNMAPIVPROC>(SDL_GL_GetProcAddress("glGetnMapiv"));
	pfn_glVertexAttrib4f = reinterpret_cast<PFNGLVERTEXATTRIB4FPROC>(SDL_GL_GetProcAddress("glVertexAttrib4f"));
	pfn_glMultiTexCoordP3ui = reinterpret_cast<PFNGLMULTITEXCOORDP3UIPROC>(SDL_GL_GetProcAddress("glMultiTexCoordP3ui"));
	pfn_glProgramUniform1dv = reinterpret_cast<PFNGLPROGRAMUNIFORM1DVPROC>(SDL_GL_GetProcAddress("glProgramUniform1dv"));
	pfn_glInvalidateSubFramebuffer = reinterpret_cast<PFNGLINVALIDATESUBFRAMEBUFFERPROC>(SDL_GL_GetProcAddress("glInvalidateSubFramebuffer"));
	pfn_glGetTexParameteriv = reinterpret_cast<PFNGLGETTEXPARAMETERIVPROC>(SDL_GL_GetProcAddress("glGetTexParameteriv"));
	pfn_glFramebufferTextureLayer = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURELAYERPROC>(SDL_GL_GetProcAddress("glFramebufferTextureLayer"));
	pfn_glPointParameterf = reinterpret_cast<PFNGLPOINTPARAMETERFPROC>(SDL_GL_GetProcAddress("glPointParameterf"));
	pfn_glMultiTexCoordP3uiv = reinterpret_cast<PFNGLMULTITEXCOORDP3UIVPROC>(SDL_GL_GetProcAddress("glMultiTexCoordP3uiv"));
	pfn_glClampColor = reinterpret_cast<PFNGLCLAMPCOLORPROC>(SDL_GL_GetProcAddress("glClampColor"));
	pfn_glInvalidateTexImage = reinterpret_cast<PFNGLINVALIDATETEXIMAGEPROC>(SDL_GL_GetProcAddress("glInvalidateTexImage"));
	pfn_glMultiTexCoordP4ui = reinterpret_cast<PFNGLMULTITEXCOORDP4UIPROC>(SDL_GL_GetProcAddress("glMultiTexCoordP4ui"));
	pfn_glProgramUniform1f = reinterpret_cast<PFNGLPROGRAMUNIFORM1FPROC>(SDL_GL_GetProcAddress("glProgramUniform1f"));
	pfn_glGetTexParameterIuiv = reinterpret_cast<PFNGLGETTEXPARAMETERIUIVPROC>(SDL_GL_GetProcAddress("glGetTexParameterIuiv"));
	pfn_glGetnMinmax = reinterpret_cast<PFNGLGETNMINMAXPROC>(SDL_GL_GetProcAddress("glGetnMinmax"));
	pfn_glMultiTexCoordP4uiv = reinterpret_cast<PFNGLMULTITEXCOORDP4UIVPROC>(SDL_GL_GetProcAddress("glMultiTexCoordP4uiv"));
	pfn_glFlush = reinterpret_cast<PFNGLFLUSHPROC>(SDL_GL_GetProcAddress("glFlush"));
	pfn_glUniform3uiv = reinterpret_cast<PFNGLUNIFORM3UIVPROC>(SDL_GL_GetProcAddress("glUniform3uiv"));
	pfn_glProgramUniform1fv = reinterpret_cast<PFNGLPROGRAMUNIFORM1FVPROC>(SDL_GL_GetProcAddress("glProgramUniform1fv"));
	pfn_glTextureSubImage1D = reinterpret_cast<PFNGLTEXTURESUBIMAGE1DPROC>(SDL_GL_GetProcAddress("glTextureSubImage1D"));
	pfn_glTextureSubImage3D = reinterpret_cast<PFNGLTEXTURESUBIMAGE3DPROC>(SDL_GL_GetProcAddress("glTextureSubImage3D"));
	pfn_glFrontFace = reinterpret_cast<PFNGLFRONTFACEPROC>(SDL_GL_GetProcAddress("glFrontFace"));
	pfn_glClear = reinterpret_cast<PFNGLCLEARPROC>(SDL_GL_GetProcAddress("glClear"));
	pfn_glPointParameterfv = reinterpret_cast<PFNGLPOINTPARAMETERFVPROC>(SDL_GL_GetProcAddress("glPointParameterfv"));
	pfn_glViewportArrayv = reinterpret_cast<PFNGLVIEWPORTARRAYVPROC>(SDL_GL_GetProcAddress("glViewportArrayv"));
	pfn_glGetTexParameterfv = reinterpret_cast<PFNGLGETTEXPARAMETERFVPROC>(SDL_GL_GetProcAddress("glGetTexParameterfv"));
	pfn_glBindVertexBuffer = reinterpret_cast<PFNGLBINDVERTEXBUFFERPROC>(SDL_GL_GetProcAddress("glBindVertexBuffer"));
	pfn_glTransformFeedbackBufferBase = reinterpret_cast<PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC>(SDL_GL_GetProcAddress("glTransformFeedbackBufferBase"));
	pfn_glProgramUniform1i = reinterpret_cast<PFNGLPROGRAMUNIFORM1IPROC>(SDL_GL_GetProcAddress("glProgramUniform1i"));
	pfn_glVertexAttribL3d = reinterpret_cast<PFNGLVERTEXATTRIBL3DPROC>(SDL_GL_GetProcAddress("glVertexAttribL3d"));
	pfn_glFlushMappedBufferRange = reinterpret_cast<PFNGLFLUSHMAPPEDBUFFERRANGEPROC>(SDL_GL_GetProcAddress("glFlushMappedBufferRange"));
	pfn_glUniform4d = reinterpret_cast<PFNGLUNIFORM4DPROC>(SDL_GL_GetProcAddress("glUniform4d"));
	pfn_glGetnPixelMapuiv = reinterpret_cast<PFNGLGETNPIXELMAPUIVPROC>(SDL_GL_GetProcAddress("glGetnPixelMapuiv"));
	pfn_glVertexAttrib4fv = reinterpret_cast<PFNGLVERTEXATTRIB4FVPROC>(SDL_GL_GetProcAddress("glVertexAttrib4fv"));
	pfn_glBindVertexBuffers = reinterpret_cast<PFNGLBINDVERTEXBUFFERSPROC>(SDL_GL_GetProcAddress("glBindVertexBuffers"));
	pfn_glViewport = reinterpret_cast<PFNGLVIEWPORTPROC>(SDL_GL_GetProcAddress("glViewport"));
	pfn_glFlushMappedNamedBufferRange = reinterpret_cast<PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC>(SDL_GL_GetProcAddress("glFlushMappedNamedBufferRange"));
	pfn_glTextureSubImage2D = reinterpret_cast<PFNGLTEXTURESUBIMAGE2DPROC>(SDL_GL_GetProcAddress("glTextureSubImage2D"));
	pfn_glGetnPixelMapfv = reinterpret_cast<PFNGLGETNPIXELMAPFVPROC>(SDL_GL_GetProcAddress("glGetnPixelMapfv"));
	pfn_glUniform4f = reinterpret_cast<PFNGLUNIFORM4FPROC>(SDL_GL_GetProcAddress("glUniform4f"));
	pfn_glTexImage1D = reinterpret_cast<PFNGLTEXIMAGE1DPROC>(SDL_GL_GetProcAddress("glTexImage1D"));
	pfn_glVertexAttribL3dv = reinterpret_cast<PFNGLVERTEXATTRIBL3DVPROC>(SDL_GL_GetProcAddress("glVertexAttribL3dv"));
	pfn_glClearBufferData = reinterpret_cast<PFNGLCLEARBUFFERDATAPROC>(SDL_GL_GetProcAddress("glClearBufferData"));
	pfn_glTextureView = reinterpret_cast<PFNGLTEXTUREVIEWPROC>(SDL_GL_GetProcAddress("glTextureView"));
	pfn_glCopyBufferSubData = reinterpret_cast<PFNGLCOPYBUFFERSUBDATAPROC>(SDL_GL_GetProcAddress("glCopyBufferSubData"));
	pfn_glGetnPixelMapusv = reinterpret_cast<PFNGLGETNPIXELMAPUSVPROC>(SDL_GL_GetProcAddress("glGetnPixelMapusv"));
	pfn_glPointParameteri = reinterpret_cast<PFNGLPOINTPARAMETERIPROC>(SDL_GL_GetProcAddress("glPointParameteri"));
	pfn_glVertexAttrib4iv = reinterpret_cast<PFNGLVERTEXATTRIB4IVPROC>(SDL_GL_GetProcAddress("glVertexAttrib4iv"));
	pfn_glUniform4dv = reinterpret_cast<PFNGLUNIFORM4DVPROC>(SDL_GL_GetProcAddress("glUniform4dv"));
	pfn_glGetnPolygonStipple = reinterpret_cast<PFNGLGETNPOLYGONSTIPPLEPROC>(SDL_GL_GetProcAddress("glGetnPolygonStipple"));
	pfn_glIsEnabled = reinterpret_cast<PFNGLISENABLEDPROC>(SDL_GL_GetProcAddress("glIsEnabled"));
	pfn_glUniform4i = reinterpret_cast<PFNGLUNIFORM4IPROC>(SDL_GL_GetProcAddress("glUniform4i"));
	pfn_glTexImage2DMultisample = reinterpret_cast<PFNGLTEXIMAGE2DMULTISAMPLEPROC>(SDL_GL_GetProcAddress("glTexImage2DMultisample"));
	pfn_glProgramUniform1iv = reinterpret_cast<PFNGLPROGRAMUNIFORM1IVPROC>(SDL_GL_GetProcAddress("glProgramUniform1iv"));
	pfn_glViewportIndexedf = reinterpret_cast<PFNGLVIEWPORTINDEXEDFPROC>(SDL_GL_GetProcAddress("glViewportIndexedf"));
	pfn_glClearBufferiv = reinterpret_cast<PFNGLCLEARBUFFERIVPROC>(SDL_GL_GetProcAddress("glClearBufferiv"));
	pfn_glTexImage2D = reinterpret_cast<PFNGLTEXIMAGE2DPROC>(SDL_GL_GetProcAddress("glTexImage2D"));
	pfn_glGetTextureImage = reinterpret_cast<PFNGLGETTEXTUREIMAGEPROC>(SDL_GL_GetProcAddress("glGetTextureImage"));
	pfn_glTexImage3D = reinterpret_cast<PFNGLTEXIMAGE3DPROC>(SDL_GL_GetProcAddress("glTexImage3D"));
	pfn_glGetnTexImage = reinterpret_cast<PFNGLGETNTEXIMAGEPROC>(SDL_GL_GetProcAddress("glGetnTexImage"));
	pfn_glPointParameteriv = reinterpret_cast<PFNGLPOINTPARAMETERIVPROC>(SDL_GL_GetProcAddress("glPointParameteriv"));
	pfn_glVertexAttrib4s = reinterpret_cast<PFNGLVERTEXATTRIB4SPROC>(SDL_GL_GetProcAddress("glVertexAttrib4s"));
	pfn_glClearBufferSubData = reinterpret_cast<PFNGLCLEARBUFFERSUBDATAPROC>(SDL_GL_GetProcAddress("glClearBufferSubData"));
	pfn_glClearBufferfv = reinterpret_cast<PFNGLCLEARBUFFERFVPROC>(SDL_GL_GetProcAddress("glClearBufferfv"));
	pfn_glGetTextureLevelParameteriv = reinterpret_cast<PFNGLGETTEXTURELEVELPARAMETERIVPROC>(SDL_GL_GetProcAddress("glGetTextureLevelParameteriv"));
	pfn_glGetnSeparableFilter = reinterpret_cast<PFNGLGETNSEPARABLEFILTERPROC>(SDL_GL_GetProcAddress("glGetnSeparableFilter"));
	pfn_glUniform4fv = reinterpret_cast<PFNGLUNIFORM4FVPROC>(SDL_GL_GetProcAddress("glUniform4fv"));
	pfn_glProgramUniform1ui = reinterpret_cast<PFNGLPROGRAMUNIFORM1UIPROC>(SDL_GL_GetProcAddress("glProgramUniform1ui"));
	pfn_glClearBufferfi = reinterpret_cast<PFNGLCLEARBUFFERFIPROC>(SDL_GL_GetProcAddress("glClearBufferfi"));
	pfn_glIsEnabledi = reinterpret_cast<PFNGLISENABLEDIPROC>(SDL_GL_GetProcAddress("glIsEnabledi"));
	pfn_glCopyImageSubData = reinterpret_cast<PFNGLCOPYIMAGESUBDATAPROC>(SDL_GL_GetProcAddress("glCopyImageSubData"));
	pfn_glTransformFeedbackBufferRange = reinterpret_cast<PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC>(SDL_GL_GetProcAddress("glTransformFeedbackBufferRange"));
	pfn_glVertexAttribL4d = reinterpret_cast<PFNGLVERTEXATTRIBL4DPROC>(SDL_GL_GetProcAddress("glVertexAttribL4d"));
	pfn_glGetCompressedTextureImage = reinterpret_cast<PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC>(SDL_GL_GetProcAddress("glGetCompressedTextureImage"));
	pfn_glGetCompressedTexImage = reinterpret_cast<PFNGLGETCOMPRESSEDTEXIMAGEPROC>(SDL_GL_GetProcAddress("glGetCompressedTexImage"));
	pfn_glGenBuffers = reinterpret_cast<PFNGLGENBUFFERSPROC>(SDL_GL_GetProcAddress("glGenBuffers"));
	pfn_glClearBufferuiv = reinterpret_cast<PFNGLCLEARBUFFERUIVPROC>(SDL_GL_GetProcAddress("glClearBufferuiv"));
	pfn_glTexImage3DMultisample = reinterpret_cast<PFNGLTEXIMAGE3DMULTISAMPLEPROC>(SDL_GL_GetProcAddress("glTexImage3DMultisample"));
	pfn_glViewportIndexedfv = reinterpret_cast<PFNGLVIEWPORTINDEXEDFVPROC>(SDL_GL_GetProcAddress("glViewportIndexedfv"));
	pfn_glGetTextureParameterIiv = reinterpret_cast<PFNGLGETTEXTUREPARAMETERIIVPROC>(SDL_GL_GetProcAddress("glGetTextureParameterIiv"));
	pfn_glClearColor = reinterpret_cast<PFNGLCLEARCOLORPROC>(SDL_GL_GetProcAddress("glClearColor"));
	pfn_glTransformFeedbackVaryings = reinterpret_cast<PFNGLTRANSFORMFEEDBACKVARYINGSPROC>(SDL_GL_GetProcAddress("glTransformFeedbackVaryings"));
	pfn_glGetTextureLevelParameterfv = reinterpret_cast<PFNGLGETTEXTURELEVELPARAMETERFVPROC>(SDL_GL_GetProcAddress("glGetTextureLevelParameterfv"));
	pfn_glProgramUniform1uiv = reinterpret_cast<PFNGLPROGRAMUNIFORM1UIVPROC>(SDL_GL_GetProcAddress("glProgramUniform1uiv"));
	pfn_glGetTextureParameterIuiv = reinterpret_cast<PFNGLGETTEXTUREPARAMETERIUIVPROC>(SDL_GL_GetProcAddress("glGetTextureParameterIuiv"));
	pfn_glGetnUniformdv = reinterpret_cast<PFNGLGETNUNIFORMDVPROC>(SDL_GL_GetProcAddress("glGetnUniformdv"));
	pfn_glVertexAttrib4sv = reinterpret_cast<PFNGLVERTEXATTRIB4SVPROC>(SDL_GL_GetProcAddress("glVertexAttrib4sv"));
	pfn_glGetCompressedTextureSubImage = reinterpret_cast<PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC>(SDL_GL_GetProcAddress("glGetCompressedTextureSubImage"));
	pfn_glProgramUniform2d = reinterpret_cast<PFNGLPROGRAMUNIFORM2DPROC>(SDL_GL_GetProcAddress("glProgramUniform2d"));
	pfn_glVertexAttribL4dv = reinterpret_cast<PFNGLVERTEXATTRIBL4DVPROC>(SDL_GL_GetProcAddress("glVertexAttribL4dv"));
}
