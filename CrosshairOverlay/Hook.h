#include <Windows.h>
#include <d3d11.h>
#include <iostream>


// Hooking via modifing PRESENT...
// Read in the end

typedef HRESULT(WINAPI* Present_t)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

// Pointer to the original Present function
Present_t oPresent = nullptr;

// Your custom hook function
HRESULT WINAPI Hooked_Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
    // Your overlay rendering code here (e.g., draw the crosshair)
    std::cout << "Rendering crosshair..." << std::endl;

    // Call the original Present function (trampoline)
    return oPresent(pSwapChain, SyncInterval, Flags);
}

// Hooking function
void HookFunction(void* targetFunction, void** trampoline) {
    *trampoline = targetFunction;

    // Change memory protection to allow writing
    DWORD oldProtect;
    VirtualProtect(targetFunction, sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect);

    // Insert a jump to our hook function (relative jump)
    DWORD_PTR jumpAddress = (DWORD_PTR)Hooked_Present;
    *(BYTE*)targetFunction = 0xE9;  // JMP opcode
    *(DWORD_PTR*)((BYTE*)targetFunction + 1) = jumpAddress - (DWORD_PTR)targetFunction - 5;

    // Restore original memory protection
    VirtualProtect(targetFunction, sizeof(void*), oldProtect, &oldProtect);
}

// To unhook the function and restore the original function
void RestoreFunction(void* targetFunction, void* trampoline) {
    DWORD oldProtect;
    VirtualProtect(targetFunction, sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect);

    // Restore the original bytes of the function
    memcpy(targetFunction, trampoline, sizeof(void*));

    VirtualProtect(targetFunction, sizeof(void*), oldProtect, &oldProtect);
}

void InitDX11Hook() {
    // Load the DX11 module and get the address of Present function
    HMODULE d3d11Module = GetModuleHandle(L"d3d11.dll");
    if (d3d11Module == NULL) {
        std::cerr << "Failed to get handle for d3d11.dll!" << std::endl;
        return;
    }

    // Find the Present function in the d3d11.dll module
    oPresent = (Present_t)GetProcAddress(d3d11Module, "Present");
    if (oPresent == nullptr) {
        std::cerr << "Failed to locate Present function!" << std::endl;
        return;
    }

    // Hook the Present function
    HookFunction(oPresent, (void**)&oPresent);
}

// Unhooking on exit
void UnhookDX11() {
    // Unhook the Present function and restore the original function
    RestoreFunction(oPresent, oPresent);
}

// study vtable hooking and API hooking.

// example of vtable hooking

typedef HRESULT(WINAPI* PresentFn)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags);

// Pointer to the original Present function
PresentFn oPresent = nullptr;

// Our hooked Present function
HRESULT WINAPI hkPresent(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags)
{
    std::cout << "Present Hooked!" << std::endl;

    // Call the original Present function after our custom code
    return oPresent(swapChain, syncInterval, flags);
}

void HookPresent(IDXGISwapChain* swapChain)
{
    // Get the vtable of the swapChain object (we assume it's DXGI_SWAP_CHAIN)
    void** vTable = *reinterpret_cast<void***>(swapChain);

    // Save the original Present function pointer from the vtable
    oPresent = reinterpret_cast<PresentFn>(vTable[8]); // Present is usually at index 8 for DirectX 11

    // Replace the Present function in the vtable with our hooked function
    vTable[8] = reinterpret_cast<void*>(hkPresent);
}

int main()
{
    // Initialize DirectX 11 (this part is just a setup for the example)
    IDXGISwapChain* swapChain = nullptr;
    // Normally you would create a Direct3D device here and obtain the swapChain.

    // Now we hook Present:
    HookPresent(swapChain);

    // After hooking, the Present function will now call hkPresent instead of the original function.
    // The next time Present is called, it will print "Present Hooked!"

    // Don't forget to clean up and restore the vtable if needed (not shown in this example).

    return 0;
}


// example of API hooking
