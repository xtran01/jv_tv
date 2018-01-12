/*
**    TP CPE Lyon
**    Copyright (C) 2018 Camille FARINEAU / Ahmed LOUDGHIRI / Xuan-Vinh TRAN
**
**    Video Games Module - Sauver le soldat Rohmer
**
**    main.cpp
*/


#include <irrlicht.h>
#include "events.hpp"
#include "gui_ids.h"
#include <iostream>
#include "enemy.h"
#include "character.h"
#include "particle.h"
#include "pnj.h"
#include <unistd.h>

using namespace irr;
namespace iv = irr::video;
namespace is = irr::scene;
namespace ic = irr::core;
namespace ig = irr::gui;



f32 direction;
f32 zdirection;
const u32 MAP_ID = 1;
const u32 HEIGHT_WINDOW = 480;
const u32 WIDTH_WINDOW = 640;
const u32 NB_PARTICULE_MAX = 10;
const u32 FIRST_ENEMY_ID = 2;
const u32 NB_ENEMY_MAX  = 10;

bool rohmer_found = false;
bool win = false;


/*------------------------------------------------------------------------*\
 * Function moveCameraControl
 * Camera will follow the mouse pointer and update the rotation of the camera
 *  Param: device, perso (main character), receiver
 *  Return :
\*------------------------------------------------------------------------*/
void moveCameraControl(IrrlichtDevice *device,
                       is::IAnimatedMeshSceneNode *perso,
                       EventReceiver receiver)
{
    // Get the position of the cursor
    ic::vector2d<f32> cursorPos = device->getCursorControl()->getRelativePosition();
    // Get the camera
    scene::ICameraSceneNode* camera = device->getSceneManager()->getActiveCamera();

    // Know the movement of the cursor from its previous position
    f32 change_x = ( cursorPos.X - 0.5 ) * 100.0f;
    f32 change_y = ( cursorPos.Y - 0.5 ) * 100.0f;
    direction += change_x;
    zdirection -= change_y;
    if( zdirection < -90 )
        zdirection = -90;
    else
        if( zdirection > 5 ) //Block the verticality of the camera
            zdirection = 5;

    // If the user wants to play (press p to deactivate the cursor / camera system)
    if(receiver.is_mouse_camera_tool_activated){
        // Set the position of the cursos in the center of the window
        device->getCursorControl()->setPosition( 0.5f, 0.5f );
        // Get position of the main character
        core::vector3df playerPos = perso->getPosition();

        // Update the camera target
        f32 xf = playerPos.X - cos( direction * M_PI / 180.0f ) * 64.0f;
        f32 yf = playerPos.Y - sin( zdirection * M_PI / 180.0f ) * 134.0f;
        f32 zf = playerPos.Z + sin( direction * M_PI / 180.0f ) * 64.0f;
        camera->setPosition( core::vector3df( xf, yf+10.0f, zf ) );
        camera->setTarget( core::vector3df( playerPos.X, playerPos.Y + 70.0f,playerPos.Z ) );
        // Update the rotation of the main character
        perso->setRotation( core::vector3df( 0, direction, 0 ) );

    }
}
/*------------------------------------------------------------------------*\
 * Function create_window_pnj_follow
 * Show the window if the main character as reached the pnj character
 *  Param: receiver
 *  Return :
\*------------------------------------------------------------------------*/
static void create_window_pnj_follow(EventReceiver *receiver)
{
    // Show the menu / window for the meeting of the pnj and main character
    if (!rohmer_found){
        receiver->show_menu = 2;
        rohmer_found = true;
    }
}


/*------------------------------------------------------------------------*\
 * Function mission_reussie
 * Verify if the pnj has met the location of the extraction point
 *  Param: pnj character
 *  Return : if the pnj has met the extraction point
\*------------------------------------------------------------------------*/
static bool mission_reussie(pnj& pnj)
{
    core::vector3df location_end(11.7243, 1051.75, -565.804);
    float epsilon = 15.0f;
    if(pnj.body->getAbsolutePosition().getDistanceFrom(location_end) < epsilon)
    {
        return true;
    }
    return false;

}

