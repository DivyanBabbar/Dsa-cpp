# Compiles every .cpp file into build\<folder>\<name>.exe (Windows / PowerShell, needs g++ e.g. MinGW-w64).
# Usage:  .\build_all.ps1
$ErrorActionPreference = "Stop"
$folders = Get-ChildItem -Directory | Where-Object { $_.Name -match '^\d\d_' }
foreach ($folder in $folders) {
    $outDir = Join-Path "build" $folder.Name
    New-Item -ItemType Directory -Force -Path $outDir | Out-Null
    foreach ($file in Get-ChildItem -Path $folder.FullName -Filter *.cpp) {
        $exe = Join-Path $outDir ($file.BaseName + ".exe")
        Write-Host "Compiling $($file.Name)"
        g++ -std=c++17 -Wall -Wextra $file.FullName -o $exe
    }
}
Write-Host "Done. Executables are in .\build"
