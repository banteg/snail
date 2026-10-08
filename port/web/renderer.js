// WebGL2 presenter for the emulated Direct3D 8 device (port/shell/
// render_backend.h). Draws arrive fully transformed in Direct3D conventions;
// this does the pixel stage: texture stage 0 (D3DTOP/D3DTA), alpha test, vertex
// fog, blending, depth and culling, with Direct3D's viewport and pixel centres.
//
// The game draws in 640x480 coordinates. setResolution renders them at a
// multiple of that instead (HiDPI): viewports scale, while the half-pixel
// offset stays half of an original pixel, so everything lands where it did.

const VERTEX_BYTES = 32;
const STATE_WORDS = 28; // RenderState, in 4-byte fields

const VERTEX_SHADER = `#version 300 es
layout(location = 0) in vec4 a_position;
layout(location = 1) in vec4 a_color;   // D3DCOLOR bytes: B, G, R, A
layout(location = 2) in vec2 a_uv;
layout(location = 3) in float a_fog;
uniform vec2 u_pixel;                    // half a pixel in NDC for the viewport
out vec4 v_color;
out vec2 v_uv;
out float v_fog;
void main() {
  vec4 p = a_position;
  // Direct3D clip z runs from 0 to w, and its pixel centres sit half a pixel
  // up and left of OpenGL's.
  gl_Position = vec4(p.x - u_pixel.x * p.w, p.y + u_pixel.y * p.w, 2.0 * p.z - p.w, p.w);
  v_color = a_color.bgra;
  v_uv = a_uv;
  v_fog = a_fog;
}`;

const FRAGMENT_SHADER = `#version 300 es
precision highp float;
in vec4 v_color;
in vec2 v_uv;
in float v_fog;
uniform sampler2D u_texture;
uniform bool u_has_texture;
uniform ivec3 u_color_op;  // D3DTOP, D3DTA, D3DTA
uniform ivec3 u_alpha_op;
uniform vec4 u_texture_factor;
uniform int u_alpha_func;  // D3DCMP, 0 when alpha testing is off
uniform float u_alpha_ref;
uniform bool u_fog;
uniform vec3 u_fog_color;
out vec4 color;

vec4 argument(int a, vec4 texel) {
  int source = a & 7;
  vec4 v = source == 2 ? texel : source == 3 ? u_texture_factor : v_color;  // DIFFUSE and CURRENT at stage 0
  if ((a & 0x10) != 0) v = 1.0 - v;
  if ((a & 0x20) != 0) v = vec4(v.a);
  return v;
}

vec4 combine(ivec3 op, vec4 texel) {
  vec4 a = argument(op.y, texel), b = argument(op.z, texel);
  switch (op.x) {
    case 1: return v_color;                 // DISABLE
    case 2: return a;                       // SELECTARG1
    case 3: return b;                       // SELECTARG2
    case 4: return a * b;                   // MODULATE
    case 5: return 2.0 * a * b;
    case 6: return 4.0 * a * b;
    case 7: return a + b;                   // ADD
    case 8: return a + b - 0.5;
    case 9: return 2.0 * (a + b - 0.5);
    case 10: return a - b;                  // SUBTRACT
    case 11: return a + b - a * b;          // ADDSMOOTH
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

void main() {
  // An unset texture samples as opaque black.
  vec4 texel = u_has_texture ? texture(u_texture, v_uv) : vec4(0.0, 0.0, 0.0, 1.0);
  vec4 result;
  if (u_color_op.x == 1) {
    result = v_color;  // a disabled stage 0 disables texturing
  } else {
    result.rgb = combine(u_color_op, texel).rgb;
    result.a = combine(u_alpha_op, texel).a;
  }
  result = clamp(result, 0.0, 1.0);
  if (u_alpha_func != 0 && !passes(u_alpha_func, floor(result.a * 255.0 + 0.5), u_alpha_ref)) discard;
  if (u_fog) result.rgb = mix(u_fog_color, result.rgb, clamp(v_fog, 0.0, 1.0));
  color = result;
}`;

function compile(gl, type, source) {
  const shader = gl.createShader(type);
  gl.shaderSource(shader, source);
  gl.compileShader(shader);
  if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) throw new Error(gl.getShaderInfoLog(shader));
  return shader;
}

function argb(value) {
  return [((value >>> 16) & 255) / 255, ((value >>> 8) & 255) / 255, (value & 255) / 255, (value >>> 24) / 255];
}

