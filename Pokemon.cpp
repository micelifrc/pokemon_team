//
// Created by mich on 21/02/19.
//

#include "Pokemon.h"

Pokemon::Pokemon(int id_, int total_stats_, std::string name_, PokeType type1, PokeType type2) :
      _id{static_cast<unsigned>(id_)}, _total_stats{static_cast<unsigned>(total_stats_)}, _name{std::move(name_)},
      _types{type1, type2} {
   if (type1 == PokeType::NUM_TYPES or type2 == PokeType::NUM_TYPES) {
      throw std::logic_error("Cannot create pokemon with type NUM_TYPES. This is not a legal type");
   }
}

int Pokemon::resistance(PokeType enemy_type) const {
   return (_types.first == _types.second) ? std::min(-static_cast<int>(effectiveness(enemy_type, _types.first)), 1)
                                          : std::min(-static_cast<int>(effectiveness(enemy_type, _types.first)) -
                                                     static_cast<int>(effectiveness(enemy_type, _types.second)), 2);
}

int Pokemon::offensive_effectiveness(PokeType enemy_type) const {
   return std::max(std::max(static_cast<int>(effectiveness(_types.first, enemy_type)),
                            static_cast<int>(effectiveness(_types.second, enemy_type))), -2);
}

int Pokemon::mismatch(PokeType enemy_type) const {
   return resistance(enemy_type) + offensive_effectiveness(enemy_type);
}

Pokemon::Effectiveness Pokemon::effectiveness(PokeType atk, PokeType def) {
   return _resistance_table[static_cast<unsigned>(atk)][static_cast<unsigned>(def)];
}

const std::array<std::array<Pokemon::Effectiveness, static_cast<unsigned>(PokeType::NUM_TYPES)>, static_cast<unsigned>(PokeType::NUM_TYPES)> Pokemon::_resistance_table{
      std::array<Pokemon::Effectiveness, static_cast<unsigned>(PokeType::NUM_TYPES)>{
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::NonVery, Effectiveness::Regular, Effectiveness::Ineffective,
            Effectiveness::NonVery, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::Regular},
      std::array<Pokemon::Effectiveness, static_cast<unsigned>(PokeType::NUM_TYPES)>{
            Effectiveness::Super, Effectiveness::Regular, Effectiveness::NonVery, Effectiveness::NonVery,
            Effectiveness::Regular, Effectiveness::Super, Effectiveness::NonVery, Effectiveness::Ineffective,
            Effectiveness::Super, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::NonVery, Effectiveness::Super, Effectiveness::Regular,
            Effectiveness::Super, Effectiveness::NonVery},
      std::array<Pokemon::Effectiveness, static_cast<unsigned>(PokeType::NUM_TYPES)>{
            Effectiveness::Regular, Effectiveness::Super, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::NonVery, Effectiveness::Super, Effectiveness::Regular,
            Effectiveness::NonVery, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Super,
            Effectiveness::NonVery, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::Regular},
      std::array<Pokemon::Effectiveness, static_cast<unsigned>(PokeType::NUM_TYPES)>{
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::NonVery,
            Effectiveness::NonVery, Effectiveness::NonVery, Effectiveness::Regular, Effectiveness::NonVery,
            Effectiveness::Ineffective, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Super,
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::Super},
      std::array<Pokemon::Effectiveness, static_cast<unsigned>(PokeType::NUM_TYPES)>{
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Ineffective, Effectiveness::Super,
            Effectiveness::Regular, Effectiveness::Super, Effectiveness::NonVery, Effectiveness::Regular,
            Effectiveness::Super, Effectiveness::Super, Effectiveness::Regular, Effectiveness::NonVery,
            Effectiveness::Super, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::Regular},
      std::array<Pokemon::Effectiveness, static_cast<unsigned>(PokeType::NUM_TYPES)>{
            Effectiveness::Regular, Effectiveness::NonVery, Effectiveness::Super, Effectiveness::Regular,
            Effectiveness::NonVery, Effectiveness::Regular, Effectiveness::Super, Effectiveness::Regular,
            Effectiveness::NonVery, Effectiveness::Super, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Super, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::Regular},
      std::array<Pokemon::Effectiveness, static_cast<unsigned>(PokeType::NUM_TYPES)>{
            Effectiveness::Regular, Effectiveness::NonVery, Effectiveness::NonVery, Effectiveness::NonVery,
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::NonVery,
            Effectiveness::NonVery, Effectiveness::NonVery, Effectiveness::Regular, Effectiveness::Super,
            Effectiveness::Regular, Effectiveness::Super, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Super, Effectiveness::NonVery},
      std::array<Pokemon::Effectiveness, static_cast<unsigned>(PokeType::NUM_TYPES)>{
            Effectiveness::Ineffective, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Super,
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::Super, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::NonVery, Effectiveness::Regular},
      std::array<Pokemon::Effectiveness, static_cast<unsigned>(PokeType::NUM_TYPES)>{
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::Super, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::NonVery, Effectiveness::NonVery, Effectiveness::NonVery, Effectiveness::Regular,
            Effectiveness::NonVery, Effectiveness::Regular, Effectiveness::Super, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::Super},
      std::array<Pokemon::Effectiveness, static_cast<unsigned>(PokeType::NUM_TYPES)>{
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::NonVery, Effectiveness::Super, Effectiveness::Regular,
            Effectiveness::Super, Effectiveness::NonVery, Effectiveness::NonVery, Effectiveness::Super,
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Super, Effectiveness::NonVery,
            Effectiveness::Regular, Effectiveness::Regular},
      std::array<Pokemon::Effectiveness, static_cast<unsigned>(PokeType::NUM_TYPES)>{
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Super, Effectiveness::Super, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::Super, Effectiveness::NonVery, Effectiveness::NonVery,
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::NonVery,
            Effectiveness::Regular, Effectiveness::Regular},
      std::array<Pokemon::Effectiveness, static_cast<unsigned>(PokeType::NUM_TYPES)>{
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::NonVery, Effectiveness::NonVery,
            Effectiveness::Super, Effectiveness::Super, Effectiveness::NonVery, Effectiveness::Regular,
            Effectiveness::NonVery, Effectiveness::NonVery, Effectiveness::Super, Effectiveness::NonVery,
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::NonVery,
            Effectiveness::Regular, Effectiveness::Regular},
      std::array<Pokemon::Effectiveness, static_cast<unsigned>(PokeType::NUM_TYPES)>{
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Super, Effectiveness::Regular,
            Effectiveness::Ineffective, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Super, Effectiveness::NonVery,
            Effectiveness::NonVery, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::NonVery,
            Effectiveness::Regular, Effectiveness::Regular},
      std::array<Pokemon::Effectiveness, static_cast<unsigned>(PokeType::NUM_TYPES)>{
            Effectiveness::Regular, Effectiveness::Super, Effectiveness::Regular, Effectiveness::Super,
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::NonVery, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::NonVery, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Ineffective, Effectiveness::Regular},
      std::array<Pokemon::Effectiveness, static_cast<unsigned>(PokeType::NUM_TYPES)>{
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Super, Effectiveness::Regular,
            Effectiveness::Super, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::NonVery, Effectiveness::NonVery, Effectiveness::NonVery, Effectiveness::Super,
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::NonVery, Effectiveness::Super,
            Effectiveness::Regular, Effectiveness::Regular},
      std::array<Pokemon::Effectiveness, static_cast<unsigned>(PokeType::NUM_TYPES)>{
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::NonVery, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Super,
            Effectiveness::Regular, Effectiveness::Ineffective},
      std::array<Pokemon::Effectiveness, static_cast<unsigned>(PokeType::NUM_TYPES)>{
            Effectiveness::Regular, Effectiveness::NonVery, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Super,
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::Super, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::NonVery, Effectiveness::NonVery},
      std::array<Pokemon::Effectiveness, static_cast<unsigned>(PokeType::NUM_TYPES)>{
            Effectiveness::Regular, Effectiveness::Super, Effectiveness::Regular, Effectiveness::NonVery,
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::NonVery, Effectiveness::NonVery, Effectiveness::Regular, Effectiveness::Regular,
            Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Regular, Effectiveness::Super,
            Effectiveness::Super, Effectiveness::Regular}
};

