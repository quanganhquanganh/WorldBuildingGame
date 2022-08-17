#ifndef WORLDGAME_SAVEGAME_HPP
#define WORLDGAME_SAVEGAME_HPP

#include <string>

namespace WorldGame {
  class SaveGame {
  public:
    /**
     * @brief SaveGame constructor
     *
     * @param save_file_name
     * The name of the save file.
     * @param version
     * The version of the save file.
     */
    SaveGame(std::string save_file_name, int version);
    ~SaveGame();
    
    /**
     * @brief close
     * Closes the save file.
     */
    void close();
  };

  class RestoreGame {
  public:
    RestoreGame();
    ~RestoreGame();
  };
}

#endif // SAVEGAME_HPP