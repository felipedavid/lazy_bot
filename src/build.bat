if not exist ..\bin\ (
    mkdir ..\bin\
)
cl.exe /LD main.cpp memory_manager.cpp game\object_manager.cpp game\functions.cpp game\objects\object.cpp
