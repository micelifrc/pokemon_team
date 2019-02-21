//
// Created by mich on 21/02/19.
//

#include "FindBestTeam.h"

FindBestTeam::FindBestTeam(const std::vector<Pokemon> &fixed_pokemon_, std::vector<PokeTeam> &best_teams_,
                           bool consider_defence_, bool consider_offence_, int filter_factor_, bool include_duplicates_)
      :
      _num_fixed_pokemon{static_cast<unsigned>(fixed_pokemon_.size())}, _best_teams{best_teams_},
      _max_score{std::numeric_limits<int>::min()}, _filter_factor{filter_factor_} {
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
         _partial_scoring[poke_idx][type_idx] = _evaluation(&_current_team[poke_idx], _all_types[type_idx]);
      }
   }
   _duplicate_step = (include_duplicates_) ? 0 : 1;
   add_kanto_pokedex(_pokedex);
}

int FindBestTeam::operator()() {
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
      for (unsigned long poke_idx = next_to_try; poke_idx < _pokedex.all_type_pairs().size(); ++poke_idx) {
         _current_team[already_in_team] = _pokedex.all_pokemon()[_pokedex.all_type_pairs()[poke_idx].second[0]].first;
         for (unsigned int type_idx = 0; type_idx != Pokemon::NUM_TYPES; ++type_idx) {
            int previous_scoring = (already_in_team == 0) ? 0 : _partial_scoring[already_in_team - 1][type_idx];
            _partial_scoring[already_in_team][type_idx] =
                  previous_scoring + _evaluation(&_current_team[already_in_team], _all_types[type_idx]);
         }
         find_best_team_loop_iter(already_in_team + 1, poke_idx + _duplicate_step);
      }
   }
}

