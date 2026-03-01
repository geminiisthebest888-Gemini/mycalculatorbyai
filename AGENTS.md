# AGENTS.md - Calculator App Development Guide

## Project Overview

This is a Windows MFC (Microsoft Foundation Classes) calculator application written in C++. The project uses Visual Studio 2022 with MSBuild for compilation.

---

## 1. Build Commands

### Build the Project
```powershell
# Using MSBuild directly
& 'C:\Program Files\Microsoft Visual Studio\18\Professional\MSBuild\Current\Bin\amd64\MSBuild.exe' 'C:\AIClaudeCode\mycalculatorbyai\MFCApplication1\MFCApplication1.slnx' /p:Configuration=Debug /p:Platform=x64
```

### Clean and Rebuild
```powershell
# Clean build artifacts
Remove-Item -Path 'C:\AIClaudeCode\mycalculatorbyai\MFCApplication1\x64' -Recurse -Force -ErrorAction SilentlyContinue

# Rebuild
& 'C:\Program Files\Microsoft Visual Studio\18\Professional\MSBuild\Current\Bin\amd64\MSBuild.exe' 'C:\AIClaudeCode\mycalculatorbyai\MFCApplication1\MFCApplication1.slnx' /p:Configuration=Debug /p:Platform=x64 /t:Clean,Build
```

### Run the Application
```powershell
Start-Process 'C:\AIClaudeCode\mycalculatorbyai\MFCApplication1\x64\Debug\MFCApplication1.exe'
```

---

## 2. Code Style Guidelines

### 2.1 File Organization

- **Header files (.h)**: Class declarations, includes, using statements
- **Implementation files (.cpp)**: Method implementations
- **Resource files (.rc)**: Dialog layouts, UI resources

### 2.2 Naming Conventions

| Element | Convention | Example |
|---------|------------|---------|
| Classes | PascalCase with C prefix | `CMFCApplication1Dlg`, `CGradientButton` |
| Member variables | m_ prefix + PascalCase | `m_strDisplay`, `m_bNewNumber` |
| Functions | PascalCase | `UpdateDisplay()`, `AppendDigit()` |
| Constants | PascalCase | `IDC_BTN0`, `VK_RETURN` |
| Parameters | PascalCase | `szDigit`, `nChar` |

### 2.3 Include Order

```cpp
// 1. Precompiled header
#include "pch.h"

// 2. Framework headers
#include "framework.h"

// 3. Application headers
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"

// 4. Third-party headers (e.g., GdiPlus)
#include <GdiPlus.h>

// 5. Standard library (if needed)
```

### 2.4 Using Statements

```cpp
// In header files - use fully qualified names
#include <GdiPlus.h>
using namespace Gdiplus;  // Only in header if needed globally

// In cpp files - prefer fully qualified or local using
using namespace Gdiplus;
```

### 2.5 MFC-Specific Patterns

#### Class Declaration
```cpp
class CMFCApplication1Dlg : public CDialog
{
public:
    CMFCApplication1Dlg(CWnd* pParent = nullptr);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    // Member variables
    CString m_strDisplay;
    BOOL m_bNewNumber;

    // Methods
    void UpdateDisplay();
    afx_msg void OnBnClickedBtn0();
    DECLARE_MESSAGE_MAP()
};
```

#### Message Map
```cpp
BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialog)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BTN0, &CMFCApplication1Dlg::OnBnClickedBtn0)
END_MESSAGE_MAP()
```

### 2.6 Error Handling

- **Never suppress errors**: Do not use `as any`, `@ts-ignore`, or empty catch blocks
- **Check return values**: Validate API return values and handle errors appropriately
- **Use TRACE for debugging**: `TRACE(traceAppMsg, 0, "Warning: ...\n")`

### 2.7 Formatting

- **Indentation**: 4 spaces (Visual Studio default)
- **Braces**: K&R style (opening brace on same line)
- **Line length**: Keep under 120 characters when practical
- **Spacing**: Use spaces around operators, after commas

