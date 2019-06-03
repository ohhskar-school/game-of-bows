#ifndef RC_UTILITIES
#define RC_UTILITIES

#include <sstream>

namespace sf
{
	class Sprite;
	class Text;
}

template <typename T>
std::string toString(const T& value);

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

template <typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

#endif
