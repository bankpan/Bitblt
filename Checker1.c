/*-------------------------------------------------
   CHECKER1.C -- Mouse Hit-Test Demo Program No. 1
                 (c) Charles Petzold, 1998
  -------------------------------------------------*/

#include <windows.h>


#define DIVISIONS 5

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR  szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("Checker1") ;
     HWND         hwnd ;
     MSG          msg ;
     WNDCLASS     wndclass ;
     
     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;
     
     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("Program requires Windows NT!"), 
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }
     
     hwnd = CreateWindow (szAppName, TEXT ("Checker1 Mouse Hit-Test Demo"),
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          NULL, NULL, hInstance, NULL) ;
     
     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;
     
     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    
     static int  cxBlock, cyBlock,cxSource,cySource ,cxClient,cyClient;
     HDC         hdc,HCompatibleDC ;
     int         x, y ;
     PAINTSTRUCT ps ;
     RECT        rect ;
	 static HBITMAP hBitMap;
	 BITMAP bitmap;
	 BOOL mark=FALSE;
	 HBRUSH brushObj ;
HINSTANCE hInstance;
	 HBRUSH brushTemp;

     
     switch (message)
     {
	 case WM_CREATE:
		 hInstance=((LPCREATESTRUCT)lParam)->hInstance;
		hBitMap = LoadImage(NULL,TEXT("Bricks.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE); 
		 GetObject(hBitMap,sizeof(BITMAP),&bitmap);
		 cxSource=bitmap.bmWidth;
		 cySource=bitmap.bmHeight;

     case WM_SIZE :
		 cxClient=LOWORD(lParam);
		 cyClient=HIWORD(lParam);
        
          return 0 ;

          
     case WM_PAINT :
          hdc = BeginPaint (hwnd, &ps) ;
		 //hdc=GetDC(hwnd);
		 HCompatibleDC=CreateCompatibleDC(hdc);
	
		 SelectObject(HCompatibleDC,hBitMap);

		 for(y=0;y<cyClient;y+=cySource)
			 for(x=0;x<cxClient;x+=cxSource)
			 {
				  BitBlt(hdc,0,0,cxSource,cySource,HCompatibleDC,0,0,SRCCOPY);
			 }
		  DeleteDC(HCompatibleDC);
          EndPaint (hwnd, &ps) ;
          return 0 ;
               
     case WM_DESTROY :
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}
