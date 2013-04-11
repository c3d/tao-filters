/**
 * @~english
 * @taomoduledescription{Filters, Filters}
 *
 * <tt>import Filters</tt> - Apply filters on imported images.
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
 *
 * <tt>import Filters</tt> - Applique des filtres sur des images.
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
 * @param n maximum number of iteration of the filter.
 *
 * @note The result texture is obtained thanks to RenderToTexture module.
 *
 * @~french
 * Applique un filtre Gaussien sur la texture courante.
 * Ce filtre permet d'ajouter du flou à l'image.
 *
 * @param n Nombre d'itérations du filtre.
 */
gaussian(n:integer);

/**
 * @~english
 * Applies a Mean filter on the current texture.
 * It can be used to remove noise of an image for instance.
 *
 * @param n number of iteration of the filter.
 *
 * @note The result texture is obtained thanks to RenderToTexture module.
 *
 * @~french
 * Applique un filtre moyenneur sur la texture courante.
 * Ce filtre permet de réduire le bruit de l'image.
 *
 * @param n Nombre d'itérations du filtre.
 */
mean(n:integer);

/**
 * @~english
 * Applies an Embross filter on the current texture.
 * It can be used to simulate 3D in an image for instance.
 *
 * @param n number of iteration of the filter.
 *
 * @note The result texture is obtained thanks to RenderToTexture module.
 *
 * @~french
 * Applique un filtre de relief sur la texture courante.
 * Ce filtre permet de créer un effet de relief sur la texture courante.
 *
 * @param n Nombre d'itérations du filtre.
 */
emboss(n:integer);

/**
 * @~english
 * Applies a Sharpness filter on the current texture.
 * It can be used to highlight details of an image for instance.
 *
 * @param n maximum number of iteration of the filter.
 *
 * @note The result texture is obtained thanks to RenderToTexture module.
 *
 * @~french
 * Applique un filtre de netteté à la texture courante.
 * Ce filtre permet d'améliorer le piqué de l'image.
 *
 * @param n Nombre d'itérations du filtre.
 */
sharpness(n:integer);

/**
 * @~english
 *
 * Applies a Laplacian filter on the current texture.
 * It can be used to detect oulines of an image for instance.
 *
 * @param n maximum number of iteration of the filter.
 *
 * @note The result texture is obtained thanks to RenderToTexture module.
 *
 * @~french
 * Applique un filtre Laplacien à la texture courante.
 * Ce filtre permet de faire une détection de contour.
 *
 * @param n Nombre d'itérations du filtre.
 */
laplacian(n:integer);

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
 */
black_and_white_levels(cr:real, cg:real, cb:real);

/**
 * @~english
 * Applies a Black & White filter on the current texture.
 * It can be used to transform a color map into a black & white one.
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
* @}
*/
