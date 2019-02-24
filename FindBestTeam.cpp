//
// Created by mich on 21/02/19.
//

#include "FindBestTeam.h"

FindBestTeam::FindBestTeam(const std::vector<Pokemon> &fixed_pokemon_, std::vector<PokeTeam> &best_teams_,
                           unsigned regions_, unsigned inclusions_, bool consider_defence_,
                           bool consider_offence_, int filter_factor_) :
      _fixed_pokemon{fixed_pokemon_}, _best_teams{best_teams_}, _max_score{std::numeric_limits<int>::min()},
      _filter_factor{filter_factor_} {
   if (_fixed_pokemon.size() > 6) {
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
   _pokedex.make(regions_, inclusions_);
   _all_subteams[0].reserve(integer_exponential(_pokedex.num_representatives(),
                                                static_cast<unsigned>(SubTeam::SIZE -
                                                                      (_fixed_pokemon.size() + 1) / 2)));
   _all_subteams[1].reserve(integer_exponential(_pokedex.num_representatives(),
                                                static_cast<unsigned>(SubTeam::SIZE - _fixed_pokemon.size() / 2)));
}

int FindBestTeam::find_best_teams() {
   form_all_subteams(0);
   std::sort(_all_subteams[0].begin(), _all_subteams[0].end(),
             [](const SubTeam &lhs, const SubTeam &rhs) { return lhs.upper_bd > rhs.upper_bd; });
   if (not _fixed_pokemon.empty()) {
      form_all_subteams(1);
      std::sort(_all_subteams[1].begin(), _all_subteams[1].end(),
                [](const SubTeam &lhs, const SubTeam &rhs) { return lhs.upper_bd > rhs.upper_bd; });
   }

   merge_best_subteams();
   std::sort(_best_teams.begin(), _best_teams.end(),
             [](const PokeTeam &lhs, const PokeTeam &rhs) { return lhs > rhs; });

   return _max_score;
}

void FindBestTeam::form_all_subteams(unsigned subteam_idx) {
   if (subteam_idx >= 2) {
      throw std::logic_error("There are only two arrays of possible subteams");
   }
   auto number_fixed = static_cast<unsigned>((_fixed_pokemon.size() + 1 - subteam_idx) / 2);  // number of fixed pokemon
   if (number_fixed > SubTeam::SIZE) {
      throw std::logic_error("There are too many fixed pokemon in the subteam");
   }
   for (unsigned member_idx = 0; member_idx != SubTeam::SIZE; ++member_idx) {
      _members_subteam[member_idx] = 0;
   }

   for (unsigned member_idx = 0; member_idx != number_fixed; ++member_idx) {
      for (unsigned type_idx = 0; type_idx != Pokemon::NUM_TYPES; ++type_idx) {
         _partial_matchups[member_idx][type_idx] = _evaluation(&_fixed_pokemon[2 * member_idx + subteam_idx],
                                                               static_cast<PokeType>(type_idx));
      }
   }

   form_all_subteams_iteration(subteam_idx, number_fixed);
}


void FindBestTeam::form_all_subteams_iteration(unsigned subteam_idx, unsigned new_member_position) {
   if (new_member_position >= SubTeam::SIZE) {
      _all_subteams[subteam_idx].emplace_back(_members_subteam, _partial_matchups[SubTeam::SIZE - 1]);
   } else {
      for (unsigned long new_member_idx = (new_member_position == 0) ? 0 : _members_subteam[new_member_position - 1];
           new_member_idx != _pokedex.num_representatives(); ++new_member_idx) {
         _members_subteam[new_member_position] = new_member_idx;
         for (unsigned type_idx = 0; type_idx != Pokemon::NUM_TYPES; ++type_idx) {
            int previous_matchup = (new_member_position == 0) ? 0 : _partial_matchups[new_member_position -
                                                                                      1][type_idx];
            _partial_matchups[new_member_position][type_idx] = previous_matchup +
                                                               _evaluation(_pokedex.representatives()[new_member_idx],
                                                                           static_cast<PokeType>(type_idx));
         }
         form_all_subteams_iteration(subteam_idx, new_member_position + 1);
      }
   }
}

void FindBestTeam::merge_best_subteams() {
   std::pair<std::vector<SubTeam> &, std::vector<SubTeam> &> subteams{_all_subteams[0], _all_subteams[1]};
   if (_fixed_pokemon.empty()) {
      subteams.second = _all_subteams[0];
   }
   unsigned front_free_index_in_first = static_cast<unsigned>(_fixed_pokemon.size() + 1) / 2;
   unsigned front_free_index_in_second = static_cast<unsigned>(_fixed_pokemon.size()) / 2;

   std::vector<std::pair<unsigned long, unsigned long>> best_pairings;
   for (unsigned long idx_first = 0; idx_first != subteams.first.size(); ++idx_first) {
      for (unsigned long idx_second = 0; idx_second != subteams.second.size(); ++idx_second) {
         if (static_cast<int>(subteams.first[idx_first].upper_bd + subteams.second[idx_second].upper_bd) < _max_score) {
            break;
         }
         if (subteams.first[idx_first][SubTeam::SIZE - 1] > subteams.second[idx_second][front_free_index_in_second]) {
            continue;  // we want the team to be in increasing order of indices
         }
         int pairing_scoring = 0;
         for (unsigned type_idx = 0; type_idx != Pokemon::NUM_TYPES; ++type_idx) {
            pairing_scoring += std::min(
                  subteams.first[idx_first].all_matchups[type_idx] + subteams.second[idx_second].all_matchups[type_idx],
                  _filter_factor);
         }
         if (pairing_scoring > _max_score) {
            _max_score = pairing_scoring;
            best_pairings.clear();
         }
         if (pairing_scoring == _max_score) {
            best_pairings.emplace_back(idx_first, idx_second);
         }
      }
   }

   for (const auto &pairing: best_pairings) {
      PokeTeam best_team{};
      for (unsigned poke_idx = 0; poke_idx != 6; ++poke_idx) {
         if (poke_idx < _fixed_pokemon.size()) {
            best_team[poke_idx] = _fixed_pokemon[poke_idx];
         } else if (poke_idx < SubTeam::SIZE + front_free_index_in_second) {
            best_team[poke_idx] = *_pokedex.representatives()[subteams.first[pairing.first][poke_idx -
                                                                                            front_free_index_in_first]];
         } else {
            best_team[poke_idx] = *_pokedex.representatives()[subteams.second[pairing.second][poke_idx -
                                                                                              SubTeam::SIZE]];
         }
      }
      _best_teams.emplace_back(best_team);
   }
}

FindBestTeam::SubTeam::SubTeam(const std::array<unsigned long, SIZE> &members_,
                               const std::array<int, Pokemon::NUM_TYPES> &all_matchups_) :
      members_idx{members_}, upper_bd{0}, all_matchups{all_matchups_} {
   for (unsigned type_idx = 0; type_idx != Pokemon::NUM_TYPES; ++type_idx) {
      upper_bd += all_matchups[type_idx];
   }
}

unsigned long FindBestTeam::SubTeam::operator[](unsigned idx) const {
   if (idx >= SIZE) {
      throw std::logic_error("A SubTeam only has " + std::to_string(SIZE) + " members");
   }
   return members_idx[idx];
}