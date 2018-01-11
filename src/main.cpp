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
const int MAP_ID = 1;
const int ENEMY_1_ID = 1<<1;
const int ENEMY_2_ID = 1<<2;
const int HEIGHT_WINDOW = 480;
const int WIDTH_WINDOW = 640;
const int NB_PARTICULE_MAX = 10;



void moveCameraControl(IrrlichtDevice *device,
                       is::IAnimatedMeshSceneNode *perso,
                       EventReceiver receiver)
{

    ic::vector2d<f32> cursorPos = device->getCursorControl()->getRelativePosition();
    scene::ICameraSceneNode* camera = device->getSceneManager()->getActiveCamera();
    core::vector3df cameraPos = camera->getAbsolutePosition();

    f32 change_x = ( cursorPos.X - 0.5 ) * 100.0f;
    f32 change_y = ( cursorPos.Y - 0.5 ) * 100.0f;
    direction += change_x;
    zdirection -= change_y;
    if( zdirection < -90 )
        zdirection = -90;
    else
        if( zdirection > 5 ) //Controle l'orientation verticale max
            zdirection = 5;


    if(receiver.is_mouse_camera_tool_activated){
        device->getCursorControl()->setPosition( 0.5f, 0.5f );

        core::vector3df playerPos = perso->getPosition();

        f32 xf = playerPos.X - cos( direction * M_PI / 180.0f ) * 64.0f;
        f32 yf = playerPos.Y - sin( zdirection * M_PI / 180.0f ) * 134.0f;
        f32 zf = playerPos.Z + sin( direction * M_PI / 180.0f ) * 64.0f;

        camera->setPosition( core::vector3df( xf, yf+10.0f, zf ) );
        camera->setTarget( core::vector3df( playerPos.X, playerPos.Y + 70.0f,
                                            playerPos.Z ) );
        perso->setRotation( core::vector3df( 0, direction, 0 ) );

    }
}
static void create_window_pnj_follow()
{

}

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

static void create_exit(is::ISceneManager *smgr, iv::ITexture* texture_fin)
{

    is::IBillboardSceneNode* bill;
    bill = smgr->addBillboardSceneNode(nullptr, core::dimension2d<f32>(400, 400), core::vector3df(11.7243, 1051.75, -565.804));
    bill->setMaterialFlag(video::EMF_LIGHTING, false);
    bill->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    bill->setMaterialTexture(0, texture_fin);
}

static void create_window(ig::IGUIEnvironment *gui)
{
    // La fenêtre
    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(420,25,
                                                          WIDTH_WINDOW+20,
                                                          HEIGHT_WINDOW-20),
                                            false, L"Settings");

    // Une zone d'édition de texte, précédée d'un label
    gui->addStaticText(L"Value", ic::rect<s32>(22,48, 65,66), false, false,
                       window);
    gui->addEditBox(L"1.0", ic::rect<s32>(65,46, 160,66), true, window,
                    WINDOW_VALUE);

    // Un bouton à clicker
    gui->addButton(ic::rect<s32>(40,74, 140,92), window, WINDOW_BUTTON,
                   L"Click me!");

    // Une case à cocher
    gui->addCheckBox(true, ic::rect<s32>(40,100, 140,118), window,
                     WINDOW_CHECK_BOX, L"Select me!");

    // Une boite combo (une liste déroulante)
    gui->addStaticText(L"Choose one: ", ic::rect<s32>(22,126, 100,142),
                       false, false, window);
    ig::IGUIComboBox *cbox = gui->addComboBox(ic::rect<s32>(100,126, 180,142),
                                              window, WINDOW_COMBO_BOX);
    cbox->addItem(L"Choice 1", WINDOW_COMBO_CHOICE_1);
    cbox->addItem(L"Choice 2", WINDOW_COMBO_CHOICE_2);
    cbox->addItem(L"Choice 3", WINDOW_COMBO_CHOICE_3);

    // Une liste déroulée
    gui->addStaticText(L"List:", ic::rect<s32>(22,150, 65,168), false, false,
                       window);
    ig::IGUIListBox *lbox = gui->addListBox(ic::rect<s32>(40,170, 160,242),
                                            window, WINDOW_LIST_BOX, true);
    lbox->addItem(L"First Entry");
    lbox->addItem(L"Second Entry");
    lbox->addItem(L"Third Entry");

    // Une barre de défilement
    gui->addScrollBar(true, ic::rect<s32>(22,250, 160,268), window,
                      WINDOW_SCROLLBAR);

    // Une spin box
    gui->addSpinBox(L"18.0", ic::rect<s32>(40,280, 160,298), true, window,
                    WINDOW_SPIN_BOX);
}

