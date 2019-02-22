//
// Created by mich on 21/02/19.
//

#include "FindBestTeam.h"

FindBestTeam::FindBestTeam(const std::vector<Pokemon> &fixed_pokemon_, std::vector<PokeTeam> &best_teams_,
                           bool consider_defence_, bool consider_offence_, int filter_factor_,
                           unsigned last_generation_to_include_, bool include_starters_, bool include_ancients_,
                           bool include_semilegendaries_, bool include_legendaries_, bool allow_type_repetitions_)
      :
      _num_fixed_pokemon{static_cast<unsigned>(fixed_pokemon_.size())}, _best_teams{best_teams_},
      _max_score{std::numeric_limits<int>::min()}, _filter_factor{filter_factor_},
      _allow_type_repetitions{allow_type_repetitions_} {
   if (last_generation_to_include_ == 0) {
      throw std::invalid_argument("Should include pokemon of some generation");
   }
   if (last_generation_to_include_ > 4) {
      throw std::invalid_argument("Generations after gen.4 are not implemented yet");
   }
   if (_num_fixed_pokemon > 6) {
      throw std::invalid_argument("Cannot complete at team that already has more than 6 pokemon");
   }

   if (not consider_defence_ and not consider_offence_) {
      throw std::invalid_argument("At least one between consider_defence and consider_offence should be set to true");
   }

   if (consider_defence_ and consider_offence_) {
      _evaluation = &Pokemon::mismatch;
   } else if (consider_defence_) {
      _evaluation = &Pokemon::resistance;
   } else {
      _evaluation = &Pokemon::offensive_effectiveness;
   }

   for (unsigned poke_idx = 0; poke_idx != _num_fixed_pokemon; ++poke_idx) {
      _current_team[poke_idx] = fixed_pokemon_[poke_idx];
      for (unsigned type_idx = 0; type_idx != Pokemon::NUM_TYPES; ++type_idx) {
         _partial_scoring[poke_idx][type_idx] = _evaluation(&_current_team[poke_idx],
                                                            static_cast<Pokemon::Type>(type_idx));
      }
   }

   if (last_generation_to_include_ >= 1) {
      add_kanto_pokedex(_pokedex, include_starters_, include_ancients_, include_semilegendaries_, include_legendaries_);
   }
   if (last_generation_to_include_ >= 2) {
      add_johto_pokedex(_pokedex, include_starters_, include_semilegendaries_, include_legendaries_);
   }
   if (last_generation_to_include_ >= 3) {
      add_hoenn_pokedex(_pokedex, include_starters_, include_ancients_, include_semilegendaries_, include_legendaries_);
   }
   if (last_generation_to_include_ >= 4) {
      add_sinnoh_pokedex(_pokedex, include_starters_, include_ancients_, include_semilegendaries_,
                         include_legendaries_);
   }
   _pokedex.extract_representatives();
}

int FindBestTeam::find_best_teams() {
   find_best_team_loop_iter(_num_fixed_pokemon, 0);
   return _max_score;
}

void FindBestTeam::find_best_team_loop_iter(unsigned already_in_team, unsigned long next_to_try) {
   if (already_in_team > 6) {
      throw std::logic_error("The team already have too many pokemon");
   }
   if (already_in_team == 6) {
      int current_score = 0;
      for (unsigned type_idx = 0; type_idx != Pokemon::NUM_TYPES; ++type_idx) {
         current_score += std::min(_filter_factor, _partial_scoring[5][type_idx]);
      }
      if (current_score == _max_score) {
         _best_teams.emplace_back(_current_team);
      } else if (current_score > _max_score) {
         _max_score = current_score;
         _best_teams = std::vector<PokeTeam>(1, _current_team);
      }
   } else {
      for (unsigned long poke_idx = next_to_try; poke_idx < _pokedex.representatives().size(); ++poke_idx) {
         bool can_use_this_type_pair = true;
         if (not _allow_type_repetitions) {
            for (unsigned in_team_idx = 0; in_team_idx != already_in_team; ++in_team_idx) {
               if (share_type(_current_team[in_team_idx], *_pokedex.representatives()[poke_idx])) {
                  can_use_this_type_pair = false;
                  break;
               }
            }
         }
         if (can_use_this_type_pair) {
            _current_team[already_in_team] = *_pokedex.representatives()[poke_idx];
            for (unsigned int type_idx = 0; type_idx != Pokemon::NUM_TYPES; ++type_idx) {
               int previous_scoring = (already_in_team == 0) ? 0 : _partial_scoring[already_in_team - 1][type_idx];
               _partial_scoring[already_in_team][type_idx] = previous_scoring +
                                                             _evaluation(&_current_team[already_in_team],
                                                                         static_cast<Pokemon::Type>(type_idx));
            }
            find_best_team_loop_iter(already_in_team + 1, poke_idx);
         }
      }
   }
}

