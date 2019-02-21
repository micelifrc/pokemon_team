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

   explicit Pokemon(unsigned id_ = 0, std::string name_ = "", Type type1 = Type::Nothing, Type type2 = Type::Nothing) :
         _id{id_}, _name{std::move(name_)}, _types{type1, type2} {}

   explicit Pokemon(int id_, std::string name_ = "", Type type1 = Type::Nothing, Type type2 = Type::Nothing) :
         _id{static_cast<unsigned>(id_)}, _name{std::move(name_)}, _types{type1, type2} {}

   // Positive if the pokemon has good resistance, negative if the pokemon has bad resistance
   int resistance(Type enemy_type) const;

   // Poistive if the pokemon has good offensive value, negative if the pokemon has bad offensive value
   int offensive_effectiveness(Type enemy_type) const;

   // Positive if the pokemon has good mismatch, negative if the pokemon has bad mismatch
   int mismatch(Type enemy_type) const;

   unsigned id() const { return _id; }

   const std::string &name() const { return _name; }

   const std::pair<Type, Type> &types() const { return _types; }

private:
   // tells if @p atk is effective against a pokemon of type @p def
   static Effectiveness effectiveness(Type atk, Type def);

   unsigned _id;
   std::string _name;
   std::pair<Type, Type> _types;
};

bool operator<(const Pokemon &lhs, const Pokemon &rhs);

bool operator>(const Pokemon &lhs, const Pokemon &rhs);

bool operator<=(const Pokemon &lhs, const Pokemon &rhs);

bool operator>=(const Pokemon &lhs, const Pokemon &rhs);

bool operator==(const Pokemon &lhs, const Pokemon &rhs);

bool operator!=(const Pokemon &lhs, const Pokemon &rhs);

std::ostream &operator<<(std::ostream &os, const Pokemon &poke);

// This class represents a subset of a pokedex of a certain region
class Pokedex {
public:

   Pokedex();

   const std::vector<const Pokemon *> &representatives() const { return _representatives; }

   template<typename... Args>
   void add_pokemon(Args... args);

   template<typename... Args>
   void remove_pokemon(Args... args);

   // extracts the vector of representatives. If you use add_pokemon or remove_pokemon,
   // @p _representatives will be wrong until you call extract_representatives again
   void extract_representatives();

private:
   // A matrix containing pointers to vectors containing all the pokemon for that pair of type in the pokedex
   // The order of the types is not relevant, and if a pokemon is single-type, it is in the diagonal of the matrix
   std::vector<std::vector<std::shared_ptr<std::vector<Pokemon> > > > _matrix;
   // One pokemon for each pair of types in the pokedex
   std::vector<const Pokemon *> _representatives;
};

template<typename... Args>
void Pokedex::add_pokemon(Args... args) {
   Pokemon poke{args...};
   Pokemon::Type second_type = (poke.types().second == Pokemon::Type::Nothing) ? poke.types().first
                                                                               : poke.types().second;
   for (const auto &similar_poke: *_matrix[static_cast<unsigned>(poke.types().first)][static_cast<unsigned>(second_type)]) {
      if (similar_poke == poke) {
         return;
      }
   }
   _matrix[static_cast<unsigned>(poke.types().first)][static_cast<unsigned>(second_type)]->emplace_back(poke);
}

template<typename... Args>
void Pokedex::remove_pokemon(Args... args) {
   Pokemon poke{args...};
   Pokemon::Type second_type = (poke.types().second == Pokemon::Type::Nothing) ? poke.types().first
                                                                               : poke.types().second;
   unsigned idx = 0;
   while (idx != _matrix[static_cast<unsigned>(poke.types().first)][static_cast<unsigned>(second_type)]->size()) {
      if ((*_matrix[static_cast<unsigned>(poke.types().first)][static_cast<unsigned>(second_type)])[idx] == poke) {
         (*_matrix[static_cast<unsigned>(poke.types().first)][static_cast<unsigned>(second_type)])[idx] =
               _matrix[static_cast<unsigned>(poke.types().first)][static_cast<unsigned>(second_type)]->back();
         _matrix[static_cast<unsigned>(poke.types().first)][static_cast<unsigned>(second_type)]->pop_back();
      } else {
         ++idx;
      }
   }
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
