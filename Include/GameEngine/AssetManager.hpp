#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <memory>

namespace GenericGameEngine
{
    class AssetManager
    {
        public:
            AssetManager() = default;
            ~AssetManager() = default;

            /* 
            * The texture is added from a file, thus specify as arg file path where texture is loaded from.
            * Also, it is given the index where the texture shall be inserted.  
            * The extra boolean arg allows the texture to be repetead such as it can fill a rectangle shape.
            */
            void addTexture(int id, const std::string& filePath, bool wantRepeated = false);
            /* 
            * The font is added from a file, thus specify as arg file path where texture is loaded from.
            * Also, it is given the index where the font shall be inserted. 
            */
            void addFont(int id, const std::string& filePath);
            /* 
            * Likewise font, sound is added from a file, thus specify as arg file path where texture is loaded from.
            * Also, it is given the index where the font shall be inserted. 
            */
            void addSoundBuffer(int id, const std::string& filePath);

            // get texture or font with the specified id
            const sf::Texture& getTexture(int id) const {return *mTextures.at(id).get();};
            const sf::Font& getFont(int id) const {return *mFonts.at(id).get();};
            const sf::SoundBuffer& getSoundBuffer(int id) const {return *mSoundBuffers.at(id).get();};

        private:
            std::map<int, std::unique_ptr<sf::Texture>> mTextures;
            std::map<int, std::unique_ptr<sf::Font>> mFonts;
            std::map<int, std::unique_ptr<sf::SoundBuffer>> mSoundBuffers;
    };
}