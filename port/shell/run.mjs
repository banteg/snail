// Run the headless port under Node's WASI, with the working directory preopened
// (it must contain SnailMail.dat). Usage: node shell/run.mjs zig-out/bin/snail.wasm [frames]
import { readFile } from "node:fs/promises";
import { WASI } from "node:wasi";
import { argv, cwd, exit } from "node:process";

const [wasmPath, ...args] = argv.slice(2);
const wasi = new WASI({ version: "preview1", args: ["snail", ...args], preopens: { ".": cwd() }, returnOnExit: true });
const module = await WebAssembly.compile(await readFile(wasmPath));
const instance = await WebAssembly.instantiate(module, wasi.getImportObject());
exit(wasi.start(instance));
