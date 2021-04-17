#include "Main.h"

// ----------------------------------------------- //
// ------------ INITIALISATION DU JEU ------------ //
// ----------------------------------------------- //

void Main::init(int largeur_grille, int hauteur_grille, int tailleZoneJeuX, int tailleZoneJeuY)
{
    win = new WindowSurface("Tetris666",tailleZoneJeuX,tailleZoneJeuY);
    win->ajouter_sprite("fond",Sprite({0,0,10,10}));
    win->ajouter_sprite("deco",Sprite({0,0,1056,287}));
    win->ajouter_sprite("pattern",Sprite({0,288,320,423}));
    win->ajouter_sprite("boxi",Sprite({299,0,40,40}));
    this->hauteur_grille = hauteur_grille;
    this->largeur_grille = largeur_grille;
    int taille_boxi = 1000/hauteur_grille;
    int largeurZoneJeu = taille_boxi*largeur_grille;

    //Musique du menu
    this->musique = Mix_LoadMUS("retro-bowl.mp3");
    Mix_PlayMusic(this->musique, -1);
    Mix_AllocateChannels(2);
    this->selection_sound = Mix_LoadWAV("selection.ogg");

    // Taille de la warzone
    tailleWarZoneX = tailleZoneJeuX;
    tailleWarZoneY = tailleZoneJeuY;

    // Marge de gauche
    left_marge1 = (1850 - largeurZoneJeu)/2;
    left_marge2 = 0;

    // Accès au menu
    this->drawMenu();
    
    int save = Mix_VolumeMusic(-1);
    for(int i = save; i > 1; i/=2)
    {
        Mix_VolumeMusic(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    Mix_VolumeMusic(save);
    ///Musique du jeu
    switch (mode)
    {
    case 1:
        this->musique = Mix_LoadMUS("tetris-theme-a-acapella_boucle.mp3");
        break;
    case 2:
        this->musique = Mix_LoadMUS("minecraft-theme-trap-remix-holder.mp3");
        break;    
    case 3:
        this->musique = Mix_LoadMUS("code_lyoko_ifscl.mp3");
        break;
    case 4:
        this->musique = Mix_LoadMUS("mii-channel-music-vgr-remix.mp3");
        break;
    }
    Mix_FreeChunk(this->selection_sound);
    Mix_PlayMusic(this->musique, -1);

    Game g1,g2;
    this->game1 = g1;
    game1.init(largeur_grille, hauteur_grille,1);
    if(mode > 1)
    {
      this->game2 = g2;
      game2.init(largeur_grille, hauteur_grille,2);
    }

    // std::cout << "bjr\n";
}


// ----------------------------------------------- //
// -------------- BOUCLE PRINCIPALE -------------- //
// ----------------------------------------------- //

void Main::loop()
{
  bool quit = false;
  bool cestPresqueLaFin = false;
  int w, h, cheh1 = 0, cheh2 = 0;
  this->win->get_dimension(&h,&w);

  // Gestion du temps
  unsigned int lastTime1 = 0, delai_chute1 = 1000, currentTime;
  unsigned int lastTime2 = 0, delai_chute2 = 1000;
  unsigned int lastTime3 = 0, delai_chute3 = 333;
  if(mode == 4) delai_chute3 = 0;

  SDL_Event event;

  // -------- BOUCLE --------- //

  while(!quit)
  {
    currentTime = SDL_GetTicks();


    while (!quit && SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT:
          // On s'en va
          SDL_Quit();
          exit(0);
          break;
        case SDL_MOUSEBUTTONDOWN:
          printf("mouse click %d\n", event.button.button);
          break;
        case SDL_KEYUP:
          switch (event.key.keysym.sym)
          {
          case SDLK_RETURN:
            game1.debuter_partie();
            if(mode > 1) { game2.debuter_partie(); }
            break;
          case SDLK_LEFT:
            game1.gauche();
            break;
          case SDLK_RIGHT:
            game1.droite();
            break;
          case SDLK_DOWN:
            delai_chute1 = 1000;
            break;
          case SDLK_UP:
            game1.rotation();
            break;
          case SDLK_RSHIFT:
            game1.sauvegarde();
            break;
          case SDLK_a:
            if(mode == 2) { game2.sauvegarde(); }
           break;
          case SDLK_z:
            if(mode == 2) { game2.rotation(); }
           break;
          case SDLK_q:
            if(mode == 2) { game2.gauche(); }
           break;
          case SDLK_s:
            if(mode == 2) { delai_chute2 = 1000; }
           break;
          case SDLK_d:
            if(mode == 2) { game2.droite(); }
            break;
          default:
            break;
          }

        break;
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym)
          {
          case SDLK_DOWN:
            delai_chute1 = 50;
            break;
          case SDLK_s:
            if(mode == 2) { delai_chute2 = 50; }
            break;
          default:
            break;
          }
          break;
        default: break;
      }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);
    quit |= (state[SDL_SCANCODE_ESCAPE]!=0);


    // IA idiote

    if(mode >= 3 && currentTime > lastTime3 + delai_chute3)
    {
      struct timeval timer;
      gettimeofday(&timer, NULL);
      srand(timer.tv_usec);
      int choix = (rand() % 9)+1; //entre 1 et 9 inclus

      delai_chute2 = (rand() % 1000) + 100;


      if(choix == 5)
      {
        game2.rotation();
      } else {
        if(choix % 2 == 0)
        {
          game2.gauche();
        } else {
          game2.droite();
        }

      }
      lastTime3 = currentTime;
    }

    // On vérifie si une nouvelle pièce doit etre générée
    game1.check_nouvelle_piece();
    if(mode > 1) { game2.check_nouvelle_piece(); }

    if (currentTime > lastTime1 + delai_chute1) {
        cheh1 = game1.actualiser_chute();
        quit = game1.EstCeFini();
        lastTime1 = currentTime;
    }

    if (mode > 1 && currentTime > lastTime2 + delai_chute2) {
        cheh2 = game2.actualiser_chute();
        quit = game2.EstCeFini();
        lastTime2 = currentTime;
    }

    if(mode > 1 && cheh2 > 0)
    {
      game1.ajouter_ligne(cheh2);
      cheh2 = 0;
    }
    if(mode > 1 && cheh1 > 0)
    {
      game2.ajouter_ligne(cheh1);
      cheh1 = 0;
    }

    //génère l'affichage
    // std::cout << "bjr\n";
    this->draw(w,h);

    // affiche la surface
    SDL_RenderPresent(win->renderer);


  }

  std::cout << "But in the end it doesn't even matter... *linkin park playing in the background*\n" ;

  // ------ ECRAN DE FIN ----- //

  while(!cestPresqueLaFin) {

    SDL_Event event;
    while (!cestPresqueLaFin && SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT:
          cestPresqueLaFin = true;
          break;

        case SDL_KEYDOWN:
          switch(event.key.keysym.sym)
          {
            case SDLK_ESCAPE:
              cestPresqueLaFin = true;
              // std::cout << "Here we are, Samwise Gamgee, here at the end of all things\n";
              break;
            default: break;
          }
        default: break;
      }
    }

    // ------- FIN DU JEU ------- //

    this->drawEndScreen();
    // affiche la surface
    SDL_RenderPresent(win->renderer);
    

  }

  
  SDL_Quit();
}

