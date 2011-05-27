/**
 * @defgroup Filters Filters
 * @ingroup Modules
 *
 * Apply filters on current texture.
 *
 * This module allows you to apply some basic filtering on your textures.
 *
 * For example, the following code will show how to detect outlines and add some iterative blur to it.
 * @include filters.ddd
 *
 * @image html filters.png "Output of filters.ddd"
 * @{
 */

/**
 * Applies a Gaussian filter on current texture.
 * It can be used to add blur on an image for instance.
 *
 * @param iter maximum number of iteration of the filter.
 */
gaussian(iter:integer);

/**
 * Applies a Mean filter on the current texture.
 * It can be used to remove noise of an image for instance.
 *
 * @param iter maximum number of iteration of the filter.
 */
mean(iter:integer);

/**
 * Applies an Embross filter on the current texture.
 * It can be used to simulate 3D in an image for instance.
 *
 * @param iter maximum number of iteration of the filter.
 */
emboss(iter:integer);

/**
 * Applies a Sharpness filter on the current texture.
 * It can be used to highlight details of an image for instance.
 *
 * @param iter maximum number of iteration of the filter.
 */
sharpness(iter:integer);

/**
 * Applies a Laplacian filter on the current texture.
 * It can be used to detect oulines of an image for instance.
 *
 * @param iter maximum number of iteration of the filter.
 */
laplacian(iter:integer);

/**
 * Defines color levels for Black & White filter.
 * These levels define the color tolerance into the Black & White filter.
 *
 * @param ratio_r ratio of the red component of the color. Its default values is 0.3.
 * @param ratio_g ratio of the green component of the color. Its default values is 0.3.
 * @param ratio_b ratio of the blue component of the color. Its default values is 0.3.
 *
 * @note This function is optionnal to apply Black & White filter
 */
black_and_white_levels(ratio_r:real, ratio_g:real, ratio_b:real);

/**
 * Applies a Black & White filter on the current texture.
 * * It can be used to transform a color map into a black & white one.
 *
 * @note color levels can be defined for this filter thanks to @ref black_and_white_levels
 *
 */
black_and_white();

/**
 * Defines erosion color.
 * This color is used to determined regions to erode into the image.
 *
 * @param r red component of the color.
 * @param g green component of the color.
 * @param b blue component of the color.
 * Its default value is the color of the erosion center.
 *
 * @note This function is optionnal to the Erosion filter.
 */
erode_color(r:real, g:real, b:real);

/**
 * Defines erosion radius.
 * This radius defines the size of the erosion circle.
 *
 * @param radius radius of the erosion circle.
 * Its default value is 1.0 (It corresponds to the entire image).
 *
 * @note This function is optionnal to the Erosion filter.
 */
erode_radius(radius:real);

/**
 * Applies an Erosion filter on the current texture.
 * It can be used to erode some part of an image with a same color.
 *
 * @param x x-coordinate of the erosion center.
 * @param y y-coordinate of the erosion center.
 * @param threshold threshold of the erosion color.
 *
 * @note erosion color can be defined thanks to @ref erode_color.
 * @note erosion radius can be defined thanks to @ref erode_radius.
 *
 */
erode_radius(x:real, y:real, threshold:real);


/**
* @}
*/
