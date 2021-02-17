#pragma once

namespace kobold_layer::nucleus::render
{
    /// <summary>
    /// <see cref="rectangle"/> defines a rectangle with the origin at the
    /// upper left.
    /// </summary>
    template <typename T>
    class rectangle sealed
    {
    public:
        /// <summary>
        /// Creates a new <see cref="rectangle"/>.
        /// </summary>
        /// <param name="x">The x position of the origin.</param>
        /// <param name="y">The y position of the origin.</param>
        /// <param name="width">The width of the new rectangle.</param>
        /// <param name="height">The height of the new rectangle.</param>
        rectangle(T const x,
                  T const y,
                  T const width,
                  T const height) : x(x), y(y), width(width), height(height)
        {
        }

        /// <summary>
        /// The x position of the origin of this <see cref="rectangle"/>.
        /// </summary>
        T const x;

        /// <summary>
        /// The y position of the origin of the <see cref="rectangle"/>.
        /// </summary>
        T const y;

        /// <summary>
        /// The width of this <see cref="rectangle"/>.
        /// </summary>
        T const width;

        /// <summary>
        /// The height of this <see cref="rectangle"/>.
        /// </summary>
        T const height;
    };

    template class rectangle<int>;
    template class rectangle<float>;
}
