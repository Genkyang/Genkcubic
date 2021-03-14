#include <lvgl.h>
#include <TFT_eSPI.h>
#include "Network.h"
#include "GUI_Home.h"
//#include "GUI_Input.h"
#define LVGL_TICK_PERIOD 2

 extern lv_obj_t* scr1 ;
 extern lv_obj_t* scr2 ;
 extern lv_obj_t* label1;
 int flag2 = 1;
 extern char temperchar[3];

TFT_eSPI tft = TFT_eSPI(); /* TFT instance */
static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];
extern char weather_info;
long times = 0;
Network wifi;
GUI_Home guihome;
//extern lv_obj_t * label1;

#if LV_USE_LOG != 0

/* --------- INPUT TEST ----------*/

lv_indev_t* indev_keypad;

lv_indev_state_t keypad_state;


/* --------- Serial debugging ----------*/
void my_print(lv_log_level_t level, const char* file, uint32_t line, const char* fun, const char* dsc)
{
	Serial.printf("%s@%d %s->%s\r\n", file, line, fun, dsc);
	Serial.flush();
}
#endif

/* ------- Display flushing --------*/
void my_disp_flush(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors(&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}


//--------- LVGL module DEFINE-----------//

long date = 0;long time1;
uint8_t date_cotter = 0;

//-------------------------------------//



void setup()
{
	Serial.begin(115200); /* prepare for possible serial debug */

	lv_init();

#if LV_USE_LOG != 0
	lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif

	tft.begin(); /* TFT init */
	tft.setRotation(0); /* mirror */ //0正常，4翻转

 #define BUTTON1_PIN 4
 #define BUTTON2_PIN 25
 #define BUTTON3_PIN 16
  pinMode(BUTTON1_PIN,INPUT);
  pinMode(BUTTON2_PIN,INPUT);
  pinMode(BUTTON3_PIN,INPUT);
  pinMode(5,OUTPUT);
	lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);
  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = 240;  //resolution 240x240
  disp_drv.ver_res = 240;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.buffer = &disp_buf;
  lv_disp_drv_register(&disp_drv);
  guihome.init();
  wifi.init("AT&T 5G", "z98052816");
  wifi.getWeather();
  
//    String ssid = tf.readFileLine("/wifi.txt", 1);    // line-1 for WiFi ssid
//    String password = tf.readFileLine("/wifi.txt", 2);  // line-2 for WiFi password
}


static void roller_callback(struct _lv_obj_t * obj, lv_event_t event)
{
  static int i = 0;
  if(event == LV_EVENT_CLICKED){
    printf("\r\nclick = %d",event);
    if(i++ >=6)
      i=0;
    lv_roller_set_selected(obj, i, LV_ANIM_OFF);
  }
}

static bool keypad_read(lv_indev_drv_t* indev_drv, lv_indev_data_t* data)
{
  static uint32_t last_key = 0;
  uint32_t act_key = keypad_get_key();
    if(act_key != 0) {
        data->state = LV_INDEV_STATE_PR;

        /*Translate the keys to LVGL control characters according to your key definitions*/
        switch(act_key) {
        case 1:
            act_key = LV_KEY_NEXT;           
            break;
        case 2:
            act_key = LV_KEY_PREV;
            break;
        case 3:
            act_key = LV_KEY_LEFT;
            break;
        case 4:
            act_key = LV_KEY_RIGHT;
            break;
        case 5:
            act_key = LV_KEY_ENTER;
            break;
                        //这个是我自己添加 我想在某个控件监听返home键，官方默认的只有1-5 ，我自己加了 6 == 》 home 键
        case 6:
            act_key = LV_KEY_HOME;
            break;
        }

        last_key = act_key;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }

    data->key = last_key;
  /*Return `false` because we are not buffering and no more data to read*/
  return false;
}

static uint32_t keypad_get_key(void)
{
    /*Your code comes here*/
    //这是我添加获取按键值相关的操作
  if( digitalRead(BUTTON1_PIN) ){
    return 1; //和 LV_KEY_NEXT 对应 
  }else if( digitalRead(BUTTON2_PIN) ){
    return 6; //自己添加和 LV_KEY_HOME 对应
  }else if( digitalRead(BUTTON3_PIN) ){
    return 5; //和 LV_KEY_ENTER 对应 
  }
    return 0;
}



void loop()
{



  digitalWrite(5,LOW);
  guihome.RUN();
	lv_task_handler(); /* let the GUI do its work */
 // Serial.println(weather_info);
  usleep(1000);   /*Sleep for 5 millisecond*/
  lv_tick_inc(LVGL_TICK_PERIOD);
  times++;
  //wifi.getTime();
  if (times == 1000000)
    {
      times = 0;
      wifi.getWeather();
      Serial.println("Updated");
    }
    
    if(flag2 ==1)
    {
    
    flag2 = 0;
      }

  
  
 // lv_scr_load_anim(scr1, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 3000, false);
}
