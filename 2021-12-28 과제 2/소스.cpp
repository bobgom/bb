#include <windows.h>                           // ������ �������
#include <time.h>
#include <stdlib.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;                              //�ν��Ͻ� �ڵ�
LPCTSTR lpszClass = TEXT("����ȣ_18032081");            //���� ǥ���ٿ� ǥ�õǴ� ����

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam,
    int nCmdShow)
{
    HWND hWnd;                                 //������ �ڵ� ����
    MSG Message;                              //�޼��� ����ü ���� ����
    WNDCLASS WndClass;                           //Windows Class ����ü ���� ����
    g_hInst = hInstance;                        //hInstance���� �ܺο����� ����� �� �ֵ��� ���������� ���� ����

    WndClass.cbClsExtra = 0;                     //���� ����. ������ ���X
    WndClass.cbWndExtra = 0;                     //���� ����
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   // �������� ��� ������ ����
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);      //�������� ���콺������ ����� ����
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);   //�������� Ŀ�� ������ ��� ����
    WndClass.hInstance = hInstance;                  //������ Ŭ������ ����ϴ� ���α׷� ��ȣ
    WndClass.lpfnWndProc = WndProc;                  //������ �޼��� ó�� �Լ� ����
    WndClass.lpszClassName = lpszClass;               //������ Ŭ������ �̸� ����
    WndClass.lpszMenuName = NULL;                  //�޴� ����
    WndClass.style = CS_HREDRAW | CS_VREDRAW;         //�������� ��Ÿ���� ����

    RegisterClass(&WndClass);                     //WNDCLASS ����ü�� ������ ����


    hWnd = CreateWindow(lpszClass, lpszClass,         //�����츦 ����
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
        /* 100,100,500,500*/, NULL, (HMENU)NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);

    //�޼��� ������ ����
    while (GetMessage(&Message, NULL, 0, 0)) {         //Queue�� �ִ� �޼����� �о���δ�
        TranslateMessage(&Message);                  //Ű���� �Է� �޼����� ���α׷����� ���� ����� �� �ֵ��� ����
        DispatchMessage(&Message);                  //�޼����� �������� �޼��� ó�� �Լ� WndProc�� ����
    }
    return (int)Message.wParam;                     //Ż�� �ڵ�. ���α׷� ����
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    static int box_x = 400;  //�߾� �ڽ� ��ǥ
    static int box_y = 400;
    static int box_s = 50;    //�ڽ� ������
    static int h = 100;       //�̵� ����
    static int ax = 400;     //���ڽ� �� ��ǥ
    static int ay = 400;
    HBRUSH HBrush, OldBrush;
    static int r;
    static int g;
    static int b;
    static BOOL Key_D = FALSE;
    int a;

    switch (iMessage) {
    case WM_CREATE:
        srand(time(NULL));

        return 0;

    case WM_KEYDOWN:
        Key_D = TRUE;
        switch (wParam) {
        case VK_UP:
            if (ax == box_x) {
                ay -= h;
                if (ay < box_y - h) {
                    ay += h;
                }
            }
            break;
        case VK_DOWN:
            if (ax == box_x) {
                ay += h;
                if (ay > box_y + h) {
                    ay -= h;
                }
            }
            break;
        case VK_LEFT:
            if (ay == box_y) {
                ax -= h;
                if (ax < box_x - h) {
                    ax += h;
                }
            }
            break;
        case VK_RIGHT:
            if (ay == box_y) {
                ax += h;
                if (ax > box_x + h) {
                    ax -= h;
                }
            }
            break;
        }
        r = rand() % 256;
        g = rand() % 256;
        b = rand() % 256;
        InvalidateRect(hWnd, NULL, TRUE);
        return 0;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        Rectangle(hdc, box_x - box_s - h, box_y - box_s, box_x + box_s - h, box_y + box_s);
        Rectangle(hdc, box_x - box_s + h, box_y - box_s, box_x + box_s + h, box_y + box_s);
        Rectangle(hdc, box_x - box_s, box_y - box_s + h, box_x + box_s, box_y + box_s + h);
        Rectangle(hdc, box_x - box_s, box_y - box_s - h, box_x + box_s, box_y + box_s - h);
        if (Key_D) {
            HBrush = CreateSolidBrush(RGB(r, g, b));
            OldBrush = (HBRUSH)SelectObject(hdc, HBrush);

            Rectangle(hdc, ax - box_s, ay - box_s, ax + box_s, ay + box_s);

            SelectObject(hdc, OldBrush);
            DeleteObject(HBrush);
        }


        EndPaint(hWnd, &ps);

        return 0;


    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}