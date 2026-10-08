// SDL3 GPU presenter for the emulated Direct3D 8 device (port/shell/
// render_backend.h), the native counterpart of port/web/renderer.js. A frame's
// clears and draws are recorded as they arrive, then submitted together:
// vertices go up in one buffer, the scene renders into a target with depth, and
// the target is scaled into the window with letterboxing. The target is
// 640x480, or with `hidpi` the size the frame fills in the window's pixels:
// viewports scale with it, while the half-pixel offset stays half of an
// original pixel, so everything lands where it did.
//
// Shaders are Metal Shading Language, so this runs on macOS. Other platforms
// need the same two shaders as SPIR-V or DXIL.

#include <SDL3/SDL.h>
#include <string.h>

#include <unordered_map>
#include <vector>

#include "host.h"

namespace {

const int kWidth = 640, kHeight = 480;
const int kVertexBytes = 32;
const int kStateWords = 28;

// render_backend.h RenderState, field for field.
struct State {
    int32_t texture;
    int32_t color_op, color_arg1, color_arg2;
    int32_t alpha_op, alpha_arg1, alpha_arg2;
    uint32_t texture_factor;
    int32_t address_u, address_v;
    int32_t alpha_blend, src_blend, dest_blend;
    int32_t alpha_test, alpha_func, alpha_ref;
    int32_t z_enable, z_write, z_func;
    int32_t cull;
    int32_t fog;
    uint32_t fog_color;
    int32_t viewport_x, viewport_y, viewport_width, viewport_height;
    float viewport_min_z, viewport_max_z;
};
static_assert(sizeof(State) == kStateWords * 4, "RenderState layout");

const char* kShaders = R"(
#include <metal_stdlib>
using namespace metal;

struct VertexIn {
    float4 position [[attribute(0)]];
    float4 color [[attribute(1)]];   // D3DCOLOR bytes: B, G, R, A
    float2 uv [[attribute(2)]];
    float fog [[attribute(3)]];
};

struct VertexOut {
    float4 position [[position]];
    float4 color;
    float2 uv;
    float fog;
};

struct VertexUniforms {
    float2 half_pixel;  // Direct3D's pixel centres sit half a pixel up and left
};

vertex VertexOut vertex_main(VertexIn in [[stage_in]], constant VertexUniforms& u [[buffer(0)]]) {
    VertexOut out;
    float4 p = in.position;
    out.position = float4(p.x - u.half_pixel.x * p.w, p.y + u.half_pixel.y * p.w, p.z, p.w);
    out.color = in.color.zyxw;
    out.uv = in.uv;
    out.fog = in.fog;
    return out;
}

struct FragmentUniforms {
    int4 color_op;    // D3DTOP, D3DTA, D3DTA, texture bound
    int4 alpha_op;    // D3DTOP, D3DTA, D3DTA, D3DCMP alpha test (0 off)
    float4 texture_factor;
    float4 fog_color; // rgb, then 1 when fog is on
    float alpha_ref;
};

float4 argument(int a, float4 diffuse, float4 texel, float4 factor) {
    int source = a & 7;
    float4 v = source == 2 ? texel : source == 3 ? factor : diffuse;
    if ((a & 0x10) != 0) v = 1.0 - v;
    if ((a & 0x20) != 0) v = float4(v.a);
    return v;
}

float4 combine(int3 op, float4 diffuse, float4 texel, float4 factor) {
    float4 a = argument(op.y, diffuse, texel, factor), b = argument(op.z, diffuse, texel, factor);
    switch (op.x) {
        case 1: return diffuse;
        case 2: return a;
        case 3: return b;
        case 4: return a * b;
        case 5: return 2.0 * a * b;
        case 6: return 4.0 * a * b;
        case 7: return a + b;
        case 8: return a + b - 0.5;
        case 9: return 2.0 * (a + b - 0.5);
        case 10: return a - b;
        case 11: return a + b - a * b;
        default: return a * b;
    }
}

bool passes(int func, float value, float reference) {
    switch (func) {
        case 1: return false;
        case 2: return value < reference;
        case 3: return value == reference;
        case 4: return value <= reference;
        case 5: return value > reference;
        case 6: return value != reference;
        case 7: return value >= reference;
        default: return true;
    }
}

fragment float4 fragment_main(VertexOut in [[stage_in]], constant FragmentUniforms& u [[buffer(0)]],
    texture2d<float> texture [[texture(0)]], sampler sampler0 [[sampler(0)]]) {
    float4 texel = u.color_op.w != 0 ? texture.sample(sampler0, in.uv) : float4(0.0, 0.0, 0.0, 1.0);
    float4 result;
    if (u.color_op.x == 1) {
        result = in.color;
    } else {
        result.rgb = combine(u.color_op.xyz, in.color, texel, u.texture_factor).rgb;
        result.a = combine(u.alpha_op.xyz, in.color, texel, u.texture_factor).a;
    }
    result = clamp(result, 0.0, 1.0);
    if (u.alpha_op.w != 0 && !passes(u.alpha_op.w, floor(result.a * 255.0 + 0.5), u.alpha_ref)) discard_fragment();
    if (u.fog_color.w != 0) result.rgb = mix(u.fog_color.rgb, result.rgb, clamp(in.fog, 0.0, 1.0));
    return result;
}

// Clears restricted to the viewport, as Direct3D's are: a full-viewport quad.
struct ClearOut {
    float4 position [[position]];
    float4 color;
};

struct ClearUniforms {
    float4 color;
    float depth;
};

vertex ClearOut clear_vertex(uint id [[vertex_id]], constant ClearUniforms& u [[buffer(0)]]) {
    float2 corner = float2((id << 1) & 2, id & 2);
    ClearOut out;
    out.position = float4(corner * 2.0 - 1.0, u.depth, 1.0);
    out.color = u.color;
    return out;
}

fragment float4 clear_fragment(ClearOut in [[stage_in]]) {
    return in.color;
}
)";

