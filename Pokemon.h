//
// Created by mich on 21/02/19.
//

#ifndef POKEMON_TEAM_POKEMON_H
#define POKEMON_TEAM_POKEMON_H

#include <iostream>
#include <string>
#include <array>
#include <vector>

class Pokemon {
public:
   static const unsigned NUM_TYPES = 18;

   enum struct Type : unsigned {
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

   enum struct Effectiveness : int {
      Effective = 0,
      Supereffective = 1,
      NonVeryEffective = -1,
      Ineffective = -10
   };

   explicit Pokemon(std::string name_ = "", Type type1 = Type::Nothing, Type type2 = Type::Nothing) :
         _name{std::move(name_)}, _types{type1, type2} {}

   // Positive if the pokemon has good resistance, negative if the pokemon has bad resistance
   int resistance(Type enemy_type) const;

   // Poistive if the pokemon has good offensive value, negative if the pokemon has bad offensive value
   int offensive_effectiveness(Type enemy_type) const;

   // Positive if the pokemon has good mismatch, negative if the pokemon has bad mismatch
   int mismatch(Type enemy_type) const;

   const std::string &name() const { return _name; }

   const std::pair<Type, Type> &types() const { return _types; }

private:
   // tells if @p atk is effective against a pokemon of type @p def
   static Effectiveness effectiveness(Type atk, Type def);

   std::string _name;
   std::pair<Type, Type> _types;
};

std::ostream &operator<<(std::ostream &os, const Pokemon &poke);

// This class represents a subset of a pokedex of a certain region
class Pokedex {
public:
   typedef std::pair<Pokemon::Type, Pokemon::Type> TypePair;
   typedef unsigned long Index;

   inline const std::vector<std::pair<Pokemon, Index>> &all_pokemon() const;

   inline const std::vector<std::pair<TypePair, std::vector<Index>>> &all_type_pairs() const;

   template<typename... Args>
   void add_pokemon(Args... args);

private:
   // each pokemon of the pokedex appears as first, and its type is in _all_type_pairs[second].first
   std::vector<std::pair<Pokemon, Index>> _all_pokemon;
   // all the pairs of types (non-sorted) in the pokedex, with the list of indices of pokemon with that type-pair
   std::vector<std::pair<TypePair, std::vector<Index>>> _all_type_pairs;
};

const std::vector<std::pair<Pokemon, Pokedex::Index>> &Pokedex::all_pokemon() const {
   return _all_pokemon;
}

const std::vector<std::pair<Pokedex::TypePair, std::vector<Pokedex::Index>>> &Pokedex::all_type_pairs() const {
   return _all_type_pairs;
}

template<typename... Args>
void Pokedex::add_pokemon(Args... args) {
   Pokemon poke{args...};
   TypePair types =
         poke.types().first < poke.types().second ? TypePair{poke.types().first, poke.types().second} : TypePair{
               poke.types().second, poke.types().first};
   for (unsigned long type_idx = 0; type_idx != _all_type_pairs.size(); ++type_idx) {
      if (types.first == _all_type_pairs[type_idx].first.first and
          types.second == _all_type_pairs[type_idx].first.second) {
         _all_type_pairs[type_idx].second.emplace_back(_all_pokemon.size());
         _all_pokemon.emplace_back(poke, type_idx);
         return;
      }
   }
   _all_type_pairs.emplace_back(types, std::vector<Index>(1, _all_pokemon.size()));
   _all_pokemon.emplace_back(poke, _all_type_pairs.size() - 1);
}

class PokeTeam {
public:
   template<typename... Args>
   explicit
   PokeTeam() : _pokemon_list{Pokemon(), Pokemon(), Pokemon(), Pokemon(), Pokemon(), Pokemon()} {}

   const Pokemon &operator[](unsigned idx) const;

   Pokemon &operator[](unsigned idx);

private:
   std::array<Pokemon, 6> _pokemon_list;
};

std::ostream &operator<<(std::ostream &os, const PokeTeam &pt);

#endif //POKEMON_TEAM_POKEMON_H