/*------------------------------------------------------------------------*\
 * Function create_exit
 * Create the billboard to simulate an extraction point
 *  Param: smgr and texture_fin
 *  Return :
\*------------------------------------------------------------------------*/
static void create_exit(is::ISceneManager *smgr, iv::ITexture* texture_fin)
{

    is::IBillboardSceneNode* bill;
    bill = smgr->addBillboardSceneNode(nullptr, core::dimension2d<f32>(400, 400), core::vector3df(11.7243, 1051.75, -565.804));
    bill->setMaterialFlag(video::EMF_LIGHTING, false);
    bill->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    bill->setMaterialTexture(0, texture_fin);
}

/*------------------------------------------------------------------------*\
 * Function is_attacking
 * Change the texture of the weapon and set mf (explosion at the end of the weapon
 * if the main character is attacking
 * Wait for the end of the animation (or no more bullets) to change the textures back and set mf invisible
 *  Param: character, textures, receiver, compteur_attack
 *  Return :
\*------------------------------------------------------------------------*/
void is_attacking(Character& character,std::vector<iv::ITexture*>& textures,
                  EventReceiver& receiver, int& compteur_attack)
{
    bool attacking = receiver.get_attack();
    if(attacking)
    {
        // Change texture of the weapon and put the explosion at the end of the weapon
        character.change_texture_weapon_fire(textures);
        character.mf->setVisible(true);
        compteur_attack++;
        // If there is no more ammo or the character is reloading or the animation if finished then switch back everything
        if(compteur_attack > 12  || character.get_nb_munition() == 0  || character.is_reloading())
        {
            compteur_attack = 0;
            receiver.set_attack(false);
            character.change_texture_weapon_rest(textures);
            character.mf->setVisible(false);
        }
    }
}

/*------------------------------------------------------------------------*\
 * Function is_character_meets_pnj
 * Verify if the main character has met the pnj character
 *  Param: character, pnj
 *  Return :
\*------------------------------------------------------------------------*/
bool is_character_meets_pnj(Character& character,pnj& pnj)
{
    float epsilon = 60.0f;
    if(character.body->getAbsolutePosition().getDistanceFrom(pnj.body->getAbsolutePosition()) < epsilon)
    {
        return true;
    }
    return false;
}