struct VertexUniforms {
    float half_pixel[2];
};

struct FragmentUniforms {
    int32_t color_op[4];
    int32_t alpha_op[4];
    float texture_factor[4];
    float fog_color[4];
    float alpha_ref;
    float padding[3];
};

struct ClearUniforms {
    float color[4];
    float depth;
    float padding[3];
};

struct Command {
    bool clear;
    int primitive;  // draws: RenderPrimitive
    int flags;      // clears: RenderClearFlags
    uint32_t color;
    float depth;
    State state;
    uint32_t first, count;  // draws: vertices in the frame buffer
};

void argb(uint32_t value, float* out)
{
    out[0] = ((value >> 16) & 255) / 255.0f;
    out[1] = ((value >> 8) & 255) / 255.0f;
    out[2] = (value & 255) / 255.0f;
    out[3] = (value >> 24) / 255.0f;
}

SDL_GPUBlendFactor blend_factor(int d3d)
{
    switch (d3d) {
    case 1: return SDL_GPU_BLENDFACTOR_ZERO;
    case 2: return SDL_GPU_BLENDFACTOR_ONE;
    case 3: return SDL_GPU_BLENDFACTOR_SRC_COLOR;
    case 4: return SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_COLOR;
    case 5: return SDL_GPU_BLENDFACTOR_SRC_ALPHA;
    case 6: return SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
    case 7: return SDL_GPU_BLENDFACTOR_DST_ALPHA;
    case 8: return SDL_GPU_BLENDFACTOR_ONE_MINUS_DST_ALPHA;
    case 9: return SDL_GPU_BLENDFACTOR_DST_COLOR;
    case 10: return SDL_GPU_BLENDFACTOR_ONE_MINUS_DST_COLOR;
    case 11: return SDL_GPU_BLENDFACTOR_SRC_ALPHA_SATURATE;
    default: return SDL_GPU_BLENDFACTOR_ONE;
    }
}