export class Renderer {
  constructor(canvas) {
    const gl = canvas.getContext("webgl2", { antialias: false, alpha: false, depth: true, stencil: false });
    if (!gl) throw new Error("WebGL2 is not available");
    this.gl = gl;
    this.canvas = canvas;
    this.scale = canvas.width / 640;
    this.memory = null;
    this.textures = new Map();

    const program = gl.createProgram();
    gl.attachShader(program, compile(gl, gl.VERTEX_SHADER, VERTEX_SHADER));
    gl.attachShader(program, compile(gl, gl.FRAGMENT_SHADER, FRAGMENT_SHADER));
    gl.linkProgram(program);
    if (!gl.getProgramParameter(program, gl.LINK_STATUS)) throw new Error(gl.getProgramInfoLog(program));
    gl.useProgram(program);
    this.uniforms = {};
    for (const name of ["u_pixel", "u_texture", "u_has_texture", "u_color_op", "u_alpha_op", "u_texture_factor",
      "u_alpha_func", "u_alpha_ref", "u_fog", "u_fog_color"]) {
      this.uniforms[name] = gl.getUniformLocation(program, name);
    }
    gl.uniform1i(this.uniforms.u_texture, 0);

    const vao = gl.createVertexArray();
    gl.bindVertexArray(vao);
    this.buffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, this.buffer);
    gl.enableVertexAttribArray(0);
    gl.vertexAttribPointer(0, 4, gl.FLOAT, false, VERTEX_BYTES, 0);
    gl.enableVertexAttribArray(1);
    gl.vertexAttribPointer(1, 4, gl.UNSIGNED_BYTE, true, VERTEX_BYTES, 16);
    gl.enableVertexAttribArray(2);
    gl.vertexAttribPointer(2, 2, gl.FLOAT, false, VERTEX_BYTES, 20);
    gl.enableVertexAttribArray(3);
    gl.vertexAttribPointer(3, 1, gl.FLOAT, false, VERTEX_BYTES, 28);