// ----------------------------------------------- //
// ------------ FONCTION DRAW DU JEU ------------- //
// ----------------------------------------------- //

void Main::draw(int largeur, int hauteur)
{

  int i, j, taille_boxi;
  taille_boxi = hauteur/hauteur_grille;
  int largeurZoneJeu = taille_boxi*this->largeur_grille;
  // Marge de gauche
  int depart = (largeur - largeurZoneJeu)/2;

  //on efface la fenêtre
  SDL_SetRenderDrawColor(win->renderer,0,0,0,255);
  SDL_RenderClear(win->renderer);

  // ---------- AFFICHAGE SPRITES ---------- //

  // Fond sombre
  SDL_Rect *srcBackground = win->sprites.at("fond").get();
  for(i = 0; i < tailleWarZoneX; i+=10)
  {
    for(j = 0; j < tailleWarZoneY ; j+=10 ) {
      SDL_Rect dest = {i,j,srcBackground->w,srcBackground->h};
      SDL_RenderCopy(win->renderer,win->pTexture,srcBackground,&dest);
    }
  }
  // Déco blocs
  SDL_Rect *srcTetris = win->sprites.at("deco").get();
  for(i = 0; i < 1400; i+=1056)
  {
    int j = 1000-287;
    SDL_Rect dest = {i,j,srcTetris->w,srcTetris->h};
    SDL_RenderCopy(win->renderer,win->pTexture,srcTetris,&dest);
  }

  // SPRITE 1 JOUEUR
  if(mode == 1) {
    // récupération sprite fond
    SDL_Rect *srcFond = win->sprites.at("pattern").get();
    for(i = depart; i < depart+largeurZoneJeu; i+=srcFond->w)
    {
      for(j = 0; j < hauteur; j+=srcFond->h)
      {
        SDL_Rect dest = {i,j,srcFond->w,srcFond->h};
        SDL_RenderCopy(win->renderer,win->pTexture,srcFond,&dest);
      }
    }
    // Bordure fenêtre de jeu
    SDL_SetRenderDrawColor(win->renderer,30,30,30,255);
    SDL_Rect bordureSombre = { depart-50, 0, 50, hauteur};
    SDL_RenderFillRect(win->renderer,&bordureSombre);
    bordureSombre = { depart+largeurZoneJeu, 0, 50, hauteur};
    SDL_RenderFillRect(win->renderer,&bordureSombre);
  }

  if(mode > 1)
  {
    left_marge1 = 970;
    left_marge2 = 40;

    // zone de jeu 1
    SDL_Rect *srcFond = win->sprites.at("pattern").get();
    for(i = left_marge1; i < left_marge1+largeurZoneJeu; i+=srcFond->w)
    {
      for(j = 0; j < hauteur; j+=srcFond->h)
      {
        SDL_Rect dest = {i,j,srcFond->w,srcFond->h};
        SDL_RenderCopy(win->renderer,win->pTexture,srcFond,&dest);
      }
    }
    // Bordure fenêtre de jeu 1
    SDL_SetRenderDrawColor(win->renderer,30,30,30,255);
    SDL_Rect bordureSombre = { left_marge1-40, 0, 40, hauteur};
    SDL_RenderFillRect(win->renderer,&bordureSombre);
    bordureSombre = { left_marge1+largeurZoneJeu, 0, 40, hauteur};
    SDL_RenderFillRect(win->renderer,&bordureSombre);

    // zone de jeu 2
    for(i = left_marge2; i < left_marge2+largeurZoneJeu; i+=srcFond->w)
    {
      for(j = 0; j < hauteur; j+=srcFond->h)
      {
        SDL_Rect dest = {i,j,srcFond->w,srcFond->h};
        SDL_RenderCopy(win->renderer,win->pTexture,srcFond,&dest);
      }
    }
    // Bordure fenêtre de jeu 2
    SDL_SetRenderDrawColor(win->renderer,30,30,30,255);
    bordureSombre = { left_marge2-40, 0, 40, hauteur};
    SDL_RenderFillRect(win->renderer,&bordureSombre);
    bordureSombre = { left_marge2+largeurZoneJeu, 0, 40, hauteur};
    SDL_RenderFillRect(win->renderer,&bordureSombre);

  }


  // Placer les boxies placés
  std::vector<Boxi> grille1 = game1.get_grille();
  for (size_t i = 0; i < grille1.size(); i++) {
    Boxi boxi = grille1[i];
    SDL_Color color = boxi.get_color();
    draw_boxi(boxi.get_x(), boxi.get_y(), taille_boxi, color, left_marge1);
  }

  // Placer la pièce qui tombe
  if(this->game1.get_yatilUnePieceEnTrainDeTomber()) {
    Piece piece_courante1 = game1.get_piece_courante();
    std::vector<Boxi> *piece = piece_courante1.get_boxies();
    SDL_Color color = piece_courante1.get_color();
    for (size_t i = 0; i < piece->size(); i++) {
      Boxi boxi = piece->at(i);
      draw_boxi(piece->at(i).get_x(), piece->at(i).get_y(), taille_boxi,color,left_marge1);
    }
  }

  if(mode > 1)
  {
      // Placer les boxies placés
      std::vector<Boxi> grille2 = game2.get_grille();
      for (size_t i = 0; i < grille2.size(); i++) {
        Boxi boxi = grille2[i];
        SDL_Color color = boxi.get_color();
        draw_boxi(boxi.get_x(), boxi.get_y(), taille_boxi, color, left_marge2);
      }

      // Placer la pièce qui tombe
      if(this->game2.get_yatilUnePieceEnTrainDeTomber()) {
        Piece piece_courante2 = game2.get_piece_courante();
        std::vector<Boxi> *piece = piece_courante2.get_boxies();
        SDL_Color color = piece_courante2.get_color();
        for (size_t i = 0; i < piece->size(); i++) {
          Boxi boxi = piece->at(i);
          draw_boxi(piece->at(i).get_x(), piece->at(i).get_y(), taille_boxi,color,left_marge2);
        }
      }
  }

  // -------------- COLONNE DE DROITE -------------- //

  if(mode > 1)
  {
    // std::cout << "bjr\n";
    afficher_colonne(left_marge2+largeurZoneJeu+70, game2);
    afficher_colonne(left_marge1+largeurZoneJeu+70, game1);
  }
  else
  {
    afficher_colonne(depart+largeurZoneJeu+100, game1);
  }

}

