// Drive the real browser reactor with null presenters for mode/render probes.
import { readFile } from 'node:fs/promises';
import { WASI } from 'node:wasi';

// Field offsets in the port's layout, from the test (tests/conftest.py).
export const LAYOUT = JSON.parse(process.env.SNAIL_LAYOUT);

// Start the reactor in a profile (1 Ultimate, 0 Original).
export async function startGame(wasm, presenter = {}, ultimate = 1) {
  const wasi = new WASI({version: 'preview1', args: [], env: {...process.env, PWD: process.cwd()}, preopens: {'/': process.cwd()}});
  const module = await WebAssembly.compile(await readFile(wasm));
  const imports = wasi.getImportObject();
  imports.snail = Object.fromEntries(WebAssembly.Module.imports(module)
    .filter(i => i.module === 'snail').map(i => [i.name, presenter[i.name] ?? (() => 0)]));
  const instance = await WebAssembly.instantiate(module, imports);
  wasi.initialize(instance);
  const e = instance.exports;
  presenter.ready?.(e);
  e.snail_set_profile(ultimate);
  if (!e.snail_start(0)) throw Error('game startup failed');
  return e;
}

// Opens Pro 1 ("Pros Only"), found by its name and its 25 segments; a test
// that rewrites the course passes its own segment count.
export async function openMobileGame(wasm, presenter = {}, segments = 50) {
  const e = await startGame(wasm, presenter);
  const step = (n = 5) => { for (let i=0; i<n; ++i) e.snail_frame(0.4); };
  const click = (x,y) => {
    e.snail_pointer(x,y);e.snail_frame(1/60);
    e.snail_button(0,1);e.snail_frame(1/60);e.snail_button(0,0);step();
  };
  step(25);e.snail_key(1,1);e.snail_frame(1/60);e.snail_key(1,0);step();
  click(345,112);click(345,240);click(289,287);step();click(320,300);step(1);
  let m=Buffer.from(e.memory.buffer), root;
  const needle=Buffer.from('Pros Only\0');
  // Its 25 listed segments, each after a Padding, as Android lays them.
  for(let p=m.indexOf(needle);p>=0;p=m.indexOf(needle,p+1)) {
    const candidate=p-LAYOUT.subgame-LAYOUT.level_definition-LAYOUT.level_display_name;
    if(candidate>0 && m.readInt32LE(candidate+LAYOUT.subgame+0x3c)===2
        && m.readInt32LE(candidate+LAYOUT.subgame+LAYOUT.level_definition)===segments) root=candidate;
  }
  if(!root) throw Error('Pro 1 did not enter gameplay');
  return {e, root, sub:root+LAYOUT.subgame, memory:()=>Buffer.from(e.memory.buffer), step, click};
}