void FindBestTeam::add_kanto_pokedex(Pokedex &pokedex) noexcept {
   pokedex.add_pokemon("Venusaur", Pokemon::Type::Grass, Pokemon::Type::Poison);
   pokedex.add_pokemon("Charizard", Pokemon::Type::Fire, Pokemon::Type::Flying);
   pokedex.add_pokemon("Blastoise", Pokemon::Type::Water);
   pokedex.add_pokemon("Butterfree", Pokemon::Type::Bug, Pokemon::Type::Flying);
   pokedex.add_pokemon("Beedrill", Pokemon::Type::Bug, Pokemon::Type::Poison);
   pokedex.add_pokemon("Beedrill", Pokemon::Type::Bug, Pokemon::Type::Poison);
   pokedex.add_pokemon("Pidgeot", Pokemon::Type::Normal, Pokemon::Type::Flying);
   pokedex.add_pokemon("Raticate", Pokemon::Type::Normal);
   pokedex.add_pokemon("Fearow", Pokemon::Type::Normal, Pokemon::Type::Flying);
   pokedex.add_pokemon("Arbok", Pokemon::Type::Poison);
   pokedex.add_pokemon("Raichu", Pokemon::Type::Electric);
   pokedex.add_pokemon("Sandlash", Pokemon::Type::Ground);
   pokedex.add_pokemon("Nidoqueen", Pokemon::Type::Poison, Pokemon::Type::Ground);
   pokedex.add_pokemon("Nidoking", Pokemon::Type::Poison, Pokemon::Type::Ground);
   pokedex.add_pokemon("Clefable", Pokemon::Type::Fairy);
   pokedex.add_pokemon("Ninetales", Pokemon::Type::Fire);
   pokedex.add_pokemon("Wiglytuff", Pokemon::Type::Normal);
   pokedex.add_pokemon("Golbat", Pokemon::Type::Poison, Pokemon::Type::Flying);
   pokedex.add_pokemon("Vileplume", Pokemon::Type::Grass, Pokemon::Type::Poison);
   pokedex.add_pokemon("Parasect", Pokemon::Type::Bug, Pokemon::Type::Grass);
   pokedex.add_pokemon("Venomoth", Pokemon::Type::Bug, Pokemon::Type::Poison);
   pokedex.add_pokemon("Dugtrio", Pokemon::Type::Ground);
   pokedex.add_pokemon("Persian", Pokemon::Type::Normal);
   pokedex.add_pokemon("Golduck", Pokemon::Type::Water);
   pokedex.add_pokemon("Primeape", Pokemon::Type::Fighting);
   pokedex.add_pokemon("Arcanine", Pokemon::Type::Fire);
   pokedex.add_pokemon("Poliwrath", Pokemon::Type::Water, Pokemon::Type::Fighting);
   pokedex.add_pokemon("Alakazam", Pokemon::Type::Psychic);
   pokedex.add_pokemon("Machamp", Pokemon::Type::Fighting);
   pokedex.add_pokemon("Victribel", Pokemon::Type::Grass, Pokemon::Type::Poison);
   pokedex.add_pokemon("Tentacruel", Pokemon::Type::Water, Pokemon::Type::Poison);
   pokedex.add_pokemon("Golem", Pokemon::Type::Rock, Pokemon::Type::Ground);
   pokedex.add_pokemon("Rapidash", Pokemon::Type::Fire);
   pokedex.add_pokemon("Slowbro", Pokemon::Type::Water, Pokemon::Type::Psychic);
   pokedex.add_pokemon("Magneton", Pokemon::Type::Electric, Pokemon::Type::Steel);
   pokedex.add_pokemon("Farfetch'd", Pokemon::Type::Normal, Pokemon::Type::Flying);
   pokedex.add_pokemon("Dodrio", Pokemon::Type::Normal, Pokemon::Type::Flying);
   pokedex.add_pokemon("Dwegong", Pokemon::Type::Water, Pokemon::Type::Ice);
   pokedex.add_pokemon("Muk", Pokemon::Type::Poison);
   pokedex.add_pokemon("Cloyster", Pokemon::Type::Water, Pokemon::Type::Ice);
   pokedex.add_pokemon("Gengar", Pokemon::Type::Ghost, Pokemon::Type::Poison);
   pokedex.add_pokemon("Onix", Pokemon::Type::Rock, Pokemon::Type::Ground);
   pokedex.add_pokemon("Hypno", Pokemon::Type::Psychic);
   pokedex.add_pokemon("Kingler", Pokemon::Type::Water);
   pokedex.add_pokemon("Electrode", Pokemon::Type::Electric);
   pokedex.add_pokemon("Exeggutor", Pokemon::Type::Grass, Pokemon::Type::Psychic);
   pokedex.add_pokemon("Marowak", Pokemon::Type::Ground);
   pokedex.add_pokemon("Hitmonlee", Pokemon::Type::Fighting);
   pokedex.add_pokemon("Hitmonchan", Pokemon::Type::Fighting);
   pokedex.add_pokemon("Lickitung", Pokemon::Type::Normal);
   pokedex.add_pokemon("Weezing", Pokemon::Type::Poison);
   pokedex.add_pokemon("Rhydon", Pokemon::Type::Ground, Pokemon::Type::Rock);
   pokedex.add_pokemon("Chansey", Pokemon::Type::Normal);
   pokedex.add_pokemon("Tangela", Pokemon::Type::Grass);
   pokedex.add_pokemon("Kangaskhan", Pokemon::Type::Normal);
   pokedex.add_pokemon("Seadra", Pokemon::Type::Water);
   pokedex.add_pokemon("Seaking", Pokemon::Type::Water);
   pokedex.add_pokemon("Starmie", Pokemon::Type::Water, Pokemon::Type::Psychic);
   pokedex.add_pokemon("Mr.Mime", Pokemon::Type::Psychic, Pokemon::Type::Fairy);
   pokedex.add_pokemon("Scyther", Pokemon::Type::Bug, Pokemon::Type::Flying);
   pokedex.add_pokemon("Jynx", Pokemon::Type::Ice, Pokemon::Type::Psychic);
   pokedex.add_pokemon("Electabuzz", Pokemon::Type::Electric);
   pokedex.add_pokemon("Magmar", Pokemon::Type::Fire);
   pokedex.add_pokemon("Pinsir", Pokemon::Type::Bug);
   pokedex.add_pokemon("Tauros", Pokemon::Type::Normal);
   pokedex.add_pokemon("Gyarados", Pokemon::Type::Water, Pokemon::Type::Flying);
   pokedex.add_pokemon("Lapras", Pokemon::Type::Water, Pokemon::Type::Ice);
   pokedex.add_pokemon("Ditto", Pokemon::Type::Normal);
   pokedex.add_pokemon("Vaporeon", Pokemon::Type::Water);
   pokedex.add_pokemon("Jolteon", Pokemon::Type::Electric);
   pokedex.add_pokemon("Flareon", Pokemon::Type::Fire);
   pokedex.add_pokemon("Porygon", Pokemon::Type::Normal);
   pokedex.add_pokemon("Snorlax", Pokemon::Type::Normal);
}

const std::array<Pokemon::Type, Pokemon::NUM_TYPES> FindBestTeam::_all_types{Pokemon::Type::Normal,
                                                                             Pokemon::Type::Fighting,
                                                                             Pokemon::Type::Flying,
                                                                             Pokemon::Type::Poison,
                                                                             Pokemon::Type::Ground, Pokemon::Type::Rock,
                                                                             Pokemon::Type::Bug, Pokemon::Type::Ghost,
                                                                             Pokemon::Type::Steel, Pokemon::Type::Fire,
                                                                             Pokemon::Type::Water, Pokemon::Type::Grass,
                                                                             Pokemon::Type::Electric,
                                                                             Pokemon::Type::Psychic, Pokemon::Type::Ice,
                                                                             Pokemon::Type::Dragon, Pokemon::Type::Dark,
                                                                             Pokemon::Type::Fairy};
