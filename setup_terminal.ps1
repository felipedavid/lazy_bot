pwsh.exe -NoExit -Command "& {
    Import-Module 'C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\Microsoft.VisualStudio.DevShell.dll';
    Enter-VsDevShell -InstanceId 1cb4bd8b -SkipAutomaticLocation -DevCmdArguments '-arch=x86 -host_arch=x64'
}"