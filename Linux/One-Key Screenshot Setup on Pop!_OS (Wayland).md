# One-Key Screenshot Setup on Pop!_OS (Wayland)

A beginner-friendly guide to setting up a screenshot tool that:
- Activates with a **single key press**
- Lets you **drag to select** any area
- **Auto-saves** the screenshot to your PC
- **Auto-copies** to clipboard on release (ready to `Ctrl+V`)

> **System:** Pop!_OS (Wayland) — HP Victus, tested June 2026

---

## What We're Using

| Tool | Purpose |
|---|---|
| `flameshot` | The screenshot tool with selection UI |
| `wl-clipboard` | Wayland-native clipboard manager |
| A custom shell script | Glues flameshot + clipboard together |
| GNOME Custom Shortcut | Binds it all to a single key |

---

## Why Not Just Use the Default Screenshot?

Pop!_OS's built-in screenshot (`PrtSc`) doesn't auto-copy region screenshots to clipboard reliably on Wayland. This setup fixes that — one key, drag, release, done.

---

## Step 1 — Install the Tools

Open your **Terminal** (Super key → type "Terminal" → Enter) and run these one by one:

```bash
sudo apt install flameshot
```

```bash
sudo apt install wl-clipboard
```

> `sudo` means "run as admin." It will ask for your password — type it (nothing appears while typing, that's normal) and hit Enter.

---

## Step 2 — Create the Folders

```bash
mkdir -p ~/Pictures/Screenshots
```
> This is where your screenshots will be saved.

```bash
mkdir -p ~/.local/bin
```
> This is where your personal scripts live. The `~` means your home folder.

---

## Step 3 — Create the Script

This script is the brain of the operation. It runs flameshot, waits for you to select an area, then copies the result to clipboard.

**Open the script file in nano (a terminal text editor):**

```bash
nano ~/.local/bin/flameshot-auto.sh
```

Your terminal will change to a text editor screen. **Paste this inside:**

```bash
#!/bin/bash
FILE=$(XDG_CURRENT_DESKTOP=GNOME flameshot gui --accept-on-select --path ~/Pictures/Screenshots 2>&1 | grep "Capture saved" | awk '{print $NF}')
wl-copy < "$FILE"
```

**What each line does:**
- `#!/bin/bash` — tells Linux this is a runnable script
- `XDG_CURRENT_DESKTOP=GNOME` — tells flameshot it's running on GNOME (needed for Wayland)
- `flameshot gui --accept-on-select` — opens selection mode, auto-accepts when you release
- `--path ~/Pictures/Screenshots` — saves the file there
- `wl-copy < "$FILE"` — copies the saved image to Wayland clipboard

**Save and exit nano:**
- `Ctrl+O` → press Enter (saves the file)
- `Ctrl+X` (exits nano)

---

## Step 4 — Make the Script Executable

By default, a new file is just text. This command gives it permission to actually run:

```bash
chmod +x ~/.local/bin/flameshot-auto.sh
```

---

## Step 5 — Test It

```bash
~/.local/bin/flameshot-auto.sh
```

A crosshair/selection overlay should appear. Drag an area, release — you should see a notification saying saved + copied. Try `Ctrl+V` somewhere to confirm clipboard works.

---

## Step 6 — Bind to a Key (PrtSc or any key)

1. Open **Settings**
2. Go to **Keyboard → View and Customize Shortcuts**
3. Scroll to the bottom → **Custom Shortcuts** → click **+**
4. Fill in:
   - **Name:** `Screenshot Select`
   - **Command:** `/home/riyadunnabi/.local/bin/flameshot-auto.sh`
   - **Shortcut:** Click the field → press `PrtSc` (or any key you want)
5. Click **Add**

> Replace `riyadunnabi` with your actual username if different.

---

## How It Works (Full Flow)

```
Press PrtSc
     ↓
flameshot opens in selection mode
     ↓
Drag with touchpad to select area
     ↓
Lift finger → selection released
     ↓
Screenshot auto-saved to ~/Pictures/Screenshots/
     ↓
Image copied to Wayland clipboard
     ↓
Ctrl+V works anywhere
```

---

## Troubleshooting

**Flameshot says "Unable to detect desktop environment"**
Run with `XDG_CURRENT_DESKTOP=GNOME` prefix — already handled inside the script.

**`grim` approach doesn't work**
Pop!_OS uses GNOME's Mutter compositor which doesn't support `wlr-screencopy`. Stick with flameshot.

**Clipboard is empty after screenshot**
Make sure `wl-clipboard` is installed: `sudo apt install wl-clipboard`

**Script doesn't run**
Make sure it's executable: `chmod +x ~/.local/bin/flameshot-auto.sh`

---

## Screenshots Are Saved At

```
~/Pictures/Screenshots/
```

Files are named by date and time, e.g. `2026-06-11_08-03.png`.

---

*Setup tested on Pop!_OS 22.04 LTS with Wayland session.*
