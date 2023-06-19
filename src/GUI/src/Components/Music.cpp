/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Music
*/

#include "Music.hpp"

namespace GUI {
    namespace Components {

        Music::Music(
            const std::string &id,
            const std::string &path,
            bool isLooping,
            bool needToPlay,
            float volume,
            CompType type
        ) : AComponent(id, type),
            _volume(volume),
            _isPlaying(false),
            _isLooping(isLooping),
            _needToPlay(needToPlay)
        {
            _music.openFromFile(path);
            _music.setLoop(_isLooping);
            _music.setVolume(_volume);
        }

        void Music::setLooping(bool isLooping)
        {
            _isLooping = isLooping;
            _music.setLoop(_isLooping);
        }

        void Music::setNeedToPlay(bool needToPlay)
        {
            _needToPlay = needToPlay;
        }

        void Music::setNeedToStop(bool needToStop)
        {
            _needToStop = needToStop;
        }

        void Music::play()
        {
            _music.play();
        }

        void Music::stop()
        {
            _music.stop();
        }

        void Music::setVolume(float volume)
        {
            _volume = volume;
            _music.setVolume(_volume);
        }

        float Music::getVolume() const
        {
            return _volume;
        }

        bool Music::getNeedToPlay() const
        {
            return _needToPlay;
        }

        bool Music::getNeedToStop() const
        {
            return _needToStop;
        }

        bool Music::getIsPlaying() const
        {
            return _isPlaying;
        }

        bool Music::getIsLooping() const
        {
            return _isLooping;
        }
    }
}
