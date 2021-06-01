#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include<math.h>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Assignment 2: Smiley face"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           800,                 /* The programs width */
           600,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}



void Draw8points(HDC hdc,int x,int y,int xc,int yc,COLORREF color)
{
    SetPixel(hdc, xc+x, yc+y, color);
    SetPixel(hdc, xc-x, yc+y, color);
    SetPixel(hdc, xc+x, yc-y, color);
    SetPixel(hdc, xc-x, yc-y, color);
    SetPixel(hdc, xc-y, yc+x, color);
    SetPixel(hdc, xc+y, yc-x, color);
    SetPixel(hdc, xc+y, yc+x, color);
    SetPixel(hdc, xc-y, yc-x, color);
}

void midpoint(HDC hdc,int xc,int yc,int r,COLORREF color)
{
    int x=0;
    int y=r;
    double d=1-r;
    while(x<y){

        if(d<=0){
            d=d+2*x+3;
            x++;
        }
        else{
            d=d+2*(x-y)+5;
            x++;
            y--;
        }
        Draw8points(hdc,x,y,xc,yc,color);
    }

}



/*  This function is called by the Windows function DispatchMessage()  */
int rr, x_1, y_1, x_2, y_2; /// For first circle
int rr2, xx_1, yy_1, xx_2, yy_2; /// For second circle (first eye).
int rr3, xxx_1, yyy_1, xxx_2, yyy_2; /// For second circle (second eye).
int cnt=0;
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);

    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;


        case WM_LBUTTONUP:
            /// Face.
            if(cnt==0)
            {
                 x_1 = LOWORD(lParam);
                 y_1 = HIWORD(lParam);
                 ++cnt;
            }
            else if (cnt==1)
            {
                 x_2 = LOWORD(lParam);
                 y_2 = HIWORD(lParam);
                 rr = sqrt(pow((x_2-x_1), 2) + pow((y_2-y_1), 2));
                 midpoint(hdc, x_1, y_1, rr,RGB(0,0,0));
                 ++cnt;
            }
            /// Eye1
            else if(cnt==2)
            {
                 xx_1 = LOWORD(lParam);
                 yy_1 = HIWORD(lParam);
                 ++cnt;
            }
            else if (cnt==3)
            {
                 xx_2 = LOWORD(lParam);
                 yy_2 = HIWORD(lParam);
                 rr2 = sqrt(pow((xx_2-xx_1), 2) + pow((yy_2-yy_1), 2));
                 midpoint(hdc, xx_1, yy_1, rr2,RGB(0,0,255));
                 ++cnt;
            }
            /// Eye2
            else if(cnt==4)
            {
                 xxx_1 = LOWORD(lParam);
                 yyy_1 = HIWORD(lParam);
                 ++cnt;
            }
            else if (cnt==5)
            {
                 xxx_2 = LOWORD(lParam);
                 yyy_2 = HIWORD(lParam);
                 rr3 = sqrt(pow((xxx_2-xxx_1), 2) + pow((yyy_2-yyy_1), 2));
                 midpoint(hdc, xxx_1, yyy_1, rr3,RGB(0,0,255));
                 ++cnt;
            }
            /// 2 clicks for the half circle (Shape’s Smile)  ->> Twatiy
            else if(cnt == 6)
            {

            }
            else if(cnt == 7)
            {

            }
            /// 2clicks for line 1(Hair of the shape)  ->> Abdelrahman
             else if(cnt == 8)
            {

            }
            else if(cnt == 9)
            {

            }
            /// 2clicks for line 2(Hair of the shape)
             else if(cnt == 10)
            {

            }
            else if(cnt == 11)
            {

            }
             /// 2clicks for line 3(Hair of the shape)
             else if(cnt == 12)
            {

            }
            else if(cnt == 13)
            {

            }


        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
