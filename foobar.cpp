#include "foobar.h"

Foobar::Foobar()
{
tempURL = "ba0das0u098ujnmkdasdaslhj7";
REGEX = "  [foobar2000 v1.0]";
Counter = 0;
checkontop = true;
Buffer = new char[2000 + 1];
}
HWND Foobar::GetFoo()
{
     return FindWindow("{97E27FAA-C0B3-4b8e-A693-ED7881E99FC1}",0x00);
}
HICON Foobar::InitNotifyIconData(HWND Foo)
{
  NOTIFYICONDATA IconData;
  memset( &IconData, 0, sizeof( NOTIFYICONDATA ) ) ;
  IconData.cbSize = sizeof(NOTIFYICONDATA);
  IconData.hWnd = Foo;
  IconData.uID = ID_TRAY_APP_ICON;
  IconData.uFlags = NIF_ICON | 
    NIF_MESSAGE | 
    NIF_TIP;     
  IconData.uCallbackMessage = WM_TRAYICON; 
  IconData.hIcon = (HICON)LoadImage( NULL, TEXT("Documentation.ico"), IMAGE_ICON, 0, 0, LR_LOADFROMFILE  ) ;
  strcpy(IconData.szTip, TEXT("Boo ya!"));
  return IconData.hIcon;
}

bool Foobar::Contains(const string iStr, const string sStr)
{
        size_t contains;
 
        contains = iStr.find(sStr);
 
        if(contains != string::npos)
                return true;
        else
                return false;
}

void Foobar::Init(HWND Foo)
{
 hINet = InternetOpen("InetURL/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );
 HMODULE hDLL = LoadLibrary ("user32");
 SetWindowLong(Foo, 
                 GWL_EXSTYLE , 
                 GetWindowLong(Foo, GWL_EXSTYLE) | WS_EX_LAYERED);
 pSetLayeredWindowAttributes = (PSLWA) GetProcAddress(hDLL, "SetLayeredWindowAttributes");
 pSetLayeredWindowAttributes(Foo,RGB(255,255,255),220,LWA_ALPHA);
 SystemParametersInfoA(SPI_GETWORKAREA,0,&Pos,0);
 SetWindowPos(Foo ,
                HWND_TOPMOST,
                GetX(),
                GetY(),
                WINDOW_WIDTH,  // width
                WINDOW_HEIGHT, 
                SWP_SHOWWINDOW  //idemo bejbi
           );       
 FooBar = GetFoo();
 CheckV(); 
}
void Foobar::SetTrans(unsigned int Faktor, HWND Foo)
{
  pSetLayeredWindowAttributes(Foo,RGB(255,255,255),Faktor,LWA_ALPHA);
}
void Foobar::CheckV()
{
   SendMessage(FooBar, 0x0D,999,(LPARAM)SongT); //proveri verziju
   if(Contains(SongT, "v0.9.6.3"))
    {
     REGEX = "  [foobar2000 v0.9.6.3]";
    }
   else if(Contains(SongT,"v0.9.6.4"))
    {
     REGEX = "  [foobar2000 v0.9.6.4]"; 
    }
   else if(Contains(SongT,"v0.9.6.9"))
    {
     REGEX = "  [foobar2000 v0.9.6.9]";
     }
   else if(Contains(SongT,"v0.9.6.2"))
    {
     REGEX = "  [foobar2000 v0.9.6.2]";
    }
   else if(Contains(SongT,"v0.9.5.3"))
    {
     REGEX = "  [foobar2000 v0.9.5.3]";
    } 
}
bool Foobar::CheckOnTop(HWND hwnd)
{
      if(!checkontop)
       {
        SetWindowPos(hwnd ,
                HWND_TOPMOST,
                GetX(),
                GetY(),
                WINDOW_WIDTH,
                WINDOW_HEIGHT, 
                SWP_SHOWWINDOW
           );        
       checkontop = true;
       return false;
       }
       else
       {
        SetWindowPos(hwnd,
                HWND_NOTOPMOST,
                GetX(),
                GetY(),
                WINDOW_WIDTH,
                WINDOW_HEIGHT,
                SWP_SHOWWINDOW 
           ); 
         checkontop = false;
         return true;
       }
}

unsigned int Foobar::GetX()
{
   return Pos.right-WINDOW_WIDTH;  
}


unsigned int Foobar::GetY()
{
   return Pos.bottom-WINDOW_HEIGHT;  
}

bool Foobar::Provera()
{
          SendMessage(FooBar, 0x0D,200,(LPARAM)SongT);
          Song = SongT;
          Position = Song.find(" - [");
          artist = Song.substr(0,Position);
          Position = Song.find("] ");
          Song = Song.substr(Position+2,Song.size());
          Position = Song.find(REGEX);
          title = Song.substr(0,Position);
          Song.clear(); 
          delete []SongT;
          URL.clear();         
          URL = "http://www.lyricsplugin.com/winamp03/plugin/?artist=";
          URL.append(artist);
          URL.append("&title=");
          URL.append(title);      
             
   if(tempURL.compare(URL)!=0)
   return true;
   else return false;
}  
bool Foobar::GetSong()
{
     if(FooBar!=0){
          Fetch();
          return true;
      }
      else{
        return false;
       }
}



void Foobar::Fetch()
{ 
       URL.clear();         
       URL = "http://www.lyricsplugin.com/winamp03/plugin/?artist=";
       URL.append(artist);
       URL.append("&title=");
       URL.append(title);
       hFile = InternetOpenUrl( hINet, URL.c_str(), NULL, 0, 0, 0 ); 
       
        if(hFile)
          {
           Counter=0;
           InternetReadFile( hFile, Buffer,2001, &dwRead );
           tBuffer = Buffer;
           DivLyr = tBuffer.find("<div id=\"lyrics\">");
           tBuffer = tBuffer.substr(DivLyr+18,tBuffer.size()); //jebo te bogG!!!#!#
           Kraj = tBuffer.find("</div>");
           tBuffer = Buffer;
           tBuffer = tBuffer.substr(DivLyr+18,Kraj);
           Position = tBuffer.find( "<br />" );
            while ( Position <= tBuffer.size() ) 
             {
              tBuffer.replace( Position, 6, "" );
              Position = tBuffer.find( "<br />", Position + 1 );
             }
           Counter++; 
           tempURL = URL;
           title.clear();
           URL.clear();
           artist.clear();
           if(Counter<=1)
            {
             Lyrics = tBuffer;
             tBuffer.clear();
             Counter=0;
             Buffer = new char[2000 + 1];
            }
          }
        else
          {
           tBuffer = "Haz you no internetz ?!";
          }        
   
}