static void create_GUI_munition(ig::IGUIEnvironment *gui, ig::IGUIImage *munition_10, ig::IGUIImage *munition_1,
                                ig::IGUIImage *stock_10, ig::IGUIImage *stock_1, ig::IGUIImage *slash){
    munition_10  = gui->addImage(ic::rect<s32>(WIDTH_WINDOW-210,HEIGHT_WINDOW-60, WIDTH_WINDOW-210+40,HEIGHT_WINDOW+40-60)); munition_10->setScaleImage(true);
    munition_1   = gui->addImage(ic::rect<s32>(WIDTH_WINDOW-210+40,HEIGHT_WINDOW-60, WIDTH_WINDOW-210+80,HEIGHT_WINDOW+40-60)); munition_1->setScaleImage(true);

    stock_10  = gui->addImage(ic::rect<s32>(WIDTH_WINDOW-100,HEIGHT_WINDOW-60, WIDTH_WINDOW-100+40,HEIGHT_WINDOW+40-60)); stock_10->setScaleImage(true);
    stock_1   = gui->addImage(ic::rect<s32>(WIDTH_WINDOW-100+40,HEIGHT_WINDOW-60, WIDTH_WINDOW-100+80,HEIGHT_WINDOW+40-60)); stock_1->setScaleImage(true);

    slash   = gui->addImage(ic::rect<s32>(WIDTH_WINDOW-170+40,HEIGHT_WINDOW-60, WIDTH_WINDOW-170+70,HEIGHT_WINDOW+40-60)); slash->setScaleImage(true);
}

void is_attacking(Character& character,std::vector<iv::ITexture*>& textures,
                  EventReceiver& receiver, int& compteur_attack)
{
    bool attacking = receiver.get_attack();
    if(attacking)
    {
        character.change_texture_weapon_fire(textures);
        character.mf->setVisible(true);
        compteur_attack++;
        if(compteur_attack > 12  || character.get_nb_munition() == 0  || character.is_reloading())
        {
            compteur_attack = 0;
            receiver.set_attack(false);
            character.change_texture_weapon_rest(textures);
            character.mf->setVisible(false);
        }
    }
}


bool is_character_meets_pnj(Character& character,pnj& pnj)
{
    float epsilon = 60.0f;
    if(character.body->getAbsolutePosition().getDistanceFrom(pnj.body->getAbsolutePosition()) < epsilon)
    {
        return true;
    }
    return false;
}



