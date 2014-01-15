/**
 * @~english
 * @taomoduledescription{Filters, Filters}
 * <tt>import Filters</tt> - Apply filters on imported images.@n
 *
 * This module allows you to apply some basic filtering on your textures.
 *
 * For example, the following code will show how to detect outlines and add some iterative blur to it.
 * @include filters.ddd
 *
 * @image html filters.png "Filters applied to an image"
 *
 * @note To improve performance in Tao, it is recommended to render to files the result texture before to reload it in Tao.
 *
 * @endtaomoduledescription{Filters}
 *
 * @~french
 * @taomoduledescription{Filters, Filtrage d'images}
 * <tt>import Filters</tt> - Applique des filtres sur des images.@n
 *
 * Ce module vous permet d'effectuer certains filtrages sur des textures.
 *
 * Par exemple, le code qui suit montre une détection de contours et un filtre
 * de flou itératif :
 * @include filters.ddd
 *
 * @image html filters.png "Application de filtres d'images"
 *
 * @note Pour améliorer les performances, vous pouvez enregister le résultat
 * dans un fichier puis le charger sous forme de texture.
 *
 * @endtaomoduledescription{Filters}
 *
 * @~
 * @{
 */

/**
 * @~english
 * Applies a Gaussian filter on current texture.
 * It can be used to add blur on an image for instance.
 *
 * @param Radius Radius for the filter in pixels
 *
 * @~french
 * Applique un filtre Gaussien sur la texture courante.
 * Ce filtre permet d'ajouter du flou à l'image.
 *
 * @param Radius Rayon du filtre en pixels
 */
gaussian(Radius:integer);

/**
 * @~english
 * Applies a Gaussian filter on current texture.
 * It can be used to add blur on an image for instance.
 *
 * @param RH Horizontal radius for the filter in pixels
 * @param RV Vertical radius for the filter in pixels
 *
 * @~french
 * Applique un filtre Gaussien sur la texture courante.
 * Ce filtre permet d'ajouter du flou à l'image.
 *
 * @param RH Rayon du filtre en pixels le long de l'axe horizontal
 * @param RV Rayon du filtre en pixels le long de l'axe vertical
 * @~
 * @since 1.018 (Tao 1.45)
 */
gaussian(RH:integer, RV:integer);

/**
 * @~english
 * Applies a Mean filter on the current texture.
 * It can be used to remove noise of an image for instance.
 *
 * @~french
 * Applique un filtre moyenneur sur la texture courante.
 * Ce filtre permet de réduire le bruit de l'image.
 */
mean();

/**
 * @~english
 * Applies an Embross filter on the current texture.
 *
 * @~french
 * Applique un filtre de relief sur la texture courante.
 */
emboss();

/**
 * @~english
 * Applies a Sharpness filter on the current texture.
 * It can be used to highlight details of an image for instance.
 *
 * @~french
 * Applique un filtre de netteté à la texture courante.
 * Ce filtre permet d'améliorer le piqué de l'image.
 */
sharpness();

/**
 * @~english
 *
 * Applies a Laplacian filter on the current texture.
 * It can be used to detect oulines of an image for instance.
 *
 * @~french
 * Applique un filtre Laplacien à la texture courante.
 * Ce filtre permet de faire une détection de contour.
 */
laplacian();

/**
 * @~english
 * Defines color levels for Black & White filter.
 * These levels define how color components are mixed to produce black
 * and white. The level of gray is given by the formula:
 * <tt>cr*r + cg*g + cb*b</tt>, where @c r, @c g and @c b are the red, green
 * and blue components of the color to be converted to black and white.
 *
 * @param cr Amount of red component. Default value is 0.299.
 * @param cg Amount of green component. Default value is 0.587.
 * @param cb Amount of blue component. Default value is 0.144.
 * @param ca Amount of alpha component. Default value is 0.0
 *
 * @note This function is optional to apply Black & White filter
 *
 * @~french
 * Définit les coefficients de mélange pour le filtre noir et blanc.
 * Ces coefficients définissent comment les composantes de couleur sont
 * mélangées pour obtenir un niveau de gris.
 * Le niveau de gris est :
 * <tt>cr*r + cg*g + cb*b</tt>, où @c r, @c g et @c b sont les composantes
 * de la couleur à convertir en niveau de gris.
 *
 * @param cr Quantité de rouge. Par défaut, 0.299.
 * @param cg Quantité de vert. Par défaut, 0.587.
 * @param cb Quantité de bleu. Par défaut, 0.114.
 * @param ca Quantité d'opacité. Par défaut, 0.
 */
