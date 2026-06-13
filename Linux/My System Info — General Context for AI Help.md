# My System Info — General Context for AI Help

Paste/mention relevant bits of this whenever asking an AI for help on this laptop.
Saves a lot of back-and-forth and wrong-tool suggestions.

## Hardware
- **Laptop:** HP Victus
- **CPU:** Intel Core (with integrated graphics)
- **GPU:** NVIDIA GeForce RTX (dual-GPU "Optimus"-style laptop)
- Mention dual-GPU for: graphics driver issues, external monitor/HDMI problems,
  performance/battery issues, gaming, video editing, ML/CUDA stuff.

## OS & Environment
- **OS:** Pop!_OS (Ubuntu-based, currently on Noble/24.04 base)
- **Session type:** Wayland (default) — **always mention this** for anything related to:
  - keyboard/mouse remapping
  - screen sharing / recording
  - multi-monitor setups
  - global hotkeys
  - any tool that says "X11 only"
  - Check anytime: `echo $XDG_SESSION_TYPE`
- **Desktop environment:** GNOME (or COSMIC if upgraded)
  - Check anytime: `echo $XDG_CURRENT_DESKTOP`
- **Package manager:** apt (standard Ubuntu/Debian)

## Things to Always Tell the AI

1. **OS + session type** — "I'm on Pop!_OS with Wayland" (or X11, if you ever switch)
2. **What you're trying to achieve**, not just the symptom — e.g. "I want X to happen" vs "Y is broken"
3. **Whether it's a laptop-specific issue** — dual-GPU, battery, trackpad, keyboard, fans, etc. — mention hardware
4. **If something used to work** — mention what changed (new OS, update, new app) and what worked before (e.g. "this worked fine on Windows")
5. **Disk space / install concerns** — if you're cautious about installing new packages, say so upfront so the AI suggests lightweight options or explains footprint
6. **Persistence requirements** — ask explicitly: "will this survive a reboot/logout?" especially on Wayland, since many old Linux fixes (xmodmap, X11 autostart hacks) silently fail to persist
7. **One step at a time** for troubleshooting — easier to verify each command's output before moving on

## Useful Diagnostic Commands to Run/Share When Asking for Help

```bash
# Session type (Wayland vs X11)
echo $XDG_SESSION_TYPE

# Desktop environment
echo $XDG_CURRENT_DESKTOP

# OS version
lsb_release -a

# GPU info
lspci | grep -E "VGA|3D"

# Disk usage of a specific tool
du -sh /usr/local/bin/<toolname>

# Check if a service is running
sudo systemctl status <servicename>
```

## Known Fixes Already Applied (so AI doesn't suggest redoing them)
- **Right Ctrl key fix:** done via `keyd` (kernel-level remapper), config at `/etc/keyd/default.conf`,
  rule: `rightcontrol = leftcontrol`. Built from source (not in apt). If reinstalling OS, needs rebuilding.
