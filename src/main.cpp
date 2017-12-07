#include <irrlicht.h>
#include "events.hpp"
#include "gui_ids.h"
#include <iostream>


using namespace irr;
namespace iv = irr::video;
namespace is = irr::scene;
namespace ic = irr::core;
namespace ig = irr::gui;


float direction;
float zdirection;

void moveCameraControl(IrrlichtDevice *device, is::IAnimatedMeshSceneNode *perso)
{
<<<<<<< HEAD
    ic::vector2d<float> cursorPos = device->getCursorControl()->getRelativePosition();
    scene::ICameraSceneNode* camera = device->getSceneManager()->getActiveCamera();
    core::vector3df cameraPos = camera->getAbsolutePosition();

    float change_x = ( cursorPos.X - 0.5 ) * 256.0f;
    float change_y = ( cursorPos.Y - 0.5 ) * 256.0f;
    direction += change_x;
    zdirection -= change_y;
    if( zdirection <- 90 )
        zdirection = -90;
    else
        if( zdirection > 2 ) //Controle l'orientation verticale max
            zdirection = 2;
    device->getCursorControl()->setPosition( 0.5f, 0.5f );

    core::vector3df playerPos = perso->getPosition();

    float xf = playerPos.X - cos( direction * M_PI / 180.0f ) * 64.0f;
    float yf = playerPos.Y - sin( zdirection * M_PI / 180.0f ) * 64.0f;
    float zf = playerPos.Z + sin( direction * M_PI / 180.0f ) * 64.0f;

    camera->setPosition( core::vector3df( xf, yf, zf ) );
    camera->setTarget( core::vector3df( playerPos.X, playerPos.Y + 25.0f, playerPos.Z ) );
    perso->setRotation( core::vector3df( 0, direction, 0 ) );
=======
     ic::vector2d<float> cursorPos = device->getCursorControl()->getRelativePosition();
     scene::ICameraSceneNode* camera = device->getSceneManager()->getActiveCamera();
     core::vector3df cameraPos = camera->getAbsolutePosition();

     float change_x = ( cursorPos.X - 0.5 ) * 256.0f;
     float change_y = ( cursorPos.Y - 0.5 ) * 256.0f;
     direction += change_x;
     zdirection -= change_y;
     if( zdirection <- 90 )
         zdirection = -90;
     else
     if( zdirection > 2 ) //Controle l'orientation verticale max
         zdirection = 2;
     device->getCursorControl()->setPosition( 0.5f, 0.5f );

     core::vector3df playerPos = perso->getPosition();

     float xf = playerPos.X - cos( direction * M_PI / 180.0f ) * 64.0f;
     float yf = playerPos.Y - sin( zdirection * M_PI / 180.0f ) * 64.0f;
     float zf = playerPos.Z + sin( direction * M_PI / 180.0f ) * 64.0f;
     camera->setPosition( core::vector3df( xf, yf, zf ) );
     camera->setTarget( core::vector3df( playerPos.X, playerPos.Y + 25.0f, playerPos.Z ) );
     perso->setRotation( core::vector3df( 0, direction, 0 ) );
>>>>>>> 52ea765c97dd455215e86ec28f55dbfd39d66a41
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
    ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(420,25, 620,460),
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

int main()
{
    EventReceiver receiver;
    std::vector<iv::ITexture*> textures;
    // Création de la fenêtre et du système de rendu.
    IrrlichtDevice *device = createDevice(iv::EDT_OPENGL,
                                          ic::dimension2d < u32 >(640 , 480) ,
                                          16 , false , false , false , &receiver);

    iv::IVideoDriver  *driver = device->getVideoDriver();
    is::ISceneManager *smgr = device->getSceneManager();
    ig::IGUIEnvironment *gui = device->getGUIEnvironment();


    //smgr->addCameraSceneNode(nullptr , ic::vector3df (0 , 30 , -40) , ic::vector3df (0 , 5 , 0));

    is::IAnimatedMesh *mesh = smgr->getMesh("../data/tris.md2");
    is::IAnimatedMeshSceneNode *perso = smgr->addAnimatedMeshSceneNode(mesh);


    perso->setMaterialFlag(iv::EMF_LIGHTING, false);
    perso->setMD2Animation(is::EMAT_STAND);
    textures.push_back(driver->getTexture("../data/base.pcx"));
    textures.push_back(driver->getTexture("../data/red_texture.pcx"));
    textures.push_back(driver->getTexture("../data/blue_texture.pcx"));
    perso->setMaterialTexture(0, textures[0]);
    std::cout<<"HHHHERREEE********************************";
    receiver.set_gui(gui);
    receiver.set_node(perso);
    receiver.set_textures(textures);

    //perso->setDebugDataVisible(is::EDS_NORMALS | is::EDS_BBOX);


    is::IAnimatedMeshSceneNode *perso_ligne = smgr->addAnimatedMeshSceneNode(mesh);
    perso_ligne->setMaterialFlag(iv::EMF_LIGHTING, false);
    perso_ligne->setMD2Animation(is::EMAT_CROUCH_WALK  );
    perso_ligne->setMaterialTexture(0, textures[1]);
    is::ISceneNodeAnimator *anim =
            smgr->createFlyStraightAnimator(ic::vector3df(-80,0,20),
<<<<<<< HEAD
                                            ic::vector3df(0,0,20), 5000, true,true);
    perso_ligne->addAnimator(anim);

    //is::ICameraSceneNode *camera = smgr->addCameraSceneNode(perso , ic::vector3df (-20 , 30 , 0) , ic::vector3df (0 , 15 , 0));//smgr->addCameraSceneNodeFPS();

    is::ICameraSceneNode *camera = smgr->addCameraSceneNode
            (0,core::vector3df(0.0f,0.0f,0.0f) , core::vector3df(0.0f,0.0f,0.0f),
             -1);
    direction = 0.0f; zdirection=0.0f;
    device->getCursorControl()->setVisible(false);
    receiver.camera_node = camera;


    // Ajout de l ’ archive qui contient entre autres un niveau complet
    device->getFileSystem()->addFileArchive("../data/cf.pk3");
    // On charge un bsp ( un niveau ) en particulier :
    mesh = smgr->getMesh ("cf.bsp");
    is::IMeshSceneNode *node2 ;
    node2 = smgr->addOctreeSceneNode( mesh->getMesh (0), nullptr , -1 , 1024);
    // Translation pour que nos personnages soient dans le décor
    node2->setPosition (core::vector3df( -300 , -20 , -500));

    // Création du triangle selector
    scene::ITriangleSelector *selector;
    selector = smgr->createOctreeTriangleSelector(node2->getMesh(), node2);
    node2->setTriangleSelector(selector);

    // Et l'animateur/collisionneur
    scene::ISceneNodeAnimator *anim1;
    const core::aabbox3d<f32>& box = perso->getBoundingBox();
    core::vector3df radius = 1.2*(box.MaxEdge - box.getCenter());
    anim1 = smgr->createCollisionResponseAnimator(selector,
                                                  perso,  // Le noeud que l'on veut gérer
                                                  radius, // "rayons" de la caméra
                                                  ic::vector3df(0, -10, 0),  // gravité
                                                  ic::vector3df(0, 0, 0));  // décalage du centre

    perso->addAnimator(anim1);

    // Création de notre Gui
    // Choix de la police de caractères
    ig::IGUISkin* skin = gui->getSkin();
    ig::IGUIFont* font = gui->getFont("../data/fontlucida.png");
    skin->setFont(font);

    // La barre de menu
    create_menu(gui);

    // Une fenêtre pour différents réglages
    //create_window(gui);


    // Ajout d'un arbre billboard
    is::IBillboardSceneNode *billboard;
    billboard = smgr->addBillboardSceneNode(nullptr,
                                            ic::dimension2d<f32>(50, 80),
                                            ic::vector3df(0, 0, 50));
    billboard->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    billboard->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
    billboard->setMaterialTexture(0, driver->getTexture("../data/tree.png"));


    int score = 0;

    while(device->run())
    {
        // Work out a frame delta time.

        receiver.keyboard_handler();

        driver->beginScene(true, true, iv::SColor(100,150,200,255));
        //camera->setTarget(perso->getPosition() + ic::vector3df (0 , 20 + 4*receiver.rotation_cam , 0));
        moveCameraControl(device,perso);

        // Dessin de la scène :
        smgr->drawAll();
        //
        gui->drawAll();

        driver->endScene();
    }
    device->drop();

    return 0;
=======
            ic::vector3df(0,0,20), 5000, true,true);
  perso_ligne->addAnimator(anim);

  //is::ICameraSceneNode *camera = smgr->addCameraSceneNode(perso , ic::vector3df (-20 , 30 , 0) , ic::vector3df (0 , 15 , 0));//smgr->addCameraSceneNodeFPS();

  is::ICameraSceneNode *camera = smgr->addCameraSceneNode(0, core::vector3df(0.0f,0.0f,0.0f) , core::vector3df(0.0f,0.0f,0.0f), -1);
  direction = 0.0f; zdirection=0.0f;
  device->getCursorControl()->setVisible(false);
  receiver.camera_node = camera;


  // Ajout de l ’ archive qui contient entre autres un niveau complet
  device->getFileSystem()->addFileArchive("../data/cf.pk3");
  // On charge un bsp ( un niveau ) en particulier :
  mesh = smgr->getMesh ("cf.bsp");
  is::IMeshSceneNode *node2 ;
  node2 = smgr->addOctreeSceneNode( mesh->getMesh (0), nullptr , -1 , 1024);
  // Translation pour que nos personnages soient dans le décor
  node2->setPosition (core::vector3df( -300 , -20 , -500));

  // Création du triangle selector
  scene::ITriangleSelector *selector;
  selector = smgr->createOctreeTriangleSelector(node2->getMesh(), node2);
  node2->setTriangleSelector(selector);

  // Et l'animateur/collisionneur
  scene::ISceneNodeAnimator *anim1;
  const core::aabbox3d<f32>& box = perso->getBoundingBox();
          core::vector3df radius = 1.2*(box.MaxEdge - box.getCenter());
  anim1 = smgr->createCollisionResponseAnimator(selector,
                                               perso,  // Le noeud que l'on veut gérer
                                               radius, // "rayons" de la caméra
                                               ic::vector3df(0, -10, 0),  // gravité
                                               ic::vector3df(0, 0, 0));  // décalage du centre

  perso->addAnimator(anim1);

  // Création de notre Gui
  // Choix de la police de caractères
  ig::IGUISkin* skin = gui->getSkin();
  ig::IGUIFont* font = gui->getFont("../data/fontlucida.png");
  skin->setFont(font);

  // La barre de menu
  create_menu(gui);

  // Une fenêtre pour différents réglages
  //create_window(gui);


  // Ajout d'un arbre billboard
  is::IBillboardSceneNode *billboard;
  billboard = smgr->addBillboardSceneNode(nullptr,
                                              ic::dimension2d<f32>(50, 80),
                                              ic::vector3df(0, 0, 50));
  billboard->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  billboard->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
  billboard->setMaterialTexture(0, driver->getTexture("../data/tree.png"));

  receiver.init_Key();
  int score = 0;

  while(device->run())
   {
     // Work out a frame delta time.

    receiver.keyboard_handler();

    driver->beginScene(true, true, iv::SColor(100,150,200,255));
    //camera->setTarget(perso->getPosition() + ic::vector3df (0 , 20 + 4*receiver.rotation_cam , 0));
    moveCameraControl(device,perso);

    // Dessin de la scène :
    smgr->drawAll();
    //
    gui->drawAll();

    driver->endScene();
  }
  device->drop();

  return 0;
>>>>>>> 52ea765c97dd455215e86ec28f55dbfd39d66a41
}
