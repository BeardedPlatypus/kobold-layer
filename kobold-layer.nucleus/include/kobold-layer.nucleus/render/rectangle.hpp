#pragma once

namespace kobold_layer::nucleus::render
{
    /// <summary>
    /// <see cref="rectangle"/> defines a rectangle with the origin at the
    /// upper left.
    /// </summary>
    class rectangle
    {
    public:
        /// <summary>
        /// Creates a new <see cref="rectangle"/>.
        /// </summary>
        /// <param name="x">The x position of the origin.</param>
        /// <param name="y">The y position of the origin.</param>
        /// <param name="width">The width of the new rectangle.</param>
        /// <param name="height">The height of the new rectangle.</param>
        rectangle(const int x,
            int const y,
            int const width,
            int const height) : x(x), y(y), width(width), height(height)
        {
        }

        /// <summary>
        /// The x position of the origin of this <see cref="rectangle"/>.
        /// </summary>
        int const x;

        /// <summary>
        /// The y position of the origin of the <see cref="rectangle"/>.
        /// </summary>
        int const y;

        /// <summary>
        /// The width of this <see cref="rectangle"/>.
        /// </summary>
        int const width;

        /// <summary>
        /// The height of this <see cref="rectangle"/>.
        /// </summary>
        int const height;
    };
}
