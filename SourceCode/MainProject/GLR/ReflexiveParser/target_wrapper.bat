@echo off
SetLocal EnableDelayedExpansion
(set PATH=C:\Qt\5.14.2\msvc2017\bin;!PATH!)
if defined QT_PLUGIN_PATH (
    set QT_PLUGIN_PATH=C:\Qt\5.14.2\msvc2017\plugins;!QT_PLUGIN_PATH!
) else (
    set QT_PLUGIN_PATH=C:\Qt\5.14.2\msvc2017\plugins
)
%*
EndLocal