// ----------------------------------------------- //
// ---------- AFFICHAGE BARRE LATERALE ----------- //
// ----------------------------------------------- //

void Main::afficher_colonne(int left_marge, Game game)
{
  SDL_Color color;


  if(game.getPlayer() == 2) {
    color = { 169, 59, 58 };
  }
  else {
    color = { 142, 71, 141 };
  }

  // --- Affichage titre ---- //
  SDL_Color colorTitre = { 80, 80, 80 };
  SDL_Surface *surface = TTF_RenderText_Solid(win->font,"TETRIS666", colorTitre);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(win->renderer, surface);
  SDL_Rect dstrect = { left_marge, 45, 190, 50 };
  SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);

  // ---- Affichage score ---- //
  // carré fond noir
  SDL_SetRenderDrawColor(win->renderer,24,24,24,255);
  SDL_Rect rightcol = { left_marge, 145, 190, 140};
  SDL_RenderFillRect(win->renderer,&rightcol);
  // titre
  surface = TTF_RenderText_Solid(win->font,"SCORE:", color);
  texture = SDL_CreateTextureFromSurface(win->renderer, surface);
  dstrect = { left_marge+15, 160, 60, 14 };
  SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
  // texte score
  SDL_Color colorPoints = { 90, 90, 90 };
  std::string s = std::to_string(game.get_score()) + " POINTS";
  surface = TTF_RenderText_Solid(win->font,s.c_str(), colorPoints);
  texture = SDL_CreateTextureFromSurface(win->renderer, surface);
  dstrect = { left_marge+40, 210, 100, 40 };
  SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);

  // ---- Affichage pièce suivante ---- //
  // carré fond noir
  SDL_SetRenderDrawColor(win->renderer,24,24,24,255);
  rightcol = { left_marge, 340, 190, 180};
  SDL_RenderFillRect(win->renderer,&rightcol);
  // titre
  surface = TTF_RenderText_Solid(win->font,"PIECE SUIVANTE:", color);
  texture = SDL_CreateTextureFromSurface(win->renderer, surface);
  dstrect = { left_marge+15, 355, 145, 20 };
  SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);

  // ---- Placer la prochaine pièce ---- //
  Piece piece_suivante = game.get_piece_suivante();
  std::vector<Boxi> *piece = piece_suivante.get_boxies();
  color = piece_suivante.get_color();
  for (size_t i = 0; i < piece->size(); i++) {
    Boxi boxi = piece->at(i);
    draw_boxi_right(-15,420,piece->at(i).get_x(), piece->at(i).get_y(), 15,color, left_marge);
  }

  // ---- Affichage pièce sauvegardée ---- //
  // carré fond noir
  SDL_SetRenderDrawColor(win->renderer,24,24,24,255);
  rightcol = { left_marge, 570, 190, 180};
  SDL_RenderFillRect(win->renderer,&rightcol);
  // titre
  if(game.getPlayer() == 2) {
    color = { 169, 59, 58 };
  }
  else {
    color = { 142, 71, 141 };
  }
  surface = TTF_RenderText_Solid(win->font,"PIECE SAUVEGARDEE:", color);
  texture = SDL_CreateTextureFromSurface(win->renderer, surface);
  dstrect = { left_marge+15, 585, 165, 20 };
  SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);

  // ---- Placer la piece sauvegardee ---- //
  if(game.get_yatilUnePieceSauvee())
  {
    int hauteur_piece,largeur_piece,min_x,min_y;
    Piece piece_sauvegarde = game.get_piece_sauvegarde();
    std::vector<Boxi> *piece = piece_sauvegarde.get_boxies();
    // std::cout << "bjr\n";
    piece_sauvegarde.get_piece_dim(&hauteur_piece,&largeur_piece,&min_x,&min_y);
    SDL_Color color = piece_sauvegarde.get_color();

    for (size_t i = 0; i < piece->size(); i++) {
      Boxi boxi = piece->at(i);
      draw_boxi_right(-15,635,piece->at(i).get_x()-min_x+6, piece->at(i).get_y()-min_y+1, 15, color, left_marge);
    }
  }
}

