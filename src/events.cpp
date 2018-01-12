/*
**    TP CPE Lyon
**    Copyright (C) 2018 Camille FARINEAU / Ahmed LOUDGHIRI / Xuan-Vinh TRAN
**
**    Video Games Module - Sauver le soldat Rohmer
**
**    events.cpp
**    Handle the different events
*/

#include <iostream>
#include "events.hpp"


#define HAUTEUR_SAUT 14


/**************************************************************************\
 * EventReceiver::EventReceiver                                           *
\**************************************************************************/
EventReceiver::EventReceiver()
    : button_pressed(false), current_texture(0),is_mouse_camera_tool_activated(true)
{
}

/*------------------------------------------------------------------------*\
 * EventReceiver::keyboard
 * Param: death : boolean to know if the main character is dead or not
 *        follow : boolean to know if the pnj character is currently following the main_character
\*------------------------------------------------------------------------*/
bool EventReceiver::keyboard_handler(bool death, bool follow)
{
    if (!personnage->body) return false;

    // Get the principal node of the main_character (the body)
    is::IAnimatedMeshSceneNode *node = personnage->body;

    // Get current position and rotation of the main_character
    ic::vector3df position = node->getPosition();
    ic::vector3df rotation = node->getRotation();

    // If return is pressed then quit menu
    if(IsKeyPressed(KEY_RETURN)){
        show_menu = 0;
    }

    // If escape is pressed then quit the game / app
    if(IsKeyPressed(KEY_ESCAPE))
        exit(0);

    // If the main_character is dead then there is no need to handle the keys except from escape
    if(death)
        return false;

    //Handle the speed of the main_character
    if(is_running) vitesse_deplacement = RUN_VITESSE_MAIN_CHARACTER;
    else vitesse_deplacement = WALK_VITESSE_MAIN_CHARACTER;

    // If R is pressed the weapon of the main_character will reload
    if(IsKeyDown(KEY_KEY_R)){
        personnage->reload();
    }

    // Handle the movement of the main_character with the ZQSD keys
    if(IsKeyDown(KEY_KEY_Z)){ // Forward
        position.X += vitesse_deplacement * cos(rotation.Y * M_PI / 180.0);
        position.Z += -vitesse_deplacement * sin(rotation.Y * M_PI / 180.0);
    }
    if(IsKeyDown(KEY_KEY_S)){ // Backward
        position.X += -vitesse_deplacement/2 * cos(rotation.Y * M_PI / 180.0);
        position.Z += vitesse_deplacement/2 * sin(rotation.Y * M_PI / 180.0);
    }
    if(IsKeyDown(KEY_KEY_Q)){ // Right strafe
        position.X += vitesse_deplacement * cos((rotation.Y-90.0) * M_PI / 180.0);
        position.Z += -vitesse_deplacement * sin((rotation.Y-90.0) * M_PI / 180.0);
    }
    if(IsKeyDown(KEY_KEY_D)){ // Left strafe
        position.X += -vitesse_deplacement * cos((rotation.Y-90.0) * M_PI / 180.0);
        position.Z += vitesse_deplacement * sin((rotation.Y-90.0) * M_PI / 180.0);
    }

    // Handle if the main_character is running or walking (will handle animation and speed of the main and pnj character)
    if(IsKeyPressed(KEY_KEY_A)){
        is_running = !(is_running);
        if (is_running && (IsKeyDown(KEY_KEY_Z) || IsKeyDown(KEY_KEY_S) || IsKeyDown(KEY_KEY_Q) || IsKeyDown(KEY_KEY_D))){
            personnage->setAnimation(personnage->RUN);
            if(follow)
                rohmer->setAnimation(rohmer->RUN);
        }
        else if(!is_running && (IsKeyDown(KEY_KEY_Z) || IsKeyDown(KEY_KEY_S) || IsKeyDown(KEY_KEY_Q) || IsKeyDown(KEY_KEY_D)))
        {
            personnage->setAnimation(personnage->WALK);
            if(follow)
                rohmer->setAnimation(rohmer->WALK);
        }
        else
        {
            personnage->setAnimation(personnage->STAND);
            if(follow)
                rohmer->setAnimation(rohmer->STAND);
        }
    }

    // Handle the jump of the main_character if space is pressed
    if(IsKeyPressed(KEY_SPACE)){ // Saute
        jump = true;
    }
    if (jump){
        height_jump++;
        if(height_jump<HAUTEUR_SAUT){
            position.Y+=(HAUTEUR_SAUT-height_jump);
        }
        // To avoid double jump
        else if(height_jump>45){
            height_jump = 0.0f;
            jump = false;
        }
    }

    // Handle the movement of the main and pnj character depending on the keys that are pressed
    if(IsKeyPressed(KEY_KEY_Z) || IsKeyPressed(KEY_KEY_S) || IsKeyPressed(KEY_KEY_Q) || IsKeyPressed(KEY_KEY_D)){
        if(!attack)
        {
            if(is_running)
            {
                personnage->setAnimation(personnage->RUN);
                if(follow)
                    rohmer->setAnimation(rohmer->RUN);
            }

            else
            {
                personnage->setAnimation(personnage->WALK);
                if(follow)
                    rohmer->setAnimation(rohmer->WALK);
            }

        }
        else
        {
            personnage->setAnimation(personnage->ATTACK);
        }

    }

    // Handle the animation of the main and pnj character if they are not attacking or just finished to attack
    if(!attack && attack_finished)
    {
        attack_finished = false;
        if(IsKeyDown(KEY_KEY_Z) || IsKeyDown(KEY_KEY_S) || IsKeyDown(KEY_KEY_Q) || IsKeyDown(KEY_KEY_D))
        {
            if(is_running)
            {
                personnage->setAnimation(personnage->RUN);
                if(follow)
                    rohmer->setAnimation(rohmer->RUN);
            }

            else
            {
                personnage->setAnimation(personnage->WALK);
                if(follow)
                    rohmer->setAnimation(rohmer->WALK);
            }

        }
    }

    // Handle the animation of the main and pnj character if they just finished to move
    if(!IsKeyDown(KEY_KEY_Z) && !IsKeyDown(KEY_KEY_S) && !IsKeyDown(KEY_KEY_Q) && !IsKeyDown(KEY_KEY_D)){
        if(!(*this).attack)
        {
            personnage->setAnimation(personnage->STAND);
            if(follow)
                rohmer->setAnimation(rohmer->STAND);
        }

    }

    // Press P to deactivate the focus of the camera on the mouse pointer
    if(IsKeyPressed(KEY_KEY_P)){
        is_mouse_camera_tool_activated = !is_mouse_camera_tool_activated;
    }

    // Set the new position and rotatin of the main_character
    node->setPosition(position);
    node->setRotation(rotation);
    // Clear the different arrays of keys
    init_KeyEvent();
    std::cout<< position.X <<" "<<position.Y <<"  "<<position.Z<<std::endl;
    return false;
}


