// ProgrammeFenetre.cpp : Définit le point d'entrée de l'application.
//

#include <vector>

#include "framework.h"
#include "ProgrammeFenetre.h"


#define MAX_LOADSTRING 100


// Variables globales :
HINSTANCE hInst;                                // instance actuelle
WCHAR szTitle[MAX_LOADSTRING];                  // Texte de la barre de titre
WCHAR szWindowClass[MAX_LOADSTRING];            // nom de la classe de fenêtre principale

// Déclarations anticipées des fonctions incluses dans ce module de code :
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Element de la page
HWND hWnd;
//HWND hWndChild;

struct PIX
{
    int x;
    int y;
    COLORREF c;
};
std::vector<PIX> pixels;
struct BitMap
{

};


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Placez le code ici.

    // Initialise les chaînes globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROGRAMMEFENETRE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Effectue l'initialisation de l'application :
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROGRAMMEFENETRE));

    MSG msg;
    // Boucle de messages principale :
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            /*TranslateMessage(&msg);*/
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  FONCTION : MyRegisterClass()
//
//  OBJECTIF : Inscrit la classe de fenêtre.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROGRAMMEFENETRE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROGRAMMEFENETRE);
    wcex.lpszClassName  = L"ClassName";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FONCTION : InitInstance(HINSTANCE, int)
//
//   OBJECTIF : enregistre le handle d'instance et crée une fenêtre principale
//
//   COMMENTAIRES :
//
//        Dans cette fonction, nous enregistrons le handle de l'instance dans une variable globale, puis
//        nous créons et affichons la fenêtre principale du programme.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Stocke le handle d'instance dans la variable globale

   hWnd = CreateWindowW(L"ClassName", L"azerty", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }
   SetTimer(hWnd, 100, 1, (TIMERPROC)NULL);

   /*HWND hwndButton1 = CreateWindowW(
       L"BUTTON", L"BipBip", WS_VISIBLE | WS_CHILD, 0, 0, 50, 25, hWnd, nullptr, hInstance, nullptr);
   if (!hwndButton1)
   {
       return FALSE;
   }

   HWND hwndButton2 = CreateWindowW(
       L"BUTTON", L"BoupBoup", WS_VISIBLE | WS_CHILD, 60, 0, 75, 50, hWnd, (HMENU)10, hInstance, nullptr);
   if (!hwndButton2)
   {
       return FALSE;
   }

   hWndChild = CreateWindowW(L"ClassName", L"Bon TouTou", WS_CHILDWINDOW | WS_BORDER, 150, 50, 200, 200,
       hWnd, nullptr, hInstance, nullptr);
   if (!hWndChild)
   {
       return FALSE;
   }*/


   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

//
//  FONCTION : WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  OBJECTIF : Traite les messages pour la fenêtre principale.
//
//  WM_COMMAND  - traite le menu de l'application
//  WM_PAINT    - Dessine la fenêtre principale
//  WM_DESTROY  - génère un message d'arrêt et retourne
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analyse les sélections de menu :
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            /*case 10:
                ShowWindow(hWndChild, SW_SHOW);
                break;*/
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            RECT rc;
            GetClientRect(hWnd, &rc);
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            /////////////////////////////////////
            FILE* chargeImg = nullptr;
            BYTE* list = new BYTE[3126];
            errno_t chargeImgeS = fopen_s(&chargeImg,
                "C:\\Users\\aberny\\Documents\\Img32x32BMP.bmp",
                "rb");
            if (chargeImgeS)
            {
                return 0;
            }
            size_t size = fread(list, 1, 3126, chargeImg);
            fclose(chargeImg);

            ////////////////////////////////////////

            BITMAPFILEHEADER bitmapHeader = {};
            memcpy(&bitmapHeader, list, sizeof(BITMAPFILEHEADER));

            BITMAPINFOHEADER info = {};
            memcpy(&info, list + sizeof(BITMAPFILEHEADER), sizeof(BITMAPINFOHEADER));

            BYTE* rgb = list + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
            for (int i = 0; i < info.biWidth * info.biHeight * 3; i++)
            {
                int r = rgb[i];
                int g = rgb[i + 1];
                int b = rgb[i + 2];


            }
            delete[] list;

            BITMAPINFO bitmapinfo;
            bitmapinfo.bmiHeader = info;

            HBITMAP h =CreateDIBitmap(hdc, &info, CBM_INIT, rgb, &bitmapinfo, DIB_RGB_COLORS);
            // TODO: Ajoutez ici le code de dessin qui utilise hdc...
            for (int i = 0; i < rc.right-rc.left; i++)
            {
                for (int j = 0; j < rc.bottom-rc.top; j++)
                {
                    //SetPixelV(hdc, i, j, RGB(0 + i, 0 + j, 0 + (i + j)));
                }
            }
            for (int i = 0; i < pixels.size(); i++)
            {
                PIX p = pixels[i];
                SetPixelV(hdc, p.x, p.y, p.c);

            }
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    //case WM_TIMER:
    //{
    //    PIX p;
    //    p.x = rand() % 100;
    //    p.y = rand() % 100;
    //    p.c = RGB(rand() % 255, rand() % 255, rand() % 255);
    //    pixels.push_back(p);
    //    RedrawWindow(hWnd, nullptr, nullptr, RDW_ERASE| RDW_INVALIDATE);
    //        //SetPixelV(hdc, i, j, RGB(0 + i, 0 + j, 0 + (i + j)))

    //       break;
    //}
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Gestionnaire de messages pour la boîte de dialogue À propos de.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
