// Each profile has one revision in IndexedDB. Its unpredictable key lets a
// writer replace exactly the revision it loaded. The unique profile index
// aborts the whole transaction if another tab has already replaced that key.
const DATABASE = "snail-mail";
const FILES = "files";
const REVISIONS = "revisions";

function newRevision(profile) {
  return { profile, id: crypto.getRandomValues(new Uint32Array(4)).join("-") };
}

function request(r) {
  return new Promise((resolve, reject) => {
    r.onsuccess = () => resolve(r.result);
    r.onerror = () => reject(r.error);
  });
}

function equal(a, b) {
  return a === b || (a && b && a.length === b.length && a.every((v, i) => v === b[i]));
}

export async function openSaves(profile, reset, reportError) {
  const open = indexedDB.open(DATABASE, 2);
  open.onupgradeneeded = ({ oldVersion }) => {
    if (oldVersion === 0) open.result.createObjectStore(FILES);
    open.result.createObjectStore(REVISIONS, { keyPath: "id" }).createIndex("profile", "profile", { unique: true });
  };
  open.onblocked = () => reportError(new Error("Close other Snail Mail tabs to update the save database."));
  const db = await request(open);
  db.onversionchange = () => db.close();
  const initial = db.transaction([FILES, REVISIONS], "readwrite");
  const store = initial.objectStore(FILES);
  const revisions = initial.objectStore(REVISIONS);
  if (reset) {
    store.clear();
    revisions.clear();
    for (const name of ["original", "ultimate"]) revisions.add(newRevision(name));
  }
  const initialCommit = new Promise((resolve, reject) => {
    initial.oncomplete = resolve;
    initial.onabort = () => reject(initial.error);
  });
  let [keys, values, revision] = await Promise.all([
    request(store.getAllKeys()), request(store.getAll()), request(revisions.index("profile").getKey(profile)),
  ]);
  if (revision === undefined) {
    const first = newRevision(profile);
    revisions.add(first);
    revision = first.id;
  }
  await initialCommit;
  const files = new Map(keys.map((key, i) => [key, values[i]]));
  let pending = new Map();
  let stopped = false;

  function flush() {
    const changes = [...pending].filter(([name, value]) => !equal(value, files.get(name)));
    pending.clear();
    if (stopped || changes.length === 0) return;
    let transaction;
    try {
      // Queue every request synchronously so it can commit even if pagehide
      // discards this document before IndexedDB delivers any result events.
      transaction = db.transaction([FILES, REVISIONS], "readwrite");
      transaction.onabort = () => {
        if (stopped) return;
        stopped = true;
        const error = transaction.error;
        reportError(error?.name === "ConstraintError"
          ? new Error("Another tab saved or reset this game. Reload to continue from its save.")
          : error ?? new Error("Save transaction aborted."));
      };
      const revisions = transaction.objectStore(REVISIONS);
      revisions.delete(revision);
      const next = newRevision(profile);
      revisions.add(next);
      const store = transaction.objectStore(FILES);
      for (const [name, value] of changes) {
        if (value === undefined) store.delete(name);
        else store.put(value, name);
      }
      transaction.commit();
      // Later saves refer to this transaction's token. If it aborts, their
      // delete cannot remove the surviving revision and they also abort.
      revision = next.id;
      for (const [name, value] of changes) {
        if (value === undefined) files.delete(name);
        else files.set(name, value);
      }
    } catch (error) {
      stopped = true;
      transaction?.abort();
      reportError(error);
    }
  }

  return {
    files,
    flush,
    write(name, bytes) {
      if (stopped) return;
      if (!pending.size) queueMicrotask(flush);
      pending.set(name, bytes?.slice());
    },
  };
}
