// Files the game writes (SnailMail.cfg, ScoreA/B/C.dat), kept in IndexedDB so
// progress, options and high scores survive reloads, as they did on disk.

const DATABASE = "snail-mail";
const STORE = "files";

function request(r) {
  return new Promise((resolve, reject) => {
    r.onsuccess = () => resolve(r.result);
    r.onerror = () => reject(r.error);
  });
}

export async function openSaves() {
  const open = indexedDB.open(DATABASE, 1);
  open.onupgradeneeded = () => open.result.createObjectStore(STORE);
  const db = await request(open);
  const store = (mode) => db.transaction(STORE, mode).objectStore(STORE);
  return {
    // [name, bytes] pairs saved earlier.
    async load() {
      const [names, contents] = await Promise.all([request(store("readonly").getAllKeys()), request(store("readonly").getAll())]);
      return names.map((name, i) => [name, contents[i]]);
    },
    save(name, bytes) {
      return request(store("readwrite").put(bytes, name));
    },
    clear() {
      return request(store("readwrite").clear());
    },
  };
}
