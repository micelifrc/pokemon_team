//
// Created by mich on 21/02/19.
//

#ifndef POKEMON_TEAM_POKEMON_H
#define POKEMON_TEAM_POKEMON_H

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <memory>

enum struct PokeType : unsigned {
   Normal = 0,
   Fighting = 1,
   Flying = 2,
   Poison = 3,
   Ground = 4,
   Rock = 5,
   Bug = 6,
   Ghost = 7,
   Steel = 8,
   Fire = 9,
   Water = 10,
   Grass = 11,
   Electric = 12,
   Psychic = 13,
   Ice = 14,
   Dragon = 15,
   Dark = 16,
   Fairy = 17,
   Nothing = 18
};

class Pokemon {
public:
   static const unsigned NUM_TYPES = 18;

   enum struct Effectiveness : int {
      Effective = 0,
      Supereffective = 1,
      NonVeryEffective = -1,
      Ineffective = -10
   };

   explicit Pokemon(int id_ = 0, int total_stats_ = 0, std::string name_ = "", PokeType type1 = PokeType::Nothing,
                    PokeType type2 = PokeType::Nothing) :
         _id{static_cast<unsigned>(id_)}, _total_stats{static_cast<unsigned>(total_stats_)}, _name{std::move(name_)},
         _types{type1, type2} {}

   // Positive if the pokemon has good resistance, negative if the pokemon has bad resistance
   int resistance(PokeType enemy_type) const;

   // Poistive if the pokemon has good offensive value, negative if the pokemon has bad offensive value
   int offensive_effectiveness(PokeType enemy_type) const;

   // Positive if the pokemon has good mismatch, negative if the pokemon has bad mismatch
   int mismatch(PokeType enemy_type) const;

   unsigned id() const { return _id; }

   unsigned total_stats() const { return _total_stats; }

   const std::string &name() const { return _name; }

   const std::pair<PokeType, PokeType> &types() const { return _types; }

private:
   // tells if @p atk is effective against a pokemon of type @p def
   static Effectiveness effectiveness(PokeType atk, PokeType def);

   unsigned _id;
   unsigned _total_stats;  // the sum of the 6 stats of the pokemon
   std::string _name;
   std::pair<PokeType, PokeType> _types;
};

bool share_type(const Pokemon &lhs, const Pokemon &rhs);  // returns true iff @p lhs and @p rhs share at least one type

bool operator==(const Pokemon &lhs, const Pokemon &rhs);  // only looks at the id

bool operator!=(const Pokemon &lhs, const Pokemon &rhs);

std::ostream &operator<<(std::ostream &os, const Pokemon &poke);

class PokeTeam {
public:
   static const unsigned SIZE = 6;

   template<typename... Args>
   explicit
   PokeTeam() : _pokemon_list{Pokemon(), Pokemon(), Pokemon(), Pokemon(), Pokemon(), Pokemon()} {}

   const Pokemon &operator[](unsigned idx) const;

   Pokemon &operator[](unsigned idx);

   unsigned sum_stats() const {
      return _pokemon_list[0].total_stats() + _pokemon_list[1].total_stats() + _pokemon_list[2].total_stats() +
             _pokemon_list[3].total_stats() + _pokemon_list[4].total_stats() + _pokemon_list[5].total_stats();
   }

private:
   std::array<Pokemon, SIZE> _pokemon_list;
};

bool operator<(const PokeTeam &lhs, const PokeTeam &rhs);

bool operator>(const PokeTeam &lhs, const PokeTeam &rhs);

std::ostream &operator<<(std::ostream &os, const PokeTeam &pt);

#endif //POKEMON_TEAM_POKEMON_H
