//
// Created by mich on 21/02/19.
//

#include "FindBestTeam.h"

FindBestTeam::FindBestTeam(const std::vector<Pokemon> &fixed_pokemon_, std::vector<PokeTeam> &best_teams_,
                           unsigned regions_, unsigned inclusions_, bool consider_defence_,
                           bool consider_offence_, int filter_factor_, bool allow_type_repetitions_) :
      _num_fixed_pokemon{static_cast<unsigned>(fixed_pokemon_.size())}, _best_teams{best_teams_},
      _max_score{std::numeric_limits<int>::min()}, _filter_factor{filter_factor_},
      _allow_type_repetitions{allow_type_repetitions_}, _max_possible_increment{0} {
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
                                                            static_cast<PokeType>(type_idx));
      }
   }
   _pokedex.make(regions_, inclusions_);
   set_max_possible_increment();
}

int FindBestTeam::find_best_teams() {
   find_best_team_loop_iter(_num_fixed_pokemon, 0);
   std::sort(_best_teams.begin(), _best_teams.end(),
             [](const PokeTeam &lhs, const PokeTeam &rhs) { return lhs > rhs; });
   return _max_score;
}


void FindBestTeam::set_max_possible_increment() {
   for (const auto &repr: _pokedex.representatives()) {
      int max_increment_for_fixed_pokemon = 0;
      for (unsigned type_idx = 0; type_idx != Pokemon::NUM_TYPES; ++type_idx) {
         max_increment_for_fixed_pokemon += std::max(0, _evaluation(repr, static_cast<PokeType>(type_idx)));
      }
      _max_possible_increment = std::max(_max_possible_increment, max_increment_for_fixed_pokemon);
   }
}

int FindBestTeam::compute_scoring(unsigned idx) {
   if (idx == 0) {
      return 0;
   }
   if (idx > 6) {
      throw std::logic_error("Cannot compute FindBestTeam::compute_scoring for index > 6");
   }
   unsigned scoring = 0;
   for (unsigned type_idx = 0; type_idx != Pokemon::NUM_TYPES; ++type_idx) {
      scoring += std::min(_filter_factor, _partial_scoring[idx - 1][type_idx]);
   }
   return scoring;
}

void FindBestTeam::find_best_team_loop_iter(unsigned already_in_team, unsigned long next_to_try) {
   if (already_in_team > 6) {
      throw std::logic_error("The team already have too many pokemon");
   }
   if (already_in_team == 6) {
      int current_score = compute_scoring(6);
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
                                                                         static_cast<PokeType>(type_idx));
            }
            if (compute_scoring(already_in_team + 1) +
                static_cast<int>(5 - already_in_team) * _max_possible_increment >= _max_score) {
               find_best_team_loop_iter(already_in_team + 1, poke_idx);
            }
         }
      }
   }
}