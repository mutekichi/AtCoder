# Check if the correct number of arguments is provided
if ($args.Length -lt 2) {
    Write-Host "Usage: .\abcg++.ps1 341 a"
    exit 1
}

# Store the arguments in variables
$number = $args[0]
$fileBaseName = $args[1]

# Construct the file paths
$cppFilePath = "./ABC/$number/$fileBaseName.cpp"
$outputExePath = "./bin/a.exe"

# Check if the cpp file exists
if (-not (Test-Path -Path $cppFilePath)) {
    Write-Host "Error: Source file '$cppFilePath' does not exist."
    exit 1
}

# Ensure the bin directory exists
if (-not (Test-Path -Path "./bin")) {
    New-Item -ItemType Directory -Path "./bin"
}

# Compile the cpp file to the exe file
$compileCommand = "g++ -std=c++14 -o $outputExePath $cppFilePath"
Invoke-Expression $compileCommand
