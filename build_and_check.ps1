$ErrorActionPreference = "Stop"
$msbuild = Get-Command MSBuild.exe -ErrorAction SilentlyContinue
if (-not $msbuild) {
    throw "Запусти цей файл з Developer PowerShell for Visual Studio або збудуй SPL_Lab3.sln у Rider."
}
& $msbuild.Source "$PSScriptRoot\SPL_Lab3.sln" /p:Configuration=Debug /p:Platform=x64 /verbosity:minimal /nologo
if ($LASTEXITCODE -ne 0) { throw "Build failed" }
foreach ($name in @("Cpp", "Flex")) {
    Push-Location "$PSScriptRoot\$name"
    try {
        & ".\bin\Debug\$name.exe"
        if ($LASTEXITCODE -ne 0) { throw "Run failed" }
    } finally { Pop-Location }
}
$cpp = Get-Content "$PSScriptRoot\output_cpp.txt" -Raw
$flex = Get-Content "$PSScriptRoot\output_flex.txt" -Raw
if ($cpp -cne $flex) { throw "Outputs differ" }
Write-Host "OK: C++ and Flex outputs are equal"