void FindBestTeam::add_kanto_pokedex(Pokedex &pokedex, bool include_starters, bool include_ancients,
                                     bool include_semilegendaries, bool include_legendaries) noexcept {
   if (include_starters) {
      pokedex.add_pokemon(3, "Venusaur", Pokemon::Type::Grass, Pokemon::Type::Poison);
      pokedex.add_pokemon(6, "Charizard", Pokemon::Type::Fire, Pokemon::Type::Flying);
      pokedex.add_pokemon(9, "Blastoise", Pokemon::Type::Water);
   }
   pokedex.add_pokemon(12, "Butterfree", Pokemon::Type::Bug, Pokemon::Type::Flying);
   pokedex.add_pokemon(15, "Beedrill", Pokemon::Type::Bug, Pokemon::Type::Poison);
   pokedex.add_pokemon(18, "Pidgeot", Pokemon::Type::Normal, Pokemon::Type::Flying);
   pokedex.add_pokemon(20, "Raticate", Pokemon::Type::Normal);
   pokedex.add_pokemon(22, "Fearow", Pokemon::Type::Normal, Pokemon::Type::Flying);
   pokedex.add_pokemon(24, "Arbok", Pokemon::Type::Poison);
   pokedex.add_pokemon(26, "Raichu", Pokemon::Type::Electric);
   pokedex.add_pokemon(28, "Sandlash", Pokemon::Type::Ground);
   pokedex.add_pokemon(31, "Nidoqueen", Pokemon::Type::Poison, Pokemon::Type::Ground);
   pokedex.add_pokemon(34, "Nidoking", Pokemon::Type::Poison, Pokemon::Type::Ground);
   pokedex.add_pokemon(36, "Clefable", Pokemon::Type::Fairy);
   pokedex.add_pokemon(38, "Ninetales", Pokemon::Type::Fire);
   pokedex.add_pokemon(40, "Wiglytuff", Pokemon::Type::Normal);
   pokedex.add_pokemon(42, "Golbat", Pokemon::Type::Poison, Pokemon::Type::Flying);
   pokedex.add_pokemon(45, "Vileplume", Pokemon::Type::Grass, Pokemon::Type::Poison);
   pokedex.add_pokemon(47, "Parasect", Pokemon::Type::Bug, Pokemon::Type::Grass);
   pokedex.add_pokemon(49, "Venomoth", Pokemon::Type::Bug, Pokemon::Type::Poison);
   pokedex.add_pokemon(51, "Dugtrio", Pokemon::Type::Ground);
   pokedex.add_pokemon(53, "Persian", Pokemon::Type::Normal);
   pokedex.add_pokemon(55, "Golduck", Pokemon::Type::Water);
   pokedex.add_pokemon(57, "Primeape", Pokemon::Type::Fighting);
   pokedex.add_pokemon(59, "Arcanine", Pokemon::Type::Fire);
   pokedex.add_pokemon(62, "Poliwrath", Pokemon::Type::Water, Pokemon::Type::Fighting);
   pokedex.add_pokemon(65, "Alakazam", Pokemon::Type::Psychic);
   pokedex.add_pokemon(68, "Machamp", Pokemon::Type::Fighting);
   pokedex.add_pokemon(71, "Victribel", Pokemon::Type::Grass, Pokemon::Type::Poison);
   pokedex.add_pokemon(73, "Tentacruel", Pokemon::Type::Water, Pokemon::Type::Poison);
   pokedex.add_pokemon(76, "Golem", Pokemon::Type::Rock, Pokemon::Type::Ground);
   pokedex.add_pokemon(78, "Rapidash", Pokemon::Type::Fire);
   pokedex.add_pokemon(80, "Slowbro", Pokemon::Type::Water, Pokemon::Type::Psychic);
   pokedex.add_pokemon(82, "Magneton", Pokemon::Type::Electric, Pokemon::Type::Steel);
   pokedex.add_pokemon(83, "Farfetch'd", Pokemon::Type::Normal, Pokemon::Type::Flying);
   pokedex.add_pokemon(85, "Dodrio", Pokemon::Type::Normal, Pokemon::Type::Flying);
   pokedex.add_pokemon(87, "Dwegong", Pokemon::Type::Water, Pokemon::Type::Ice);
   pokedex.add_pokemon(89, "Muk", Pokemon::Type::Poison);
   pokedex.add_pokemon(91, "Cloyster", Pokemon::Type::Water, Pokemon::Type::Ice);
   pokedex.add_pokemon(94, "Gengar", Pokemon::Type::Ghost, Pokemon::Type::Poison);
   pokedex.add_pokemon(95, "Onix", Pokemon::Type::Rock, Pokemon::Type::Ground);
   pokedex.add_pokemon(97, "Hypno", Pokemon::Type::Psychic);
   pokedex.add_pokemon(99, "Kingler", Pokemon::Type::Water);
   pokedex.add_pokemon(101, "Electrode", Pokemon::Type::Electric);
   pokedex.add_pokemon(103, "Exeggutor", Pokemon::Type::Grass, Pokemon::Type::Psychic);
   pokedex.add_pokemon(105, "Marowak", Pokemon::Type::Ground);
   pokedex.add_pokemon(106, "Hitmonlee", Pokemon::Type::Fighting);
   pokedex.add_pokemon(107, "Hitmonchan", Pokemon::Type::Fighting);
   pokedex.add_pokemon(108, "Lickitung", Pokemon::Type::Normal);
   pokedex.add_pokemon(110, "Weezing", Pokemon::Type::Poison);
   pokedex.add_pokemon(112, "Rhydon", Pokemon::Type::Ground, Pokemon::Type::Rock);
   pokedex.add_pokemon(113, "Chansey", Pokemon::Type::Normal);
   pokedex.add_pokemon(114, "Tangela", Pokemon::Type::Grass);
   pokedex.add_pokemon(115, "Kangaskhan", Pokemon::Type::Normal);
   pokedex.add_pokemon(117, "Seadra", Pokemon::Type::Water);
   pokedex.add_pokemon(119, "Seaking", Pokemon::Type::Water);
   pokedex.add_pokemon(121, "Starmie", Pokemon::Type::Water, Pokemon::Type::Psychic);
   pokedex.add_pokemon(122, "Mr.Mime", Pokemon::Type::Psychic, Pokemon::Type::Fairy);
   pokedex.add_pokemon(123, "Scyther", Pokemon::Type::Bug, Pokemon::Type::Flying);
   pokedex.add_pokemon(124, "Jynx", Pokemon::Type::Ice, Pokemon::Type::Psychic);
   pokedex.add_pokemon(125, "Electabuzz", Pokemon::Type::Electric);
   pokedex.add_pokemon(126, "Magmar", Pokemon::Type::Fire);
   pokedex.add_pokemon(127, "Pinsir", Pokemon::Type::Bug);
   pokedex.add_pokemon(128, "Tauros", Pokemon::Type::Normal);
   pokedex.add_pokemon(130, "Gyarados", Pokemon::Type::Water, Pokemon::Type::Flying);
   pokedex.add_pokemon(131, "Lapras", Pokemon::Type::Water, Pokemon::Type::Ice);
   pokedex.add_pokemon(132, "Ditto", Pokemon::Type::Normal);
   pokedex.add_pokemon(134, "Vaporeon", Pokemon::Type::Water);
   pokedex.add_pokemon(135, "Jolteon", Pokemon::Type::Electric);
   pokedex.add_pokemon(136, "Flareon", Pokemon::Type::Fire);
   pokedex.add_pokemon(137, "Porygon", Pokemon::Type::Normal);
   if (include_ancients) {
      pokedex.add_pokemon(139, "Omastar", Pokemon::Type::Rock, Pokemon::Type::Water);
      pokedex.add_pokemon(141, "Kabutops", Pokemon::Type::Rock, Pokemon::Type::Water);
      pokedex.add_pokemon(142, "Aerodactyl", Pokemon::Type::Rock, Pokemon::Type::Flying);
   }
   pokedex.add_pokemon(143, "Snorlax", Pokemon::Type::Normal);
   if (include_legendaries) {
      pokedex.add_pokemon(144, "Articuno", Pokemon::Type::Ice, Pokemon::Type::Flying);
      pokedex.add_pokemon(145, "Zapdos", Pokemon::Type::Electric, Pokemon::Type::Flying);
      pokedex.add_pokemon(146, "Moltres", Pokemon::Type::Fire, Pokemon::Type::Flying);
   }
   if (include_semilegendaries) {
      pokedex.add_pokemon(149, "Dragonite", Pokemon::Type::Dragon, Pokemon::Type::Flying);
   }
   if (include_legendaries) {
      pokedex.add_pokemon(150, "MewTwo", Pokemon::Type::Psychic);
      pokedex.add_pokemon(151, "Mew", Pokemon::Type::Psychic);
   }
}