/*------------------------------------------------------------------------*\
 * EventReceiver::mouse
 *  Param: mouse event
 *  Return : false by default
\*------------------------------------------------------------------------*/
bool EventReceiver::mouse_handler(const SEvent &event)
{
  switch(event.MouseInput.Event)
  {
    // If the left button of the mouse is pressed then
    case EMIE_LMOUSE_PRESSED_DOWN:
      // Set the animation of main_character on attacking
      personnage->setAnimation(personnage->ATTACK);
      // Handle the different useful boolean
      button_pressed = true;
      attack = true;
      attack_finished = true;

      // Update the location of the mouse pointer
      old_x = event.MouseInput.X;
      old_y = event.MouseInput.Y;
      break;
    // If the left button is released
    case EMIE_LMOUSE_LEFT_UP:
      // Boolean to know that the button is released
      button_pressed = false;
      break;
    default:;
  }
  return false;
}


/*------------------------------------------------------------------------*\
 * EventReceiver::update_key_event
 *  Param: a key event
 *  Return: if the key, which there was an event on, is now pressed or released
\*------------------------------------------------------------------------*/
bool EventReceiver::update_key_event(const SEvent &event)
{
    // Update the KeyEvent array for the correct key:
    // If the key was not pressed and is is now pressed there there is an event on the key
    // If the key was pressed and still pressed then there is no event on the key
    // If the key was pressed and now release then there is an event on the ley
    KeyEvent[event.KeyInput.Key] = KeyIsDown[event.KeyInput.Key] != event.KeyInput.PressedDown;

    // Update the array KeyIsDown for the correct key : is the key pressed or not
    KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

    // Return is the key pressed or not
    return event.KeyInput.PressedDown;

}