black_and_white_levels(cr:real, cg:real, cb:real, ca:real);

/**
 * @~english
 * Applies a Black & White filter on the current texture.
 * It can be used to transform a color image into a black & white one.
 *
 * @note color levels can be defined for this filter thanks to @ref black_and_white_levels
 *
 * @~french
 * Convertit la texture courante en niveaux de gris.
 * La formule de conversion peut être ajustée grâce à
 * @ref black_and_white_levels.
 */
black_and_white();

/**
 * @~english
 * Applies a Sepia filter on the current texture.
 *
 * @note color levels can be defined for this filter thanks to @ref black_and_white_levels
 *
 * @~french
 * Applique un filtre sepia sur la texture en cours
 * @note La formule de conversion peut être ajustée grâce à
 * @ref black_and_white_levels.
 * @~
 * @since 1.018 (Tao 1.45)
 */
sepia();


/**
 * @~english
 * Defines erosion color.
 * This color is used to determined regions to erode into the image.
 *
 * @param r red component of the color.
 * @param g green component of the color.
 * @param b blue component of the color.
 * Its default value is the color of the erosion center.
 *
 * @note This function is optional to the Erosion filter.
 *
 * @~french
 * Définit la couleur d'érosion.
 * Cette couleur est celle qui sera érodée par le filtre @ref erode.
 * Par défaut, c'est la couleur du point du centre d'érosion passé à la
 * fonction @ref erode.
 *
 * @param r Composante rouge.
 * @param g Composante verte.
 * @param b Composante bleue.
 */
erode_color(r:real, g:real, b:real);

/**
 * @~english
 * Defines erosion radius.
 * This radius defines the size of the erosion circle.
 *
 * @param radius radius of the erosion circle.
 * Its default value is 1.0 (It corresponds to the entire image).
 *
 * @note This function is optional to the Erosion filter.
 *
 * @~french
 * Définit le rayon d'érosion.
 * La valeur par défaut est 1.0, ce qui correspond à l'image entière.
 */
erode_radius(radius:real);

/**
 * @~english
 * Applies an Erosion filter on the current texture.
 * The pixels that have a color that is close to the erosion color
 * (@ref erode_color, or the color of (@p x, @p y) by default) are made
 * transparent.
 *
 * @param x x-coordinate of the erosion center.
 * @param y y-coordinate of the erosion center.
 * @param threshold threshold of the erosion color.
 *
 * @~french
 * Applique un filtre d'érosion à la texure courante.
 * Les parties de l'image qui ont une couleur proche de la couleur
 * d´érosion (@ref erode_color) deviennent transparentes.
 * @ref erode_radius permet de limiter la zone d'érosion.
 *
 * @param x Abscisse du centre d'érosion.
 * @param y Ordonnée du centre d'érosion.
 * @param threshold Tolérance de l'érosion.
 */
erode(x:real, y:real, threshold:real);


/**
 * @~english
 * Render the given code with a drop shadow.
 * The given code is drawn in a texture of size @a W x @a H pixels,
 * at position @a X, @a Y. A drop shadow is behind it at a depth
 * specified by @ref shadow_depth.
 * Many attributes of the drop shadows can be controlled individually:
 * @ref shadow_angle, @ref shadow_offset, @ref shadow_color,
 * @ref shadow_opacity, @ref shadow_blur, @ref shadow_depth,
 * @ref shadow_filter.
 *
 * @param X Horizontal coordinate of the center of the draw area
 * @param Y Vertical coordinate of the center of the draw area
 * @param W Width of the draw area
 * @param H Height of the draw area
 * @param Body Rendering code for the contents of the draw area
 *
@code
shadow 0, 0, 800, 600,
    color "red"
    circle -20, -20, 30
    font "Arial", 50
    color "blue"
    text "Hello"
@endcode
 *
 * @image html TaoShadow.jpg "Simple shadow"
 *
 * @~french
 * Affiche le code donné avec une ombre portée
 * Le code donné est dessiné dans une texture de dimensions @a W x @a H
 * pixels, aux coordonnées @a X, @a Y. Une ombre portée est dessinée
 * derrière cette texture à une distance indiquée par @ref shadow_depth.
 * De nombreux attributs de l'ombre portée peuvent être contrôlés
 * individuellement :
 * @ref shadow_angle, @ref shadow_offset, @ref shadow_color,
 * @ref shadow_opacity, @ref shadow_blur, @ref shadow_depth,
 * @ref shadow_filter.
 *
 * @param X Coordonnée horizontale du centre de la zone de dessin
 * @param Y Coordonnée verticale du centre de la zone de dessin
 * @param W Largeur de la zone de tracé
 * @param H Hauteur de la zone de tracé
 * @param Body Code décrivant le contenu de la zone de tracé
 *
@code
shadow 0, 0, 800, 600,
    color "red"
    circle -20, -20, 30
    font "Arial", 50
    color "blue"
    text "Hello"
@endcode
 *
 * @image html TaoShadow.jpg "Exemple d'ombrage simple"
 *
 * @~
 * @since 1.018 (Tao 1.45)
 */
