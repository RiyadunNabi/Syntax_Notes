To instantly set Firefox as your system-wide default PDF viewer using the terminal, open your terminal (Super + T) and run this command:

xdg-mime default firefox.desktop application/pdf

## Verification
To verify that the change worked, run:
```bash
xdg-mime query default application/pdf
```

It should output firefox.desktop.
## Note for Flatpak Users
If you installed Firefox via Flathub (Flatpak) instead of the default Pop!_OS package, use this command instead:

xdg-mime default org.mozilla.firefox.desktop application/pdf

If you are interested, let me know:

* Did the command throw an error?
* Does clicking a PDF now successfully trigger Firefox?

I can help you troubleshoot if your desktop environment ignores the rule!

