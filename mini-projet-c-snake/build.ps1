param(
    [switch]$Run,
    [switch]$Sanitize
)

$ErrorActionPreference = 'Stop'

$root = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $root

$ucrtBin = "C:\msys64\ucrt64\bin"
$ucrtGcc = Join-Path $ucrtBin "gcc.exe"

if (-not (Test-Path $ucrtGcc)) {
    Write-Error "GCC UCRT64 introuvable. Installe MSYS2 puis: pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-raylib"
    exit 1
}

# Force l'outil de compilation UCRT64 pour eviter les conflits avec d'autres GCC.
$env:Path = "$ucrtBin;$env:Path"

$raylibHeaderCandidates = @(
    "C:\msys64\ucrt64\include\raylib.h",
    "C:\msys64\mingw64\include\raylib.h",
    "C:\MinGW\include\raylib.h"
)

$raylibFound = $false
foreach ($candidate in $raylibHeaderCandidates) {
    if (Test-Path $candidate) {
        $raylibFound = $true
        break
    }
}

if (-not $raylibFound) {
    Write-Host "Raylib semble absente (raylib.h non trouvee)." -ForegroundColor Yellow
    Write-Host "Installe MSYS2 puis: pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-raylib" -ForegroundColor Yellow
    exit 1
}

$flags = @('-std=c11', '-Wall', '-Wextra', '-Wpedantic', '-Iinclude')
if ($Sanitize) {
    $flags += @('-fsanitize=address', '-fno-omit-frame-pointer')
}

$src = @('src/main.c', 'src/game.c')
$out = 'snake.exe'
$libs = @('-lraylib', '-lopengl32', '-lgdi32', '-lwinmm')

$cmd = @($ucrtGcc) + $flags + $src + @('-o', $out) + $libs
Write-Host "Compilation..." -ForegroundColor Cyan
Write-Host ($cmd -join ' ')

& $ucrtGcc @flags @src -o $out @libs
if ($LASTEXITCODE -ne 0) {
    Write-Error "Compilation echouee."
    exit $LASTEXITCODE
}

# Copie locale des DLL runtime usuelles pour lancer snake.exe meme hors shell MSYS2.
$runtimeDlls = @(
    "libraylib.dll",
    "glfw3.dll",
    "libgcc_s_seh-1.dll",
    "libwinpthread-1.dll",
    "libstdc++-6.dll"
)

foreach ($dll in $runtimeDlls) {
    $srcDll = Join-Path $ucrtBin $dll
    if (Test-Path $srcDll) {
        Copy-Item $srcDll (Join-Path $root $dll) -Force
    }
}

Write-Host "Build OK: snake.exe" -ForegroundColor Green

if ($Run) {
    Write-Host "Lancement du jeu..." -ForegroundColor Cyan
    .\snake.exe
}
