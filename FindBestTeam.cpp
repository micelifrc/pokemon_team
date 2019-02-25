//
// Created by mich on 21/02/19.
//

#include "FindBestTeam.h"
#include <thread>

FindBestTeam::FindBestTeam(const std::vector<Pokemon> &fixed_pokemon_, std::vector<PokeTeam> &best_teams_,
                           unsigned regions_, unsigned tipology_, bool consider_defence_,
                           bool consider_offence_, int filter_factor_, bool allow_repetitions_) :
      _fixed_pokemon{fixed_pokemon_}, _best_teams{best_teams_}, _max_score{std::numeric_limits<int>::min()},
      _filter_factor{filter_factor_} {

   if (_fixed_pokemon.size() > PokeTeam::SIZE) {
      throw std::invalid_argument(
            "Cannot complete at team that already has more than " + std::to_string(PokeTeam::SIZE) + " pokemon");
   }

   if (not consider_defence_ and not consider_offence_) {
      throw std::invalid_argument("At least one between consider_defence and consider_offence should be set to true");
   }

   _repetition_step = allow_repetitions_ ? 0 : 1;
   if (consider_defence_ and consider_offence_) {
      _evaluation = &Pokemon::mismatch;
   } else if (consider_defence_) {
      _evaluation = &Pokemon::resistance;
   } else {
      _evaluation = &Pokemon::offensive_effectiveness;
   }
   _pokedex.make(regions_, tipology_);
}

int FindBestTeam::find_best_teams(unsigned num_threads) {
   _best_teams.clear();
   _max_score = 0;
   _best_pairings.clear();

   form_all_subteams(0);
   std::sort(_all_subteams[0]->begin(), _all_subteams[0]->end(),
             [](const SubTeam &lhs, const SubTeam &rhs) { return lhs.upper_bd > rhs.upper_bd; });
   if (_fixed_pokemon.empty()) {
      _all_subteams[1] = _all_subteams[0];
   } else {
      form_all_subteams(1);
      std::sort(_all_subteams[1]->begin(), _all_subteams[1]->end(),
                [](const SubTeam &lhs, const SubTeam &rhs) { return lhs.upper_bd > rhs.upper_bd; });
   }

   merge_best_subteams(num_threads);
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
      for (unsigned type_idx = 0; type_idx != static_cast<unsigned>(PokeType::NUM_TYPES); ++type_idx) {
         _partial_matchups[member_idx][type_idx] = _evaluation(&_fixed_pokemon[2 * member_idx + subteam_idx],
                                                               static_cast<PokeType>(type_idx));
      }
   }

   _all_subteams[subteam_idx] = std::make_shared<std::vector<SubTeam>>();
   _all_subteams[subteam_idx]->reserve(
         integer_exponential(_pokedex.num_representatives(), SubTeam::SIZE - number_fixed));
   form_all_subteams_iteration(subteam_idx, number_fixed);
}


void FindBestTeam::form_all_subteams_iteration(unsigned subteam_idx, unsigned new_member_position) {
   if (new_member_position >= SubTeam::SIZE) {
      _all_subteams[subteam_idx]->emplace_back(_members_subteam, _partial_matchups[SubTeam::SIZE - 1]);
   } else {
      for (unsigned new_member_idx = (new_member_position == 0) ? 0 : _members_subteam[new_member_position - 1] +
                                                                      _repetition_step;
           new_member_idx != _pokedex.num_representatives(); ++new_member_idx) {
         _members_subteam[new_member_position] = new_member_idx;
         for (unsigned type_idx = 0; type_idx != static_cast<unsigned>(PokeType::NUM_TYPES); ++type_idx) {
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

void FindBestTeam::merge_best_subteams(unsigned num_threads) {
   if (_all_subteams[0]->size() < num_threads) {
      num_threads = static_cast<unsigned>(_all_subteams[0]->size());
   }
   std::vector<std::thread> threads;
   threads.reserve(num_threads);

   _next_idx_first_to_consider = 0;
   for (unsigned thread_idx = 0; thread_idx != num_threads; ++thread_idx) {
      threads.emplace_back(&FindBestTeam::merge_best_subteams_iteration, this);
   }
   for (auto &thread: threads) {
      thread.join();
   }

   save_best_teams();
}

void FindBestTeam::merge_best_subteams_iteration() {
   unsigned long idx_first = 0;
   while (idx_first < _all_subteams[0]->size()) {
      _next_idx_first_to_consider_lock.lock();
      idx_first = _next_idx_first_to_consider++;
      _next_idx_first_to_consider_lock.unlock();
      for (unsigned long idx_second = 0; idx_second != _all_subteams[1]->size(); ++idx_second) {
         if ((*_all_subteams[0])[idx_first].upper_bd + (*_all_subteams[1])[idx_second].upper_bd < _max_score) {
            break;
         }
         if ((*_all_subteams[0])[idx_first][SubTeam::SIZE - 1] >
             (*_all_subteams[1])[idx_second][_fixed_pokemon.size() / 2]) {
            continue;  // we want the team to be in increasing order of indices
         }
         int pairing_scoring = 0;
         for (unsigned type_idx = 0; type_idx != static_cast<unsigned>(PokeType::NUM_TYPES); ++type_idx) {
            pairing_scoring += std::min((*_all_subteams[0])[idx_first].all_matchups[type_idx] +
                                        (*_all_subteams[1])[idx_second].all_matchups[type_idx], _filter_factor);
         }

         _max_score_lock.lock();
         if (pairing_scoring > _max_score) {
            _max_score = pairing_scoring;
            _best_pairings.clear();
         }
         if (pairing_scoring == _max_score) {
            _best_pairings.emplace_back(idx_first, idx_second);
         }
         _max_score_lock.unlock();
      }
   }
}

void FindBestTeam::save_best_teams() {
   for (const auto &pairing: _best_pairings) {
      PokeTeam best_team{};
      for (unsigned poke_idx = 0; poke_idx != PokeTeam::SIZE; ++poke_idx) {
         if (poke_idx < _fixed_pokemon.size()) {
            best_team[poke_idx] = _fixed_pokemon[poke_idx];
         } else if (poke_idx < SubTeam::SIZE + _fixed_pokemon.size() / 2) {
            best_team[poke_idx] =
                  *_pokedex.representatives()[(*_all_subteams[0])[pairing.first][poke_idx - _fixed_pokemon.size() / 2]];
         } else {
            best_team[poke_idx] =
                  *_pokedex.representatives()[(*_all_subteams[1])[pairing.second][poke_idx - SubTeam::SIZE]];
         }
      }
      _best_teams.emplace_back(best_team);
   }
}

FindBestTeam::SubTeam::SubTeam(const std::array<unsigned, SIZE> &members_,
                               const std::array<int, static_cast<unsigned>(PokeType::NUM_TYPES)> &all_matchups_) :
      members_idx{members_}, upper_bd{0}, all_matchups{all_matchups_} {
   for (unsigned type_idx = 0; type_idx != static_cast<unsigned>(PokeType::NUM_TYPES); ++type_idx) {
      upper_bd += all_matchups[type_idx];
   }
}

unsigned long FindBestTeam::SubTeam::operator[](unsigned idx) const {
   if (idx >= SIZE) {
      throw std::logic_error("A SubTeam only has " + std::to_string(SIZE) + " members");
   }
   return members_idx[idx];
}