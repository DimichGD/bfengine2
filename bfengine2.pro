TEMPLATE = app
CONFIG += console c++latest strict_c++
CONFIG += link_pkgconfig
CONFIG -= qt app_bundle
CONFIG -= debug_and_release debug_and_release_target

INCLUDEPATH += src
OBJECTS_DIR = obj

SOURCES += \
    src/core/config.cpp \
    src/core/log.cpp \
    src/engine/resource_manager.cpp \
    src/entities/transform.cpp \
    src/graphics/geometry.cpp \
    src/graphics/opengl/convert_enum_gl.cpp \
    src/graphics/opengl/opengl_gen.cpp \
    src/graphics/opengl/render_device_gl.cpp \
    src/graphics/render_doc.cpp \
    src/graphics/render_paths/debug_render_path.cpp \
    src/graphics/render_paths/deferred_render_path.cpp \
    src/graphics/render_paths/point_light_render_path.cpp \
    src/graphics/vulkan/vk_convert_enum.cpp \
    src/graphics/vulkan/vk_enumerate_stuff.cpp \
    src/graphics/vulkan/vk_internal.cpp \
    src/graphics/vulkan/vk_pipeline_builder.cpp \
    src/graphics/vulkan/vk_render_device.cpp \
    src/graphics/vulkan/vk_shader_builder.cpp \
    src/graphics/vulkan/vk_shader_reflection.cpp \
    src/io/file.cpp \
    src/main.cpp \
    src/math/matrix.cpp \
    src/platform/input.cpp \
    src/platform/window_sdl2.cpp \
    src/ui/font.cpp \
    src/ui/ui_manager.cpp \
    src/utils/lexer.cpp \
    src/utils/parser.cpp \
    src/utils/utf8.cpp

HEADERS += \
    src/core/config.hpp \
    src/core/context.hpp \
    src/core/defines.hpp \
    src/core/log.hpp \
    src/engine/resource_manager.hpp \
    src/entities/transform.hpp \
    src/graphics/frame_graph.hpp \
    src/graphics/geometry.hpp \
    src/graphics/opengl/convert_enum_gl.hpp \
    src/graphics/opengl/opengl_gen.hpp \
    src/graphics/opengl/render_device_gl.hpp \
    src/graphics/render_device.hpp \
    src/graphics/render_doc.hpp \
    src/graphics/render_paths/debug_render_path.hpp \
    src/graphics/render_paths/deferred_render_path.hpp \
    src/graphics/render_paths/graphics_context.hpp \
    src/graphics/render_paths/point_light_render_path.hpp \
    src/graphics/resource_array.hpp \
    src/graphics/shader_description.hpp \
    src/graphics/types.hpp \
    src/graphics/vulkan/vk_convert_enum.hpp \
    src/graphics/vulkan/vk_enumerate_stuff.hpp \
    src/graphics/vulkan/vk_internal.hpp \
    src/graphics/vulkan/vk_pipeline_builder.hpp \
    src/graphics/vulkan/vk_render_device.hpp \
    src/graphics/vulkan/vk_shader_builder.hpp \
    src/graphics/vulkan/vk_shader_reflection.hpp \
    src/io/file.hpp \
    src/math/matrix.hpp \
    src/platform/input.hpp \
    src/platform/window_sdl2.hpp \
    src/ui/font.hpp \
    src/ui/ui_manager.hpp \
    src/utils/enum_operators.hpp \
    src/utils/hash.hpp \
    src/utils/lexer.hpp \
    src/utils/parser.hpp \
    src/utils/utf8.hpp

PKGCONFIG += freetype2 shaderc spirv-cross-c-shared
LIBS += -lSDL3 -lSDL3_image -lvulkan-1 -lfmt -lpng -lzip