// ------------------------------------------------- //
// ----------------- MENU D'ACCUEIL ---------------- //
// ------------------------------------------------- //

void Main::drawMenu() {
  int quelEstTonChoix = 0;
  int nbChoix = 4;
  int theChoosenHasBeenChoosen = false;

  while(!theChoosenHasBeenChoosen) {

    SDL_Event event;
    while(!theChoosenHasBeenChoosen && SDL_PollEvent(&event)) {
      // Evenements
      switch (event.type)
      {
        case SDL_QUIT:
          // On s'en va
          SDL_Quit();
          exit(0);
          break;

        case SDL_KEYDOWN:
          switch(event.key.keysym.sym)
          {
            case SDLK_DOWN:
              {
                quelEstTonChoix = (quelEstTonChoix + 1)%nbChoix;
                // std::cout << "Mode suivant = " << quelEstTonChoix << "\n";
                break;
              }
            case SDLK_UP:
              {
                quelEstTonChoix = (quelEstTonChoix - 1);
                if(quelEstTonChoix < 0) {
                  quelEstTonChoix = 3;
                }
                // std::cout << "Mode précédent = " << quelEstTonChoix << "\n";
                break;
              }
            case SDLK_RETURN:
              {
                std::cout << "Mode choisi = " << quelEstTonChoix+1 << "\n";
                this->mode = quelEstTonChoix+1;
                theChoosenHasBeenChoosen = true;
                Mix_PlayChannel(-1, this->selection_sound, 0);
                break;
              }
            case SDLK_ESCAPE:
              {
                // On s'en va
                SDL_Quit();
                exit(0);
                break;
              }
            default: break;
          }
        default: break;
      }
    }

    // On efface la fenêtre
    SDL_SetRenderDrawColor(win->renderer,19,19,19,255);
    SDL_RenderClear(win->renderer);

    // ---- On dessine le fond ---- //
    // Déco blocs
    SDL_Rect *srcTetris = win->sprites.at("deco").get();
    for(int i = 0; i < 1400; i+=1056)
    {
      int j = 1000-287;
      SDL_Rect dest = {i,j,srcTetris->w,srcTetris->h};
      SDL_RenderCopy(win->renderer,win->pTexture,srcTetris,&dest);
    }
    // --- Affichage titre ---- //
    SDL_Color colorTitre = { 169, 59, 58 };
    SDL_Surface *surface = TTF_RenderText_Solid(win->font,"TETRIS666", colorTitre);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(win->renderer, surface);
    SDL_Rect dstrect = { (tailleWarZoneX-600)/2, 100, 600, 100 };
    SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

    SDL_Color color = { 100, 100, 100 };
    SDL_Color colorSelect = { 95, 128, 144 };
    int marginTop = 300;
    switch (quelEstTonChoix) {
      case 0:
        {
          SDL_Surface *surface = TTF_RenderText_Solid(win->font,"> MODE SOLO <", colorSelect);
          SDL_Texture *texture = SDL_CreateTextureFromSurface(win->renderer, surface);
          SDL_Rect dstrect = { (tailleWarZoneX-250)/2, marginTop, 250, 45 };
          SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
          SDL_DestroyTexture(texture);
          SDL_FreeSurface(surface);
          surface = TTF_RenderText_Solid(win->font,"MODE 1V1", color);
          texture = SDL_CreateTextureFromSurface(win->renderer, surface);
          dstrect = { (tailleWarZoneX-170)/2, marginTop+60, 170, 45 };
          SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
          SDL_DestroyTexture(texture);
          SDL_FreeSurface(surface);
          surface = TTF_RenderText_Solid(win->font,"MODE VS IA", color);
          texture = SDL_CreateTextureFromSurface(win->renderer, surface);
          dstrect = { (tailleWarZoneX-180)/2, marginTop+120, 180, 45 };
          SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
          SDL_DestroyTexture(texture);
          SDL_FreeSurface(surface);
          surface = TTF_RenderText_Solid(win->font,"MODE CARNAGE", color);
          texture = SDL_CreateTextureFromSurface(win->renderer, surface);
          dstrect = { (tailleWarZoneX-250)/2, marginTop+180, 250, 45 };
          SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
          SDL_DestroyTexture(texture);
          SDL_FreeSurface(surface);
          break;
        }
      case 1:
        {
          SDL_Surface *surface = TTF_RenderText_Solid(win->font,"MODE SOLO", color);
          SDL_Texture *texture = SDL_CreateTextureFromSurface(win->renderer, surface);
          SDL_Rect dstrect = { (tailleWarZoneX-185)/2, marginTop, 185, 45 };
          SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
          SDL_DestroyTexture(texture);
          SDL_FreeSurface(surface);
          surface = TTF_RenderText_Solid(win->font,"> MODE 1V1 <", colorSelect);
          texture = SDL_CreateTextureFromSurface(win->renderer, surface);
          dstrect = { (tailleWarZoneX-235)/2, marginTop+60, 235, 45 };
          SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
          SDL_DestroyTexture(texture);
          SDL_FreeSurface(surface);
          surface = TTF_RenderText_Solid(win->font,"MODE VS IA", color);
          texture = SDL_CreateTextureFromSurface(win->renderer, surface);
          dstrect = { (tailleWarZoneX-180)/2, marginTop+120, 180, 45 };
          SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
          SDL_DestroyTexture(texture);
          SDL_FreeSurface(surface);
          surface = TTF_RenderText_Solid(win->font,"MODE CARNAGE", color);
          texture = SDL_CreateTextureFromSurface(win->renderer, surface);
          dstrect = { (tailleWarZoneX-250)/2, marginTop+180, 250, 45 };
          SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
          SDL_DestroyTexture(texture);
          SDL_FreeSurface(surface);
          break;
        }
      case 2:
        {
          SDL_Surface *surface = TTF_RenderText_Solid(win->font,"MODE SOLO", color);
          SDL_Texture *texture = SDL_CreateTextureFromSurface(win->renderer, surface);
          SDL_Rect dstrect = { (tailleWarZoneX-185)/2, marginTop, 185, 45 };
          SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
          SDL_DestroyTexture(texture);
          SDL_FreeSurface(surface);
          surface = TTF_RenderText_Solid(win->font,"MODE 1V1", color);
          texture = SDL_CreateTextureFromSurface(win->renderer, surface);
          dstrect = { (tailleWarZoneX-170)/2, marginTop+60, 170, 45 };
          SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
          SDL_DestroyTexture(texture);
          SDL_FreeSurface(surface);
          surface = TTF_RenderText_Solid(win->font,"> MODE VS IA <", colorSelect);
          texture = SDL_CreateTextureFromSurface(win->renderer, surface);
          dstrect = { (tailleWarZoneX-245)/2, marginTop+120, 245, 45 };
          SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
          SDL_DestroyTexture(texture);
          SDL_FreeSurface(surface);
          surface = TTF_RenderText_Solid(win->font,"MODE CARNAGE", color);
          texture = SDL_CreateTextureFromSurface(win->renderer, surface);
          dstrect = { (tailleWarZoneX-250)/2, marginTop+180, 250, 45 };
          SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
          SDL_DestroyTexture(texture);
          SDL_FreeSurface(surface);
          break;
        }
      case 3:
        {
          SDL_Surface *surface = TTF_RenderText_Solid(win->font,"MODE SOLO", color);
          SDL_Texture *texture = SDL_CreateTextureFromSurface(win->renderer, surface);
          SDL_Rect dstrect = { (tailleWarZoneX-185)/2, marginTop, 185, 45 };
          SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
          SDL_DestroyTexture(texture);
          SDL_FreeSurface(surface);
          surface = TTF_RenderText_Solid(win->font,"MODE 1V1", color);
          texture = SDL_CreateTextureFromSurface(win->renderer, surface);
          dstrect = { (tailleWarZoneX-170)/2, marginTop+60, 170, 45 };
          SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
          SDL_DestroyTexture(texture);
          SDL_FreeSurface(surface);
          surface = TTF_RenderText_Solid(win->font,"MODE VS IA", color);
          texture = SDL_CreateTextureFromSurface(win->renderer, surface);
          dstrect = { (tailleWarZoneX-180)/2, marginTop+120, 180, 45 };
          SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
          SDL_DestroyTexture(texture);
          SDL_FreeSurface(surface);
          surface = TTF_RenderText_Solid(win->font,"> MODE CARNAGE <", colorSelect);
          texture = SDL_CreateTextureFromSurface(win->renderer, surface);
          dstrect = { (tailleWarZoneX-305)/2, marginTop+180, 305, 45 };
          SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
          SDL_DestroyTexture(texture);
          SDL_FreeSurface(surface);
          break;
        }
      default: break;
    }

    SDL_RenderPresent(win->renderer);

  }


}

