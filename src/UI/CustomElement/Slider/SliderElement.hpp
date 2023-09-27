#include "SliderComponent.hpp"
#include "../Label.hpp"
#include "UI/ElementBuilders.hpp"
#include <optional>
#include <memory>
#include <iostream>
#include "General/Constants.hpp"
#include "General/Utilities.hpp"

using IntSlider = Slider<int>;

using PotentialStatePtr = std::optional<std::shared_ptr<State<Element<IntSlider>>>>;
using StatePtr = std::shared_ptr<State<Element<IntSlider>>>;

Element<IntSlider> BasicSliderBuilder(IntSlider image, int minValue, int maxValue, std::function<void(int)> UpdateFunction);