int main()
{
    EventReceiver receiver;
    std::vector<iv::ITexture*> textures;
    iv::ITexture* texture_fin;
    // Création de la fenêtre et du système de rendu.
    IrrlichtDevice *device = createDevice(iv::EDT_OPENGL,
                                          ic::dimension2d < u32 >(WIDTH_WINDOW ,
                                                                  HEIGHT_WINDOW)
                                          ,16 , false , false ,
                                          false , &receiver);

    iv::IVideoDriver  *driver = device->getVideoDriver();
    is::ISceneManager *smgr = device->getSceneManager();
    ig::IGUIEnvironment *gui  = device->getGUIEnvironment();
    // Chargement des textures pour les chiffres
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
    iv::ITexture *slash_tex = driver->getTexture("../data/slash.png");
    iv::ITexture *bloody_screen_tex = driver->getTexture("../data/bloody_screen.png");
    iv::ITexture *bloodier_screen_tex = driver->getTexture("../data/bloodier_screen.png");
    iv::ITexture *gameover_screen_tex = driver->getTexture("../data/gameover_screen.png");
    iv::ITexture *objectif1_tex = driver->getTexture("../data/objectif1.png");
    iv::ITexture *objectif2_tex = driver->getTexture("../data/objectif2.png");


    // Création des places pour les chiffres

    ig::IGUIImage *munition_10  = gui->addImage(ic::rect<s32>(WIDTH_WINDOW-210,HEIGHT_WINDOW-60, WIDTH_WINDOW-210+40,HEIGHT_WINDOW+40-60)); munition_10->setScaleImage(true);
    ig::IGUIImage *munition_1   = gui->addImage(ic::rect<s32>(WIDTH_WINDOW-210+40,HEIGHT_WINDOW-60, WIDTH_WINDOW-210+80,HEIGHT_WINDOW+40-60)); munition_1->setScaleImage(true);

    ig::IGUIImage *stock_10  = gui->addImage(ic::rect<s32>(WIDTH_WINDOW-100,HEIGHT_WINDOW-60, WIDTH_WINDOW-100+40,HEIGHT_WINDOW+40-60)); stock_10->setScaleImage(true);
    ig::IGUIImage *stock_1   = gui->addImage(ic::rect<s32>(WIDTH_WINDOW-100+40,HEIGHT_WINDOW-60, WIDTH_WINDOW-100+80,HEIGHT_WINDOW+40-60)); stock_1->setScaleImage(true);

    ig::IGUIImage *slash   = gui->addImage(ic::rect<s32>(WIDTH_WINDOW-170+40,HEIGHT_WINDOW-60, WIDTH_WINDOW-170+70,HEIGHT_WINDOW+40-60)); slash->setScaleImage(true);



    ig::IGUIImage *bloody_screen   = gui->addImage(ic::rect<s32>(0,0, WIDTH_WINDOW,HEIGHT_WINDOW)); bloody_screen->setScaleImage(true);
    ig::IGUIImage *objectif   = gui->addImage(ic::rect<s32>(0,0, WIDTH_WINDOW,HEIGHT_WINDOW)); bloody_screen->setScaleImage(true);

    //create_GUI_munition(gui,munition_10,munition_1,stock_10,stock_1,slash);

    // Ajout de l ’ archive qui contient entre autres un niveau complet
    device->getFileSystem()->addFileArchive("../data/cf.pk3");
    // On charge un bsp ( un niveau ) en particulier :
    is::IAnimatedMesh *mesh_map = smgr->getMesh ("cf.bsp");
    is::IMeshSceneNode *node_map ;
    node_map = smgr->addOctreeSceneNode(mesh_map->getMesh (0), nullptr , -1 , 1024);
    // Translation pour que nos personnages soient dans le décor
    node_map->setPosition (core::vector3df( 200 , -100 , -500));
    //node_map->setRotation(core::vector3df( 0 , 180 , 0));
    node_map->setID(MAP_ID);

    // Création du triangle selector
    scene::ITriangleSelector *selector;
    selector = smgr->createOctreeTriangleSelector(node_map->getMesh(), node_map);
    node_map->setTriangleSelector(selector);
    node_map->setID(MAP_ID);

    textures.push_back(driver->getTexture("../data/Chaingunner/chaingunner_body.png"));
    textures.push_back(driver->getTexture("../data/Chaingunner/chaingunner_weapon.png"));
    textures.push_back(driver->getTexture("../data/Chaingunner/chaingunner_head1.png"));
    textures.push_back(driver->getTexture("../data/Chaingunner/chaingunner_fire_weapon.png"));
    textures.push_back(driver->getTexture("../data/Chaingunner/chaingunner_mf0.png"));

    textures.push_back(driver->getTexture("../data/Chaingunner/chaingunner_pain_body.png"));
    textures.push_back(driver->getTexture("../data/Chaingunner/chaingunner_head2.png"));
    textures.push_back(driver->getTexture("../data/Chaingunner/chaingunner_die_body.png"));

    textures.push_back(driver->getTexture("../data/Warrior/warrior.jpg"));

    texture_fin = driver->getTexture("../data/particlegreen.jpg");


    //create Main character
    Character main_character;

    main_character.addCharacterMeshToScene(smgr, textures);
    main_character.setAnimation(main_character.RUN);
    main_character.addCharacterCollider(smgr,selector);

    //create pnj
    pnj rohmer;
    rohmer.addPNJMeshToScene(smgr,textures);
    rohmer.addPNJCollider(smgr,selector);
    rohmer.setAnimation(rohmer.STAND);
    //rohmer.body->setPosition(core::vector3df(-1269.31,155.75,-2033.84));

    //create enemy
    Enemy e1(smgr,device->getRandomizer(), main_character.body);
    e1.addEnemyMeshToScene();
    e1.setTexture(driver->getTexture("../data/blue_texture.pcx"));
    //e1.create_collision_with_map(selector);
    ic::vector3df pos(100,0.0f,200);
    e1.setPosition(pos);
    e1.move_randomely_arround_waiting_position();
    e1.setID(ENEMY_1_ID);



    receiver.set_gui(gui);
    receiver.set_personnage(&main_character);
    receiver.set_pnj(&rohmer);
    receiver.set_textures(textures);


    is::ICameraSceneNode *camera = smgr->addCameraSceneNode(0,core::vector3df(0.0f,0.0f,0.0f) ,core::vector3df(0.0f,0.0f,0.0f), -1);
    direction = 0.0f; zdirection=0.0f;
    device->getCursorControl()->setVisible(false);
    receiver.camera_node = camera;

    receiver.init_Key();

    // Chargement des textures pour le reticule
    iv::ITexture *scope_tex;
    scope_tex= driver->getTexture("../data/scope.png");


    is::ISceneCollisionManager *collision_manager = smgr->getSceneCollisionManager();

    Particle list_part[NB_PARTICULE_MAX];
    for(int i=0;i<NB_PARTICULE_MAX;i++){
        list_part[i].initializeParticle(driver->getTexture("../data/particlered.bmp"), driver->getTexture("../data/fireball.bmp"));
    }
    int i_FIFO = 0;
    bool list_part_rempli = false;

    int compteur_attack = 0;
    bool attack_one_tic = false;
    bool last_attack = false;

    bool meeting = false;
    bool follow = false;
    bool start_anim_death = false;
    bool anim_death = false;
    int cpt_anim_death = 0;
    int compteur_follow = 0;

    while(device->run())
    {
        e1.handle_walking();
        //set image for the "viseur"

       ig::IGUIImage *scope = gui->addImage(ic::rect<s32>(driver->getScreenSize().Width/2 -15,driver->getScreenSize().Height/2-15,  driver->getScreenSize().Width/2+15,driver->getScreenSize().Height/2+15)); scope->setScaleImage(true);

        scope->setImage(scope_tex);
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

        driver->beginScene(true, true, iv::SColor(100,150,200,255));
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
                    std::cout<<selected_scene_node->getID()<<std::endl;

                    switch(selected_scene_node->getID()){
                    case ENEMY_1_ID :

                        if (list_part_rempli){ list_part[i_FIFO].remove();}
                        list_part[i_FIFO].addParticleToScene(smgr,main_character.body->getPosition(),intersection,selected_scene_node);
                        i_FIFO++;
                        if (i_FIFO==NB_PARTICULE_MAX){i_FIFO = 0; list_part_rempli = true;}
                        e1.being_hit(driver->getTexture("../data/red_texture.pcx"));
                        break;
                    case MAP_ID :

                        if (list_part_rempli){ list_part[i_FIFO].remove();}
                        list_part[i_FIFO].addParticleToScene(smgr,main_character.body->getPosition(),intersection,selected_scene_node);
                        i_FIFO++;
                        if (i_FIFO==NB_PARTICULE_MAX){i_FIFO = 0; list_part_rempli = true;}
                        break;
                    default:;
                    }

                    attack_one_tic =false;
                    main_character.use_munition();

                }

            }
        }

        for (int k = 0; k<NB_PARTICULE_MAX; k++){
            list_part[k].frame_time_life--;
            if(list_part[k].frame_time_life == 0)
                list_part[k].remove();
        }

        e1.make_blink(driver->getTexture("../data/blue_texture.pcx"));

        e1.attack(&main_character);
        main_character.invincibility_counting(textures);
        last_attack = receiver.button_pressed;



        // Set image2D
        munition_10->setImage(digits[(main_character.get_nb_munition() / 10) % 10]);
        munition_1->setImage(digits[(main_character.get_nb_munition() / 1) % 10]);

        stock_10->setImage(digits[(main_character.get_nb_stock() / 10) % 10]);
        stock_1->setImage(digits[(main_character.get_nb_stock() / 1) % 10]);

        slash->setImage(slash_tex);
        //objectif->setImage(objectif1_tex);

        switch(main_character.getHealth_point()){
        case 2 :
            bloody_screen->setImage(bloody_screen_tex);
            break;
        case 1 :
            bloody_screen->setImage(bloodier_screen_tex);
            break;
        case 0 :
            start_anim_death = true;
            if(cpt_anim_death<=60)
            {
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
                bloody_screen->setImage(gameover_screen_tex);
                scope->setVisible(false);
                objectif->setVisible(false);
            }


            break;
        default:;
        }

        // Gestion suivi PNJ
        compteur_follow++;
        if(compteur_follow > 10)
            meeting = is_character_meets_pnj(main_character,rohmer);
        //std::cout<<"meeting: "<<meeting<<std::endl;
        if(meeting == true && follow == false)
        {
            follow = true;
            create_window_pnj_follow();
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
            //std::cout<<"FIN"<<std::endl;
        }


        // Dessin de la scène :
        smgr->drawAll();
        gui->drawAll();

        driver->endScene();
    }
    device->drop();

    return 0;
}