void FindBestTeam::add_johto_pokedex(Pokedex &pokedex, bool include_starters,
                                     bool include_semilegendaries, bool include_legendaries) noexcept {
   if (include_starters) {
      pokedex.add_pokemon(154, "Meganium", Pokemon::Type::Grass);
      pokedex.add_pokemon(157, "Typhlosion", Pokemon::Type::Fire);
      pokedex.add_pokemon(160, "Feraligatr", Pokemon::Type::Water);
   }
   pokedex.add_pokemon(162, "Furret", Pokemon::Type::Normal);
   pokedex.add_pokemon(164, "Noctowl", Pokemon::Type::Normal);
   pokedex.add_pokemon(166, "Ledian", Pokemon::Type::Bug, Pokemon::Type::Flying);
   pokedex.add_pokemon(168, "Ariados", Pokemon::Type::Bug, Pokemon::Type::Poison);
   pokedex.remove_pokemon(42, "Golbat", Pokemon::Type::Poison, Pokemon::Type::Flying);
   pokedex.add_pokemon(169, "Crobat", Pokemon::Type::Poison, Pokemon::Type::Flying);
   pokedex.add_pokemon(171, "Lanturn", Pokemon::Type::Water, Pokemon::Type::Electric);
   pokedex.add_pokemon(176, "Togetic", Pokemon::Type::Fairy, Pokemon::Type::Flying);
   pokedex.add_pokemon(178, "Xatu", Pokemon::Type::Psychic, Pokemon::Type::Flying);
   pokedex.add_pokemon(181, "Ampharos", Pokemon::Type::Electric);
   pokedex.add_pokemon(182, "Bellossom", Pokemon::Type::Grass);
   pokedex.add_pokemon(184, "Azumarill", Pokemon::Type::Water, Pokemon::Type::Fairy);
   pokedex.add_pokemon(185, "Sodowoodo", Pokemon::Type::Rock);
   pokedex.add_pokemon(186, "Politoed", Pokemon::Type::Water);
   pokedex.add_pokemon(189, "Jumpluff", Pokemon::Type::Grass, Pokemon::Type::Flying);
   pokedex.add_pokemon(190, "Aipom", Pokemon::Type::Normal);
   pokedex.add_pokemon(192, "Sunflora", Pokemon::Type::Grass);
   pokedex.add_pokemon(193, "Yanma", Pokemon::Type::Bug, Pokemon::Type::Flying);
   pokedex.add_pokemon(195, "Quagsire", Pokemon::Type::Water, Pokemon::Type::Ground);
   pokedex.add_pokemon(196, "Espeon", Pokemon::Type::Psychic);
   pokedex.add_pokemon(197, "Umbreon", Pokemon::Type::Dark);
   pokedex.add_pokemon(198, "Murkrow", Pokemon::Type::Dark, Pokemon::Type::Flying);
   pokedex.add_pokemon(199, "Slowking", Pokemon::Type::Water, Pokemon::Type::Psychic);
   pokedex.add_pokemon(200, "Misdreavus", Pokemon::Type::Ghost);
   pokedex.add_pokemon(201, "Unown", Pokemon::Type::Psychic);
   pokedex.add_pokemon(202, "Wobbuffet", Pokemon::Type::Psychic);
   pokedex.add_pokemon(203, "Girafing", Pokemon::Type::Normal, Pokemon::Type::Psychic);
   pokedex.add_pokemon(205, "Forrtress", Pokemon::Type::Bug, Pokemon::Type::Steel);
   pokedex.add_pokemon(206, "Dunsparce", Pokemon::Type::Normal);
   pokedex.add_pokemon(207, "Gligar", Pokemon::Type::Ground, Pokemon::Type::Flying);
   pokedex.remove_pokemon(95, "Onix", Pokemon::Type::Rock, Pokemon::Type::Ground);
   pokedex.add_pokemon(208, "Steelix", Pokemon::Type::Steel, Pokemon::Type::Ground);
   pokedex.add_pokemon(210, "Granbull", Pokemon::Type::Fairy);
   pokedex.add_pokemon(211, "Qwilfish", Pokemon::Type::Water, Pokemon::Type::Poison);
   pokedex.remove_pokemon(123, "Scyther", Pokemon::Type::Bug, Pokemon::Type::Flying);
   pokedex.add_pokemon(212, "Scizor", Pokemon::Type::Bug, Pokemon::Type::Steel);
   pokedex.add_pokemon(213, "Shuckle", Pokemon::Type::Bug, Pokemon::Type::Rock);
   pokedex.add_pokemon(214, "Heracross", Pokemon::Type::Bug, Pokemon::Type::Fighting);
   pokedex.add_pokemon(215, "Sneasel", Pokemon::Type::Dark, Pokemon::Type::Ice);
   pokedex.add_pokemon(217, "Ursaring", Pokemon::Type::Normal);
   pokedex.add_pokemon(219, "Magcargo", Pokemon::Type::Fire, Pokemon::Type::Rock);
   pokedex.add_pokemon(221, "Piloswine", Pokemon::Type::Ice, Pokemon::Type::Ground);
   pokedex.add_pokemon(222, "Corsola", Pokemon::Type::Water, Pokemon::Type::Rock);
   pokedex.add_pokemon(224, "Octillery", Pokemon::Type::Water);
   pokedex.add_pokemon(225, "Delibird", Pokemon::Type::Ice, Pokemon::Type::Flying);
   pokedex.add_pokemon(226, "Mantine", Pokemon::Type::Water, Pokemon::Type::Flying);
   pokedex.add_pokemon(227, "Skarmory", Pokemon::Type::Steel, Pokemon::Type::Flying);
   pokedex.add_pokemon(229, "Houndoom", Pokemon::Type::Dark, Pokemon::Type::Fire);
   pokedex.remove_pokemon(117, "Seadra", Pokemon::Type::Water);
   pokedex.add_pokemon(230, "Kingdra", Pokemon::Type::Water, Pokemon::Type::Dragon);
   pokedex.add_pokemon(232, "Donphan", Pokemon::Type::Ground);
   pokedex.add_pokemon(233, "Porygon2", Pokemon::Type::Normal);
   pokedex.add_pokemon(234, "Stantler", Pokemon::Type::Normal);
   pokedex.add_pokemon(235, "Smeargle", Pokemon::Type::Normal);
   pokedex.add_pokemon(237, "Hitmontop", Pokemon::Type::Fighting);
   pokedex.add_pokemon(241, "Miltank", Pokemon::Type::Normal);
   pokedex.remove_pokemon(113, "Chansey", Pokemon::Type::Normal);
   pokedex.add_pokemon(242, "Blissey", Pokemon::Type::Normal);
   if (include_legendaries) {
      pokedex.add_pokemon(243, "Raikou", Pokemon::Type::Electric);
      pokedex.add_pokemon(244, "Entei", Pokemon::Type::Fire);
      pokedex.add_pokemon(245, "Suicune", Pokemon::Type::Water);
   }
   if (include_semilegendaries) {
      pokedex.add_pokemon(248, "Tyranitar", Pokemon::Type::Rock, Pokemon::Type::Dark);
   }
   if (include_legendaries) {
      pokedex.add_pokemon(249, "Lugia", Pokemon::Type::Psychic, Pokemon::Type::Flying);
      pokedex.add_pokemon(250, "Ho-Oh", Pokemon::Type::Fire, Pokemon::Type::Flying);
      pokedex.add_pokemon(251, "Celebi", Pokemon::Type::Psychic, Pokemon::Type::Grass);
   }
}

