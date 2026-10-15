// Drive the real browser reactor with null presenters for mode/render probes.
import { readFile } from 'node:fs/promises';
import { WASI } from 'node:wasi';

export async function openMobileGame(wasm, presenter = {}) {
  const wasi = new WASI({version: 'preview1', args: [], env: {...process.env, PWD: process.cwd()}, preopens: {'/': process.cwd()}});
  const module = await WebAssembly.compile(await readFile(wasm));
  const imports = wasi.getImportObject();
  imports.snail = Object.fromEntries(WebAssembly.Module.imports(module)
    .filter(i => i.module === 'snail').map(i => [i.name, presenter[i.name] ?? (() => 0)]));
  const instance = await WebAssembly.instantiate(module, imports);
  wasi.initialize(instance);
  const e = instance.exports;
  presenter.ready?.(e);
  e.snail_set_extras(1);
  if (!e.snail_start(0)) throw Error('game startup failed');
  const step = (n = 5) => { for (let i=0; i<n; ++i) e.snail_frame(0.4); };
  const click = (x,y) => {
    e.snail_pointer(x,y);e.snail_frame(1/60);
    e.snail_button(0,1);e.snail_frame(1/60);e.snail_button(0,0);step();
  };
  step(25);e.snail_key(1,1);e.snail_frame(1/60);e.snail_key(1,0);step();
  click(345,112);click(345,383);click(289,287);step();click(320,300);step(1);
  let m=Buffer.from(e.memory.buffer), root;
  const needle=Buffer.from('Pros Only\0');
  for(let p=m.indexOf(needle);p>=0;p=m.indexOf(needle,p+1)) {
    const candidate=p-0x74618-0xa874-0x1a58dc;
    if(candidate>0 && m.readInt32LE(candidate+0x74618+0x3c)===2
        && m.readInt32LE(candidate+0x74618+0xa874)===25) root=candidate;
  }
  if(!root) throw Error('Pro 1 did not enter gameplay');
  return {e, root, sub:root+0x74618, memory:()=>Buffer.from(e.memory.buffer)};
}