// ------------------------------------------------- //
// -------------- ECRAN DE FIN DE JEU -------------- //
// ------------------------------------------------- //

void Main::drawEndScreen() {
  // On efface la fenêtre
  SDL_SetRenderDrawColor(win->renderer,0,0,0,255);
  SDL_RenderClear(win->renderer);

  // ---- On dessine le fond ---- //
  SDL_SetRenderDrawColor(win->renderer,25,25,25,255);
  SDL_Rect cestLaFinLesZamis = { 0, 0, tailleWarZoneX, tailleWarZoneY};
  SDL_RenderFillRect(win->renderer,&cestLaFinLesZamis);
  SDL_Rect *srcFond = win->sprites.at("pattern").get();
  for(int i = 0; i < tailleWarZoneX; i+=srcFond->w)
  {
    for(int j = 0; j < tailleWarZoneY; j+=srcFond->h)
    {
      SDL_Rect dest = {i,j,srcFond->w,srcFond->h};
      SDL_RenderCopy(win->renderer,win->pTexture,srcFond,&dest);
    }
  }

  // ---- Bloc qui contient le texte ---- //
  int grandeur = 200;
  int epaisseur = 400;
  int topDepartEnX = (tailleWarZoneX - epaisseur)/2;
  int topDepartEnY = (tailleWarZoneY - grandeur)/2;
  SDL_SetRenderDrawColor(win->renderer,30,30,30,255);
  cestLaFinLesZamis = { topDepartEnX-30, topDepartEnY-30, epaisseur+60, grandeur+60};
  SDL_RenderFillRect(win->renderer,&cestLaFinLesZamis);
  SDL_SetRenderDrawColor(win->renderer,20,20,20,255);
  cestLaFinLesZamis = { topDepartEnX, topDepartEnY, epaisseur, grandeur};
  SDL_RenderFillRect(win->renderer,&cestLaFinLesZamis);
  // ---- Texte rouge qui indique comment on quitte ---- //
  SDL_Color color = { 169, 59, 58 };
  SDL_Surface *surface = TTF_RenderText_Solid(win->font,"APPUIE SUR ECHAP POUR QUITTER", color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(win->renderer, surface);
  SDL_Rect dstrect = { topDepartEnX-30, topDepartEnY+grandeur+45, 460, 45 };
  SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);

  // ---- Affichage du vainqueur selon le mode de jeu ---- //
  if (mode > 1) {
    int zblehExploseeee;
    int unScoreScoreux;
    if(game1.get_score() > game2.get_score()) {
      zblehExploseeee = 1;
      unScoreScoreux = game1.get_score();
    }
    else {
      zblehExploseeee = 2;
      unScoreScoreux = game2.get_score();
    }
    // ---- Affichage de fin ---- //
    color = { 174, 174, 174 };
    std::string endCreditsWinner = "JOUEUR" + std::to_string(zblehExploseeee) + " A GAGNE";
    std::string theFinalScore = std::to_string(unScoreScoreux) + " POINTS";
    surface = TTF_RenderText_Solid(win->font,endCreditsWinner.c_str(), color);
    texture = SDL_CreateTextureFromSurface(win->renderer, surface);
    dstrect = { topDepartEnX+25, topDepartEnY+25, 350, 55 };
    SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    surface = TTF_RenderText_Solid(win->font,"AVEC", color);
    texture = SDL_CreateTextureFromSurface(win->renderer, surface);
    dstrect = { topDepartEnX+155, topDepartEnY+82, 90, 35 };
    SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    color = { 142, 71, 141 };
    surface = TTF_RenderText_Solid(win->font,theFinalScore.c_str(), color);
    texture = SDL_CreateTextureFromSurface(win->renderer, surface);
    dstrect = { topDepartEnX+95, topDepartEnY+135, 210, 50 };
    SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

  }
  else { // ---- Affichage du score pour le mode solo ---- //
    color = { 174, 174, 174 };
    std::string theFinalScore = std::to_string(game1.get_score()) + " POINTS";
    // ---- Affichage de fin ---- //
    surface = TTF_RenderText_Solid(win->font,"PARTIE TERMINEE", color);
    texture = SDL_CreateTextureFromSurface(win->renderer, surface);
    dstrect = { topDepartEnX+33, topDepartEnY+25, 340, 50 };
    SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
    surface = TTF_RenderText_Solid(win->font,"AVEC", color);
    texture = SDL_CreateTextureFromSurface(win->renderer, surface);
    dstrect = { topDepartEnX+155, topDepartEnY+82, 90, 35 };
    SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
    color = { 142, 71, 141 };
    surface = TTF_RenderText_Solid(win->font,theFinalScore.c_str(), color);
    texture = SDL_CreateTextureFromSurface(win->renderer, surface);
    dstrect = { topDepartEnX+95, topDepartEnY+135, 210, 50 };
    SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
  }
}

