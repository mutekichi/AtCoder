# Check if the correct number of arguments is provided
if ($args.Length -lt 2) {
    Write-Host "Usage: .\mkarcdir.ps1 directory_name content_file"
    exit 1
}

# Store the directory name and content file name in variables
$dirName = $args[0]
$contentFile = $args[1]

# Check if the content file exists
if (-not (Test-Path -Path $contentFile)) {
    Write-Host "Error: Content file '$contentFile' does not exist."
    exit 1
}

# Check if the ARC directory exists, if not, create it
if (-not (Test-Path -Path "./ARC")) {
    New-Item -ItemType Directory -Path "./ARC"
}

# Create the subdirectory with the specified directory name
New-Item -ItemType Directory -Path "./ARC/$dirName"

# Read the content from the specified file
$content = Get-Content -Path $contentFile

# Create files a.cpp to f.cpp and write the content into them
'a.cpp', 'b.cpp', 'c.cpp', 'd.cpp', 'e.cpp', 'f.cpp', 'g.cpp' | ForEach-Object {
    $filePath = "./ARC/$dirName/$_"
    New-Item -ItemType File -Path $filePath -Force
    Set-Content -Path $filePath -Value $content
}

Write-Host "Directory './ARC/$dirName' and files a.cpp to f.cpp have been created with the content from '$contentFile'."
