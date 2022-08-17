#include "StorySpiral.hpp"
#include <math.h>

using namespace WorldGame;
StorySpiral::StorySpiral(int _num_circles)
 : _num_circles(_num_circles) {}

std::vector<StorySpiral::StoryLoc&> StorySpiral::get_previous_stories(int from, int to) {
  std::vector<StoryLoc&> stories;
  for (auto& story : _stories) {
    auto from_angle = from % 360;
    auto to_angle = to % 360;
    auto story_angle = story.location % 360;

    if (story_angle >= from_angle && story_angle <= to_angle) {
      stories.push_back(story);
    }
  }
  return stories;
}

void StorySpiral::put_story(Story story, int location) {
  _stories.push_back(StoryLoc{story, location});
}