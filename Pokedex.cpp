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
   if (RegionsFlag::KANTO & regions) {
      if (InclusionFlag::STARTERS & inclusions) {
         if(InclusionFlag::PREEVOLUTIONS & inclusions){
            add_pokemon(1, "Bulbasaur", Pokemon::Type::Grass, Pokemon::Type::Poison);
            add_pokemon(2, "Ivysaur", Pokemon::Type::Grass, Pokemon::Type::Poison);
         }
         add_pokemon(3, "Venusaur", Pokemon::Type::Grass, Pokemon::Type::Poison);
         if(InclusionFlag::PREEVOLUTIONS & inclusions){
            add_pokemon(4, "Charmander", Pokemon::Type::Fire);
            add_pokemon(5, "Charmeleon", Pokemon::Type::Fire);
         }
         add_pokemon(6, "Charizard", Pokemon::Type::Fire, Pokemon::Type::Flying);
         if(InclusionFlag::PREEVOLUTIONS & inclusions){
            add_pokemon(7, "Squirtle", Pokemon::Type::Water);
            add_pokemon(8, "Wartortle", Pokemon::Type::Water);
         }
         add_pokemon(9, "Blastoise", Pokemon::Type::Water);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions){
         add_pokemon(10, "Caterpie", Pokemon::Type::Bug);
         add_pokemon(11, "Metapod", Pokemon::Type::Bug);
      }
      add_pokemon(12, "Butterfree", Pokemon::Type::Bug, Pokemon::Type::Flying);
      if(InclusionFlag::PREEVOLUTIONS & inclusions){
         add_pokemon(13, "Weedle", Pokemon::Type::Bug, Pokemon::Type::Poison);
         add_pokemon(14, "Kakuna", Pokemon::Type::Bug, Pokemon::Type::Poison);
      }
      add_pokemon(15, "Beedrill", Pokemon::Type::Bug, Pokemon::Type::Poison);
      if(InclusionFlag::PREEVOLUTIONS & inclusions){
         add_pokemon(16, "Pidgey", Pokemon::Type::Normal, Pokemon::Type::Flying);
         add_pokemon(17, "Pidgeotto", Pokemon::Type::Normal, Pokemon::Type::Flying);
      }
      add_pokemon(18, "Pidgeot", Pokemon::Type::Normal, Pokemon::Type::Flying);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(19, "Rattata", Pokemon::Type::Normal);
      }
      add_pokemon(20, "Raticate", Pokemon::Type::Normal);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(21, "Spearow", Pokemon::Type::Normal, Pokemon::Type::Flying);
      }
      add_pokemon(22, "Fearow", Pokemon::Type::Normal, Pokemon::Type::Flying);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(23, "Ekans", Pokemon::Type::Poison);
      }
      add_pokemon(24, "Arbok", Pokemon::Type::Poison);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(25, "Pikachu", Pokemon::Type::Electric);
      }
      add_pokemon(26, "Raichu", Pokemon::Type::Electric);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(27, "Snadshrew", Pokemon::Type::Ground);
      }
      add_pokemon(28, "Sandlash", Pokemon::Type::Ground);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(29, "Nidoranf_f", Pokemon::Type::Poison);
         add_pokemon(30, "Nidorina", Pokemon::Type::Poison);
      }
      add_pokemon(31, "Nidoqueen", Pokemon::Type::Poison, Pokemon::Type::Ground);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(32, "Nidoranf_m", Pokemon::Type::Poison);
         add_pokemon(33, "Nidorino", Pokemon::Type::Poison);
      }
      add_pokemon(34, "Nidoking", Pokemon::Type::Poison, Pokemon::Type::Ground);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(35, "Clefairy", Pokemon::Type::Fairy);
      }
      add_pokemon(36, "Clefable", Pokemon::Type::Fairy);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(37, "Vulpix", Pokemon::Type::Fire);
      }
      add_pokemon(38, "Ninetales", Pokemon::Type::Fire);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(39, "Jigglypuff", Pokemon::Type::Normal, Pokemon::Type::Fairy);
      }
      add_pokemon(40, "Wiglytuff", Pokemon::Type::Normal, Pokemon::Type::Fairy);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(41, "Zubat", Pokemon::Type::Poison, Pokemon::Type::Flying);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(42, "Golbat", Pokemon::Type::Poison, Pokemon::Type::Flying);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(43, "Oddish", Pokemon::Type::Grass, Pokemon::Type::Poison);
         add_pokemon(44, "Gloom", Pokemon::Type::Grass, Pokemon::Type::Poison);
      }
      add_pokemon(45, "Vileplume", Pokemon::Type::Grass, Pokemon::Type::Poison);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(46, "Paras", Pokemon::Type::Bug, Pokemon::Type::Grass);
      }
      add_pokemon(47, "Parasect", Pokemon::Type::Bug, Pokemon::Type::Grass);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(48, "Venonat", Pokemon::Type::Bug, Pokemon::Type::Poison);
      }
      add_pokemon(49, "Venomoth", Pokemon::Type::Bug, Pokemon::Type::Poison);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(50, "Diglett", Pokemon::Type::Ground);
      }
      add_pokemon(51, "Dugtrio", Pokemon::Type::Ground);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(52, "Meowth", Pokemon::Type::Normal);
      }
      add_pokemon(53, "Persian", Pokemon::Type::Normal);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(54, "Psyduck", Pokemon::Type::Water);
      }
      add_pokemon(55, "Golduck", Pokemon::Type::Water);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(56, "Mankey", Pokemon::Type::Fighting);
      }
      add_pokemon(57, "Primeape", Pokemon::Type::Fighting);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(58, "Growlithe", Pokemon::Type::Fire);
      }
      add_pokemon(59, "Arcanine", Pokemon::Type::Fire);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(60, "Poliwag", Pokemon::Type::Water);
         add_pokemon(61, "Poliwhirl", Pokemon::Type::Water);
      }
      add_pokemon(62, "Poliwrath", Pokemon::Type::Water, Pokemon::Type::Fighting);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(63, "Abra", Pokemon::Type::Psychic);
         add_pokemon(64, "Kadabra", Pokemon::Type::Psychic);
      }
      add_pokemon(65, "Alakazam", Pokemon::Type::Psychic);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(66, "Machop", Pokemon::Type::Fighting);
         add_pokemon(67, "Machoke", Pokemon::Type::Fighting);
      }
      add_pokemon(68, "Machamp", Pokemon::Type::Fighting);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(69, "Bellsprout", Pokemon::Type::Grass, Pokemon::Type::Poison);
         add_pokemon(70, "Weepinbell", Pokemon::Type::Grass, Pokemon::Type::Poison);
      }
      add_pokemon(71, "Victribel", Pokemon::Type::Grass, Pokemon::Type::Poison);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(72, "Tentacool", Pokemon::Type::Water, Pokemon::Type::Poison);
      }
      add_pokemon(73, "Tentacruel", Pokemon::Type::Water, Pokemon::Type::Poison);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(74, "Geodude", Pokemon::Type::Rock, Pokemon::Type::Ground);
         add_pokemon(75, "Graveler", Pokemon::Type::Rock, Pokemon::Type::Ground);
      }
      add_pokemon(76, "Golem", Pokemon::Type::Rock, Pokemon::Type::Ground);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(77, "Ponyta", Pokemon::Type::Fire);
      }
      add_pokemon(78, "Rapidash", Pokemon::Type::Fire);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(79, "Slopoke", Pokemon::Type::Water, Pokemon::Type::Psychic);
      }
      add_pokemon(80, "Slowbro", Pokemon::Type::Water, Pokemon::Type::Psychic);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(81, "Magnemite", Pokemon::Type::Electric, Pokemon::Type::Steel);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(82, "Magneton", Pokemon::Type::Electric, Pokemon::Type::Steel);
      }
      add_pokemon(83, "Farfetch'd", Pokemon::Type::Normal, Pokemon::Type::Flying);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(84, "Doduo", Pokemon::Type::Normal, Pokemon::Type::Flying);
      }
      add_pokemon(85, "Dodrio", Pokemon::Type::Normal, Pokemon::Type::Flying);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(86, "Seel", Pokemon::Type::Water, Pokemon::Type::Ice);
      }
      add_pokemon(87, "Dwegong", Pokemon::Type::Water, Pokemon::Type::Ice);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(88, "Grimer", Pokemon::Type::Poison);
      }
      add_pokemon(89, "Muk", Pokemon::Type::Poison);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(90, "Shellder", Pokemon::Type::Water);
      }
      add_pokemon(91, "Cloyster", Pokemon::Type::Water, Pokemon::Type::Ice);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(92, "Gastly", Pokemon::Type::Ghost, Pokemon::Type::Poison);
         add_pokemon(93, "Haunter", Pokemon::Type::Ghost, Pokemon::Type::Poison);
      }
      add_pokemon(94, "Gengar", Pokemon::Type::Ghost, Pokemon::Type::Poison);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(95, "Onix", Pokemon::Type::Rock, Pokemon::Type::Ground);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(98, "Drowzee", Pokemon::Type::Psychic);
      }
      add_pokemon(97, "Hypno", Pokemon::Type::Psychic);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(98, "Krabby", Pokemon::Type::Water);
      }
      add_pokemon(99, "Kingler", Pokemon::Type::Water);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(100, "Voltorb", Pokemon::Type::Electric);
      }
      add_pokemon(101, "Electrode", Pokemon::Type::Electric);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(102, "Exeggcute", Pokemon::Type::Grass, Pokemon::Type::Psychic);
      }
      add_pokemon(103, "Exeggutor", Pokemon::Type::Grass, Pokemon::Type::Psychic);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(104, "Cubone", Pokemon::Type::Ground);
      }
      add_pokemon(105, "Marowak", Pokemon::Type::Ground);
      add_pokemon(106, "Hitmonlee", Pokemon::Type::Fighting);
      add_pokemon(107, "Hitmonchan", Pokemon::Type::Fighting);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(108, "Lickitung", Pokemon::Type::Normal);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(109, "Koffing", Pokemon::Type::Poison);
      }
      add_pokemon(110, "Weezing", Pokemon::Type::Poison);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(111, "Rhyhorn", Pokemon::Type::Ground, Pokemon::Type::Rock);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(112, "Rhydon", Pokemon::Type::Ground, Pokemon::Type::Rock);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(113, "Chansey", Pokemon::Type::Normal);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(114, "Tangela", Pokemon::Type::Grass);
      }
      add_pokemon(115, "Kangaskhan", Pokemon::Type::Normal);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(116, "Horsea", Pokemon::Type::Water);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(117, "Seadra", Pokemon::Type::Water);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(118, "Goldeen", Pokemon::Type::Water);
      }
      add_pokemon(119, "Seaking", Pokemon::Type::Water);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(120, "Staryu", Pokemon::Type::Water);
      }
      add_pokemon(121, "Starmie", Pokemon::Type::Water, Pokemon::Type::Psychic);
      add_pokemon(122, "Mr.Mime", Pokemon::Type::Psychic, Pokemon::Type::Fairy);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::JOHTO & regions)) {
         add_pokemon(123, "Scyther", Pokemon::Type::Bug, Pokemon::Type::Flying);
      }
      add_pokemon(124, "Jynx", Pokemon::Type::Ice, Pokemon::Type::Psychic);

      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(125, "Electabuzz", Pokemon::Type::Electric);
         add_pokemon(126, "Magmar", Pokemon::Type::Fire);
      }
      add_pokemon(127, "Pinsir", Pokemon::Type::Bug);
      add_pokemon(128, "Tauros", Pokemon::Type::Normal);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(129, "Magikarp", Pokemon::Type::Water);
      }
      add_pokemon(130, "Gyarados", Pokemon::Type::Water, Pokemon::Type::Flying);
      add_pokemon(131, "Lapras", Pokemon::Type::Water, Pokemon::Type::Ice);
      add_pokemon(132, "Ditto", Pokemon::Type::Normal);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(133, "Eevee", Pokemon::Type::Normal);
      }
      add_pokemon(134, "Vaporeon", Pokemon::Type::Water);
      add_pokemon(135, "Jolteon", Pokemon::Type::Electric);
      add_pokemon(136, "Flareon", Pokemon::Type::Fire);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or
          (not(RegionsFlag::JOHTO & regions) and not(RegionsFlag::SINNOH & regions))) {
         add_pokemon(137, "Porygon", Pokemon::Type::Normal);
      }
      if (InclusionFlag::FOSSILS & inclusions) {
         if(InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(138, "Omanyte", Pokemon::Type::Rock, Pokemon::Type::Water);
         }
         add_pokemon(139, "Omastar", Pokemon::Type::Rock, Pokemon::Type::Water);
         if(InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(140, "Kabuto", Pokemon::Type::Rock, Pokemon::Type::Water);
         }
         add_pokemon(141, "Kabutops", Pokemon::Type::Rock, Pokemon::Type::Water);
         add_pokemon(142, "Aerodactyl", Pokemon::Type::Rock, Pokemon::Type::Flying);
      }
      add_pokemon(143, "Snorlax", Pokemon::Type::Normal);
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(144, "Articuno", Pokemon::Type::Ice, Pokemon::Type::Flying);
         add_pokemon(145, "Zapdos", Pokemon::Type::Electric, Pokemon::Type::Flying);
         add_pokemon(146, "Moltres", Pokemon::Type::Fire, Pokemon::Type::Flying);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(147, "Dratini", Pokemon::Type::Dragon);
         add_pokemon(148, "Dragonair", Pokemon::Type::Dragon);
      }
      if (InclusionFlag::SEMILEGENDARIES & inclusions) {
         add_pokemon(149, "Dragonite", Pokemon::Type::Dragon, Pokemon::Type::Flying);
      }
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(150, "MewTwo", Pokemon::Type::Psychic);
         add_pokemon(151, "Mew", Pokemon::Type::Psychic);
      }
   }

   if (RegionsFlag::JOHTO & regions) {
      if (InclusionFlag::STARTERS & inclusions) {
         if(InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(152, "Chikorita", Pokemon::Type::Grass);
            add_pokemon(153, "Bayleef", Pokemon::Type::Grass);
         }
         add_pokemon(154, "Meganium", Pokemon::Type::Grass);
         if(InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(155, "Cyndaquil", Pokemon::Type::Fire);
            add_pokemon(156, "Quilava", Pokemon::Type::Fire);
         }
         add_pokemon(157, "Typhlosion", Pokemon::Type::Fire);
         if(InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(158, "Totodile", Pokemon::Type::Water);
            add_pokemon(159, "Croconaw", Pokemon::Type::Water);
         }
         add_pokemon(160, "Feraligatr", Pokemon::Type::Water);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(161, "FurrSentretet", Pokemon::Type::Normal);
      }
      add_pokemon(162, "Furret", Pokemon::Type::Normal);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(163, "Hoothoot", Pokemon::Type::Normal, Pokemon::Type::Flying);
      }
      add_pokemon(164, "Noctowl", Pokemon::Type::Normal);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(165, "Ledyba", Pokemon::Type::Bug, Pokemon::Type::Flying);
      }
      add_pokemon(166, "Ledian", Pokemon::Type::Bug, Pokemon::Type::Flying);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(167, "Spinarak", Pokemon::Type::Bug, Pokemon::Type::Poison);
      }
      add_pokemon(168, "Ariados", Pokemon::Type::Bug, Pokemon::Type::Poison);
      add_pokemon(169, "Crobat", Pokemon::Type::Poison, Pokemon::Type::Flying);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(170, "Chinchou", Pokemon::Type::Water, Pokemon::Type::Electric);
      }
      add_pokemon(171, "Lanturn", Pokemon::Type::Water, Pokemon::Type::Electric);
      if((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::KANTO & regions)) {
         add_pokemon(172, "Pichu", Pokemon::Type::Electric);
         add_pokemon(173, "Cleffa", Pokemon::Type::Fairy);
         add_pokemon(174, "Igglybuff", Pokemon::Type::Normal, Pokemon::Type::Fairy);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(175, "Togepi", Pokemon::Type::Fairy);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(176, "Togetic", Pokemon::Type::Fairy, Pokemon::Type::Flying);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(177, "Natu", Pokemon::Type::Psychic, Pokemon::Type::Flying);
      }
      add_pokemon(178, "Xatu", Pokemon::Type::Psychic, Pokemon::Type::Flying);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(179, "Mareep", Pokemon::Type::Electric);
         add_pokemon(180, "Flaffa", Pokemon::Type::Electric);
      }
      add_pokemon(181, "Ampharos", Pokemon::Type::Electric);
      add_pokemon(182, "Bellossom", Pokemon::Type::Grass);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(183, "Marill", Pokemon::Type::Water, Pokemon::Type::Fairy);
      }
      add_pokemon(184, "Azumarill", Pokemon::Type::Water, Pokemon::Type::Fairy);
      add_pokemon(185, "Sudowoodo", Pokemon::Type::Rock);
      add_pokemon(186, "Politoed", Pokemon::Type::Water);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(187, "Hippip", Pokemon::Type::Grass, Pokemon::Type::Flying);
         add_pokemon(188, "Skiploom", Pokemon::Type::Grass, Pokemon::Type::Flying);
      }
      add_pokemon(189, "Jumpluff", Pokemon::Type::Grass, Pokemon::Type::Flying);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(190, "Aipom", Pokemon::Type::Normal);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(191, "Sunkern", Pokemon::Type::Grass);
      }
      add_pokemon(192, "Sunflora", Pokemon::Type::Grass);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(193, "Yanma", Pokemon::Type::Bug, Pokemon::Type::Flying);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(194, "Wooper", Pokemon::Type::Water, Pokemon::Type::Ground);
      }
      add_pokemon(195, "Quagsire", Pokemon::Type::Water, Pokemon::Type::Ground);
      add_pokemon(196, "Espeon", Pokemon::Type::Psychic);
      add_pokemon(197, "Umbreon", Pokemon::Type::Dark);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(198, "Murkrow", Pokemon::Type::Dark, Pokemon::Type::Flying);
      }
      add_pokemon(199, "Slowking", Pokemon::Type::Water, Pokemon::Type::Psychic);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(200, "Misdreavus", Pokemon::Type::Ghost);
      }
      add_pokemon(201, "Unown", Pokemon::Type::Psychic);
      add_pokemon(202, "Wobbuffet", Pokemon::Type::Psychic);
      add_pokemon(203, "Girafing", Pokemon::Type::Normal, Pokemon::Type::Psychic);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(204, "Pineco", Pokemon::Type::Bug);
      }
      add_pokemon(205, "Forrtress", Pokemon::Type::Bug, Pokemon::Type::Steel);
      add_pokemon(206, "Dunsparce", Pokemon::Type::Normal);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(207, "Gligar", Pokemon::Type::Ground, Pokemon::Type::Flying);
      }
      add_pokemon(208, "Steelix", Pokemon::Type::Steel, Pokemon::Type::Ground);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(209, "Snubbull", Pokemon::Type::Fairy);
      }
      add_pokemon(210, "Granbull", Pokemon::Type::Fairy);
      add_pokemon(211, "Qwilfish", Pokemon::Type::Water, Pokemon::Type::Poison);
      add_pokemon(212, "Scizor", Pokemon::Type::Bug, Pokemon::Type::Steel);
      add_pokemon(213, "Shuckle", Pokemon::Type::Bug, Pokemon::Type::Rock);
      add_pokemon(214, "Heracross", Pokemon::Type::Bug, Pokemon::Type::Fighting);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(215, "Sneasel", Pokemon::Type::Dark, Pokemon::Type::Ice);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(216, "Teddiursa", Pokemon::Type::Normal);
      }
      add_pokemon(217, "Ursaring", Pokemon::Type::Normal);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(218, "Slugma", Pokemon::Type::Fire);
      }
      add_pokemon(219, "Magcargo", Pokemon::Type::Fire, Pokemon::Type::Rock);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(220, "Swinub", Pokemon::Type::Ice, Pokemon::Type::Ground);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(221, "Piloswine", Pokemon::Type::Ice, Pokemon::Type::Ground);
      }
      add_pokemon(222, "Corsola", Pokemon::Type::Water, Pokemon::Type::Rock);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(223, "Remoraid", Pokemon::Type::Water);
      }
      add_pokemon(224, "Octillery", Pokemon::Type::Water);
      add_pokemon(225, "Delibird", Pokemon::Type::Ice, Pokemon::Type::Flying);
      add_pokemon(226, "Mantine", Pokemon::Type::Water, Pokemon::Type::Flying);
      add_pokemon(227, "Skarmory", Pokemon::Type::Steel, Pokemon::Type::Flying);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(228, "Houndour", Pokemon::Type::Dark, Pokemon::Type::Fire);
      }
      add_pokemon(229, "Houndoom", Pokemon::Type::Dark, Pokemon::Type::Fire);
      add_pokemon(230, "Kingdra", Pokemon::Type::Water, Pokemon::Type::Dragon);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(231, "Phanpy", Pokemon::Type::Ground);
      }
      add_pokemon(232, "Donphan", Pokemon::Type::Ground);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(233, "Porygon2", Pokemon::Type::Normal);
      }
      add_pokemon(234, "Stantler", Pokemon::Type::Normal);
      add_pokemon(235, "Smeargle", Pokemon::Type::Normal);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(236, "Tyrogue", Pokemon::Type::Fighting);
      }
      add_pokemon(237, "Hitmontop", Pokemon::Type::Fighting);
      if((InclusionFlag::PREEVOLUTIONS & inclusions) or not (RegionsFlag::KANTO & regions)) {
         add_pokemon(238, "Smoochum", Pokemon::Type::Ice, Pokemon::Type::Psychic);
         add_pokemon(239, "Elekid", Pokemon::Type::Electric);
         add_pokemon(240, "Magby", Pokemon::Type::Fire);
      }
      add_pokemon(241, "Miltank", Pokemon::Type::Normal);
      add_pokemon(242, "Blissey", Pokemon::Type::Normal);
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(243, "Raikou", Pokemon::Type::Electric);
         add_pokemon(244, "Entei", Pokemon::Type::Fire);
         add_pokemon(245, "Suicune", Pokemon::Type::Water);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(246, "Larvitar", Pokemon::Type::Rock, Pokemon::Type::Dark);
         add_pokemon(247, "Pupitar", Pokemon::Type::Rock, Pokemon::Type::Dark);
      }
      if (InclusionFlag::SEMILEGENDARIES & inclusions) {
         add_pokemon(248, "Tyranitar", Pokemon::Type::Rock, Pokemon::Type::Dark);
      }
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(249, "Lugia", Pokemon::Type::Psychic, Pokemon::Type::Flying);
         add_pokemon(250, "Ho-Oh", Pokemon::Type::Fire, Pokemon::Type::Flying);
         add_pokemon(251, "Celebi", Pokemon::Type::Psychic, Pokemon::Type::Grass);
      }
   }

   if (RegionsFlag::HOENN & regions) {
      if (InclusionFlag::STARTERS & inclusions) {
         if(InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(252, "Treecko", Pokemon::Type::Grass);
            add_pokemon(253, "Grovyle", Pokemon::Type::Grass);
         }
         add_pokemon(254, "Sceptile", Pokemon::Type::Grass);
         if(InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(255, "Torchic", Pokemon::Type::Fire);
            add_pokemon(256, "Combusken", Pokemon::Type::Fire, Pokemon::Type::Fighting);
         }
         add_pokemon(257, "Blanziken", Pokemon::Type::Fire, Pokemon::Type::Fighting);
         if(InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(258, "Mudkip", Pokemon::Type::Water);
            add_pokemon(259, "Marshtomp", Pokemon::Type::Water, Pokemon::Type::Ground);
         }
         add_pokemon(260, "Swampert", Pokemon::Type::Water, Pokemon::Type::Ground);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(261, "Poochyena", Pokemon::Type::Dark);
      }
      add_pokemon(262, "Mightyena", Pokemon::Type::Dark);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(263, "Zigzagoon", Pokemon::Type::Normal);
      }
      add_pokemon(264, "Linoone", Pokemon::Type::Normal);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(265, "Wurmple", Pokemon::Type::Bug);
         add_pokemon(266, "Silcoon", Pokemon::Type::Bug);
      }
      add_pokemon(267, "Beautifly", Pokemon::Type::Bug, Pokemon::Type::Flying);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(268, "Cascoon", Pokemon::Type::Bug);
      }
      add_pokemon(269, "Dustox", Pokemon::Type::Bug, Pokemon::Type::Poison);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(270, "Lotad", Pokemon::Type::Water, Pokemon::Type::Grass);
         add_pokemon(271, "Lombre", Pokemon::Type::Water, Pokemon::Type::Grass);
      }
      add_pokemon(272, "Ludicolo", Pokemon::Type::Water, Pokemon::Type::Grass);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(273, "Seedot", Pokemon::Type::Grass);
         add_pokemon(274, "Nuzleaf", Pokemon::Type::Grass, Pokemon::Type::Dark);
      }
      add_pokemon(275, "Shiftry", Pokemon::Type::Grass, Pokemon::Type::Dark);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(276, "Taillow", Pokemon::Type::Normal, Pokemon::Type::Flying);
      }
      add_pokemon(277, "Swellow", Pokemon::Type::Normal, Pokemon::Type::Flying);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(278, "Wingull", Pokemon::Type::Water, Pokemon::Type::Flying);
      }
      add_pokemon(279, "Pelipper", Pokemon::Type::Water, Pokemon::Type::Flying);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(280, "Ralts", Pokemon::Type::Psychic, Pokemon::Type::Fairy);
         add_pokemon(281, "Kirlia", Pokemon::Type::Psychic, Pokemon::Type::Fairy);
      }
      add_pokemon(282, "Gardevoir", Pokemon::Type::Psychic, Pokemon::Type::Fairy);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(283, "Surskit", Pokemon::Type::Bug, Pokemon::Type::Water);
      }
      add_pokemon(284, "Masquerain", Pokemon::Type::Bug, Pokemon::Type::Flying);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(285, "Shroomish", Pokemon::Type::Grass);
      }
      add_pokemon(286, "Breloom", Pokemon::Type::Grass, Pokemon::Type::Fighting);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(287, "Slakoth", Pokemon::Type::Normal);
         add_pokemon(288, "Vigoroth", Pokemon::Type::Normal);
      }
      add_pokemon(289, "Slaking", Pokemon::Type::Normal);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(290, "Nincada", Pokemon::Type::Bug, Pokemon::Type::Ground);
      }
      add_pokemon(291, "Ninjask", Pokemon::Type::Bug, Pokemon::Type::Flying);
      add_pokemon(292, "Shedinja", Pokemon::Type::Bug, Pokemon::Type::Ghost);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(293, "Whismur", Pokemon::Type::Normal);
         add_pokemon(294, "Loudred", Pokemon::Type::Normal);
      }
      add_pokemon(295, "Exploud", Pokemon::Type::Normal);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(296, "Makuhita", Pokemon::Type::Fighting);
      }
      add_pokemon(297, "Hariyama", Pokemon::Type::Fighting);
      if((InclusionFlag::PREEVOLUTIONS & inclusions) or not (RegionsFlag::JOHTO & regions)) {
         add_pokemon(298, "Azurill", Pokemon::Type::Normal, Pokemon::Type::Fairy);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(299, "Nosepass", Pokemon::Type::Rock);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(300, "Skitty", Pokemon::Type::Normal);
      }
      add_pokemon(301, "Delcatty", Pokemon::Type::Normal);
      add_pokemon(302, "Sableye", Pokemon::Type::Dark, Pokemon::Type::Ghost);
      add_pokemon(303, "Mawile", Pokemon::Type::Steel, Pokemon::Type::Fairy);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(304, "Aron", Pokemon::Type::Steel, Pokemon::Type::Rock);
         add_pokemon(305, "Aggron", Pokemon::Type::Steel, Pokemon::Type::Rock);
      }
      add_pokemon(306, "Aggron", Pokemon::Type::Steel, Pokemon::Type::Rock);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(307, "Meditite", Pokemon::Type::Fighting, Pokemon::Type::Psychic);
      }
      add_pokemon(308, "Medicham", Pokemon::Type::Fighting, Pokemon::Type::Psychic);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(309, "Electrike", Pokemon::Type::Electric);
      }
      add_pokemon(310, "Manectric", Pokemon::Type::Electric);
      add_pokemon(311, "Pluse", Pokemon::Type::Electric);
      add_pokemon(312, "Minun", Pokemon::Type::Electric);
      add_pokemon(313, "Volbeat", Pokemon::Type::Bug);
      add_pokemon(314, "Illumise", Pokemon::Type::Bug);
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(315, "Roselia", Pokemon::Type::Grass, Pokemon::Type::Poison);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(316, "Gulpin", Pokemon::Type::Poison);
      }
      add_pokemon(317, "Swalot", Pokemon::Type::Poison);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(318, "Carvanha", Pokemon::Type::Water, Pokemon::Type::Dark);
      }
      add_pokemon(319, "Sharpedo", Pokemon::Type::Water, Pokemon::Type::Dark);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(320, "Wailmer", Pokemon::Type::Water);
      }
      add_pokemon(321, "Wailord", Pokemon::Type::Water);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(322, "Numel", Pokemon::Type::Fire, Pokemon::Type::Ground);
      }
      add_pokemon(323, "Camerupt", Pokemon::Type::Fire, Pokemon::Type::Ground);
      add_pokemon(324, "Torkoal", Pokemon::Type::Fire);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(325, "Spoink", Pokemon::Type::Psychic);
      }
      add_pokemon(326, "Grumping", Pokemon::Type::Psychic);
      add_pokemon(327, "Spinda", Pokemon::Type::Normal);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(328, "Trapinch", Pokemon::Type::Ground);
         add_pokemon(329, "Vibrava", Pokemon::Type::Ground, Pokemon::Type::Dragon);
      }
      add_pokemon(330, "Flygon", Pokemon::Type::Ground, Pokemon::Type::Dragon);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(331, "Cacnea", Pokemon::Type::Grass);
      }
      add_pokemon(332, "Cacturne", Pokemon::Type::Grass, Pokemon::Type::Dark);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(333, "Swablu", Pokemon::Type::Normal, Pokemon::Type::Flying);
      }
      add_pokemon(334, "Altaria", Pokemon::Type::Dragon, Pokemon::Type::Flying);
      add_pokemon(335, "Zangoose", Pokemon::Type::Normal);
      add_pokemon(336, "Seviper", Pokemon::Type::Poison);
      add_pokemon(337, "Lunatone", Pokemon::Type::Rock, Pokemon::Type::Psychic);
      add_pokemon(338, "Solrock", Pokemon::Type::Rock, Pokemon::Type::Psychic);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(339, "Barboach", Pokemon::Type::Water, Pokemon::Type::Ground);
      }
      add_pokemon(340, "Whiscash", Pokemon::Type::Water, Pokemon::Type::Ground);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(341, "Corphish", Pokemon::Type::Water);
      }
      add_pokemon(342, "Crawdaunt", Pokemon::Type::Water, Pokemon::Type::Dark);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(343, "Baltoy", Pokemon::Type::Ground, Pokemon::Type::Psychic);
      }
      add_pokemon(344, "Claydol", Pokemon::Type::Ground, Pokemon::Type::Psychic);
      if (InclusionFlag::FOSSILS & inclusions) {
         if(InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(345, "Lileep", Pokemon::Type::Rock, Pokemon::Type::Grass);
         }
         add_pokemon(346, "Cradily", Pokemon::Type::Rock, Pokemon::Type::Grass);
         if(InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(347, "Anorith", Pokemon::Type::Rock, Pokemon::Type::Bug);
         }
         add_pokemon(348, "Armaldo", Pokemon::Type::Rock, Pokemon::Type::Bug);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(349, "Feebas", Pokemon::Type::Water);
      }
      add_pokemon(350, "Milotic", Pokemon::Type::Water);
      add_pokemon(351, "Castform", Pokemon::Type::Normal);
      add_pokemon(352, "Keckleon", Pokemon::Type::Normal);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(353, "Shuppet", Pokemon::Type::Ghost);
      }
      add_pokemon(354, "Banette", Pokemon::Type::Ghost);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(355, "Duskull", Pokemon::Type::Ghost);
      }
      if ((InclusionFlag::PREEVOLUTIONS & inclusions) or not(RegionsFlag::SINNOH & regions)) {
         add_pokemon(356, "Dusclops", Pokemon::Type::Ghost);
      }
      add_pokemon(357, "Tropius", Pokemon::Type::Grass, Pokemon::Type::Flying);
      add_pokemon(358, "Chimecho", Pokemon::Type::Psychic);
      add_pokemon(359, "Absol", Pokemon::Type::Dark);
      add_pokemon(360, "Wynaut", Pokemon::Type::Psychic);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(361, "Snorunt", Pokemon::Type::Ice);
      }
      add_pokemon(362, "Glalie", Pokemon::Type::Ice);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(363, "Spheal", Pokemon::Type::Ice, Pokemon::Type::Water);
         add_pokemon(364, "Sealeo", Pokemon::Type::Ice, Pokemon::Type::Water);
      }
      add_pokemon(365, "Walrein", Pokemon::Type::Ice, Pokemon::Type::Water);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(366, "Clamperl", Pokemon::Type::Water);
      }
      add_pokemon(367, "Huntail", Pokemon::Type::Water);
      add_pokemon(368, "Gorebyss", Pokemon::Type::Water);
      add_pokemon(369, "Relicanth", Pokemon::Type::Water, Pokemon::Type::Rock);
      add_pokemon(370, "Luvdisc", Pokemon::Type::Water);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(371, "Bagon", Pokemon::Type::Dragon);
         add_pokemon(372, "Shelgon", Pokemon::Type::Dragon);
      }
      if (InclusionFlag::SEMILEGENDARIES & inclusions) {
         add_pokemon(373, "Salamence", Pokemon::Type::Dragon, Pokemon::Type::Flying);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(374, "Beldum", Pokemon::Type::Steel, Pokemon::Type::Psychic);
         add_pokemon(375, "Metang", Pokemon::Type::Steel, Pokemon::Type::Psychic);
      }
      if (InclusionFlag::SEMILEGENDARIES & inclusions) {
         add_pokemon(376, "Metagross", Pokemon::Type::Steel, Pokemon::Type::Psychic);
      }
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(377, "Regirock", Pokemon::Type::Rock);
         add_pokemon(378, "Regice", Pokemon::Type::Ice);
         add_pokemon(379, "Registeel", Pokemon::Type::Steel);
         add_pokemon(380, "Latias", Pokemon::Type::Dragon, Pokemon::Type::Psychic);
         add_pokemon(381, "Latios", Pokemon::Type::Dragon, Pokemon::Type::Psychic);
         add_pokemon(382, "Kyogre", Pokemon::Type::Water);
         add_pokemon(383, "Groudon", Pokemon::Type::Ground);
         add_pokemon(384, "Rayquaza", Pokemon::Type::Dragon, Pokemon::Type::Flying);
         add_pokemon(385, "Jirachi", Pokemon::Type::Steel, Pokemon::Type::Psychic);
         add_pokemon(386, "Deoxys", Pokemon::Type::Psychic);
      }
   }

   if (RegionsFlag::SINNOH & regions) {
      if (InclusionFlag::STARTERS & inclusions) {
         if(InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(387, "Turtwig", Pokemon::Type::Grass);
            add_pokemon(388, "Grotle", Pokemon::Type::Grass);
         }
         add_pokemon(389, "Torterra", Pokemon::Type::Grass, Pokemon::Type::Ground);
         if(InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(390, "Chimchar", Pokemon::Type::Fire);
            add_pokemon(391, "Monferno", Pokemon::Type::Fire, Pokemon::Type::Fighting);
         }
         add_pokemon(392, "Infernape", Pokemon::Type::Fire, Pokemon::Type::Fighting);
         if(InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(393, "Piplup", Pokemon::Type::Water);
            add_pokemon(394, "Prinplup", Pokemon::Type::Water);
         }
         add_pokemon(395, "Empoleon", Pokemon::Type::Water, Pokemon::Type::Steel);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(396, "Starly", Pokemon::Type::Normal, Pokemon::Type::Flying);
         add_pokemon(397, "Starvia", Pokemon::Type::Normal, Pokemon::Type::Flying);
      }
      add_pokemon(398, "Staraptor", Pokemon::Type::Normal, Pokemon::Type::Flying);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(399, "Bidoof", Pokemon::Type::Normal);
      }
      add_pokemon(400, "Bibarel", Pokemon::Type::Normal, Pokemon::Type::Water);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(401, "Kricketot", Pokemon::Type::Bug);
      }
      add_pokemon(402, "Kricketune", Pokemon::Type::Bug);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(403, "Shinx", Pokemon::Type::Electric);
         add_pokemon(404, "Luxio", Pokemon::Type::Electric);
      }
      add_pokemon(405, "Luxray", Pokemon::Type::Electric);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(406, "Budew", Pokemon::Type::Grass, Pokemon::Type::Poison);
      }
      add_pokemon(407, "Roserade", Pokemon::Type::Grass, Pokemon::Type::Poison);
      if (InclusionFlag::FOSSILS & inclusions) {
         if(InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(408, "Cranidos", Pokemon::Type::Rock);
         }
         add_pokemon(409, "Rampardos", Pokemon::Type::Rock);
         if(InclusionFlag::PREEVOLUTIONS & inclusions) {
            add_pokemon(410, "Shieldon", Pokemon::Type::Rock, Pokemon::Type::Steel);
         }
         add_pokemon(411, "Bastiadon", Pokemon::Type::Rock, Pokemon::Type::Steel);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(412, "Burmy", Pokemon::Type::Bug);
      }
      add_pokemon(413, "Wormadam_grass", Pokemon::Type::Bug, Pokemon::Type::Grass);
      add_pokemon(413, "Wormadam_ground", Pokemon::Type::Bug, Pokemon::Type::Ground);
      add_pokemon(413, "Wormadam_steel", Pokemon::Type::Bug, Pokemon::Type::Steel);
      add_pokemon(414, "Mothim", Pokemon::Type::Bug, Pokemon::Type::Flying);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(415, "Combee", Pokemon::Type::Bug, Pokemon::Type::Flying);
      }
      add_pokemon(416, "Vespiquen", Pokemon::Type::Bug, Pokemon::Type::Flying);
      add_pokemon(417, "Pachirisu", Pokemon::Type::Electric);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(418, "Buizel", Pokemon::Type::Water);
      }
      add_pokemon(419, "Floatzel", Pokemon::Type::Water);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(420, "Cherubi", Pokemon::Type::Grass);
      }
      add_pokemon(421, "Cherrim", Pokemon::Type::Grass);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(422, "Shellos", Pokemon::Type::Water);
      }
      add_pokemon(423, "Gastrodon", Pokemon::Type::Water, Pokemon::Type::Ground);
      add_pokemon(424, "Ambipom", Pokemon::Type::Normal);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(425, "Drifloon", Pokemon::Type::Ghost, Pokemon::Type::Flying);
      }
      add_pokemon(426, "Drifblim", Pokemon::Type::Ghost, Pokemon::Type::Flying);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(427, "Buneary", Pokemon::Type::Normal);
      }
      add_pokemon(428, "Lopunny", Pokemon::Type::Normal, Pokemon::Type::Fighting);
      add_pokemon(429, "Mismagius", Pokemon::Type::Ghost);
      add_pokemon(430, "Honchkrow", Pokemon::Type::Dark, Pokemon::Type::Flying);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(431, "Glameow", Pokemon::Type::Normal);
      }
      add_pokemon(432, "Perugly", Pokemon::Type::Normal);

      if((InclusionFlag::PREEVOLUTIONS & inclusions) or not (RegionsFlag::HOENN & regions)) {
         add_pokemon(433, "Chingling", Pokemon::Type::Psychic);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(434, "Skuntank", Pokemon::Type::Poison, Pokemon::Type::Dark);
      }
      add_pokemon(435, "Skuntank", Pokemon::Type::Poison, Pokemon::Type::Dark);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(436, "Bronzor", Pokemon::Type::Steel, Pokemon::Type::Psychic);
      }
      add_pokemon(437, "Bronzong", Pokemon::Type::Steel, Pokemon::Type::Psychic);
      if((InclusionFlag::PREEVOLUTIONS & inclusions) or not (RegionsFlag::JOHTO & regions)) {
         add_pokemon(438, "Bonsly", Pokemon::Type::Rock);
      }
      if((InclusionFlag::PREEVOLUTIONS & inclusions) or not (RegionsFlag::KANTO & regions)) {
         add_pokemon(439, "MimeJr.", Pokemon::Type::Psychic, Pokemon::Type::Fairy);
         add_pokemon(440, "Happiny", Pokemon::Type::Normal);
      }
      add_pokemon(441, "Chatot", Pokemon::Type::Normal, Pokemon::Type::Flying);
      add_pokemon(442, "Spiritomb", Pokemon::Type::Ghost, Pokemon::Type::Dark);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(443, "Gible", Pokemon::Type::Dragon, Pokemon::Type::Ground);
         add_pokemon(444, "Babite", Pokemon::Type::Dragon, Pokemon::Type::Ground);
      }
      if (InclusionFlag::SEMILEGENDARIES & inclusions) {
         add_pokemon(445, "Garchomp", Pokemon::Type::Dragon, Pokemon::Type::Ground);
      }
      if((InclusionFlag::PREEVOLUTIONS & inclusions) or not (RegionsFlag::KANTO & regions)) {
         add_pokemon(446, "Munchlax", Pokemon::Type::Normal);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(447, "Riolu", Pokemon::Type::Fighting);
      }
      add_pokemon(448, "Lucario", Pokemon::Type::Fighting, Pokemon::Type::Steel);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(449, "Hippopotas", Pokemon::Type::Ground);
      }
      add_pokemon(450, "Hippowdon", Pokemon::Type::Ground);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(451, "Skorupi", Pokemon::Type::Poison, Pokemon::Type::Bug);
      }
      add_pokemon(452, "Drapion", Pokemon::Type::Poison, Pokemon::Type::Dark);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(453, "Croagunk", Pokemon::Type::Poison, Pokemon::Type::Fighting);
      }
      add_pokemon(454, "Toxicroak", Pokemon::Type::Poison, Pokemon::Type::Fighting);
      add_pokemon(455, "Carnivine", Pokemon::Type::Grass);
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(456, "Finneon", Pokemon::Type::Water);
      }
      add_pokemon(457, "Lumineon", Pokemon::Type::Water);
      if((InclusionFlag::PREEVOLUTIONS & inclusions) or not (RegionsFlag::JOHTO & regions)) {
         add_pokemon(458, "Mantyke", Pokemon::Type::Water, Pokemon::Type::Flying);
      }
      if(InclusionFlag::PREEVOLUTIONS & inclusions) {
         add_pokemon(459, "Snover", Pokemon::Type::Water, Pokemon::Type::Ice);
      }
      add_pokemon(460, "Abomasnow", Pokemon::Type::Grass, Pokemon::Type::Ice);
      add_pokemon(461, "Weavile", Pokemon::Type::Dark, Pokemon::Type::Ice);
      add_pokemon(462, "Magnezone", Pokemon::Type::Electric, Pokemon::Type::Steel);
      add_pokemon(463, "Lickilicky", Pokemon::Type::Normal);
      add_pokemon(464, "Rhyperior", Pokemon::Type::Ground, Pokemon::Type::Rock);
      add_pokemon(465, "Tangrowth", Pokemon::Type::Grass);
      add_pokemon(466, "Electivire", Pokemon::Type::Electric);
      add_pokemon(467, "Magmortar", Pokemon::Type::Fire);
      add_pokemon(468, "Togekiss", Pokemon::Type::Fairy, Pokemon::Type::Flying);
      add_pokemon(469, "Yanmega", Pokemon::Type::Bug, Pokemon::Type::Flying);
      add_pokemon(470, "Leafeon", Pokemon::Type::Grass);
      add_pokemon(471, "Glaceon", Pokemon::Type::Ice);
      add_pokemon(472, "Gliscor", Pokemon::Type::Ground, Pokemon::Type::Flying);
      add_pokemon(473, "Mamoswine", Pokemon::Type::Ice, Pokemon::Type::Ground);
      add_pokemon(474, "Porygon-Z", Pokemon::Type::Normal);
      add_pokemon(475, "Gallade", Pokemon::Type::Psychic, Pokemon::Type::Fighting);
      add_pokemon(476, "Probopass", Pokemon::Type::Rock, Pokemon::Type::Steel);
      add_pokemon(477, "Dusknoir", Pokemon::Type::Ghost);
      add_pokemon(478, "Froslass", Pokemon::Type::Ice, Pokemon::Type::Ghost);
      add_pokemon(479, "Rotom_ghost", Pokemon::Type::Electric, Pokemon::Type::Ghost);
      add_pokemon(479, "Rotom_fire", Pokemon::Type::Electric, Pokemon::Type::Fire);
      add_pokemon(479, "Rotom_water", Pokemon::Type::Electric, Pokemon::Type::Water);
      add_pokemon(479, "Rotom_ice", Pokemon::Type::Electric, Pokemon::Type::Ice);
      add_pokemon(479, "Rotom_flying", Pokemon::Type::Electric, Pokemon::Type::Flying);
      add_pokemon(479, "Rotom_grass", Pokemon::Type::Electric, Pokemon::Type::Grass);
      if (InclusionFlag::LEGENDARIES & inclusions) {
         add_pokemon(480, "Uxie", Pokemon::Type::Psychic);
         add_pokemon(481, "Mesprit", Pokemon::Type::Psychic);
         add_pokemon(482, "Azelf", Pokemon::Type::Psychic);
         add_pokemon(483, "Dialga", Pokemon::Type::Steel, Pokemon::Type::Dragon);
         add_pokemon(484, "Palkia", Pokemon::Type::Water, Pokemon::Type::Dragon);
         add_pokemon(485, "Heatran", Pokemon::Type::Fire, Pokemon::Type::Steel);
         add_pokemon(486, "Regigigas", Pokemon::Type::Normal);
         add_pokemon(487, "Giratina", Pokemon::Type::Ghost, Pokemon::Type::Dragon);
         add_pokemon(488, "Cresselia", Pokemon::Type::Psychic);
         add_pokemon(489, "Phione", Pokemon::Type::Water);
         add_pokemon(490, "Manaphy", Pokemon::Type::Water);
         add_pokemon(491, "Darkrai", Pokemon::Type::Dark);
         add_pokemon(492, "Shaymin", Pokemon::Type::Grass);
         add_pokemon(492, "Shaymin_flying", Pokemon::Type::Grass, Pokemon::Type::Flying);
         add_pokemon(493, "Arceus_normal", Pokemon::Type::Normal);
         add_pokemon(493, "Arceus_fighting", Pokemon::Type::Fighting);
         add_pokemon(493, "Arceus_flying", Pokemon::Type::Flying);
         add_pokemon(493, "Arceus_poison", Pokemon::Type::Poison);
         add_pokemon(493, "Arceus_ground", Pokemon::Type::Ground);
         add_pokemon(493, "Arceus_rock", Pokemon::Type::Rock);
         add_pokemon(493, "Arceus_bug", Pokemon::Type::Bug);
         add_pokemon(493, "Arceus_ghost", Pokemon::Type::Ghost);
         add_pokemon(493, "Arceus_steel", Pokemon::Type::Steel);
         add_pokemon(493, "Arceus_fire", Pokemon::Type::Fire);
         add_pokemon(493, "Arceus_water", Pokemon::Type::Water);
         add_pokemon(493, "Arceus_grass", Pokemon::Type::Grass);
         add_pokemon(493, "Arceus_electric", Pokemon::Type::Electric);
         add_pokemon(493, "Arceus_psychic", Pokemon::Type::Psychic);
         add_pokemon(493, "Arceus_ice", Pokemon::Type::Ice);
         add_pokemon(493, "Arceus_dragon", Pokemon::Type::Dragon);
         add_pokemon(493, "Arceus_dark", Pokemon::Type::Dark);
         add_pokemon(493, "Arceus_fairy", Pokemon::Type::Fairy);
      }
   }

   extract_representatives();
}