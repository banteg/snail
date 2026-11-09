// Run the headless port under Node's WASI. The working directory must contain
// SnailMail.dat. The file system root is preopened and the program starts in
// $PWD, so paths work as in a native shell. Usage: node shell/run.mjs zig-out/bin/snail.wasm [snail options]
import { readFile } from "node:fs/promises";
import { WASI } from "node:wasi";
import { argv, cwd, exit } from "node:process";

const [wasmPath, ...args] = argv.slice(2);
// WASI writes directly to these descriptors. Node normally makes pipes
// nonblocking; a short write followed by EAGAIN loses the rest of a libc flush.
for (const stream of [process.stdout, process.stderr]) {
  if (!stream.isTTY) stream._handle?.setBlocking(true);
}
const wasi = new WASI({ version: "preview1", args: ["snail", ...args], env: { ...process.env, PWD: cwd() }, preopens: { "/": "/" }, returnOnExit: true });
const module = await WebAssembly.compile(await readFile(wasmPath));
const instance = await WebAssembly.instantiate(module, wasi.getImportObject());
exit(wasi.start(instance));