SDL_GPUCompareOp compare_op(int d3d)
{
    switch (d3d) {
    case 1: return SDL_GPU_COMPAREOP_NEVER;
    case 2: return SDL_GPU_COMPAREOP_LESS;
    case 3: return SDL_GPU_COMPAREOP_EQUAL;
    case 4: return SDL_GPU_COMPAREOP_LESS_OR_EQUAL;
    case 5: return SDL_GPU_COMPAREOP_GREATER;
    case 6: return SDL_GPU_COMPAREOP_NOT_EQUAL;
    case 7: return SDL_GPU_COMPAREOP_GREATER_OR_EQUAL;
    default: return SDL_GPU_COMPAREOP_ALWAYS;
    }
}

SDL_GPUSamplerAddressMode address_mode(int d3d)
{
    switch (d3d) {
    case 2: return SDL_GPU_SAMPLERADDRESSMODE_MIRRORED_REPEAT;
    case 3: case 4: return SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
    default: return SDL_GPU_SAMPLERADDRESSMODE_REPEAT;
    }
}

}  // namespace

struct GpuPresenter {
    SDL_Window* window;
    SDL_GPUDevice* device;
    SDL_GPUShader *vertex, *fragment, *clear_vertex, *clear_fragment;
    SDL_GPUTexture *target = nullptr, *depth = nullptr, *blank;
    SDL_GPUTextureFormat depth_format;
    bool hidpi;
    int width = 0, height = 0;  // of the target
    float scale = 1;            // target pixels per original pixel
    SDL_GPUSampler* samplers[5][5];
    std::unordered_map<uint64_t, SDL_GPUGraphicsPipeline*> pipelines;
    std::unordered_map<int, SDL_GPUTexture*> textures;
    std::vector<uint8_t> vertices;
    std::vector<Command> commands;
    SDL_GPUBuffer* vertex_buffer = nullptr;
    uint32_t vertex_capacity = 0;
};

