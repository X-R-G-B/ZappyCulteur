/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** Music
*/

#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include "AComponent.hpp"

namespace GUI {
    namespace Components {
        class Music : public AComponent {
            public:
                Music(
                    const std::string &id,
                    const std::string &path,
                    bool isLooping = true,
                    bool needToPlay = true,
                    float volume = 100,
                    CompType type = CompType::MUSIC
                );
                ~Music() = default;

                void setLooping(bool isLooping);
                void setNeedToPlay(bool needToPlay);
                void setNeedToStop(bool needToStop);
                void setVolume(float volume);
                void play();
                void stop();

                float getVolume() const;
                bool getNeedToPlay() const;
                bool getNeedToStop() const;
                bool getIsPlaying() const;
                bool getIsLooping() const;

            private:
                sf::Music _music;
                float _volume;
                bool _isPlaying;
                bool _isLooping;
                bool _needToPlay;
                bool _needToStop;
        };
    }
}
