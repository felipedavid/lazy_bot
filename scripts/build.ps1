mkdir build -Force > $null
cl /LD src/main.c /Fo:build\ /Fe:build\lazy_bot.dll user32.lib