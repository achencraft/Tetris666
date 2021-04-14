#include "Main.h"




void Main::init(int mode, int largeur_grille, int hauteur_grille, int tailleZoneJeuX, int tailleZoneJeuY)
{
    win = new WindowSurface("Tetris666",tailleZoneJeuX,tailleZoneJeuY);
    win->ajouter_sprite("fond",Sprite({0,0,10,10}));
    win->ajouter_sprite("deco",Sprite({0,0,1056,287}));
    win->ajouter_sprite("pattern",Sprite({0,288,320,423}));
    win->ajouter_sprite("boxi",Sprite({299,0,40,40}));
    this->hauteur_grille = hauteur_grille;
    this->largeur_grille = largeur_grille;
    this->mode = mode;
    int taille_boxi = 1000/hauteur_grille;
    int largeurZoneJeu = taille_boxi*largeur_grille;

    // Marge de gauche
    left_marge1 = (1400 - largeurZoneJeu)/2;
    left_marge2 = 0;

    Game g1,g2;
    this->game1 = g1;
    game1.init(largeur_grille, hauteur_grille);
    if(mode > 1)
    {
      this->game2 = g2;
      game2.init(largeur_grille, hauteur_grille);
    }

}




void Main::loop()
{

  bool quit = false;
  int w, h, cheh1 = 0, cheh2 = 0;
  this->win->get_dimension(&h,&w);

  //gestion du temps
  unsigned int lastTime1 = 0, delai_chute1 = 1000, currentTime;
  unsigned int lastTime2 = 0, delai_chute2 = 1000;
  unsigned int lastTime3 = 0, delai_chute3 = 333;
  if(mode == 4) delai_chute3 = 0;
  

  while(!quit)
  {
    currentTime = SDL_GetTicks();

    SDL_Event event;
    while (!quit && SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT:
          quit = true;
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


    //IA idiote
    
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

    //on vérifie si une nouvelle pièce doit etre générée
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
    this->draw(w,h);

    // affiche la surface
    SDL_RenderPresent(win->renderer);


  }

  std::cout << "fini\n" ;
  SDL_Quit();
}

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

  // --------------------------------------- //
  // ---------- AFFICHAGE SPRITES ---------- //
  // --------------------------------------- //

  // Fond sombre
  SDL_Rect *srcBackground = win->sprites.at("fond").get();
  for(i = 0; i < 1400; i+=10)
  {
    for(j = 0; j < 1000 ; j+=10 ) {
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
  SDL_SetRenderDrawColor(win->renderer,24,24,24,255);
  SDL_Rect bordureSombre = { depart-50, 0, 50, hauteur};
  SDL_RenderFillRect(win->renderer,&bordureSombre);
  bordureSombre = { depart+largeurZoneJeu, 0, 50, hauteur};
  SDL_RenderFillRect(win->renderer,&bordureSombre);


  if(mode > 1)
  {
    left_marge1 = 700;
  }


  //placer les boxies placés
  std::vector<Boxi> grille1 = game1.get_grille();
  for (size_t i = 0; i < grille1.size(); i++) {
    Boxi boxi = grille1[i];
    SDL_Color color = boxi.get_color();
    draw_boxi(boxi.get_x(), boxi.get_y(), taille_boxi, color, left_marge1);
  }

  //placer la pièce qui tombe
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
      //placer les boxies placés
      std::vector<Boxi> grille2 = game2.get_grille();
      for (size_t i = 0; i < grille2.size(); i++) {
        Boxi boxi = grille2[i];
        SDL_Color color = boxi.get_color();
        draw_boxi(boxi.get_x(), boxi.get_y(), taille_boxi, color, left_marge2);
      }

      //placer la pièce qui tombe
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

  // Placer colonne droite

  // SDL_SetRenderDrawColor(win->renderer,209,141,127,0);
  // SDL_Rect rightcol = { posBordureDroite, 0, 200, hauteur};
  // SDL_RenderFillRect(win->renderer,&rightcol);

  if(mode > 1)
  {
    //afficher_colonne(depart+largeurZoneJeu+100, game2);
    //afficher_colonne(depart+largeurZoneJeu+100, game1);
  }
  else
  {
    afficher_colonne(depart+largeurZoneJeu+100, game1);
  }

}

void Main::afficher_colonne(int left_marge, Game game)
{
  // --------------------------------------- //
  // ---------- AFFICHAGE TEXTES ----------- //
  // --------------------------------------- //

  SDL_Color color = { 169, 59, 58 };
  //Affichage titre
  SDL_Color colorTitre = { 80, 80, 80 };
  SDL_Surface *surface = TTF_RenderText_Solid(win->font,"TETRIS666", colorTitre);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(win->renderer, surface);
  SDL_Rect dstrect = { left_marge, 45, 190, 50 };
  SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);

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
  // texte score
  SDL_Color colorPoints = { 90, 90, 90 };
  std::string s = std::to_string(game.get_score()) + " POINTS";
  surface = TTF_RenderText_Solid(win->font,s.c_str(), colorPoints);
  texture = SDL_CreateTextureFromSurface(win->renderer, surface);
  dstrect = { left_marge+40, 210, 100, 40 };
  SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);

  //Affichage pièce suivante
  // carré fond noir
  SDL_SetRenderDrawColor(win->renderer,24,24,24,255);
  rightcol = { left_marge, 340, 190, 180};
  SDL_RenderFillRect(win->renderer,&rightcol);
  // titre
  surface = TTF_RenderText_Solid(win->font,"PIECE SUIVANTE:", color);
  texture = SDL_CreateTextureFromSurface(win->renderer, surface);
  dstrect = { left_marge+15, 355, 145, 20 };
  SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);

  //placer la prochaine pièce
  Piece piece_suivante = game.get_piece_suivante();
  std::vector<Boxi> *piece = piece_suivante.get_boxies();
  color = piece_suivante.get_color();
  for (size_t i = 0; i < piece->size(); i++) {
    Boxi boxi = piece->at(i);
    draw_boxi_right(-15,420,piece->at(i).get_x(), piece->at(i).get_y(), 15,color, left_marge);
  }

  //Affichage pièce sauvegardée
  // carré fond noir
  SDL_SetRenderDrawColor(win->renderer,24,24,24,255);
  rightcol = { left_marge, 570, 190, 180};
  SDL_RenderFillRect(win->renderer,&rightcol);
  // titre
  color = { 169, 59, 58 };
  surface = TTF_RenderText_Solid(win->font,"PIECE SAUVEGARDEE:", color);
  texture = SDL_CreateTextureFromSurface(win->renderer, surface);
  dstrect = { left_marge+15, 585, 165, 20 };
  SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);

  //placer la piece sauvegardee
  if(game.get_yatilUnePieceSauvee())
  {
    int hauteur_piece,largeur_piece,min_x,min_y;
    Piece piece_sauvegarde = game.get_piece_sauvegarde();
    std::vector<Boxi> *piece = piece_sauvegarde.get_boxies();
    piece_sauvegarde.get_piece_dim(&hauteur_piece,&largeur_piece,&min_x,&min_y);
    SDL_Color color = piece_sauvegarde.get_color();

    for (size_t i = 0; i < piece->size(); i++) {
      Boxi boxi = piece->at(i);
      draw_boxi_right(-15,635,piece->at(i).get_x()-min_x+6, piece->at(i).get_y()-min_y+1, 15, color, left_marge);
    }
  }

}

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



int main(int argc, char** argv)
{
  if(SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() != 0)
  {
    return 1;
  }

  if(argc < 1 || argc > 2)
  {
      std::cout << "Usage:" << argv[0] << " [versus | ordi] \n" ;
      return 1;
  }

  if(argc == 2)
  {
      if(strcmp(argv[1],"versus") == 0)
        {
            Main m;
            m.init(2,15,25,1400,1000);
            m.loop();
            return 0;
        }
      if(strcmp(argv[1],"ordi") == 0)
        {
            Main m;
            m.init(3,15,25,1400,1000);
            m.loop();
            return 0;
        }
      if(strcmp(argv[1],"carnage") == 0)
        {
            Main m;
            m.init(4,15,25,1400,1000);
            m.loop();
            return 0;
        }
      std::cout << "Usage:" << argv[0] << " [versus | ordi] \n" ;
      return 1;
  }
  else
  {
      Main m;
      m.init(1,15,25,1400,1000);
      m.loop();
  }

    return 0;

}
