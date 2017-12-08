// events.cpp

#include <irrlicht.h>
#include <iostream>
#include "events.hpp"
#include "gui_ids.h"

#define HAUTEUR_SAUT 14


/**************************************************************************\
 * EventReceiver::EventReceiver                                           *
\**************************************************************************/
EventReceiver::EventReceiver()
    : node(nullptr), button_pressed(false), current_texture(0)
{
}

/*------------------------------------------------------------------------*\
 * EventReceiver::keyboard                                                *
\*------------------------------------------------------------------------*/
bool EventReceiver::keyboard_handler()
{
    if (!node) return false;

    ic::vector3df position = node->getPosition();
    ic::vector3df rotation = node->getRotation();

    if(IsKeyPressed(KEY_ESCAPE))
        exit(0);
    if(is_crouched ) vitesse_deplacement = 1.0f;
    if(is_running) vitesse_deplacement = 4.0f;
    if(!is_crouched && !is_running) vitesse_deplacement = 2.0f;
    if(IsKeyDown(KEY_KEY_Z)){ // Avance
        position.X += vitesse_deplacement * cos(rotation.Y * M_PI / 180.0);
        position.Z += -vitesse_deplacement * sin(rotation.Y * M_PI / 180.0);
    }
    if(IsKeyDown(KEY_KEY_S)){ // Recule
        position.X += -vitesse_deplacement/2 * cos(rotation.Y * M_PI / 180.0);
        position.Z += vitesse_deplacement/2 * sin(rotation.Y * M_PI / 180.0);
    }
    if(IsKeyDown(KEY_KEY_Q)){ // Tourne à droite
        position.X += vitesse_deplacement * cos((rotation.Y-90.0) * M_PI / 180.0);
        position.Z += -vitesse_deplacement * sin((rotation.Y-90.0) * M_PI / 180.0);
    }
    if(IsKeyDown(KEY_KEY_D)){ // Tourne à gauche
        position.X += -vitesse_deplacement * cos((rotation.Y-90.0) * M_PI / 180.0);
        position.Z += vitesse_deplacement * sin((rotation.Y-90.0) * M_PI / 180.0);
    }
    if(IsKeyDown(KEY_KEY_C)){ // S'accroupit
        vitesse_deplacement = 1;
        button_pressed = false;
    }
    if(IsKeyPressed(KEY_KEY_A)){ // Active la course
        is_running = !(is_running);
        is_crouched = 0;
        if(is_crouched){
            if (IsKeyPressed(KEY_KEY_Z))
                node->setMD2Animation(is::EMAT_CROUCH_STAND);
            else
                node->setMD2Animation(is::EMAT_CROUCH_WALK);
        }
        else{
            if (IsKeyDown(KEY_KEY_Z) || IsKeyDown(KEY_KEY_S) || IsKeyDown(KEY_KEY_Q) || IsKeyDown(KEY_KEY_D)){
                node->setMD2Animation(is::EMAT_RUN);
            }
            else
                node->setMD2Animation(is::EMAT_STAND);

        }
    }


    if(IsKeyPressed(KEY_SPACE)){ // Saute
        //node->setMD2Animation(is::EMAT_JUMP);
        jump = true;
    }
    if (jump){
        height_jump++;
        if(height_jump<HAUTEUR_SAUT){
            position.Y+=(HAUTEUR_SAUT-height_jump);
        }
        //Eviter le double saut
        else if(height_jump>45){
            height_jump = 0.0f;
            jump = false;
        }
    }

    if(IsKeyPressed(KEY_KEY_Z) || IsKeyPressed(KEY_KEY_S) || IsKeyPressed(KEY_KEY_Q) || IsKeyPressed(KEY_KEY_D)){
        if(is_crouched){
            node->setMD2Animation(is::EMAT_CROUCH_WALK);
        }
        else{
            node->setMD2Animation(is::EMAT_RUN);
        }
    }

    if(!IsKeyDown(KEY_KEY_Z) && !IsKeyDown(KEY_KEY_S) && !IsKeyDown(KEY_KEY_Q) && !IsKeyDown(KEY_KEY_D)){
        if(is_crouched)
            node->setMD2Animation(is::EMAT_CROUCH_STAND);
        else
            node->setMD2Animation(is::EMAT_STAND);
    }


    if(IsKeyPressed(KEY_KEY_C)){
        is_crouched = !(is_crouched);
        is_running = 0;
        if(is_crouched){
            if (IsKeyPressed(KEY_KEY_Z))
                node->setMD2Animation(is::EMAT_CROUCH_STAND);
            else
                node->setMD2Animation(is::EMAT_CROUCH_WALK);
        }
        else{
            if (IsKeyDown(KEY_KEY_Z) || IsKeyDown(KEY_KEY_S) || IsKeyDown(KEY_KEY_Q) || IsKeyDown(KEY_KEY_D)){
                node->setMD2Animation(is::EMAT_RUN);
            }
            else
                node->setMD2Animation(is::EMAT_STAND);

        }
    }

    node->setPosition(position);
    node->setRotation(rotation);
    init_KeyEvent();

    return false;
}


