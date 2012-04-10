#define ID_TRAY_APP_ICON                5000
#define ID_TRAY_EXIT_CONTEXT_MENU_ITEM  3000
#define WM_TRAYICON ( WM_USER + 1 )
#define LWA_COLORKEY            0x00000001
#define LWA_ALPHA               0x00000002
#include <wininet.h>
#define WINDOW_WIDTH 250
#define WINDOW_HEIGHT 200
#include <string>

using namespace std;

typedef DWORD (WINAPI *PSLWA)(HWND, DWORD, BYTE, DWORD);
static PSLWA pSetLayeredWindowAttributes = NULL;

class Foobar
{

public:
        Foobar();    
        HICON InitNotifyIconData(HWND form2);
        void Init(HWND Foo);
        HWND GetFoo();
        unsigned int GetX();
        unsigned int GetY();
        bool GetSong();
        void Fetch();
        void CheckV();
        bool Contains(const string iStr, const string sStr);
        bool CheckOnTop(HWND hwnd);
        bool Provera();
        HWND FooBar;
        string Lyrics;
        void SetTrans(unsigned int Faktor,HWND Foo);
private:
        
        RECT Pos;
        HINTERNET hINet,hFile;
        string URL;
        string tempURL;
        char *Buffer;
        string tBuffer;
        DWORD dwRead;
        unsigned int Position;
        size_t Kraj;
        size_t DivLyr;
        int Counter;
        char SongT[200];
        string Song;
        string REGEX;
        string artist;
        string m_strContents ;
        string title;
        bool checkontop;
};


