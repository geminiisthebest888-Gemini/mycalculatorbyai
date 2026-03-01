# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Windows MFC (Microsoft Foundation Classes) Calculator Application written in C++. Uses Visual Studio 2022 with MSBuild.

## Build Commands

```powershell
# Build the project
& 'C:\Program Files\Microsoft Visual Studio\18\Professional\MSBuild\Current\Bin\amd64\MSBuild.exe' 'C:\AIClaudeCode\mycalculatorbyai\MFCApplication1\MFCApplication1.slnx' /p:Configuration=Debug /p:Platform=x64

# Run the application
Start-Process 'C:\AIClaudeCode\mycalculatorbyai\MFCApplication1\x64\Debug\MFCApplication1.exe'
```

## Architecture

### Key Files

| File | Purpose |
|------|---------|
| `MFCApplication1/MFCApplication1.cpp` | Application entry point, GDI+ initialization |
| `MFCApplication1/MFCApplication1Dlg.cpp` | Calculator logic, UI event handlers |
| `MFCApplication1/MFCApplication1Dlg.h` | Dialog class + CGradientButton custom control |

### Code Organization

- **CGradientButton**: Custom MFC button with gradient fill and rounded corners using GDI+
- **CMFCApplication1Dlg**: Main calculator dialog implementing calculator state machine
- State variables: `m_dwFirstOperand`, `m_dwSecondOperand`, `m_strOperation`, `m_bNewNumber`, `m_bAfterEquals`

### Input Handling Pattern

The app uses `PreTranslateMessage()` to intercept keyboard input before child controls:
- Returns TRUE to consume the message
- Handles both WM_KEYDOWN and VK codes
- `OnKeyUp()` is also wired but may cause duplicate processing

## Known Issues

No known issues - previously identified issues have been fixed:
- Font memory leak: Now managed with member variable and destructor
- GDI+ shutdown: Now only in ExitInstance()
- InitInstance: Returns TRUE after successful init
- Duplicate key handling: Removed ON_WM_KEYUP handler, now uses PreTranslateMessage only
