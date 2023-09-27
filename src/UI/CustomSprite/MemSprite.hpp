#pragma once

#include "SFML/Graphics.hpp"

using namespace sf;

//A custom sprite class that "forgets"
class MemSprite : public Drawable, public Transformable{

    public:

        // Creates an empty sprite with no source texture.
        MemSprite();

        // Construct the sprite from a source texture
        explicit MemSprite(const Texture& texture);

        explicit MemSprite(Texture&& texture) = delete;

        // Construct the sprite from a sub-rectangle of a source texture
        MemSprite(const Texture& texture, const IntRect& rectangle);

        // Overwrite its history of transformation. The Sprite now thinks all prior transformations are the sprite's default
        void Forget();

        // Change the source texture of the sprite
        void setTexture(const Texture& texture, bool resetRect = false);
        void setTexture(Texture&& texture, bool resetRect = false) = delete;

        // Set the sub-rectangle of the texture that the sprite will display
        void setTextureRect(const IntRect& rectangle);

        // Set the global color of the sprite
        void setColor(const Color& color);

        // Get the source texture of the sprite
        const Texture& getTexture() const;

        // Get the sub-rectangle of the texture displayed by the sprite
        const IntRect getTextureRect() const;

        // Get the global color of the sprite
        const Color& getColor() const;

        FloatRect getLocalBounds() const;

        FloatRect getGlobalBounds() const;

        const Transform getCompleteTransform() const;

    private:

        // Draw the sprite to a render target
        void draw(RenderTarget& target, RenderStates states) const override;

        void updatePositions();

        void updateTexCoords();

        Vertex m_vertices[4];
        const Texture* m_texture;
        IntRect m_textureRect;
        Transform BaseTransform = Transform::Identity;

};