bool share_type(const Pokemon &lhs, const Pokemon &rhs) {
   return lhs.types().first == rhs.types().first or lhs.types().first == rhs.types().second or
          lhs.types().second == rhs.types().first or lhs.types().second == rhs.types().second;
}

bool operator==(const Pokemon &lhs, const Pokemon &rhs) {
   return lhs.id() == rhs.id() and lhs.name() == rhs.name();
}

bool operator!=(const Pokemon &lhs, const Pokemon &rhs) {
   return not(lhs == rhs);
}

std::ostream &operator<<(std::ostream &os, const Pokemon &poke) {
   return os << poke.name();
}

const Pokemon &PokeTeam::operator[](unsigned idx) const {
   if (idx >= SIZE) {
      throw std::out_of_range(
            "Invalid call of operator[] for PokeTeam. There are only " + std::to_string(PokeTeam::SIZE) +
            " pokemon in the team");
   }
   return _pokemon_list[idx];
}

Pokemon &PokeTeam::operator[](unsigned idx) {
   return const_cast<Pokemon &>(static_cast<const PokeTeam &>(*this)[idx]);
}

bool operator<(const PokeTeam &lhs, const PokeTeam &rhs) {
   return lhs.sum_stats() < rhs.sum_stats();
}

bool operator>(const PokeTeam &lhs, const PokeTeam &rhs) {
   return lhs.sum_stats() > rhs.sum_stats();
}

std::ostream &operator<<(std::ostream &os, const PokeTeam &pt) {
   os << '[' << pt[0];
   for (unsigned idx = 1; idx != PokeTeam::SIZE; ++idx) {
      os << ", " << pt[idx];
   }
   return os << "] = " << pt.sum_stats();
}