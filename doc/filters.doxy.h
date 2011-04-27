/**
 * @defgroup DigitalClock Digital Clock
 * @ingroup Modules
 *
 * Shows a digital clock.
 *
 * You can use the Digital Clock module in your presentation if you want
 * to display the time like a traditional alarm clock does.
 *
 * For example, the following document
 * (<a href="examples/fonts.ddd">fonts.ddd</a>) will show a nice clock
 * 40 pixels high:
 * @include digital_clock.ddd
 *
 * @image html digital_clock.png "Output of digital_clock.ddd"
 * @{
 */


//
// Settings
//


/**
 * The color for "ON" segments
 */
text dc_segment_color_on  = "#229988";
/**
 * The color for "OFF" segments
 */
text dc_segment_color_off = "#004477";
/**
 * The display's background color
 */
text dc_background_color  = "#003366";
/**
 * Whether or not to display 6 and 9 with a horizontal bar
 *   @li @c "off" Do not display a horizontal bar
 *   @li @c "on"  Display a horizontal bar
 * @bug Should be a boolean
 */
text dc_hbar_6_9          = "off";
/**
 * Whether or not to display the hour with a leading zero
 *   @li @c "true"  Display a leading zero
 *   @li @c "false" Do not display a leading zero
 */
text dc_hours_leading_zero = "false";
/**
 * Whether or not the clock displays seconds
 *   @li @c "true"  Display hours, minutes and seconds
 *   @li @c "false" Display hours and minutes only
 */
text dc_show_seconds = "false";
/**
 * The time to display
 * If @ref dc_time is -1.0, use current time. Otherwise, @ref dc_time is
 * to display, expressed in seconds as per POSIX time standards.
 * This variable is of type real, so it can include a fractional part.
 */
real dc_time = -1.0;


/**
 * Shows a digital clock with specified size and position.
 * The clock is centered at (@a cX, @a cY) and z=0.
 * By default, it shows the current local time. You can display
 * the time for any other date by setting @ref dc_time accordingly. Note
 * however that dc_time is always shown in local time format. \n
 *
 * The digits are similar in shape with those of real digital clocks
 * with LED, VFD or LCD displays: they are made of 7 segments that are
 * either on or off. The color for each state is configurable with
 * @ref dc_segment_color_on and @ref dc_segment_color_off, the background
 * being controlled by @ref dc_background_color. \n
 *
 * The clock has a number of other configuration options. You may
 * show or hide the leading zero for the hours display (@ref
 * dc_hours_leading_zero); you may change the format to hours:minutes or
 * hours:minutes:seconds (@ref dc_show_seconds). You may even select how
 * 6 and 9 and drawn (with or without a horizontal bar), thanks to
 * @ref dc_hbar_6_9. \n
 *
 * Currently, only the 24-hour format is supported; you cannot switch to
 * the AM/PM format.
 *
 * @param cX x coordinate of the clock's center
 * @param cY y coordinate of the clock's center
 * @param cH the clock's height. The width is 2.86555 * @a cH when the
 *    clock shows only hours and minutes, and 4.5042 * @a cH when seconds
 *     are enabled.
 */
digital_clock(real cX, real cY, real cH);

/**
 * Shows a digital clock of height 238 px at (@a x, @a y).
 */
digital_clock(real x, real y);

/**
 * Shows a digital clock of height 238 px at (0, 0).
 */
digital_clock();

/**
 * @}
 */
