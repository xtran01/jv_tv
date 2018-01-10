#include <irrlicht.h>
#include "events.hpp"
#include "gui_ids.h"
#include <iostream>
#include "enemy.h"
#include "character.h"
#include "particle.h"

using namespace irr;
namespace iv = irr::video;
namespace is = irr::scene;
namespace ic = irr::core;
namespace ig = irr::gui;


f32 direction;
f32 zdirection;
const int MAP_ID = 1;
const int ENEMY_ID = 42;
const int HEIGHT_WINDOW = 480;
const int WIDTH_WINDOW = 640;
const int NB_PARTICULE_MAX = 20;

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

/*===========================================================================*\
 * create_menu                                                               *
\*===========================================================================*/
static void create_menu(ig::IGUIEnvironment *gui)
{
    ig::IGUIContextMenu *submenu;

    // Les trois entrées principales :
    ig::IGUIContextMenu *menu = gui->addMenu();
    menu->addItem(L"File", -1, true, true);
    menu->addItem(L"Debug", -1, true, true);
    menu->addItem(L"Help", -1, true, true);

    // Le contenu du menu File :
    submenu = menu->getSubMenu(0);
    submenu->addItem(L"New game...", MENU_NEW_GAME);
    submenu->addSeparator();
    submenu->addItem(L"Quit", MENU_QUIT);

    // Le contenu du menu Debug :
    submenu = menu->getSubMenu(1);
    submenu->addItem(L"Bounding Box",   MENU_BOUNDING_BOX);
    submenu->addItem(L"Show Normals",   MENU_NORMALS);
    submenu->addItem(L"Show Triangles", MENU_TRIANGLES);
    submenu->addItem(L"Transparency",   MENU_TRANSPARENCY);

    // Le contenu du menu Help :
    submenu = menu->getSubMenu(2);
    submenu->addItem(L"About...", MENU_ABOUT);
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

void is_attacking(Character& character,std::vector<iv::ITexture*>& textures, EventReceiver& receiver, int& compteur_attack)
{
    bool attacking = receiver.get_attack();
    if(attacking)
    {
        character.change_texture_weapon_fire(textures);
        character.mf->setVisible(true);
        compteur_attack++;
        if(compteur_attack > 12)
        {
            compteur_attack = 0;
            receiver.set_attack(false);
            character.change_texture_weapon_rest(textures);
            character.mf->setVisible(false);
        }
    }

}

void generate_particle(int &mouse_x, int &mouse_y, EventReceiver& receiver, int &i_FIFO, bool &rempli, std::vector<iv::ITexture*> textures,
                       is::ISceneCollisionManager *collision_manager,is::ISceneManager *smgr,Particle part,Character main_character,Particle list_part[NB_PARTICULE_MAX]){
    bool attacking = receiver.get_attack();
    if(attacking)
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
                ENEMY_ID); // On ne veut que des noeuds avec cet identifiant

    if (selected_scene_node){
        selected_scene_node->setMaterialTexture(0, textures[1]);
        std::cout<<"Touché"<<std::endl;
        part.addParticleToScene(smgr,main_character.body->getPosition(),intersection);}

    selected_scene_node =
            collision_manager->getSceneNodeAndCollisionPointFromRay(
                ray,
                intersection, // On récupère ici les coordonnées 3D de l'intersection
                hit_triangle, // et le triangle intersecté
                MAP_ID); // On ne veut que des noeuds avec cet identifiant


    if (selected_scene_node){
        if (rempli){ list_part[i_FIFO].remove();}

        list_part[i_FIFO].addParticleToScene(smgr,main_character.body->getPosition(),intersection);
        i_FIFO++;

        if (i_FIFO==NB_PARTICULE_MAX){i_FIFO = 0; rempli = true;}
    }
    }
}

int main()
{



    EventReceiver receiver;
    std::vector<iv::ITexture*> textures;
    // Création de la fenêtre et du système de rendu.
    IrrlichtDevice *device = createDevice(iv::EDT_OPENGL,
                                          ic::dimension2d < u32 >(WIDTH_WINDOW ,
                                                                  HEIGHT_WINDOW)
                                          ,16 , false , false ,
                                          false , &receiver);

    iv::IVideoDriver  *driver = device->getVideoDriver();
    is::ISceneManager *smgr = device->getSceneManager();
    ig::IGUIEnvironment *gui = device->getGUIEnvironment();




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






    //create Main character
    Character main_character(smgr);


    main_character.addCharacterMeshToScene(smgr, textures);
    main_character.setAnimation(main_character.RUN);
    main_character.addCharacterCollider(smgr,selector);

    //create enemy
    Enemy e1(smgr,device->getRandomizer(), main_character.body);
    e1.addEnemyMeshToScene();
    e1.setTexture(driver->getTexture("../data/blue_texture.pcx"));
    e1.create_collision_with_map(selector);
    ic::vector3df pos(200,0.0f,200);
    e1.setPosition(pos);
    e1.move_randomely_arround_waiting_position();
    e1.setID(ENEMY_ID);
    e1.follow_main_character();

    receiver.set_gui(gui);
    receiver.set_personnage(&main_character);
    receiver.set_textures(textures);


    is::ICameraSceneNode *camera = smgr->
            addCameraSceneNode(0,core::vector3df(0.0f,0.0f,0.0f) ,
                               core::vector3df(0.0f,0.0f,0.0f), -1);
    direction = 0.0f; zdirection=0.0f;
    device->getCursorControl()->setVisible(false);
    receiver.camera_node = camera;

    receiver.init_Key();

    // Chargement des textures pour le reticule
    iv::ITexture *scope_tex;
    scope_tex= driver->getTexture("../data/scope.png");



    /****************
     * Gestion des particules
     ***************/
    is::ISceneCollisionManager *collision_manager = smgr->getSceneCollisionManager();

    Particle part(driver->getTexture("../data/particlered.bmp"), driver->getTexture("../data/fireball.bmp"));
    Particle list_part[NB_PARTICULE_MAX];
    for(int i=0;i<NB_PARTICULE_MAX;i++){
        list_part[i].initializeParticle(driver->getTexture("../data/particlered.bmp"), driver->getTexture("../data/fireball.bmp"));
    }
    int i_FIFO = 0;
    bool rempli = false;


    int compteur_attack = 0;

    while(device->run())
    {
        //set image for the "viseur"

        ig::IGUIImage *scope = gui->addImage(ic::rect<s32>(driver->getScreenSize().Width/2 -15,driver->getScreenSize().Height/2-15,  driver->getScreenSize().Width/2+15,driver->getScreenSize().Height/2+15)); scope->setScaleImage(true);
        scope->setImage(scope_tex);

        is_attacking(main_character, textures, receiver, compteur_attack);

        //receiver.keyboard_handler();
        //driver->beginScene(true, true, iv::SColor(100,150,200,255));
        moveCameraControl(device,main_character.body, receiver);

        receiver.keyboard_handler();
        driver->beginScene(true, true, iv::SColor(100,150,200,255));

        int mouse_x, mouse_y;
        if (receiver.is_mouse_pressed(mouse_x, mouse_y))
        {
            generate_particle(mouse_x, mouse_y,receiver,i_FIFO,rempli,textures,collision_manager,smgr,part,main_character,list_part);
        }


        // Dessin de la scène :
        smgr->drawAll();
        gui->drawAll();

        driver->endScene();
    }
    device->drop();

    return 0;
}