namespace {

SDL_GPUShader* shader(GpuPresenter* gpu, const char* entry, SDL_GPUShaderStage stage, int samplers, int uniforms)
{
    SDL_GPUShaderCreateInfo info = {};
    info.code = (const Uint8*)kShaders;
    info.code_size = strlen(kShaders);
    info.entrypoint = entry;
    info.format = SDL_GPU_SHADERFORMAT_MSL;
    info.stage = stage;
    info.num_samplers = samplers;
    info.num_uniform_buffers = uniforms;
    SDL_GPUShader* result = SDL_CreateGPUShader(gpu->device, &info);
    if (!result)
        SDL_Log("snail: shader %s: %s", entry, SDL_GetError());
    return result;
}

SDL_GPUTexture* create_texture(GpuPresenter* gpu, int width, int height, SDL_GPUTextureFormat format,
    SDL_GPUTextureUsageFlags usage)
{
    SDL_GPUTextureCreateInfo info = {};
    info.type = SDL_GPU_TEXTURETYPE_2D;
    info.format = format;
    info.usage = usage;
    info.width = width;
    info.height = height;
    info.layer_count_or_depth = 1;
    info.num_levels = 1;
    return SDL_CreateGPUTexture(gpu->device, &info);
}

void upload_texture(GpuPresenter* gpu, SDL_GPUTexture* texture, int width, int height, const uint8_t* rgba)
{
    uint32_t size = (uint32_t)width * height * 4;
    SDL_GPUTransferBufferCreateInfo transfer_info = {SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD, size, 0};
    SDL_GPUTransferBuffer* transfer = SDL_CreateGPUTransferBuffer(gpu->device, &transfer_info);
    memcpy(SDL_MapGPUTransferBuffer(gpu->device, transfer, false), rgba, size);
    SDL_UnmapGPUTransferBuffer(gpu->device, transfer);
    SDL_GPUCommandBuffer* commands = SDL_AcquireGPUCommandBuffer(gpu->device);
    SDL_GPUCopyPass* copy = SDL_BeginGPUCopyPass(commands);
    SDL_GPUTextureTransferInfo source = {transfer, 0, (Uint32)width, (Uint32)height};
    SDL_GPUTextureRegion destination = {};
    destination.texture = texture;
    destination.w = width;
    destination.h = height;
    destination.d = 1;
    SDL_UploadToGPUTexture(copy, &source, &destination, false);
    SDL_EndGPUCopyPass(copy);
    SDL_SubmitGPUCommandBuffer(commands);
    SDL_ReleaseGPUTransferBuffer(gpu->device, transfer);
}

// Draw pipelines differ in blending, depth, culling and primitive; clear
// pipelines in which of colour and depth they write.
SDL_GPUGraphicsPipeline* pipeline(GpuPresenter* gpu, const Command& command)
{
    const State& s = command.state;
    uint64_t key;
    if (command.clear) {
        key = 1ull << 63 | (uint64_t)command.flags;
    } else {
        key = (uint64_t)(s.alpha_blend != 0) | (uint64_t)(s.src_blend & 15) << 1 | (uint64_t)(s.dest_blend & 15) << 5
            | (uint64_t)(s.z_enable != 0) << 9 | (uint64_t)(s.z_write != 0) << 10 | (uint64_t)(s.z_func & 15) << 11
            | (uint64_t)(s.cull & 3) << 15 | (uint64_t)command.primitive << 17;
    }
    auto found = gpu->pipelines.find(key);
    if (found != gpu->pipelines.end())
        return found->second;

    SDL_GPUColorTargetDescription color = {};
    color.format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM;
    SDL_GPUGraphicsPipelineCreateInfo info = {};
    info.target_info.color_target_descriptions = &color;
    info.target_info.num_color_targets = 1;
    info.target_info.has_depth_stencil_target = true;
    info.target_info.depth_stencil_format = gpu->depth_format;
    info.rasterizer_state.fill_mode = SDL_GPU_FILLMODE_FILL;
    // Direct3D's front faces are clockwise; D3DCULL_CCW culls the back ones.
    info.rasterizer_state.front_face = SDL_GPU_FRONTFACE_CLOCKWISE;

    SDL_GPUVertexBufferDescription buffer = {0, kVertexBytes, SDL_GPU_VERTEXINPUTRATE_VERTEX, 0};
    SDL_GPUVertexAttribute attributes[4] = {
        {0, 0, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4, 0},
        {1, 0, SDL_GPU_VERTEXELEMENTFORMAT_UBYTE4_NORM, 16},
        {2, 0, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2, 20},
        {3, 0, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT, 28},
    };
    if (command.clear) {
        info.vertex_shader = gpu->clear_vertex;
        info.fragment_shader = gpu->clear_fragment;
        info.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
        info.rasterizer_state.cull_mode = SDL_GPU_CULLMODE_NONE;
        color.blend_state.enable_color_write_mask = true;
        color.blend_state.color_write_mask = (command.flags & 1) ? 0xf : 0;
        info.depth_stencil_state.enable_depth_test = (command.flags & 2) != 0;
        info.depth_stencil_state.enable_depth_write = (command.flags & 2) != 0;
        info.depth_stencil_state.compare_op = SDL_GPU_COMPAREOP_ALWAYS;
    } else {
        info.vertex_shader = gpu->vertex;
        info.fragment_shader = gpu->fragment;
        info.vertex_input_state.vertex_buffer_descriptions = &buffer;
        info.vertex_input_state.num_vertex_buffers = 1;
        info.vertex_input_state.vertex_attributes = attributes;
        info.vertex_input_state.num_vertex_attributes = 4;
        info.primitive_type =
            command.primitive == 1 ? SDL_GPU_PRIMITIVETYPE_LINELIST : SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
        info.rasterizer_state.cull_mode =
            s.cull == 3 ? SDL_GPU_CULLMODE_BACK : s.cull == 2 ? SDL_GPU_CULLMODE_FRONT : SDL_GPU_CULLMODE_NONE;
        if (s.alpha_blend) {
            color.blend_state.enable_blend = true;
            color.blend_state.src_color_blendfactor = color.blend_state.src_alpha_blendfactor = blend_factor(s.src_blend);
            color.blend_state.dst_color_blendfactor = color.blend_state.dst_alpha_blendfactor = blend_factor(s.dest_blend);
            color.blend_state.color_blend_op = color.blend_state.alpha_blend_op = SDL_GPU_BLENDOP_ADD;
        }
        info.depth_stencil_state.enable_depth_test = s.z_enable != 0;
        info.depth_stencil_state.enable_depth_write = s.z_enable != 0 && s.z_write != 0;
        info.depth_stencil_state.compare_op = compare_op(s.z_func);
    }
    SDL_GPUGraphicsPipeline* result = SDL_CreateGPUGraphicsPipeline(gpu->device, &info);
    if (!result)
        SDL_Log("snail: pipeline: %s", SDL_GetError());
    gpu->pipelines[key] = result;
    return result;
}

void set_viewport(GpuPresenter* gpu, SDL_GPURenderPass* pass, const State& s)
{
    float k = gpu->scale;
    SDL_GPUViewport viewport = {SDL_roundf(s.viewport_x * k), SDL_roundf(s.viewport_y * k),
        SDL_roundf(s.viewport_width * k), SDL_roundf(s.viewport_height * k), s.viewport_min_z, s.viewport_max_z};
    SDL_SetGPUViewport(pass, &viewport);
}

// (Re)creates the target at `width` pixels across, 4:3.
void resize_target(GpuPresenter* gpu, int width)
{
    int height = (width * 3 + 2) / 4;
    if (width == gpu->width && height == gpu->height)
        return;
    if (gpu->target) {
        SDL_ReleaseGPUTexture(gpu->device, gpu->target);
        SDL_ReleaseGPUTexture(gpu->device, gpu->depth);
    }
    gpu->target = create_texture(gpu, width, height, SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
        SDL_GPU_TEXTUREUSAGE_COLOR_TARGET | SDL_GPU_TEXTUREUSAGE_SAMPLER);
    gpu->depth = create_texture(gpu, width, height, gpu->depth_format, SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET);
    gpu->width = width;
    gpu->height = height;
    gpu->scale = (float)width / kWidth;
}

}  // namespace

