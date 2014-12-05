#define DllExport   __declspec(dllexport)

int DllExport addition(int entier1, int entier2) {
    return entier1 + entier2;
}