void FindBestTeam::add_hoenn_pokedex(Pokedex &pokedex, bool include_starters, bool include_ancients,
                                     bool include_semilegendaries, bool include_legendaries) noexcept {
   if (include_starters) {
      pokedex.add_pokemon(254, "Sceptile", Pokemon::Type::Grass);
      pokedex.add_pokemon(257, "Blanziken", Pokemon::Type::Fire, Pokemon::Type::Fighting);
      pokedex.add_pokemon(260, "Swampert", Pokemon::Type::Water, Pokemon::Type::Ground);
   }
   pokedex.add_pokemon(262, "Mightyena", Pokemon::Type::Dark);
   pokedex.add_pokemon(264, "Linoone", Pokemon::Type::Normal);
   pokedex.add_pokemon(267, "Beautifly", Pokemon::Type::Bug, Pokemon::Type::Flying);
   pokedex.add_pokemon(269, "Dustox", Pokemon::Type::Bug, Pokemon::Type::Poison);
   pokedex.add_pokemon(272, "Ludicolo", Pokemon::Type::Water, Pokemon::Type::Grass);
   pokedex.add_pokemon(275, "Shiftry", Pokemon::Type::Grass, Pokemon::Type::Dark);
   pokedex.add_pokemon(277, "Swellow", Pokemon::Type::Normal, Pokemon::Type::Flying);
   pokedex.add_pokemon(279, "Pelipper", Pokemon::Type::Water, Pokemon::Type::Flying);
   pokedex.add_pokemon(282, "Gardevoir", Pokemon::Type::Psychic, Pokemon::Type::Fairy);
   pokedex.add_pokemon(284, "Masquerain", Pokemon::Type::Bug, Pokemon::Type::Flying);
   pokedex.add_pokemon(286, "Breloom", Pokemon::Type::Grass, Pokemon::Type::Fighting);
   pokedex.add_pokemon(289, "Slaking", Pokemon::Type::Normal);
   pokedex.add_pokemon(291, "Ninjask", Pokemon::Type::Bug, Pokemon::Type::Flying);
   pokedex.add_pokemon(292, "Shedinja", Pokemon::Type::Bug, Pokemon::Type::Ghost);
   pokedex.add_pokemon(295, "Exploud", Pokemon::Type::Normal);
   pokedex.add_pokemon(297, "Hariyama", Pokemon::Type::Fighting);
   pokedex.add_pokemon(299, "Nosepass", Pokemon::Type::Rock);
   pokedex.add_pokemon(301, "Delcatty", Pokemon::Type::Normal);
   pokedex.add_pokemon(302, "Sableye", Pokemon::Type::Dark, Pokemon::Type::Ghost);
   pokedex.add_pokemon(303, "Mawile", Pokemon::Type::Steel, Pokemon::Type::Fairy);
   pokedex.add_pokemon(306, "Aggron", Pokemon::Type::Steel, Pokemon::Type::Rock);
   pokedex.add_pokemon(308, "Medicham", Pokemon::Type::Fighting, Pokemon::Type::Psychic);
   pokedex.add_pokemon(310, "Manectric", Pokemon::Type::Electric);
   pokedex.add_pokemon(311, "Pluse", Pokemon::Type::Electric);
   pokedex.add_pokemon(312, "Minun", Pokemon::Type::Electric);
   pokedex.add_pokemon(314, "Volbeat", Pokemon::Type::Bug);
   pokedex.add_pokemon(315, "Roselia", Pokemon::Type::Grass, Pokemon::Type::Poison);
   pokedex.add_pokemon(317, "Swalot", Pokemon::Type::Poison);
   pokedex.add_pokemon(319, "Sharpedo", Pokemon::Type::Water, Pokemon::Type::Dark);
   pokedex.add_pokemon(321, "Wailord", Pokemon::Type::Water);
   pokedex.add_pokemon(323, "Camerupt", Pokemon::Type::Fire, Pokemon::Type::Ground);
   pokedex.add_pokemon(324, "Torkoal", Pokemon::Type::Fire);
   pokedex.add_pokemon(326, "Grumping", Pokemon::Type::Psychic);
   pokedex.add_pokemon(327, "Spinda", Pokemon::Type::Normal);
   pokedex.add_pokemon(330, "Flygon", Pokemon::Type::Ground, Pokemon::Type::Dragon);
   pokedex.add_pokemon(332, "Cacturne", Pokemon::Type::Grass, Pokemon::Type::Dark);
   pokedex.add_pokemon(334, "Altaria", Pokemon::Type::Dragon, Pokemon::Type::Flying);
   pokedex.add_pokemon(335, "Zangoose", Pokemon::Type::Normal);
   pokedex.add_pokemon(336, "Seviper", Pokemon::Type::Poison);
   pokedex.add_pokemon(337, "Lunatone", Pokemon::Type::Rock, Pokemon::Type::Psychic);
   pokedex.add_pokemon(338, "Solrock", Pokemon::Type::Rock, Pokemon::Type::Psychic);
   pokedex.add_pokemon(340, "Whiscash", Pokemon::Type::Water, Pokemon::Type::Ground);
   pokedex.add_pokemon(342, "Crawdaunt", Pokemon::Type::Water, Pokemon::Type::Dark);
   pokedex.add_pokemon(344, "Claydol", Pokemon::Type::Ground, Pokemon::Type::Psychic);
   if (include_ancients) {
      pokedex.add_pokemon(346, "Cradily", Pokemon::Type::Rock, Pokemon::Type::Grass);
      pokedex.add_pokemon(348, "Armaldo", Pokemon::Type::Rock, Pokemon::Type::Bug);
   }
   pokedex.add_pokemon(350, "Milotic", Pokemon::Type::Water);
   pokedex.add_pokemon(351, "Castform", Pokemon::Type::Normal);
   pokedex.add_pokemon(352, "Keckleon", Pokemon::Type::Normal);
   pokedex.add_pokemon(354, "Banette", Pokemon::Type::Ghost);
   pokedex.add_pokemon(356, "Dusclops", Pokemon::Type::Ghost);
   pokedex.add_pokemon(357, "Tropius", Pokemon::Type::Grass, Pokemon::Type::Flying);
   pokedex.add_pokemon(358, "Chimecho", Pokemon::Type::Psychic);
   pokedex.add_pokemon(359, "Absol", Pokemon::Type::Dark);
   pokedex.add_pokemon(360, "Wynaut", Pokemon::Type::Psychic);
   pokedex.add_pokemon(362, "Glalie", Pokemon::Type::Ice);
   pokedex.add_pokemon(365, "Walrein", Pokemon::Type::Ice, Pokemon::Type::Water);
   pokedex.add_pokemon(368, "Gorebyss", Pokemon::Type::Water);
   pokedex.add_pokemon(369, "Relicanth", Pokemon::Type::Water, Pokemon::Type::Rock);
   pokedex.add_pokemon(370, "Luvdisc", Pokemon::Type::Water);
   if (include_semilegendaries) {
      pokedex.add_pokemon(373, "Salamence", Pokemon::Type::Dragon, Pokemon::Type::Flying);
      pokedex.add_pokemon(376, "Metagross", Pokemon::Type::Steel, Pokemon::Type::Psychic);
   }
   if (include_legendaries) {
      pokedex.add_pokemon(377, "Regirock", Pokemon::Type::Rock);
      pokedex.add_pokemon(378, "Regice", Pokemon::Type::Ice);
      pokedex.add_pokemon(379, "Registeel", Pokemon::Type::Steel);
      pokedex.add_pokemon(380, "Latias", Pokemon::Type::Dragon, Pokemon::Type::Psychic);
      pokedex.add_pokemon(381, "Latios", Pokemon::Type::Dragon, Pokemon::Type::Psychic);
      pokedex.add_pokemon(382, "Kyogre", Pokemon::Type::Water);
      pokedex.add_pokemon(383, "Groudon", Pokemon::Type::Ground);
      pokedex.add_pokemon(384, "Rayquaza", Pokemon::Type::Dragon, Pokemon::Type::Flying);
      pokedex.add_pokemon(385, "Jirachi", Pokemon::Type::Steel, Pokemon::Type::Psychic);
      pokedex.add_pokemon(386, "Deoxys", Pokemon::Type::Psychic);
   }
}

