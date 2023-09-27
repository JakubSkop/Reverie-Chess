#include "MemSprite.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"

using namespace sf;


MemSprite::MemSprite() :
m_texture    (NULL),
m_textureRect()
{
}

MemSprite::MemSprite(const Texture& texture) :
m_texture    (NULL),
m_textureRect()
{
    setTexture(texture, true);
}

MemSprite::MemSprite(const Texture& texture, const IntRect& rectangle) :
m_texture    (NULL),
m_textureRect()
{
    // Compute the texture area
    setTextureRect(rectangle);
    // Assign texture
    setTexture(texture, false);
}

void MemSprite::Forget(){
    BaseTransform = getTransform() * BaseTransform;

    setPosition(0,0);
    setRotation(0.0);
    setScale(1,1);
}

void MemSprite::setTexture(const Texture& texture, bool resetRect){
    // Recompute the texture area if requested, or if there was no valid texture & rect before
    if (resetRect || (!m_texture && (m_textureRect == sf::IntRect())))
    {
        Vector2i size = Vector2i(texture.getSize());
        setTextureRect(IntRect(0, 0, size.x, size.y));
    }

    // Assign the new texture
    m_texture = &texture;
}

void MemSprite::setTextureRect(const IntRect& rectangle){
    if (rectangle != m_textureRect)
    {
        m_textureRect = rectangle;
        updatePositions();
        updateTexCoords();
    }
}

void MemSprite::setColor(const Color& color){
     // Update the vertices' color
    m_vertices[0].color = color;
    m_vertices[1].color = color;
    m_vertices[2].color = color;
    m_vertices[3].color = color;
}

const Texture& MemSprite::getTexture() const{
    return *m_texture;
}

const IntRect MemSprite::getTextureRect() const{
    return m_textureRect;
}

const Color& MemSprite::getColor() const{
    return m_vertices[0].color;
}

FloatRect MemSprite::getLocalBounds() const{
    const auto width  = static_cast<float>(std::abs(m_textureRect.width));
    const auto height = static_cast<float>(std::abs(m_textureRect.height));

    return FloatRect(sf::Vector2f{0.f, 0.f}, sf::Vector2f{width, height});
}

FloatRect MemSprite::getGlobalBounds() const{
    return (getTransform() * BaseTransform).transformRect(getLocalBounds());
}

void MemSprite::draw(RenderTarget& target, RenderStates states) const{

    //states.transform *= (getTransform() * BaseTransform);
    if (m_texture)
    {
        states.transform *= (getTransform() * BaseTransform);
        states.texture = m_texture;
        target.draw(m_vertices, 4, TriangleStrip, states);
    }
}

void MemSprite::updatePositions()
{
    const FloatRect bounds = getLocalBounds();

    m_vertices[0].position = Vector2f(0, 0);
    m_vertices[1].position = Vector2f(0, bounds.height);
    m_vertices[2].position = Vector2f(bounds.width, 0);
    m_vertices[3].position = Vector2f(bounds.width, bounds.height);
}

void MemSprite::updateTexCoords()
{
    const FloatRect convertedTextureRect(m_textureRect);

    const float left   = convertedTextureRect.left;
    const float right  = left + convertedTextureRect.width;
    const float top    = convertedTextureRect.top;
    const float bottom = top + convertedTextureRect.height;

    m_vertices[0].texCoords = Vector2f(left, top);
    m_vertices[1].texCoords = Vector2f(left, bottom);
    m_vertices[2].texCoords = Vector2f(right, top);
    m_vertices[3].texCoords = Vector2f(right, bottom);
}

const Transform MemSprite::getCompleteTransform() const{
    return (getTransform() * BaseTransform);
}