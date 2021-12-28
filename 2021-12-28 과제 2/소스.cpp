#include <windows.h>                           // 윈도우 헤더파일
#include <time.h>
#include <stdlib.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;                              //인스턴스 핸들
LPCTSTR lpszClass = TEXT("정상호_18032081");            //제목 표시줄에 표시되는 내용

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam,
    int nCmdShow)
{
    HWND hWnd;                                 //윈도우 핸들 선언
    MSG Message;                              //메세지 구조체 변수 선언
    WNDCLASS WndClass;                           //Windows Class 구조체 변수 선언
    g_hInst = hInstance;                        //hInstance값을 외부에서도 사용할 수 있도록 전역변수에 값을 저장

    WndClass.cbClsExtra = 0;                     //예약 영역. 지금은 사용X
    WndClass.cbWndExtra = 0;                     //예약 영역
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   // 윈도우의 배경 색상을 지정
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);      //윈도우의 마우스포인터 모양을 지정
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);   //윈도우의 커서 아이콘 모양 지정
    WndClass.hInstance = hInstance;                  //윈도우 클래스를 등록하는 프로그램 번호
    WndClass.lpfnWndProc = WndProc;                  //윈도우 메세지 처리 함수 지정
    WndClass.lpszClassName = lpszClass;               //윈도우 클래스의 이름 지정
    WndClass.lpszMenuName = NULL;                  //메뉴 지정
    WndClass.style = CS_HREDRAW | CS_VREDRAW;         //윈도우의 스타일을 정의

    RegisterClass(&WndClass);                     //WNDCLASS 구조체의 번지를 전달


    hWnd = CreateWindow(lpszClass, lpszClass,         //윈도우를 생성
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
        /* 100,100,500,500*/, NULL, (HMENU)NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);

    //메세지 루프를 실행
    while (GetMessage(&Message, NULL, 0, 0)) {         //Queue에 있는 메세지를 읽어들인다
        TranslateMessage(&Message);                  //키보드 입력 메세지를 프로그램에서 쉽게 사용할 수 있도록 가공
        DispatchMessage(&Message);                  //메세지를 윈도우의 메세지 처리 함수 WndProc로 전달
    }
    return (int)Message.wParam;                     //탈출 코드. 프로그램 종료
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    static int box_x = 400;  //중앙 박스 좌표
    static int box_y = 400;
    static int box_s = 50;    //박스 사이즈
    static int h = 100;       //이동 범위
    static int ax = 400;     //색박스 의 좌표
    static int ay = 400;
    HBRUSH HBrush, OldBrush;
    static int r;
    static int g;
    static int b;
    static BOOL Key_D = FALSE;

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