// ---------------------------------------------- //
// -------------- DESSIN D'UN CUBE -------------- //
// ---------------------------------------------- //

void Main::draw_boxi(int x, int y, int taille, SDL_Color color, int left_marge)
{
    SDL_Rect dest = { left_marge + taille*x, taille*y, taille, taille };
    SDL_SetRenderDrawColor(win->renderer,color.r,color.g,color.b,255);
    SDL_RenderFillRect(win->renderer,&dest);
    SDL_SetRenderDrawColor(win->renderer,color.r/2,color.g/2,color.b/2,100);
    SDL_RenderDrawRect(win->renderer,&dest);
}

void Main::draw_boxi_right(int sx, int sy, int x, int y, int taille,SDL_Color color, int left_marge)
{
    SDL_Rect dest = { left_marge + sx+(taille*x), sy+(taille*y), taille, taille };
    SDL_SetRenderDrawColor(win->renderer,color.r,color.g,color.b,255);
    SDL_RenderFillRect(win->renderer,&dest);
    SDL_SetRenderDrawColor(win->renderer,color.r/2,color.g/2,color.b/2,10);
    SDL_RenderDrawRect(win->renderer,&dest);
}

// ----------------------------------------------- //
// ---------------- FONCTION MAIN ---------------- //
// ----------------------------------------------- //

int main(int argc, char** argv)
{
  if(SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() != 0)
  {
    return 1;
  }

  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
  {
    printf("%s", Mix_GetError());
  }

  Main m;
  m.init(15,25,1850,1000);
  // std::cout << "bjr\n";
  m.loop();

  
  Mix_CloseAudio();
  return 0;

}
