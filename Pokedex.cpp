//
// Created by mich on 22/02/19.
//

#include "Pokedex.h"

void Pokedex::extract_representatives() {
   _representatives.clear();
   for (unsigned x = 0; x != Pokemon::NUM_TYPES; ++x) {
      for (unsigned y = x; y != Pokemon::NUM_TYPES; ++y) {
         if (not _matrix[x][y]->empty()) {
            _representatives.emplace_back(&_matrix[x][y]->front());
            for (auto const &similar: *_matrix[x][y]) {
               if (_representatives.back()->total_stats() < similar.total_stats()) {
                  _representatives.back() = &similar;  // in this way we keep the representative with higher stats
               }
            }
         }
      }
   }
}

std::array<std::array<std::shared_ptr<std::vector<Pokemon>>, Pokemon::NUM_TYPES>, Pokemon::NUM_TYPES>
Pokedex::create_type_pair_matrix() {
   std::array<std::array<std::shared_ptr<std::vector<Pokemon>>, Pokemon::NUM_TYPES>, Pokemon::NUM_TYPES> matrix;
   for (unsigned x = 0; x != Pokemon::NUM_TYPES; ++x) {
      for (unsigned y = 0; y != Pokemon::NUM_TYPES; ++y) {
         if (x <= y) {
            matrix[x][y] = std::make_shared<std::vector<Pokemon>>(std::vector<Pokemon>(0));
         } else {
            matrix[x][y] = matrix[y][x];
         }
      }
   }
   return matrix;
}

