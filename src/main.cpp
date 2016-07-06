#include <iostream>
#include "../includes/Image.h" 
#include <string>

// // a sample exported function
// void DLL_EXPORT SomeFunction(const LPCSTR sometext)
// {
//     MessageBoxA(0, sometext, "DLL Message", MB_OK | MB_ICONINFORMATION);
// }

// extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
// {
//     switch (fdwReason)
//     {
//         case DLL_PROCESS_ATTACH:
//             // attach to process
//             // return FALSE to fail DLL load
//             break;

//         case DLL_PROCESS_DETACH:
//             // detach from process
//             break;

//         case DLL_THREAD_ATTACH:
//             // attach to thread
//             break;

//         case DLL_THREAD_DETACH:
//             // detach from thread
//             break;
//     }
//     return TRUE; // succesful
// }

int main(int c, char* argv[]) {
    std::cout << "Loading:" <<"\"" <<argv[1] << "\"" << "\n";
    try{
        KOCREngine::Image image{argv[1]};
        std::cout << "Data size:" << sizeof(image)<< "WxH:" << image.getProportion().width << " x "<< image.getProportion().height << "\n";        
    }catch(std::exception e){
        std::cout << e.what();
    }
}