void FindBestTeam::add_sinnoh_pokedex(Pokedex &pokedex, bool include_starters, bool include_ancients,
                                      bool include_semilegendaries, bool include_legendaries) noexcept {
   if (include_starters) {
      pokedex.add_pokemon(389, "Torterra", Pokemon::Type::Grass, Pokemon::Type::Ground);
      pokedex.add_pokemon(392, "Infernape", Pokemon::Type::Fire, Pokemon::Type::Fighting);
      pokedex.add_pokemon(395, "Empoleon", Pokemon::Type::Water, Pokemon::Type::Steel);
   }
   pokedex.add_pokemon(398, "Staraptor", Pokemon::Type::Normal, Pokemon::Type::Flying);
   pokedex.add_pokemon(400, "Bibarel", Pokemon::Type::Normal, Pokemon::Type::Water);
   pokedex.add_pokemon(402, "Kricketune", Pokemon::Type::Bug);
   pokedex.add_pokemon(405, "Luxray", Pokemon::Type::Electric);
   pokedex.remove_pokemon(315, "Roselia", Pokemon::Type::Grass, Pokemon::Type::Poison);
   pokedex.add_pokemon(407, "Roserade", Pokemon::Type::Grass, Pokemon::Type::Poison);
   if (include_ancients) {
      pokedex.add_pokemon(409, "Rampardos", Pokemon::Type::Rock);
      pokedex.add_pokemon(411, "Bastiadon", Pokemon::Type::Rock, Pokemon::Type::Steel);
   }
   pokedex.add_pokemon(413, "Wormadam_grass", Pokemon::Type::Bug, Pokemon::Type::Grass);
   pokedex.add_pokemon(413, "Wormadam_ground", Pokemon::Type::Bug, Pokemon::Type::Ground);
   pokedex.add_pokemon(413, "Wormadam_steel", Pokemon::Type::Bug, Pokemon::Type::Steel);
   pokedex.add_pokemon(414, "Mothim", Pokemon::Type::Bug, Pokemon::Type::Flying);
   pokedex.add_pokemon(416, "Vespiquen", Pokemon::Type::Bug, Pokemon::Type::Flying);
   pokedex.add_pokemon(417, "Pachirisu", Pokemon::Type::Electric);
   pokedex.add_pokemon(419, "Floatzel", Pokemon::Type::Water);
   pokedex.add_pokemon(421, "Cherrim", Pokemon::Type::Grass);
   pokedex.add_pokemon(423, "Gastrodon", Pokemon::Type::Water, Pokemon::Type::Ground);
   pokedex.remove_pokemon(190, "Aipom", Pokemon::Type::Normal);
   pokedex.add_pokemon(424, "Ambipom", Pokemon::Type::Normal);
   pokedex.add_pokemon(426, "Drifblim", Pokemon::Type::Ghost, Pokemon::Type::Flying);
   pokedex.add_pokemon(428, "Lopunny", Pokemon::Type::Normal, Pokemon::Type::Fighting);
   pokedex.remove_pokemon(200, "Misdreavus", Pokemon::Type::Ghost);
   pokedex.add_pokemon(429, "Mismagius", Pokemon::Type::Ghost);
   pokedex.remove_pokemon(198, "Murkrow", Pokemon::Type::Dark, Pokemon::Type::Flying);
   pokedex.add_pokemon(430, "Honchkrow", Pokemon::Type::Dark, Pokemon::Type::Flying);
   pokedex.add_pokemon(432, "Perugly", Pokemon::Type::Normal);
   pokedex.add_pokemon(435, "Skuntank", Pokemon::Type::Poison, Pokemon::Type::Dark);
   pokedex.add_pokemon(437, "Bronzong", Pokemon::Type::Steel, Pokemon::Type::Psychic);
   pokedex.add_pokemon(441, "Chatot", Pokemon::Type::Normal, Pokemon::Type::Flying);
   pokedex.add_pokemon(442, "Spiritomb", Pokemon::Type::Ghost, Pokemon::Type::Dark);
   if (include_semilegendaries) {
      pokedex.add_pokemon(445, "Garchomp", Pokemon::Type::Dragon, Pokemon::Type::Ground);
   }
   pokedex.add_pokemon(448, "Lucario", Pokemon::Type::Fighting, Pokemon::Type::Steel);
   pokedex.add_pokemon(450, "Hippowdon", Pokemon::Type::Ground);
   pokedex.add_pokemon(452, "Drapion", Pokemon::Type::Poison, Pokemon::Type::Dark);
   pokedex.add_pokemon(454, "Toxicroak", Pokemon::Type::Poison, Pokemon::Type::Fighting);
   pokedex.add_pokemon(455, "Carnivine", Pokemon::Type::Grass);
   pokedex.add_pokemon(457, "Lumineon", Pokemon::Type::Water);
   pokedex.add_pokemon(460, "Abomasnow", Pokemon::Type::Grass, Pokemon::Type::Ice);
   pokedex.remove_pokemon(215, "Sneasel", Pokemon::Type::Dark, Pokemon::Type::Ice);
   pokedex.add_pokemon(461, "Weavile", Pokemon::Type::Dark, Pokemon::Type::Ice);
   pokedex.remove_pokemon(82, "Magneton", Pokemon::Type::Electric, Pokemon::Type::Steel);
   pokedex.add_pokemon(462, "Magnezone", Pokemon::Type::Electric, Pokemon::Type::Steel);
   pokedex.remove_pokemon(108, "Lickitung", Pokemon::Type::Normal);
   pokedex.add_pokemon(463, "Lickilicky", Pokemon::Type::Normal);
   pokedex.remove_pokemon(112, "Rhydon", Pokemon::Type::Ground, Pokemon::Type::Rock);
   pokedex.add_pokemon(464, "Rhyperior", Pokemon::Type::Ground, Pokemon::Type::Rock);
   pokedex.remove_pokemon(114, "Tangela", Pokemon::Type::Grass);
   pokedex.add_pokemon(465, "Tangrowth", Pokemon::Type::Grass);
   pokedex.remove_pokemon(125, "Electabuzz", Pokemon::Type::Electric);
   pokedex.add_pokemon(466, "Electivire", Pokemon::Type::Electric);
   pokedex.remove_pokemon(126, "Magmar", Pokemon::Type::Fire);
   pokedex.add_pokemon(467, "Magmortar", Pokemon::Type::Fire);
   pokedex.remove_pokemon(176, "Togetic", Pokemon::Type::Fairy, Pokemon::Type::Flying);
   pokedex.add_pokemon(468, "Togekiss", Pokemon::Type::Fairy, Pokemon::Type::Flying);
   pokedex.remove_pokemon(193, "Yanma", Pokemon::Type::Bug, Pokemon::Type::Flying);
   pokedex.add_pokemon(469, "Yanmega", Pokemon::Type::Bug, Pokemon::Type::Flying);
   pokedex.add_pokemon(470, "Leafeon", Pokemon::Type::Grass);
   pokedex.add_pokemon(471, "Glaceon", Pokemon::Type::Ice);
   pokedex.remove_pokemon(207, "Gligar", Pokemon::Type::Ground, Pokemon::Type::Flying);
   pokedex.add_pokemon(472, "Gliscor", Pokemon::Type::Ground, Pokemon::Type::Flying);
   pokedex.remove_pokemon(221, "Piloswine", Pokemon::Type::Ice, Pokemon::Type::Ground);
   pokedex.add_pokemon(473, "Mamoswine", Pokemon::Type::Ice, Pokemon::Type::Ground);
   pokedex.remove_pokemon(137, "Porygon", Pokemon::Type::Normal);
   pokedex.add_pokemon(474, "Porygon-Z", Pokemon::Type::Normal);
   pokedex.add_pokemon(475, "Gallade", Pokemon::Type::Psychic, Pokemon::Type::Fighting);
   pokedex.remove_pokemon(299, "Nosepass", Pokemon::Type::Rock);
   pokedex.add_pokemon(476, "Probopass", Pokemon::Type::Rock, Pokemon::Type::Steel);
   pokedex.remove_pokemon(356, "Dusclops", Pokemon::Type::Ghost);
   pokedex.add_pokemon(477, "Dusknoir", Pokemon::Type::Ghost);
   pokedex.add_pokemon(478, "Froslass", Pokemon::Type::Ice, Pokemon::Type::Ghost);
   pokedex.add_pokemon(479, "Rotom_ghost", Pokemon::Type::Electric, Pokemon::Type::Ghost);
   pokedex.add_pokemon(479, "Rotom_fire", Pokemon::Type::Electric, Pokemon::Type::Fire);
   pokedex.add_pokemon(479, "Rotom_water", Pokemon::Type::Electric, Pokemon::Type::Water);
   pokedex.add_pokemon(479, "Rotom_ice", Pokemon::Type::Electric, Pokemon::Type::Ice);
   pokedex.add_pokemon(479, "Rotom_flying", Pokemon::Type::Electric, Pokemon::Type::Flying);
   pokedex.add_pokemon(479, "Rotom_grass", Pokemon::Type::Electric, Pokemon::Type::Grass);
   if (include_legendaries) {
      pokedex.add_pokemon(480, "Uxie", Pokemon::Type::Psychic);
      pokedex.add_pokemon(481, "Mesprit", Pokemon::Type::Psychic);
      pokedex.add_pokemon(482, "Azelf", Pokemon::Type::Psychic);
      pokedex.add_pokemon(483, "Dialga", Pokemon::Type::Steel, Pokemon::Type::Dragon);
      pokedex.add_pokemon(484, "Palkia", Pokemon::Type::Water, Pokemon::Type::Dragon);
      pokedex.add_pokemon(485, "Heatran", Pokemon::Type::Fire, Pokemon::Type::Steel);
      pokedex.add_pokemon(486, "Regigigas", Pokemon::Type::Normal);
      pokedex.add_pokemon(487, "Giratina", Pokemon::Type::Ghost, Pokemon::Type::Dragon);
      pokedex.add_pokemon(488, "Cresselia", Pokemon::Type::Psychic);
      pokedex.add_pokemon(489, "Phione", Pokemon::Type::Water);
      pokedex.add_pokemon(490, "Manaphy", Pokemon::Type::Water);
      pokedex.add_pokemon(491, "Darkrai", Pokemon::Type::Dark);
      pokedex.add_pokemon(492, "Shaymin", Pokemon::Type::Grass);
      pokedex.add_pokemon(492, "Shaymin_flying", Pokemon::Type::Grass, Pokemon::Type::Flying);
      pokedex.add_pokemon(493, "Arceus_normal", Pokemon::Type::Normal);
      pokedex.add_pokemon(493, "Arceus_fighting", Pokemon::Type::Fighting);
      pokedex.add_pokemon(493, "Arceus_flying", Pokemon::Type::Flying);
      pokedex.add_pokemon(493, "Arceus_poison", Pokemon::Type::Poison);
      pokedex.add_pokemon(493, "Arceus_ground", Pokemon::Type::Ground);
      pokedex.add_pokemon(493, "Arceus_rock", Pokemon::Type::Rock);
      pokedex.add_pokemon(493, "Arceus_bug", Pokemon::Type::Bug);
      pokedex.add_pokemon(493, "Arceus_ghost", Pokemon::Type::Ghost);
      pokedex.add_pokemon(493, "Arceus_steel", Pokemon::Type::Steel);
      pokedex.add_pokemon(493, "Arceus_fire", Pokemon::Type::Fire);
      pokedex.add_pokemon(493, "Arceus_water", Pokemon::Type::Water);
      pokedex.add_pokemon(493, "Arceus_grass", Pokemon::Type::Grass);
      pokedex.add_pokemon(493, "Arceus_electric", Pokemon::Type::Electric);
      pokedex.add_pokemon(493, "Arceus_psychic", Pokemon::Type::Psychic);
      pokedex.add_pokemon(493, "Arceus_ice", Pokemon::Type::Ice);
      pokedex.add_pokemon(493, "Arceus_dragon", Pokemon::Type::Dragon);
      pokedex.add_pokemon(493, "Arceus_dark", Pokemon::Type::Dark);
      pokedex.add_pokemon(493, "Arceus_fairy", Pokemon::Type::Fairy);
   }
}