    // D3DTADDRESS (1 wrap, 2 mirror, 3 clamp) for u and v: one sampler each.
    this.samplers = new Map();
    const modes = { 1: gl.REPEAT, 2: gl.MIRRORED_REPEAT, 3: gl.CLAMP_TO_EDGE, 4: gl.CLAMP_TO_EDGE };
    for (const u of [1, 2, 3, 4]) for (const v of [1, 2, 3, 4]) {
      const sampler = gl.createSampler();
      gl.samplerParameteri(sampler, gl.TEXTURE_WRAP_S, modes[u]);
      gl.samplerParameteri(sampler, gl.TEXTURE_WRAP_T, modes[v]);
      gl.samplerParameteri(sampler, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
      gl.samplerParameteri(sampler, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
      this.samplers.set(u * 8 + v, sampler);
    }
    gl.frontFace(gl.CW); // Direct3D's front faces are clockwise
  }

  bind(memory) {
    this.memory = memory;
  }

  // Backing store width in device pixels; 640 is the original resolution.
  setResolution(width) {
    const height = Math.round((width * 3) / 4);
    if (this.canvas.width === width && this.canvas.height === height) return;
    this.canvas.width = width;
    this.canvas.height = height;
    this.scale = width / 640;
  }

  state(pointer) {
    const words = new Int32Array(this.memory.buffer, pointer, STATE_WORDS);
    const floats = new Float32Array(this.memory.buffer, pointer, STATE_WORDS);
    return {
      texture: words[0],
      colorOp: [words[1], words[2], words[3]],
      alphaOp: [words[4], words[5], words[6]],
      textureFactor: words[7] >>> 0,
      addressU: words[8], addressV: words[9],
      alphaBlend: words[10], srcBlend: words[11], destBlend: words[12],
      alphaTest: words[13], alphaFunc: words[14], alphaRef: words[15],
      zEnable: words[16], zWrite: words[17], zFunc: words[18],
      cull: words[19],
      fog: words[20], fogColor: words[21] >>> 0,
      viewport: [words[22], words[23], words[24], words[25]],
      depthRange: [floats[26], floats[27]],
    };
  }

  applyViewport(state) {
    const gl = this.gl;
    const [x, y, width, height] = state.viewport;
    const k = this.scale;
    const box = [Math.round(x * k), Math.round(this.canvas.height - (y + height) * k), Math.round(width * k), Math.round(height * k)];
    gl.viewport(...box);
    gl.scissor(...box);
    gl.depthRange(state.depthRange[0], state.depthRange[1]);
    gl.uniform2f(this.uniforms.u_pixel, 1 / width, 1 / height); // half an original pixel, in NDC
  }

  imports() {
    const gl = this.gl;
    const blend = {
      1: gl.ZERO, 2: gl.ONE, 3: gl.SRC_COLOR, 4: gl.ONE_MINUS_SRC_COLOR, 5: gl.SRC_ALPHA,
      6: gl.ONE_MINUS_SRC_ALPHA, 7: gl.DST_ALPHA, 8: gl.ONE_MINUS_DST_ALPHA, 9: gl.DST_COLOR,
      10: gl.ONE_MINUS_DST_COLOR, 11: gl.SRC_ALPHA_SATURATE,
    };
    const compare = {
      1: gl.NEVER, 2: gl.LESS, 3: gl.EQUAL, 4: gl.LEQUAL, 5: gl.GREATER, 6: gl.NOTEQUAL, 7: gl.GEQUAL, 8: gl.ALWAYS,
    };
    return {
      texture_create: (id, width, height, pointer) => {
        const texture = gl.createTexture();
        gl.activeTexture(gl.TEXTURE0);
        gl.bindTexture(gl.TEXTURE_2D, texture);
        const pixels = new Uint8Array(this.memory.buffer, pointer, width * height * 4);
        gl.pixelStorei(gl.UNPACK_ALIGNMENT, 1);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA8, width, height, 0, gl.RGBA, gl.UNSIGNED_BYTE, pixels);
        this.textures.set(id, texture);
      },
      texture_destroy: (id) => {
        gl.deleteTexture(this.textures.get(id));
        this.textures.delete(id);
      },
      clear: (flags, color, z, pointer) => {
        const state = this.state(pointer);
        this.applyViewport(state);
        gl.enable(gl.SCISSOR_TEST);
        let mask = 0;
        if (flags & 1) {
          const [r, g, b, a] = argb(color >>> 0);
          gl.clearColor(r, g, b, a);
          gl.colorMask(true, true, true, true);
          mask |= gl.COLOR_BUFFER_BIT;
        }
        if (flags & 2) {
          gl.clearDepth(z);
          gl.depthMask(true);
          mask |= gl.DEPTH_BUFFER_BIT;
        }
        gl.clear(mask);
        gl.disable(gl.SCISSOR_TEST);
      },
      draw: (primitive, pointer, count, statePointer) => {
        const s = this.state(statePointer);
        const u = this.uniforms;
        this.applyViewport(s);

        const texture = s.texture ? this.textures.get(s.texture) : null;
        gl.activeTexture(gl.TEXTURE0);
        gl.bindTexture(gl.TEXTURE_2D, texture ?? null);
        gl.bindSampler(0, this.samplers.get((s.addressU || 1) * 8 + (s.addressV || 1)) ?? null);
        gl.uniform1i(u.u_has_texture, texture ? 1 : 0);
        gl.uniform3i(u.u_color_op, ...s.colorOp);
        gl.uniform3i(u.u_alpha_op, ...s.alphaOp);
        gl.uniform4f(u.u_texture_factor, ...argb(s.textureFactor));
        gl.uniform1i(u.u_alpha_func, s.alphaTest ? s.alphaFunc : 0);
        gl.uniform1f(u.u_alpha_ref, s.alphaRef & 255);
        gl.uniform1i(u.u_fog, s.fog ? 1 : 0);
        gl.uniform3f(u.u_fog_color, ...argb(s.fogColor).slice(0, 3));

        if (s.alphaBlend) {
          gl.enable(gl.BLEND);
          gl.blendFunc(blend[s.srcBlend] ?? gl.ONE, blend[s.destBlend] ?? gl.ZERO);
        } else {
          gl.disable(gl.BLEND);
        }
        if (s.zEnable) {
          gl.enable(gl.DEPTH_TEST);
          gl.depthFunc(compare[s.zFunc] ?? gl.LEQUAL);
        } else {
          gl.disable(gl.DEPTH_TEST);
        }
        gl.depthMask(!!s.zWrite);
        if (s.cull === 2 || s.cull === 3) {
          gl.enable(gl.CULL_FACE);
          gl.cullFace(s.cull === 3 ? gl.BACK : gl.FRONT); // D3DCULL_CCW culls counter-clockwise (back) faces
        } else {
          gl.disable(gl.CULL_FACE);
        }

        gl.bindBuffer(gl.ARRAY_BUFFER, this.buffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Uint8Array(this.memory.buffer, pointer, count * VERTEX_BYTES), gl.STREAM_DRAW);
        gl.drawArrays(primitive === 1 ? gl.LINES : gl.TRIANGLES, 0, count);
      },
    };
  }
}
