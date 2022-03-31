#include "GameEngine/AssetManager.hpp"

namespace GenericGameEngine
{
    using namespace std;

    void AssetManager::addTexture(int id, const std::string& filePath, bool wantRepeated)
    {
        unique_ptr<sf::Texture> uPtrTexture = make_unique<sf::Texture>();

        if(uPtrTexture->loadFromFile(filePath))
        {
            uPtrTexture->setRepeated(wantRepeated);
            //insert the new texture at the specified id, if it does not exist yet with that id
            mTextures[id] = move(uPtrTexture);
        }
    }

    void AssetManager::addFont(int id, const std::string& filePath)
    {
        unique_ptr<sf::Font> uPtrFont = make_unique<sf::Font>();

        if(uPtrFont->loadFromFile(filePath))
        {
            //insert the new font at the specified id, if it does not exist yet with that id
            mFonts[id] = move(uPtrFont);
        }
    }

    void AssetManager::addSoundBuffer(int id, const std::string& filePath)
    {
        unique_ptr<sf::SoundBuffer> uPtrSoundBuffer = make_unique<sf::SoundBuffer>();

        if(uPtrSoundBuffer->loadFromFile(filePath))
        {
            //insert the new font at the specified id, if it does not exist yet with that id
            mSoundBuffers[id] = move(uPtrSoundBuffer);
        }
    }

}