GpuPresenter* gpu_create(SDL_Window* window, bool hidpi)
{
    GpuPresenter* gpu = new GpuPresenter;
    gpu->window = window;
    gpu->hidpi = hidpi;
    gpu->device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_MSL, false, nullptr);
    if (!gpu->device || !SDL_ClaimWindowForGPUDevice(gpu->device, window)) {
        SDL_Log("snail: GPU device: %s", SDL_GetError());
        return nullptr;
    }
    SDL_SetGPUSwapchainParameters(gpu->device, window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, SDL_GPU_PRESENTMODE_VSYNC);
    gpu->vertex = shader(gpu, "vertex_main", SDL_GPU_SHADERSTAGE_VERTEX, 0, 1);
    gpu->fragment = shader(gpu, "fragment_main", SDL_GPU_SHADERSTAGE_FRAGMENT, 1, 1);
    gpu->clear_vertex = shader(gpu, "clear_vertex", SDL_GPU_SHADERSTAGE_VERTEX, 0, 1);
    gpu->clear_fragment = shader(gpu, "clear_fragment", SDL_GPU_SHADERSTAGE_FRAGMENT, 0, 0);
    if (!gpu->vertex || !gpu->fragment || !gpu->clear_vertex || !gpu->clear_fragment)
        return nullptr;

    gpu->depth_format = SDL_GPU_TEXTUREFORMAT_D32_FLOAT;
    resize_target(gpu, kWidth);
    gpu->blank = create_texture(gpu, 1, 1, SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM, SDL_GPU_TEXTUREUSAGE_SAMPLER);
    const uint8_t black[4] = {0, 0, 0, 255};
    upload_texture(gpu, gpu->blank, 1, 1, black);

    for (int u = 0; u < 5; ++u)
        for (int v = 0; v < 5; ++v) {
            SDL_GPUSamplerCreateInfo info = {};
            info.min_filter = info.mag_filter = SDL_GPU_FILTER_LINEAR;
            info.mipmap_mode = SDL_GPU_SAMPLERMIPMAPMODE_NEAREST;
            info.address_mode_u = address_mode(u);
            info.address_mode_v = address_mode(v);
            info.address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_REPEAT;
            gpu->samplers[u][v] = SDL_CreateGPUSampler(gpu->device, &info);
        }
    return gpu;
}

