/**
 * Netero sources under BSD-3-Clause
 * see LICENCE.txt
 */

#include <cassert>
#include <iostream>
#include <netero/ecs/world.hpp>

netero::ecs::World	world;

void	entityLocalScope() {
	std::cout << "ecs_entity: Create entity first" << std::endl;
	netero::ecs::Entity	first = world.createEntity();
	std::cout << "ecs_entity: Create entity second" << std::endl;
	netero::ecs::Entity	second = world.createEntity();
	std::cout << "ecs_entity: Enable entity second" << std::endl;
	second.enable();
	std::cout << "ecs_entity: entity killed" << std::endl;
	first.kill();
	assert(!first.valid());
	std::cout << "ecs_entity: update world" << std::endl;
	world.update();
	auto stat = world.getStatistic();
	assert(stat.size == 1);
	std::cout << "ecs_entity: update world" << std::endl;
	world.update();
	stat = world.getStatistic();
	assert(stat.size == 1);
}

int	main() {
	entityLocalScope();
	return 0;
}
