#include <radc++.h>
#include "foobar.h"

PopUpMenu popup;
MenuItem faktor50,faktor100,faktor150,faktor200,faktor250,show,hide,exitm,ontop,about,trans;
Foobar *l;
Form form2("Lyrics",0,0,WINDOW_WIDTH,WINDOW_HEIGHT,RCP_NONE);
RichTextBox Lyrics("Foobar2000 is not running !",AUTO_ID,0,0,WINDOW_WIDTH,WINDOW_HEIGHT,form2);
String timer = "timer";


FormProcedure Loop(FormProcArgs)
{

  	ON_CLOSE() { 
		form2.removeTimer(timer);
        form2.removeTrayIcon(); 
	    delete l; 
        Application.close();	
	}
   ON_TIMER_NOTIFICATION(timer) {
        if(l->Provera())
        {
         if(l->GetSong())
         {               
          Lyrics.setText(l->Lyrics);
         }
         else{
          Lyrics.setText("Foobar2000 is not running !");
         }
        }
	}
	ON_COMMAND_BY_ID(1255)
     {
       l->SetTrans(50,form2.hwnd);
     }
    ON_COMMAND_BY_ID(2555)
     {
       l->SetTrans(100,form2.hwnd);
     }
    ON_COMMAND_BY_ID(3555)
     {
       l->SetTrans(150,form2.hwnd);
     }
    ON_COMMAND_BY_ID(4555)
     {
       l->SetTrans(200,form2.hwnd);
     }
    ON_COMMAND_BY_ID(5555)
     {
       l->SetTrans(255,form2.hwnd);
     } 
    ON_COMMAND_BY(about)
     {
       MessageBox(form2.hwnd,"Goran Mandic i Sale, za dobro covecanstva !!","Daymen!",MB_OK);
     }
    ON_COMMAND_BY(ontop)
     {
       if(!l->CheckOnTop(form2.hwnd))
       {
            ontop.rename("Turn off  'Always stay on top' ");
       }
       else{
            ontop.rename("Always stay on top ");
       }
     }        
    ON_COMMAND_BY(show) form2.visible = true;
    ON_COMMAND_BY(hide) form2.visible = false;
    ON_COMMAND_BY(exitm) Application.close();
    ON_TRAYICON_RIGHT_CLICK(form2)
    {
        popup.show(form2);
    }
    ON_TRAYICON_CLICK(form2)
    {
       if(!form2.visible)
       {
         form2.visible=true;
       }             
       else
       {
         form2.visible = false; 
       }
    }

 return 0;
}





rad_main()

 l = new Foobar();
 l->Init(form2.hwnd);
 form2.moveTo(l->GetX(),l->GetY());
 form2.setTimer(timer, 1 * 500);
 form2.setTrayIcon(l->InitNotifyIconData(form2.hwnd));
 Lyrics.setMargins(5,0);
  show = popup.add("Show",AUTO_ID);
  hide = popup.add("Hide",AUTO_ID);
  exitm = popup.add("Exit",AUTO_ID);
  ontop = popup.add("Turn off  'Always stay on top'",AUTO_ID);
  popup.addSeparator();
  about = popup.add("About",9910);
  popup.addSeparator();
  trans = popup.addPopup("Transparency"); 
			trans.add("50",1255);
			trans.add("100",2555);
			trans.add("150",3555);	
			trans.add("200",4555);
			trans.add("255",5555);
  form2.setProcedure(Loop); 		
rad_end()

