# 🐒 Monkeybrew

Monkeybrew is a lightweight, Homebrew-inspired package manager written in C.  
Fast. Minimal. Easy to extend.

---

## 📥 Install Monkeybrew

Paste this into your terminal:

```bash
sudo /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Monkeybrews/install/HEAD/install.sh)" -- global </dev/null
```

## ♻️ Uninstall Monkeybrew

To remove Monkeybrew completely, run the following command:

```bash
sudo /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Monkeybrews/install/HEAD/uninstall.sh)" -- global </dev/null
```

## 📦 What Does Monkeybrew Do?

Monkeybrew provides a clean, C-powered package management system using its own local package database.
Every package entry defines its source URL, checksum, build steps, and metadata — allowing Monkeybrew to install software reliably and reproducibly.

## 📜 Monkeybrew Cheatsheet

`mbrew install <package>` : installs the current package specified.

> [!NOTE]
> make sure that the package is in the monkeybrew database!

** new commands comming soon! **