bool gpu_frame_pending(GpuPresenter* gpu) { return !gpu->commands.empty(); }

void gpu_end_frame(GpuPresenter* gpu, bool present)
{
    if (gpu->hidpi) {
        int width, height;
        SDL_GetWindowSizeInPixels(gpu->window, &width, &height);
        resize_target(gpu, SDL_max(kWidth, SDL_min(width, height * 4 / 3)));
    }
    SDL_GPUCommandBuffer* commands = SDL_AcquireGPUCommandBuffer(gpu->device);

    // All of the frame's vertices in one buffer.
    uint32_t size = (uint32_t)gpu->vertices.size();
    if (size > gpu->vertex_capacity) {
        if (gpu->vertex_buffer)
            SDL_ReleaseGPUBuffer(gpu->device, gpu->vertex_buffer);
        gpu->vertex_capacity = size * 2;
        SDL_GPUBufferCreateInfo info = {SDL_GPU_BUFFERUSAGE_VERTEX, gpu->vertex_capacity, 0};
        gpu->vertex_buffer = SDL_CreateGPUBuffer(gpu->device, &info);
    }
    if (size) {
        SDL_GPUTransferBufferCreateInfo transfer_info = {SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD, size, 0};
        SDL_GPUTransferBuffer* transfer = SDL_CreateGPUTransferBuffer(gpu->device, &transfer_info);
        memcpy(SDL_MapGPUTransferBuffer(gpu->device, transfer, false), gpu->vertices.data(), size);
        SDL_UnmapGPUTransferBuffer(gpu->device, transfer);
        SDL_GPUCopyPass* copy = SDL_BeginGPUCopyPass(commands);
        SDL_GPUTransferBufferLocation source = {transfer, 0};
        SDL_GPUBufferRegion destination = {gpu->vertex_buffer, 0, size};
        SDL_UploadToGPUBuffer(copy, &source, &destination, false);
        SDL_EndGPUCopyPass(copy);
        SDL_ReleaseGPUTransferBuffer(gpu->device, transfer);
    }

    // The scene: the original never cleared colour between frames, so the
    // target keeps its contents.
    SDL_GPUColorTargetInfo color = {};
    color.texture = gpu->target;
    color.load_op = SDL_GPU_LOADOP_LOAD;
    color.store_op = SDL_GPU_STOREOP_STORE;
    SDL_GPUDepthStencilTargetInfo depth = {};
    depth.texture = gpu->depth;
    depth.load_op = SDL_GPU_LOADOP_LOAD;
    depth.store_op = SDL_GPU_STOREOP_STORE;
    depth.stencil_load_op = SDL_GPU_LOADOP_DONT_CARE;
    depth.stencil_store_op = SDL_GPU_STOREOP_DONT_CARE;
    SDL_GPURenderPass* pass = SDL_BeginGPURenderPass(commands, &color, 1, &depth);
    SDL_GPUBufferBinding binding = {gpu->vertex_buffer, 0};
    for (const Command& command : gpu->commands) {
        SDL_GPUGraphicsPipeline* state_pipeline = pipeline(gpu, command);
        if (!state_pipeline)
            continue;
        SDL_BindGPUGraphicsPipeline(pass, state_pipeline);
        set_viewport(gpu, pass, command.state);
        if (command.clear) {
            ClearUniforms uniforms = {};
            argb(command.color, uniforms.color);
            uniforms.depth = command.depth;
            SDL_PushGPUVertexUniformData(commands, 0, &uniforms, sizeof(uniforms));
            SDL_DrawGPUPrimitives(pass, 3, 1, 0, 0);
            continue;
        }
        const State& s = command.state;
        VertexUniforms vertex_uniforms = {{1.0f / s.viewport_width, 1.0f / s.viewport_height}};
        SDL_PushGPUVertexUniformData(commands, 0, &vertex_uniforms, sizeof(vertex_uniforms));
        auto texture = gpu->textures.find(s.texture);
        bool textured = s.texture && texture != gpu->textures.end();
        FragmentUniforms uniforms = {};
        int32_t color_op[4] = {s.color_op, s.color_arg1, s.color_arg2, textured};
        int32_t alpha_op[4] = {s.alpha_op, s.alpha_arg1, s.alpha_arg2, s.alpha_test ? s.alpha_func : 0};
        memcpy(uniforms.color_op, color_op, sizeof(color_op));
        memcpy(uniforms.alpha_op, alpha_op, sizeof(alpha_op));
        argb(s.texture_factor, uniforms.texture_factor);
        argb(s.fog_color, uniforms.fog_color);
        uniforms.fog_color[3] = s.fog ? 1.0f : 0.0f;
        uniforms.alpha_ref = (float)(s.alpha_ref & 255);
        SDL_PushGPUFragmentUniformData(commands, 0, &uniforms, sizeof(uniforms));
        int u = s.address_u >= 1 && s.address_u <= 4 ? s.address_u : 1;
        int v = s.address_v >= 1 && s.address_v <= 4 ? s.address_v : 1;
        SDL_GPUTextureSamplerBinding sampler = {textured ? texture->second : gpu->blank, gpu->samplers[u][v]};
        SDL_BindGPUFragmentSamplers(pass, 0, &sampler, 1);
        SDL_BindGPUVertexBuffers(pass, 0, &binding, 1);
        SDL_DrawGPUPrimitives(pass, command.count, 1, command.first, 0);
    }
    SDL_EndGPURenderPass(pass);
    gpu->commands.clear();
    gpu->vertices.clear();

    // Scale the frame into the window, letterboxed.
    SDL_GPUTexture* swapchain;
    Uint32 width, height;
    if (present && SDL_WaitAndAcquireGPUSwapchainTexture(commands, gpu->window, &swapchain, &width, &height) && swapchain) {
        float scale = SDL_min((float)width / kWidth, (float)height / kHeight);
        float w = kWidth * scale, h = kHeight * scale;
        SDL_GPUBlitInfo blit = {};
        blit.source.texture = gpu->target;
        blit.source.w = gpu->width;
        blit.source.h = gpu->height;
        blit.destination.texture = swapchain;
        blit.destination.x = (Uint32)((width - w) / 2);
        blit.destination.y = (Uint32)((height - h) / 2);
        blit.destination.w = (Uint32)w;
        blit.destination.h = (Uint32)h;
        blit.load_op = SDL_GPU_LOADOP_CLEAR;
        blit.clear_color = {0, 0, 0, 1};
        blit.filter = SDL_GPU_FILTER_LINEAR;
        SDL_BlitGPUTexture(commands, &blit);
    }
    SDL_SubmitGPUCommandBuffer(commands);
}

