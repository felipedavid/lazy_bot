if not exist ..\bin\ (
    mkdir ..\bin\
)
cl.exe /Zi /LD /EHsc main.cpp -o ..\bin\lazy_bot.dll /link user32.lib
