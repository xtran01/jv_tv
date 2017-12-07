// events.hpp

#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <vector>

#include <irrlicht.h>
using namespace irr;


namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;

class EventReceiver : public irr::IEventReceiver
{
  irr::gui::IGUIEnvironment *gui;
  bool button_pressed = true;
  bool is_crouched =false;
  bool is_running =false;
  float vitesse_deplacement = 2;
  is::EMD2_ANIMATION_TYPE last_pos = is::EMAT_STAND ;

  int  old_x, old_y;
  std::vector<irr::video::ITexture*> textures;
  int current_texture;



  bool ClicIsDown[KEY_KEY_CODES_COUNT];
  bool ClicEvent[KEY_KEY_CODES_COUNT];
  bool update_mouse_event(const SEvent &event);
  bool mouse_handlertest();
 void init_ClicEvent();
  bool IsClicDown(EMOUSE_INPUT_EVENT mouseInput) const;
  bool IsClicPressed(EMOUSE_INPUT_EVENT mouseInput) const;
  bool IsClicReleased(EMOUSE_INPUT_EVENT mouseInput) const;

  bool gui_handler(const irr::SEvent &event);
  bool KeyIsDown[KEY_KEY_CODES_COUNT];
  bool KeyEvent[KEY_KEY_CODES_COUNT];
  bool update_key_event(const SEvent &event);
  void init_KeyEvent();
  bool IsKeyDown(EKEY_CODE keyCode) const;
  bool IsKeyPressed(EKEY_CODE keyCode) const;
  bool IsKeyReleased(EKEY_CODE keyCode) const;
  bool jump = false;
  float height_jump =0.0f;

public:
  EventReceiver();
  float rotation_cam =0.0f;
  irr::scene::IAnimatedMeshSceneNode *node;
  irr::scene::ICameraSceneNode *camera_node;
    void init_Key();
  bool keyboard_handler();
  bool mouse_handler(const irr::SEvent &event);
  bool OnEvent(const irr::SEvent &event);
  void set_gui(irr::gui::IGUIEnvironment *gui);
  void set_node(irr::scene::IAnimatedMeshSceneNode *node);
  void set_textures(const std::vector<irr::video::ITexture *> &tex){textures=tex;}
  bool is_mouse_pressed(int &x, int &y);

};

#endif
