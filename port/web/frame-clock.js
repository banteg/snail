// rAF timestamps and performance.now() share a monotonic millisecond clock.
// Subtract them here, before the elapsed seconds cross the WASM float boundary.
export function scheduleFrames(onFrame) {
  let last = performance.now();
  const frame = (now) => {
    const elapsed = Math.min(1, (now - last) / 1000);
    last = now;
    if (onFrame(elapsed)) requestAnimationFrame(frame);
  };
  requestAnimationFrame(frame);
  return () => { last = performance.now(); };
}
