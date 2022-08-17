#ifndef WORLDGAME_DECK_HPP
#define WORLDGAME_DECK_HPP

#include <string>
#include "../inspirator.hpp"

namespace WorldGame {
  class WorldDeck {
  public:
    WorldDeck();

    void load_deck();
    void save_deck();
  private:
    Inspirator::Deck _deck;
    Inspirator::CardFactory _factory;
  };
}

#endif // WORLDGAME_DECK_HPP