/*------------------------------------------------------------------------*\
 * EventReceiver::init_Key
 *  Initialize the two arrays for the keys: KeyIsDown and KeyEvent
 *  Param:
 *  Return:
\*------------------------------------------------------------------------*/
void EventReceiver::init_Key() {
    for (u32 i = 0; i<KEY_KEY_CODES_COUNT; i++){
        KeyIsDown[i] = false;
        KeyEvent[i]=false;
    }
}
/*------------------------------------------------------------------------*\
 * EventReceiver::init_KeyEvent
 *  Initialize the array KeyEvent
 *  Param:
 *  Return:
\*------------------------------------------------------------------------*/
void EventReceiver::init_KeyEvent() {
    for (u32 i = 0; i<KEY_KEY_CODES_COUNT; i++)
        KeyEvent[i] = false;
}
/*------------------------------------------------------------------------*\
 * EventReceiver::IsKeyDown
 *  return if a particular key is currently down (no matter the state of the key the frame before)
 *  Param: keyCode: a particular key
 *  Return:
\*------------------------------------------------------------------------*/
bool EventReceiver::IsKeyDown(EKEY_CODE keyCode) const {
    return KeyIsDown[keyCode];
}
/*------------------------------------------------------------------------*\
 * EventReceiver::IsKeyPressed
 *  return if a particular key was just pressed right now (not pressed the frame before and now pressed)
 *  Param: keyCode: a particular key
 *  Return:
\*------------------------------------------------------------------------*/
bool EventReceiver::IsKeyPressed(EKEY_CODE keyCode) const {
    return (KeyIsDown[keyCode] && KeyEvent[keyCode]);
}
/*------------------------------------------------------------------------*\
 * EventReceiver::IsKeyReleased
 *  return if a particular key was just released
 *  Param: keyCode: a particular key
 *  Return:
\*------------------------------------------------------------------------*/
bool EventReceiver::IsKeyReleased(EKEY_CODE keyCode) const {
    return (!KeyIsDown[keyCode] && KeyEvent[keyCode]);
}



/**************************************************************************\
 * EventReceiver::OnEvent                                                 *
 * Handle the different categories of event
\**************************************************************************/
bool EventReceiver::OnEvent(const SEvent &event)
{
    switch (event.EventType)
    {
    case EET_KEY_INPUT_EVENT:
        return update_key_event(event);
    case EET_MOUSE_INPUT_EVENT:
        return mouse_handler(event);
    default:;
    }

    return false;
}

/**************************************************************************\
 * EventReceiver::set_personnage                                          *
 * Set the main_character
\**************************************************************************/
void EventReceiver::set_personnage(Character *perso)
{
    personnage = perso;
}

/**************************************************************************\
 * EventReceiver::set_pnj                                                 *
 * Set the pnj character
\**************************************************************************/
void EventReceiver::set_pnj(pnj *pnj_perso)
{
    rohmer = pnj_perso;
}


/**************************************************************************\
 * EventReceiver::is_mouse_pressed                                        *
 * Know the location of the mouse pointer and return true if the mouse is pressed
 * Param: x, y the location of the mouse pointer
\**************************************************************************/
bool EventReceiver::is_mouse_pressed(int &x, int &y)
{
  if (button_pressed)
  {
    x = old_x;
    y = old_y;
    return true;
  }
  return false;
}
/**************************************************************************\
 * EventReceiver::get_attack()                                               *
\**************************************************************************/
bool EventReceiver::get_attack()
{
    return attack;
}

/**************************************************************************\
 * EventReceiver::set_attack()                                               *
\**************************************************************************/
void EventReceiver::set_attack(bool is_attacking)
{
    (*this).attack = is_attacking;
}