/*------------------------------------------------------------------------*\
 * EventReceiver::mouse                                                   *
\*------------------------------------------------------------------------*/
bool EventReceiver::mouse_handler(const SEvent &event)
{
  switch(event.MouseInput.Event)
  {
    case EMIE_LMOUSE_PRESSED_DOWN:
      node->setMD2Animation(is::EMAT_ATTACK);
      button_pressed = true;
      old_x = event.MouseInput.X;
      old_y = event.MouseInput.Y;
      break;
    case EMIE_LMOUSE_LEFT_UP:
      button_pressed = false;
      break;
    case EMIE_MOUSE_MOVED:
      if (button_pressed)
      {
          ic::vector3df rotation = node->getRotation();
          rotation.Y += (event.MouseInput.X - old_x);
          node->setRotation(rotation);
          old_x = event.MouseInput.X;
          old_y = event.MouseInput.Y;

      }
      break;
    case EMIE_MOUSE_WHEEL:
      current_texture = (current_texture + 1) % textures.size();
      node->setMaterialTexture(0, textures[current_texture]);
      break;
    default:
      ;
  }

  return false;
}
/*------------------------------------------------------------------------*\
 * EventReceiver::gui_handler                                             *
\*------------------------------------------------------------------------*/
bool EventReceiver::gui_handler(const SEvent &event)
{
    if (!node) return false;
    switch(event.GUIEvent.EventType)
    {
    // Gestion des menus de la barre de menu
    case ig::EGET_MENU_ITEM_SELECTED:
    {
        ig::IGUIContextMenu *menu = (ig::IGUIContextMenu*)event.GUIEvent.Caller;
        s32 item = menu->getSelectedItem();
        s32 id = menu->getItemCommandId(item);
        u32 debug_info = node->isDebugDataVisible();
        switch(id){
        case MENU_NEW_GAME:
            // Faire quelque chose ici !
            break;
        case MENU_QUIT:
            exit(0);

        case MENU_BOUNDING_BOX:
            menu->setItemChecked(item, !menu->isItemChecked(item));
            node->setDebugDataVisible(debug_info ^ is::EDS_BBOX);
            break;

        case MENU_NORMALS:
            menu->setItemChecked(item, !menu->isItemChecked(item));
            node->setDebugDataVisible(debug_info ^ is::EDS_NORMALS);
            break;

        case MENU_TRIANGLES:
            menu->setItemChecked(item, !menu->isItemChecked(item));
            node->setDebugDataVisible(debug_info ^ is::EDS_MESH_WIRE_OVERLAY);
            break;

        case MENU_TRANSPARENCY:
            menu->setItemChecked(item, !menu->isItemChecked(item));
            node->setDebugDataVisible(debug_info ^ is::EDS_HALF_TRANSPARENCY);
            break;

        case MENU_ABOUT:
            gui->addMessageBox(L"Boite About", L"Texte présentant ce super jeu\nd'un intérêt incroyable");
            break;

        }
        break;

    }
        // gestion des boites d'édition de texte
    case ig::EGET_EDITBOX_CHANGED:
    {
        s32 id = event.GUIEvent.Caller->getID();
        if (id == WINDOW_VALUE)
        {
            ic::stringc s = event.GUIEvent.Caller->getText();
            std::cout << "editbox changed:" << s.c_str() << std::endl;
        }
    }
        break;
        // gestion des boutons
    case ig::EGET_BUTTON_CLICKED:
    {
        s32 id = event.GUIEvent.Caller->getID();
        if (id == WINDOW_BUTTON)
            std::cout << "Button clicked\n";
    }
        break;
        // gestion des cases à cocher
    case ig::EGET_CHECKBOX_CHANGED:
    {
        s32 id = event.GUIEvent.Caller->getID();
        if (id == WINDOW_CHECK_BOX)
        {
            std::cout << "Check box clicked: ";
            bool checked = ((ig::IGUICheckBox*)event.GUIEvent.Caller)->isChecked();
            if (!checked) std::cout << "un";
            std::cout << "checked\n";
        }
    }
        break;
        // gestion des combo-box
    case ig::EGET_COMBO_BOX_CHANGED:
    {
        s32 id = event.GUIEvent.Caller->getID();
        if (id == WINDOW_COMBO_BOX)
        {
            ig::IGUIComboBox *cbox = (ig::IGUIComboBox*)event.GUIEvent.Caller;
            s32 item = cbox->getSelected();
            u32 elem_id = cbox->getItemData(item);
            std::cout << "Combo box changed: item " << item << ", id " << elem_id << std::endl;
        }
    }
        break;
        // Gestion des listes
    case ig::EGET_LISTBOX_CHANGED:
    {
        s32 id = event.GUIEvent.Caller->getID();
        if (id == WINDOW_LIST_BOX)
        {
            ig::IGUIListBox *lbox = (ig::IGUIListBox*)event.GUIEvent.Caller;
            s32 item = lbox->getSelected();
            std::cout << "List box changed: item " << item << std::endl;
        }
    }
        break;
        // Gestion des barres de défilement
    case ig::EGET_SCROLL_BAR_CHANGED:
    {
        s32 id = event.GUIEvent.Caller->getID();
        if (id == WINDOW_SCROLLBAR)
        {
            ig::IGUIScrollBar *scroll = (ig::IGUIScrollBar*)event.GUIEvent.Caller;
            s32 value = scroll->getPos();
            std::cout << "Scrollbar moved: " << value << std::endl;
        }
    }
        break;
        // Gestion des spinbox
    case ig::EGET_SPINBOX_CHANGED:
    {
        s32 id = event.GUIEvent.Caller->getID();
        if (id == WINDOW_SPIN_BOX)
        {
            ig::IGUISpinBox *spin = (ig::IGUISpinBox*)event.GUIEvent.Caller;
            f32 value = spin->getValue();
            std::cout << "Spin Box changed: " << value << std::endl;
        }
    }
        break;
    default:;
    }



    return false;

}


