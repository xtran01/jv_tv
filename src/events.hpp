// events.hpp

#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <vector>

#include <irrlicht.h>
#include "character.h"

using namespace irr;


namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;
/**
 * @brief The EventReceiver class
 */
class EventReceiver : public irr::IEventReceiver
{
    irr::gui::IGUIEnvironment *gui;
    bool is_running =false;

    f32 vitesse_deplacement = 2;
    is::EMD2_ANIMATION_TYPE last_pos = is::EMAT_STAND ;

    int  old_x, old_y;
    std::vector<irr::video::ITexture*> textures;
    int current_texture;

    bool attack_finished = false;
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
    f32 height_jump =0.0f;

public:
    EventReceiver();
    bool button_pressed = true;

    bool attack = false;
    bool attack_inter = false;

    f32 rotation_cam =0.0f;
    irr::scene::IAnimatedMeshSceneNode *node;
    Character *personnage;
    irr::scene::ICameraSceneNode *camera_node;
    /**
     * @brief init_Key : Initialize all the key in the arrays
     */
    void init_Key();
    /**
     * @brief keyboard_handler : Handle all the action linked to a key
     * @return false everytime
     */
    bool keyboard_handler();
    /**
     * @brief mouse_handler : Handle all the action linked to the mouse
     * @param event : click event
     * @return false everytime
     */
    bool mouse_handler(const irr::SEvent &event);
    bool OnEvent(const irr::SEvent &event);
    /**
     * @brief set_gui
     * @param gui
     */
    void set_gui(irr::gui::IGUIEnvironment *gui);
    /**
     * @brief set_personnage
     * @param perso
     */
    void set_personnage(Character *perso);
    /**
     * @brief set_textures
     * @param tex
     */
    void set_textures(const std::vector<irr::video::ITexture *> &tex){textures=tex;}
    bool is_mouse_pressed(int &x, int &y);
    bool is_mouse_camera_tool_activated;
    bool get_attack();
    void set_attack(bool is_attacking);

};

#endif