shadow(X:real, Y:real, W:integer, H:integer, Body:code); 


/**
 * @~english
 * Create a drop-shadow texture for the given rendering code
 * The given code is drawn in a texture of size @a W x @a H pixels,
 * and a drop shadow is then created for it.
 * Many attributes of the drop shadows can be controlled individually:
 * @ref shadow_angle, @ref shadow_offset, @ref shadow_color,
 * @ref shadow_opacity, @ref shadow_blur, @ref shadow_depth,
 * @ref shadow_filter.
 *
 * @param W Width of the draw area
 * @param H Height of the draw area
 * @param Body Rendering code for the contents of the draw area
 *
 * @~french
 * Crée une texture d'ombre portée pour le code donné
 * Le code donné est dessiné dans une texture de dimmensions @a W x @a H
 * pixels, et une texture contentant l'ombre portée correspondante est
 * retournée et activée.
 * De nombreux attributs de l'ombre portée peuvent être contrôlés
 * individuellement :
 * @ref shadow_angle, @ref shadow_offset, @ref shadow_color,
 * @ref shadow_opacity, @ref shadow_blur, @ref shadow_depth,
 * @ref shadow_filter.
 *
 * @param W Largeur de la zone de tracé
 * @param H Hauteur de la zone de tracé
 * @param Body Code décrivant le contenu de la zone de tracé
 *
 * @~
 * @since 1.018 (Tao 1.45)
 */
shadow_texture(W:integer, H:integer, Body:code); 

/**
 * @~english
 * Specify the angle in degrees for drop shadows
 * @param A Angle in degrees, 0 being towards the top
 * @see shadow
 * 
 * @~french
 * Indique l'angle en degrés pour les ombres portées
 * @param A Angle en degrés, 0 étant la verticale (115 par défaut)
 * @see shadow
 *
 * @~
 * @since 1.018 (Tao 1.45)
 */

shadow_angle (A:real);

/**
 * @~english
 * Specify the distance from the source for the drop shadow
 * @param D Distance from the origin, defaults to 5
 * @see shadow
 * 
 * @~french
 * Indique la distance entre la source et l'ombre portée
 * @param D Distance entre l'ombre portée et la source, 5 par défaut
 * @see shadow
 *
 * @~
 * @since 1.018 (Tao 1.45)
 */

shadow_offset (D:real);

/**
 * @~english
 * Specify the depth at which the shadow will be drawn
 * @param D Depth behind the source at which the shadow will be drawn
 * @see shadow
 * 
 * @~french
 * Indique la profondeur à laquelle l'ombre portée sera dessinée
 * @param D Profondeur à laquelle l'ombre portée sera dessinée
 * @see shadow
 *
 * @~
 * @since 1.018 (Tao 1.45)
 */

shadow_depth (D:real);

/**
 * @~english
 * Specify the blur radius for drop shadows
 * @param R Blur radius for subsequent drop shadows
 * @see shadow
 * 
 * @~french
 * Indique le rayon de floutage pour les ombres portées
 * @param R Rayon de floutage pour les ombres portées
 * @see shadow
 *
 * @~
 * @since 1.018 (Tao 1.45)
 */

shadow_blur (R:real);

/**
 * @~english
 * Specify the color for drop shadows
 * @param C Color for subsequent drop shadows
 * @see shadow @see shadow_opacity
 * 
 * @~french
 * Indique la couleur pour les ombres portées
 * @param C Couleur pour les ombres portées
 * @see shadow @see shadow_opacity
 *
 * @~
 * @since 1.018 (Tao 1.45)
 */

shadow_color (C:text);

