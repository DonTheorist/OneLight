#ifndef FLUX_TEXTDRAWER_H
#define FLUX_TEXTDRAWER_H

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <iterator>
#include <memory>

#include "FluxTextureMaterial.hpp"
#include "FluxSprite.hpp"
#include "FluxSpriteBatch.hpp"
#include "FluxRectangle2D.hpp"
#include "FluxVector2.hpp"
#include "FluxTexture.hpp"
#include "rapidxml.hpp"

namespace Flux
{
    class TextDrawer
    {
        public:
            TextDrawer(const Vector2 &position, std::shared_ptr<Texture> texture, const std::string &xmlMap, const Colour &colour=Colour::WHITE);
            ~TextDrawer();

            std::shared_ptr<SpriteBatch> getSpriteBatch();
            void setString(const std::string &String);

            Colour getColour();
            void setColour(const Colour &colour);

            unsigned int getFontSize();
            void setFontSize(const unsigned fontSize);

            void setDepth(const float dpeth);
            float getWidth();

            void centreText(const float screenWidth);
    
        private:
            Vector2 position;
            Colour colour;
            std::shared_ptr<Material> material;
            std::shared_ptr<SpriteBatch> sb;
            std::map<char, Rectangle2D> characterMap;
            std::map<char, Vector2> offset;
            std::string string = "";
            unsigned int originalFontSize, fontSize;
            float fontScale;

    };

}

#endif

