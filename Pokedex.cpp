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
            add_pokemon(1, "Bulbasaur", PokeType::Grass, PokeType::Poison);
            add_pokemon(2, "Ivysaur", PokeType::Grass, PokeType::Poison);
         }
         add_pokemon(3, "Venusaur", PokeType::Grass, PokeType::Poison);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(4, "Charmander", PokeType::Fire);
            add_pokemon(5, "Charmeleon", PokeType::Fire);
         }
         add_pokemon(6, "Charizard", PokeType::Fire, PokeType::Flying);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(7, "Squirtle", PokeType::Water);
            add_pokemon(8, "Wartortle", PokeType::Water);
         }
         add_pokemon(9, "Blastoise", PokeType::Water);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(10, "Caterpie", PokeType::Bug);
         add_pokemon(11, "Metapod", PokeType::Bug);
      }
      add_pokemon(12, "Butterfree", PokeType::Bug, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(13, "Weedle", PokeType::Bug, PokeType::Poison);
         add_pokemon(14, "Kakuna", PokeType::Bug, PokeType::Poison);
      }
      add_pokemon(15, "Beedrill", PokeType::Bug, PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(16, "Pidgey", PokeType::Normal, PokeType::Flying);
         add_pokemon(17, "Pidgeotto", PokeType::Normal, PokeType::Flying);
      }
      add_pokemon(18, "Pidgeot", PokeType::Normal, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(19, "Rattata", PokeType::Normal);
      }
      add_pokemon(20, "Raticate", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(21, "Spearow", PokeType::Normal, PokeType::Flying);
      }
      add_pokemon(22, "Fearow", PokeType::Normal, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(23, "Ekans", PokeType::Poison);
      }
      add_pokemon(24, "Arbok", PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(25, "Pikachu", PokeType::Electric);
      }
      add_pokemon(26, "Raichu", PokeType::Electric);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(27, "Snadshrew", PokeType::Ground);
      }
      add_pokemon(28, "Sandlash", PokeType::Ground);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(29, "Nidoranf_f", PokeType::Poison);
         add_pokemon(30, "Nidorina", PokeType::Poison);
      }
      add_pokemon(31, "Nidoqueen", PokeType::Poison, PokeType::Ground);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(32, "Nidoranf_m", PokeType::Poison);
         add_pokemon(33, "Nidorino", PokeType::Poison);
      }
      add_pokemon(34, "Nidoking", PokeType::Poison, PokeType::Ground);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(35, "Clefairy", PokeType::Fairy);
      }
      add_pokemon(36, "Clefable", PokeType::Fairy);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(37, "Vulpix", PokeType::Fire);
      }
      add_pokemon(38, "Ninetales", PokeType::Fire);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(39, "Jigglypuff", PokeType::Normal, PokeType::Fairy);
      }
      add_pokemon(40, "Wiglytuff", PokeType::Normal, PokeType::Fairy);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(41, "Zubat", PokeType::Poison, PokeType::Flying);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(42, "Golbat", PokeType::Poison, PokeType::Flying);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(43, "Oddish", PokeType::Grass, PokeType::Poison);
         add_pokemon(44, "Gloom", PokeType::Grass, PokeType::Poison);
      }
      add_pokemon(45, "Vileplume", PokeType::Grass, PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(46, "Paras", PokeType::Bug, PokeType::Grass);
      }
      add_pokemon(47, "Parasect", PokeType::Bug, PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(48, "Venonat", PokeType::Bug, PokeType::Poison);
      }
      add_pokemon(49, "Venomoth", PokeType::Bug, PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(50, "Diglett", PokeType::Ground);
      }
      add_pokemon(51, "Dugtrio", PokeType::Ground);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(52, "Meowth", PokeType::Normal);
      }
      add_pokemon(53, "Persian", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(54, "Psyduck", PokeType::Water);
      }
      add_pokemon(55, "Golduck", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(56, "Mankey", PokeType::Fighting);
      }
      add_pokemon(57, "Primeape", PokeType::Fighting);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(58, "Growlithe", PokeType::Fire);
      }
      add_pokemon(59, "Arcanine", PokeType::Fire);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(60, "Poliwag", PokeType::Water);
         add_pokemon(61, "Poliwhirl", PokeType::Water);
      }
      add_pokemon(62, "Poliwrath", PokeType::Water, PokeType::Fighting);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(63, "Abra", PokeType::Psychic);
         add_pokemon(64, "Kadabra", PokeType::Psychic);
      }
      add_pokemon(65, "Alakazam", PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(66, "Machop", PokeType::Fighting);
         add_pokemon(67, "Machoke", PokeType::Fighting);
      }
      add_pokemon(68, "Machamp", PokeType::Fighting);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(69, "Bellsprout", PokeType::Grass, PokeType::Poison);
         add_pokemon(70, "Weepinbell", PokeType::Grass, PokeType::Poison);
      }
      add_pokemon(71, "Victribel", PokeType::Grass, PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(72, "Tentacool", PokeType::Water, PokeType::Poison);
      }
      add_pokemon(73, "Tentacruel", PokeType::Water, PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(74, "Geodude", PokeType::Rock, PokeType::Ground);
         add_pokemon(75, "Graveler", PokeType::Rock, PokeType::Ground);
      }
      add_pokemon(76, "Golem", PokeType::Rock, PokeType::Ground);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(77, "Ponyta", PokeType::Fire);
      }
      add_pokemon(78, "Rapidash", PokeType::Fire);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(79, "Slopoke", PokeType::Water, PokeType::Psychic);
      }
      add_pokemon(80, "Slowbro", PokeType::Water, PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(81, "Magnemite", PokeType::Electric, PokeType::Steel);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(82, "Magneton", PokeType::Electric, PokeType::Steel);
      }
      add_pokemon(83, "Farfetch'd", PokeType::Normal, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(84, "Doduo", PokeType::Normal, PokeType::Flying);
      }
      add_pokemon(85, "Dodrio", PokeType::Normal, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(86, "Seel", PokeType::Water, PokeType::Ice);
      }
      add_pokemon(87, "Dwegong", PokeType::Water, PokeType::Ice);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(88, "Grimer", PokeType::Poison);
      }
      add_pokemon(89, "Muk", PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(90, "Shellder", PokeType::Water);
      }
      add_pokemon(91, "Cloyster", PokeType::Water, PokeType::Ice);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(92, "Gastly", PokeType::Ghost, PokeType::Poison);
         add_pokemon(93, "Haunter", PokeType::Ghost, PokeType::Poison);
      }
      add_pokemon(94, "Gengar", PokeType::Ghost, PokeType::Poison);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(95, "Onix", PokeType::Rock, PokeType::Ground);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(98, "Drowzee", PokeType::Psychic);
      }
      add_pokemon(97, "Hypno", PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(98, "Krabby", PokeType::Water);
      }
      add_pokemon(99, "Kingler", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(100, "Voltorb", PokeType::Electric);
      }
      add_pokemon(101, "Electrode", PokeType::Electric);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(102, "Exeggcute", PokeType::Grass, PokeType::Psychic);
      }
      add_pokemon(103, "Exeggutor", PokeType::Grass, PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(104, "Cubone", PokeType::Ground);
      }
      add_pokemon(105, "Marowak", PokeType::Ground);
      add_pokemon(106, "Hitmonlee", PokeType::Fighting);
      add_pokemon(107, "Hitmonchan", PokeType::Fighting);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(108, "Lickitung", PokeType::Normal);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(109, "Koffing", PokeType::Poison);
      }
      add_pokemon(110, "Weezing", PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(111, "Rhyhorn", PokeType::Ground, PokeType::Rock);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(112, "Rhydon", PokeType::Ground, PokeType::Rock);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(113, "Chansey", PokeType::Normal);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(114, "Tangela", PokeType::Grass);
      }
      add_pokemon(115, "Kangaskhan", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(116, "Horsea", PokeType::Water);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(117, "Seadra", PokeType::Water);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(118, "Goldeen", PokeType::Water);
      }
      add_pokemon(119, "Seaking", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(120, "Staryu", PokeType::Water);
      }
      add_pokemon(121, "Starmie", PokeType::Water, PokeType::Psychic);
      add_pokemon(122, "Mr.Mime", PokeType::Psychic, PokeType::Fairy);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(123, "Scyther", PokeType::Bug, PokeType::Flying);
      }
      add_pokemon(124, "Jynx", PokeType::Ice, PokeType::Psychic);

      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(125, "Electabuzz", PokeType::Electric);
         add_pokemon(126, "Magmar", PokeType::Fire);
      }
      add_pokemon(127, "Pinsir", PokeType::Bug);
      add_pokemon(128, "Tauros", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(129, "Magikarp", PokeType::Water);
      }
      add_pokemon(130, "Gyarados", PokeType::Water, PokeType::Flying);
      add_pokemon(131, "Lapras", PokeType::Water, PokeType::Ice);
      add_pokemon(132, "Ditto", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(133, "Eevee", PokeType::Normal);
      }
      add_pokemon(134, "Vaporeon", PokeType::Water);
      add_pokemon(135, "Jolteon", PokeType::Electric);
      add_pokemon(136, "Flareon", PokeType::Fire);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or
          (not(RegionsFlag::JOHTO & regions) and not(RegionsFlag::SINNOH & regions))) {
         add_pokemon(137, "Porygon", PokeType::Normal);
      }
      if (InclusionFlag::FOSSILS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(138, "Omanyte", PokeType::Rock, PokeType::Water);
         }
         add_pokemon(139, "Omastar", PokeType::Rock, PokeType::Water);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(140, "Kabuto", PokeType::Rock, PokeType::Water);
         }
         add_pokemon(141, "Kabutops", PokeType::Rock, PokeType::Water);
         add_pokemon(142, "Aerodactyl", PokeType::Rock, PokeType::Flying);
      }
      add_pokemon(143, "Snorlax", PokeType::Normal);
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(144, "Articuno", PokeType::Ice, PokeType::Flying);
         add_pokemon(145, "Zapdos", PokeType::Electric, PokeType::Flying);
         add_pokemon(146, "Moltres", PokeType::Fire, PokeType::Flying);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(147, "Dratini", PokeType::Dragon);
         add_pokemon(148, "Dragonair", PokeType::Dragon);
      }
      if (InclusionFlag::PSEUDOLEGENDARIES & inclusions) {
         add_pokemon(149, "Dragonite", PokeType::Dragon, PokeType::Flying);
      }
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(150, "MewTwo", PokeType::Psychic);
         add_pokemon(151, "Mew", PokeType::Psychic);
      }
   }

   if (RegionsFlag::JOHTO & regions) {
      if (InclusionFlag::STARTERS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(152, "Chikorita", PokeType::Grass);
            add_pokemon(153, "Bayleef", PokeType::Grass);
         }
         add_pokemon(154, "Meganium", PokeType::Grass);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(155, "Cyndaquil", PokeType::Fire);
            add_pokemon(156, "Quilava", PokeType::Fire);
         }
         add_pokemon(157, "Typhlosion", PokeType::Fire);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(158, "Totodile", PokeType::Water);
            add_pokemon(159, "Croconaw", PokeType::Water);
         }
         add_pokemon(160, "Feraligatr", PokeType::Water);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(161, "FurrSentretet", PokeType::Normal);
      }
      add_pokemon(162, "Furret", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(163, "Hoothoot", PokeType::Normal, PokeType::Flying);
      }
      add_pokemon(164, "Noctowl", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(165, "Ledyba", PokeType::Bug, PokeType::Flying);
      }
      add_pokemon(166, "Ledian", PokeType::Bug, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(167, "Spinarak", PokeType::Bug, PokeType::Poison);
      }
      add_pokemon(168, "Ariados", PokeType::Bug, PokeType::Poison);
      add_pokemon(169, "Crobat", PokeType::Poison, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(170, "Chinchou", PokeType::Water, PokeType::Electric);
      }
      add_pokemon(171, "Lanturn", PokeType::Water, PokeType::Electric);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::KANTO & regions)) {
         add_pokemon(172, "Pichu", PokeType::Electric);
         add_pokemon(173, "Cleffa", PokeType::Fairy);
         add_pokemon(174, "Igglybuff", PokeType::Normal, PokeType::Fairy);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(175, "Togepi", PokeType::Fairy);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(176, "Togetic", PokeType::Fairy, PokeType::Flying);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(177, "Natu", PokeType::Psychic, PokeType::Flying);
      }
      add_pokemon(178, "Xatu", PokeType::Psychic, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(179, "Mareep", PokeType::Electric);
         add_pokemon(180, "Flaffa", PokeType::Electric);
      }
      add_pokemon(181, "Ampharos", PokeType::Electric);
      add_pokemon(182, "Bellossom", PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(183, "Marill", PokeType::Water, PokeType::Fairy);
      }
      add_pokemon(184, "Azumarill", PokeType::Water, PokeType::Fairy);
      add_pokemon(185, "Sudowoodo", PokeType::Rock);
      add_pokemon(186, "Politoed", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(187, "Hippip", PokeType::Grass, PokeType::Flying);
         add_pokemon(188, "Skiploom", PokeType::Grass, PokeType::Flying);
      }
      add_pokemon(189, "Jumpluff", PokeType::Grass, PokeType::Flying);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(190, "Aipom", PokeType::Normal);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(191, "Sunkern", PokeType::Grass);
      }
      add_pokemon(192, "Sunflora", PokeType::Grass);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(193, "Yanma", PokeType::Bug, PokeType::Flying);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(194, "Wooper", PokeType::Water, PokeType::Ground);
      }
      add_pokemon(195, "Quagsire", PokeType::Water, PokeType::Ground);
      add_pokemon(196, "Espeon", PokeType::Psychic);
      add_pokemon(197, "Umbreon", PokeType::Dark);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(198, "Murkrow", PokeType::Dark, PokeType::Flying);
      }
      add_pokemon(199, "Slowking", PokeType::Water, PokeType::Psychic);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(200, "Misdreavus", PokeType::Ghost);
      }
      add_pokemon(201, "Unown", PokeType::Psychic);
      add_pokemon(202, "Wobbuffet", PokeType::Psychic);
      add_pokemon(203, "Girafing", PokeType::Normal, PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(204, "Pineco", PokeType::Bug);
      }
      add_pokemon(205, "Forrtress", PokeType::Bug, PokeType::Steel);
      add_pokemon(206, "Dunsparce", PokeType::Normal);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(207, "Gligar", PokeType::Ground, PokeType::Flying);
      }
      add_pokemon(208, "Steelix", PokeType::Steel, PokeType::Ground);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(209, "Snubbull", PokeType::Fairy);
      }
      add_pokemon(210, "Granbull", PokeType::Fairy);
      add_pokemon(211, "Qwilfish", PokeType::Water, PokeType::Poison);
      add_pokemon(212, "Scizor", PokeType::Bug, PokeType::Steel);
      add_pokemon(213, "Shuckle", PokeType::Bug, PokeType::Rock);
      add_pokemon(214, "Heracross", PokeType::Bug, PokeType::Fighting);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(215, "Sneasel", PokeType::Dark, PokeType::Ice);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(216, "Teddiursa", PokeType::Normal);
      }
      add_pokemon(217, "Ursaring", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(218, "Slugma", PokeType::Fire);
      }
      add_pokemon(219, "Magcargo", PokeType::Fire, PokeType::Rock);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(220, "Swinub", PokeType::Ice, PokeType::Ground);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(221, "Piloswine", PokeType::Ice, PokeType::Ground);
      }
      add_pokemon(222, "Corsola", PokeType::Water, PokeType::Rock);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(223, "Remoraid", PokeType::Water);
      }
      add_pokemon(224, "Octillery", PokeType::Water);
      add_pokemon(225, "Delibird", PokeType::Ice, PokeType::Flying);
      add_pokemon(226, "Mantine", PokeType::Water, PokeType::Flying);
      add_pokemon(227, "Skarmory", PokeType::Steel, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(228, "Houndour", PokeType::Dark, PokeType::Fire);
      }
      add_pokemon(229, "Houndoom", PokeType::Dark, PokeType::Fire);
      add_pokemon(230, "Kingdra", PokeType::Water, PokeType::Dragon);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(231, "Phanpy", PokeType::Ground);
      }
      add_pokemon(232, "Donphan", PokeType::Ground);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(233, "Porygon2", PokeType::Normal);
      }
      add_pokemon(234, "Stantler", PokeType::Normal);
      add_pokemon(235, "Smeargle", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(236, "Tyrogue", PokeType::Fighting);
      }
      add_pokemon(237, "Hitmontop", PokeType::Fighting);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::KANTO & regions)) {
         add_pokemon(238, "Smoochum", PokeType::Ice, PokeType::Psychic);
         add_pokemon(239, "Elekid", PokeType::Electric);
         add_pokemon(240, "Magby", PokeType::Fire);
      }
      add_pokemon(241, "Miltank", PokeType::Normal);
      add_pokemon(242, "Blissey", PokeType::Normal);
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(243, "Raikou", PokeType::Electric);
         add_pokemon(244, "Entei", PokeType::Fire);
         add_pokemon(245, "Suicune", PokeType::Water);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(246, "Larvitar", PokeType::Rock, PokeType::Dark);
         add_pokemon(247, "Pupitar", PokeType::Rock, PokeType::Dark);
      }
      if (InclusionFlag::PSEUDOLEGENDARIES & inclusions) {
         add_pokemon(248, "Tyranitar", PokeType::Rock, PokeType::Dark);
      }
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(249, "Lugia", PokeType::Psychic, PokeType::Flying);
         add_pokemon(250, "Ho-Oh", PokeType::Fire, PokeType::Flying);
         add_pokemon(251, "Celebi", PokeType::Psychic, PokeType::Grass);
      }
   }

   if (RegionsFlag::HOENN & regions) {
      if (InclusionFlag::STARTERS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(252, "Treecko", PokeType::Grass);
            add_pokemon(253, "Grovyle", PokeType::Grass);
         }
         add_pokemon(254, "Sceptile", PokeType::Grass);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(255, "Torchic", PokeType::Fire);
            add_pokemon(256, "Combusken", PokeType::Fire, PokeType::Fighting);
         }
         add_pokemon(257, "Blanziken", PokeType::Fire, PokeType::Fighting);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(258, "Mudkip", PokeType::Water);
            add_pokemon(259, "Marshtomp", PokeType::Water, PokeType::Ground);
         }
         add_pokemon(260, "Swampert", PokeType::Water, PokeType::Ground);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(261, "Poochyena", PokeType::Dark);
      }
      add_pokemon(262, "Mightyena", PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(263, "Zigzagoon", PokeType::Normal);
      }
      add_pokemon(264, "Linoone", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(265, "Wurmple", PokeType::Bug);
         add_pokemon(266, "Silcoon", PokeType::Bug);
      }
      add_pokemon(267, "Beautifly", PokeType::Bug, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(268, "Cascoon", PokeType::Bug);
      }
      add_pokemon(269, "Dustox", PokeType::Bug, PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(270, "Lotad", PokeType::Water, PokeType::Grass);
         add_pokemon(271, "Lombre", PokeType::Water, PokeType::Grass);
      }
      add_pokemon(272, "Ludicolo", PokeType::Water, PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(273, "Seedot", PokeType::Grass);
         add_pokemon(274, "Nuzleaf", PokeType::Grass, PokeType::Dark);
      }
      add_pokemon(275, "Shiftry", PokeType::Grass, PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(276, "Taillow", PokeType::Normal, PokeType::Flying);
      }
      add_pokemon(277, "Swellow", PokeType::Normal, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(278, "Wingull", PokeType::Water, PokeType::Flying);
      }
      add_pokemon(279, "Pelipper", PokeType::Water, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(280, "Ralts", PokeType::Psychic, PokeType::Fairy);
         add_pokemon(281, "Kirlia", PokeType::Psychic, PokeType::Fairy);
      }
      add_pokemon(282, "Gardevoir", PokeType::Psychic, PokeType::Fairy);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(283, "Surskit", PokeType::Bug, PokeType::Water);
      }
      add_pokemon(284, "Masquerain", PokeType::Bug, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(285, "Shroomish", PokeType::Grass);
      }
      add_pokemon(286, "Breloom", PokeType::Grass, PokeType::Fighting);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(287, "Slakoth", PokeType::Normal);
         add_pokemon(288, "Vigoroth", PokeType::Normal);
      }
      add_pokemon(289, "Slaking", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(290, "Nincada", PokeType::Bug, PokeType::Ground);
      }
      add_pokemon(291, "Ninjask", PokeType::Bug, PokeType::Flying);
      add_pokemon(292, "Shedinja", PokeType::Bug, PokeType::Ghost);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(293, "Whismur", PokeType::Normal);
         add_pokemon(294, "Loudred", PokeType::Normal);
      }
      add_pokemon(295, "Exploud", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(296, "Makuhita", PokeType::Fighting);
      }
      add_pokemon(297, "Hariyama", PokeType::Fighting);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(298, "Azurill", PokeType::Normal, PokeType::Fairy);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(299, "Nosepass", PokeType::Rock);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(300, "Skitty", PokeType::Normal);
      }
      add_pokemon(301, "Delcatty", PokeType::Normal);
      add_pokemon(302, "Sableye", PokeType::Dark, PokeType::Ghost);
      add_pokemon(303, "Mawile", PokeType::Steel, PokeType::Fairy);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(304, "Aron", PokeType::Steel, PokeType::Rock);
         add_pokemon(305, "Aggron", PokeType::Steel, PokeType::Rock);
      }
      add_pokemon(306, "Aggron", PokeType::Steel, PokeType::Rock);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(307, "Meditite", PokeType::Fighting, PokeType::Psychic);
      }
      add_pokemon(308, "Medicham", PokeType::Fighting, PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(309, "Electrike", PokeType::Electric);
      }
      add_pokemon(310, "Manectric", PokeType::Electric);
      add_pokemon(311, "Pluse", PokeType::Electric);
      add_pokemon(312, "Minun", PokeType::Electric);
      add_pokemon(313, "Volbeat", PokeType::Bug);
      add_pokemon(314, "Illumise", PokeType::Bug);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(315, "Roselia", PokeType::Grass, PokeType::Poison);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(316, "Gulpin", PokeType::Poison);
      }
      add_pokemon(317, "Swalot", PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(318, "Carvanha", PokeType::Water, PokeType::Dark);
      }
      add_pokemon(319, "Sharpedo", PokeType::Water, PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(320, "Wailmer", PokeType::Water);
      }
      add_pokemon(321, "Wailord", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(322, "Numel", PokeType::Fire, PokeType::Ground);
      }
      add_pokemon(323, "Camerupt", PokeType::Fire, PokeType::Ground);
      add_pokemon(324, "Torkoal", PokeType::Fire);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(325, "Spoink", PokeType::Psychic);
      }
      add_pokemon(326, "Grumping", PokeType::Psychic);
      add_pokemon(327, "Spinda", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(328, "Trapinch", PokeType::Ground);
         add_pokemon(329, "Vibrava", PokeType::Ground, PokeType::Dragon);
      }
      add_pokemon(330, "Flygon", PokeType::Ground, PokeType::Dragon);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(331, "Cacnea", PokeType::Grass);
      }
      add_pokemon(332, "Cacturne", PokeType::Grass, PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(333, "Swablu", PokeType::Normal, PokeType::Flying);
      }
      add_pokemon(334, "Altaria", PokeType::Dragon, PokeType::Flying);
      add_pokemon(335, "Zangoose", PokeType::Normal);
      add_pokemon(336, "Seviper", PokeType::Poison);
      add_pokemon(337, "Lunatone", PokeType::Rock, PokeType::Psychic);
      add_pokemon(338, "Solrock", PokeType::Rock, PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(339, "Barboach", PokeType::Water, PokeType::Ground);
      }
      add_pokemon(340, "Whiscash", PokeType::Water, PokeType::Ground);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(341, "Corphish", PokeType::Water);
      }
      add_pokemon(342, "Crawdaunt", PokeType::Water, PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(343, "Baltoy", PokeType::Ground, PokeType::Psychic);
      }
      add_pokemon(344, "Claydol", PokeType::Ground, PokeType::Psychic);
      if (InclusionFlag::FOSSILS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(345, "Lileep", PokeType::Rock, PokeType::Grass);
         }
         add_pokemon(346, "Cradily", PokeType::Rock, PokeType::Grass);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(347, "Anorith", PokeType::Rock, PokeType::Bug);
         }
         add_pokemon(348, "Armaldo", PokeType::Rock, PokeType::Bug);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(349, "Feebas", PokeType::Water);
      }
      add_pokemon(350, "Milotic", PokeType::Water);
      add_pokemon(351, "Castform", PokeType::Normal);
      add_pokemon(352, "Keckleon", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(353, "Shuppet", PokeType::Ghost);
      }
      add_pokemon(354, "Banette", PokeType::Ghost);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(355, "Duskull", PokeType::Ghost);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(356, "Dusclops", PokeType::Ghost);
      }
      add_pokemon(357, "Tropius", PokeType::Grass, PokeType::Flying);
      add_pokemon(358, "Chimecho", PokeType::Psychic);
      add_pokemon(359, "Absol", PokeType::Dark);
      add_pokemon(360, "Wynaut", PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(361, "Snorunt", PokeType::Ice);
      }
      add_pokemon(362, "Glalie", PokeType::Ice);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(363, "Spheal", PokeType::Ice, PokeType::Water);
         add_pokemon(364, "Sealeo", PokeType::Ice, PokeType::Water);
      }
      add_pokemon(365, "Walrein", PokeType::Ice, PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(366, "Clamperl", PokeType::Water);
      }
      add_pokemon(367, "Huntail", PokeType::Water);
      add_pokemon(368, "Gorebyss", PokeType::Water);
      add_pokemon(369, "Relicanth", PokeType::Water, PokeType::Rock);
      add_pokemon(370, "Luvdisc", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(371, "Bagon", PokeType::Dragon);
         add_pokemon(372, "Shelgon", PokeType::Dragon);
      }
      if (InclusionFlag::PSEUDOLEGENDARIES & inclusions) {
         add_pokemon(373, "Salamence", PokeType::Dragon, PokeType::Flying);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(374, "Beldum", PokeType::Steel, PokeType::Psychic);
         add_pokemon(375, "Metang", PokeType::Steel, PokeType::Psychic);
      }
      if (InclusionFlag::PSEUDOLEGENDARIES & inclusions) {
         add_pokemon(376, "Metagross", PokeType::Steel, PokeType::Psychic);
      }
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(377, "Regirock", PokeType::Rock);
         add_pokemon(378, "Regice", PokeType::Ice);
         add_pokemon(379, "Registeel", PokeType::Steel);
         add_pokemon(380, "Latias", PokeType::Dragon, PokeType::Psychic);
         add_pokemon(381, "Latios", PokeType::Dragon, PokeType::Psychic);
         add_pokemon(382, "Kyogre", PokeType::Water);
         add_pokemon(383, "Groudon", PokeType::Ground);
         add_pokemon(384, "Rayquaza", PokeType::Dragon, PokeType::Flying);
         add_pokemon(385, "Jirachi", PokeType::Steel, PokeType::Psychic);
         add_pokemon(386, "Deoxys", PokeType::Psychic);
      }
   }

   if (RegionsFlag::SINNOH & regions) {
      if (InclusionFlag::STARTERS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(387, "Turtwig", PokeType::Grass);
            add_pokemon(388, "Grotle", PokeType::Grass);
         }
         add_pokemon(389, "Torterra", PokeType::Grass, PokeType::Ground);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(390, "Chimchar", PokeType::Fire);
            add_pokemon(391, "Monferno", PokeType::Fire, PokeType::Fighting);
         }
         add_pokemon(392, "Infernape", PokeType::Fire, PokeType::Fighting);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(393, "Piplup", PokeType::Water);
            add_pokemon(394, "Prinplup", PokeType::Water);
         }
         add_pokemon(395, "Empoleon", PokeType::Water, PokeType::Steel);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(396, "Starly", PokeType::Normal, PokeType::Flying);
         add_pokemon(397, "Starvia", PokeType::Normal, PokeType::Flying);
      }
      add_pokemon(398, "Staraptor", PokeType::Normal, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(399, "Bidoof", PokeType::Normal);
      }
      add_pokemon(400, "Bibarel", PokeType::Normal, PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(401, "Kricketot", PokeType::Bug);
      }
      add_pokemon(402, "Kricketune", PokeType::Bug);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(403, "Shinx", PokeType::Electric);
         add_pokemon(404, "Luxio", PokeType::Electric);
      }
      add_pokemon(405, "Luxray", PokeType::Electric);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(406, "Budew", PokeType::Grass, PokeType::Poison);
      }
      add_pokemon(407, "Roserade", PokeType::Grass, PokeType::Poison);
      if (InclusionFlag::FOSSILS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(408, "Cranidos", PokeType::Rock);
         }
         add_pokemon(409, "Rampardos", PokeType::Rock);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(410, "Shieldon", PokeType::Rock, PokeType::Steel);
         }
         add_pokemon(411, "Bastiadon", PokeType::Rock, PokeType::Steel);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(412, "Burmy", PokeType::Bug);
      }
      add_pokemon(413, "Wormadam_grass", PokeType::Bug, PokeType::Grass);
      add_pokemon(413, "Wormadam_ground", PokeType::Bug, PokeType::Ground);
      add_pokemon(413, "Wormadam_steel", PokeType::Bug, PokeType::Steel);
      add_pokemon(414, "Mothim", PokeType::Bug, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(415, "Combee", PokeType::Bug, PokeType::Flying);
      }
      add_pokemon(416, "Vespiquen", PokeType::Bug, PokeType::Flying);
      add_pokemon(417, "Pachirisu", PokeType::Electric);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(418, "Buizel", PokeType::Water);
      }
      add_pokemon(419, "Floatzel", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(420, "Cherubi", PokeType::Grass);
      }
      add_pokemon(421, "Cherrim", PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(422, "Shellos", PokeType::Water);
      }
      add_pokemon(423, "Gastrodon", PokeType::Water, PokeType::Ground);
      add_pokemon(424, "Ambipom", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(425, "Drifloon", PokeType::Ghost, PokeType::Flying);
      }
      add_pokemon(426, "Drifblim", PokeType::Ghost, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(427, "Buneary", PokeType::Normal);
      }
      add_pokemon(428, "Lopunny", PokeType::Normal, PokeType::Fighting);
      add_pokemon(429, "Mismagius", PokeType::Ghost);
      add_pokemon(430, "Honchkrow", PokeType::Dark, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(431, "Glameow", PokeType::Normal);
      }
      add_pokemon(432, "Perugly", PokeType::Normal);

      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::HOENN & regions)) {
         add_pokemon(433, "Chingling", PokeType::Psychic);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(434, "Skuntank", PokeType::Poison, PokeType::Dark);
      }
      add_pokemon(435, "Skuntank", PokeType::Poison, PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(436, "Bronzor", PokeType::Steel, PokeType::Psychic);
      }
      add_pokemon(437, "Bronzong", PokeType::Steel, PokeType::Psychic);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(438, "Bonsly", PokeType::Rock);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::KANTO & regions)) {
         add_pokemon(439, "MimeJr.", PokeType::Psychic, PokeType::Fairy);
         add_pokemon(440, "Happiny", PokeType::Normal);
      }
      add_pokemon(441, "Chatot", PokeType::Normal, PokeType::Flying);
      add_pokemon(442, "Spiritomb", PokeType::Ghost, PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(443, "Gible", PokeType::Dragon, PokeType::Ground);
         add_pokemon(444, "Babite", PokeType::Dragon, PokeType::Ground);
      }
      if (InclusionFlag::PSEUDOLEGENDARIES & inclusions) {
         add_pokemon(445, "Garchomp", PokeType::Dragon, PokeType::Ground);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::KANTO & regions)) {
         add_pokemon(446, "Munchlax", PokeType::Normal);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(447, "Riolu", PokeType::Fighting);
      }
      add_pokemon(448, "Lucario", PokeType::Fighting, PokeType::Steel);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(449, "Hippopotas", PokeType::Ground);
      }
      add_pokemon(450, "Hippowdon", PokeType::Ground);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(451, "Skorupi", PokeType::Poison, PokeType::Bug);
      }
      add_pokemon(452, "Drapion", PokeType::Poison, PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(453, "Croagunk", PokeType::Poison, PokeType::Fighting);
      }
      add_pokemon(454, "Toxicroak", PokeType::Poison, PokeType::Fighting);
      add_pokemon(455, "Carnivine", PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(456, "Finneon", PokeType::Water);
      }
      add_pokemon(457, "Lumineon", PokeType::Water);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(458, "Mantyke", PokeType::Water, PokeType::Flying);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(459, "Snover", PokeType::Water, PokeType::Ice);
      }
      add_pokemon(460, "Abomasnow", PokeType::Grass, PokeType::Ice);
      add_pokemon(461, "Weavile", PokeType::Dark, PokeType::Ice);
      add_pokemon(462, "Magnezone", PokeType::Electric, PokeType::Steel);
      add_pokemon(463, "Lickilicky", PokeType::Normal);
      add_pokemon(464, "Rhyperior", PokeType::Ground, PokeType::Rock);
      add_pokemon(465, "Tangrowth", PokeType::Grass);
      add_pokemon(466, "Electivire", PokeType::Electric);
      add_pokemon(467, "Magmortar", PokeType::Fire);
      add_pokemon(468, "Togekiss", PokeType::Fairy, PokeType::Flying);
      add_pokemon(469, "Yanmega", PokeType::Bug, PokeType::Flying);
      add_pokemon(470, "Leafeon", PokeType::Grass);
      add_pokemon(471, "Glaceon", PokeType::Ice);
      add_pokemon(472, "Gliscor", PokeType::Ground, PokeType::Flying);
      add_pokemon(473, "Mamoswine", PokeType::Ice, PokeType::Ground);
      add_pokemon(474, "Porygon-Z", PokeType::Normal);
      add_pokemon(475, "Gallade", PokeType::Psychic, PokeType::Fighting);
      add_pokemon(476, "Probopass", PokeType::Rock, PokeType::Steel);
      add_pokemon(477, "Dusknoir", PokeType::Ghost);
      add_pokemon(478, "Froslass", PokeType::Ice, PokeType::Ghost);
      add_pokemon(479, "Rotom_ghost", PokeType::Electric, PokeType::Ghost);
      add_pokemon(479, "Rotom_fire", PokeType::Electric, PokeType::Fire);
      add_pokemon(479, "Rotom_water", PokeType::Electric, PokeType::Water);
      add_pokemon(479, "Rotom_ice", PokeType::Electric, PokeType::Ice);
      add_pokemon(479, "Rotom_flying", PokeType::Electric, PokeType::Flying);
      add_pokemon(479, "Rotom_grass", PokeType::Electric, PokeType::Grass);
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(480, "Uxie", PokeType::Psychic);
         add_pokemon(481, "Mesprit", PokeType::Psychic);
         add_pokemon(482, "Azelf", PokeType::Psychic);
         add_pokemon(483, "Dialga", PokeType::Steel, PokeType::Dragon);
         add_pokemon(484, "Palkia", PokeType::Water, PokeType::Dragon);
         add_pokemon(485, "Heatran", PokeType::Fire, PokeType::Steel);
         add_pokemon(486, "Regigigas", PokeType::Normal);
         add_pokemon(487, "Giratina", PokeType::Ghost, PokeType::Dragon);
         add_pokemon(488, "Cresselia", PokeType::Psychic);
         add_pokemon(489, "Phione", PokeType::Water);
         add_pokemon(490, "Manaphy", PokeType::Water);
         add_pokemon(491, "Darkrai", PokeType::Dark);
         add_pokemon(492, "Shaymin", PokeType::Grass);
         add_pokemon(492, "Shaymin_flying", PokeType::Grass, PokeType::Flying);
         add_pokemon(493, "Arceus_normal", PokeType::Normal);
         add_pokemon(493, "Arceus_fighting", PokeType::Fighting);
         add_pokemon(493, "Arceus_flying", PokeType::Flying);
         add_pokemon(493, "Arceus_poison", PokeType::Poison);
         add_pokemon(493, "Arceus_ground", PokeType::Ground);
         add_pokemon(493, "Arceus_rock", PokeType::Rock);
         add_pokemon(493, "Arceus_bug", PokeType::Bug);
         add_pokemon(493, "Arceus_ghost", PokeType::Ghost);
         add_pokemon(493, "Arceus_steel", PokeType::Steel);
         add_pokemon(493, "Arceus_fire", PokeType::Fire);
         add_pokemon(493, "Arceus_water", PokeType::Water);
         add_pokemon(493, "Arceus_grass", PokeType::Grass);
         add_pokemon(493, "Arceus_electric", PokeType::Electric);
         add_pokemon(493, "Arceus_psychic", PokeType::Psychic);
         add_pokemon(493, "Arceus_ice", PokeType::Ice);
         add_pokemon(493, "Arceus_dragon", PokeType::Dragon);
         add_pokemon(493, "Arceus_dark", PokeType::Dark);
         add_pokemon(493, "Arceus_fairy", PokeType::Fairy);
      }
   }

   if (RegionsFlag::ALOLA & regions) {
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(494, "Victini", PokeType::Psychic, PokeType::Fire);
      }
      if (InclusionFlag::STARTERS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(495, "Snivy", PokeType::Grass);
            add_pokemon(496, "Servine", PokeType::Grass);
         }
         add_pokemon(497, "Serperior", PokeType::Grass);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(498, "Tepig", PokeType::Fire);
            add_pokemon(499, "Pignite", PokeType::Fire, PokeType::Fighting);
         }
         add_pokemon(500, "Emboar", PokeType::Fire, PokeType::Fighting);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(501, "Oshawott", PokeType::Water);
            add_pokemon(502, "Dewott", PokeType::Water);
         }
         add_pokemon(503, "Samurott", PokeType::Water);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(504, "Patrat", PokeType::Normal);
      }
      add_pokemon(505, "Watchog", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(506, "Lillipup", PokeType::Normal);
         add_pokemon(507, "Herdier", PokeType::Normal);
      }
      add_pokemon(508, "Purrloin", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(509, "Purrloin", PokeType::Dark);
      }
      add_pokemon(510, "Liepard", PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(511, "Pansage", PokeType::Grass);
      }
      add_pokemon(512, "Simisage", PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(513, "Pansear", PokeType::Fire);
      }
      add_pokemon(514, "Simisear", PokeType::Fire);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(515, "Panpour", PokeType::Water);
      }
      add_pokemon(516, "Simipour", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(517, "Munna", PokeType::Psychic);
      }
      add_pokemon(518, "Musharna", PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(519, "Pidove", PokeType::Normal, PokeType::Flying);
         add_pokemon(520, "Tranquill", PokeType::Normal, PokeType::Flying);
      }
      add_pokemon(521, "Unfezant", PokeType::Normal, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(522, "Blitzle", PokeType::Electric);
      }
      add_pokemon(523, "Zebstrika", PokeType::Electric);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(524, "Roggenrola", PokeType::Rock);
         add_pokemon(525, "Boldore", PokeType::Rock);
      }
      add_pokemon(526, "Gigalith", PokeType::Rock);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(527, "Woobat", PokeType::Psychic, PokeType::Flying);
      }
      add_pokemon(528, "Swoobat", PokeType::Psychic, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(529, "Drillbur", PokeType::Ground);
      }
      add_pokemon(530, "Excadrill", PokeType::Ground, PokeType::Steel);
      add_pokemon(531, "Audino", PokeType::Normal);
      add_pokemon(531, "Audino_fairy", PokeType::Normal, PokeType::Fairy);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(532, "Timburr", PokeType::Fighting);
         add_pokemon(533, "Gurdurr", PokeType::Fighting);
      }
      add_pokemon(534, "Conkeldurr", PokeType::Fighting);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(535, "Tympole", PokeType::Water);
         add_pokemon(536, "Palpitoad", PokeType::Water, PokeType::Ground);
      }
      add_pokemon(537, "Seismitoad", PokeType::Water, PokeType::Ground);
      add_pokemon(538, "Throh", PokeType::Fighting);
      add_pokemon(539, "Sawk", PokeType::Fighting);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(540, "Sewaddle", PokeType::Bug, PokeType::Grass);
         add_pokemon(541, "Swadloon", PokeType::Bug, PokeType::Grass);
      }
      add_pokemon(542, "Leavanny", PokeType::Bug, PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(543, "Venipede", PokeType::Bug, PokeType::Poison);
         add_pokemon(544, "Whirlipede", PokeType::Bug, PokeType::Poison);
      }
      add_pokemon(545, "Scolipede", PokeType::Bug, PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(546, "Cottonee", PokeType::Grass, PokeType::Fairy);
      }
      add_pokemon(547, "Whimsicott", PokeType::Grass, PokeType::Fairy);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(548, "Petilil", PokeType::Grass);
      }
      add_pokemon(549, "Lilligant", PokeType::Grass);
      add_pokemon(550, "Basculin", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(551, "Sandile", PokeType::Ground, PokeType::Dark);
         add_pokemon(552, "Krokorok", PokeType::Ground, PokeType::Dark);
      }
      add_pokemon(553, "Krookodile", PokeType::Ground, PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(554, "Darumaka", PokeType::Fire);
      }
      add_pokemon(555, "Darmanitan", PokeType::Fire);
      add_pokemon(555, "Darmanitan_zen", PokeType::Fire, PokeType::Psychic);
      add_pokemon(556, "Maractus", PokeType::Grass);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(557, "Dwebble", PokeType::Bug, PokeType::Rock);
      }
      add_pokemon(558, "Crustle", PokeType::Bug, PokeType::Rock);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(559, "Scaggy", PokeType::Dark, PokeType::Fighting);
      }
      add_pokemon(560, "Scrafty", PokeType::Dark, PokeType::Fighting);
      add_pokemon(561, "Sigilyph", PokeType::Psychic, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(562, "Yamask", PokeType::Ghost);
      }
      add_pokemon(563, "Cofagrigus", PokeType::Ghost);
      if (InclusionFlag::FOSSILS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(564, "Tirtouga", PokeType::Rock, PokeType::Water);
         }
         add_pokemon(565, "Carracosta", PokeType::Rock, PokeType::Water);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(566, "Archen", PokeType::Rock, PokeType::Flying);
         }
         add_pokemon(567, "Archeops", PokeType::Rock, PokeType::Flying);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(568, "Trubbish", PokeType::Poison);
      }
      add_pokemon(569, "Garbodor", PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(570, "Zorua", PokeType::Dark);
      }
      add_pokemon(571, "Zoroark", PokeType::Dark);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(572, "Minccino", PokeType::Normal);
      }
      add_pokemon(573, "Cinccino", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(574, "Gothita", PokeType::Psychic);
         add_pokemon(575, "Gothorita", PokeType::Psychic);
      }
      add_pokemon(576, "Gothietelle", PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(577, "Solosis", PokeType::Psychic);
         add_pokemon(578, "Duodolis", PokeType::Psychic);
      }
      add_pokemon(579, "Reuniclus", PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(580, "Ducklett", PokeType::Water, PokeType::Flying);
      }
      add_pokemon(581, "Swanna", PokeType::Water, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(582, "Vanillite", PokeType::Ice);
         add_pokemon(583, "Vanillish", PokeType::Ice);
      }
      add_pokemon(584, "Vanilluxe", PokeType::Ice);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(585, "Deerling", PokeType::Normal, PokeType::Grass);
      }
      add_pokemon(586, "Sawsbuck", PokeType::Normal, PokeType::Grass);
      add_pokemon(587, "Emolga", PokeType::Electric, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(588, "Karrablast", PokeType::Bug);
      }
      add_pokemon(589, "Escavalier", PokeType::Bug, PokeType::Steel);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(590, "Foongus", PokeType::Grass, PokeType::Poison);
      }
      add_pokemon(591, "Amoonguss", PokeType::Grass, PokeType::Poison);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(592, "Frillish", PokeType::Water, PokeType::Ghost);
      }
      add_pokemon(593, "Jellicent", PokeType::Water, PokeType::Ghost);
      add_pokemon(594, "Alomomola", PokeType::Water);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(595, "Joltik", PokeType::Bug, PokeType::Electric);
      }
      add_pokemon(596, "Galvantula", PokeType::Bug, PokeType::Electric);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(597, "Ferroseed", PokeType::Grass, PokeType::Steel);
      }
      add_pokemon(598, "Ferrothorn", PokeType::Grass, PokeType::Steel);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(599, "Klink", PokeType::Steel);
         add_pokemon(600, "Klang", PokeType::Steel);
      }
      add_pokemon(601, "Klinklang", PokeType::Steel);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(602, "Tynamo", PokeType::Electric);
         add_pokemon(603, "Eelektrik", PokeType::Electric);
      }
      add_pokemon(604, "Eelektross", PokeType::Electric);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(605, "Elgyem", PokeType::Psychic);
      }
      add_pokemon(606, "Beheeyem", PokeType::Psychic);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(607, "Litwick", PokeType::Ghost, PokeType::Fire);
         add_pokemon(608, "Lampent", PokeType::Ghost, PokeType::Fire);
      }
      add_pokemon(609, "Chandelure", PokeType::Ghost, PokeType::Fire);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(610, "Axew", PokeType::Dragon);
         add_pokemon(611, "Fraxure", PokeType::Dragon);
      }
      add_pokemon(612, "Haxorus", PokeType::Dragon);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(613, "Cubchoo", PokeType::Ice);
      }
      add_pokemon(614, "Beartic", PokeType::Ice);
      add_pokemon(615, "Cryogonal", PokeType::Ice);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(616, "Shelmet", PokeType::Bug);
      }
      add_pokemon(617, "Accelgor", PokeType::Bug);
      add_pokemon(618, "Stunfisk", PokeType::Ground, PokeType::Electric);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(619, "Mienfoo", PokeType::Fighting);
      }
      add_pokemon(620, "Mienshao", PokeType::Fighting);
      add_pokemon(621, "Druggidon", PokeType::Dragon);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(622, "Golett", PokeType::Ground, PokeType::Ghost);
      }
      add_pokemon(623, "Golurk", PokeType::Ground, PokeType::Ghost);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(624, "Pawniard", PokeType::Dark, PokeType::Steel);
      }
      add_pokemon(625, "Bisharp", PokeType::Dark, PokeType::Steel);
      add_pokemon(626, "Bouffalant", PokeType::Normal);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(627, "Rufflet", PokeType::Normal, PokeType::Flying);
      }
      add_pokemon(628, "Braviary", PokeType::Normal, PokeType::Flying);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(629, "Vullaby", PokeType::Dark, PokeType::Flying);
      }
      add_pokemon(630, "Mandibuzz", PokeType::Dark, PokeType::Flying);
      add_pokemon(631, "Heatmor", PokeType::Fire);
      add_pokemon(632, "Durant", PokeType::Bug, PokeType::Steel);
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(633, "Deino", PokeType::Dark, PokeType::Dragon);
         add_pokemon(634, "Zweilous", PokeType::Dark, PokeType::Dragon);
      }
      if (InclusionFlag::PSEUDOLEGENDARIES & inclusions) {
         add_pokemon(635, "Hydreigon", PokeType::Dark, PokeType::Dragon);
      }
      if (InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(636, "Larvesta", PokeType::Bug, PokeType::Fire);
      }
      add_pokemon(637, "Volcarona", PokeType::Bug, PokeType::Fire);
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(638, "Cobalion", PokeType::Steel, PokeType::Fighting);
         add_pokemon(639, "Terrakion", PokeType::Rock, PokeType::Fighting);
         add_pokemon(640, "Virizion", PokeType::Grass, PokeType::Fighting);
         add_pokemon(641, "Tornadus", PokeType::Flying);
         add_pokemon(642, "Thundurus", PokeType::Electric, PokeType::Flying);
         add_pokemon(643, "Reshiram", PokeType::Dragon, PokeType::Fire);
         add_pokemon(644, "Zekrom", PokeType::Dragon, PokeType::Electric);
         add_pokemon(645, "Landorus", PokeType::Ground, PokeType::Flying);
         add_pokemon(646, "Kyurem", PokeType::Dragon, PokeType::Ice);
         add_pokemon(647, "Keldeo", PokeType::Water, PokeType::Fighting);
         add_pokemon(648, "Meloetta_psychic", PokeType::Normal, PokeType::Psychic);
         add_pokemon(648, "Meloetta_fighting", PokeType::Normal, PokeType::Fighting);
         add_pokemon(649, "Genesect", PokeType::Bug, PokeType::Steel);
      }
   }

   if(RegionsFlag::KALOS & regions) {
      if(InclusionFlag::STARTERS & inclusions) {
         if(InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(650, "Chespin", PokeType::Grass);
            add_pokemon(651, "Quilladin", PokeType::Grass);
         }
         add_pokemon(652, "Chesnaught", PokeType::Grass, PokeType::Fighting);
         if(InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(653, "Fennekin", PokeType::Fire);
            add_pokemon(654, "Braixen", PokeType::Fire);
         }
         add_pokemon(655, "Delphox", PokeType::Fire, PokeType::Psychic);
         if(InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(656, "Froakie", PokeType::Water);
            add_pokemon(657, "Frogadier", PokeType::Water);
         }
         add_pokemon(658, "Greninja", PokeType::Water, PokeType::Dark);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(659, "Bunnelby", PokeType::Normal);
      }
      add_pokemon(660, "Diggersby", PokeType::Normal, PokeType::Ground);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(661, "Fletchling", PokeType::Normal, PokeType::Flying);
         add_pokemon(662, "Fletchinder", PokeType::Fire, PokeType::Flying);
      }
      add_pokemon(663, "Talonflame", PokeType::Fire, PokeType::Flying);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(664, "Scatterbug", PokeType::Bug);
         add_pokemon(665, "Spewpa", PokeType::Bug);
      }
      add_pokemon(666, "Vivillon", PokeType::Bug, PokeType::Flying);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(667, "Litleo", PokeType::Fire, PokeType::Normal);
      }
      add_pokemon(668, "Pyroar", PokeType::Fire, PokeType::Normal);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(669, "Flabebe", PokeType::Fairy);
         add_pokemon(670, "Floette", PokeType::Fairy);
      }
      add_pokemon(671, "Florges", PokeType::Fairy);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(672, "Skiddo", PokeType::Grass);
      }
      add_pokemon(673, "Gogoat", PokeType::Grass);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(674, "Pancham", PokeType::Fighting);
      }
      add_pokemon(675, "Pangoro", PokeType::Fighting, PokeType::Dark);
      add_pokemon(676, "Furfrou", PokeType::Normal);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(677, "Espurr", PokeType::Psychic);
      }
      add_pokemon(678, "Meowstic", PokeType::Psychic);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(679, "Honedge", PokeType::Steel, PokeType::Ghost);
         add_pokemon(680, "Doublade", PokeType::Steel, PokeType::Ghost);
      }
      add_pokemon(681, "Aegislash", PokeType::Steel, PokeType::Ghost);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(682, "Spritzee", PokeType::Fairy);
      }
      add_pokemon(683, "Aromatisse", PokeType::Fairy);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(684, "Swirlix", PokeType::Fairy);
      }
      add_pokemon(685, "Slurpuff", PokeType::Fairy);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(686, "Inkay", PokeType::Dark, PokeType::Psychic);
      }
      add_pokemon(687, "Malamar", PokeType::Dark, PokeType::Psychic);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(688, "Binacle", PokeType::Rock, PokeType::Water);
      }
      add_pokemon(689, "Barbaracle", PokeType::Rock, PokeType::Water);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(690, "Skrelp", PokeType::Poison, PokeType::Water);
      }
      add_pokemon(691, "Dragalge", PokeType::Poison, PokeType::Dragon);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(692, "Clauncher", PokeType::Water);
      }
      add_pokemon(693, "Clawitzer", PokeType::Water);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(694, "Helioptile", PokeType::Electric, PokeType::Normal);
      }
      add_pokemon(695, "Heliolisk", PokeType::Electric, PokeType::Normal);
      if(InclusionFlag::FOSSILS & inclusions) {
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(696, "Tyrunt", PokeType::Rock, PokeType::Dragon);
         }
         add_pokemon(697, "Tyrantrum", PokeType::Rock, PokeType::Dragon);
         if (InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(698, "Amaura", PokeType::Rock, PokeType::Ice);
         }
         add_pokemon(699, "Aurorus", PokeType::Rock, PokeType::Ice);
      }
      add_pokemon(700, "Sylveon", PokeType::Fairy);
      add_pokemon(701, "Hawlucha", PokeType::Fighting, PokeType::Flying);
      add_pokemon(702, "Dedenne", PokeType::Electric, PokeType::Fairy);
      add_pokemon(703, "Carbink", PokeType::Rock, PokeType::Fairy);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(704, "Goomy", PokeType::Dragon);
         add_pokemon(705, "Sliggoo", PokeType::Dragon);
      }
      if(InclusionFlag::PSEUDOLEGENDARIES & inclusions) {
         add_pokemon(706, "Goodra", PokeType::Dragon);
      }
      add_pokemon(707, "Klefki", PokeType::Steel, PokeType::Fairy);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(708, "Phantump", PokeType::Ghost, PokeType::Grass);
      }
      add_pokemon(709, "Trevenant", PokeType::Ghost, PokeType::Grass);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(710, "Pumpkaboo", PokeType::Ghost, PokeType::Grass);
      }
      add_pokemon(711, "Gourgeist", PokeType::Ghost, PokeType::Grass);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(712, "Bergmite", PokeType::Ice);
      }
      add_pokemon(713, "Avalugg", PokeType::Ice);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(714, "Noibat", PokeType::Flying, PokeType::Dragon);
      }
      add_pokemon(715, "Noivern", PokeType::Flying, PokeType::Dragon);
      if(InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(716, "Xerneas", PokeType::Fairy);
         add_pokemon(717, "Yvetal", PokeType::Dark, PokeType::Flying);
         add_pokemon(718, "Zygarde", PokeType::Dragon, PokeType::Ground);
         add_pokemon(719, "Diancie", PokeType::Rock, PokeType::Fairy);
         add_pokemon(720, "Hoopa_confined", PokeType::Psychic, PokeType::Ghost);
         add_pokemon(720, "Hoopa_unbound", PokeType::Psychic, PokeType::Dark);
         add_pokemon(721, "Volcanion", PokeType::Fire, PokeType::Water);
      }
   }

   extract_representatives();
}