```cpp
// Good
void CMFCApplication1Dlg::AppendDigit(LPCTSTR szDigit)
{
    if (m_bNewNumber)
    {
        m_strDisplay = szDigit;
        m_bNewNumber = FALSE;
    }
}

// Bad
void AppendDigit(LPCTSTR szDigit){
if(m_bNewNumber){
m_strDisplay=szDigit;m_bNewNumber=FALSE;}
}
```

### 2.8 Types and Conversions

- **Use MFC types**: `CString`, `BOOL`, `UINT`, `LPCTSTR` for MFC compatibility
- **Avoid C casts**: Use `static_cast`, `dynamic_cast` where needed
- **Unicode**: Use `_T()` macro for string literals

```cpp
// Good
CString strResult;
strResult.Format(_T("%g"), result);
m_strDisplay = _T("0");

// Avoid
char* str = "hello";
```

### 2.9 Custom Controls

When creating custom controls (like CGradientButton):
- Subclass existing controls with `SubclassDlgItem()`
- Use `DrawItem()` for owner-drawn controls
- Initialize GDI+ in `InitInstance()` and shutdown in `ExitInstance()`

```cpp
// Initialize GDI+ in app's InitInstance()
Gdiplus::GdiplusStartupInput gdiplusStartupInput;
Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

// Shutdown in ExitInstance()
Gdiplus::GdiplusShutdown(m_gdiplusToken);
```

### 2.10 Keyboard Input Handling

- Use `PreTranslateMessage()` to intercept keyboard messages
- Handle both `WM_KEYDOWN` for immediate action
- Check for modifier keys (Shift, Ctrl) when needed

```cpp
BOOL CMFCApplication1Dlg::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
    {
        HandleKeyDown(pMsg->wParam);
        return TRUE;
    }
    return CDialog::PreTranslateMessage(pMsg);
}
```

---

## 3. Testing Guidelines

### Manual Testing Checklist

1. **Basic Operations**: Test 2+3=, 6-2=, 3*4=, 8/2=
2. **Keyboard Input**: Verify all number keys and operators work
3. **Button Clicks**: Verify all buttons respond correctly
4. **Edge Cases**: Division by zero, large numbers, decimal points
5. **UI Behavior**: Cursor position, gradient button hover states

### Automated Testing

Currently no automated test framework. For manual verification:
```powershell
# Launch app and verify it starts
$proc = Start-Process 'C:\AIClaudeCode\mycalculatorbyai\MFCApplication1\x64\Debug\MFCApplication1.exe' -PassThru
Start-Sleep -Seconds 2

# Check if running
if ($proc.Responding) { Write-Host "App running successfully" }

# Stop app
Stop-Process -Id $proc.Id -Force
```

---

## 4. Git Workflow

### Commit Message Format
```
<type>: <description>

<optional body>
```

Types: `Fix:`, `Add:`, `Remove:`, `Refactor:`

Example:
```
Fix: keyboard divide key not working

Added VK_OEM_2 handling for forward slash key
```

### Before Committing
1. Build succeeds with no errors
2. No new warnings introduced
3. Changes match the requirement

---

## 5. Key Files

| File | Purpose |
|------|---------|
| `MFCApplication1Dlg.cpp` | Main dialog implementation |
| `MFCApplication1Dlg.h` | Dialog class declaration |
| `MFCApplication1.cpp` | Application entry point |
| `MFCApplication1.rc` | Dialog resources |
| `MFCApplication1.vcxproj` | Project configuration |

---

## 6. Common Issues and Solutions

### Duplicate Key Detection
- **Problem**: Single key press registers multiple times
- **Solution**: Use `PreTranslateMessage` with `WM_KEYDOWN` only (not timer-based polling)

### GDI+ Not Working
- **Problem**: Gradient buttons don't render
- **Solution**: Ensure `GdiplusStartup()` called in `InitInstance()` and `GdiplusShutdown()` in `ExitInstance()`

### Keyboard Input Not Reaching Dialog
- **Problem**: Child controls (buttons) have focus
- **Solution**: Use `PreTranslateMessage` to intercept keys before child controls

### OEM Key Issues
- **Problem**: Some keys (like `/` and `=`) not working
- **Solution**: Use both virtual key codes (VK_DIVIDE) and OEM codes (VK_OEM_2)
