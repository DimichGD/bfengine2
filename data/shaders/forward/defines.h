#define INPUT_POSITION   layout(location = 0) in vec3 IN_POSITION
#define INPUT_TEXCOORD_0 layout(location = 1) in vec2 IN_TEXCOORD_0
#define INPUT_TEXCOORD_1 layout(location = 2) in vec2 IN_TEXCOORD_1
#define INPUT_COLOR      layout(location = 3) in vec3 IN_COLOR
#define INPUT_NORMAL     layout(location = 4) in vec4 IN_NORMAL
#define INPUT_TANGENT    layout(location = 5) in vec4 IN_TANGENT
#define INPUT_BONES      layout(location = 6) in vec4 IN_BONES
#define INPUT_WEIGHTS    layout(location = 7) in vec4 IN_WEIGHTS

#define UNIFORM_MODEL_MATRIX layout(location = 0) uniform mat4 MODEL_MATRIX
#define UNIFORM_VIEW_MATRIX  layout(location = 1) uniform mat4 VIEW_MATRIX
#define UNIFORM_PROJ_MATRIX  layout(location = 2) uniform mat4 PROJ_MATRIX
#define UNIFORM_COLOR        layout(location = 3) uniform vec4 COLOR
