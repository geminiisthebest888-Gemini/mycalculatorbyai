# Code Review Script - Advanced Version
# Usage:
#   .\code-review.ps1              - Review uncommitted changes
#   .\code-review.ps1 HEAD~1      - Review last commit
#   .\code-review.ps1 <commit>     - Review specific commit
#   .\code-review.ps1 main..HEAD   - Review all commits since main

param(
    [string]$Target = ""
)

$ErrorActionPreference = "Stop"

function Review-Commit {
    param([string]$Commit)
    
    Write-Host "=== Reviewing Commit: $Commit ===" -ForegroundColor Cyan
    
    # Get commit message
    $msg = git log -1 --format="%s%n%b" $Commit
    Write-Host "`nCommit Message:" -ForegroundColor Yellow
    Write-Host $msg
    
    # Get the diff
    Write-Host "`n=== Diff ===" -ForegroundColor Yellow
    git show $Commit --format="" --patch
    
    # Get list of changed files
    Write-Host "`n=== Changed Files ===" -ForegroundColor Yellow
    git show $Commit --stat --format=""
}

function Review-Uncommitted {
    Write-Host "=== Reviewing Uncommitted Changes ===" -ForegroundColor Cyan
    
    # Check for uncommitted changes
    $status = git status --short
    if ($status) {
        Write-Host "`n=== Changed Files ===" -ForegroundColor Yellow
        $status

        Write-Host "`n=== Unstaged Diff ===" -ForegroundColor Yellow
        git diff

        Write-Host "`n=== Staged Diff ===" -ForegroundColor Yellow
        git diff --cached
    } else {
        Write-Host "No uncommitted changes found." -ForegroundColor Green
    }

    # Check for untracked files
    $untracked = git status --short | Where-Object { $_ -match "^\?\?" }
    if ($untracked) {
        Write-Host "`n=== Untracked (New) Files ===" -ForegroundColor Yellow
        $untracked | ForEach-Object { 
            $file = $_ -replace "^\?\? ", ""
            Write-Host "  $file"
        }
    }
}

# Main logic
if ($Target -eq "") {
    # No target - review uncommitted
    Review-Uncommitted
} elseif ($Target -match "\.\.") {
    # Range review (e.g., main..HEAD)
    Write-Host "=== Reviewing commits: $Target ===" -ForegroundColor Cyan
    git log --oneline $Target
    Write-Host "`n=== Full Diff ===" -ForegroundColor Yellow
    git diff $Target
} else {
    # Single commit or HEAD~n
    Review-Commit $Target
}

Write-Host "`n=== Review Complete ===" -ForegroundColor Cyan