/**
 * @~english
 * Specify the opacity for drop shadows
 * @param O Opacity for subsequent drop shadows (between 0 and 1)
 * @see shadow @see shadow_color
 * 
 * @~french
 * Indique l'opacité pour les ombres portées
 * @param O Opacité pour les ombres portées (entre 0 et 1)
 * @see shadow @see shadow_color
 *
 * @~
 * @since 1.018 (Tao 1.45)
 */

shadow_opacity(O:real);

/**
 * @~english
 * Specify the color filter identifying shadow casting parts of a picture
 * @param R Red component between 0 and 1 (default 0)
 * @param G Green component between 0 and 1 (default 0)
 * @param B Blue component between 0 and 1 (default 0)
 * @param A Alpha component between 0 and 1 (default 1)
 * @see shadow @see shadow_color
 * 
 * @~french
 * Indique le filtre de couleurs identifiant les parties d'un image à ombrer
 * @param R Composante rouge, entre 0 et 1 (0 par défaut)
 * @param G Composante verte, entre 0 et 1 (0 par défaut)
 * @param B Composante bleue, entre 0 et 1 (0 par défaut)
 * @param A Opacité, entre 0 et 1 (1 par défaut)
 * @see shadow @see shadow_color
 *
 * @~
 * @since 1.018 (Tao 1.45)
 */

shadow_filter(R:real, G:real, B:real, A:real);

/**
 * @~english
 * Create a new texture by applying a filter to the current one
 * Renders the current texture through a filter, typically implemented
 * using a GLSL shader program. The output texture after filtering is
 * bound to the same texture unit as the inout texture, and replaces
 * it. As seen by the rendering code, it is always the only active
 * texture and bound to texture unit 0.
 *
 * @param Code Code to execute for the filter
 *
@code
texture_unit 1
frame_texture 400, 400,
    color "pink"
    circle 0, 0, 800 * sin time^2
texture_unit 2
movie_texture "my_movie.mov"
rectangle -400, 0, texture_width, texture_height
render_to_texture { color "yellow" }
rectangle 400, 0, texture_width, texture_height
@endcode
 * @~french
 * Crée une nouvelle texture en appliquant un filtre à la texture en cours
 * Trace la texture en cours à travers un filtre, le plus souvent 
 * défini à l'aide d'un programme de shader écrit en GLSL. La texture
 * d'entrée est prise sur l'unité de texture en cours, et la texture
 * de sortie y est placée après filtrage, remplaçant la texture
 * d'origine. Pour le code de rendu, en revanche, la texture d'entrée
 * est la seule active, et est placée dans l'unité de texture 0.
 *
 * @param Code Code du filtre
@code
texture_unit 1
frame_texture 400, 400,
    color "pink"
    circle 0, 0, 800 * sin time^2
texture_unit 2
movie_texture "my_movie.mov"
rectangle -400, 0, texture_width, texture_height
render_to_texture { color "yellow" }
rectangle 400, 0, texture_width, texture_height
@endcode
 */
render_to_texture (Code:tree);

/**
 * @~english
 * Set the amount of filtering
 * Sets the amount of filtering. When the ratio is 1, the filter
 * applies fully. When the ratio is 0, the original image is
 * returned.
 *
 * @note Normally, only values between 0 and 1 (or 0% and 100%) are
 * used, but interesting effects may occasionally be achieved with
 * values that are out of range, e.g. negative values can be used
 * to enhance colors with the @ref black_and_white filter.
 *
 * @param Amount Amount of application for subsequent filters
 * 
 * @~french
 * Fixe le taux d'application des filtres
 * Fixe le taux d'application des filtres. Quand le taux est à 1, le
 * filtre s'applique complètement. Quand le taux est à 0, l'image
 * originale est préservée.
 *
 * @note Normalement, les valeurs entre 0 et 1 (ou entre 0% et 100%)
 * sont les plus utiles. Néanmoins, des effets intéressants peuvent
 * être obtenus en utilisant des valeurs en dehors de cet intervalle.
 * Par exemple, des valeurs négatives permettent d'augmenter l'intensité
 * des couleurs avec le filtre @ref black_and_white.
 *
 * @param Amount Taux d'application pour les filtres ultérieurs
 *
 * @~
 * @since 1.018 (Tao 1.45)
 */

filtering_amount(Amount:real); 

/**
 * @~english
 * Return the current filtering amount
 * @~french
 * Retourne le taux de filtrage actuel
 *
 * @~
 * @since 1.018 (Tao 1.45)
 */

filtering_amount(); 


/**
* @}
*/
