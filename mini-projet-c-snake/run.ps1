powershell -ExecutionPolicy Bypass -File .\mini-projet-c-snake\run.ps1$ErrorActionPreference = 'Stop'

$root = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $root

powershell -ExecutionPolicy Bypass -File .\build.ps1
if ($LASTEXITCODE -ne 0) {
    Write-Error "Build echoue, lancement annule."
    exit $LASTEXITCODE
}

Start-Process .\snake.exe
Write-Host "Snake lance." -ForegroundColor Green