bool gpu_save_frame(GpuPresenter* gpu, const char* path)
{
    uint32_t size = (uint32_t)gpu->width * gpu->height * 4;
    SDL_GPUTransferBufferCreateInfo transfer_info = {SDL_GPU_TRANSFERBUFFERUSAGE_DOWNLOAD, size, 0};
    SDL_GPUTransferBuffer* transfer = SDL_CreateGPUTransferBuffer(gpu->device, &transfer_info);
    SDL_GPUCommandBuffer* commands = SDL_AcquireGPUCommandBuffer(gpu->device);
    SDL_GPUCopyPass* copy = SDL_BeginGPUCopyPass(commands);
    SDL_GPUTextureRegion source = {};
    source.texture = gpu->target;
    source.w = gpu->width;
    source.h = gpu->height;
    source.d = 1;
    SDL_GPUTextureTransferInfo destination = {transfer, 0, (Uint32)gpu->width, (Uint32)gpu->height};
    SDL_DownloadFromGPUTexture(copy, &source, &destination);
    SDL_EndGPUCopyPass(copy);
    SDL_GPUFence* fence = SDL_SubmitGPUCommandBufferAndAcquireFence(commands);
    SDL_WaitForGPUFences(gpu->device, true, &fence, 1);
    SDL_ReleaseGPUFence(gpu->device, fence);
    SDL_Surface* surface = SDL_CreateSurface(gpu->width, gpu->height, SDL_PIXELFORMAT_RGBA32);
    memcpy(surface->pixels, SDL_MapGPUTransferBuffer(gpu->device, transfer, false), size);
    SDL_UnmapGPUTransferBuffer(gpu->device, transfer);
    SDL_ReleaseGPUTransferBuffer(gpu->device, transfer);
    bool saved = SDL_SavePNG(surface, path);
    SDL_DestroySurface(surface);
    return saved;
}

