#ifndef IN_MEMORY_CAR_REPOSITORY_H
#define IN_MEMORY_CAR_REPOSITORY_H

#include "CarRepository.h"
#include <list>

namespace repository {
	class InMemoryCarRepository : public repository::CarRepository
	{
	public:
		InMemoryCarRepository() = default;
		virtual ~InMemoryCarRepository();
		virtual void save(const domain::Car&);
	private:
		std::list<domain::Car> cars;
	};
}

#endif // !IN_MEMORY_CAR_REPOSITORY_H