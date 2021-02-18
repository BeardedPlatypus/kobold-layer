#pragma once

namespace kobold_layer::clr {
	public ref class rectangle sealed {
	public:
        /// <summary>
        /// Creates a new <see cref="rectangle"/>.
        /// </summary>
        /// <param name="x">The x position of the origin.</param>
        /// <param name="y">The y position of the origin.</param>
        /// <param name="width">The width of the new rectangle.</param>
        /// <param name="height">The height of the new rectangle.</param>
        rectangle(float const x,
                  float const y,
                  float const width,
                  float const height) : x(x), y(y), width(width), height(height)
        {
        }

        /// <summary>
        /// The x position of the origin of this <see cref="rectangle"/>.
        /// </summary>
        float const x;

        /// <summary>
        /// The y position of the origin of the <see cref="rectangle"/>.
        /// </summary>
        float const y;

        /// <summary>
        /// The width of this <see cref="rectangle"/>.
        /// </summary>
        float const width;

        /// <summary>
        /// The height of this <see cref="rectangle"/>.
        /// </summary>
        float const height;
	};
}
