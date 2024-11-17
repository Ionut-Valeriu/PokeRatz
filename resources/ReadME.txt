In this file you will find explanation for .txt files that are used in configuration:

--- In "resources/config/config.txt" ---

-The configuration for WINDOW is the following:
Window W H FR FS R G B
    Keyword             Window
    Window width        W           int
    Window height       H           int
    Framerate limit     FR          int
    Fullscreen          FS          bool (0/1)
    Background color    (R,G,B)     (unsigned char, unsigned char, unsigned char)

-The configuration for ASSETS is the following:
Assets path
    Keyword                                                             Assets
    Path of assets config file, usually "resources/config/assets.txt"   path    std::string

--- In "resources/config/assets.txt" ---

-The configuration for FONT is the following:
Font name path
    Keyword                                             Font
    Name of the font                                    name    std::string
    Path to the font, usually "resources/fonts/*.ttf"   path    std::string

-The configuration for TEXTURE is the following:
Texture name path
    Keyword                                                 Texture
    Name of the texture                                     name    std::string
    Path to the texture, usually "resources/images/*.png"   path    std::string

-The configuration for ANIMATION is the following:
Animation A_name T_name FR S
    Keyword                             Animation
    Name of the animation               A_name      std::string
    Name of the texture of animation    T_name      std::string
    Number of frames                    FR          int
    Speed                               S           int