#include "GUI_Home.h"
#include "math.h"
 lv_obj_t* scr1 ;
 lv_obj_t* scr2 ;
 // extern lv_obj_t* gauge1;
 lv_obj_t* img1;
 lv_obj_t* label1;
 LV_IMG_DECLARE(me);
 LV_IMG_DECLARE(Sunny);
 LV_IMG_DECLARE(Thunder);
 LV_IMG_DECLARE(ThunderShower);
 LV_IMG_DECLARE(Cloudy);
 LV_IMG_DECLARE(Night);
 LV_IMG_DECLARE(PartCloudy_Night);
 LV_IMG_DECLARE(PartCloudy);
 LV_IMG_DECLARE(Rain1);
 LV_IMG_DECLARE(Rain2);
 LV_IMG_DECLARE(Rain3);
 LV_IMG_DECLARE(Rain4);
 LV_IMG_DECLARE(Snow1);
 LV_IMG_DECLARE(Snow2);
 LV_IMG_DECLARE(Snow3);
 LV_IMG_DECLARE(Snow4);
  extern long times;
  int flag = 1;
  extern int codeday,temper;
  char temperchar[4] = "---";
void GUI_Home::init(void)
{
  /*Initialize the display*/
 

  static lv_style_t default_style;  //设置Style颜色
  lv_style_init(&default_style);
  lv_style_set_bg_color(&default_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
  lv_style_set_bg_color(&default_style, LV_STATE_PRESSED, LV_COLOR_GRAY);
  lv_style_set_bg_color(&default_style, LV_STATE_FOCUSED, LV_COLOR_BLACK);
  lv_style_set_bg_color(&default_style, LV_STATE_FOCUSED | LV_STATE_PRESSED, lv_color_hex(0xf88));
  lv_obj_add_style(lv_scr_act(), LV_BTN_PART_MAIN, &default_style);


  scr1 = lv_scr_act();    // -------------Screen1-------------//
  img1 = lv_img_create(scr1, NULL);

  lv_img_set_src(img1, &Cloudy);
  lv_obj_align(img1, NULL, LV_ALIGN_CENTER, 0, -20);


  static lv_style_t label_style; 
  lv_style_init(&label_style);
  lv_style_set_text_color(&label_style, LV_LABEL_PART_MAIN, LV_COLOR_WHITE);
  lv_style_set_text_font(&label_style, LV_STATE_DEFAULT, &lv_font_montserrat_48);
  static lv_style_t labelc_style;
  lv_style_init(&labelc_style);
  lv_style_set_text_font(&labelc_style, LV_STATE_DEFAULT, &lv_font_montserrat_18);

  label1 = lv_label_create(scr1, NULL);
  lv_label_set_long_mode(label1, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
  lv_label_set_align(label1, LV_LABEL_ALIGN_RIGHT);       /*Center aligned lines*/
  lv_label_set_text(label1, temperchar);
  lv_obj_add_style(label1, LV_LABEL_PART_MAIN, &label_style);
  lv_obj_set_width(label1, 150);
  lv_obj_align(label1, NULL, LV_ALIGN_CENTER, -10, 65);
  
  lv_obj_t * labelc = lv_label_create(scr1, NULL);
  lv_label_set_long_mode(labelc, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
  lv_label_set_recolor(labelc, true);                      /*Enable re-coloring by commands in the text*/
  lv_label_set_align(labelc, LV_LABEL_ALIGN_CENTER);       /*Center aligned lines*/
  lv_label_set_text(labelc, "#ffffff °C#");
  lv_obj_add_style(labelc, LV_LABEL_PART_MAIN, &labelc_style);
  lv_obj_set_width(labelc, 150);
  lv_obj_align(labelc, NULL, LV_ALIGN_CENTER, 80, 75);

  lv_obj_t * label_city = lv_label_create(scr1, NULL);
  lv_label_set_long_mode(label_city, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
  lv_label_set_recolor(label_city, true);                      /*Enable re-coloring by commands in the text*/
  lv_label_set_align(label_city, LV_LABEL_ALIGN_CENTER);       /*Center aligned lines*/
  lv_label_set_text(label_city, "#ffffff Dongying#");
  lv_obj_add_style(label_city, LV_LABEL_PART_MAIN, &labelc_style);
  lv_obj_set_width(label_city, 150);
  lv_obj_align(label_city, NULL, LV_ALIGN_CENTER, -50, 70);

  
///////////--------end screen1--------///

  scr2 = lv_obj_create(NULL, NULL);
  lv_obj_t* img2 = lv_img_create(scr2, NULL);

  lv_img_set_src(img2, &me);
  lv_obj_align(img2, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_style(scr2, LV_OBJ_PART_MAIN, &default_style);
  lv_scr_load_anim(scr2, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0, false);
 // lv_scr_load_anim(scr1, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 3000, false);
  
  
  static lv_style_t label_shadow_style; 
  lv_style_init(&label_shadow_style);
  lv_style_set_text_color(&label_shadow_style, LV_LABEL_PART_MAIN, LV_COLOR_WHITE);
  lv_style_set_text_font(&label_shadow_style, LV_STATE_DEFAULT, &lv_font_montserrat_18);
  
  lv_obj_t * label2 = lv_label_create(scr2, NULL);
  lv_obj_add_style(label2, LV_LABEL_PART_MAIN, &label_shadow_style);

  lv_label_set_long_mode(label2, LV_LABEL_LONG_SROLL_CIRC);     /*Circular scroll*/
  lv_obj_set_width(label2, 150);
  lv_label_set_text(label2, "Genkyang's Smart Workstation");
  lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 80);

//  scr1 = lv_scr_act();
//  LV_IMG_DECLARE(me);
//  lv_obj_t* img1 = lv_img_create(lv_scr_act(), NULL);
//  lv_img_set_src(img1, &me);
//  lv_obj_align(img1, NULL, LV_ALIGN_CENTER, 0, 0);





}


void GUI_Home::RUN(void)
{

  if(digitalRead(4) && flag==1)
  {
    lv_scr_load_anim(scr1, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 500, 0, false);
    flag=0;
    Serial.println("1");
    }

  if(digitalRead(25) && flag==0)
  {
    lv_scr_load_anim(scr2, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0, false);
    flag=1;
    Serial.println("2");
    }
   



  if(times == 0)//
  {
    if(temper>=10 && temper<=50)
    {
      temperchar[0] = ' ';
      temperchar[1] = (temper/10)+48;
      temperchar[2] = (temper%10)+48;
      }
    else if(temper<0 && temper>-10)
    {
      temperchar[0] = ' ';
      temperchar[1] = '-';
      temperchar[2] = (abs(temper)%10)+48;
      }
    else if(temper<=-10 && temper>=-30)
    {
      temperchar[0] = '-';
      temperchar[1] = (abs(temper)/10)+48;
      temperchar[2] = (abs(temper)%10)+48;
      }
    else if(temper>=0 && temper<10)
    {
      temperchar[0] = ' ';
      temperchar[1] = ' ';
      temperchar[2] = (temper%10)+48;
     }
    else if(temper>50 || temper<-30)
    {
      temperchar[0] = ' ';
      temperchar[1] = '-';
      temperchar[2] = '-';
     }

    switch (codeday)  //Follow the code and change the status  https://docs.seniverse.com/api/start/code.html
    {
      case 0:
          lv_img_set_src(img1, &Sunny);
          break;
      case 1:
          lv_img_set_src(img1, &Night);
          break;
//      case 2:
//          lv_img_set_src(img1, &Cloudy);
//          break;
//      case 3:
//          lv_img_set_src(img1, &Cloudy);
//          break;
      case 4:
          lv_img_set_src(img1, &Cloudy);
          break;
      case 5:
          lv_img_set_src(img1, &PartCloudy);
          break;
      case 6:
          lv_img_set_src(img1, &PartCloudy_Night);
          break;
      case 7:
          lv_img_set_src(img1, &PartCloudy);
          break;
      case 8:
          lv_img_set_src(img1, &PartCloudy_Night);
          break;
      case 9:
          lv_img_set_src(img1, &Cloudy);
          break;
      case 10:
          lv_img_set_src(img1, &Rain1);
          break;
      case 11:
          lv_img_set_src(img1, &ThunderShower);
          break;
      case 12:
          lv_img_set_src(img1, &ThunderShower);
          break;
      case 13:
          lv_img_set_src(img1, &Rain1);
          break;
      case 14:
          lv_img_set_src(img1, &Rain2);
          break;
      case 15:
          lv_img_set_src(img1, &Rain2);
          break;
      case 16:
          lv_img_set_src(img1, &Rain4);
          break;
      case 17:
          lv_img_set_src(img1, &Rain4);
          break;
      case 18:
          lv_img_set_src(img1, &Rain4);
          break;
      case 19:
          lv_img_set_src(img1, &Rain2);
          break;
      case 20:
          lv_img_set_src(img1, &Rain2);
          break;
      case 21:
          lv_img_set_src(img1, &Snow1);
          break;
      case 22:
          lv_img_set_src(img1, &Snow2);
          break;
      case 23:
          lv_img_set_src(img1, &Snow2);
          break;
      case 24:
          lv_img_set_src(img1, &Snow4);
          break;
      case 25:
          lv_img_set_src(img1, &Snow4);
          break;
      }
    
    lv_label_set_text(label1, temperchar);
    
    }
    
   // lv_scr_load_anim(scr1, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 3000, false);
//  if(digitalRead(BUTTON1_PIN))
//  {
//    delay(10);
//    while(digitalRead(BUTTON1_PIN))
//    lv_scr_load_anim(scr1, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 500, 0, false);
//    Serial.println("1");
//    }
//  if(digitalRead(BUTTON2_PIN))
//  {
//    delay(10);
//    while(digitalRead(BUTTON2_PIN))
//    lv_scr_load_anim(scr1, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0, false);
//    Serial.println("2");
//    }
}
