#include <assert.h>
#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


#define local_persist static
#define global_var    static
#define internal      static

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef struct win32_buffer {
    BITMAPINFO Info;
    void*      Memory;
    int        Width;
    int        Height;
    int        BytesPerPixel;
    int        Pitch;
} win32_buffer;

typedef struct win32_window_dimensions {
    int Width;
    int Height;
}win32_window_dimensions; 

global_var bool         Running;
global_var win32_buffer BackBuffer;
global_var bool flag;
global_var int counter;

#define SIZE 100
global_var bool last[SIZE][SIZE];
global_var bool curr[SIZE][SIZE];

size_t check_neighbors(size_t i, size_t j) {
    size_t count = 0;
    if (j > 0 && last[i][j-1]) count++;
    if (i < SIZE-1 && j > 0 && last[i+1][j-1]) count++;
    if (i < SIZE-1 && last[i+1][j]) count++;
    if (i < SIZE-1 && j < SIZE-1 && last[i+1][j+1]) count++;
    if (j < SIZE-1 && last[i][j+1]) count++;
    if (i > 0 && j < SIZE-1 && last[i-1][j+1]) count++;
    if (i > 0 && last[i-1][j]) count++;
    if (i > 0 && j > 0 && last[i-1][j-1]) count++;

    return count;
}

void update_grid() {
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            if (!((i == 0 && j == 0)  ||
            (i == 0 && j == SIZE - 1) ||
            (i == SIZE - 1 && j == 0) ||
            (i == SIZE - 1 && j == SIZE - 1))) 
            {
                size_t neighbors_on = check_neighbors(i, j);
                if (last[i][j]) {
                    if (neighbors_on != 2 && neighbors_on != 3) curr[i][j] = false;
                } else {
                    if (neighbors_on == 3) curr[i][j] = true;
                }
            }
        }
    }
}

internal win32_window_dimensions
Win32GetWindowDimensions(HWND Window)
{
    win32_window_dimensions WindowDimensions;
    RECT ClientRect;
    GetClientRect(Window, &ClientRect);
    WindowDimensions.Width  = ClientRect.right - ClientRect.left;
    WindowDimensions.Height = ClientRect.bottom - ClientRect.top;   
    return  WindowDimensions;
}

internal void
step (win32_buffer Buffer, bool flag)
{
    local_persist int cell_size = 10;
    // OutputDebugStringA(sprintf("Flag is %d\n", flag));
    uint8 *Row = (uint8 *)Buffer.Memory;
    for (int Y = 0; Y < Buffer.Height; ++Y)
    {   
        uint32 *Pixel = (uint32 *)Row;
        for (int X = 0; X < Buffer.Width; ++X)
        {
            int col = X / cell_size;
            int row = Y / cell_size;
            
            bool is_on = curr[row][col];
            if (is_on) 
            {
                *Pixel++ = 0xe7ea31;
            }
            else 
            {
				*Pixel++ = 0x000000;
            }
        }
        Row += Buffer.Pitch;
    }
}

internal void
Win32ResizeDIBSection(win32_buffer* Buffer, int Width, int Height)
{
    if (Buffer->Memory)
    {
        VirtualFree(Buffer->Memory, 0, MEM_RELEASE);   
    }
    
    Buffer->Width         = Width;
    Buffer->Height        = Height;
    Buffer->BytesPerPixel = 4;
    
    Buffer->Info.bmiHeader.biSize        = sizeof(Buffer->Info.bmiHeader);
    Buffer->Info.bmiHeader.biWidth       = Buffer->Width;
    Buffer->Info.bmiHeader.biHeight      = -Buffer->Height;
    Buffer->Info.bmiHeader.biPlanes      = 1;
    Buffer->Info.bmiHeader.biBitCount    = 32;
    Buffer->Info.bmiHeader.biCompression = BI_RGB;
    
    int BitmapMemorySize = (Width*Height)*Buffer->BytesPerPixel;
    Buffer->Memory       = VirtualAlloc(0, BitmapMemorySize, MEM_COMMIT, PAGE_READWRITE);
    Buffer->Pitch        = Width*Buffer->BytesPerPixel;
}

internal void
Win32UpdateWindow(HDC DeviceContext, 
                  int WindowWidth, int WindowHeight, 
                  win32_buffer Buffer, 
                  int X, int Y, int Width, int Height) 
{   
    StretchDIBits(
        DeviceContext,
        /*X,
        Y,
        Width,
        Height,
        X,
        Y,
        Width,
        Height,*/
        0, 0, WindowWidth, WindowHeight,
        0, 0, Buffer.Width, Buffer.Height,
        Buffer.Memory,
        &Buffer.Info,
        DIB_RGB_COLORS,
        SRCCOPY
    );
}

