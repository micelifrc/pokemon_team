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
    * @param filter_factors_ Values in order to also consider effectiveness, and not just weakness.
    * @param allow_type_repetitions_ Do you allow two pokemon in your team to share (at least) one type?
    */
   FindBestTeam(const std::vector<Pokemon> &fixed_pokemon_, std::vector<PokeTeam> &best_teams_,
                unsigned regions_ = RegionsFlag::KANTO | RegionsFlag::JOHTO | RegionsFlag::HOENN | RegionsFlag::SINNOH |
                                    RegionsFlag::UNOVA | RegionsFlag::KALOS | RegionsFlag::ALOLA,
                unsigned tipology_ = TypologyFlag::STARTERS | TypologyFlag::FOSSILS |
                                     TypologyFlag::PSEUDOLEGENDARIES | TypologyFlag::ALOLAFORMS |
                                     TypologyFlag::PREEVOLUTIONS);

   // Will find the best possible team, for the first _num_fixed_pokemon already fixed in _current_team
   int find_best_teams(unsigned num_threads = 1, bool consider_defence = true, bool consider_offence = false,
                       bool allow_repetitions = true,
                       const std::array<int, static_cast<unsigned>(PokeType::NUM_TYPES)> &filter_factors =
                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1});

   int find_best_teams(unsigned num_threads, bool consider_defence, bool consider_offence, bool allow_repetitions,
                       int filter_factor);

private:
   struct UBRange {
      unsigned long start, end;
      int upper_bd;

      UBRange(unsigned long start_, unsigned long end_, int upper_bd_) : start{start_}, end{end_},
                                                                         upper_bd{upper_bd_} {}
   };

   struct UBSegment : public UBRange {
      unsigned long const_coord;

      UBSegment(unsigned long const_coord_, unsigned long start_, unsigned long end_, int upper_bd_) : const_coord{
            const_coord_}, UBRange(start_, end_, upper_bd_) {}
   };

   struct UBRectangle {
      std::array<unsigned long, 2> start, end;
      int upper_bd;

      UBRectangle(unsigned long start0_, unsigned long end0_, unsigned long start1_, unsigned long end1_, int upper_bd_)
            :
            start{start0_, start1_}, end{end0_, end1_}, upper_bd{upper_bd_} {}
   };

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
      std::array<int, static_cast<unsigned>(PokeType::NUM_TYPES)> all_matchups;  // the precise values for all the matchups

      SubTeam(const std::array<unsigned, SIZE> &members_,
              const std::array<int, static_cast<unsigned>(PokeType::NUM_TYPES)> &all_matchups_);

      unsigned long operator[](unsigned idx) const;
   };

   // creates all possible subteams containing the fixed_pokemon with required_index parity
   void form_all_subteams(unsigned subteam_idx);

   // The loop part of the function form_all_subteams
   void form_all_subteams_iteration(unsigned subteam_idx, unsigned new_member_position);

   // Initialize the vector _all_rectangles
   void initialize_all_rectangles();

   void update_ubranges(const std::vector<SubTeam> &all_subteams, std::vector<UBRange> &all_ubranges);

   // update the vector of _segments including all the segments in rectangles in *_rectangle_iter
   void update_segments();

   // merges the two teams represented in the arrays _all_subteams to form 6-pokemon teams
   void merge_best_subteams(unsigned num_threads);

   // one iteration of the merge_best_subteams() procedure
   void merge_best_subteams_iteration();

   void save_best_teams();

   std::vector<Pokemon> _fixed_pokemon;  // the pokemon we specify from constructor
   std::vector<PokeTeam> &_best_teams;  // the list of all best teams found
   int _max_score;  // the max score found in the computation
   std::function<int(const Pokemon *, PokeType)> _evaluation;  // the function to compute which team is the best
   std::array<int, static_cast<unsigned>(PokeType::NUM_TYPES)> _filter_factors;  // Numbes to adjust the computation (if 0, we only consider the bad match-ups, this is weak)
   unsigned _repetition_step;
   Pokedex _pokedex;  // The pokedex where to search the other pokemon for the team
   std::array<std::shared_ptr<std::vector<SubTeam>>, 2> _all_subteams;  // All the possible subteams (we use also the second only if there are some specified pokemon)
   std::vector<std::pair<unsigned long, unsigned long>> _best_pairings;  // used during merge_best_subteams
   std::array<std::array<int, static_cast<unsigned>(PokeType::NUM_TYPES)>, SubTeam::SIZE> _partial_matchups;
   std::array<unsigned, SubTeam::SIZE> _members_subteam;
   std::vector<std::vector<UBRectangle>> _all_rectangles;  // used to partition _all_subteams[0]x_all_subteams[1] in rectangles with same upper_bound
   std::vector<std::vector<UBRectangle>>::iterator _rectangle_iter;  // an iterator on _all_rectangles, denoting the next to addd
   std::vector<UBSegment> _segments;  // the segments to process with current upper_bd
   std::mutex _max_score_lock, _segments_lock;
};


#endif //POKEMON_TEAM_FINDBESTTEAM_H
