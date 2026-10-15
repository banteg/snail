// Port options, kept per browser. The gameplay profile picks what the game
// plays (shell/profile.h) and reloads the page; the comfort options change only
// how it is shown and controlled. A gear in the corner opens the panel; while
// it is open, keys stay out of the game and the pointer is free
// (`releasePointer`).

const KEY = "snail-mail-settings";

export const PROFILES = [
  { id: "original", label: "Original", detail: "The 2004 PC release as shipped, bugs included" },
  { id: "ultimate", label: "Ultimate", detail: "Mobile courses, rules and Pro-Challenge, with the original's bugs fixed" },
];

export const OPTIONS = [
  { id: "hidpi", label: "Sharp rendering", detail: "Draw at the display's resolution instead of 640×480" },
  { id: "fullscreen", label: "Fullscreen", detail: "The game's Fullscreen option fills the screen" },
  { id: "trapMouse", label: "Trap the mouse", detail: "Keep the pointer in the game; Esc lets it go" },
];

export class Settings {
  constructor(onChange, releasePointer) {
    this.onChange = onChange;
    this.releasePointer = releasePointer;
    this.values = { profile: "ultimate", ...Object.fromEntries(OPTIONS.map((option) => [option.id, true])) };
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
    panel.innerHTML = `<h2>Gameplay</h2>
      <div class="presets">${PROFILES.map((profile) => `<button type="button" data-profile="${profile.id}">${profile.label}</button>`).join("")}</div>
      <small class="profile-detail"></small>
      <h2>Comfort</h2>`;
    for (const option of OPTIONS) {
      const row = document.createElement("label");
      row.innerHTML = `<input type="checkbox" data-id="${option.id}"><span><b>${option.label}</b><small>${option.detail}</small></span>`;
      panel.append(row);
    }
    panel.addEventListener("change", (event) => this.set({ [event.target.dataset.id]: event.target.checked }));
    for (const button of panel.querySelectorAll("[data-profile]")) {
      button.addEventListener("click", () => {
        if (button.dataset.profile !== this.values.profile) this.set({ profile: button.dataset.profile });
      });
    }
    document.body.append(gear, panel);
    this.panel = panel;
    this.sync();
  }

  sync() {
    for (const input of this.panel.querySelectorAll("input[data-id]")) input.checked = this.values[input.dataset.id];
    for (const button of this.panel.querySelectorAll("[data-profile]")) {
      button.classList.toggle("active", button.dataset.profile === this.values.profile);
    }
    this.panel.querySelector(".profile-detail").textContent = PROFILES.find((profile) => profile.id === this.values.profile).detail;
  }

  toggle(open = !this.open) {
    this.open = open;
    this.panel.hidden = !open;
    if (open) this.releasePointer();
  }
}