// --- imports from the game ---------------------------------------------------------

extern "C" {

void w2c_snail_texture_create(w2c_snail* host, uint32_t id, uint32_t width, uint32_t height, uint32_t pointer)
{
    GpuPresenter* gpu = host->gpu;
    SDL_GPUTexture* texture =
        create_texture(gpu, (int)width, (int)height, SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM, SDL_GPU_TEXTUREUSAGE_SAMPLER);
    upload_texture(gpu, texture, (int)width, (int)height, linear_memory(host->game) + pointer);
    gpu->textures[(int)id] = texture;
}

void w2c_snail_texture_destroy(w2c_snail* host, uint32_t id)
{
    auto it = host->gpu->textures.find((int)id);
    if (it != host->gpu->textures.end()) {
        SDL_ReleaseGPUTexture(host->gpu->device, it->second);
        host->gpu->textures.erase(it);
    }
}

void w2c_snail_clear(w2c_snail* host, uint32_t flags, uint32_t color, float z, uint32_t state)
{
    Command command = {};
    command.clear = true;
    command.flags = (int)flags & 3;
    command.color = color;
    command.depth = z;
    memcpy(&command.state, linear_memory(host->game) + state, sizeof(State));
    if (command.flags)
        host->gpu->commands.push_back(command);
}

void w2c_snail_draw(w2c_snail* host, uint32_t primitive, uint32_t pointer, uint32_t count, uint32_t state)
{
    GpuPresenter* gpu = host->gpu;
    Command command = {};
    command.primitive = (int)primitive;
    memcpy(&command.state, linear_memory(host->game) + state, sizeof(State));
    command.first = (uint32_t)(gpu->vertices.size() / kVertexBytes);
    command.count = count;
    const uint8_t* source = linear_memory(host->game) + pointer;
    gpu->vertices.insert(gpu->vertices.end(), source, source + (size_t)count * kVertexBytes);
    gpu->commands.push_back(command);
}

}  // extern "C"
