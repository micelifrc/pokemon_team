//
// Created by mich on 21/02/19.
//

#ifndef POKEMON_TEAM_FINDBESTTEAM_H
#define POKEMON_TEAM_FINDBESTTEAM_H

#include <functional>
#include <mutex>
#include "Pokedex.h"

class FindBestTeam {
public:
   /**
    * Creates an instance for FindBestTeam to find the best possible team extension
    * @param fixed_pokemon_ The pokemon you want in your team (can be empty)
    * @param best_teams_ The list of the teams realizing the optimum objective (the output)
    * @param tipology_ A flag from TipologyFlag to say which kinds of pokemon we should consider
    * @param last_generation_to_include_ The last generation to include. In future cound be replaced with another flag
    * @param consider_defence_ You should consider the defensive resistances in the objective?
    * @param consider_offence_ You should consider the offensive effectiveness in the objective?
    * @param filter_factor_ A value in order to also consider effectiveness, and not just weakness.
    * @param allow_type_repetitions_ Do you allow two pokemon in your team to share (at least) one type?
    */
   FindBestTeam(const std::vector<Pokemon> &fixed_pokemon_, std::vector<PokeTeam> &best_teams_,
                unsigned regions_ = RegionsFlag::KANTO | RegionsFlag::JOHTO | RegionsFlag::HOENN | RegionsFlag::SINNOH |
                                    RegionsFlag::UNOVA | RegionsFlag::KALOS | RegionsFlag::ALOLA,
                unsigned tipology_ = TipologyFlag::STARTERS | TipologyFlag::FOSSILS |
                                     TipologyFlag::PSEUDOLEGENDARIES | TipologyFlag::ALOLAFORMS |
                                     TipologyFlag::PREEVOLUTIONS,
                bool consider_defence_ = true, bool consider_offence_ = false, int filter_factor_ = 1);

   // Will find the best possible team, for the first _num_fixed_pokemon already fixed in _current_team
   int find_best_teams(unsigned num_threads = 1);

private:
   // The exponential function on integers (for some reason I only find it with double exponent in std, so I think this is faster)
   static unsigned long integer_exponential(unsigned long base, unsigned exponent) {
      return (exponent == 0) ? 1 : base * integer_exponential(base, exponent - 1);
   }

   // the SubTeam struct represents a team of 3 pokemon only
   // the team will contain pokemon in _pokedex._representatives[idx] for idx in members
   struct SubTeam {
      static const unsigned SIZE = 3;
      std::array<unsigned, SIZE> members_idx;
      int upper_bd;   // an upper bound to the value of the SubTeam
      std::array<int, Pokemon::NUM_TYPES> all_matchups;  // the precise values for all the matchups

      SubTeam(const std::array<unsigned, SIZE> &members_, const std::array<int, Pokemon::NUM_TYPES> &all_matchups_);

      unsigned long operator[](unsigned idx) const;
   };

   // creates all possible subteams containing the fixed_pokemon with required_index parity
   void form_all_subteams(unsigned subteam_idx);

   // The loop part of the function form_all_subteams
   void form_all_subteams_iteration(unsigned subteam_idx, unsigned new_member_position);

   // merges the two teams represented in the arrays _all_subteams to form 6-pokemon teams
   void merge_best_subteams(unsigned num_threads);

   // one iteration of the merge_best_subteams() procedure
   void merge_best_subteams_iteration();

   void save_best_teams();

   std::vector<Pokemon> _fixed_pokemon;  // the number of pokemon we specify from constructor
   std::vector<PokeTeam> &_best_teams;  // the list of all best teams found
   int _max_score;  // the max score found in the computation
   std::function<int(const Pokemon *, PokeType)> _evaluation;  // the function to compute which team is the best
   int _filter_factor;  // A number to adjust the computation (if 0, we only consider the bad match-ups, this is weak)
   Pokedex _pokedex;  // The pokedex where to search the other pokemon for the team
   std::array<std::vector<SubTeam>, 2> _all_subteams;  // All the possible subteams (we use also the second only if there are some specified pokemon)
   std::array<std::array<int, Pokemon::NUM_TYPES>, SubTeam::SIZE> _partial_matchups;
   std::array<unsigned, SubTeam::SIZE> _members_subteam;
   std::pair<std::vector<SubTeam> &, std::vector<SubTeam> &> _subteams;  // references to the two subteams
   std::vector<std::pair<unsigned long, unsigned long>> _best_pairings;  // used during merge_best_subteams
   unsigned long _next_idx_first_to_consider;
   std::mutex _max_score_lock, _next_idx_first_to_consider_lock;
};


#endif //POKEMON_TEAM_FINDBESTTEAM_H
