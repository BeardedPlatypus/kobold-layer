#include "kobold-layer.nucleus.mock/texture/texture_factory_mock.hpp"
#include "kobold-layer.nucleus.mock/texture/texture_mock.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "texture/texture_manager_implementation.hpp"

using ::testing::Return;
using ::testing::ByMove;
using ::testing::IsTrue;
using ::testing::IsFalse;

namespace kobold_layer::nucleus::texture {
	TEST(texture_manager_test, load_texture_first_time_the_texture_is_added_to_the_manager)
	{
		// Setup
		auto p_texture_mock = std::make_unique<texture_mock>();
		texture const* texture = p_texture_mock.get();

		const auto texture_path = std::filesystem::path();

		auto p_texture_factory_mock = std::make_unique<texture_factory_mock>();
		EXPECT_CALL(*(p_texture_factory_mock.get()), construct_texture(texture_path))
			.Times(1)
			.WillOnce(Return(ByMove(std::move(p_texture_mock))));

		auto texture_manager = texture_manager_implementation(std::move(p_texture_factory_mock));

		const std::string key = "key";

		// Call
		texture_manager.load_texture(key, texture_path);

		// Assert
		ASSERT_THAT(texture_manager.has_texture(key), IsTrue);
		ASSERT_THAT(texture_manager.get_texture(key), texture);
	}

	TEST(texture_manager_test, load_texture_twice_only_one_time_constructed)
	{
		auto p_texture_mock = std::make_unique<texture_mock>();
		texture const* texture = p_texture_mock.get();

		const auto texture_path_a = std::filesystem::path();
		const auto texture_path_b = std::filesystem::path();

		auto p_texture_factory_mock = std::make_unique<texture_factory_mock>();
		EXPECT_CALL(*(p_texture_factory_mock.get()), construct_texture(texture_path_a))
			.Times(1)
			.WillOnce(Return(ByMove(std::move(p_texture_mock))));

		auto texture_manager = texture_manager_implementation(std::move(p_texture_factory_mock));

		const std::string key = "key";

		// Call
		texture_manager.load_texture(key, texture_path_a);
		texture_manager.load_texture(key, texture_path_b);

		// Assert
		ASSERT_THAT(texture_manager.has_texture(key), IsTrue);
		ASSERT_THAT(texture_manager.get_texture(key), texture);
	}

	TEST(texture_manager_test, has_texture_not_loaded_returns_false)
	{
		// Setup
		auto p_texture_factory_mock = std::make_unique<texture_factory_mock>();
		const auto texture_manager = texture_manager_implementation(std::move(p_texture_factory_mock));

		// Call
		bool const result = texture_manager.has_texture("any_not_loaded_key");

		// Assert
		ASSERT_THAT(result, IsFalse());
	}
}