/*------------------------------------------------------------------------*\
 * Function main
 * Handle the general behaviour of the scene
 *
 * NOTE:
 * - This function should have split into several functions and methods
 * - Some variables or gameplay is not correctly handle with the memory and processor usage
 * - Some optimization in the code are necessary
 * But the game is working as it is eventhough there is a need in many improvement in this function
 *
 *
\*------------------------------------------------------------------------*/
int main()
{
    /*******************************************/
    // Prerequities
    // Create an event receiver
    EventReceiver receiver;
    // Création de la fenêtre et du système de rendu.
    IrrlichtDevice *device = createDevice(iv::EDT_OPENGL,
                                          ic::dimension2d < u32 >(WIDTH_WINDOW ,
                                                                  HEIGHT_WINDOW)
                                          ,16 , false , false ,
                                          false , &receiver);
    // Creation of the driver, the scene manager and the gui
    iv::IVideoDriver  *driver = device->getVideoDriver();
    is::ISceneManager *smgr = device->getSceneManager();
    ig::IGUIEnvironment *gui  = device->getGUIEnvironment();


    /*******************************************/
    // TEXTURES
    // Vector of textures for the textures of the characters
    std::vector<iv::ITexture*> textures;
    // Texture for the billboard use at the end
    iv::ITexture* texture_fin;

    // Textures for the digit
    iv::ITexture *digits[10];
    digits[0] = driver->getTexture("../data/0.png");
    digits[1] = driver->getTexture("../data/1.png");
    digits[2] = driver->getTexture("../data/2.png");
    digits[3] = driver->getTexture("../data/3.png");
    digits[4] = driver->getTexture("../data/4.png");
    digits[5] = driver->getTexture("../data/5.png");
    digits[6] = driver->getTexture("../data/6.png");
    digits[7] = driver->getTexture("../data/7.png");
    digits[8] = driver->getTexture("../data/8.png");
    digits[9] = driver->getTexture("../data/9.png");
    // Texture for the slash in ammo
    iv::ITexture *slash_tex = driver->getTexture("../data/slash.png");

    // Textures for the bloody screen if the character has been hit (relative to health point)
    iv::ITexture *bloody_screen_tex = driver->getTexture("../data/bloody_screen.png");
    iv::ITexture *bloodier_screen_tex = driver->getTexture("../data/bloodier_screen.png");

    // Textures for the gameover screen
    iv::ITexture *gameover_screen_tex = driver->getTexture("../data/gameover_screen.png");

    // Textures for the objectives menu after reaching the pnj character
    iv::ITexture *objectif_tex = driver->getTexture("../data/objectif1.png");

    // Textures for the first menu of the game (opening screen)
    iv::ITexture *menu_tex = driver->getTexture("../data/first_menu.png");


    // Creation of the images for the ammunitions left(location in the window)
    ig::IGUIImage *munition_10  = gui->addImage(ic::rect<s32>(WIDTH_WINDOW-210,HEIGHT_WINDOW-60, WIDTH_WINDOW-210+40,HEIGHT_WINDOW+40-60)); munition_10->setScaleImage(true);
    ig::IGUIImage *munition_1   = gui->addImage(ic::rect<s32>(WIDTH_WINDOW-210+40,HEIGHT_WINDOW-60, WIDTH_WINDOW-210+80,HEIGHT_WINDOW+40-60)); munition_1->setScaleImage(true);

    // Creation of the images for the stock of ammunitions left(location in the window)
    ig::IGUIImage *stock_10  = gui->addImage(ic::rect<s32>(WIDTH_WINDOW-100,HEIGHT_WINDOW-60, WIDTH_WINDOW-100+40,HEIGHT_WINDOW+40-60)); stock_10->setScaleImage(true);
    ig::IGUIImage *stock_1   = gui->addImage(ic::rect<s32>(WIDTH_WINDOW-100+40,HEIGHT_WINDOW-60, WIDTH_WINDOW-100+80,HEIGHT_WINDOW+40-60)); stock_1->setScaleImage(true);

    // Creation of the image of the slash between ammo and stock of ammo
    ig::IGUIImage *slash   = gui->addImage(ic::rect<s32>(WIDTH_WINDOW-170+40,HEIGHT_WINDOW-60, WIDTH_WINDOW-170+70,HEIGHT_WINDOW+40-60)); slash->setScaleImage(true);

    // Creation of the image for the different screen that are used
    ig::IGUIImage *bloody_screen   = gui->addImage(ic::rect<s32>(0,0, WIDTH_WINDOW,HEIGHT_WINDOW)); bloody_screen->setScaleImage(true);
    ig::IGUIImage *objectif   = gui->addImage(ic::rect<s32>(0,0, WIDTH_WINDOW,HEIGHT_WINDOW)); objectif->setScaleImage(true);
    ig::IGUIImage *menu   = gui->addImage(ic::rect<s32>(0,0, WIDTH_WINDOW,HEIGHT_WINDOW)); menu->setScaleImage(true);

    // Push the textures in a vector of textures for the main character and the pnj character
    textures.push_back(driver->getTexture("../data/Chaingunner/chaingunner_body.png"));
    textures.push_back(driver->getTexture("../data/Chaingunner/chaingunner_weapon.png"));
    textures.push_back(driver->getTexture("../data/Chaingunner/chaingunner_head1.png"));
    textures.push_back(driver->getTexture("../data/Chaingunner/chaingunner_fire_weapon.png"));
    textures.push_back(driver->getTexture("../data/Chaingunner/chaingunner_mf0.png"));
    textures.push_back(driver->getTexture("../data/Chaingunner/chaingunner_pain_body.png"));
    textures.push_back(driver->getTexture("../data/Chaingunner/chaingunner_head2.png"));
    textures.push_back(driver->getTexture("../data/Chaingunner/chaingunner_die_body.png"));
    textures.push_back(driver->getTexture("../data/Warrior/warrior.jpg"));

    // A different texture object for the billboard use at the end of the game
    texture_fin = driver->getTexture("../data/particlegreen.jpg");

    /*******************************************/
    // MAP

    // Add the archive that contains the map
    device->getFileSystem()->addFileArchive("../data/cf.pk3");
    // Add the bsp (level) corrresponding to the 3D Map :
    is::IAnimatedMesh *mesh_map = smgr->getMesh ("cf.bsp");
    is::IMeshSceneNode *node_map ;
    node_map = smgr->addOctreeSceneNode(mesh_map->getMesh (0), nullptr , -1 , 1024);
    // Translation of the map
    node_map->setPosition (core::vector3df( 200 , -100 , -500));
    // Set an ID for the map
    node_map->setID(MAP_ID);

    // Creation of the triangle selector
    scene::ITriangleSelector *selector;
    selector = smgr->createOctreeTriangleSelector(node_map->getMesh(), node_map);
    node_map->setTriangleSelector(selector);
    node_map->setID(MAP_ID);

    /*******************************************/

    /*******************************************/
    // MAIN CHARACTER
    //create Main character
    Character main_character;
    // Add the character mesh to the scene
    main_character.addCharacterMeshToScene(smgr, textures);
    // Set its animation
    main_character.setAnimation(main_character.RUN);
    // Add a collider (with the map)
    main_character.addCharacterCollider(smgr,selector);

    /*******************************************/

    /*******************************************/
    // PNJ
    // Create pnj
    // His name is Rohmer because of our fabulous assistant professor we had at CPE. This is a tribute to him.
    pnj rohmer;
    // Add the mesh to the scene and add a collider
    rohmer.addPNJMeshToScene(smgr,textures);
    rohmer.addPNJCollider(smgr,selector);
    // Set the stand animation
    rohmer.setAnimation(rohmer.STAND);
    /*******************************************/

    /*******************************************/
    // ENEMIES
    // Create an array of enemy instance
    Enemy enemies[NB_ENEMY_MAX];
    // Create the first enemy ID
    u32 id = FIRST_ENEMY_ID;
    // For loop to create all the enemies
    for(u32 i = 0; i<NB_ENEMY_MAX; i++){
        //create enemy
        // Add it the the scene and add texture and collider with the map
        enemies[i].addEnemyMeshToScene(smgr, main_character.body,device->getRandomizer());
        enemies[i].setTexture(driver->getTexture("../data/Baron/baron.jpg"));
        enemies[i].create_collision_with_map(selector);


        f32 radius = 50.0f;
        f32 r = device->getRandomizer()->frand() * radius;
        f32 teta = device->getRandomizer()->frand() * M_PI * 2.0f;
        ic::vector3df pos(r*cos(teta),0,r*sin(teta));

        // Set the position of the enemy
        enemies[i].setPosition(pos);
        // Set the rotation as random
        f32 angle_enemy = device->getRandomizer()->frand() * 360;
        enemies[i].setRotation(ic::vector3df(0,angle_enemy,0));

        // The enemy will move randomly around his initial position
        enemies[i].move_randomely_arround_waiting_position();
        // Set its ID
        enemies[i].setID(id);
        id++;
    }

    /*******************************************/

    /*******************************************/
    //RECEIVER
    //Set the characters and textures for the event part
    receiver.set_personnage(&main_character);
    receiver.set_pnj(&rohmer);
    receiver.set_textures(textures);
    /*******************************************/

    /*******************************************/
    //CAMERA
    //Creation of the camera
    is::ICameraSceneNode *camera = smgr->addCameraSceneNode(0,core::vector3df(0.0f,0.0f,0.0f) ,core::vector3df(0.0f,0.0f,0.0f), -1);
    direction = 0.0f; zdirection=0.0f;
    //Don't show the cursor of the mouse
    device->getCursorControl()->setVisible(false);
    receiver.camera_node = camera;
    /*******************************************/


    // Reset the arrays for the keyboard's keys
    receiver.init_Key();


    /*******************************************/
    // SCOPE
    // Get the texture for the scope
    iv::ITexture *scope_tex;
    scope_tex= driver->getTexture("../data/scope.png");
    /*******************************************/

    // Create the collision manager
    is::ISceneCollisionManager *collision_manager = smgr->getSceneCollisionManager();

    /*******************************************/
    // Create the array for the particule (ammo) that are shot
    Particle list_part[NB_PARTICULE_MAX];
    for(u32 i=0;i<NB_PARTICULE_MAX;i++){
        list_part[i].initializeParticle(driver->getTexture("../data/particlered.bmp"), driver->getTexture("../data/fireball.bmp"));
    }
    // Counter for the place in the arrays to write
    int i_FIFO = 0;
    // Boolean to know if the array is full
    bool list_part_rempli = false;
    /*******************************************/

    // Counter for the attack animation
    int compteur_attack = 0;
    // Boolean to know if the character is currently attacking
    bool attack_one_tic = false;
    bool last_attack = false;

    // Bool to know if the main character as met the pnj character
    bool meeting = false;
    // Bool to know if the pnj character is currently following the main character
    bool follow = false;
    // Counter for the follow (issue with the location of the differents character at the frame 1)
    int compteur_follow = 0;

    // Bool to know if the character need to start its death anim
    bool start_anim_death = false;
    // Bool to know if the caracter is currently playing is death anim
    bool anim_death = false;
    // Counter for the death animation
    int cpt_anim_death = 0;

    while(device->run())
    {
        driver->beginScene(true, true, iv::SColor(100,150,200,255));
        ig::IGUIImage *scope = gui->addImage(ic::rect<s32>(driver->getScreenSize().Width/2 -15,driver->getScreenSize().Height/2-15,  driver->getScreenSize().Width/2+15,driver->getScreenSize().Height/2+15)); scope->setScaleImage(true);
        //set image for the "viseur"
        scope->setImage(scope_tex);

        if(receiver.show_menu == 0 && !win){
            menu->setVisible(false);
            objectif->setImage(objectif_tex);

            for(u32 i = 0; i<NB_ENEMY_MAX; i++){
                enemies[i].handle_walking();
            }

            if(main_character.getReloading_cooldown()>0 || main_character.get_nb_munition() == 0){
                scope_tex= driver->getTexture("../data/scope_not.png");
            }
            else{
                scope_tex= driver->getTexture("../data/scope.png");
            }

            is_attacking(main_character, textures, receiver, compteur_attack);
            if(main_character.getHealth_point() != 0)
            {
                moveCameraControl(device,main_character.body, receiver);
                receiver.keyboard_handler(false, follow);
            }
            else
                receiver.keyboard_handler(true, follow);

            if(!main_character.is_reloading()){
                int mouse_x, mouse_y;
                if (receiver.is_mouse_pressed(mouse_x, mouse_y))
                {
                    if (receiver.button_pressed != last_attack && receiver.button_pressed == true)
                        attack_one_tic = true;
                    if(attack_one_tic && main_character.get_nb_munition() > 0)
                    {
                        ic::line3d<f32> ray;
                        ray = collision_manager->getRayFromScreenCoordinates(ic::position2d<s32>(mouse_x, mouse_y));
                        ic::vector3df intersection;
                        ic::triangle3df hit_triangle;
                        is::ISceneNode *selected_scene_node =
                                collision_manager->getSceneNodeAndCollisionPointFromRay(
                                    ray,
                                    intersection, // On récupère ici les coordonnées 3D de l'intersection
                                    hit_triangle, // et le triangle intersecté
                                    0); // On ne veut que des noeuds avec cet identifiant
                        const u32 selected_scene_node_id = selected_scene_node->getID();

                        if(selected_scene_node_id == MAP_ID){
                            if (list_part_rempli){ list_part[i_FIFO].remove();}
                            list_part[i_FIFO].addParticleToScene(smgr,main_character.body->getPosition(),intersection);
                            i_FIFO++;
                            if (i_FIFO==NB_PARTICULE_MAX){i_FIFO = 0; list_part_rempli = true;}

                        }

                        for(u32 i=0; i<NB_ENEMY_MAX; i++){
                            //if is an enemy and distance is inferior form range_max
                            if(enemies[i].node->getID() == selected_scene_node_id &&
                                    selected_scene_node->getAbsolutePosition().getDistanceFrom(main_character.body->getAbsolutePosition())<RANGE_MAX){
                                if (list_part_rempli){ list_part[i_FIFO].remove();}
                                list_part[i_FIFO].addParticleToScene(smgr,main_character.body->getPosition(),intersection);
                                i_FIFO++;
                                if (i_FIFO==NB_PARTICULE_MAX){i_FIFO = 0; list_part_rempli = true;}
                                enemies[i].being_hit(driver->getTexture("../data/Baron/baronlight.jpg"));
                            }
                        }

                        attack_one_tic = false;
                        main_character.use_munition();

                    }

                }
            }

            for (u32 k = 0; k<NB_PARTICULE_MAX; k++){
                list_part[k].frame_time_life--;
                if(list_part[k].frame_time_life == 0)
                    list_part[k].remove();
            }

            for(u32 i=0;i<NB_ENEMY_MAX ; i++){
                enemies[i].make_blink(driver->getTexture("../data/Baron/baron.jpg"));
                enemies[i].attack(&main_character);
            }

            main_character.is_invincible(textures);
            last_attack = receiver.button_pressed;



            // Set image2D
            munition_10->setImage(digits[(main_character.get_nb_munition() / 10) % 10]);
            munition_1->setImage(digits[(main_character.get_nb_munition() / 1) % 10]);

            stock_10->setImage(digits[(main_character.get_nb_stock() / 10) % 10]);
            stock_1->setImage(digits[(main_character.get_nb_stock() / 1) % 10]);
            slash->setImage(slash_tex);

            switch(main_character.getHealth_point()){
            case 2 :
                bloody_screen->setVisible(true);
                bloody_screen->setImage(bloody_screen_tex);

                break;
            case 1 :
                bloody_screen->setImage(bloodier_screen_tex);
                break;
            case 0 :
                scope->setVisible(false); // ENLEVER RETICULE A LA MORT

                start_anim_death = true;
                if(cpt_anim_death<=60)
                {
                    main_character.head->setMaterialTexture(0,textures[6]);
                    main_character.body->setMaterialTexture(0,textures[7]);
                    if(start_anim_death == true && anim_death == false)
                    {
                        main_character.setAnimation(main_character.DEATH);
                        rohmer.setAnimation(rohmer.DEATH);
                        anim_death = true;
                    }
                    cpt_anim_death++;
                }
                else if(cpt_anim_death>50)
                {
                    objectif->setVisible(false);
                    bloody_screen->setImage(gameover_screen_tex);
                }
                break;
            default: bloody_screen->setVisible(false);
                scope->setVisible(true);
                break;
            }

            // Gestion suivi PNJ
            compteur_follow++;
            if(compteur_follow > 10)
                meeting = is_character_meets_pnj(main_character,rohmer);
            if(meeting == true && follow == false)
            {
                follow = true;
                create_window_pnj_follow(&receiver);
                create_exit(smgr,texture_fin);
            }


            if(follow == true && meeting == true)
            {
                rohmer.follow(main_character.body->getAbsolutePosition(),main_character.body->getRotation());
            }
            if(meeting == false && follow == true)
            {
                rohmer.setAnimation(rohmer.STAND);
                follow = false;
            }
            if(mission_reussie(rohmer))
            {
                win = true;
            }
            rohmer.position_prev_character = main_character.body->getAbsolutePosition();


        }
        if (receiver.show_menu == 1){
            menu->setVisible(true);
            scope->setVisible(false);
            menu->setImage(menu_tex);
            receiver.keyboard_handler(false, follow);
        }
        if (receiver.show_menu == 2){
            menu_tex = driver->getTexture("../data/dialogue_menu.png");
            scope->setVisible(false);

            menu->setVisible(true);
            menu->setImage(menu_tex);
            receiver.keyboard_handler(true, follow);
            objectif_tex = driver->getTexture("../data/objectif2.png");
        }

        if (win){
            menu_tex = driver->getTexture("../data/win_menu.png");
            scope->setVisible(false);
            menu->setVisible(true);
            menu->setImage(menu_tex);
            receiver.keyboard_handler(true, follow);

        }

        // Dessin de la scène :
        smgr->drawAll();
        gui->drawAll();

        driver->endScene();
    }
    device->drop();

    return 0;
}
