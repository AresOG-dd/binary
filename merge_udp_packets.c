# Define the path to your local repository
$repoDir = "C:\path\to\your\repository"  # Adjust this path to your local GitHub repository

# Define the output file where the merged content will be saved
$outputFile = "C:\path\to\merged_udp_packets.bin"  # Adjust this to where you want the output file

# Open the output file for writing
$outputStream = [System.IO.File]::Create($outputFile)

# List of specific folders that contain the .bin files you want to merge
$folders = @(
    "upstream", "upstream1", "upstream2", "upstream3", "upstream4",
    "downstream", "downstream1", "downstream2", "downstream3", "downstream4"
)

# Function to merge .bin files from a specified directory
function Merge-BinFilesFromFolder {
    param (
        [string]$folderPath
    )

    # Get all .bin files in the folder (without subdirectories)
    $files = Get-ChildItem -Path $folderPath -Filter *.bin

    # Iterate over each .bin file and append its content to the output file
    foreach ($file in $files) {
        Write-Host "Merging file: $($file.FullName)"
        $fileStream = [System.IO.File]::OpenRead($file.FullName)
        $fileStream.CopyTo($outputStream)
        $fileStream.Close()
    }
}

# Iterate over each folder in the list and merge the .bin files from each folder
foreach ($folder in $folders) {
    $folderPath = Join-Path -Path $repoDir -ChildPath $folder

    if (Test-Path $folderPath) {
        Write-Host "Processing folder: $folderPath"
        Merge-BinFilesFromFolder -folderPath $folderPath
    } else {
        Write-Warning "Folder not found: $folderPath"
    }
}

# Close the output file stream
$outputStream.Close()

Write-Host "Merging completed! The merged file is saved as $outputFile"
