// Port options: enhancements over the original, each switchable, kept per
// browser. "Original" turns them all off, "Enhanced" all on. A gear in the
// corner opens the panel; while it is open, keys stay out of the game.

const KEY = "snail-mail-settings";

export const OPTIONS = [
  { id: "hidpi", label: "Sharp rendering", detail: "Draw at the display's resolution instead of 640×480" },
  { id: "fullscreen", label: "Fullscreen", detail: "The game's Fullscreen option fills the screen" },
  { id: "trapMouse", label: "Trap the mouse", detail: "Keep the pointer in the game; Esc lets it go" },
];

export class Settings {
  constructor(onChange) {
    this.onChange = onChange;
    this.values = Object.fromEntries(OPTIONS.map((option) => [option.id, true]));
    try {
      Object.assign(this.values, JSON.parse(localStorage.getItem(KEY)) ?? {});
    } catch {}
    this.open = false;
    this.build();
  }

  get(id) {
    return this.values[id];
  }

  set(changes) {
    Object.assign(this.values, changes);
    try {
      localStorage.setItem(KEY, JSON.stringify(this.values));
    } catch {}
    this.sync();
    this.onChange(changes);
  }

  build() {
    const gear = document.createElement("button");
    gear.id = "gear";
    gear.type = "button";
    gear.title = "Port options";
    gear.textContent = "⚙";
    gear.addEventListener("click", () => this.toggle());

    const panel = document.createElement("div");
    panel.id = "options";
    panel.hidden = true;
    panel.innerHTML = `<h2>Port options</h2>
      <div class="presets"><button type="button" data-preset="0">Original</button><button type="button" data-preset="1">Enhanced</button></div>`;
    for (const option of OPTIONS) {
      const row = document.createElement("label");
      row.innerHTML = `<input type="checkbox" data-id="${option.id}"><span><b>${option.label}</b><small>${option.detail}</small></span>`;
      panel.append(row);
    }
    panel.addEventListener("change", (event) => this.set({ [event.target.dataset.id]: event.target.checked }));
    for (const button of panel.querySelectorAll("[data-preset]")) {
      const on = button.dataset.preset === "1";
      button.addEventListener("click", () => this.set(Object.fromEntries(OPTIONS.map((option) => [option.id, on]))));
    }
    document.body.append(gear, panel);
    this.panel = panel;
    this.sync();
  }

  sync() {
    for (const input of this.panel.querySelectorAll("input[data-id]")) input.checked = this.values[input.dataset.id];
    const all = OPTIONS.map((option) => this.values[option.id]);
    for (const button of this.panel.querySelectorAll("[data-preset]")) {
      button.classList.toggle("active", all.every((value) => value === (button.dataset.preset === "1")));
    }
  }

  toggle(open = !this.open) {
    this.open = open;
    this.panel.hidden = !open;
    if (open && document.pointerLockElement) document.exitPointerLock();
  }
}
