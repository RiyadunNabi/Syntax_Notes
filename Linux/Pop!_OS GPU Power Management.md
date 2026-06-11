# Pop!_OS GPU Power Management

## Problem

Pop!_OS warns that the discrete GPU (NVIDIA) is active and reducing battery life. This happens when the system is locked to `nvidia` mode instead of using hybrid or integrated graphics.

## Diagnosis

Check the current graphics mode:

```bash
system76-power graphics
```

If the output is `nvidia`, the RTX is always on — draining battery even during light tasks.

## Fix

Switch to integrated (best battery) or hybrid (balanced) mode:

```bash
# Best battery — Intel iGPU only
sudo system76-power graphics integrated

# Balanced — Intel by default, NVIDIA on demand
sudo system76-power graphics hybrid

# Maximum GPU performance — NVIDIA always on
sudo system76-power graphics nvidia
```

Then reboot:

```bash
sudo reboot
```

After reboot, verify:

```bash
system76-power graphics
# Should output: integrated (or hybrid)
```

## Graphics Modes Summary

| Mode         | GPU Used                        | Best For                        |
|--------------|----------------------------------|----------------------------------|
| `integrated` | Intel iGPU only                 | Daily use, studying, battery life |
| `hybrid`     | Intel default, NVIDIA on demand | General use with occasional GPU  |
| `nvidia`     | NVIDIA always on                | Gaming, ML training              |

## Notes

- This applies to systems with `system76-power` installed (Pop!_OS default).
- A full reboot is required after changing graphics mode — log out is not enough.
- On HP Victus 15 (Intel i5 13th Gen + RTX 3050), `integrated` mode is recommended for campus/daily use.
