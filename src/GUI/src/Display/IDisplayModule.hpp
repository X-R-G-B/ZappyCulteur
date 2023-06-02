/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** IDisplayModule
*/

namespace GUI {
        enum class WINDOW_MODE {
            WINDOWED,
            FULLSCREEN,
            BORDERLESS
        };

    class IDisplayModule {
        public:
            ~IDisplayModule() = default;
            
            /**
             * @brief Update the display module, with clear, draw and display
             */
            virtual void update() = 0;
            
            /**
             * @brief Check if the window is open
             * @return true if the window is open, false otherwise
             */
            virtual bool isOpen() = 0;

            /**
             * @brief Handle the events of the program
             */
            virtual void handleEvents() = 0;

            /**
             * @brief Set the framerate limit of the window and apply it
             * @param framerateLimit The framerate limit
             */
            virtual void setFramerateLimit(unsigned int framerateLimit) = 0;
    
            /**
             * @brief Get the framerate limit of the window
             * @return The framerate limit
             */
            virtual unsigned int getFramerateLimit() = 0;

            /**
             * @brief Set the width of the window
             * @param width The width of the window
             */
            virtual void setWidth(unsigned int width) = 0;

            /**
             * @brief Set the height of the window
             * @param height The height of the window
             */
            virtual void setHeight(unsigned int height) = 0;

            /**
             * @brief Get the width of the window
             * @return The width of the window
             */
            virtual unsigned int getWidth() = 0;

            /**
             * @brief Get the height of the window
             * @return The height of the window
             */
            virtual unsigned int getHeigth() = 0;

            /**
             * @brief Set the title of the window
             * @param windowTitle The title of the window
             */
            virtual void setWindowTitle(std::string windowTitle) = 0;

            /**
             * @brief Get the title of the window
             * @return The title of the window
             */
            virtual std::string getWindowTitle() = 0;

            /**
             * @brief get the window mode of the window
             * @return WINDOW_MODE The window mode of the window
             */
            virtual WINDOW_MODE getWindowMode() = 0;

            /**
             * @brief Set the window mode for the window
             * @param WINDOW_MODE The window mode of the window and apply it
             */
            virtual void setWindowMode(WINDOW_MODE windowMode) = 0;
    };
}