/*------------------------------------------------------------------------*\
 * EventReceiver::update_key_event                                             *
\*------------------------------------------------------------------------*/
bool EventReceiver::update_key_event(const SEvent &event)
{
    KeyEvent[event.KeyInput.Key] = KeyIsDown[event.KeyInput.Key] != event.KeyInput.PressedDown;

    KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    return event.KeyInput.PressedDown;

}
void EventReceiver::init_Key() {
    for (u32 i = 0; i<KEY_KEY_CODES_COUNT; i++){
        KeyIsDown[i] = false;
        KeyEvent[i]=false;
    }
}
void EventReceiver::init_KeyEvent() {
    for (u32 i = 0; i<KEY_KEY_CODES_COUNT; i++)
        KeyEvent[i] = false;
}
bool EventReceiver::IsKeyDown(EKEY_CODE keyCode) const {
    return KeyIsDown[keyCode];
}

bool EventReceiver::IsKeyPressed(EKEY_CODE keyCode) const {
    return (KeyIsDown[keyCode] && KeyEvent[keyCode]);
}
bool EventReceiver::IsKeyReleased(EKEY_CODE keyCode) const {
    return (!KeyIsDown[keyCode] && KeyEvent[keyCode]);
}

/*------------------------------------------------------------------------*\
 * EventReceiver::update_mouse_event                                             *
\*------------------------------------------------------------------------*/
/*bool EventReceiver::update_mouse_event(const SEvent &event)
{
    ClicEvent[event.MouseInput.Event] = ClicIsDown[event.MouseInput.Event] != event.KeyInput.PressedDown;
    ClicIsDown[event.MouseInput.Event] = event.MouseInput.PressedDown;
    return event.MouseInput.PressedDown;

}
void EventReceiver::init_ClicEvent() {
    for (u32 i = 0; i<KEY_KEY_CODES_COUNT; i++)
        ClicEvent[i] = false;
}
bool EventReceiver::IsClicDown(EMOUSE_INPUT_EVENT mouseInput) const {
    return ClicIsDown[mouseInput];
}

bool EventReceiver::IsClicPressed(EMOUSE_INPUT_EVENT mouseInput) const {
    return (ClicIsDown[mouseInput] && KeyEvent[mouseInput]);
}
bool EventReceiver::IsClicReleased(EMOUSE_INPUT_EVENT mouseInput) const {
    return (!ClicIsDown[mouseInput] && KeyEvent[mouseInput]);
}*/



/**************************************************************************\
 * EventReceiver::OnEvent                                                 *
\**************************************************************************/
bool EventReceiver::OnEvent(const SEvent &event)
{
    if (!node) return false;
    switch (event.EventType)
    {
    case EET_KEY_INPUT_EVENT:
        return update_key_event(event);
    case EET_MOUSE_INPUT_EVENT:
        return mouse_handler(event);
    case EET_GUI_EVENT:
        return gui_handler(event);
    default:;
    }

    return false;
}

/**************************************************************************\
 * EventReceiver::set_node                                                *
\**************************************************************************/
void EventReceiver::set_node(irr::scene::IAnimatedMeshSceneNode *n)
{
    node = n;
}

/**************************************************************************\
 * EventReceiver::set_gui                                                 *
\**************************************************************************/
void EventReceiver::set_gui(irr::gui::IGUIEnvironment *g)
{
    gui = g;
}
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
