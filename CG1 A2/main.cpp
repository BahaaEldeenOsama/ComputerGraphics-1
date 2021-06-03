#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include<math.h>
#include <iostream>

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



void Draw8points2(HDC hdc,int x,int y,int xc,int yc,COLORREF color)
{
    SetPixel(hdc, xc+x, yc+y, color);
    SetPixel(hdc, xc-x, yc+y, color);
    //SetPixel(hdc, xc+x, yc-y, color);
    //SetPixel(hdc, xc-x, yc-y, color);
    SetPixel(hdc, xc-y, yc+x, color);
    //SetPixel(hdc, xc+y, yc-x, color);
    SetPixel(hdc, xc+y, yc+x, color);
    //SetPixel(hdc, xc-y, yc-x, color);
}
void midpoint2(HDC hdc,int xc,int yc,int r,COLORREF color)
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
        Draw8points2(hdc,x,y,xc,yc,color);
    }

}

double distanceBetweenTwoPoints(int x1, int y1, int x2, int y2)
{
    double distance;
    distance = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));

    return distance;
}


void parametricline(HDC hdc, double x1, double y1, double x2, double y2, COLORREF color) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    for (double t = 0; t < 1; t += 0.001) {
        int x = x1 + (dx * t);
        int y = y1 + (dy * t);
        SetPixel(hdc, x, y, color);
    }
}

void parametricline(HDC hdc, double x1, double y1, double x2, double y2, int xi, int yi) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    COLORREF color = RGB(0,0, 255);
    for (double t = 0; t < 1; t += 0.001) {
        int x = x1 + (dx * t);
        int y = y1 + (dy * t);

        if (x == xi & y == yi)
            color = RGB(255,0, 0);

        SetPixel(hdc, x, y, color);
    }
}



/*  This function is called by the Windows function DispatchMessage()  */
int rr, x_1, y_1, x_2, y_2; /// For first circle
int rr2, xx_1, yy_1, xx_2, yy_2; /// For second circle (first eye).
int rr3, xxx_1, yyy_1, xxx_2, yyy_2; /// For second circle (second eye).
int Xx, Yy, Xx2, Yy2, Rr; /// For Smile (second eye).
int hair_x1, hair_y1, hair_x2, hair_y2; /// For hair
int cnt=0;



bool isPointOutCircle(int p_x, int p_y)
{
    double distanceFromCenter;
    distanceFromCenter = distanceBetweenTwoPoints(x_1, y_1, p_x, p_y);

    return (distanceFromCenter > rr);
}

void getIntersectionPoint(HDC hdc, int &xi, int &yi)
{
    double dx = hair_x2 -  hair_x1;
    double dy =  hair_y2 -  hair_y1;

    for (double t = 0; t < 1; t += 0.001) {
        int x = hair_x1 + (dx * t);
        int y = hair_y1 + (dy * t);

        COLORREF pixel_color = GetPixel(hdc, x, y);
        // if circle border is found
        if (pixel_color == RGB(0, 0, 0))
        {
            xi = x; yi = y;
            return;
        }
    }
}

void drawHair(HDC hdc, int x1, int y1, int x2, int y2)
{
    bool is_start_out, is_end_out;
    is_start_out = isPointOutCircle(x1, y1);
    is_end_out = isPointOutCircle(x2, y2);

    // if the line is out it's all red
    if (is_start_out && is_end_out)
    {
        parametricline(hdc, x1, y1, x2, y2, RGB(255,0,0));
        return;
    }

    // if the line is inside it's all blue
    else if (!(is_start_out || is_end_out))
    {
        parametricline(hdc, x1, y1, x2, y2, RGB(0,0,255));
        return;
    }

    // if only a port of the hair inside
    else
    {
        int xi, yi;
        getIntersectionPoint(hdc, xi, yi);

        if (is_start_out)
            parametricline(hdc, x2, y2, x1, y1, xi, yi);

        if (is_end_out)
            parametricline(hdc, x1, y1, x2, y2, xi, yi);
    }

}

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
                /// 2 clicks for the half circle (Shape’s Smile)  ->> Tawaty
            else if(cnt == 6)
            {
                Xx = LOWORD(lParam);
                Yy = HIWORD(lParam);
                ++cnt;
            }
            else if(cnt == 7)
            {
                Xx2 = LOWORD(lParam);
                Yy2 = HIWORD(lParam);
                Rr  = sqrt(pow((Xx2 - Xx), 2) + pow((Yy2 - Yy), 2));
                midpoint2(hdc, Xx, Yy, Rr,RGB(0,155,55));
                ++cnt;
            }
                /// 2clicks for line 1(Hair of the shape)  ->> Abdelrahman
            else if(cnt == 8)
            {
                hair_x1 = LOWORD(lParam);
                hair_y1 = HIWORD(lParam);
                ++cnt;


            }
            else if(cnt == 9)
            {
                hair_x2 = LOWORD(lParam);
                hair_y2 = HIWORD(lParam);
                ++cnt;

                drawHair(hdc, hair_x1, hair_y1, hair_x2, hair_y2);

            }
                /// 2clicks for line 2(Hair of the shape)
            else if(cnt == 10)
            {
                hair_x1 = LOWORD(lParam);
                hair_y1 = HIWORD(lParam);
                ++cnt;

            }
            else if(cnt == 11)
            {
                hair_x2 = LOWORD(lParam);
                hair_y2 = HIWORD(lParam);
                ++cnt;

                drawHair(hdc, hair_x1, hair_y1, hair_x2, hair_y2);

            }
                /// 2clicks for line 3(Hair of the shape)
            else if(cnt == 12)
            {
                hair_x1 = LOWORD(lParam);
                hair_y1 = HIWORD(lParam);
                ++cnt;

            }
            else if(cnt == 13)
            {
                hair_x2 = LOWORD(lParam);
                hair_y2 = HIWORD(lParam);
                ++cnt;

                drawHair(hdc, hair_x1, hair_y1, hair_x2, hair_y2);

            }


        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
