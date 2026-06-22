# Windows-Style Clipboard History on Pop!_OS (COSMIC + Wayland)

A working setup that brings Windows' `Super+V` clipboard history experience to Pop!_OS — copy multiple things, press a key, pick one, and it auto-pastes.

> **System:** Pop!_OS, COSMIC desktop, Wayland — tested June 2026

---

## What We're Using

| Tool | Purpose |
|---|---|
| `cliphist` | Stores clipboard history |
| `rofi` | Popup menu to browse/select history |
| `wl-clipboard` (`wl-copy`) | Writes selected item back to clipboard |
| `wtype` | Simulates `Ctrl+V` keypress (Wayland-safe) |
| A custom shell script | Glues everything together |
| `.desktop` autostart file | Keeps clipboard watcher running after reboot |

---

## Step 1 — Install Everything

```bash
sudo apt install cliphist rofi wtype
```

---

## Step 2 — Test the Clipboard Watcher

Run this once manually to confirm it works:

```bash
wl-paste --watch cliphist store &
```

Copy a few different things (text), then check:

```bash
cliphist list
```

You should see your copied items listed.

---

## Step 3 — Create the Paste Script

```bash
mkdir -p ~/.local/bin
nano ~/.local/bin/cosmic-paste.sh
```

Paste this inside:

```bash
#!/bin/bash
# 1. Open clipboard history in rofi, capture selection
SELECTION=$(cliphist list | rofi -dmenu -p "Clipboard" -config /dev/null)

# 2. If nothing selected (cancelled), exit
if [ -z "$SELECTION" ]; then
    exit 0
fi

# 3. Decode and copy the selected item back to clipboard
echo "$SELECTION" | cliphist decode | wl-copy

# 4. Small delay to let rofi window close
sleep 0.15

# 5. Simulate Ctrl+V to auto-paste
wtype -M ctrl v -m ctrl
```

Save: `Ctrl+O` → Enter → `Ctrl+X`

Make it executable:

```bash
chmod +x ~/.local/bin/cosmic-paste.sh
```

Test it:

```bash
~/.local/bin/cosmic-paste.sh
```

A rofi popup should appear showing your clipboard history.

---

## Step 4 — Bind to Super+V

1. **Settings → Keyboard → View and Customize Shortcuts → Custom Shortcuts**
2. Click **+**
3. Fill in:
   - **Name:** `Instant Clipboard`
   - **Command:** `/home/riyadunnabi/.local/bin/cosmic-paste.sh`
   - **Shortcut:** Press `Super+V`
4. Click **Add**

Now `Super+V` anywhere opens the popup. Selecting an item auto-pastes it directly — no manual `Ctrl+V` needed.

---

## Step 5 — Make the Watcher Survive Reboot

COSMIC's Startup Applications panel only toggles existing `.desktop` apps — it doesn't let you add raw commands directly. So we create our own `.desktop` file:

```bash
mkdir -p ~/.config/autostart
nano ~/.config/autostart/cliphist-watcher.desktop
```

Paste this inside:

```ini
[Desktop Entry]
Type=Application
Exec=wl-paste --watch cliphist store
Hidden=false
NoDisplay=false
X-GNOME-Autostart-enabled=true
Name=Cliphist Watcher
Comment=Watches clipboard for cliphist history
```

Save: `Ctrl+O` → Enter → `Ctrl+X`

Go to **Settings → Startup Applications** and confirm **"Cliphist Watcher"** is toggled **ON**.

---

## How It Works (Full Flow)

```
Press Super+V
     ↓
rofi opens showing cliphist history
     ↓
Select an item (double-click or Enter)
     ↓
Item is decoded and copied to clipboard (wl-copy)
     ↓
rofi closes
     ↓
wtype simulates Ctrl+V
     ↓
Item pastes into the active app
```

---

## Known Issues (Unresolved, as of June 2026)

These are **not fixed yet** — documented for future reference:

| Issue | Details |
|---|---|
| **No image preview** | Image clipboard items show as raw binary data in the rofi list instead of a thumbnail |
| **Escape doesn't close popup** | Pressing `Escape` (or any keyboard input) does not reach the rofi window — confirmed it's a **COSMIC compositor keyboard-focus bug**, not a rofi config issue. Typing into the rofi search filter also doesn't work. Only mouse clicks (selecting an item) close the popup |
| **No cancel button** | Because keyboard input doesn't reach rofi, there's no way to back out of the popup without selecting an item |
| **No delete option** | No way to remove individual items from history through the UI |
| **No pin/favorites** | No way to mark items as permanent — `cliphist` has no native pinning support |

### Root Cause Summary

Confirmed through testing: COSMIC's Wayland compositor does not forward keyboard focus to the rofi window. Mouse input works (clicking/selecting), but no keyboard input (typing, Escape, custom keybinds) reaches rofi at all. This is a COSMIC-specific compositor limitation, not something fixable via rofi flags or config.

### Planned Fix

Build a custom GTK4-based popup (project name: **WayClip**) instead of relying on rofi, since GTK apps integrate natively with COSMIC's window management (COSMIC itself is built on GTK/libcosmic foundations). This would natively support:
- Working Escape/cancel
- Image thumbnails
- Delete button per item
- Pin to favorites (separate persistent list)

See the separate `wayland-clipboard-manager-spec.md` document for the full project specification.

---

## Quick Reference — Files Created

```
~/.local/bin/cosmic-paste.sh              # Main paste script
~/.config/autostart/cliphist-watcher.desktop   # Autostart entry for clipboard watcher
```

---

*Setup tested on Pop!_OS, COSMIC desktop, Wayland session. Core paste functionality works; UI polish issues remain open due to COSMIC compositor limitations.*



---
---
---
## Clipboard History Size Management

Default behavior stores indefinitely. To cap history:

**Edit the autostart file:**
```bash
nano ~/.config/autostart/cliphist-watcher.desktop
```

Change `Exec` line to:
```ini
Exec=wl-paste --watch cliphist store --max-items 200
```

Restart the watcher:
```bash
pkill -f "wl-paste --watch"
wl-paste --watch cliphist store --max-items 200 &
```

**To wipe existing history:**
```bash
cliphist wipe
```

> **Note:** Item IDs don't reset after a wipe — that's just cliphist's internal counter behavior, cosmetic only.

**Check DB size anytime:**
```bash
du -sh ~/.cache/cliphist/
```

DB location: `~/.cache/cliphist/db` (SQLite file). At 200 text items it stays well under 5MB.