void Pokedex::make(unsigned regions, unsigned inclusions) {
   for (unsigned x = 0; x != Pokemon::NUM_TYPES; ++x) {
      for (unsigned y = 0; y != Pokemon::NUM_TYPES; ++y) {
         _matrix[x][y]->clear();
      }
   }

   if (RegionsFlag::KANTO & regions) {
      if (InclusionFlag::STARTERS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(1, 318, "Bulbasaur", PokeType::Grass, PokeType::Poison);
            add_pokemon(2, 405, "Ivysaur", PokeType::Grass, PokeType::Poison);
         }
         add_pokemon(3, 525, "Venusaur", PokeType::Grass, PokeType::Poison);
         if (InclusionFlag::MEGAS & inclusions) {
            add_pokemon(3, 625, "MegaVenusaur", PokeType::Grass, PokeType::Poison);
         }
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(4, 309, "Charmander", PokeType::Fire);
            add_pokemon(5, 405, "Charmeleon", PokeType::Fire);
         }
         add_pokemon(6, 534, "Charizard", PokeType::Fire, PokeType::Flying);
         if (InclusionFlag::MEGAS & inclusions) {
            add_pokemon(6, 634, "MegaCharizardX", PokeType::Fire, PokeType::Dragon);
            add_pokemon(6, 634, "MegaCharizardY", PokeType::Fire, PokeType::Flying);
         }
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(7, 314, "Squirtle", PokeType::Water);
            add_pokemon(8, 405, "Wartortle", PokeType::Water);
         }
         add_pokemon(9, 530, "Blastoise", PokeType::Water);
         if (InclusionFlag::MEGAS & inclusions) {
            add_pokemon(9, 630, "MegaBlastoise", PokeType::Water);
         }
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(10, 195, "Caterpie", PokeType::Bug);
         add_pokemon(11, 205, "Metapod", PokeType::Bug);
      }
      add_pokemon(12, 395, "Butterfree", PokeType::Bug, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(13, 195, "Weedle", PokeType::Bug, PokeType::Poison);
         add_pokemon(14, 205, "Kakuna", PokeType::Bug, PokeType::Poison);
      }
      add_pokemon(15, 395, "Beedrill", PokeType::Bug, PokeType::Poison);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(15, 495, "MegaBeedrill", PokeType::Bug, PokeType::Poison);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(16, 251, "Pidgey", PokeType::Normal, PokeType::Flying);
         add_pokemon(17, 349, "Pidgeotto", PokeType::Normal, PokeType::Flying);
      }
      add_pokemon(18, 479, "Pidgeot", PokeType::Normal, PokeType::Flying);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(18, 579, "MegaPidgeot", PokeType::Normal, PokeType::Flying);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(19, 253, "Rattata", PokeType::Normal);
         if (InclusionFlag::ALOLAFORMS & inclusions) {
            add_pokemon(19, 253, "AlolanRattata", PokeType::Dark, PokeType::Normal);
         }
      }
      add_pokemon(20, 413, "Raticate", PokeType::Normal);
      if (InclusionFlag::ALOLAFORMS & inclusions) {
         add_pokemon(20, 413, "AlolanRaticate", PokeType::Dark, PokeType::Normal);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(21, 262, "Spearow", PokeType::Normal, PokeType::Flying);
      }
      add_pokemon(22, 442, "Fearow", PokeType::Normal, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(23, 288, "Ekans", PokeType::Poison);
      }
      add_pokemon(24, 448, "Arbok", PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(25, 320, "Pikachu", PokeType::Electric);
      }
      add_pokemon(26, 485, "Raichu", PokeType::Electric);
      if (InclusionFlag::ALOLAFORMS & inclusions) {
         add_pokemon(26, 485, "AlolanRaichu", PokeType::Electric, PokeType::Psychic);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(27, 300, "Sandshrew", PokeType::Ground);
         if (InclusionFlag::ALOLAFORMS & inclusions) {
            add_pokemon(27, 300, "AlolanSandshrew", PokeType::Ice, PokeType::Steel);
         }
      }
      add_pokemon(28, 450, "Sandlash", PokeType::Ground);
      if (InclusionFlag::ALOLAFORMS & inclusions) {
         add_pokemon(28, 450, "AlolanSandslash", PokeType::Ice, PokeType::Steel);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(29, 275, "Nidoran_f", PokeType::Poison);
         add_pokemon(30, 365, "Nidorina", PokeType::Poison);
      }
      add_pokemon(31, 505, "Nidoqueen", PokeType::Poison, PokeType::Ground);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(32, 273, "Nidoran_m", PokeType::Poison);
         add_pokemon(33, 365, "Nidorino", PokeType::Poison);
      }
      add_pokemon(34, 505, "Nidoking", PokeType::Poison, PokeType::Ground);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(35, 323, "Clefairy", PokeType::Fairy);
      }
      add_pokemon(36, 483, "Clefable", PokeType::Fairy);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(37, 299, "Vulpix", PokeType::Fire);
         if (InclusionFlag::ALOLAFORMS & inclusions) {
            add_pokemon(37, 299, "AlolanVulpix", PokeType::Ice);
         }
      }
      add_pokemon(38, 505, "Ninetales", PokeType::Fire);
      if (InclusionFlag::ALOLAFORMS & inclusions) {
         add_pokemon(38, 505, "AlolanNinetales", PokeType::Ice, PokeType::Fairy);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(39, 270, "Jigglypuff", PokeType::Normal, PokeType::Fairy);
      }
      add_pokemon(40, 435, "Wiglytuff", PokeType::Normal, PokeType::Fairy);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(41, 245, "Zubat", PokeType::Poison, PokeType::Flying);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(42, 455, "Golbat", PokeType::Poison, PokeType::Flying);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(43, 320, "Oddish", PokeType::Grass, PokeType::Poison);
         add_pokemon(44, 395, "Gloom", PokeType::Grass, PokeType::Poison);
      }
      add_pokemon(45, 490, "Vileplume", PokeType::Grass, PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(46, 285, "Paras", PokeType::Bug, PokeType::Grass);
      }
      add_pokemon(47, 405, "Parasect", PokeType::Bug, PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(48, 305, "Venonat", PokeType::Bug, PokeType::Poison);
      }
      add_pokemon(49, 450, "Venomoth", PokeType::Bug, PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(50, 265, "Diglett", PokeType::Ground);
         if (InclusionFlag::ALOLAFORMS & inclusions) {
            add_pokemon(50, 265, "AlolanDiglett", PokeType::Ground, PokeType::Steel);
         }
      }
      add_pokemon(51, 425, "Dugtrio", PokeType::Ground);
      if (InclusionFlag::ALOLAFORMS & inclusions) {
         add_pokemon(51, 425, "AlolanDugtrio", PokeType::Ground, PokeType::Steel);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(52, 290, "Meowth", PokeType::Normal);
         if (InclusionFlag::ALOLAFORMS & inclusions) {
            add_pokemon(52, 290, "AlolanMeowth", PokeType::Dark);
         }
      }
      add_pokemon(53, 440, "Persian", PokeType::Normal);
      if (InclusionFlag::ALOLAFORMS & inclusions) {
         add_pokemon(53, 440, "AlolanPersian", PokeType::Dark);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(54, 320, "Psyduck", PokeType::Water);
      }
      add_pokemon(55, 500, "Golduck", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(56, 305, "Mankey", PokeType::Fighting);
      }
      add_pokemon(57, 455, "Primeape", PokeType::Fighting);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(58, 350, "Growlithe", PokeType::Fire);
      }
      add_pokemon(59, 555, "Arcanine", PokeType::Fire);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(60, 300, "Poliwag", PokeType::Water);
         add_pokemon(61, 385, "Poliwhirl", PokeType::Water);
      }
      add_pokemon(62, 510, "Poliwrath", PokeType::Water, PokeType::Fighting);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(63, 310, "Abra", PokeType::Psychic);
         add_pokemon(64, 400, "Kadabra", PokeType::Psychic);
      }
      add_pokemon(65, 500, "Alakazam", PokeType::Psychic);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(65, 600, "MegaAlakazam", PokeType::Psychic);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(66, 305, "Machop", PokeType::Fighting);
         add_pokemon(67, 405, "Machoke", PokeType::Fighting);
      }
      add_pokemon(68, 505, "Machamp", PokeType::Fighting);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(69, 300, "Bellsprout", PokeType::Grass, PokeType::Poison);
         add_pokemon(70, 390, "Weepinbell", PokeType::Grass, PokeType::Poison);
      }
      add_pokemon(71, 490, "Victreebel", PokeType::Grass, PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(72, 335, "Tentacool", PokeType::Water, PokeType::Poison);
      }
      add_pokemon(73, 515, "Tentacruel", PokeType::Water, PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(74, 300, "Geodude", PokeType::Rock, PokeType::Ground);
         if (InclusionFlag::ALOLAFORMS & inclusions) {
            add_pokemon(74, 300, "AlolanGeodude", PokeType::Rock, PokeType::Electric);
         }
         add_pokemon(75, 390, "Graveler", PokeType::Rock, PokeType::Ground);
         if (InclusionFlag::ALOLAFORMS & inclusions) {
            add_pokemon(75, 390, "AlolanGraveler", PokeType::Rock, PokeType::Electric);
         }
      }
      add_pokemon(76, 495, "Golem", PokeType::Rock, PokeType::Ground);
      if (InclusionFlag::ALOLAFORMS & inclusions) {
         add_pokemon(76, 495, "AlolanGolem", PokeType::Rock, PokeType::Electric);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(77, 410, "Ponyta", PokeType::Fire);
      }
      add_pokemon(78, 500, "Rapidash", PokeType::Fire);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(79, 315, "Slopoke", PokeType::Water, PokeType::Psychic);
      }
      add_pokemon(80, 490, "Slowbro", PokeType::Water, PokeType::Psychic);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(80, 590, "MegaSlowbro", PokeType::Water, PokeType::Psychic);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(81, 325, "Magnemite", PokeType::Electric, PokeType::Steel);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(82, 465, "Magneton", PokeType::Electric, PokeType::Steel);
      }
      add_pokemon(83, 377, "Farfetch'd", PokeType::Normal, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(84, 310, "Doduo", PokeType::Normal, PokeType::Flying);
      }
      add_pokemon(85, 470, "Dodrio", PokeType::Normal, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(86, 325, "Seel", PokeType::Water, PokeType::Ice);
      }
      add_pokemon(87, 475, "Dwegong", PokeType::Water, PokeType::Ice);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(88, 325, "Grimer", PokeType::Poison);
         if (InclusionFlag::ALOLAFORMS & inclusions) {
            add_pokemon(88, 325, "AlolanGrimer", PokeType::Poison, PokeType::Dark);
         }
      }
      add_pokemon(89, 500, "Muk", PokeType::Poison);
      if (InclusionFlag::ALOLAFORMS & inclusions) {
         add_pokemon(89, 500, "AlolanMuk", PokeType::Poison, PokeType::Dark);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(90, 305, "Shellder", PokeType::Water);
      }
      add_pokemon(91, 525, "Cloyster", PokeType::Water, PokeType::Ice);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(92, 310, "Gastly", PokeType::Ghost, PokeType::Poison);
         add_pokemon(93, 405, "Haunter", PokeType::Ghost, PokeType::Poison);
      }
      add_pokemon(94, 500, "Gengar", PokeType::Ghost, PokeType::Poison);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(94, 600, "MegaGengar", PokeType::Ghost, PokeType::Poison);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(95, 385, "Onix", PokeType::Rock, PokeType::Ground);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(96, 328, "Drowzee", PokeType::Psychic);
      }
      add_pokemon(97, 483, "Hypno", PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(98, 325, "Krabby", PokeType::Water);
      }
      add_pokemon(99, 475, "Kingler", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(100, 330, "Voltorb", PokeType::Electric);
      }
      add_pokemon(101, 490, "Electrode", PokeType::Electric);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(102, 325, "Exeggcute", PokeType::Grass, PokeType::Psychic);
      }
      add_pokemon(103, 530, "Exeggutor", PokeType::Grass, PokeType::Psychic);
      if (InclusionFlag::ALOLAFORMS & inclusions) {
         add_pokemon(103, 530, "AlolanExeggutor", PokeType::Grass, PokeType::Dragon);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(104, 320, "Cubone", PokeType::Ground);
      }
      add_pokemon(105, 425, "Marowak", PokeType::Ground);
      if (InclusionFlag::ALOLAFORMS & inclusions) {
         add_pokemon(105, 425, "AlolanMarowak", PokeType::Fire, PokeType::Ghost);
      }
      add_pokemon(106, 455, "Hitmonlee", PokeType::Fighting);
      add_pokemon(107, 455, "Hitmonchan", PokeType::Fighting);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(108, 385, "Lickitung", PokeType::Normal);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(109, 340, "Koffing", PokeType::Poison);
      }
      add_pokemon(110, 490, "Weezing", PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(111, 345, "Rhyhorn", PokeType::Ground, PokeType::Rock);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(112, 485, "Rhydon", PokeType::Ground, PokeType::Rock);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(113, 450, "Chansey", PokeType::Normal);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(114, 435, "Tangela", PokeType::Grass);
      }
      add_pokemon(115, 490, "Kangaskhan", PokeType::Normal);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(115, 590, "MegaKangakhan", PokeType::Normal);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(116, 295, "Horsea", PokeType::Water);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(117, 440, "Seadra", PokeType::Water);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(118, 320, "Goldeen", PokeType::Water);
      }
      add_pokemon(119, 450, "Seaking", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(120, 340, "Staryu", PokeType::Water);
      }
      add_pokemon(121, 520, "Starmie", PokeType::Water, PokeType::Psychic);
      add_pokemon(122, 460, "Mr.Mime", PokeType::Psychic, PokeType::Fairy);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(123, 500, "Scyther", PokeType::Bug, PokeType::Flying);
      }
      add_pokemon(124, 455, "Jynx", PokeType::Ice, PokeType::Psychic);

      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(125, 490, "Electabuzz", PokeType::Electric);
         add_pokemon(126, 495, "Magmar", PokeType::Fire);
      }
      add_pokemon(127, 500, "Pinsir", PokeType::Bug);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(127, 600, "MegaPinsir", PokeType::Bug, PokeType::Flying);
      }
      add_pokemon(128, 490, "Tauros", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(129, 200, "Magikarp", PokeType::Water);
      }
      add_pokemon(130, 540, "Gyarados", PokeType::Water, PokeType::Flying);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(130, 640, "MegaGyarados", PokeType::Water, PokeType::Dark);
      }
      add_pokemon(131, 535, "Lapras", PokeType::Water, PokeType::Ice);
      add_pokemon(132, 288, "Ditto", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(133, 325, "Eevee", PokeType::Normal);
      }
      add_pokemon(134, 525, "Vaporeon", PokeType::Water);
      add_pokemon(135, 525, "Jolteon", PokeType::Electric);
      add_pokemon(136, 525, "Flareon", PokeType::Fire);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or
          (not(RegionsFlag::JOHTO & regions) and not(RegionsFlag::SINNOH & regions))) {
         add_pokemon(137, 395, "Porygon", PokeType::Normal);
      }
      if (InclusionFlag::FOSSILS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(138, 355, "Omanyte", PokeType::Rock, PokeType::Water);
         }
         add_pokemon(139, 495, "Omastar", PokeType::Rock, PokeType::Water);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(140, 355, "Kabuto", PokeType::Rock, PokeType::Water);
         }
         add_pokemon(141, 495, "Kabutops", PokeType::Rock, PokeType::Water);
         add_pokemon(142, 515, "Aerodactyl", PokeType::Rock, PokeType::Flying);
         if (InclusionFlag::MEGAS & inclusions) {
            add_pokemon(142, 615, "MegaAerodactyl", PokeType::Rock, PokeType::Flying);
         }
      }
      add_pokemon(143, 540, "Snorlax", PokeType::Normal);
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(144, 580, "Articuno", PokeType::Ice, PokeType::Flying);
         add_pokemon(145, 580, "Zapdos", PokeType::Electric, PokeType::Flying);
         add_pokemon(146, 580, "Moltres", PokeType::Fire, PokeType::Flying);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(147, 300, "Dratini", PokeType::Dragon);
         add_pokemon(148, 420, "Dragonair", PokeType::Dragon);
      }
      if (InclusionFlag::PSEUDOLEGENDARIES & inclusions) {
         add_pokemon(149, 600, "Dragonite", PokeType::Dragon, PokeType::Flying);
      }
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(150, 680, "MewTwo", PokeType::Psychic);
         if (InclusionFlag::MEGAS & inclusions) {
            add_pokemon(150, 780, "MegaMewTwoX", PokeType::Psychic, PokeType::Fighting);
            add_pokemon(150, 780, "MegaMewTwoY", PokeType::Psychic);
         }
      }
      if (InclusionFlag::MYSTERIOUS & inclusions) {
         add_pokemon(151, 600, "Mew", PokeType::Psychic);
      }
   }

   if (RegionsFlag::JOHTO & regions) {
      if (InclusionFlag::STARTERS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(152, 318, "Chikorita", PokeType::Grass);
            add_pokemon(153, 405, "Bayleef", PokeType::Grass);
         }
         add_pokemon(154, 525, "Meganium", PokeType::Grass);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(155, 309, "Cyndaquil", PokeType::Fire);
            add_pokemon(156, 405, "Quilava", PokeType::Fire);
         }
         add_pokemon(157, 534, "Typhlosion", PokeType::Fire);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(158, 314, "Totodile", PokeType::Water);
            add_pokemon(159, 405, "Croconaw", PokeType::Water);
         }
         add_pokemon(160, 530, "Feraligatr", PokeType::Water);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(161, 215, "Sentret", PokeType::Normal);
      }
      add_pokemon(162, 415, "Furret", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(163, 262, "Hoothoot", PokeType::Normal, PokeType::Flying);
      }
      add_pokemon(164, 452, "Noctowl", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(165, 265, "Ledyba", PokeType::Bug, PokeType::Flying);
      }
      add_pokemon(166, 390, "Ledian", PokeType::Bug, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(167, 250, "Spinarak", PokeType::Bug, PokeType::Poison);
      }
      add_pokemon(168, 400, "Ariados", PokeType::Bug, PokeType::Poison);
      add_pokemon(169, 535, "Crobat", PokeType::Poison, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(170, 330, "Chinchou", PokeType::Water, PokeType::Electric);
      }
      add_pokemon(171, 460, "Lanturn", PokeType::Water, PokeType::Electric);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::KANTO & regions)) {
         add_pokemon(172, 205, "Pichu", PokeType::Electric);
         add_pokemon(173, 218, "Cleffa", PokeType::Fairy);
         add_pokemon(174, 210, "Igglybuff", PokeType::Normal, PokeType::Fairy);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(175, 245, "Togepi", PokeType::Fairy);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(176, 405, "Togetic", PokeType::Fairy, PokeType::Flying);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(177, 320, "Natu", PokeType::Psychic, PokeType::Flying);
      }
      add_pokemon(178, 470, "Xatu", PokeType::Psychic, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(179, 280, "Mareep", PokeType::Electric);
         add_pokemon(180, 365, "Flaaffa", PokeType::Electric);
      }
      add_pokemon(181, 510, "Ampharos", PokeType::Electric);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(181, 610, "MegaAmpharos", PokeType::Electric, PokeType::Dragon);
      }
      add_pokemon(182, 490, "Bellossom", PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(183, 250, "Marill", PokeType::Water, PokeType::Fairy);
      }
      add_pokemon(184, 420, "Azumarill", PokeType::Water, PokeType::Fairy);
      add_pokemon(185, 410, "Sudowoodo", PokeType::Rock);
      add_pokemon(186, 500, "Politoed", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(187, 250, "Hoppip", PokeType::Grass, PokeType::Flying);
         add_pokemon(188, 340, "Skiploom", PokeType::Grass, PokeType::Flying);
      }
      add_pokemon(189, 460, "Jumpluff", PokeType::Grass, PokeType::Flying);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(190, 360, "Aipom", PokeType::Normal);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(191, 180, "Sunkern", PokeType::Grass);
      }
      add_pokemon(192, 425, "Sunflora", PokeType::Grass);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(193, 390, "Yanma", PokeType::Bug, PokeType::Flying);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(194, 210, "Wooper", PokeType::Water, PokeType::Ground);
      }
      add_pokemon(195, 430, "Quagsire", PokeType::Water, PokeType::Ground);
      add_pokemon(196, 525, "Espeon", PokeType::Psychic);
      add_pokemon(197, 525, "Umbreon", PokeType::Dark);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(198, 405, "Murkrow", PokeType::Dark, PokeType::Flying);
      }
      add_pokemon(199, 490, "Slowking", PokeType::Water, PokeType::Psychic);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(200, 435, "Misdreavus", PokeType::Ghost);
      }
      add_pokemon(201, 336, "Unown", PokeType::Psychic);
      add_pokemon(202, 405, "Wobbuffet", PokeType::Psychic);
      add_pokemon(203, 455, "Girafarig", PokeType::Normal, PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(204, 290, "Pineco", PokeType::Bug);
      }
      add_pokemon(205, 465, "Forretress", PokeType::Bug, PokeType::Steel);
      add_pokemon(206, 415, "Dunsparce", PokeType::Normal);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(207, 430, "Gligar", PokeType::Ground, PokeType::Flying);
      }
      add_pokemon(208, 510, "Steelix", PokeType::Steel, PokeType::Ground);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(208, 610, "MegaSteelix", PokeType::Steel, PokeType::Fairy);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(209, 300, "Snubbull", PokeType::Fairy);
      }
      add_pokemon(210, 450, "Granbull", PokeType::Fairy);
      add_pokemon(211, 440, "Qwilfish", PokeType::Water, PokeType::Poison);
      add_pokemon(212, 500, "Scizor", PokeType::Bug, PokeType::Steel);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(212, 600, "MegaScizor", PokeType::Bug, PokeType::Steel);
      }
      add_pokemon(213, 505, "Shuckle", PokeType::Bug, PokeType::Rock);
      add_pokemon(214, 500, "Heracross", PokeType::Bug, PokeType::Fighting);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(214, 600, "MegaHeracross", PokeType::Bug, PokeType::Fighting);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(215, 430, "Sneasel", PokeType::Dark, PokeType::Ice);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(216, 330, "Teddiursa", PokeType::Normal);
      }
      add_pokemon(217, 500, "Ursaring", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(218, 250, "Slugma", PokeType::Fire);
      }
      add_pokemon(219, 430, "Magcargo", PokeType::Fire, PokeType::Rock);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(220, 250, "Swinub", PokeType::Ice, PokeType::Ground);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(221, 450, "Piloswine", PokeType::Ice, PokeType::Ground);
      }
      add_pokemon(222, 410, "Corsola", PokeType::Water, PokeType::Rock);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(223, 300, "Remoraid", PokeType::Water);
      }
      add_pokemon(224, 480, "Octillery", PokeType::Water);
      add_pokemon(225, 330, "Delibird", PokeType::Ice, PokeType::Flying);
      add_pokemon(226, 485, "Mantine", PokeType::Water, PokeType::Flying);
      add_pokemon(227, 465, "Skarmory", PokeType::Steel, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(228, 330, "Houndour", PokeType::Dark, PokeType::Fire);
      }
      add_pokemon(229, 500, "Houndoom", PokeType::Dark, PokeType::Fire);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(229, 600, "MegaHoundoom", PokeType::Dark, PokeType::Fire);
      }
      add_pokemon(230, 540, "Kingdra", PokeType::Water, PokeType::Dragon);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(231, 330, "Phanpy", PokeType::Ground);
      }
      add_pokemon(232, 500, "Donphan", PokeType::Ground);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(233, 515, "Porygon2", PokeType::Normal);
      }
      add_pokemon(234, 465, "Stantler", PokeType::Normal);
      add_pokemon(235, 250, "Smeargle", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(236, 210, "Tyrogue", PokeType::Fighting);
      }
      add_pokemon(237, 455, "Hitmontop", PokeType::Fighting);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::KANTO & regions)) {
         add_pokemon(238, 305, "Smoochum", PokeType::Ice, PokeType::Psychic);
         add_pokemon(239, 360, "Elekid", PokeType::Electric);
         add_pokemon(240, 365, "Magby", PokeType::Fire);
      }
      add_pokemon(241, 490, "Miltank", PokeType::Normal);
      add_pokemon(242, 540, "Blissey", PokeType::Normal);
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(243, 580, "Raikou", PokeType::Electric);
         add_pokemon(244, 580, "Entei", PokeType::Fire);
         add_pokemon(245, 580, "Suicune", PokeType::Water);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(246, 300, "Larvitar", PokeType::Rock, PokeType::Dark);
         add_pokemon(247, 410, "Pupitar", PokeType::Rock, PokeType::Dark);
      }
      if (InclusionFlag::PSEUDOLEGENDARIES & inclusions) {
         add_pokemon(248, 600, "Tyranitar", PokeType::Rock, PokeType::Dark);
         if (InclusionFlag::MEGAS & inclusions) {
            add_pokemon(248, 700, "MegaTyranitar", PokeType::Rock, PokeType::Dark);
         }
      }
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(249, 680, "Lugia", PokeType::Psychic, PokeType::Flying);
         add_pokemon(250, 680, "Ho-Oh", PokeType::Fire, PokeType::Flying);
      }
      if (InclusionFlag::MYSTERIOUS & inclusions) {
         add_pokemon(251, 600, "Celebi", PokeType::Psychic, PokeType::Grass);
      }
   }

   if (RegionsFlag::HOENN & regions) {
      if (InclusionFlag::STARTERS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(252, 310, "Treecko", PokeType::Grass);
            add_pokemon(253, 405, "Grovyle", PokeType::Grass);
         }
         add_pokemon(254, 530, "Sceptile", PokeType::Grass);
         if (InclusionFlag::MEGAS & inclusions) {
            add_pokemon(254, 630, "MegaSceptile", PokeType::Grass, PokeType::Dragon);
         }
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(255, 310, "Torchic", PokeType::Fire);
            add_pokemon(256, 405, "Combusken", PokeType::Fire, PokeType::Fighting);
         }
         add_pokemon(257, 530, "Blanziken", PokeType::Fire, PokeType::Fighting);
         if (InclusionFlag::MEGAS & inclusions) {
            add_pokemon(257, 630, "MegaBlanziken", PokeType::Fire, PokeType::Fighting);
         }
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(258, 310, "Mudkip", PokeType::Water);
            add_pokemon(259, 405, "Marshtomp", PokeType::Water, PokeType::Ground);
         }
         add_pokemon(260, 535, "Swampert", PokeType::Water, PokeType::Ground);
         if (InclusionFlag::MEGAS & inclusions) {
            add_pokemon(260, 635, "MegaSwampert", PokeType::Water, PokeType::Ground);
         }
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(261, 220, "Poochyena", PokeType::Dark);
      }
      add_pokemon(262, 420, "Mightyena", PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(263, 240, "Zigzagoon", PokeType::Normal);
      }
      add_pokemon(264, 420, "Linoone", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(265, 195, "Wurmple", PokeType::Bug);
         add_pokemon(266, 205, "Silcoon", PokeType::Bug);
      }
      add_pokemon(267, 395, "Beautifly", PokeType::Bug, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(268, 205, "Cascoon", PokeType::Bug);
      }
      add_pokemon(269, 385, "Dustox", PokeType::Bug, PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(270, 220, "Lotad", PokeType::Water, PokeType::Grass);
         add_pokemon(271, 340, "Lombre", PokeType::Water, PokeType::Grass);
      }
      add_pokemon(272, 480, "Ludicolo", PokeType::Water, PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(273, 220, "Seedot", PokeType::Grass);
         add_pokemon(274, 340, "Nuzleaf", PokeType::Grass, PokeType::Dark);
      }
      add_pokemon(275, 480, "Shiftry", PokeType::Grass, PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(276, 270, "Taillow", PokeType::Normal, PokeType::Flying);
      }
      add_pokemon(277, 455, "Swellow", PokeType::Normal, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(278, 270, "Wingull", PokeType::Water, PokeType::Flying);
      }
      add_pokemon(279, 440, "Pelipper", PokeType::Water, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(280, 198, "Ralts", PokeType::Psychic, PokeType::Fairy);
         add_pokemon(281, 278, "Kirlia", PokeType::Psychic, PokeType::Fairy);
      }
      add_pokemon(282, 518, "Gardevoir", PokeType::Psychic, PokeType::Fairy);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(282, 618, "MegaGardevoir", PokeType::Psychic, PokeType::Fairy);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(283, 269, "Surskit", PokeType::Bug, PokeType::Water);
      }
      add_pokemon(284, 454, "Masquerain", PokeType::Bug, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(285, 295, "Shroomish", PokeType::Grass);
      }
      add_pokemon(286, 460, "Breloom", PokeType::Grass, PokeType::Fighting);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(287, 280, "Slakoth", PokeType::Normal);
         add_pokemon(288, 440, "Vigoroth", PokeType::Normal);
      }
      add_pokemon(289, 670, "Slaking", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(290, 266, "Nincada", PokeType::Bug, PokeType::Ground);
      }
      add_pokemon(291, 456, "Ninjask", PokeType::Bug, PokeType::Flying);
      add_pokemon(292, 236, "Shedinja", PokeType::Bug, PokeType::Ghost);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(293, 240, "Whismur", PokeType::Normal);
         add_pokemon(294, 360, "Loudred", PokeType::Normal);
      }
      add_pokemon(295, 490, "Exploud", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(296, 237, "Makuhita", PokeType::Fighting);
      }
      add_pokemon(297, 474, "Hariyama", PokeType::Fighting);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(298, 190, "Azurill", PokeType::Normal, PokeType::Fairy);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(299, 375, "Nosepass", PokeType::Rock);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(300, 260, "Skitty", PokeType::Normal);
      }
      add_pokemon(301, 400, "Delcatty", PokeType::Normal);
      add_pokemon(302, 380, "Sableye", PokeType::Dark, PokeType::Ghost);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(302, 480, "MegaSableye", PokeType::Dark, PokeType::Ghost);
      }
      add_pokemon(303, 380, "Mawile", PokeType::Steel, PokeType::Fairy);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(303, 480, "MegaMawile", PokeType::Steel, PokeType::Fairy);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(304, 330, "Aron", PokeType::Steel, PokeType::Rock);
         add_pokemon(305, 430, "Lairon", PokeType::Steel, PokeType::Rock);
      }
      add_pokemon(306, 530, "Aggron", PokeType::Steel, PokeType::Rock);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(306, 630, "MegaAggron", PokeType::Steel);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(307, 280, "Meditite", PokeType::Fighting, PokeType::Psychic);
      }
      add_pokemon(308, 410, "Medicham", PokeType::Fighting, PokeType::Psychic);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(308, 510, "MegaMedicham", PokeType::Fighting, PokeType::Psychic);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(309, 295, "Electrike", PokeType::Electric);
      }
      add_pokemon(310, 475, "Manectric", PokeType::Electric);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(310, 575, "MegaManectirc", PokeType::Electric);
      }
      add_pokemon(311, 405, "Pluse", PokeType::Electric);
      add_pokemon(312, 405, "Minun", PokeType::Electric);
      add_pokemon(313, 430, "Volbeat", PokeType::Bug);
      add_pokemon(314, 430, "Illumise", PokeType::Bug);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(315, 400, "Roselia", PokeType::Grass, PokeType::Poison);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(316, 302, "Gulpin", PokeType::Poison);
      }
      add_pokemon(317, 467, "Swalot", PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(318, 305, "Carvanha", PokeType::Water, PokeType::Dark);
      }
      add_pokemon(319, 460, "Sharpedo", PokeType::Water, PokeType::Dark);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(319, 560, "MegaSharpedo", PokeType::Water, PokeType::Dark);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(320, 400, "Wailmer", PokeType::Water);
      }
      add_pokemon(321, 500, "Wailord", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(322, 305, "Numel", PokeType::Fire, PokeType::Ground);
      }
      add_pokemon(323, 460, "Camerupt", PokeType::Fire, PokeType::Ground);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(323, 560, "MegaCamerupt", PokeType::Fire, PokeType::Ground);
      }
      add_pokemon(324, 470, "Torkoal", PokeType::Fire);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(325, 330, "Spoink", PokeType::Psychic);
      }
      add_pokemon(326, 470, "Grumpig", PokeType::Psychic);
      add_pokemon(327, 360, "Spinda", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(328, 290, "Trapinch", PokeType::Ground);
         add_pokemon(329, 340, "Vibrava", PokeType::Ground, PokeType::Dragon);
      }
      add_pokemon(330, 520, "Flygon", PokeType::Ground, PokeType::Dragon);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(331, 335, "Cacnea", PokeType::Grass);
      }
      add_pokemon(332, 475, "Cacturne", PokeType::Grass, PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(333, 310, "Swablu", PokeType::Normal, PokeType::Flying);
      }
      add_pokemon(334, 490, "Altaria", PokeType::Dragon, PokeType::Flying);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(334, 590, "MegaAltaria", PokeType::Dragon, PokeType::Fairy);
      }
      add_pokemon(335, 458, "Zangoose", PokeType::Normal);
      add_pokemon(336, 458, "Seviper", PokeType::Poison);
      add_pokemon(337, 460, "Lunatone", PokeType::Rock, PokeType::Psychic);
      add_pokemon(338, 460, "Solrock", PokeType::Rock, PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(339, 288, "Barboach", PokeType::Water, PokeType::Ground);
      }
      add_pokemon(340, 468, "Whiscash", PokeType::Water, PokeType::Ground);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(341, 308, "Corphish", PokeType::Water);
      }
      add_pokemon(342, 468, "Crawdaunt", PokeType::Water, PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(343, 300, "Baltoy", PokeType::Ground, PokeType::Psychic);
      }
      add_pokemon(344, 500, "Claydol", PokeType::Ground, PokeType::Psychic);
      if (InclusionFlag::FOSSILS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(345, 355, "Lileep", PokeType::Rock, PokeType::Grass);
         }
         add_pokemon(346, 495, "Cradily", PokeType::Rock, PokeType::Grass);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(347, 355, "Anorith", PokeType::Rock, PokeType::Bug);
         }
         add_pokemon(348, 495, "Armaldo", PokeType::Rock, PokeType::Bug);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(349, 200, "Feebas", PokeType::Water);
      }
      add_pokemon(350, 540, "Milotic", PokeType::Water);
      add_pokemon(351, 420, "Castform", PokeType::Normal);
      add_pokemon(352, 440, "Keckleon", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(353, 295, "Shuppet", PokeType::Ghost);
      }
      add_pokemon(354, 455, "Banette", PokeType::Ghost);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(354, 555, "MegaBanette", PokeType::Ghost);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(355, 295, "Duskull", PokeType::Ghost);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(356, 455, "Dusclops", PokeType::Ghost);
      }
      add_pokemon(357, 460, "Tropius", PokeType::Grass, PokeType::Flying);
      add_pokemon(358, 455, "Chimecho", PokeType::Psychic);
      add_pokemon(359, 465, "Absol", PokeType::Dark);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(359, 565, "MegaAbsol", PokeType::Dark);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(360, 260, "Wynaut", PokeType::Psychic);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(361, 300, "Snorunt", PokeType::Ice);
      }
      add_pokemon(362, 480, "Glalie", PokeType::Ice);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(362, 580, "MegaGlaliie", PokeType::Ice);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(363, 290, "Spheal", PokeType::Ice, PokeType::Water);
         add_pokemon(364, 410, "Sealeo", PokeType::Ice, PokeType::Water);
      }
      add_pokemon(365, 530, "Walrein", PokeType::Ice, PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(366, 345, "Clamperl", PokeType::Water);
      }
      add_pokemon(367, 485, "Huntail", PokeType::Water);
      add_pokemon(368, 485, "Gorebyss", PokeType::Water);
      add_pokemon(369, 485, "Relicanth", PokeType::Water, PokeType::Rock);
      add_pokemon(370, 330, "Luvdisc", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(371, 300, "Bagon", PokeType::Dragon);
         add_pokemon(372, 420, "Shelgon", PokeType::Dragon);
      }
      if (InclusionFlag::PSEUDOLEGENDARIES & inclusions) {
         add_pokemon(373, 600, "Salamence", PokeType::Dragon, PokeType::Flying);
         if (InclusionFlag::MEGAS & inclusions) {
            add_pokemon(373, 700, "MegaSalamence", PokeType::Dragon, PokeType::Flying);
         }
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(374, 300, "Beldum", PokeType::Steel, PokeType::Psychic);
         add_pokemon(375, 420, "Metang", PokeType::Steel, PokeType::Psychic);
      }
      if (InclusionFlag::PSEUDOLEGENDARIES & inclusions) {
         add_pokemon(376, 600, "Metagross", PokeType::Steel, PokeType::Psychic);
         if (InclusionFlag::MEGAS & inclusions) {
            add_pokemon(376, 700, "MegaMetagross", PokeType::Steel, PokeType::Psychic);
         }
      }
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(377, 580, "Regirock", PokeType::Rock);
         add_pokemon(378, 580, "Regice", PokeType::Ice);
         add_pokemon(379, 580, "Registeel", PokeType::Steel);
         add_pokemon(380, 600, "Latias", PokeType::Dragon, PokeType::Psychic);
         if (InclusionFlag::MEGAS & inclusions) {
            add_pokemon(380, 700, "MegaLatias", PokeType::Dragon, PokeType::Psychic);
         }
         add_pokemon(381, 600, "Latios", PokeType::Dragon, PokeType::Psychic);
         if (InclusionFlag::MEGAS & inclusions) {
            add_pokemon(381, 700, "MegaLatios", PokeType::Dragon, PokeType::Psychic);
         }
         add_pokemon(382, 670, "Kyogre", PokeType::Water);
         add_pokemon(382, 770, "PrimalKyogre", PokeType::Water);
         add_pokemon(383, 670, "Groudon", PokeType::Ground);
         add_pokemon(383, 770, "PrimalGroudon", PokeType::Ground, PokeType::Fire);
         add_pokemon(384, 680, "Rayquaza", PokeType::Dragon, PokeType::Flying);
         if (InclusionFlag::MEGAS & inclusions) {
            add_pokemon(384, 780, "MegaRayquaza", PokeType::Dragon, PokeType::Flying);
         }
      }
      if (InclusionFlag::MYSTERIOUS & inclusions) {
         add_pokemon(385, 600, "Jirachi", PokeType::Steel, PokeType::Psychic);
         add_pokemon(386, 600, "Deoxys", PokeType::Psychic);
      }
   }

   if (RegionsFlag::SINNOH & regions) {
      if (InclusionFlag::STARTERS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(387, 318, "Turtwig", PokeType::Grass);
            add_pokemon(388, 405, "Grotle", PokeType::Grass);
         }
         add_pokemon(389, 525, "Torterra", PokeType::Grass, PokeType::Ground);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(390, 309, "Chimchar", PokeType::Fire);
            add_pokemon(391, 405, "Monferno", PokeType::Fire, PokeType::Fighting);
         }
         add_pokemon(392, 534, "Infernape", PokeType::Fire, PokeType::Fighting);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(393, 314, "Piplup", PokeType::Water);
            add_pokemon(394, 405, "Prinplup", PokeType::Water);
         }
         add_pokemon(395, 530, "Empoleon", PokeType::Water, PokeType::Steel);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(396, 245, "Starly", PokeType::Normal, PokeType::Flying);
         add_pokemon(397, 340, "Staravia", PokeType::Normal, PokeType::Flying);
      }
      add_pokemon(398, 485, "Staraptor", PokeType::Normal, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(399, 250, "Bidoof", PokeType::Normal);
      }
      add_pokemon(400, 410, "Bibarel", PokeType::Normal, PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(401, 194, "Kricketot", PokeType::Bug);
      }
      add_pokemon(402, 384, "Kricketune", PokeType::Bug);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(403, 263, "Shinx", PokeType::Electric);
         add_pokemon(404, 363, "Luxio", PokeType::Electric);
      }
      add_pokemon(405, 523, "Luxray", PokeType::Electric);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(406, 280, "Budew", PokeType::Grass, PokeType::Poison);
      }
      add_pokemon(407, 515, "Roserade", PokeType::Grass, PokeType::Poison);
      if (InclusionFlag::FOSSILS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(408, 350, "Cranidos", PokeType::Rock);
         }
         add_pokemon(409, 495, "Rampardos", PokeType::Rock);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(410, 350, "Shieldon", PokeType::Rock, PokeType::Steel);
         }
         add_pokemon(411, 495, "Bastiadon", PokeType::Rock, PokeType::Steel);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(412, 224, "Burmy", PokeType::Bug);
      }
      add_pokemon(413, 424, "Wormadam_plant", PokeType::Bug, PokeType::Grass);
      add_pokemon(413, 424, "Wormadam_sandy", PokeType::Bug, PokeType::Ground);
      add_pokemon(413, 424, "Wormadam_trash", PokeType::Bug, PokeType::Steel);
      add_pokemon(414, 424, "Mothim", PokeType::Bug, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(415, 244, "Combee", PokeType::Bug, PokeType::Flying);
      }
      add_pokemon(416, 474, "Vespiquen", PokeType::Bug, PokeType::Flying);
      add_pokemon(417, 405, "Pachirisu", PokeType::Electric);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(418, 330, "Buizel", PokeType::Water);
      }
      add_pokemon(419, 495, "Floatzel", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(420, 275, "Cherubi", PokeType::Grass);
      }
      add_pokemon(421, 450, "Cherrim", PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(422, 325, "Shellos", PokeType::Water);
      }
      add_pokemon(423, 475, "Gastrodon", PokeType::Water, PokeType::Ground);
      add_pokemon(424, 482, "Ambipom", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(425, 348, "Drifloon", PokeType::Ghost, PokeType::Flying);
      }
      add_pokemon(426, 498, "Drifblim", PokeType::Ghost, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(427, 350, "Buneary", PokeType::Normal);
      }
      add_pokemon(428, 480, "Lopunny", PokeType::Normal, PokeType::Fighting);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(428, 580, "MegaLopunny", PokeType::Normal, PokeType::Fighting);
      }
      add_pokemon(429, 495, "Mismagius", PokeType::Ghost);
      add_pokemon(430, 505, "Honchkrow", PokeType::Dark, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(431, 310, "Glameow", PokeType::Normal);
      }
      add_pokemon(432, 452, "Perugly", PokeType::Normal);

      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::HOENN & regions)) {
         add_pokemon(433, 285, "Chingling", PokeType::Psychic);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(434, 329, "Stunky", PokeType::Poison, PokeType::Dark);
      }
      add_pokemon(435, 479, "Skuntank", PokeType::Poison, PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(436, 300, "Bronzor", PokeType::Steel, PokeType::Psychic);
      }
      add_pokemon(437, 500, "Bronzong", PokeType::Steel, PokeType::Psychic);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(438, 290, "Bonsly", PokeType::Rock);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::KANTO & regions)) {
         add_pokemon(439, 310, "MimeJr.", PokeType::Psychic, PokeType::Fairy);
         add_pokemon(440, 220, "Happiny", PokeType::Normal);
      }
      add_pokemon(441, 411, "Chatot", PokeType::Normal, PokeType::Flying);
      add_pokemon(442, 485, "Spiritomb", PokeType::Ghost, PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(443, 300, "Gible", PokeType::Dragon, PokeType::Ground);
         add_pokemon(444, 410, "Babite", PokeType::Dragon, PokeType::Ground);
      }
      if (InclusionFlag::PSEUDOLEGENDARIES & inclusions) {
         add_pokemon(445, 600, "Garchomp", PokeType::Dragon, PokeType::Ground);
         if (InclusionFlag::MEGAS & inclusions) {
            add_pokemon(445, 700, "MegaGarchomp", PokeType::Dragon, PokeType::Ground);
         }
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::KANTO & regions)) {
         add_pokemon(446, 390, "Munchlax", PokeType::Normal);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(447, 285, "Riolu", PokeType::Fighting);
      }
      add_pokemon(448, 525, "Lucario", PokeType::Fighting, PokeType::Steel);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(448, 625, "MegaLucario", PokeType::Fighting, PokeType::Steel);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(449, 330, "Hippopotas", PokeType::Ground);
      }
      add_pokemon(450, 525, "Hippowdon", PokeType::Ground);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(451, 330, "Skorupi", PokeType::Poison, PokeType::Bug);
      }
      add_pokemon(452, 500, "Drapion", PokeType::Poison, PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(453, 300, "Croagunk", PokeType::Poison, PokeType::Fighting);
      }
      add_pokemon(454, 490, "Toxicroak", PokeType::Poison, PokeType::Fighting);
      add_pokemon(455, 454, "Carnivine", PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(456, 330, "Finneon", PokeType::Water);
      }
      add_pokemon(457, 460, "Lumineon", PokeType::Water);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(458, 345, "Mantyke", PokeType::Water, PokeType::Flying);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(459, 334, "Snover", PokeType::Water, PokeType::Ice);
      }
      add_pokemon(460, 494, "Abomasnow", PokeType::Grass, PokeType::Ice);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(460, 594, "MegaAbomasnow", PokeType::Grass, PokeType::Ice);
      }
      add_pokemon(461, 510, "Weavile", PokeType::Dark, PokeType::Ice);
      add_pokemon(462, 535, "Magnezone", PokeType::Electric, PokeType::Steel);
      add_pokemon(463, 515, "Lickilicky", PokeType::Normal);
      add_pokemon(464, 535, "Rhyperior", PokeType::Ground, PokeType::Rock);
      add_pokemon(465, 535, "Tangrowth", PokeType::Grass);
      add_pokemon(466, 540, "Electivire", PokeType::Electric);
      add_pokemon(467, 540, "Magmortar", PokeType::Fire);
      add_pokemon(468, 545, "Togekiss", PokeType::Fairy, PokeType::Flying);
      add_pokemon(469, 515, "Yanmega", PokeType::Bug, PokeType::Flying);
      add_pokemon(470, 525, "Leafeon", PokeType::Grass);
      add_pokemon(471, 525, "Glaceon", PokeType::Ice);
      add_pokemon(472, 510, "Gliscor", PokeType::Ground, PokeType::Flying);
      add_pokemon(473, 530, "Mamoswine", PokeType::Ice, PokeType::Ground);
      add_pokemon(474, 535, "Porygon-Z", PokeType::Normal);
      add_pokemon(475, 518, "Gallade", PokeType::Psychic, PokeType::Fighting);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(475, 618, "MegaGallade", PokeType::Psychic, PokeType::Fighting);
      }
      add_pokemon(476, 525, "Probopass", PokeType::Rock, PokeType::Steel);
      add_pokemon(477, 525, "Dusknoir", PokeType::Ghost);
      add_pokemon(478, 480, "Froslass", PokeType::Ice, PokeType::Ghost);
      add_pokemon(479, 440, "Rotom", PokeType::Electric, PokeType::Ghost);
      add_pokemon(479, 520, "HeatRotom", PokeType::Electric, PokeType::Fire);
      add_pokemon(479, 520, "WashRotom", PokeType::Electric, PokeType::Water);
      add_pokemon(479, 520, "FrostRotom", PokeType::Electric, PokeType::Ice);
      add_pokemon(479, 520, "FanRotom", PokeType::Electric, PokeType::Flying);
      add_pokemon(479, 520, "MowRotom", PokeType::Electric, PokeType::Grass);
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(480, 580, "Uxie", PokeType::Psychic);
         add_pokemon(481, 580, "Mesprit", PokeType::Psychic);
         add_pokemon(482, 580, "Azelf", PokeType::Psychic);
         add_pokemon(483, 680, "Dialga", PokeType::Steel, PokeType::Dragon);
         add_pokemon(484, 680, "Palkia", PokeType::Water, PokeType::Dragon);
         add_pokemon(485, 600, "Heatran", PokeType::Fire, PokeType::Steel);
         add_pokemon(486, 670, "Regigigas", PokeType::Normal);
         add_pokemon(487, 680, "Giratina", PokeType::Ghost, PokeType::Dragon);
         add_pokemon(488, 600, "Cresselia", PokeType::Psychic);
      }
      if (InclusionFlag::MYSTERIOUS & inclusions) {
         add_pokemon(489, 480, "Phione", PokeType::Water);
         add_pokemon(490, 600, "Manaphy", PokeType::Water);
         add_pokemon(491, 600, "Darkrai", PokeType::Dark);
         add_pokemon(492, 600, "Shaymin_land", PokeType::Grass);
         add_pokemon(492, 600, "Shaymin_sky", PokeType::Grass, PokeType::Flying);
         add_pokemon(493, 720, "Arceus_normal", PokeType::Normal);
         add_pokemon(493, 720, "Arceus_fighting", PokeType::Fighting);
         add_pokemon(493, 720, "Arceus_flying", PokeType::Flying);
         add_pokemon(493, 720, "Arceus_poison", PokeType::Poison);
         add_pokemon(493, 720, "Arceus_ground", PokeType::Ground);
         add_pokemon(493, 720, "Arceus_rock", PokeType::Rock);
         add_pokemon(493, 720, "Arceus_bug", PokeType::Bug);
         add_pokemon(493, 720, "Arceus_ghost", PokeType::Ghost);
         add_pokemon(493, 720, "Arceus_steel", PokeType::Steel);
         add_pokemon(493, 720, "Arceus_fire", PokeType::Fire);
         add_pokemon(493, 720, "Arceus_water", PokeType::Water);
         add_pokemon(493, 720, "Arceus_grass", PokeType::Grass);
         add_pokemon(493, 720, "Arceus_electric", PokeType::Electric);
         add_pokemon(493, 720, "Arceus_psychic", PokeType::Psychic);
         add_pokemon(493, 720, "Arceus_ice", PokeType::Ice);
         add_pokemon(493, 720, "Arceus_dragon", PokeType::Dragon);
         add_pokemon(493, 720, "Arceus_dark", PokeType::Dark);
         add_pokemon(493, 720, "Arceus_fairy", PokeType::Fairy);
      }
   }

   if (RegionsFlag::ALOLA & regions) {
      if (InclusionFlag::MYSTERIOUS & inclusions) {
         add_pokemon(494, 600, "Victini", PokeType::Psychic, PokeType::Fire);
      }
      if (InclusionFlag::STARTERS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(495, 308, "Snivy", PokeType::Grass);
            add_pokemon(496, 413, "Servine", PokeType::Grass);
         }
         add_pokemon(497, 528, "Serperior", PokeType::Grass);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(498, 308, "Tepig", PokeType::Fire);
            add_pokemon(499, 418, "Pignite", PokeType::Fire, PokeType::Fighting);
         }
         add_pokemon(500, 528, "Emboar", PokeType::Fire, PokeType::Fighting);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(501, 308, "Oshawott", PokeType::Water);
            add_pokemon(502, 413, "Dewott", PokeType::Water);
         }
         add_pokemon(503, 528, "Samurott", PokeType::Water);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(504, 255, "Patrat", PokeType::Normal);
      }
      add_pokemon(505, 420, "Watchog", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(506, 275, "Lillipup", PokeType::Normal);
         add_pokemon(507, 370, "Herdier", PokeType::Normal);
      }
      add_pokemon(508, 500, "Stoutland", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(509, 281, "Purrloin", PokeType::Dark);
      }
      add_pokemon(510, 446, "Liepard", PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(511, 316, "Pansage", PokeType::Grass);
      }
      add_pokemon(512, 498, "Simisage", PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(513, 316, "Pansear", PokeType::Fire);
      }
      add_pokemon(514, 498, "Simisear", PokeType::Fire);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(515, 316, "Panpour", PokeType::Water);
      }
      add_pokemon(516, 498, "Simipour", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(517, 292, "Munna", PokeType::Psychic);
      }
      add_pokemon(518, 487, "Musharna", PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(519, 264, "Pidove", PokeType::Normal, PokeType::Flying);
         add_pokemon(520, 358, "Tranquill", PokeType::Normal, PokeType::Flying);
      }
      add_pokemon(521, 488, "Unfezant", PokeType::Normal, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(522, 295, "Blitzle", PokeType::Electric);
      }
      add_pokemon(523, 497, "Zebstrika", PokeType::Electric);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(524, 280, "Roggenrola", PokeType::Rock);
         add_pokemon(525, 390, "Boldore", PokeType::Rock);
      }
      add_pokemon(526, 515, "Gigalith", PokeType::Rock);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(527, 323, "Woobat", PokeType::Psychic, PokeType::Flying);
      }
      add_pokemon(528, 425, "Swoobat", PokeType::Psychic, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(529, 328, "Drilbur", PokeType::Ground);
      }
      add_pokemon(530, 508, "Excadrill", PokeType::Ground, PokeType::Steel);
      add_pokemon(531, 445, "Audino", PokeType::Normal);
      if (InclusionFlag::MEGAS & inclusions) {
         add_pokemon(531, 555, "MegaAudino", PokeType::Normal, PokeType::Fairy);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(532, 305, "Timburr", PokeType::Fighting);
         add_pokemon(533, 405, "Gurdurr", PokeType::Fighting);
      }
      add_pokemon(534, 505, "Conkeldurr", PokeType::Fighting);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(535, 294, "Tympole", PokeType::Water);
         add_pokemon(536, 384, "Palpitoad", PokeType::Water, PokeType::Ground);
      }
      add_pokemon(537, 509, "Seismitoad", PokeType::Water, PokeType::Ground);
      add_pokemon(538, 465, "Throh", PokeType::Fighting);
      add_pokemon(539, 465, "Sawk", PokeType::Fighting);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(540, 310, "Sewaddle", PokeType::Bug, PokeType::Grass);
         add_pokemon(541, 380, "Swadloon", PokeType::Bug, PokeType::Grass);
      }
      add_pokemon(542, 500, "Leavanny", PokeType::Bug, PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(543, 260, "Venipede", PokeType::Bug, PokeType::Poison);
         add_pokemon(544, 360, "Whirlipede", PokeType::Bug, PokeType::Poison);
      }
      add_pokemon(545, 485, "Scolipede", PokeType::Bug, PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(546, 280, "Cottonee", PokeType::Grass, PokeType::Fairy);
      }
      add_pokemon(547, 480, "Whimsicott", PokeType::Grass, PokeType::Fairy);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(548, 280, "Petilil", PokeType::Grass);
      }
      add_pokemon(549, 480, "Lilligant", PokeType::Grass);
      add_pokemon(550, 460, "Basculin", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(551, 292, "Sandile", PokeType::Ground, PokeType::Dark);
         add_pokemon(552, 351, "Krokorok", PokeType::Ground, PokeType::Dark);
      }
      add_pokemon(553, 519, "Krookodile", PokeType::Ground, PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(554, 315, "Darumaka", PokeType::Fire);
      }
      add_pokemon(555, 480, "Darmanitan", PokeType::Fire);
      add_pokemon(555, 540, "Darmanitan_zen", PokeType::Fire, PokeType::Psychic);
      add_pokemon(556, 461, "Maractus", PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(557, 325, "Dwebble", PokeType::Bug, PokeType::Rock);
      }
      add_pokemon(558, 485, "Crustle", PokeType::Bug, PokeType::Rock);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(559, 348, "Scraggy", PokeType::Dark, PokeType::Fighting);
      }
      add_pokemon(560, 488, "Scrafty", PokeType::Dark, PokeType::Fighting);
      add_pokemon(561, 490, "Sigilyph", PokeType::Psychic, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(562, 303, "Yamask", PokeType::Ghost);
      }
      add_pokemon(563, 483, "Cofagrigus", PokeType::Ghost);
      if (InclusionFlag::FOSSILS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(564, 355, "Tirtouga", PokeType::Rock, PokeType::Water);
         }
         add_pokemon(565, 495, "Carracosta", PokeType::Rock, PokeType::Water);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(566, 401, "Archen", PokeType::Rock, PokeType::Flying);
         }
         add_pokemon(567, 567, "Archeops", PokeType::Rock, PokeType::Flying);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(568, 329, "Trubbish", PokeType::Poison);
      }
      add_pokemon(569, 474, "Garbodor", PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(570, 330, "Zorua", PokeType::Dark);
      }
      add_pokemon(571, 510, "Zoroark", PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(572, 300, "Minccino", PokeType::Normal);
      }
      add_pokemon(573, 470, "Cinccino", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(574, 290, "Gothita", PokeType::Psychic);
         add_pokemon(575, 390, "Gothorita", PokeType::Psychic);
      }
      add_pokemon(576, 490, "Gothitelle", PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(577, 290, "Solosis", PokeType::Psychic);
         add_pokemon(578, 370, "Duosion", PokeType::Psychic);
      }
      add_pokemon(579, 490, "Reuniclus", PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(580, 305, "Ducklett", PokeType::Water, PokeType::Flying);
      }
      add_pokemon(581, 473, "Swanna", PokeType::Water, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(582, 305, "Vanillite", PokeType::Ice);
         add_pokemon(583, 395, "Vanillish", PokeType::Ice);
      }
      add_pokemon(584, 535, "Vanilluxe", PokeType::Ice);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(585, 335, "Deerling", PokeType::Normal, PokeType::Grass);
      }
      add_pokemon(586, 475, "Sawsbuck", PokeType::Normal, PokeType::Grass);
      add_pokemon(587, 428, "Emolga", PokeType::Electric, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(588, 315, "Karrablast", PokeType::Bug);
      }
      add_pokemon(589, 495, "Escavalier", PokeType::Bug, PokeType::Steel);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(590, 294, "Foongus", PokeType::Grass, PokeType::Poison);
      }
      add_pokemon(591, 464, "Amoonguss", PokeType::Grass, PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(592, 335, "Frillish", PokeType::Water, PokeType::Ghost);
      }
      add_pokemon(593, 480, "Jellicent", PokeType::Water, PokeType::Ghost);
      add_pokemon(594, 470, "Alomomola", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(595, 319, "Joltik", PokeType::Bug, PokeType::Electric);
      }
      add_pokemon(596, 472, "Galvantula", PokeType::Bug, PokeType::Electric);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(597, 305, "Ferroseed", PokeType::Grass, PokeType::Steel);
      }
      add_pokemon(598, 489, "Ferrothorn", PokeType::Grass, PokeType::Steel);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(599, 300, "Klink", PokeType::Steel);
         add_pokemon(600, 440, "Klang", PokeType::Steel);
      }
      add_pokemon(601, 520, "Klinklang", PokeType::Steel);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(602, 275, "Tynamo", PokeType::Electric);
         add_pokemon(603, 405, "Eelektrik", PokeType::Electric);
      }
      add_pokemon(604, 515, "Eelektross", PokeType::Electric);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(605, 335, "Elgyem", PokeType::Psychic);
      }
      add_pokemon(606, 485, "Beheeyem", PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(607, 275, "Litwick", PokeType::Ghost, PokeType::Fire);
         add_pokemon(608, 370, "Lampent", PokeType::Ghost, PokeType::Fire);
      }
      add_pokemon(609, 520, "Chandelure", PokeType::Ghost, PokeType::Fire);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(610, 320, "Axew", PokeType::Dragon);
         add_pokemon(611, 410, "Fraxure", PokeType::Dragon);
      }
      add_pokemon(612, 540, "Haxorus", PokeType::Dragon);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(613, 305, "Cubchoo", PokeType::Ice);
      }
      add_pokemon(614, 505, "Beartic", PokeType::Ice);
      add_pokemon(615, 515, "Cryogonal", PokeType::Ice);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(616, 305, "Shelmet", PokeType::Bug);
      }
      add_pokemon(617, 495, "Accelgor", PokeType::Bug);
      add_pokemon(618, 471, "Stunfisk", PokeType::Ground, PokeType::Electric);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(619, 350, "Mienfoo", PokeType::Fighting);
      }
      add_pokemon(620, 510, "Mienshao", PokeType::Fighting);
      add_pokemon(621, 485, "Druddigon", PokeType::Dragon);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(622, 303, "Golett", PokeType::Ground, PokeType::Ghost);
      }
      add_pokemon(623, 483, "Golurk", PokeType::Ground, PokeType::Ghost);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(624, 340, "Pawniard", PokeType::Dark, PokeType::Steel);
      }
      add_pokemon(625, 490, "Bisharp", PokeType::Dark, PokeType::Steel);
      add_pokemon(626, 490, "Bouffalant", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(627, 350, "Rufflet", PokeType::Normal, PokeType::Flying);
      }
      add_pokemon(628, 510, "Braviary", PokeType::Normal, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(629, 370, "Vullaby", PokeType::Dark, PokeType::Flying);
      }
      add_pokemon(630, 510, "Mandibuzz", PokeType::Dark, PokeType::Flying);
      add_pokemon(631, 484, "Heatmor", PokeType::Fire);
      add_pokemon(632, 484, "Durant", PokeType::Bug, PokeType::Steel);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(633, 300, "Deino", PokeType::Dark, PokeType::Dragon);
         add_pokemon(634, 420, "Zweilous", PokeType::Dark, PokeType::Dragon);
      }
      if (InclusionFlag::PSEUDOLEGENDARIES & inclusions) {
         add_pokemon(635, 600, "Hydreigon", PokeType::Dark, PokeType::Dragon);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(636, 360, "Larvesta", PokeType::Bug, PokeType::Fire);
      }
      add_pokemon(637, 550, "Volcarona", PokeType::Bug, PokeType::Fire);
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(638, 580, "Cobalion", PokeType::Steel, PokeType::Fighting);
         add_pokemon(639, 580, "Terrakion", PokeType::Rock, PokeType::Fighting);
         add_pokemon(640, 580, "Virizion", PokeType::Grass, PokeType::Fighting);
         add_pokemon(641, 580, "Tornadus", PokeType::Flying);
         add_pokemon(642, 580, "Thundurus", PokeType::Electric, PokeType::Flying);
         add_pokemon(643, 680, "Reshiram", PokeType::Dragon, PokeType::Fire);
         add_pokemon(644, 680, "Zekrom", PokeType::Dragon, PokeType::Electric);
         add_pokemon(645, 600, "Landorus", PokeType::Ground, PokeType::Flying);
         add_pokemon(646, 660, "Kyurem", PokeType::Dragon, PokeType::Ice);
         add_pokemon(646, 700, "KyuremWhite", PokeType::Dragon, PokeType::Ice);
         add_pokemon(646, 700, "KyuremBlack", PokeType::Dragon, PokeType::Ice);
      }
      if (InclusionFlag::MYSTERIOUS & inclusions) {
         add_pokemon(647, 580, "Keldeo", PokeType::Water, PokeType::Fighting);
         add_pokemon(648, 600, "Meloetta_psychic", PokeType::Normal, PokeType::Psychic);
         add_pokemon(648, 600, "Meloetta_fighting", PokeType::Normal, PokeType::Fighting);
         add_pokemon(649, 600, "Genesect", PokeType::Bug, PokeType::Steel);
      }
   }

   if (RegionsFlag::KALOS & regions) {
      if (InclusionFlag::STARTERS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(650, 313, "Chespin", PokeType::Grass);
            add_pokemon(651, 405, "Quilladin", PokeType::Grass);
         }
         add_pokemon(652, 530, "Chesnaught", PokeType::Grass, PokeType::Fighting);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(653, 307, "Fennekin", PokeType::Fire);
            add_pokemon(654, 409, "Braixen", PokeType::Fire);
         }
         add_pokemon(655, 534, "Delphox", PokeType::Fire, PokeType::Psychic);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(656, 314, "Froakie", PokeType::Water);
            add_pokemon(657, 405, "Frogadier", PokeType::Water);
         }
         add_pokemon(658, 530, "Greninja", PokeType::Water, PokeType::Dark);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(659, 237, "Bunnelby", PokeType::Normal);
      }
      add_pokemon(660, 423, "Diggersby", PokeType::Normal, PokeType::Ground);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(661, 278, "Fletchling", PokeType::Normal, PokeType::Flying);
         add_pokemon(662, 382, "Fletchinder", PokeType::Fire, PokeType::Flying);
      }
      add_pokemon(663, 499, "Talonflame", PokeType::Fire, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(664, 200, "Scatterbug", PokeType::Bug);
         add_pokemon(665, 213, "Spewpa", PokeType::Bug);
      }
      add_pokemon(666, 411, "Vivillon", PokeType::Bug, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(667, 369, "Litleo", PokeType::Fire, PokeType::Normal);
      }
      add_pokemon(668, 507, "Pyroar", PokeType::Fire, PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(669, 303, "Flabebe", PokeType::Fairy);
         add_pokemon(670, 371, "Floette", PokeType::Fairy);
      }
      add_pokemon(671, 552, "Florges", PokeType::Fairy);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(672, 350, "Skiddo", PokeType::Grass);
      }
      add_pokemon(673, 531, "Gogoat", PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(674, 348, "Pancham", PokeType::Fighting);
      }
      add_pokemon(675, 495, "Pangoro", PokeType::Fighting, PokeType::Dark);
      add_pokemon(676, 472, "Furfrou", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(677, 355, "Espurr", PokeType::Psychic);
      }
      add_pokemon(678, 466, "Meowstic", PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(679, 325, "Honedge", PokeType::Steel, PokeType::Ghost);
         add_pokemon(680, 448, "Doublade", PokeType::Steel, PokeType::Ghost);
      }
      add_pokemon(681, 520, "Aegislash", PokeType::Steel, PokeType::Ghost);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(682, 341, "Spritzee", PokeType::Fairy);
      }
      add_pokemon(683, 462, "Aromatisse", PokeType::Fairy);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(684, 341, "Swirlix", PokeType::Fairy);
      }
      add_pokemon(685, 480, "Slurpuff", PokeType::Fairy);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(686, 288, "Inkay", PokeType::Dark, PokeType::Psychic);
      }
      add_pokemon(687, 482, "Malamar", PokeType::Dark, PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(688, 306, "Binacle", PokeType::Rock, PokeType::Water);
      }
      add_pokemon(689, 500, "Barbaracle", PokeType::Rock, PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(690, 320, "Skrelp", PokeType::Poison, PokeType::Water);
      }
      add_pokemon(691, 494, "Dragalge", PokeType::Poison, PokeType::Dragon);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(692, 330, "Clauncher", PokeType::Water);
      }
      add_pokemon(693, 500, "Clawitzer", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(694, 289, "Helioptile", PokeType::Electric, PokeType::Normal);
      }
      add_pokemon(695, 481, "Heliolisk", PokeType::Electric, PokeType::Normal);
      if (InclusionFlag::FOSSILS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(696, 362, "Tyrunt", PokeType::Rock, PokeType::Dragon);
         }
         add_pokemon(697, 521, "Tyrantrum", PokeType::Rock, PokeType::Dragon);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(698, 362, "Amaura", PokeType::Rock, PokeType::Ice);
         }
         add_pokemon(699, 521, "Aurorus", PokeType::Rock, PokeType::Ice);
      }
      add_pokemon(700, 525, "Sylveon", PokeType::Fairy);
      add_pokemon(701, 500, "Hawlucha", PokeType::Fighting, PokeType::Flying);
      add_pokemon(702, 431, "Dedenne", PokeType::Electric, PokeType::Fairy);
      add_pokemon(703, 500, "Carbink", PokeType::Rock, PokeType::Fairy);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(704, 300, "Goomy", PokeType::Dragon);
         add_pokemon(705, 452, "Sliggoo", PokeType::Dragon);
      }
      if (InclusionFlag::PSEUDOLEGENDARIES & inclusions) {
         add_pokemon(706, 600, "Goodra", PokeType::Dragon);
      }
      add_pokemon(707, 470, "Klefki", PokeType::Steel, PokeType::Fairy);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(708, 309, "Phantump", PokeType::Ghost, PokeType::Grass);
      }
      add_pokemon(709, 474, "Trevenant", PokeType::Ghost, PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(710, 335, "Pumpkaboo", PokeType::Ghost, PokeType::Grass);
      }
      add_pokemon(711, 494, "Gourgeist", PokeType::Ghost, PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(712, 304, "Bergmite", PokeType::Ice);
      }
      add_pokemon(713, 514, "Avalugg", PokeType::Ice);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(714, 245, "Noibat", PokeType::Flying, PokeType::Dragon);
      }
      add_pokemon(715, 535, "Noivern", PokeType::Flying, PokeType::Dragon);
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(716, 680, "Xerneas", PokeType::Fairy);
         add_pokemon(717, 680, "Yvetal", PokeType::Dark, PokeType::Flying);
         add_pokemon(718, 708, "Zygarde", PokeType::Dragon, PokeType::Ground);
      }
      if (InclusionFlag::MYSTERIOUS & inclusions) {
         add_pokemon(719, 600, "Diancie", PokeType::Rock, PokeType::Fairy);
         if (InclusionFlag::MEGAS & inclusions) {
            add_pokemon(719, 700, "MegaDiancie", PokeType::Rock, PokeType::Fairy);
         }
         add_pokemon(720, 600, "Hoopa_confined", PokeType::Psychic, PokeType::Ghost);
         add_pokemon(720, 680, "Hoopa_unbound", PokeType::Psychic, PokeType::Dark);
         add_pokemon(721, 600, "Volcanion", PokeType::Fire, PokeType::Water);
      }
   }

   if (RegionsFlag::ALOLA & regions) {
      if (InclusionFlag::STARTERS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(722, 320, "Rowlet", PokeType::Grass, PokeType::Flying);
            add_pokemon(723, 420, "Dartrix", PokeType::Grass, PokeType::Flying);
         }
         add_pokemon(724, 530, "Decidueye", PokeType::Grass, PokeType::Ghost);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(725, 320, "Litten", PokeType::Fire);
            add_pokemon(726, 420, "Torracat", PokeType::Fire);
         }
         add_pokemon(727, 530, "Rowlet", PokeType::Fire, PokeType::Dark);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(728, 320, "Popplio", PokeType::Water);
            add_pokemon(729, 420, "Brionne", PokeType::Water);
         }
         add_pokemon(730, 530, "Primatina", PokeType::Water, PokeType::Fairy);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(731, 265, "Pikipek", PokeType::Normal, PokeType::Flying);
         add_pokemon(732, 355, "Trumbeak", PokeType::Normal, PokeType::Flying);
      }
      add_pokemon(733, 485, "Toucannon", PokeType::Normal, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(734, 253, "Yungoos", PokeType::Normal);
      }
      add_pokemon(735, 418, "Gumshoos", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(736, 300, "Grubbin", PokeType::Bug);
         add_pokemon(737, 400, "Charjabug", PokeType::Bug, PokeType::Electric);
      }
      add_pokemon(738, 500, "Vikavolt", PokeType::Bug, PokeType::Electric);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(739, 338, "Crabrawler", PokeType::Fighting);
      }
      add_pokemon(740, 478, "Crabominable", PokeType::Fighting, PokeType::Ice);
      add_pokemon(741, 476, "Oricorio_baile", PokeType::Fire, PokeType::Flying);
      add_pokemon(741, 476, "Oricorio_pom-pom", PokeType::Electric, PokeType::Flying);
      add_pokemon(741, 476, "Oricorio_pa'u", PokeType::Psychic, PokeType::Flying);
      add_pokemon(741, 476, "Oricori_sensu", PokeType::Ghost, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(742, 304, "Cutiefly", PokeType::Bug, PokeType::Fairy);
      }
      add_pokemon(743, 464, "Ribombee", PokeType::Bug, PokeType::Fairy);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(744, 280, "Rockruff", PokeType::Rock);
      }
      add_pokemon(745, 487, "Lycanroc", PokeType::Rock);
      add_pokemon(746, 175, "Wishiwashi", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(747, 305, "Mareanie", PokeType::Poison, PokeType::Water);
      }
      add_pokemon(748, 495, "Toxapex", PokeType::Poison, PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(749, 385, "Mudbray", PokeType::Ground);
      }
      add_pokemon(750, 500, "Mudsdale", PokeType::Ground);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(751, 269, "Dewpider", PokeType::Water, PokeType::Bug);
      }
      add_pokemon(752, 454, "Araquanid", PokeType::Water, PokeType::Bug);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(753, 250, "Fomantis", PokeType::Grass);
      }
      add_pokemon(754, 480, "Lurantis", PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(755, 285, "Morelull", PokeType::Grass, PokeType::Fairy);
      }
      add_pokemon(756, 405, "Shiinotic", PokeType::Grass, PokeType::Fairy);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(757, 320, "Salandit", PokeType::Poison, PokeType::Fire);
      }
      add_pokemon(758, 480, "Salazzle", PokeType::Poison, PokeType::Fire);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(759, 340, "Stufful", PokeType::Normal, PokeType::Fighting);
      }
      add_pokemon(760, 500, "Bewear", PokeType::Normal, PokeType::Fighting);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(761, 210, "Bounsweet", PokeType::Grass);
         add_pokemon(762, 290, "Steenee", PokeType::Grass);
      }
      add_pokemon(763, 510, "Tsareena", PokeType::Grass);
      add_pokemon(764, 485, "Comfey", PokeType::Fairy);
      add_pokemon(765, 490, "Oranguru", PokeType::Normal, PokeType::Psychic);
      add_pokemon(766, 490, "Passimian", PokeType::Fighting);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(767, 230, "Wimpod", PokeType::Bug, PokeType::Water);
      }
      add_pokemon(768, 530, "Golisopod", PokeType::Bug, PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(769, 320, "Sandygast", PokeType::Ghost, PokeType::Ground);
      }
      add_pokemon(770, 480, "Palossand", PokeType::Ghost, PokeType::Ground);
      add_pokemon(771, 410, "Pyukumuku", PokeType::Water);
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(772, 534, "Type:Null", PokeType::Normal);
         add_pokemon(773, 570, "Silvally_normal", PokeType::Normal);
         add_pokemon(773, 570, "Silvally_fighting", PokeType::Fighting);
         add_pokemon(773, 570, "Silvally_flying", PokeType::Flying);
         add_pokemon(773, 570, "Silvally_poison", PokeType::Poison);
         add_pokemon(773, 570, "Silvally_ground", PokeType::Ground);
         add_pokemon(773, 570, "Silvally_rock", PokeType::Rock);
         add_pokemon(773, 570, "Silvally_bug", PokeType::Bug);
         add_pokemon(773, 570, "Silvally_ghost", PokeType::Ghost);
         add_pokemon(773, 570, "Silvally_steel", PokeType::Steel);
         add_pokemon(773, 570, "Silvally_fire", PokeType::Fire);
         add_pokemon(773, 570, "Silvally_water", PokeType::Water);
         add_pokemon(773, 570, "Silvally_grass", PokeType::Grass);
         add_pokemon(773, 570, "Silvally_electric", PokeType::Electric);
         add_pokemon(773, 570, "Silvally_psychic", PokeType::Psychic);
         add_pokemon(773, 570, "Silvally_ice", PokeType::Ice);
         add_pokemon(773, 570, "Silvally_dragon", PokeType::Dragon);
         add_pokemon(773, 570, "Silvally_dark", PokeType::Dark);
         add_pokemon(773, 570, "Silvally_fairy", PokeType::Fairy);
      }
      add_pokemon(774, 440, "Minior", PokeType::Rock, PokeType::Flying);
      add_pokemon(775, 480, "Komala", PokeType::Normal);
      add_pokemon(776, 485, "Turtonator", PokeType::Fire, PokeType::Dragon);
      add_pokemon(777, 435, "Togedemaru", PokeType::Electric, PokeType::Steel);
      add_pokemon(778, 476, "Mimikyu", PokeType::Ghost, PokeType::Fairy);
      add_pokemon(779, 475, "Bruxish", PokeType::Water, PokeType::Psychic);
      add_pokemon(780, 485, "Drampa", PokeType::Normal, PokeType::Dragon);
      add_pokemon(781, 517, "Dhelmise", PokeType::Grass, PokeType::Ghost);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(782, 300, "Jangmo-o", PokeType::Dragon);
         add_pokemon(783, 420, "Hakamo-o", PokeType::Dragon, PokeType::Fighting);
      }
      if (InclusionFlag::PSEUDOLEGENDARIES & inclusions) {
         add_pokemon(784, 600, "Kommo-o", PokeType::Dragon, PokeType::Fighting);
      }
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(785, 570, "TapuKoko", PokeType::Electric, PokeType::Fairy);
         add_pokemon(786, 570, "TapuLele", PokeType::Psychic, PokeType::Fairy);
         add_pokemon(787, 570, "TapuBulu", PokeType::Grass, PokeType::Fairy);
         add_pokemon(788, 570, "TapuFini", PokeType::Water, PokeType::Fairy);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(789, 200, "Cosmog", PokeType::Psychic);
            add_pokemon(790, 400, "Cosmoem", PokeType::Psychic);
         }
         add_pokemon(791, 680, "Solgaleo", PokeType::Psychic, PokeType::Steel);
         add_pokemon(792, 680, "Lunala", PokeType::Psychic, PokeType::Ghost);
      }
      if (InclusionFlag::ULTRACREATURES & inclusions) {
         add_pokemon(793, 570, "Nihilego", PokeType::Rock, PokeType::Poison);
         add_pokemon(794, 570, "Buzzwole", PokeType::Bug, PokeType::Fighting);
         add_pokemon(795, 570, "Pheromosa", PokeType::Bug, PokeType::Fighting);
         add_pokemon(796, 570, "Xurkitree", PokeType::Electric);
         add_pokemon(797, 570, "Celesteela", PokeType::Steel, PokeType::Flying);
         add_pokemon(798, 570, "Kartana", PokeType::Grass, PokeType::Steel);
         add_pokemon(799, 570, "Guzzlord", PokeType::Dark, PokeType::Dragon);
      }
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(800, 600, "Necrozma", PokeType::Psychic);
         add_pokemon(800, 680, "DuskManeNecrozma", PokeType::Psychic, PokeType::Steel);
         add_pokemon(800, 680, "DawnWingsNecrozma", PokeType::Psychic, PokeType::Ghost);
         add_pokemon(800, 754, "UltraNecrozma", PokeType::Psychic, PokeType::Dragon);
      }
      if (InclusionFlag::MYSTERIOUS & inclusions) {
         add_pokemon(801, 600, "Magearna", PokeType::Steel, PokeType::Fairy);
         add_pokemon(802, 600, "Marshadow", PokeType::Fighting, PokeType::Ghost);
      }
      if (InclusionFlag::ULTRACREATURES & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(803, 420, "Poipole", PokeType::Poison);
         }
         add_pokemon(804, 540, "Naganadel", PokeType::Poison, PokeType::Dragon);
         add_pokemon(805, 570, "Stakataka", PokeType::Rock, PokeType::Steel);
         add_pokemon(806, 570, "Blacephalon", PokeType::Fire, PokeType::Ghost);
      }
      if (InclusionFlag::MYSTERIOUS & inclusions) {
         add_pokemon(807, 600, "Zeraora", PokeType::Electric);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(808, 300, "Meltan", PokeType::Steel);
         }
         add_pokemon(809, 600, "Melmetal", PokeType::Steel);
      }
   }

   extract_representatives();
}