LRESULT CALLBACK Win32MainWindowCallback (
    HWND Window,
    UINT Message,
    WPARAM WParam,
    LPARAM LParam 
)
{
    LRESULT Result = 0;
    switch(Message) 
    {
        case WM_SIZE:
        { 
            OutputDebugStringA("WM_SIZE\n");   
        } break;
        
        case WM_DESTROY:
        {
            Running = false;
            OutputDebugStringA("WM_DESTROY\n");
        } break;
        
        case WM_CLOSE:
        {
            Running = false;
            OutputDebugStringA("WM_SIZE\n");
        } break;
        
        case WM_ACTIVATEAPP:
        {
            OutputDebugStringA("WM_ACTIVATEAPP\n");
        } break;
        
        case WM_TIMER:
        {    
            switch(WParam) 
            {
                case 1:
                { 
                    update_grid(); 
                    memcpy(last, curr, sizeof(last));
                    step(BackBuffer, flag);
                    flag = !flag;
                    counter++;
                    if (counter >= 300) {
                        Running = false;
                    }
                } break;

                case 2:
                {
                    KillTimer(Window, 2);
                    SetTimer(
                        Window,
                        1,
                        (1.0 / 30.0) * 1000,
                        (TIMERPROC)NULL
                    );
                } break;
            }
        } break;
        
        case WM_PAINT:
        {
            PAINTSTRUCT Paint;
            HDC DeviceContext = BeginPaint(Window, &Paint);
            int X = Paint.rcPaint.left;
            int Y = Paint.rcPaint.top;
            int Width = Paint.rcPaint.right - Paint.rcPaint.left;
            int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
            win32_window_dimensions WinDim = Win32GetWindowDimensions(Window);
            Win32UpdateWindow(DeviceContext, WinDim.Width, WinDim.Height, BackBuffer, X, Y, Width, Height);
            EndPaint(Window, &Paint);
        } break;

        default:
        {
            Result = DefWindowProc(Window, Message, WParam, LParam);
        } break;
    }
    return(Result);
}

int CALLBACK WinMain(
    HINSTANCE   Instance,
    HINSTANCE   PrevInstance,
    LPSTR       CommandLine,
    int         ShowCode
) 
{
    FILE* f = fopen("C:\\Users\\nirva\\proj\\aoc\\2015\\day18\\input.txt", "r");
    assert(f != NULL);

    int c;
    int row, col;
    row = col = 0;
    // populate last with the configuration from text file
    while ((c = getc(f)) != EOF) {
        if (c == '#') {
            last[row][col] = true;
            col++;
        } else if (c == '.') {
            last[row][col] = false;
            col++;
        } else if (c == '\n') {
            row++;
            col = 0;
        }
    }
    fclose(f);
    memcpy(curr, last, sizeof(last));
    
    WNDCLASS WindowClass = {};
    
    // win32_window_dimensions WinDim = Win32GetWindowDimensions(Window); 
    Win32ResizeDIBSection(&BackBuffer, 1000, 1000);
    
    WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    WindowClass.lpfnWndProc = Win32MainWindowCallback;
    WindowClass.hInstance = Instance;
    WindowClass.lpszClassName = "HandmadeHeroWindowClass";
    // WindowClass.hIcon = ;
    if (RegisterClass(&WindowClass)) 
    {
        HWND Window = 
        CreateWindowEx
        (
            0,
            WindowClass.lpszClassName,
            "Handmade Hero",
            WS_OVERLAPPEDWINDOW|WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            0,
            0,
            Instance,
            0
        );
        
        if (Window)
        {
            SetTimer(
                Window,
                2,
                10 * 1000,
                (TIMERPROC)NULL
            );
        
            Running = true;
            while (Running) {
                MSG Message;
                while (PeekMessage(&Message, NULL, NULL, NULL, PM_REMOVE))
                {
                    if (Message.message == WM_QUIT) {
                        Running = false;
                    }
                    
                    TranslateMessage(&Message);
                    DispatchMessage(&Message);   
                }
                // step(BackBuffer, flag);
                
                HDC DeviceContext = GetDC(Window);
                win32_window_dimensions WinDim = Win32GetWindowDimensions(Window);
                Win32UpdateWindow(DeviceContext, WinDim.Width, WinDim.Height, BackBuffer, 0, 0, 0, 0);
                ReleaseDC(Window, DeviceContext);
            }
        } 
        else
        {
            // TODO logging
        }
        
    } else 
    {
        // TODO() logging
    }
    
    return(0);
}
