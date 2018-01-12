/*
**    TP CPE Lyon
**    Copyright (C) 2018 Camille FARINEAU / Ahmed LOUDGHIRI / Xuan-Vinh TRAN
**
**    Video Games Module - Sauver le soldat Rohmer
**
**    events.hpp
**    Handle the different events
*/

#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <vector>
#include "constantes.h"
#include "character.h"
#include "pnj.h"
#include "gui_ids.h"
#include "particle.h"

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
    // Boolean to know if the the main character is running
    bool is_running =false;

    // Speed of the main_character
    f32 vitesse_deplacement = 3;

    // Old position of the mouse pointer
    int  old_x, old_y;

    // Vector of textures
    std::vector<irr::video::ITexture*> textures;

    // Int to know which texture to apply
    int current_texture;

    // Boolean to know if the attack is finished (for the animation)
    bool attack_finished = false;

    // Function to update the scene if there was a mouse event
    bool update_mouse_event(const SEvent &event);

    // Array of all keys of the keyboard : boolean to know if the key is currently pressed
    bool KeyIsDown[KEY_KEY_CODES_COUNT];

    // Array of all keys of the keyboard : boolean to know if there was an event with the key (just pressed or released)
    bool KeyEvent[KEY_KEY_CODES_COUNT];

    // Function to update the scene if there was a keyboard event : update the arrays KeyIsDown and KeyEvent
    bool update_key_event(const SEvent &event);

    // Function to intialize the arrays KeyEvent and KeyIsDown
    void init_KeyEvent();

    // Function return a boolean corresponding if the key passed in parameter in down or not
    bool IsKeyDown(EKEY_CODE keyCode) const;

    // Function return a boolean corresponding if the key passed in parameter was just pressed
    bool IsKeyPressed(EKEY_CODE keyCode) const;

    // Function return a boolean corresponding if the key passed in parameter was just released
    bool IsKeyReleased(EKEY_CODE keyCode) const;

    // Boolean to know if the main character is currently jumping
    bool jump = false;

    // Max height for the jump
    f32 height_jump =0.0f;

public:
    EventReceiver();
    /**
     * @brief is_mouse_camera_tool_activated: boolean to know if the camera is following the mouse pointer or not
     */
    bool is_mouse_camera_tool_activated;
    /**
     * @brief button_pressed: know if a the left button of mouse has been pressed
     */
    bool button_pressed = true;

    /**
     * @brief attack: Know if the the main character is attacking
     */
    bool attack = false;

    /**
     * @brief show_menu: know if the menu / opening scene should be print
     */
    int show_menu = 1;

    /**
     * @brief persoonage: A Character instance (useful for movement)
     */
    Character *personnage;
    /**
     * @brief rohmer: a pnj class instance (useful for the animation of the pnj)
     */
    pnj *rohmer;
    /**
     * @brief camera_node: node to handle the camera
     */
    irr::scene::ICameraSceneNode *camera_node;
    /**
     * @brief init_Key : Initialize all the key in the arrays
     */
    void init_Key();
    /**
     * @brief keyboard_handler : Handle all the action linked to a key
     * @return false everytime
     */
    bool keyboard_handler(bool death, bool follow);
    /**
     * @brief mouse_handler : Handle all the action linked to the mouse
     * @param event : click event
     * @return false everytime
     */
    bool mouse_handler(const irr::SEvent &event);
    /**
     * @brief OnEvent : Handle all the events
     * @param event : a particular event (mouse, keyboard)
     * @return false everytime
     */
    bool OnEvent(const irr::SEvent &event);
    /**
     * @brief set_personnage
     * @param perso
     */
    void set_personnage(Character *perso);
    /**
     * @brief set_personnage
     * @param perso
     */
    void set_pnj(pnj *rohmer);
    /**
     * @brief set_textures
     * @param tex
     */
    void set_textures(const std::vector<irr::video::ITexture *> &tex){textures=tex;}
    /**
     * @brief is_mouse_pressed : Actions to execute when the left button of the mouse is pressed
     * @param x, y: location of the mouse pointer
     * @return true if the mouse was pressed, else false
     */
    bool is_mouse_pressed(int &x, int &y);
    /**
     * @brief get_attack : Get the attack boolean
     * @return the value of attack boolean
     */
    bool get_attack();
    /**
     * @brief set_attack : Set the attack boolean (Know if the the main character is attacking)
     * @param is_attacking: boolean to apply to attack variable
     */
    void set_attack(bool is_attacking);

};

#endif
